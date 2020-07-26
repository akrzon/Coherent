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

namespace cohtml
{
class Binder;

template <typename T>
void CoherentTArrayElementReader(Binder* binder, void* data, size_t position)
{
	auto castedData = (T*)data;
	CoherentReadInternal(binder, castedData[position]);
}


template <typename TArrayType>
void* CoherentTArrayNativeElementReader(void* data, size_t position)
{
	return &(*(TArrayType*)data)[position];
}

template <typename TArrayType>
size_t CoherentTArrayLength(void* data)
{
	return ((TArrayType*)data)->Num();
}

template <typename TArrayType, typename T>
typename EnableIf<!cohtml::PointerTrait<T>::Value, void>::Type CoherentTArrayElementReader(Binder* binder, void* data, size_t position)
{
	CoherentReadInternal(binder, (*(TArrayType*)data)[position]);
}

template <typename TArrayType, typename T>
typename EnableIf<cohtml::PointerTrait<T>::Value, void>::Type CoherentTArrayElementReader(Binder* binder, void* data, size_t position)
{
	typedef typename UnwrapPointerType<T, PointerTrait<T>::Value>::Type UnwrappedType;
	if (auto unwrappedObjectPtr = (UnwrappedType*)UnwrapPointer<T>::Unwrap(&(*(TArrayType*)data)[position]))
	{
		CoherentReadInternal(binder, *unwrappedObjectPtr);
	}
}

template <typename TArrayType, typename T>
typename EnableIf<!cohtml::PointerTrait<T>::Value, void*>::Type CoherentTArrayNativeElementReader(void* data, size_t position)
{
	return &(*(TArrayType*)data)[position];
}

template <typename TArrayType, typename T>
typename EnableIf<cohtml::PointerTrait<T>::Value, void*>::Type CoherentTArrayNativeElementReader(void* data, size_t position)
{
	return UnwrapPointer<T>::Unwrap(&(*(TArrayType*)data)[position]);
}

typedef void(*Reader)(Binder*, void*, size_t);
typedef void*(*NativeReader)(void*, size_t);
typedef size_t(*VectorLengthFunc)(void*);

template <typename T>
class TArrayReaderFactory
{
public:
	static Reader ElementReader()
	{
		return cohtml::CoherentTArrayElementReader<T>;
	}
	static NativeReader NativeElementReader()
	{
		return cohtml::CoherentTArrayNativeElementReader<T>;
	}

	static VectorLengthFunc VectorLength()
	{
		return CoherentTArrayLength<T>;
	}
};

template <typename T, typename A>
class TArrayReaderFactory<TArray<T, A>>
{
public:
	typedef TArray<T, A> TArrayType;

	static Reader ElementReader()
	{
		return cohtml::CoherentTArrayElementReader<TArrayType, T>;
	}

	static NativeReader NativeElementReader()
	{
		return cohtml::CoherentTArrayNativeElementReader<TArrayType, T>;
	}

	static VectorLengthFunc VectorLength()
	{
		return CoherentTArrayLength<TArrayType>;
	}
};

template <typename T>
void CoherentTArrayElementBinder(Binder* binder, void* arr, size_t index)
{
	auto castedArray = (T*)arr;
	if (arr)
	{
		CoherentBindInternal(binder, castedArray[index]);
	}
	else
	{
		binder->BindNull();
	}
}

template <typename T, typename A>
void CoherentBindInternal(Binder* binder, TArray<T, A>& value)
{
	if (!binder->TryBindArrayByRef(value.GetData(),
		value.Num(),
		CoherentTArrayElementBinder<T>,
		TArrayReaderFactory<TArray<T, A>>::ElementReader()))
	{
		binder->ArrayBegin(value.Num());
		typedef typename TArray<T, A>::TConstIterator Iterator;

		for (Iterator i = value.CreateConstIterator(); i; ++i)
		{
			CoherentBindInternal(binder, *i);
		}

		binder->ArrayEnd();
	}
}

template <typename T, typename A>
void CoherentBindInternal(Binder* binder, const TArray<T, A>& value)
{
	if (!binder->TryBindArrayByRef(const_cast<T*> (value.GetData()),
		value.Num(),
		CoherentTArrayElementBinder<T>,
		TArrayReaderFactory<TArray<T, A>>::ElementReader()))
	{
		binder->ArrayBegin(value.Num());
		typedef typename TArray<T, A>::TConstIterator Iterator;

		for (Iterator i = value.CreateConstIterator(); i; ++i)
		{
			CoherentBindInternal(binder, *i);
		}

		binder->ArrayEnd();
	}
}

template <typename A>
void CoherentBindInternal(Binder* binder, TArray<float, A>& value)
{
	if (!binder->TryBindArrayByRef(value.GetData(),
		value.Num(),
		CoherentTArrayElementBinder<float>,
		TArrayReaderFactory<float>::ElementReader()))
	{
		binder->BindArray(&value[0], value.Num());
	}
}
template <typename A>
void CoherentBindInternal(Binder* binder, const TArray<float, A>& value)
{
	if (!binder->TryBindArrayByRef(const_cast<float*> (value.GetData()),
		value.Num(),
		CoherentTArrayElementBinder<float>,
		TArrayReaderFactory<float>::ElementReader()))
	{
		binder->BindArray(&value[0], value.Num());
	}
}
template <typename A>
void CoherentBindInternal(Binder* binder, TArray<int32, A>& value)
{
	if (!binder->TryBindArrayByRef(value.GetData(),
		value.Num(),
		CoherentTArrayElementBinder<int32>,
		TArrayReaderFactory<int32>::ElementReader()))
	{
		binder->BindArray(&value[0], value.Num());
	}
}
template <typename A>
void CoherentBindInternal(Binder* binder, const TArray<int32, A>& value)
{
	if (!binder->TryBindArrayByRef(const_cast<int32*> (value.GetData()),
		value.Num(),
		CoherentTArrayElementBinder<int32>,
		TArrayReaderFactory<int32>::ElementReader()))
	{
		binder->BindArray(&value[0], value.Num());
	}
}

template <typename T, typename A>
void CoherentReadInternal(Binder* binder, TArray<T, A>& value)
{
	size_t size = binder->ReadArrayBegin();

	value.SetNum(size);

	for (size_t index = 0; index != size; ++index)
	{
		binder->ReadArrayElement(index);
		CoherentReadInternal(binder, value[index]);
	}

	binder->ReadArrayEnd();
}

template<typename T, typename A>
struct TypeToElementType<TArray<T, A>>
{
	static constexpr ElementType value = ElementType::ET_Array;
};

template<typename T, typename A>
struct TypeToElementType<TArray<T, A>&>
{
	static constexpr ElementType value = ElementType::ET_Array;
};

template<typename T, typename A>
struct GetArrayValue<const TArray<T, A>&>
{
	static bool Invoke(Binder* binder, void* object, ArrayInfo* arrayInfo, const TypedProperty<const TArray<T, A>&>* prop)
	{
		*arrayInfo = ArrayInfo{
			TypeToElementType<T>::value,
			TArrayReaderFactory<TArray<T, A>>::VectorLength(),
			TArrayReaderFactory<TArray<T, A>>::NativeElementReader(),
			CoherentTypeInfo<T>::Get(binder),
			const_cast<TArray<T, A>*>(&prop->GetValue(object))
		};
		return true;
	}
	static bool Invoke(Binder* binder, void* object, ArrayInfo* arrayInfo, const TypedProperty<TArray<T, A>&>* prop)
	{
		*arrayInfo = ArrayInfo{
			TypeToElementType<T>::value,
			TArrayReaderFactory<TArray<T, A>>::VectorLength(),
			TArrayReaderFactory<TArray<T, A>>::NativeElementReader(),
			CoherentTypeInfo<T>::Get(binder),
			const_cast<TArray<T, A>*>(&prop->GetValue(object))
		};
		return true;
	}
};

template <typename T, typename A>
struct GetArrayValue<TArray<T, A>&>
{
	static bool Invoke(Binder* binder, void* object, ArrayInfo* arrayInfo, const TypedProperty<TArray<T, A>&>* prop)
	{
		*arrayInfo = ArrayInfo{
			TypeToElementType<T>::value,
			TArrayReaderFactory<TArray<T, A>>::VectorLength(),
			TArrayReaderFactory<TArray<T, A>>::NativeElementReader(),
			CoherentTypeInfo<T>::Get(binder),
			const_cast<TArray<T, A>*>(&prop->GetValue(object))
		};
		return true;
	}
};



}
