/*
This file is part of Cohtml, modern user interface library for
games. Release $RELEASE$. Build $VERSION$ for $LICENSEE$.

Copyright (c) 2012-2018 Coherent Labs AD and/or its licensors. All
rights reserved in all media.

The coded instructions, statements, computer programs, and/or related
material (collectively the "Data") in these files contain confidential
and unpublished information proprietary Coherent Labs and/or its
licensors, which is protected by United States of America federal
copyright law and by international treaties.

This software or source code is supplied under the terms of a license
agreement and nondisclosure agreement with Coherent Labs Limited and may
not be copied, disclosed, or exploited except in accordance with the
terms of that agreement. The Data may not be disclosed or distributed to
third parties, in whole or in part, without the prior written consent of
Coherent Labs Limited.

COHERENT LABS MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS
SOURCE CODE FOR ANY PURPOSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER, ITS AFFILIATES,
PARENT COMPANIES, LICENSORS, SUPPLIERS, OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OR PERFORMANCE OF THIS SOFTWARE OR SOURCE CODE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "CohtmlPluginPrivatePCH.h"
#include "CohtmlFileHandler.h"
#include "CohtmlSystemHolder.h"

#include <cohtml/System.h>
#include "CohHelpers.h"
#include <CohTexture.h>

#include "Engine/Texture2D.h"
#include "HAL/PlatformFilemanager.h"
#include "SslModule.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

namespace
{
bool FORCEINLINE IsGarbageCollectionRunning()
{
	// This check is necessary because if we use LoadObject while GC is running
	// we hit an error and the game crashes. We leave the task for the next frame.
	// We assume that then there will be no GC.
	// This check is taken from UObjectGlobals.cpp.
	return GIsSavingPackage || (IsInGameThread() && IsGarbageCollecting());
}

bool FORCEINLINE IsUrealResource(EUnrealResourceType ResourceType)
{
	return ResourceType == EUnrealResourceType::PreloadedImage
		|| ResourceType == EUnrealResourceType::PreloadedImageInAtlas;
}

bool FUnrealResourcePtr::IsValid() const
{
	return ResourcePtr && ResourcePtr->IsA<UTexture2D>() == (IsUrealResource(ResourceType)) &&
		ResourcePtr->IsA<UTextureRenderTarget2D>() == (ResourceType == EUnrealResourceType::LiveView);
}

renoir::PixelFormat FUnrealResourcePtr::GetImageFormat() const
{
	switch (ResourceType)
	{
	case EUnrealResourceType::PreloadedImage:
	case EUnrealResourceType::PreloadedImageInAtlas:
		return GetImageFormat(Cast<UTexture2D>(ResourcePtr));
	case EUnrealResourceType::LiveView:
		return GetImageFormat(Cast<UTextureRenderTarget2D>(ResourcePtr));
	}
	verify(false);
	return renoir::PF_USER_FORMAT;
}

cohtml::IAsyncResourceResponse::UserImageData FUnrealResourcePtr::GetImageData()
{
	switch (ResourceType)
	{
	case EUnrealResourceType::PreloadedImageInAtlas:
		return GetImageData(Cast<UTexture2D>(ResourcePtr), AtlasSizes);
	case EUnrealResourceType::PreloadedImage:
		return GetImageData(Cast<UTexture2D>(ResourcePtr), nullptr);
	case EUnrealResourceType::LiveView:
		return GetImageData(Cast<UTextureRenderTarget2D>(ResourcePtr));
	}
	verify(false);
	return cohtml::IAsyncResourceResponse::UserImageData();
}

renoir::PixelFormat FUnrealResourcePtr::GetImageFormat(const UTexture2D* Texture)
{
	return renoir::FromUnrealTextureFormat(Texture->PlatformData->PixelFormat);
}

renoir::PixelFormat FUnrealResourcePtr::GetImageFormat(const UTextureRenderTarget2D* Texture)
{
	return renoir::FromUnrealTextureFormat(Texture->GetFormat());
}

cohtml::IAsyncResourceResponse::UserImageData FUnrealResourcePtr::GetImageData(UTextureRenderTarget2D* Texture)
{
	cohtml::IAsyncResourceResponse::UserImageData ImageData;
	ImageData.Width = Texture->SizeX;
	ImageData.Height = Texture->SizeY;
	ImageData.ContentRectX = 0;
	ImageData.ContentRectY = 0;
	ImageData.ContentRectWidth = ImageData.Width;
	ImageData.ContentRectHeight = ImageData.Height;
	ImageData.Format = GetImageFormat(Texture);
	ImageData.Origin = renoir::ImageOrigin::TopLeft;
	ImageData.ImageHandle = 0;
	ImageData.TextureBatchingHint = nullptr;

	renoir::Texture2D TextureDescription;
	TextureDescription.Width = ImageData.Width;
	TextureDescription.Height = ImageData.Height;
	TextureDescription.Format = ImageData.Format;
	TextureDescription.Origin = ImageData.Origin;
	TextureDescription.Props = renoir::IMP_None;
	TextureDescription.IsRenderTarget = false;
	TextureDescription.WillNeverOverwrite = true;
	TextureDescription.MipsCount = Texture->GetNumMips();
	TextureDescription.SamplesCount = 1;
	// The backend will take ownership of the texture
	ImageData.Texture = new FCohTextureUserWrapData(TextureDescription, Texture);

	return ImageData;
}

cohtml::IAsyncResourceResponse::UserImageData FUnrealResourcePtr::GetImageData(UTexture2D* Texture, const uint32* InAtlasSizes)
{
	cohtml::IAsyncResourceResponse::UserImageData ImageData;
	ImageData.Width = Texture->GetSizeX();
	ImageData.Height = Texture->GetSizeY();
	if (InAtlasSizes)
	{
		ImageData.ContentRectX = InAtlasSizes[0];
		ImageData.ContentRectY = InAtlasSizes[1];
		ImageData.ContentRectWidth = InAtlasSizes[2];
		ImageData.ContentRectHeight = InAtlasSizes[3];
	}
	else
	{
		ImageData.ContentRectX = 0;
		ImageData.ContentRectY = 0;
		ImageData.ContentRectWidth = ImageData.Width;
		ImageData.ContentRectHeight = ImageData.Height;
	}
	ImageData.Format = GetImageFormat(Texture);
	ImageData.Origin = renoir::ImageOrigin::TopLeft;
	ImageData.TextureBatchingHint = Texture;

	renoir::Texture2D TextureDescription;
	TextureDescription.Width = ImageData.Width;
	TextureDescription.Height = ImageData.Height;
	TextureDescription.Format = ImageData.Format;
	TextureDescription.Origin = ImageData.Origin;
	TextureDescription.Props = renoir::IMP_None;
	TextureDescription.IsRenderTarget = false;
	TextureDescription.WillNeverOverwrite = true;
	TextureDescription.MipsCount = Texture->GetNumMips();
	TextureDescription.SamplesCount = 1;
	// The backend will take ownership of the texture
	ImageData.Texture = new FCohTextureUserWrapData(TextureDescription, Texture);

	return ImageData;
}
}

FCohtmlStreamReader::FCohtmlStreamReader(const TCHAR* Path)
	: FilePath(Path)
	, FileSize(0)
{
	GetOrCreateFileHandle();
}

IFileHandle* FCohtmlStreamReader::GetOrCreateFileHandle()
{
	uint32 CurrentThreadId = FPlatformTLS::GetCurrentThreadId();
	IFileHandle* Handle = nullptr;
	{
		FScopeLock Lock(&CriticalSection);
		if (ThreadFileHandleMap.Contains(CurrentThreadId))
		{
			Handle = ThreadFileHandleMap[CurrentThreadId].Get();
		}
		else
		{
			Handle = FPlatformFileManager::Get().GetPlatformFile().OpenRead(*FilePath);
			if (Handle)
			{
				ThreadFileHandleMap.Emplace(CurrentThreadId, Handle);
			}
		}
	}

	if (Handle)
	{
		if (!FileSize)
		{
			FileSize = Handle->Size();
		}
		// Make sure that all handles agree on the size
		check(Handle->Size() == FileSize);
	}

	return Handle;
}

unsigned FCohtmlStreamReader::GetSize()
{
	return FileSize;
}

unsigned FCohtmlStreamReader::Read(unsigned Offset, unsigned char* Buffer, unsigned Count)
{
	auto Handle = GetOrCreateFileHandle();
	if (Handle && Buffer && Handle->Seek(Offset) && Handle->Read(Buffer, Count))
	{
		return FMath::Min(Count, static_cast<unsigned>(Handle->Size() - Offset));
	}
	return 0;
}

void FCohtmlStreamReader::Close()
{
	ThreadFileHandleMap.Empty();
}

// This class is an adapter between the cohtml::IAsyncStreamResponse and the non-stream version
// This saves us from reimplementing HTTP support for OnResourceStreamRequest
class HttpStreamResponseAdapter : public cohtml::IAsyncResourceResponse
{
public:
	HttpStreamResponseAdapter(cohtml::IAsyncResourceStreamResponse* Response)
		: StreamResponse(Response)
	{}

	virtual void ReceiveUserImage(const UserImageData&) override { check(false); }
	virtual void SignalProgress() override { check(false); }
	virtual void SetResponseURL(const char*) override { }
	virtual void SetHeader(const char*, const char*) override { }

	virtual void* GetSpace(unsigned long long size) override
	{
		DataBuffer.SetNumUninitialized(size);
		return DataBuffer.GetData();
	}
	virtual void SetStatus(unsigned short Status) override
	{
		ResponseCode = Status;
	}
	virtual void Finish(cohtml::IAsyncResourceResponse::Status Status) override
	{
		if (Status == Success && EHttpResponseCodes::IsOk(ResponseCode))
		{
			StreamResponse->SetStreamReader(new FCohtmlMemoryBufferStreamReader(MoveTemp(DataBuffer)));
			StreamResponse->Finish(cohtml::IAsyncResourceStreamResponse::Success);
		}
		else
		{
			StreamResponse->Finish(cohtml::IAsyncResourceStreamResponse::Failure);
		}
		delete this;
	}

private:
	TArray<uint8> DataBuffer;
	cohtml::IAsyncResourceStreamResponse* StreamResponse;
	int32 ResponseCode;
};

FCohtmlFileHandler::FCohtmlFileHandler()
#if defined(COHTML_UE4_417_SUPPORT)
	: GameRoot(FPaths::GameDir())
#else
	: GameRoot(FPaths::ProjectDir())
#endif
	, GameContent(CohtmlGetProjectContentDir())
#if PLATFORM_PS4 || PLATFORM_DPX || PLATFORM_XBOXONE || PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_SWITCH
	, MaxSimultaneousHttpRequests(6)
#else
	, MaxSimultaneousHttpRequests(24)
#endif
{
#if WITH_SSL
	//make sure the SSL module is loaded on the main thread
	FSslModule::Get();
#endif

	FallbackURLsOverride = ICohtmlPlugin::Get().OnURLRequest;
}

FCohtmlFileHandler::~FCohtmlFileHandler()
{
	for (auto& task : UnrealResourceQueue)
	{
		task.Response->Finish(cohtml::IAsyncResourceResponse::Failure);
	}
}

FURLWithFallbacks FCohtmlFileHandler::GeneratePossibleURLs(const cohtml::IAsyncResourceRequest* Request)
{
	FURLWithFallbacks ResultingURLs(Request->GetAbsoluteURL(), Request->GetFallbackURLs());
	if (FallbackURLsOverride.IsBound())
	{
		FallbackURLsOverride.Execute(ResultingURLs);
	}
	return ResultingURLs;
}

void FCohtmlFileHandler::OnResourceRequest(const cohtml::IAsyncResourceRequest* Request,
	cohtml::IAsyncResourceResponse* Response)
{
	FURLWithFallbacks ResultingURLs = GeneratePossibleURLs(Request);

	EResourceProtocol ResourceProtocol;
	if (!TryGetResourcePath(Request, ResourceProtocol, ResultingURLs))
	{
		Response->Finish(cohtml::IAsyncResourceResponse::Failure);
		return;
	}
	FString ResultPath = ResultingURLs.BaseURL;

	if (ResourceProtocol == EResourceProtocol::Http)
	{
		if (!TryEnqueueHttpResource(ResultingURLs, Request, Response))
		{
			Response->Finish(cohtml::IAsyncResourceResponse::Failure);
		}
		return;
	}
	// Only add non-Http files to the directory watcher
#if WITH_EDITOR
	FCohtmlDirectoryWatcher::Get().OnAssetLoadedByView.ExecuteIfBound(Request->GetURL());
#endif
	if (ResourceProtocol == EResourceProtocol::UnrealAsset)
	{
		if (!TryEnqueueUnrealResource(ResultPath, Response))
		{
			Response->Finish(cohtml::IAsyncResourceResponse::Failure);
		}
		return;
	}
	// If we reached here, the protocol must be coui
	check(ResourceProtocol == EResourceProtocol::Coui);
	ReadRawResource(Request, Response, ResultPath);
}

void FCohtmlFileHandler::OnResourceStreamRequest(const cohtml::IAsyncResourceRequest* Request,
	cohtml::IAsyncResourceStreamResponse* Response)
{

	FURLWithFallbacks ResultingURLs(Request->GetAbsoluteURL(), Request->GetFallbackURLs());
	EResourceProtocol ResourceProtocol;

	if (!TryGetResourcePath(Request, ResourceProtocol, ResultingURLs))
	{
		Response->Finish(cohtml::IAsyncResourceStreamResponse::Failure);
		return;
	}
	// We should never get a request to stream UE4 assets
	check(ResourceProtocol != EResourceProtocol::UnrealAsset);

	if (ResourceProtocol == EResourceProtocol::Http)
	{
		// Simulate a standard HTTP response
		OnResourceRequest(Request, new HttpStreamResponseAdapter(Response));
		return;
	}
	// If we reached here, the protocol must be coui
	check(ResourceProtocol == EResourceProtocol::Coui);

	FString ResultPath = ResultingURLs.BaseURL;
	auto Stream = new FCohtmlStreamReader(*ResultPath);
	if (!Stream->IsValid())
	{
		Stream->Close();
		Response->Finish(cohtml::IAsyncResourceStreamResponse::Failure);
		return;
	}

	Response->SetStreamReader(Stream);
	Response->Finish(cohtml::IAsyncResourceStreamResponse::Success);
}

/// Called when the backend wants a load to abort. The user is STILL REQUIRED
/// to call Finish on the resource response with the associated request.
void FCohtmlFileHandler::OnAbortResourceRequest(unsigned id)
{
	check(false);
}

void FCohtmlFileHandler::LoadAtlasMetaData()
{
	AtlasMetaData.LoadAtlasMetaData();
}

void FCohtmlFileHandler::ReadRawResource(const cohtml::IAsyncResourceRequest* Request, cohtml::IAsyncResourceResponse* Response, const FString& ResourcePath)
{
	int64 Start = 0;
	int64 End = 0;
	bool bIsRangeRequest = IsRangeRequest(Start, End, Request);
	TArray<uint8> Buffer;
	int64 FileSize = 0;

	if (!TryReadFile(ResourcePath, Start, End, bIsRangeRequest, Buffer, FileSize))
	{
		COHTML_UE_LOG(Error, TEXT("Could not read file '%s'."), *ResourcePath);
		Response->Finish(cohtml::IAsyncResourceResponse::Failure);
		return;
	}
	SetResponseHeadersForCoui(FileSize, Buffer.Num(), Start, bIsRangeRequest, Response);
	FMemory::Memcpy(Response->GetSpace(Buffer.Num()), (const char*)Buffer.GetData(), Buffer.Num());
	Response->Finish(cohtml::IAsyncResourceResponse::Success);
}

FString FCohtmlFileHandler::ResolveCouiToGameContent(FString InPath)
{
	InPath = InPath.RightChop(7/*coui://*/);
	return GameContent / InPath;
}

bool FCohtmlFileHandler::TryGetResourcePath(const cohtml::IAsyncResourceRequest* Request, EResourceProtocol& ResourceProtocol, FURLWithFallbacks& ResultPathWithFallbacks)
{
	FString ResultPath = ResultPathWithFallbacks.BaseURL;

	// Check if we are trying to use preloaded image. If we are the path will be handled in TryUseUserResource,
	// so we just return true.
	if (ResultPath.Contains(TEXT("Texture2D'")) || ResultPath.Contains(TEXT("TextureRenderTarget2D'")))
	{
		ResourceProtocol = EResourceProtocol::UnrealAsset;
		return true;
	}

	if (ResultPath.StartsWith(TEXT("http://")) || ResultPath.StartsWith(TEXT("https://")))
	{
		ResourceProtocol = EResourceProtocol::Http;
		return true;
	}

	if (!ResultPath.StartsWith(TEXT("coui://")))
	{
		COHTML_UE_LOG(Warning, TEXT("Got unexpected protocol - %s!"), *ResultPath.Mid(0, ResultPath.Find("://") + 3));
		return false;
	}

	ResourceProtocol = EResourceProtocol::Coui;
	FString PathFromContent = ResolveCouiToGameContent(ResultPath);
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (!PlatformFile.FileExists(*PathFromContent))
	{
		if (ResultPathWithFallbacks.PossibleFallbacks.Num() > 0)
		{
			// The requested URL becomes the first fallback and we remove it from the
			// list of possible fallbacks so that we don't request it again
			ResultPathWithFallbacks.BaseURL = ResultPathWithFallbacks.PossibleFallbacks[0];
			ResultPathWithFallbacks.PossibleFallbacks.RemoveAt(0);
			COHTML_UE_LOG(Display, TEXT("Unable to find '%s', falling back to '%s''")
						 , *PathFromContent, *ResultPathWithFallbacks.BaseURL);
			return TryGetResourcePath(Request, ResourceProtocol, ResultPathWithFallbacks);
		}
		return false;
	}
	ResultPathWithFallbacks.BaseURL = PathFromContent;
	return true;
}

namespace
{
	static const int64 UnboundedRequest = -1;
	static const int64 MaxPartialReponseSize = 1 * 1024 * 1024;

	int64 GetActualEndByte(int64 FileSize, int64 Start, int64 End, bool bIsRangeRequest)
	{
		if (End == UnboundedRequest)
		{
			End = FileSize - 1;

			// Clamp range requests since new chunks will be requested
			// when needed
			if (bIsRangeRequest && (End - Start > MaxPartialReponseSize))
			{
				End = Start + MaxPartialReponseSize;
			}
		}
		return End;
	}
}

bool FCohtmlFileHandler::IsRangeRequest(int64& Start, int64& End,
	const cohtml::IAsyncResourceRequest* Request)
{
	Start = 0;
	End = UnboundedRequest;

	auto RangeHeader = Request->GetHeaderValue("Range");
	if (!RangeHeader || !strlen(RangeHeader))
	{
		return false;
	}
	// Verify the beginning of the header value
	FString RangePrefix(TEXT("bytes="));
	FString RangeValue(ANSI_TO_TCHAR(Request->GetHeaderValue("Range")));
	if (RangeValue.Contains(RangePrefix))
	{
		int32 DashIndex;
		if (RangeValue.FindChar('-', DashIndex))
		{
			FString RangeFrom = RangeValue.Mid(RangePrefix.Len(), DashIndex - RangePrefix.Len());
			Start = FCString::Strtoui64(*RangeFrom, nullptr, 10);

			if (RangeValue.Len() > DashIndex + 1)
			{
				FString RangeTo = RangeValue.Mid(DashIndex + 1);
				End = FCString::Strtoui64(*RangeTo, nullptr, 10);
			}
		}
		else
		{
			COHTML_UE_LOG(Log, TEXT("Request has a 'Range' header but does not specify a valid byte range!"));
		}
	}
	else
	{
		COHTML_UE_LOG(Log, TEXT("Request has a 'Range' header but does not start with the 'bytes=' prefix!"));
	}

	return true;
}

bool FCohtmlFileHandler::TryReadFile(const FString& Url, int64 Start, int64 End, bool bIsRangeRequest,
	TArray<uint8>& OutBuffer, int64& OutFileSize)
{
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	// Windows refuses to open a file for reading if any other process is currently writing to it.
	// In the case of LiveReload it is extremely likely that some text editor hasn't finished saving
	// the file. So we force Windows to give us access to it by telling UE4 we want write access
	// (even thought we don't really need it).

	TUniquePtr<IFileHandle> File(PlatformFile.OpenRead(*Url, true));
	if (!File)
	{
		return false;
	}
	OutFileSize = File->Size();

	if (OutFileSize == 0)
	{
		COHTML_UE_LOG(Warning, TEXT("Attempt to load an empty file: %s"), *Url);
		return false;
	}
	if (Start >= OutFileSize)
	{
		if (bIsRangeRequest)
		{
			// Range requests starting after the end of file will be handled as Range Not Satisfiable
			return true;
		}
		else
		{
			COHTML_UE_LOG(Warning, TEXT("Attempt to start reading after file end: %s"), *Url);
			return false;
		}

	}

	if (End > OutFileSize - 1)
	{
		// clamp End if trying to read after the file size
		End = OutFileSize - 1;
	}
	bool bIsUnbounded = End == UnboundedRequest;

	check(Start >= 0 && Start < OutFileSize);
	check((End >= 0 && End < OutFileSize) || bIsUnbounded);
	check(End >= Start || bIsUnbounded);

	End = GetActualEndByte(OutFileSize, Start, End, bIsRangeRequest);
	File->Seek(Start);
	auto ContentSize = End - Start + 1;
	OutBuffer.SetNumZeroed(ContentSize);
	bool bSuccess = File->Read(OutBuffer.GetData(), ContentSize);
	return bSuccess;
}

void FCohtmlFileHandler::SetResponseHeadersForCoui(int64 FileSize, int64 ContentSize, int64 Start,
	bool bIsRangeRequest, cohtml::IAsyncResourceResponse* Response)
{
	if (bIsRangeRequest)
	{
		Response->SetHeader("Accept-Ranges", "bytes");

		auto End = Start + ContentSize - 1;
		auto ContentRange = FString::Printf(TEXT("bytes %d-%d/%d"), Start, End, FileSize);
		Response->SetHeader("Content-Range", TCHAR_TO_ANSI(*ContentRange));

		auto ContentLength = FString::FromInt(ContentSize);
		Response->SetHeader("Content-Length", TCHAR_TO_ANSI(*ContentLength));

		const unsigned PartialContent = 206;
		const unsigned RequestedRangeNotSatisfiable = 416;
		Response->SetStatus(Start < FileSize ? PartialContent : RequestedRangeNotSatisfiable);
	}
	else
	{
		Response->SetStatus(200);
	}
}

bool FCohtmlFileHandler::TryEnqueueUnrealResource(const FString& RelativePath, cohtml::IAsyncResourceResponse* Response)
{
	// We can't load all images directly - this is to avoid a limitation of renoir
	// which is unable to work with non-premultiplied images
	// Attempt to preload only if the asset is an ue4 object path
	bool bIsPreloadedImage = RelativePath.Contains(TEXT("Texture2D'"));
	bool bIsLiveView = RelativePath.Contains(TEXT("TextureRenderTarget2D'"));
	check(bIsPreloadedImage || bIsLiveView);

	FStringAssetReference RelativePathAsset = RelativePath;
	FStringAssetReference RequestPathAsset = RelativePathAsset;

	uint32 SubTextureAtlasSizes[4] = { 0,0,0,0 };
	EUnrealResourceType ResourceType = EUnrealResourceType::PreloadedImage;
	if (bIsPreloadedImage)
	{
		ResourceType = EUnrealResourceType::PreloadedImage;

		// Check if the texture is part of an Atlas
		auto AtlasData = AtlasMetaData.GetAtlasedTextures().Find(RequestPathAsset.GetAssetPathString());
		if (AtlasData)
		{
			ResourceType = EUnrealResourceType::PreloadedImageInAtlas;
			RequestPathAsset = AtlasData->AtlasPath;
			SubTextureAtlasSizes[0] = AtlasData->OriginX;
			SubTextureAtlasSizes[1] = AtlasData->OriginY;
			SubTextureAtlasSizes[2] = AtlasData->Width;
			SubTextureAtlasSizes[3] = AtlasData->Height;
		}
	}
	else if (bIsLiveView)
	{
		ResourceType = EUnrealResourceType::LiveView;
	}

	FUnrealResourceTask Task(RequestPathAsset, Response, ResourceType, RelativePathAsset, SubTextureAtlasSizes);
	if (Task.AssetName.IsNull())
	{
		return false;
	}
	{
		FScopeLock ScopeLock(&UnrealResourceLock);
		UnrealResourceQueue.Add(Task);
	}

	ScheduleUnrealResourceProcessing_AnyThread();
	return true;
}

class FCohtmlUnrealResourceLoaderTask
{
	FCohtmlFileHandler* FileHandler;
public:
	FCohtmlUnrealResourceLoaderTask(FCohtmlFileHandler* InFileHandler)
		: FileHandler(InFileHandler)
	{}

	static const TCHAR* GetTaskName()
	{
		return TEXT("Cohtml Unreal Resource Loader");
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FCohtmlUnrealResourceLoaderTask, STATGROUP_TaskGraphTasks);
	}
	static ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::GameThread;
	}
	static ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::FireAndForget;
	}
	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& CompletionGraphEvent)
	{
		FileHandler->ProcessUnrealResources_MainThread();
	}
};

void FCohtmlFileHandler::ScheduleUnrealResourceProcessing_AnyThread()
{
	bool bNeedsToScheduleProcessing =
		UnrealResourceQueue.Num() != 0 &&
		(!GraphTaskForUnrealResources.IsValid() || GraphTaskForUnrealResources->IsComplete());

	if (bNeedsToScheduleProcessing)
	{
		GraphTaskForUnrealResources = TGraphTask<FCohtmlUnrealResourceLoaderTask>::CreateTask(nullptr).ConstructAndDispatchWhenReady(this);
	}
}

void FCohtmlFileHandler::ProcessUnrealResources_MainThread()
{
	// If GC is running leave the request for next frame.
	if (IsGarbageCollectionRunning())
	{
		ScheduleUnrealResourceProcessing_AnyThread();
		return;
	}
	TArray<FUnrealResourceTask> UnrealResourceQueueWorkingCopy;
	{
		FScopeLock ScopeLock(&UnrealResourceLock);
		UnrealResourceQueueWorkingCopy = UnrealResourceQueue;
		UnrealResourceQueue.Empty();
	}
	for (auto& Task : UnrealResourceQueueWorkingCopy)
	{
		check(!Task.StreamingHandle.IsValid());
		Task.StreamingHandle = StreamableManager.RequestAsyncLoad(Task.AssetName, FStreamableDelegate(), 0, false);
		if (!Task.StreamingHandle.IsValid())
		{
			COHTML_UE_LOG(Error, TEXT("Unable to load unreal resource: %s"), *Task.AssetName.ToString());
			continue;
		}
		auto OnCompletion = FStreamableDelegate::CreateLambda([this, Task]()
		{
			OnUnrealResourceLoaded(Task);
		});
		if (!Task.StreamingHandle->BindCompleteDelegate(OnCompletion))
		{
			// Binding failed because the resource is already loaded; call the callback manually
			OnUnrealResourceLoaded(Task);
		}
	}
}

void FCohtmlFileHandler::OnUnrealResourceLoaded(const FUnrealResourceTask& ResourceTask)
{
	check(ResourceTask.StreamingHandle->HasLoadCompleted());

	FUnrealResourcePtr Resource(ResourceTask.StreamingHandle->GetLoadedAsset(),
		ResourceTask.ResourceType,
		ResourceTask.ResourceAtlasSizes);
	if (!Resource.IsValid())
	{
		ResourceTask.Response->Finish(cohtml::IAsyncResourceResponse::Failure);
		// No need to log for the resource here; both Cohtml and UE4 will log on Failure anyway.
		return;
	}
	const renoir::PixelFormat ImageFormat = Resource.GetImageFormat();
	const FString AssetNameAsString = ResourceTask.AssetName.ToString();
	if (ImageFormat == renoir::PF_USER_FORMAT)
	{
		COHTML_UE_LOG(Error, TEXT("Failed to load preloaded image: unsupported pixel format for image %s"), *AssetNameAsString);
		ResourceTask.Response->Finish(cohtml::IAsyncResourceResponse::Failure);
		return;
	}

	cohtml::IAsyncResourceResponse::UserImageData ImageData = Resource.GetImageData();
	bool bIsRenderTarget = Resource.IsRenderTarget();
	if (bIsRenderTarget)
	{
		if (!FCohtmlSystemHolder::IsLiveViewRegistered(AssetNameAsString))
		{
			ImageData.ImageHandle = FCohtmlSystemHolder::GetNewLiveViewHandle();
			FCohtmlSystemHolder::RegisterLiveView(AssetNameAsString);
			// Set the LiveViewUrl on the texture so that the backend knows when a live view is destroyed / created
			// We don't need to set it in the else clause since the backend will see only one texture
			static_cast<FCohTextureUserWrapData*>(ImageData.Texture)->LiveViewUrl = AssetNameAsString;
		}
		else
		{
			ImageData.ImageHandle = FCohtmlSystemHolder::GetLiveViewHandle(AssetNameAsString);
		}
	}
	ResourceTask.Response->ReceiveUserImage(ImageData);
	ResourceTask.Response->Finish(cohtml::IAsyncResourceResponse::Success);
	COHTML_UE_LOG(Log, TEXT("Successfully loaded Unreal texture: %s"), *AssetNameAsString);
}

bool FCohtmlFileHandler::TryEnqueueHttpResource(FURLWithFallbacks& InURLWithFallbacks,
	const cohtml::IAsyncResourceRequest* Request, cohtml::IAsyncResourceResponse* Response)
{
	const FString URL = InURLWithFallbacks.BaseURL;
	check(URL.StartsWith(TEXT("http")));

	auto UE4Request = FHttpModule::Get().CreateRequest();
	UE4Request->SetURL(URL);
	auto HeaderCount = Request->GetHeadersCount();
	for (unsigned i = 0; i < HeaderCount; i++)
	{
		FString HeaderName = Request->GetHeaderName(i);
		FString HeaderValue = Request->GetHeaderValue(i);
		UE4Request->SetHeader(HeaderName, HeaderValue);
	}
	FString Content = Request->GetBody();
	UE4Request->SetContentAsString(Content);
	FString Verb = Request->GetMethod();
	UE4Request->SetVerb(Verb);

	UE4Request->OnProcessRequestComplete().BindRaw(this, &FCohtmlFileHandler::OnHttpRequestComplete);

	FPendingHttpResource PendingDownload(InURLWithFallbacks, Response, Request);
	{
		FScopeLock ScopeLock(&HttpResourceLock);
		if (PendingHttpResources.Num() >= MaxSimultaneousHttpRequests)
		{
			NotStartedHttpRequestsQueue.Enqueue(TKeyValuePair<FHttpRequestPtr, FPendingHttpResource>(UE4Request, PendingDownload));
			return true;
		}
	}

	if (!UE4Request->ProcessRequest())
	{
		return false;
	}
	{
		FScopeLock ScopeLock(&HttpResourceLock);
		PendingHttpResources.Add(UE4Request, PendingDownload);
	}
	return true;
}

void FCohtmlFileHandler::OnHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	FPendingHttpResource PendingResource;
	{
		FScopeLock ScopeLock(&HttpResourceLock);
		PendingResource = PendingHttpResources.FindAndRemoveChecked(HttpRequest);
		if (!NotStartedHttpRequestsQueue.IsEmpty())
		{
			TKeyValuePair<FHttpRequestPtr, FPendingHttpResource> NotStartedRequest;
			bool bSuccessfullRemoved = NotStartedHttpRequestsQueue.Dequeue(NotStartedRequest);
			check(bSuccessfullRemoved);

			if (!NotStartedRequest.Key->ProcessRequest())
			{
				NotStartedRequest.Value.Response->Finish(cohtml::IAsyncResourceResponse::Failure);
			}
			PendingHttpResources.Add(NotStartedRequest.Key, NotStartedRequest.Value);
		}
	}

	if (!HttpResponse.IsValid())
	{
		// The server didn't respond
		PendingResource.Response->Finish(cohtml::IAsyncResourceResponse::Failure);
		return;
	}

	TArray<FString> Headers = HttpResponse->GetAllHeaders();
	for (const auto& Header : Headers)
	{
		auto HeaderValueDelimiterIndex = Header.Find(": ");
		check(HeaderValueDelimiterIndex != INDEX_NONE);
		FString HeaderName = Header.RightChop(HeaderValueDelimiterIndex);
		FString HeaderValue = Header.LeftChop(HeaderValueDelimiterIndex);
		PendingResource.Response->SetHeader(TCHAR_TO_UTF8(*HeaderName), TCHAR_TO_UTF8(*HeaderValue));
	}
	PendingResource.Response->SetStatus(HttpResponse->GetResponseCode());
	auto& UE4Buffer = HttpResponse->GetContent();
	void* CohtmlBuffer = PendingResource.Response->GetSpace(UE4Buffer.Num());
	FMemory::Memcpy(CohtmlBuffer, UE4Buffer.GetData(), UE4Buffer.Num());
	if (EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		PendingResource.Response->Finish(cohtml::IAsyncResourceResponse::Success);
	}
	else
	{
		if (PendingResource.URLWithFallbacks .PossibleFallbacks.Num() > 0)
		{
			COHTML_UE_LOG(Display, TEXT("Unable to find '%s', falling back to '%s''")
				, *PendingResource.URLWithFallbacks .BaseURL, *PendingResource.URLWithFallbacks .PossibleFallbacks[0]);

			FScopeLock ScopeLock(&HttpResourceLock);
			// The requested URL becomes the first fallback and we remove it from the
			// list of possible fallbacks so that we don't request it again
			PendingResource.URLWithFallbacks .BaseURL = PendingResource.URLWithFallbacks .PossibleFallbacks[0];
			PendingResource.URLWithFallbacks .PossibleFallbacks.RemoveAt(0);

			TryEnqueueHttpResource(PendingResource.URLWithFallbacks , PendingResource.Request, PendingResource.Response);
		}
		else
		{
			PendingResource.Response->Finish(cohtml::IAsyncResourceResponse::Failure);
		}
	}
}
