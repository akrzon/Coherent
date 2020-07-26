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

#include <cohtml/Binding/Binding.h>

#include "CohtmlBackwardsCompatibility.h"

namespace cohtml
{
// This function converts char* UTF-8 string to UTF-16 encoding and stores it in an FString
inline void AnsiToTCharConverter(const char* Buffer, size_t Size, FString& Text)
{
	auto ConvertedLen = FUTF8ToTCHAR_Convert::ConvertedLength(Buffer, Size);
	auto& CharArray = Text.GetCharArray();
	CharArray.SetNumZeroed(ConvertedLen + 1, true);
	CharArray[ConvertedLen] = 0;
	FUTF8ToTCHAR_Convert::Convert(CharArray.GetData(), ConvertedLen, Buffer, Size);
}

inline void CoherentBindInternal(Binder* binder, FString& value)
{
	binder->Bind(*value);
}

inline void CoherentBindInternal(Binder* binder, const FString& value)
{
	binder->Bind(*value);
}

inline void CoherentReadInternal(Binder* binder, FString& value)
{
	size_t size = 0;
	const char* buffer = nullptr;
	binder->Read(buffer, size);
	AnsiToTCharConverter(buffer, size, value);
}

inline void CoherentBindInternal(Binder* binder, FText& value)
{
	CoherentBindInternal(binder, value.ToString());
}

inline void CoherentBindInternal(Binder* binder, const FText& value)
{
	CoherentBindInternal(binder, value.ToString());
}

inline void CoherentReadInternal(Binder* binder, FText& value)
{
	FString strValue;
	CoherentReadInternal(binder, strValue);
	value = FText::FromString(strValue);
}

inline void CoherentBindInternal(Binder* binder, FName& value)
{
	CoherentBindInternal(binder, value.ToString());
}

inline void CoherentBindInternal(Binder* binder, const FName& value)
{
	CoherentBindInternal(binder, value.ToString());
}

inline void CoherentReadInternal(Binder* binder, FName& value)
{
	FString strValue;
	CoherentReadInternal(binder, strValue);
	value = FName(*strValue);
}

template <>
struct CoherentToString<FString>
{
	static bool Invoke(const FString& value, char* buffer, size_t* length)
	{
		FTCHARToUTF8 UTF8Converted(*value);
		const size_t UTF8Length = UTF8Converted.Length();
		// if there is a buffer and it's size is no less than UTF8 data size
		// then we can write data inside the buffer
		// but if length is less we should only set the new length so this
		// converter function can be called again after the buffer is properly resized
		if (buffer && *length >= UTF8Length)
		{
			FMemory::Memcpy(buffer, UTF8Converted.Get(), UTF8Length);
		}
		*length = UTF8Length;
		return true;
	}
};

template <>
struct CoherentToString<FText>
{
	static bool Invoke(const FText& value, char* buffer, size_t* length)
	{
		return CoherentToString<FString>::Invoke(value.ToString(), buffer, length);
	}
};

template <>
struct CoherentToString<FName>
{
	static bool Invoke(const FName& value, char* buffer, size_t* length)
	{
		return CoherentToString<FString>::Invoke(value.ToString(), buffer, length);
	}
};

template<>
struct TypeToElementType<FString>
{
	static const ElementType value = ElementType::ET_String;
};

template<>
struct TypeToElementType<FString&>
{
	static const ElementType value = ElementType::ET_String;
};

template<>
struct TypeToElementType<FText>
{
	static const ElementType value = ElementType::ET_String;
};

template<>
struct TypeToElementType<FText&>
{
	static const ElementType value = ElementType::ET_String;
};

template<>
struct TypeToElementType<FName>
{
	static const ElementType value = ElementType::ET_String;
};

template<>
struct TypeToElementType<FName&>
{
	static const ElementType value = ElementType::ET_String;
};

}
