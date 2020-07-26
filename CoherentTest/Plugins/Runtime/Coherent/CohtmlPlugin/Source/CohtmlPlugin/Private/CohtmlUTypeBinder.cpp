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
#include "CohtmlUTypeBinder.h"

#include "UObject/Class.h"
#include "Internationalization/Regex.h"
#include "CohtmlEventHelpers.h"
#include "cohtml/Binding/Binding.h"
#include "cohtml/Binding/Binder.h"
#include "cohtml/Binding/EventHandler.h"
#include "CohtmlFStringBinder.h"
#include "CohtmlFVectorBinder.h"
#include "CohtmlFIntVectorBinder.h"
#include "CohtmlFColorBinder.h"
#include "CohtmlSettings.h"

#if defined(COHTML_UE4_413_SUPPORT)
#include <UObject/ObjectBase.h>
#else
#include <UObject/UObjectBase.h>
#endif
#include "UObject/TextProperty.h"

namespace cohtml
{

class UE4Property : public Property
{
public:
	UE4Property(const UProperty* Prop)
		: Property(nullptr)
		, UPropertyMember(Prop)
	{
		// When registering a struct made from Blueprints UE4 adds suffix on each property name.
		// We search for this suffix and remove it.
		const FRegexPattern MyPattern(TEXT("^(\\w+?)_[\\d\\w]+_(?:.*)"));
		FString RealPropName = UPropertyMember->GetName();
		FRegexMatcher MyMatcher(MyPattern, RealPropName);

		if (MyMatcher.FindNext())
		{
			RealPropName = MyMatcher.GetCaptureGroup(1);
		}

		FTCHARToUTF8 Converter(*RealPropName);
		UTF8Name.SetNumUninitialized(Converter.Length() + 1);
		FMemory::Memcpy(UTF8Name.GetData(), Converter.Get(), Converter.Length());
		UTF8Name[Converter.Length()] = '\0';

		m_Name = reinterpret_cast<const char*>(UTF8Name.GetData());
	}

	UE4Property(const UE4Property& CopiedProp)
		: Property(CopiedProp)
		, UPropertyMember(CopiedProp.UPropertyMember)
		, UTF8Name(CopiedProp.UTF8Name)
	{
		m_Name = reinterpret_cast<const char*>(UTF8Name.GetData());
	}

	virtual void* Bind(Binder* Binder, void* Object) const override
	{
		Binder->PropertyName(GetName());
		return BindValue(Binder, Object);
	}
	virtual void* BindValue(Binder* Binder, void* Object) const override = 0;
	virtual void* Read(Binder* Binder, void* Object) const override
	{
		if (Binder->ReadProperty(GetName()))
		{
			ReadValue(Binder, Object);
		}
		return Object;
	}
	virtual void* ReadValue(Binder* Binder, void* Object) const = 0;
	virtual UE4Property* Clone() const override = 0;

	virtual bool ToBoolean(void* object, bool* boolean) const override
	{
		return false;
	}

	virtual bool ToNumber(void* object, float* number) const override
	{
		return false;
	}

	virtual bool ToString(void* object, char* buffer, size_t* length) const override
	{
		return false;
	}

	virtual bool ToColor(void* object, renoir::Color* color) const override
	{
		return false;
	}

	virtual bool ToTransformMatrix2D(void* object, float matrix[6]) const override
	{
		return false;
	}

	virtual bool ToArray(Binder* binder, void* object, cohtml::ArrayInfo* arrayInfo) const override
	{
		return false;
	}

	virtual bool ToPair(Binder* binder, void* object, PairInfo* pairInfo) const override
	{
		return false;
	}

	virtual bool ToMap(Binder* binder, void* object, MapInfo* mapInfo) const override
	{
		return false;
	}

	virtual bool ToObject(Binder* binder, void* object, cohtml::ObjectInfo* typeInfo) const override
	{
		return false;
	}

protected:
	const UProperty* UPropertyMember;
	TArray<UTF8CHAR> UTF8Name;
};

template<typename T>
struct TIsSignedIntegerProperty
{
	static const bool Value = TOr<TIsSame<T, UIntProperty>, TIsSame<T, UInt64Property>>::Value;
};

template<typename T>
struct TIsUnsignedIntegerProperty
{
	static const bool Value = TOr<TIsSame<T, UUInt32Property>, TIsSame<T, UByteProperty>, TIsSame<T, UUInt64Property>>::Value;
};

template<typename T>
struct TIsFloatingPointProperty
{
	static const bool Value = TOr<TIsSame<T, UFloatProperty>, TIsSame<T, UDoubleProperty>>::Value;
};

template<typename T>
struct TIsNumericProperty
{
	static const bool Value = TOr<TIsSignedIntegerProperty<T>, TIsUnsignedIntegerProperty<T>, TIsFloatingPointProperty<T>>::Value;
};

template<typename PropType, typename CType>
typename TEnableIf<TIsNumericProperty<PropType>::Value, bool>::Type
	UE4PropertyToString(const UProperty* Property, void* object, char* buffer, size_t* length)
{
	const auto Prop = static_cast<const PropType*>(Property);
	const auto PropValue = Prop->GetNumericPropertyValueToString(Prop->template ContainerPtrToValuePtr<CType>(object));
	CoherentToString<FString>::Invoke(PropValue, buffer, length);
	return true;
}

template<typename PropType, typename CType>
typename TEnableIf<TOr<TIsSame<PropType, UTextProperty>, TIsSame<PropType, UNameProperty>>::Value, bool>::Type
	UE4PropertyToString(const UProperty* Property, void* object, char* buffer, size_t* length)
{
	const auto Prop = static_cast<const PropType*>(Property);
	const auto PropValue = Prop->GetPropertyValuePtr_InContainer(object);
	CoherentToString<FString>::Invoke(PropValue->ToString(), buffer, length);
	return true;
}

template<typename PropType, typename CType>
typename TEnableIf<TIsSame<PropType, UStrProperty>::Value, bool>::Type
	UE4PropertyToString(const UProperty* Property, void* object, char* buffer, size_t* length)
{
	const auto Prop = static_cast<const PropType*>(Property);
	const FString* PropValue = Prop->GetPropertyValuePtr_InContainer(object);
	CoherentToString<FString>::Invoke(*PropValue, buffer, length);
	return true;
}

template<typename PropType, typename CType>
typename TEnableIf<!TOr<TIsNumericProperty<PropType>, TIsSame<PropType, UNameProperty>, TIsSame<PropType, UTextProperty>,
						TIsSame<PropType, UStrProperty>>::Value, bool>::Type
	UE4PropertyToString(const UProperty* Property, void* object, char* buffer, size_t* length)
{
	return false;
}

template<typename PropType, typename CType>
typename TEnableIf<TIsSignedIntegerProperty<PropType>::Value, bool>::Type
	UE4PropertyToNumber(const UProperty* Property, void* object, float* number)
{
	const auto Prop = static_cast<const PropType*>(Property);
	*number = Prop->GetSignedIntPropertyValue(Prop->template ContainerPtrToValuePtr<CType>(object));
	return true;
}

template<typename PropType, typename CType>
typename TEnableIf<TIsUnsignedIntegerProperty<PropType>::Value, bool>::Type
	UE4PropertyToNumber(const UProperty* Property, void* object, float* number)
{
	const auto Prop = static_cast<const PropType*>(Property);
	*number = Prop->GetUnsignedIntPropertyValue(Prop->template ContainerPtrToValuePtr<CType>(object));
	return true;
}

template<typename PropType, typename CType>
typename TEnableIf<TIsFloatingPointProperty<PropType>::Value, bool>::Type
	UE4PropertyToNumber(const UProperty* Property, void* object, float* number)
{
	const auto Prop = static_cast<const PropType*>(Property);
	*number = Prop->GetFloatingPointPropertyValue(Prop->template ContainerPtrToValuePtr<CType>(object));
	return true;
}

template<typename PropType, typename CType>
typename TEnableIf<!TIsNumericProperty<PropType>::Value, bool>::Type
	UE4PropertyToNumber(const UProperty* Property, void* object, float* number)
{
	return false;
}

template<typename PropType, typename CType>
class UE4PrimitiveProperty : public UE4Property
{
public:
	UE4PrimitiveProperty(const UProperty* Prop)
		: UE4Property(Prop)
	{}

	UE4PrimitiveProperty(const UE4PrimitiveProperty& CopiedProp)
		: UE4Property(CopiedProp)
	{}

	virtual void* BindValue(Binder* Binder, void* Object) const override
	{
		using namespace cohtml;
		const auto Prop = Cast<PropType>(UPropertyMember);
		check(Prop);
		auto value = Prop->GetPropertyValue(Prop->template ContainerPtrToValuePtr<CType>(Object));
		CoherentBindInternal(Binder, value);

		return Object;
	}

	virtual void* ReadValue(Binder* Binder, void* Object) const override
	{
		using namespace cohtml;
		const auto Prop = Cast<PropType>(UPropertyMember);
		check(Prop);
		auto Value = Prop->GetDefaultPropertyValue();
		CoherentReadInternal(Binder, Value);
		auto PropAddress = Prop->template ContainerPtrToValuePtr<CType>(Object);
		Prop->SetPropertyValue(PropAddress, Value);

		return Object;
	}

	virtual UE4PrimitiveProperty* Clone() const override
	{
		return new UE4PrimitiveProperty(*this);
	}

	virtual bool ToBoolean(void* object, bool* boolean) const override
	{
		const auto Prop = Cast<UBoolProperty>(UPropertyMember);
		*boolean = Prop->GetPropertyValue(Prop->template ContainerPtrToValuePtr<bool>(object));
		return true;
	}

	virtual bool ToNumber(void* object, float* number) const override
	{
		return UE4PropertyToNumber<PropType, CType>(UPropertyMember, object, number);
	}

	virtual bool ToString(void* object, char* buffer, size_t* length) const override
	{
		return UE4PropertyToString<PropType, CType>(UPropertyMember, object, buffer, length);
	}
};

#if !defined(COHTML_UE4_414_SUPPORT)
class UE4EnumProperty : public UE4Property
{
public:
	UE4EnumProperty(const UProperty* Prop)
		: UE4Property(Prop)
	{}
	UE4EnumProperty(const UE4EnumProperty& CopiedProp)
		: UE4Property(CopiedProp)
	{}

	virtual void* BindValue(Binder* Binder, void* Object) const override
	{
		using namespace cohtml;
		const auto Prop = Cast<UEnumProperty>(UPropertyMember);
		check(Prop);
		auto value = Prop->GetUnderlyingProperty()->GetSignedIntPropertyValue(Prop->template ContainerPtrToValuePtr<UEnum>(Object));
		CoherentBindInternal(Binder, value);

		return Object;
	}

	virtual void* ReadValue(Binder* Binder, void* Object) const override
	{
		using namespace cohtml;
		const auto Prop = Cast<UEnumProperty>(UPropertyMember);
		check(Prop);
		int64 Value = 0;
		CoherentReadInternal(Binder, Value);
		auto PropAddress = Prop->template ContainerPtrToValuePtr<UEnum>(Object);
		Prop->GetUnderlyingProperty()->SetIntPropertyValue(PropAddress, Value);

		return Object;
	}

	virtual UE4EnumProperty* Clone() const override
	{
		return new UE4EnumProperty(*this);
	}

	virtual bool ToNumber(void* object, float* number) const override
	{
		const auto Prop = static_cast<const UEnumProperty*>(UPropertyMember);
		const auto EnumNumProp = Prop->GetUnderlyingProperty();
		*number = EnumNumProp->GetSignedIntPropertyValue(EnumNumProp->ContainerPtrToValuePtr<int64>(object));

		return true;
	}

	virtual bool ToString(void* object, char* buffer, size_t* length) const override
	{
		const auto Prop = static_cast<const UEnumProperty*>(UPropertyMember);
		const auto EnumNumProp = Prop->GetUnderlyingProperty();
		return UE4PropertyToString<UNumericProperty, int64>(EnumNumProp, object, buffer, length);
	}
};
#endif

void BindUType(cohtml::Binder* Binder, const void* Object, const UStruct* Type);

cohtml::ElementType UE4PropertyToElementType(const UProperty* Property)
{
	UClass* PropertyClass = Property->StaticClass();
	if (PropertyClass == UBoolProperty::StaticClass())
	{
		return cohtml::ElementType::ET_Boolean;
	}
	else if (PropertyClass == UByteProperty::StaticClass() ||
		PropertyClass == UIntProperty::StaticClass() ||
		PropertyClass == UInt64Property::StaticClass())
	{
		return cohtml::ElementType::ET_Int32;
	}
	else if (PropertyClass == UUInt32Property::StaticClass() ||
		PropertyClass == UUInt64Property::StaticClass())
	{
		return cohtml::ElementType::ET_UInt32;
	}
	else if (PropertyClass == UFloatProperty::StaticClass())
	{
		return cohtml::ElementType::ET_Float;
	}
	else if (PropertyClass == UDoubleProperty::StaticClass())
	{
		return cohtml::ElementType::ET_Double;
	}
	else if (PropertyClass == UStrProperty::StaticClass() ||
		PropertyClass == UNameProperty::StaticClass() ||
		PropertyClass == UTextProperty::StaticClass())
	{
		return cohtml::ElementType::ET_String;
	}
	else if (PropertyClass == UArrayProperty::StaticClass())
	{
		return cohtml::ElementType::ET_Array;
	}

	return cohtml::ElementType::ET_UserType;
}

class UE4StructProperty : public UE4Property
{
public:
	UE4StructProperty(const UProperty* Prop)
		:UE4Property(Prop)
	{}

	UE4StructProperty(const UE4StructProperty& CopiedProp)
		: UE4Property(CopiedProp)
	{}

	virtual void* BindValue(Binder* Binder, void* Object) const override
	{
		const auto Prop = Cast<UStructProperty>(UPropertyMember);
		check(Prop);
		const auto StructAddress = static_cast<const uint8*>(Object) + Prop->GetOffset_ForInternal();
		BindUType(Binder, StructAddress, Prop->Struct);

		return Object;
	}

	virtual void* ReadValue(Binder* Binder, void* Object) const override
	{
		const auto Prop = Cast<UStructProperty>(UPropertyMember);
		check(Prop);
		auto StructAddress = static_cast<uint8*>(Object) + Prop->GetOffset_ForInternal();
		ReadUType(Binder, StructAddress, Prop->Struct);

		return Object;
	}

	virtual UE4StructProperty* Clone() const override
	{
		return new UE4StructProperty(*this);
	}

	virtual bool ToObject(Binder* Binder, void* Object, cohtml::ObjectInfo* ObjInfo) const override
	{
		Binder::BindingMode Save = Binder->GetMode();
		Binder->SetMode(Binder::BindingMode::BM_GetTypeInfo);
		BindValue(Binder, Object);
		Binder->SetMode(Save);
		TypeInfo* TypeInfo = Binder->GetTypeInfo();

		const auto Prop = Cast<UStructProperty>(UPropertyMember);
		check(Prop);
		auto StructAddress = static_cast<uint8*>(Object) + Prop->GetOffset_ForInternal();

		*ObjInfo = cohtml::ObjectInfo
		{
			UE4PropertyToElementType(UPropertyMember),
			TypeInfo,
			StructAddress
		};

		return true;
	}
};

class UE4ObjectProperty : public UE4Property
{
public:
	UE4ObjectProperty(const UProperty* Prop)
		: UE4Property(Prop)
	{
	}

	UE4ObjectProperty(const UE4ObjectProperty& CopiedProp)
		: UE4Property(CopiedProp)
	{
	}

	virtual void* BindValue(Binder* Binder, void* Object) const override
	{
		auto Prop = Cast<UObjectProperty>(UPropertyMember);
		BindUType(Binder, UnwrapUObjectPointer(Object, Prop), Prop->PropertyClass);

		return Object;
	}

	virtual void* ReadValue(Binder* Binder, void* Object) const override
	{
		const auto Prop = Cast<UObjectProperty>(UPropertyMember);
		ReadUType(Binder, UnwrapUObjectPointer(Object, Prop), Prop->PropertyClass);

		return Object;
	}

	virtual UE4ObjectProperty* Clone() const override
	{
		return new UE4ObjectProperty(*this);
	}

	virtual bool ToObject(Binder* Binder, void* Object, cohtml::ObjectInfo* ObjInfo) const override
	{
		Binder::BindingMode Save = Binder->GetMode();
		Binder->SetMode(Binder::BindingMode::BM_GetTypeInfo);
		BindValue(Binder, Object);
		Binder->SetMode(Save);
		TypeInfo* TypeInfo = Binder->GetTypeInfo();

		const auto Prop = Cast<UObjectProperty>(UPropertyMember);
		check(Prop);
		auto Address = UnwrapUObjectPointer(Object, Prop);

		*ObjInfo = cohtml::ObjectInfo{
			UE4PropertyToElementType(UPropertyMember),
			TypeInfo,
			Address
		};

		return true;
	}

private:
	void* UnwrapUObjectPointer(void* Object, const UObjectProperty* Prop) const
	{
		check(Prop);
		auto UObjectPointer = static_cast<const uint8*>(Object) + Prop->GetOffset_ForInternal();
		check(UObjectPointer)
		auto* PointedAddress = reinterpret_cast<const size_t*>(UObjectPointer);
		return reinterpret_cast<void*>(*PointedAddress);
	}
};

class UE4FTransformProperty : public UE4StructProperty
{
public:
	UE4FTransformProperty(const UProperty* Prop)
		: UE4StructProperty(Prop)
	{}
	UE4FTransformProperty(const UE4FTransformProperty& CopiedProp)
		: UE4StructProperty(CopiedProp)
	{}

	virtual UE4FTransformProperty* Clone() const override
	{
		return new UE4FTransformProperty(*this);
	}

	virtual bool ToTransformMatrix2D(void* object, float matrix[6]) const override
	{
		const auto Prop = static_cast<const UStructProperty*>(UPropertyMember);
		const auto TransformMatrix = Prop->ContainerPtrToValuePtr<FTransform>(object)->ToMatrixWithScale();
		matrix[0] = TransformMatrix.M[0][0];
		matrix[1] = TransformMatrix.M[0][1];
		matrix[2] = TransformMatrix.M[1][0];
		matrix[3] = TransformMatrix.M[1][1];
		matrix[4] = TransformMatrix.M[0][3];
		matrix[5] = TransformMatrix.M[1][3];

		return true;
	}
};

class UE4FColorProperty : public UE4StructProperty
{
public:
	UE4FColorProperty(const UProperty* Prop)
		: UE4StructProperty(Prop)
	{}
	UE4FColorProperty(const UE4FColorProperty& CopiedProp)
		: UE4StructProperty(CopiedProp)
	{}

	virtual UE4FColorProperty* Clone() const override
	{
		return new UE4FColorProperty(*this);
	}

	virtual bool ToColor(void* object, renoir::Color* color) const override
	{
		const auto Prop = static_cast<const UStructProperty*>(UPropertyMember);
		FColor* PropValue = Prop->ContainerPtrToValuePtr<FColor>(object);
		*color = renoir::Color(
			PropValue->R,
			PropValue->G,
			PropValue->B,
			PropValue->A
		);

		return true;
	}
};

class UE4FLinearColorProperty : public UE4StructProperty
{
public:
	UE4FLinearColorProperty(const UProperty* Prop)
		: UE4StructProperty(Prop)
	{}
	UE4FLinearColorProperty(const UE4FLinearColorProperty& CopiedProp)
		: UE4StructProperty(CopiedProp)
	{}

	virtual UE4FLinearColorProperty* Clone() const override
	{
		return new UE4FLinearColorProperty(*this);
	}

	virtual bool ToColor(void* object, renoir::Color* color) const override
	{
		const auto Prop = static_cast<const UStructProperty*>(UPropertyMember);
		FLinearColor* PropValue = Prop->ContainerPtrToValuePtr<FLinearColor>(object);
		FColor PropColor = PropValue->ToFColor(false);
		*color = renoir::Color(
			PropColor.R,
			PropColor.G,
			PropColor.B,
			PropColor.A
		);

		return true;
	}
};

struct FPropBinder
{
	using CanBindPredicate = bool(*)(const UProperty*, bool);
	using BindProperty = TUniquePtr<UE4Property>(*)(const UProperty*);

	CanBindPredicate CanBind;
	BindProperty Bind;
};

struct UE4ArrayInfo
{
	void* Array = nullptr;
	UArrayProperty* Prop = nullptr;
	UE4Property* InnerProp = nullptr;
};
const FPropBinder* IsPropertyBindable(const UProperty* Property, bool DissableUObjectBinding);

void CoherentVectorElementReader(Binder* Binder, void* Data, size_t Position)
{
	const auto Info = static_cast<UE4ArrayInfo*>(Data);
	FScriptArrayHelper ArrayHelper(Info->Prop, Info->Prop->ContainerPtrToValuePtr<void>(Info->Array));

	Info->InnerProp->ReadValue(Binder, ArrayHelper.GetRawPtr(Position));
}

using ReaderFunction = void(*)(Binder*, void*, size_t);

class VectorReaderFactory
{
public:
	static ReaderFunction ElementReader()
	{
		return cohtml::CoherentVectorElementReader;
	}
};

void CoherentVectorElementBinder(Binder* Binder, void* Array, size_t Index)
{
	const auto Info = static_cast<UE4ArrayInfo*>(Array);

	if (Info)
	{
		FScriptArrayHelper ArrayHelper(Info->Prop, Info->Prop->ContainerPtrToValuePtr<void>(Info->Array));

		Info->InnerProp->BindValue(Binder, ArrayHelper.GetRawPtr(Index));
	}
	else
	{
		Binder->BindNull();
	}
}

void* CoherentArrayElementGetter(void* Array, size_t Index)
{
	const auto Info = static_cast<UE4ArrayInfo*>(Array);
	const auto Prop = Info->Prop;
	FScriptArrayHelper ArrayHelper(Prop, Prop->ContainerPtrToValuePtr<void>(Info->Array));
	return ArrayHelper.GetRawPtr(Index);
}

size_t CoherentArrayLengthGetter(void* Array)
{
	const auto Info = static_cast<UE4ArrayInfo*>(Array);
	const auto Prop = Info->Prop;
	FScriptArrayHelper ArrayHelper(Prop, Prop->ContainerPtrToValuePtr<void>(Info->Array));
	return ArrayHelper.Num();
}

class UE4ArrayProperty : public UE4Property
{
public:
	UE4ArrayProperty(const UProperty* prop)
		: UE4Property(prop)
	{
		auto Prop = Cast<UArrayProperty>(UPropertyMember);
		if (auto PropBinder = IsPropertyBindable(Prop->Inner, false))
		{
			InnerProperty = PropBinder->Bind(Prop->Inner);
		}
		else
		{
			InnerProperty = nullptr;
		}
	}
	UE4ArrayProperty(const UE4ArrayProperty& o)
		: UE4Property(o)
		, InnerProperty(o.InnerProperty->Clone())
	{
	}

	virtual void* Bind(Binder* Binder, void* Object) const override
	{
		Binder->PropertyName(GetName());
		if (InnerProperty)
		{
			return UE4ArrayProperty::BindValue(Binder, Object);
		}
		else
		{
			Binder->BindNull();
			return Object;
		}
	}

	virtual void* BindValue(Binder* Binder, void* Object) const override
	{
		auto Prop = Cast<UArrayProperty>(UPropertyMember);
		check(Prop);

		const auto ElementProperty = Prop->Inner;
		Info.Array = Object;
		Info.Prop = const_cast<UArrayProperty*>(Prop);
		Info.InnerProp = InnerProperty.Get();

		FScriptArrayHelper ArrayHelper(Prop, Prop->ContainerPtrToValuePtr<void>(Object));

		if (!Binder->TryBindArrayByRef(&Info,
			ArrayHelper.Num(),
			CoherentVectorElementBinder,
			VectorReaderFactory::ElementReader()))
		{
			Binder->ArrayBegin(ArrayHelper.Num());
			for (auto Index = 0; Index < ArrayHelper.Num(); ++Index)
			{
				InnerProperty->BindValue(Binder, ArrayHelper.GetRawPtr(Index));
			}
			Binder->ArrayEnd();
		}

		return Object;
	}

	virtual void* Read(Binder* Binder, void* Object) const override
	{
		if (Binder->ReadProperty(GetName()))
		{
			UE4ArrayProperty::ReadValue(Binder, Object);
		}
		return Object;
	}

	virtual void* ReadValue(Binder* Binder, void* Object) const override
	{
		const auto Prop = Cast<UArrayProperty>(UPropertyMember);
		check(Prop);

		Prop->InitializeValue_InContainer(Object);
		const auto ElementProperty = Prop->Inner;
		FScriptArrayHelper ArrayHelper(Prop, Prop->ContainerPtrToValuePtr<void>(Object));
		const auto Size = Binder->ReadArrayBegin();
		if (Size != 0)
		{
			ArrayHelper.Resize(Size);
		}
		for (auto Index = 0u; Index < Size; ++Index)
		{
			Binder->ReadArrayElement(Index);
			InnerProperty->ReadValue(Binder, ArrayHelper.GetRawPtr(Index));
		}
		Binder->ReadArrayEnd();

		return Object;
	}

	virtual UE4ArrayProperty* Clone() const override
	{
		return new UE4ArrayProperty(*this);
	}

	virtual bool ToArray(Binder* Binder, void* Object, cohtml::ArrayInfo* ArrayInfo) const override
	{
		const auto Prop = static_cast<const UArrayProperty*>(UPropertyMember);
		Info.Array = Object;
		Info.Prop = const_cast<UArrayProperty*>(Prop);
		Info.InnerProp = InnerProperty.Get();
		Binder::BindingMode Save = Binder->GetMode();
		Binder->SetMode(Binder::BindingMode::BM_GetTypeInfo);
		InnerProperty->BindValue(Binder, Object);
		Binder->SetMode(Save);
		TypeInfo* TypeInfo = Binder->GetTypeInfo();

		*ArrayInfo = cohtml::ArrayInfo
		{
			UE4PropertyToElementType(Prop->Inner),
			&CoherentArrayLengthGetter,
			&CoherentArrayElementGetter,
			TypeInfo,
			&Info
		};

		return true;
	}

private:
	TUniquePtr<UE4Property> InnerProperty;
	mutable UE4ArrayInfo Info;
};

class UE4MapProperty : public UE4Property
{
public:
	UE4MapProperty(const UProperty* prop)
		: UE4Property(prop)
	{
		const auto Prop = Cast<UMapProperty>(UPropertyMember);
		check(Prop);

		if (auto PropBinder = IsPropertyBindable(Prop->KeyProp, false))
		{
			KeyProperty = PropBinder->Bind(Prop->KeyProp);
		}
		else
		{
			KeyProperty = nullptr;
		}

		if (auto PropBinder = IsPropertyBindable(Prop->ValueProp, false))
		{
			ValueProperty = PropBinder->Bind(Prop->ValueProp);
		}
		else
		{
			ValueProperty = nullptr;
		}
	}
	UE4MapProperty(const UE4MapProperty& o)
		: UE4Property(o)
		, KeyProperty(o.KeyProperty->Clone())
		, ValueProperty(o.ValueProperty->Clone())
	{
	}

	virtual void* Bind(Binder* Binder, void* Object) const override
	{
		Binder->PropertyName(GetName());
		if (KeyProperty && ValueProperty)
		{
			return UE4MapProperty::BindValue(Binder, Object);
		}
		else
		{
			Binder->BindNull();
			return Object;
		}
	}

	virtual void* BindValue(Binder* Binder, void* Object) const override
	{
		const auto Prop = Cast<UMapProperty>(UPropertyMember);
		check(Prop);
		FScriptMapHelper MapHelper(Prop, Prop->ContainerPtrToValuePtr<void>(Object));
		Binder->MapBegin(MapHelper.Num());

		for (auto Index = 0; Index < MapHelper.Num(); ++Index)
		{
			KeyProperty->BindValue(Binder, MapHelper.GetPairPtr(Index));
			ValueProperty->BindValue(Binder, MapHelper.GetPairPtr(Index));
		}
		Binder->MapEnd();

		return Object;
	}

	virtual void* Read(Binder* Binder, void* Object) const override
	{
		if (Binder->ReadProperty(GetName()))
		{
			UE4MapProperty::ReadValue(Binder, Object);
		}
		return Object;
	}

	virtual void* ReadValue(Binder* Binder, void* Object) const override
	{
		const auto Prop = Cast<UMapProperty>(UPropertyMember);
		check(Prop);
		const auto KeyProp = Prop->KeyProp;
		const auto ValueProp = Prop->ValueProp;
		Prop->InitializeValue_InContainer(Object);
		FScriptMapHelper MapHelper(Prop, Prop->ContainerPtrToValuePtr<void>(Object));
		const auto Size = Binder->ReadMapBegin();
		for (auto Index = 0u; Index < Size; ++Index)
		{
			const auto PairAddress = MapHelper.GetPairPtr(MapHelper.AddUninitializedValue());
			Binder->ReadKeyValuePair();
			// Important: We don't need to offset the value from the pair address! This is done automatically
			// inside the ValueProp
			KeyProp->InitializeValue_InContainer(PairAddress);
			ValueProp->InitializeValue_InContainer(PairAddress);
			KeyProperty->ReadValue(Binder, PairAddress);
			ValueProperty->ReadValue(Binder, PairAddress);
		}
		Binder->ReadMapEnd();
		MapHelper.Rehash();

		return Object;
	}

	virtual UE4MapProperty* Clone() const override
	{
		return new UE4MapProperty(*this);
	}

private:
	TUniquePtr<UE4Property> KeyProperty;
	TUniquePtr<UE4Property> ValueProperty;
};

template<typename PropType, typename CType>
TUniquePtr<UE4Property> InstantiateProperty(const UProperty* Prop)
{
	TUniquePtr<UE4Property> CohtmlProp(new UE4PrimitiveProperty<PropType, CType>(Prop));
	return CohtmlProp;
}

TUniquePtr<UE4Property> InstantiateFColorProperty(const UProperty* Prop)
{
	TUniquePtr<UE4Property> CohtmlProp(new UE4FColorProperty(Prop));
	return CohtmlProp;
}

TUniquePtr<UE4Property> InstantiateFLinearColorProperty(const UProperty* Prop)
{
	TUniquePtr<UE4Property> CohtmlProp(new UE4FLinearColorProperty(Prop));
	return CohtmlProp;
}

TUniquePtr<UE4Property> InstantiateFTransformProperty(const UProperty* Prop)
{
	TUniquePtr<UE4Property> CohtmlProp(new UE4FTransformProperty(Prop));
	return CohtmlProp;
}

TUniquePtr<UE4Property> InstantiateStructProperty(const UProperty* Prop)
{
	TUniquePtr<UE4Property> CohtmlProp(new UE4StructProperty(Prop));
	return CohtmlProp;
}

TUniquePtr<UE4Property> InstantiateObjectProperty(const UProperty* Prop)
{
	TUniquePtr<UE4Property> CohtmlProp(new UE4ObjectProperty(Prop));
	return CohtmlProp;
}

TUniquePtr<UE4Property> InstantiateArrayProperty(const UProperty* Prop)
{
	TUniquePtr<UE4Property> CohtmlProp(new UE4ArrayProperty(Prop));
	return CohtmlProp;
}

TUniquePtr<UE4Property> InstantiateMapProperty(const UProperty* Prop)
{
	TUniquePtr<UE4Property> CohtmlProp(new UE4MapProperty(Prop));
	return CohtmlProp;
}
#if !defined(COHTML_UE4_414_SUPPORT)
TUniquePtr<UE4Property> InstantiateEnumProperty(const UProperty* Prop)
{
	TUniquePtr<UE4Property> CohtmlProp(new UE4EnumProperty(Prop));
	return CohtmlProp;
}
#endif

template<typename PropType>
bool CanBindProperty(const UProperty* Property, bool DissableUObjectBinding);
template<>
bool CanBindProperty<UArrayProperty>(const UProperty* Property, bool DissableUObjectBinding);
template<>
bool CanBindProperty<UMapProperty>(const UProperty* Property, bool DissableUObjectBinding);
bool CanBindFColorProperty(const UProperty* Property, bool DissableUObjectBinding);
bool CanBindFLinearColorProperty(const UProperty* Property, bool DissableUObjectBinding);
bool CanBindFTransformProperty(const UProperty* Property, bool DissableUObjectBinding);

const FPropBinder FPropertyBinders[] =
{
	{ &CanBindProperty<UBoolProperty>, &InstantiateProperty<UBoolProperty, bool> },
	{ &CanBindProperty<UByteProperty>, &InstantiateProperty<UByteProperty, uint8> },
	{ &CanBindProperty<UIntProperty>, &InstantiateProperty<UIntProperty, int32> },
	{ &CanBindProperty<UUInt32Property>, &InstantiateProperty<UUInt32Property, uint32> },
	{ &CanBindProperty<UInt64Property>, &InstantiateProperty<UInt64Property, int64> },
	{ &CanBindProperty<UUInt64Property>, &InstantiateProperty<UUInt64Property, uint64> },
	{ &CanBindProperty<UFloatProperty>, &InstantiateProperty<UFloatProperty, float> },
	{ &CanBindProperty<UDoubleProperty>, &InstantiateProperty<UDoubleProperty, double> },
	{ &CanBindProperty<UStrProperty>, &InstantiateProperty<UStrProperty, FString> },
	{ &CanBindProperty<UTextProperty>, &InstantiateProperty<UTextProperty, FText> },
	{ &CanBindProperty<UNameProperty>, &InstantiateProperty<UNameProperty, FName> },
#if !defined(COHTML_UE4_414_SUPPORT)
	{ &CanBindProperty<UEnumProperty>, &InstantiateEnumProperty },
#endif
	{ &CanBindFColorProperty, &InstantiateFColorProperty },
	{ &CanBindFLinearColorProperty, &InstantiateFLinearColorProperty },
	{ &CanBindFTransformProperty, &InstantiateFTransformProperty },
	{ &CanBindProperty<UStructProperty>, &InstantiateStructProperty },
	{ &CanBindProperty<UArrayProperty>, &InstantiateArrayProperty },
	{ &CanBindProperty<UMapProperty>, &InstantiateMapProperty },
	// InstantiateObjectProperty must be the last element of the sequence.
	// The order is used to prevent recursive binding of UObject when the binding mode is ByValue
	{ &CanBindProperty<UObjectProperty>, &InstantiateObjectProperty }
	};

const FPropBinder* IsPropertyBindable(const UProperty* Property, bool DissableUObjectBinding)
{
	auto PrimitiveBindersCount = sizeof(FPropertyBinders) / sizeof(FPropBinder);
	if (DissableUObjectBinding)
	{
		--PrimitiveBindersCount;
	}
	for (auto Index = 0u; Index < PrimitiveBindersCount; ++Index)
	{
		const auto& PropBinder = FPropertyBinders[Index];
		if (PropBinder.CanBind(Property, DissableUObjectBinding))
		{
			return &PropBinder;
		}
	}
	return nullptr;
}

bool CanBindFColorProperty(const UProperty* Property, bool)
{
	const auto Prop = Cast<UStructProperty>(Property);
	if (!Prop)
	{
		return false;
	}

	return Prop->Struct == TBaseStructure<FColor>::Get();
}

bool CanBindFLinearColorProperty(const UProperty* Property, bool)
{
	const auto Prop = Cast<UStructProperty>(Property);
	if (!Prop)
	{
		return false;
	}

	return Prop->Struct == TBaseStructure<FLinearColor>::Get();
}

bool CanBindFTransformProperty(const UProperty* Property, bool)
{
	const auto Prop = Cast<UStructProperty>(Property);
	if (!Prop)
	{
		return false;
	}

	return Prop->Struct == TBaseStructure<FTransform>::Get();
}

template<typename PropType>
bool CanBindProperty(const UProperty* Property, bool)
{
	return Property->IsA<PropType>();
}

// Only bind containers if their types are bindable
template<>
bool CanBindProperty<UArrayProperty>(const UProperty* Property, bool DissableUObjectBinding)
{
	const auto Prop = Cast<UArrayProperty>(Property);
	return Prop && IsPropertyBindable(Prop->Inner, DissableUObjectBinding);
}
template<>
bool CanBindProperty<UMapProperty>(const UProperty* Property, bool DissableUObjectBinding)
{
	const auto Prop = Cast<UMapProperty>(Property);
	if (!Prop)
	{
		return false;
	}
	const auto KeyProperty = Prop->KeyProp;
	if (!KeyProperty->IsA(UStrProperty::StaticClass()))
	{
		COHTML_UE_LOG(Warning, TEXT("Can't bind map property '%s'! JS only supports strings as map keys but this property's key type is '%s'"), *Prop->GetName(), *KeyProperty->GetName());
		return false;
	}
	return IsPropertyBindable(Prop->ValueProp, DissableUObjectBinding) != nullptr;
}

typedef TMap<const UStruct*, CoherentCustomBind> CustomUStructBinders;
typedef TMap<const UClass*, CoherentCustomBind> CustomUClassBinders;

CustomUStructBinders s_UStructBinders;
CustomUClassBinders s_UClassBinders;

void RegisterCustomBindImpl(const UStruct* type, CoherentCustomBind stub)
{
	s_UStructBinders.Add(type, stub);
}

void RegisterCustomBindImpl(const UClass* type, CoherentCustomBind stub)
{
	s_UClassBinders.Add(type, stub);
}


void RegisterUType(cohtml::Binder* Binder, void* Object, const UStruct* Type)
{
	const bool ShouldDisableUObjectBinding = Binder->GetMode() == Binder::BindingMode::BM_Value;
	FString TypeName(Type->GetName());
	if (auto type = Binder->RegisterType(TCHAR_TO_UTF8(*TypeName), Object))
	{
		for (const auto Property : TFieldRange<UProperty>(Type, EFieldIteratorFlags::IncludeSuper))
		{
			if (auto PropBinder = IsPropertyBindable(Property, ShouldDisableUObjectBinding))
			{
				Binder->AddProperty(Object, *(PropBinder->Bind(Property).Get()));
			}
		}
	}
}

void BindUType(cohtml::Binder* Binder, const void* Object, const UStruct* Type)
{
	Binder->BeginType();
	auto binder = s_UStructBinders.Find(Type);
	if (!binder)
	{
		RegisterUType(Binder, const_cast<void*>(Object), Type);
	}
	else
	{
		(**binder)(Binder, Object);
	}
	Binder->EndType(const_cast<void*>(Object));
}

void RegisterUType(cohtml::Binder* Binder, void* Object, const UClass* Type)
{
	const bool ShouldDisableUObjectBinding = Binder->GetMode() == Binder::BindingMode::BM_Value;
	FString TypeName(Type->GetName());
	// It is correct to expose the same object as by-ref and/or by-value. So we must register two different types
	if (!ShouldDisableUObjectBinding)
	{
		TypeName += "_ByRef";
	}
	if (auto type = Binder->RegisterType(TCHAR_TO_UTF8(*TypeName), Object))
	{
		for (const auto Property : TFieldRange<UProperty>(Type, EFieldIteratorFlags::IncludeSuper))
		{
			if (auto PropBinder = IsPropertyBindable(Property, ShouldDisableUObjectBinding))
			{
				Binder->AddProperty(Object, *(PropBinder->Bind(Property).Get()));
			}
		}
	}
}

void BindUType(cohtml::Binder* Binder, const void* Object, const UClass* Type)
{
	Binder->BeginType();
	auto binder = s_UClassBinders.Find(Type);
	if (!binder)
	{
		RegisterUType(Binder, const_cast<void*>(Object), Type);
	}
	else
	{
		(**binder)(Binder, Object);
	}
	Binder->EndType(const_cast<void*>(Object));
}

void ReadUType(cohtml::Binder* Binder, void* Object, const UStruct* Type)
{
	if (!Object)
	{
		return;
	}

	Binder->ReadType();
	auto binder = s_UStructBinders.Find(Type);
	if (!binder)
	{
		RegisterUType(Binder, const_cast<void*>(Object), Type);
	}
	else
	{
		(**binder)(Binder, Object);
	}
	Binder->EndType(const_cast<void*>(Object));
}

void ReadUType(cohtml::Binder* Binder, void* Object, const UClass* Type)
{
	if (!Object)
	{
		return;
	}

	if (Binder->PeekValueType() == cohtml::VT_Null)
	{
		Binder->ReadNull();
		return;
	}

	if (Binder->PeekValueType() != cohtml::VT_Object)
	{
		const FString TypeName = Type->GetName();
		COHTML_UE_LOG(Warning,
			TEXT("Binding for UObject property of type %s failed - received a non-object value (%d). This looks like argument stack corruption."),
			*TypeName, static_cast<int32>(Binder->PeekValueType()));
		return;
	}

	Binder->ReadType();
	auto binder = s_UClassBinders.Find(Type);
	if (!binder)
	{
		RegisterUType(Binder, const_cast<void*>(Object), Type);
	}
	else
	{
		(**binder)(Binder, Object);
	}
	Binder->EndType(const_cast<void*>(Object));
}

}

