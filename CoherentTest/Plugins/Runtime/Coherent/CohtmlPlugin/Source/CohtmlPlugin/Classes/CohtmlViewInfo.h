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

#include "CohtmlViewInfo.generated.h"

USTRUCT(Blueprintable)
struct  FCohtmlViewSettings
{
	GENERATED_USTRUCT_BODY()

	FCohtmlViewSettings()
		: Width(0)
		, Height(0)
		, IsTransparent(true)
		, AnimationFrameDefer(0.016f)
	{}

	/** The Width of a View in pixels */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prysm")
	int32 Width;

	/** The Height of a View in pixels */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prysm")
	int32 Height;

	/**
	* Defines if a view is transparent or not. A transparent view can be have transparent parts that will
	* be correctly blended with the client's surfaces. Non-transparent views are always implicitly composited
	* as if on a white background. Don't use transparent views unless you have transparent parts in the page
	* because non-transparent view are slightly faster.
	* @note Do not blend non-transparent views.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prysm")
	bool IsTransparent;

	/// Sets the minimal frame time between invocations of requested animation
	/// frames in seconds. Decreasing the number will trigger animations more 
	/// often but will consume more CPU. A good figure is around half the 
	/// frame-rate of the application.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prysm")
	float AnimationFrameDefer;

};