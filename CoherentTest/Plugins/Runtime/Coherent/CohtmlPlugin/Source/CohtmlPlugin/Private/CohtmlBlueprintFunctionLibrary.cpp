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
#include "CohtmlBlueprintFunctionLibrary.h"

#include "CohtmlBaseComponent.h"
#include "CohtmlJSEvent.h"

UCohtmlBlueprintFunctionLibrary::UCohtmlBlueprintFunctionLibrary(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

UCohtmlJSEvent* UCohtmlBlueprintFunctionLibrary::CreateJSEvent(UObject* WorldContextObject)
{
	return NewObject<UCohtmlJSEvent>();
}

void UCohtmlBlueprintFunctionLibrary::AddByte(UCohtmlJSEvent* JSEvent, uint8 Arg)
{
	JSEvent->AddByte(Arg);
}

void UCohtmlBlueprintFunctionLibrary::AddInt32(UCohtmlJSEvent* JSEvent, int32 Arg)
{
	JSEvent->AddInt32(Arg);
}

void UCohtmlBlueprintFunctionLibrary::AddString(UCohtmlJSEvent* JSEvent, const FString& Arg)
{
	JSEvent->AddString(Arg);
}

void UCohtmlBlueprintFunctionLibrary::AddFloat(UCohtmlJSEvent* JSEvent, float Arg)
{
	JSEvent->AddFloat(Arg);
}

void UCohtmlBlueprintFunctionLibrary::AddBool(UCohtmlJSEvent* JSEvent, bool Arg)
{
	JSEvent->AddBool(Arg);
}

void UCohtmlBlueprintFunctionLibrary::AddObject(UCohtmlJSEvent* JSEvent, UObject* Arg)
{
	JSEvent->AddObject(Arg);
}

void UCohtmlBlueprintFunctionLibrary::AddStructArg(UCohtmlJSEvent* JSEvent, const UStructProperty* Arg)
{
	// This is only a stub.
	// It should never be called, there's a custom thunk implementation in the header
	check(0);
}

void UCohtmlBlueprintFunctionLibrary::AddArrayOfStructs(UCohtmlJSEvent* JSEvent, const TArray<int32>& Arg)
{
	// This is only a stub.
	// It should never be called, there's a custom thunk implementation in the header
	check(0);
}

void UCohtmlBlueprintFunctionLibrary::AddArray(UCohtmlJSEvent* JSEvent, const TArray<int32>& Arg, int32 ArrayType)
{
	auto Ptr = (void*)&Arg;
	JSEvent->AddArrayInternal(Ptr, static_cast<UCohtmlJSEvent::EVariableType>(ArrayType));
}

void UCohtmlBlueprintFunctionLibrary::TriggerJSEvent(UCohtmlBaseComponent* Component, const FString& EventName, UCohtmlJSEvent* JSEvent)
{
	if (!Component)
	{
		COHTML_UE_LOG(Error, TEXT("Trigger JS Event called on null " COHTML_PRODUCT " component!"));
		return;
	}
	Component->TriggerJSEvent(EventName, JSEvent);
}
