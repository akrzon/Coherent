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

#include <cohtml/Binding/Binder.h>

namespace cohtml
{
	inline void CoherentBindInternal(Binder* binder, FVector2D& value)
	{
		binder->MapBegin(2);

		CoherentBindInternal(binder, "X");
		CoherentBindInternal(binder, value.X);
		CoherentBindInternal(binder, "Y");
		CoherentBindInternal(binder, value.Y);

		binder->MapEnd();
	}

	inline void CoherentBindInternal(Binder* binder, const FVector2D& value)
	{
		binder->MapBegin(2);

		CoherentBindInternal(binder, "X");
		CoherentBindInternal(binder, value.X);
		CoherentBindInternal(binder, "Y");
		CoherentBindInternal(binder, value.Y);

		binder->MapEnd();
	}

	inline void CoherentReadInternal(Binder* binder, FVector2D& value)
	{
		size_t size = binder->ReadMapBegin();

		if (binder->ReadProperty("X"))
		{
			CoherentReadInternal(binder, value.X);
		}

		if (binder->ReadProperty("Y"))
		{
			CoherentReadInternal(binder, value.Y);
		}

		binder->ReadMapEnd();
	}

	inline void CoherentBindInternal(Binder* binder, FVector& value)
	{
		binder->MapBegin(3);

		CoherentBindInternal(binder, "X");
		CoherentBindInternal(binder, value.X);
		CoherentBindInternal(binder, "Y");
		CoherentBindInternal(binder, value.Y);
		CoherentBindInternal(binder, "Z");
		CoherentBindInternal(binder, value.Z);

		binder->MapEnd();
	}

	inline void CoherentBindInternal(Binder* binder, const FVector& value)
	{
		binder->MapBegin(3);

		CoherentBindInternal(binder, "X");
		CoherentBindInternal(binder, value.X);
		CoherentBindInternal(binder, "Y");
		CoherentBindInternal(binder, value.Y);
		CoherentBindInternal(binder, "Z");
		CoherentBindInternal(binder, value.Z);

		binder->MapEnd();
	}

	inline void CoherentReadInternal(Binder* binder, FVector& value)
	{
		size_t size = binder->ReadMapBegin();

		if (binder->ReadProperty("X"))
		{
			CoherentReadInternal(binder, value.X);
		}

		if (binder->ReadProperty("Y"))
		{
			CoherentReadInternal(binder, value.Y);
		}

		if (binder->ReadProperty("Z"))
		{
			CoherentReadInternal(binder, value.Z);
		}

		binder->ReadMapEnd();
	}

	inline void CoherentBindInternal(Binder* binder, FVector4& value)
	{
		binder->MapBegin(4);

		CoherentBindInternal(binder, "X");
		CoherentBindInternal(binder, value.X);
		CoherentBindInternal(binder, "Y");
		CoherentBindInternal(binder, value.Y);
		CoherentBindInternal(binder, "Z");
		CoherentBindInternal(binder, value.Z);
		CoherentBindInternal(binder, "W");
		CoherentBindInternal(binder, value.W);

		binder->MapEnd();
	}

	inline void CoherentBindInternal(Binder* binder, const FVector4& value)
	{
		binder->MapBegin(4);

		CoherentBindInternal(binder, "X");
		CoherentBindInternal(binder, value.X);
		CoherentBindInternal(binder, "Y");
		CoherentBindInternal(binder, value.Y);
		CoherentBindInternal(binder, "Z");
		CoherentBindInternal(binder, value.Z);
		CoherentBindInternal(binder, "W");
		CoherentBindInternal(binder, value.W);

		binder->MapEnd();
	}

	inline void CoherentReadInternal(Binder* binder, FVector4& value)
	{
		size_t size = binder->ReadMapBegin();

		if (binder->ReadProperty("X"))
		{
			CoherentReadInternal(binder, value.X);
		}

		if (binder->ReadProperty("Y"))
		{
			CoherentReadInternal(binder, value.Y);
		}

		if (binder->ReadProperty("Z"))
		{
			CoherentReadInternal(binder, value.Z);
		}

		if (binder->ReadProperty("W"))
		{
			CoherentReadInternal(binder, value.W);
		}

		binder->ReadMapEnd();
	}
}