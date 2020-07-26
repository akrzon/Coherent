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

#include <cohtml/Config.h>
#include <cohtml/Binding/Binding.h>
#include <Templates/UnrealTemplate.h>

namespace cohtml
{
	template<typename T>
	using TRemoveAllExtents_T = typename TRemoveCV<typename TRemovePointer<typename TRemoveReference<T>::Type>::Type>::Type;
	template<typename T>
	using TRemoveCV_T = typename TRemoveCV<T>::Type;

	// UE4 only has a check for a member function but we need a check for a static function too
#define GENERATE_STATIC_FUNCTION_CHECK(MemberName, Result)						\
template <typename T>															\
class THasMemberFunction_##MemberName											\
{																				\
	template <typename U, Result (*)()> struct Check {};						\
	template <typename U> static char MemberTest(Check<U, &U::MemberName> *);	\
	template <typename U> static int MemberTest(...);							\
public:																			\
	enum { Value = sizeof(MemberTest<T>(0)) == sizeof(char) };					\
};

	GENERATE_STATIC_FUNCTION_CHECK(StaticStruct, UScriptStruct*)
		GENERATE_STATIC_FUNCTION_CHECK(StaticClass, UClass*)

#undef GENERATE_STATIC_FUNCTION_CHECK

	template<typename T>
	struct TIsUStruct
	{
		enum { Value = THasMemberFunction_StaticStruct<T>::Value };
	};

	template <typename T>
	struct TIsUClass
	{
		enum { Value = THasMemberFunction_StaticClass<T>::Value };
	};

	// Since UClasses can be bound via derived types, we need to do extra work on them so split the implementation
	COHTMLPLUGIN_API void BindUType(cohtml::Binder* binder, const void* Object, const UStruct* Type);
	COHTMLPLUGIN_API void ReadUType(cohtml::Binder* binder, void* Object, const UStruct* Type);
	COHTMLPLUGIN_API void BindUType(cohtml::Binder* binder, const void* Object, const UClass* Type);
	COHTMLPLUGIN_API void ReadUType(cohtml::Binder* binder, void* Object, const UClass* Type);

	template <typename T>
	struct DisableDefaultBinding<T, typename TEnableIf<TIsUClass<T>::Value || TIsUStruct<T>::Value, T>::Type> : TrueType
	{
	};
}

namespace cohtml
{

typedef void (*CoherentCustomBind)(cohtml::Binder* binder, const void* instance);

template <typename T>
void CoherentCustomBindStub(cohtml::Binder* binder, const void* instance)
{
	CoherentBind(binder, const_cast<T*>(static_cast<const T*>(instance)));
}

COHTMLPLUGIN_API void RegisterCustomBindImpl(const UStruct* type, CoherentCustomBind stub);
COHTMLPLUGIN_API void RegisterCustomBindImpl(const UClass* type, CoherentCustomBind stub);

template <typename T>
typename TEnableIf<TIsUStruct<T>::Value>::Type RegisterCustomBind()
{
	RegisterCustomBindImpl(T::StaticStruct(), &CoherentCustomBindStub<T>);
}

template <typename T>
typename TEnableIf<TIsUClass<T>::Value>::Type RegisterCustomBind()
{
	RegisterCustomBindImpl(T::StaticClass(), &CoherentCustomBindStub<T>);
}

template<typename UType>
typename TEnableIf<TIsUClass<UType>::Value>::Type
CoherentBind(cohtml::Binder* Binder, const UType* Object)
{
	BindUType(Binder, Object, UType::StaticClass());
}
template<typename UType>
typename TEnableIf<TIsUStruct<UType>::Value>::Type
CoherentBind(cohtml::Binder* Binder, const UType* Object)
{
	BindUType(Binder, Object, UType::StaticStruct());
}

template<typename UType>
typename TEnableIf<TIsUClass<UType>::Value>::Type
CoherentBind(cohtml::Binder* Binder, UType* Object)
{
	BindUType(Binder, Object, UType::StaticClass());
}
template<typename UType>
typename TEnableIf<TIsUStruct<UType>::Value>::Type
CoherentBind(cohtml::Binder* Binder, UType* Object)
{
	BindUType(Binder, Object, UType::StaticStruct());
}

template <typename T>
typename TEnableIf<TIsUClass<T>::Value || TIsUStruct<T>::Value>::Type CoherentBindInternal(Binder* binder, T& object)
{
	CoherentBindInternalPointer(binder, object);
}

template <typename T>
typename TEnableIf<TIsUClass<T>::Value || TIsUStruct<T>::Value>::Type CoherentBindInternal(Binder* binder, const T& object)
{
	CoherentBindInternalPointer(binder, object);
}
template<typename UType>
typename TEnableIf<TIsUStruct<UType>::Value>::Type
	CoherentReadInternal(cohtml::Binder* Binder, UType& Object)
{
	ReadUType(Binder, &Object, UType::StaticStruct());
}
template<typename UType>
typename TEnableIf<TIsUClass<UType>::Value>::Type
	CoherentReadInternal(cohtml::Binder* Binder, UType& Object)
{
	ReadUType(Binder, &Object, UType::StaticClass());
}
// If you accept UObject* or a pointer to a UStruct as an argument
// We need to create the object manually - provide extra specializations for this purpose

// UStructs are not garbage-collected - only allow TUniquePtr
template<typename UType>
typename TEnableIf<TIsUStruct<UType>::Value>::Type
	CoherentReadInternal(cohtml::Binder* Binder, TUniquePtr<UType>& Object)
{
	Object.Reset(new UType());
	ReadUType(Binder, Object.Get(), UType::StaticStruct());
}
template<typename UType>
typename TEnableIf<TIsUClass<UType>::Value>::Type
	CoherentReadInternal(cohtml::Binder* Binder, UType*& Object)
{
	Object = NewObject<UType>(GetTransientPackage(), UType::StaticClass());
	// const_cast any potential constness here as it will error out
	ReadUType(Binder, const_cast<TRemoveCV_T<UType>*>(Object), UType::StaticClass());
}

}
