/*
This file is part of Renoir, a modern graphics library.
Release $RELEASE$. Build $VERSION$ for $LICENSEE$.

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
#include "CoherentRenderingPluginPrivatePCH.h"
#include "CoherentRenderingFileManipulator.h"

#include "HAL/PlatformFilemanager.h"
#include "HAL/PlatformFile.h"
#if !defined(COHERENT_RENDERING_UE4_413_SUPPORT)
#include "Misc/ScopeLock.h"
#endif
#include "Misc/Paths.h"

namespace {
	class FontDirectoryVisitor : public IPlatformFile::FDirectoryVisitor
	{
	public:

		FontDirectoryVisitor(TArray<FString>& Files) : CurrentDirectoryFiles(Files)
		{
		}

		bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
		{
			if (!bIsDirectory)
			{
				const FString Path = FilenameOrDirectory;
				if (Path.EndsWith(TEXT(".ttf")) || Path.EndsWith(TEXT(".otf")) || Path.EndsWith(TEXT(".ttc")))
				{
					CurrentDirectoryFiles.Add(FPaths::GetCleanFilename(Path));
				}
			}
			return true;
		}
	private:
		TArray<FString>& CurrentDirectoryFiles;
	};
}

FRenderingStreamReader::FRenderingStreamReader(const TCHAR* Path)
	: FilePath(Path)
	, FileSize(0)
{
	GetOrCreateFileHandle();
}

IFileHandle* FRenderingStreamReader::GetOrCreateFileHandle()
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
			if(Handle)
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

unsigned FRenderingStreamReader::GetSize()
{
	return FileSize;
}

unsigned FRenderingStreamReader::Read(unsigned Offset, unsigned char* Buffer, unsigned Count)
{
	auto Handle = GetOrCreateFileHandle();
	if (Handle && Buffer && Handle->Seek(Offset) && Handle->Read(Buffer, Count))
	{
		return FMath::Min(Count, static_cast<unsigned>(Handle->Size() - Offset));
	}
	return 0;
}

void FRenderingStreamReader::Close()
{
	ThreadFileHandleMap.Empty();
}

FRenderingFileManipulator::FRenderingFileManipulator()
	: CurrentFileIndex(0)
{
}

bool FRenderingFileManipulator::EnumerateFolder(const char* Path)
{
	CurrentDirectoryFiles.Empty();
	CurrentFileIndex = 0;
	FontDirectoryVisitor DirectoryVisitor(CurrentDirectoryFiles);
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.IterateDirectory(UTF8_TO_TCHAR(Path), DirectoryVisitor);
}

const char* FRenderingFileManipulator::NextFile()
{
	if (CurrentFileIndex < static_cast<unsigned>(CurrentDirectoryFiles.Num()))
	{
		FTCHARToUTF8 Converter(*CurrentDirectoryFiles[CurrentFileIndex++]);
		LastFileName.SetNumUninitialized(Converter.Length() + 1);
		FMemory::Memcpy(LastFileName.GetData(), Converter.Get(), Converter.Length());
		LastFileName[LastFileName.Num() - 1] = 0;
		return LastFileName.GetData();
	}
	return nullptr;
}

renoir::IStreamReader* FRenderingFileManipulator::OpenFile(const char* Path)
{
	TUniquePtr<FRenderingStreamReader> Reader(new FRenderingStreamReader(UTF8_TO_TCHAR(Path)));
	return Reader->IsValid() ? Reader.Release() : nullptr;
}
