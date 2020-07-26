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

#include "Runtime/Launch/Resources/Version.h"

// COHTML_UE4_410_SUPPORT means that this define is to be used
// for all versions <= 4.10 (i.e. all versions < 4.11)
#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 10)
#define COHTML_UE4_410_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 11)
#define COHTML_UE4_411_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 12)
#define COHTML_UE4_412_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 13)
#define COHTML_UE4_413_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 14)
#define COHTML_UE4_414_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 15)
#define COHTML_UE4_415_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 16)
#define COHTML_UE4_416_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 17)
#define COHTML_UE4_417_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 18)
#define COHTML_UE4_418_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 19)
#define COHTML_UE4_419_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 20)
#define COHTML_UE4_420_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 21)
#define COHTML_UE4_421_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 22)
#define COHTML_UE4_422_SUPPORT
#endif

#if (ENGINE_MAJOR_VERSION == 4) && (ENGINE_MINOR_VERSION <= 23)
#define COHTML_UE4_423_SUPPORT
#endif

#if defined(COHTML_UE4_414_SUPPORT)
#include "Core.h"
#endif
#include <Containers/UnrealString.h>
#include <Misc/Paths.h>
#include <Logging/LogMacros.h>

FORCEINLINE FString CohtmlGetProjectContentDir()
{
#if defined(COHTML_UE4_417_SUPPORT)
	return FPaths::GameContentDir();
#else
	return FPaths::ProjectContentDir();
#endif
}

FORCEINLINE FString CohtmlGetProjectPluginDir()
{
#if defined(COHTML_UE4_417_SUPPORT)
	return FPaths::GamePluginsDir();
#else
	return FPaths::ProjectPluginsDir();
#endif
}

#ifndef COHTML_IS_GAMEFACE
#define COHTML_IS_GAMEFACE 0
#endif

#if COHTML_IS_GAMEFACE
#define COHTML_PRODUCT "Gameface"
DECLARE_LOG_CATEGORY_EXTERN(LogGameface, Log, All);
#define COHTML_UE_LOG(Severity, Message, ...) UE_LOG(LogGameface, Severity, Message, ##__VA_ARGS__)
#define COHTML_STAT_GROUP_ID_DEFAULT STATGROUP_Gameface
#define COHTML_STAT_GROUP_ID(StatGroup) STATGROUP_Gameface##StatGroup
#else
#define COHTML_PRODUCT "Prysm"
DECLARE_LOG_CATEGORY_EXTERN(LogPrysm, Log, All);
#define COHTML_UE_LOG(Severity, Message, ...) UE_LOG(LogPrysm, Severity, Message, ##__VA_ARGS__)
#define COHTML_STAT_GROUP_ID_DEFAULT STATGROUP_Prysm
#define COHTML_STAT_GROUP_ID(StatGroup) STATGROUP_Prysm##StatGroup
#endif

#if !defined(COHTML_UE4_421_SUPPORT)
#define ENQUEUE_COHTML_RENDERING_COMMAND(Name, Code)\
	ENQUEUE_RENDER_COMMAND(Name)([](FRHICommandListImmediate& RHICmdList) Code);

#define ENQUEUE_COHTML_RENDERING_COMMAND_ONEPARAMETER(Name, ParamType1, ParamName1, ParamValue1, Code)\
	{\
		ParamType1 ParamName1 = ParamValue1;\
		ENQUEUE_RENDER_COMMAND(Name)([=](FRHICommandListImmediate& RHICmdList) Code);\
	}

#define ENQUEUE_COHTML_RENDERING_COMMAND_TWOPARAMETER(Name, ParamType1, ParamName1, ParamValue1, ParamType2, ParamName2, ParamValue2, Code)\
	{\
		ParamType1 ParamName1 = ParamValue1;\
		ParamType2 ParamName2 = ParamValue2;\
		ENQUEUE_RENDER_COMMAND(Name)([=](FRHICommandListImmediate& RHICmdList) Code);\
	}

#define ENQUEUE_COHTML_RENDERING_COMMAND_THREEPARAMETER(Name, ParamType1, ParamName1, ParamValue1, ParamType2, ParamName2, ParamValue2, ParamType3, ParamName3, ParamValue3, Code)\
	{\
		ParamType1 ParamName1 = ParamValue1;\
		ParamType2 ParamName2 = ParamValue2;\
		ParamType3 ParamName3 = ParamValue3;\
		ENQUEUE_RENDER_COMMAND(Name)([=](FRHICommandListImmediate& RHICmdList) Code);\
	}

#define ENQUEUE_COHTML_RENDERING_COMMAND_FOURPARAMETER(Name, ParamType1, ParamName1, ParamValue1, ParamType2, ParamName2, ParamValue2, ParamType3, ParamName3, ParamValue3, ParamType4, ParamName4, ParamValue4, Code)\
	{\
		ParamType1 ParamName1 = ParamValue1;\
		ParamType2 ParamName2 = ParamValue2;\
		ParamType3 ParamName3 = ParamValue3;\
		ParamType4 ParamName4 = ParamValue4;\
		ENQUEUE_RENDER_COMMAND(Name)([=](FRHICommandListImmediate& RHICmdList) Code);\
	}

#else
#define ENQUEUE_COHTML_RENDERING_COMMAND(Name, Code)\
	ENQUEUE_UNIQUE_RENDER_COMMAND(Name, Code);

#define ENQUEUE_COHTML_RENDERING_COMMAND_ONEPARAMETER(Name, ParamType1, ParamName1, ParamValue1, Code)\
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(Name, ParamType1, ParamName1, ParamValue1, Code);

#define ENQUEUE_COHTML_RENDERING_COMMAND_TWOPARAMETER(Name, ParamType1, ParamName1, ParamValue1, ParamType2, ParamName2, ParamValue2, Code)\
	ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(Name, ParamType1, ParamName1, ParamValue1, ParamType2, ParamName2, ParamValue2, Code);

#define ENQUEUE_COHTML_RENDERING_COMMAND_THREEPARAMETER(Name, ParamType1, ParamName1, ParamValue1, ParamType2, ParamName2, ParamValue2, ParamType3, ParamName3, ParamValue3, Code)\
	ENQUEUE_UNIQUE_RENDER_COMMAND_THREEPARAMETER(Name, ParamType1, ParamName1, ParamValue1, ParamType2, ParamName2, ParamValue2, ParamType3, ParamName3, ParamValue3, Code);

#define ENQUEUE_COHTML_RENDERING_COMMAND_FOURPARAMETER(Name, ParamType1, ParamName1, ParamValue1, ParamType2, ParamName2, ParamValue2, ParamType3, ParamName3, ParamValue3, ParamType4, ParamName4, ParamValue4, Code)\
	ENQUEUE_UNIQUE_RENDER_COMMAND_FOURPARAMETER(Name, ParamType1, ParamName1, ParamValue1, ParamType2, ParamName2, ParamValue2, ParamType3, ParamName3, ParamValue3, ParamType4, ParamName4, ParamValue4, Code);
#endif
