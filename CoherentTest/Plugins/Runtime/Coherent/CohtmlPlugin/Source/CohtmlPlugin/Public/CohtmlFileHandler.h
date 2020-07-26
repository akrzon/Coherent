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
#pragma once

#include <Engine/StreamableManager.h>

#include "CohtmlAtlasMappingData.h"
#include "CohtmlDirectoryWatcher.h"
#include "cohtml/ResourceHandler.h"
#include <cohtml/Library.h>


namespace
{
	FString SanitizeURL(const char* Request)
	{
		unsigned RequestStrlen = (unsigned)strlen(Request);
		// Query the needed buffer size
		unsigned DecodedUrlSize = 0;
		cohtml::Library::DecodeURLString(Request, RequestStrlen, nullptr, &DecodedUrlSize);

		TUniquePtr<char[]> Buffer(new char[DecodedUrlSize]);
		cohtml::Library::DecodeURLString(Request, RequestStrlen, Buffer.Get(), &DecodedUrlSize);

		FUTF8ToTCHAR Converter(Buffer.Get());
		FString URL(Converter.Get(), Converter.Length());

		// If the protocol is http, preserve the full URL
		if (URL.StartsWith(TEXT("http://")) || URL.StartsWith(TEXT("https://")))
		{
			return URL;
		}

		// Otherwise, trim the query component
		int32 QuestionMark;
		if (URL.FindLastChar('?', QuestionMark))
		{
			URL = URL.Left(QuestionMark);
		}
		return URL;
	}
}
// Encapsulates the resource we are currently loading, plus all possible fallbacks for that resource
struct FURLWithFallbacks
{
	FURLWithFallbacks(const char* InBaseURL, const cohtml::IAsyncResourceRequest::FallbackURLsData& InPossibleFallbacks)
	{
		BaseURL = SanitizeURL(InBaseURL);
		for (unsigned i = 0; i < InPossibleFallbacks.Count; i++)
		{
			PossibleFallbacks.Push(SanitizeURL(InPossibleFallbacks.Data[i]));
		}
	}

	FURLWithFallbacks() {}

	FString BaseURL;
	TArray<FString> PossibleFallbacks;
};


struct FOverridableFallbackFormat
{
	FString BaseFormat;
	TArray<FString> FallbackFormats;
};


namespace
{
enum class EUnrealResourceType
{
	PreloadedImage,
	PreloadedImageInAtlas,
	LiveView
};
// This struct holds the necessary info to load a UE4 resource via the StreamingManager
struct FUnrealResourceTask
{
	FUnrealResourceTask(const FStringAssetReference& InAssetName,
		cohtml::IAsyncResourceResponse* InResponse,
		EUnrealResourceType InResourceType,
		const FStringAssetReference& InOriginalAssetName,
		uint32* InAtlasSizes)
		: AssetName(InAssetName)
		, OriginalAssetName(InOriginalAssetName)
		, Response(InResponse)
		, ResourceType(InResourceType)
	{
		FMemory::Memcpy(ResourceAtlasSizes, InAtlasSizes, sizeof(ResourceAtlasSizes));
	}

	const FStringAssetReference AssetName;
	const FStringAssetReference OriginalAssetName;
	cohtml::IAsyncResourceResponse* Response;
	const EUnrealResourceType ResourceType;
	TSharedPtr<FStreamableHandle> StreamingHandle;

	uint32 ResourceAtlasSizes[4];
};
// This struct type-erases any differences between the different UE4 resource types
struct FUnrealResourcePtr
{
	FUnrealResourcePtr(UObject* InResourcePtr, EUnrealResourceType InResourceType, const uint32* SubTextureSize)
		: ResourcePtr(InResourcePtr)
		, ResourceType(InResourceType)
	{
		FMemory::Memcpy(AtlasSizes, SubTextureSize, sizeof(AtlasSizes));
	}
	bool IsValid() const;
	renoir::PixelFormat GetImageFormat() const;
	cohtml::IAsyncResourceResponse::UserImageData GetImageData();
	bool IsRenderTarget() const
	{
		return ResourceType == EUnrealResourceType::LiveView;
	}
private:
	static renoir::PixelFormat GetImageFormat(const UTexture2D* Texture);
	static renoir::PixelFormat GetImageFormat(const UTextureRenderTarget2D* Texture);
	static cohtml::IAsyncResourceResponse::UserImageData GetImageData(UTexture2D* Texture, const uint32* InAtlasSizes);
	static cohtml::IAsyncResourceResponse::UserImageData GetImageData(UTextureRenderTarget2D* Texture);

	UObject* ResourcePtr;
	const EUnrealResourceType ResourceType;
	uint32 AtlasSizes[4];
};

// This struct holds the necessary info to load a UE4 resource via the StreamingManager
struct FPendingHttpResource
{
	FPendingHttpResource()
		: Response(nullptr)
		, Request(nullptr)
	{}

	FPendingHttpResource(const FURLWithFallbacks& InURL, cohtml::IAsyncResourceResponse* InResponse
						, const cohtml::IAsyncResourceRequest* InRequest)
		: URLWithFallbacks(InURL)
		, Response(InResponse)
		, Request(InRequest)
	{}

	FURLWithFallbacks URLWithFallbacks;
	cohtml::IAsyncResourceResponse* Response;
	const cohtml::IAsyncResourceRequest* Request;
};
}


class FCohtmlStreamReader : public cohtml::ISyncStreamReader
{
public:
	FCohtmlStreamReader(const TCHAR* Path);

	virtual unsigned GetSize() override;
	virtual unsigned Read(unsigned Offset, unsigned char* Buffer, unsigned Count) override;
	virtual void Close() override;
	bool IsValid()
	{
		return GetOrCreateFileHandle() != nullptr;
	}

private:
	IFileHandle* GetOrCreateFileHandle();

	FCriticalSection CriticalSection;
	FString FilePath;
	unsigned FileSize;
	TMap<uint32, TUniquePtr<IFileHandle>> ThreadFileHandleMap;
};

class FCohtmlMemoryBufferStreamReader : public cohtml::ISyncStreamReader
{
public:
	FCohtmlMemoryBufferStreamReader(TArray<uint8>&& InData)
		: Data(InData)
	{}
	virtual unsigned GetSize() override
	{
		return Data.Num();
	}
	virtual unsigned Read(unsigned Offset, unsigned char* Buffer, unsigned Count) override
	{
		check(Offset + Count <= static_cast<unsigned>(Data.Num()));
		FMemory::Memcpy(Buffer, Data.GetData() + Offset, Count);
		return Count;
	}
	virtual void Close()
	{
		delete this;
	}
private:
	TArray<uint8> Data;
};

// This class is responsible for loading all files Prysm needs through the UE4 API
// It can handle 3 types of files:
// - standard (raw) files loaded through coui from disk
// - UE4 assets (live views and preloaded textures) through UE4's texture streaming
// - raw files loaded through HTTP
class COHTMLPLUGIN_API FCohtmlFileHandler : public cohtml::IAsyncResourceHandler
{
public:
	FCohtmlFileHandler();
	~FCohtmlFileHandler();

	virtual void OnResourceRequest(const cohtml::IAsyncResourceRequest* request,
		cohtml::IAsyncResourceResponse* response) override;

	virtual void OnResourceStreamRequest(const cohtml::IAsyncResourceRequest* request,
		cohtml::IAsyncResourceStreamResponse* response) override;

	virtual void OnAbortResourceRequest(unsigned id) override;

	void LoadAtlasMetaData();

private:

	enum class EResourceProtocol
	{
		Coui,
		UnrealAsset,
		Http
	};
	bool TryGetResourcePath(const cohtml::IAsyncResourceRequest* Request, EResourceProtocol& ResourceProtocol, FURLWithFallbacks& ResultPath);
	bool IsRangeRequest(int64& Start, int64& End, const cohtml::IAsyncResourceRequest* Request);
	void SetResponseHeadersForCoui(int64 FileSize, int64 ContentSize, int64 Start, bool bIsRangeRequest, cohtml::IAsyncResourceResponse* Response);

	FString GameRoot;
	FString GameContent;
	FString ResolveCouiToGameContent(FString InPath);
	// Raw files from disk
	// Attempts to read the chunk of the file from [Start; End]
	// Returns the number of read bytes (if any)
	bool TryReadFile(const FString& Url, int64 Start, int64 End, bool bIsRangeRequest,
		TArray<uint8>& OutBuffer, int64& OutFileSize);
	void ReadRawResource(const cohtml::IAsyncResourceRequest* Request, cohtml::IAsyncResourceResponse* Response, const FString& ResourcePath);
	void OnUnrealResourceLoaded(const FUnrealResourceTask& ResourceTask);
	// UE4 resources
	bool TryEnqueueUnrealResource(const FString& RelativePath, cohtml::IAsyncResourceResponse* Response);
	void ScheduleUnrealResourceProcessing_AnyThread();
	// Goes through all queued unreal resources and tries to load them immediately
	// If that's not possible, this will schedule itself in the task graph repeatedly until done
	void ProcessUnrealResources_MainThread();

	TArray<FUnrealResourceTask> UnrealResourceQueue;
	FStreamableManager StreamableManager;
	FGraphEventRef GraphTaskForUnrealResources;
	// Used to sync changes to the UnrealResourceQueue since it will be accessed on multiple threads;
	// Note: no two threads will ever access the SAME ResourceTask in the queue
	// but two threads CAN add / remove elements at the same time. Thus, we only need to lock changes to the collection
	// but NOT changes to the elements inside.
	FCriticalSection UnrealResourceLock;
	friend class FCohtmlUnrealResourceLoaderTask;

	FTextureAtlasMetaData AtlasMetaData;

	// Http Resources
	bool TryEnqueueHttpResource(FURLWithFallbacks& URL, const cohtml::IAsyncResourceRequest* Request, cohtml::IAsyncResourceResponse* Response);
	typedef TSharedPtr<class IHttpRequest> FHttpRequestPtr;
	typedef TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;
	void OnHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	TMap<FHttpRequestPtr, FPendingHttpResource> PendingHttpResources;
	// On some platforms UE4's HTTP module can be overloaded by too many requests so
	// we keep them limited and this queue holds all requests we haven't started yet.
	TQueue<TKeyValuePair<FHttpRequestPtr, FPendingHttpResource>> NotStartedHttpRequestsQueue;
	const uint8 MaxSimultaneousHttpRequests;
	// Used for syncing access to the pending list as we push resources there from any background thread
	// but UE4 always calls the completion callback on the main thread
	FCriticalSection HttpResourceLock;

	ICohtmlPlugin::FOnURLRequest FallbackURLsOverride;
	FURLWithFallbacks GeneratePossibleURLs(const cohtml::IAsyncResourceRequest* Request);
};
