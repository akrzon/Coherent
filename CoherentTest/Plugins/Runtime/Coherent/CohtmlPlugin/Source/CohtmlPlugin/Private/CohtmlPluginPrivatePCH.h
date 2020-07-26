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

#include "CohtmlBackwardsCompatibility.h"
#if defined(COHTML_UE4_414_SUPPORT)
#include <CoreUObject.h>
#include <Engine.h>
#else
#include <CoreMinimal.h>
#include <UObject/ObjectMacros.h>
#include <Engine/Engine.h>
#endif

DECLARE_STATS_GROUP(TEXT(COHTML_PRODUCT), COHTML_STAT_GROUP_ID_DEFAULT, STATCAT_Advanced);
DECLARE_STATS_GROUP(TEXT(COHTML_PRODUCT " Counters"), COHTML_STAT_GROUP_ID(Counters), STATCAT_Advanced);
DECLARE_STATS_GROUP(TEXT(COHTML_PRODUCT " CPU Memory"), COHTML_STAT_GROUP_ID(CPUMemory), STATCAT_Advanced);
DECLARE_STATS_GROUP(TEXT(COHTML_PRODUCT " GPU Memory"), COHTML_STAT_GROUP_ID(GPUMemory), STATCAT_Advanced);
// This counter tracks all major CPU calls to the native library, please update the list below should you add a new function
// * View::Advance
// * System::Advance
// * View::Paint
DECLARE_CYCLE_STAT_EXTERN(TEXT("Total CPU"), STAT_CohtmlTotalCPU, COHTML_STAT_GROUP_ID_DEFAULT, /* API_MACRO */);
DECLARE_CYCLE_STAT_EXTERN(TEXT("View Advance"), STAT_CohtmlViewAdvance, COHTML_STAT_GROUP_ID_DEFAULT, /* API_MACRO */);
DECLARE_CYCLE_STAT_EXTERN(TEXT("Paint"), STAT_CohtmlPaint, COHTML_STAT_GROUP_ID_DEFAULT, /* API_MACRO */);

DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Memory"), STAT_CohtmlCPUMemoryTotal, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Unknown Memory"), STAT_CohtmlCPUMemoryUnknown, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Untagged Memory"), STAT_CohtmlCPUMemoryUntagged, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU System Memory"), STAT_CohtmlCPUMemorySystem, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Logging Memory"), STAT_CohtmlCPUMemoryLogging, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Loader Memory"), STAT_CohtmlCPUMemoryLoader, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU DOM Memory"), STAT_CohtmlCPUMemoryDOM, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU CSSStatic Memory"), STAT_CohtmlCPUMemoryDOMStatic, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Layout Memory"), STAT_CohtmlCPUMemoryLayout, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU CSS Memory"), STAT_CohtmlCPUMemoryCSS, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU CSSStatic Memory"), STAT_CohtmlCPUMemoryCSSStatic, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU TaskSystemMemory Memory"), STAT_CohtmlCPUMemoryTaskSystemMemory, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Display Memory"), STAT_CohtmlCPUMemoryDisplay, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Profiling Memory"), STAT_CohtmlCPUMemoryProfiling, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU HTMLParser Memory"), STAT_CohtmlCPUMemoryHTMLParser, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU TempAllocator Memory"), STAT_CohtmlCPUMemoryTempAllocator, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU PoolAllocator Memory"), STAT_CohtmlCPUMemoryPoolAllocator, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Dump Memory"), STAT_CohtmlCPUMemoryDump, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Script Memory"), STAT_CohtmlCPUMemoryScript, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU XML Memory"), STAT_CohtmlCPUMemoryXML, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Server Memory"), STAT_CohtmlCPUMemoryServer, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Inspector Memory"), STAT_CohtmlCPUMemoryInspector, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU SVG Memory"), STAT_CohtmlCPUMemorySVG, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU UriParser Memory"), STAT_CohtmlCPUMemoryUriParser, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("CPU Media Memory"), STAT_CohtmlCPUMemoryMedia, COHTML_STAT_GROUP_ID(CPUMemory), /* API_MACRO */);

DECLARE_MEMORY_STAT_EXTERN(TEXT("GPU Memory"), STAT_CohtmlGPUTotalMemory, COHTML_STAT_GROUP_ID(GPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("GPU Texture Memory"), STAT_CohtmlGPUTextureMemory, COHTML_STAT_GROUP_ID(GPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("GPU Depth-Stencil Memory"), STAT_CohtmlGPUDepthStencilMemory, COHTML_STAT_GROUP_ID(GPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("GPU Vertex Buffers"), STAT_CohtmlGPUVertexBuffersMemory, COHTML_STAT_GROUP_ID(GPUMemory), /* API_MACRO */);
DECLARE_MEMORY_STAT_EXTERN(TEXT("GPU Index Buffers"), STAT_CohtmlGPUIndexBuffersMemory, COHTML_STAT_GROUP_ID(GPUMemory), /* API_MACRO */);

#define GET_STAT_OBJECT(Stat) StatPtr_##Stat

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.
#include "ICohtmlPlugin.h"
#include "cohtml/Declarations.h"
#include "cohtml/Config.h"

#include "CohtmlUTypeBinder.h"
#include "CohtmlBaseComponent.h"
#include "CohtmlHUD.h"
#include "CohtmlComponent.h"
#include "CohtmlSystemWrapper.h"
