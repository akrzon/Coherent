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
#include "CohVertexBuffer.h"

FCohVertexBuffer::FCohVertexBuffer(unsigned VertexCount, bool bIsDynamic, renoir::VertexType VertexDeclaration)
	: IsDynamic(bIsDynamic)
	, LockedPointer(nullptr)
	, VertexDecl(VertexDeclaration)
{
	uint32 Stride;
	switch (VertexDecl)
	{
	case renoir::VT_Standard:
		Stride = sizeof(renoir::StandardVertex);
		break;
	case renoir::VT_Slim:
		Stride = sizeof(renoir::SlimVertex);
		break;
	default:
		check(false && "Unknown vertex type!");
		return;
	}
	Size = Stride * VertexCount;
	InitResource();
}

FCohVertexBuffer::~FCohVertexBuffer()
{
	ReleaseResource();
}

void FCohVertexBuffer::InitRHI()
{
	FRHIResourceCreateInfo Info;
	VertexBufferRHI = RHICreateVertexBuffer(Size,
#if PLATFORM_PS4 || PLATFORM_DPX
		IsDynamic ? BUF_Volatile : BUF_Static,
#else
		IsDynamic ? BUF_Dynamic : BUF_Static,
#endif
		Info);
	verify(VertexBufferRHI);
}

void* FCohVertexBuffer::Lock()
{
	check(!IsLocked());
	LockedPointer = RHILockVertexBuffer(VertexBufferRHI, 0, Size, RLM_WriteOnly);
	return LockedPointer;
}

void* FCohVertexBuffer::LockPtr()
{
	return LockedPointer;
}

void FCohVertexBuffer::Unlock()
{
	check(IsLocked());
	RHIUnlockVertexBuffer(VertexBufferRHI);
	LockedPointer = nullptr;
}

bool FCohVertexBuffer::IsLocked() const
{
	return LockedPointer != nullptr;
}

bool FCohVertexBuffer::UpdateData(const void* Data, size_t DataLen)
{
	check(DataLen <= Size);
	bool wasLocked = IsLocked();
	if (!wasLocked)
	{
		Lock();
	}

	FMemory::Memcpy(LockPtr(), Data, DataLen);

	if (!wasLocked)
	{
		Unlock();
	}

	return true;
}

size_t FCohVertexBuffer::GetMemorySize()
{
	return Size;
}
