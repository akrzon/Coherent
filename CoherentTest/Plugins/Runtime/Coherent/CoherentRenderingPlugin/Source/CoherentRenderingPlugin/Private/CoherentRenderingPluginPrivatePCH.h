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
#pragma once

#include "CoherentRenderingBackwardsCompatibility.h"
#if defined(COHERENT_RENDERING_UE4_414_SUPPORT)
#include <CoreUObject.h>
#include <Engine.h>
#else
#include <CoreMinimal.h>
#include <UObject/ObjectMacros.h>
#include <Engine/Engine.h>
#endif

DECLARE_STATS_GROUP(TEXT("Coherent Rendering Counters"), STATGROUP_CoherentRenderingCounters, STATCAT_Advanced);

DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Total Memory"), STAT_CoherentRenderingCPUMemory, STATGROUP_CoherentRenderingCounters, /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("GPU Total Memory"), STAT_CoherentRenderingGPUTotalMemory, STATGROUP_CoherentRenderingCounters, /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("GPU Texture Memory"), STAT_CoherentRenderingGPUTextureMemory, STATGROUP_CoherentRenderingCounters, /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("GPU Depth-Stencil Memory"), STAT_CoherentRenderingGPUDepthStencilMemory, STATGROUP_CoherentRenderingCounters, /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("GPU Vertex Buffers"), STAT_CoherentRenderingGPUVertexBuffersMemory, STATGROUP_CoherentRenderingCounters, /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("GPU Index Buffers"), STAT_CoherentRenderingGPUIndexBuffersMemory, STATGROUP_CoherentRenderingCounters, /* API_MACRO */);

#define GET_STAT_OBJECT(Stat) StatPtr_##Stat

DECLARE_LOG_CATEGORY_EXTERN(LogCoherentRendering, Log, All)

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.
#include "ICoherentRenderingPlugin.h"
#include "RenoirCore/Config.h"