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
#include "CohtmlTextTransformationManager.h"

#include <Runtime/Core/Public/Containers/StringConv.h>

FCohtmlTextTransformationManager::FCohtmlTextTransformationManager()
{}

namespace {

bool CopyToOutBuffer(char* Destination, const FTCHARToUTF8& Source, unsigned PreAllocatedBytesCount)
{
	if (PreAllocatedBytesCount < (unsigned)Source.Length())
	{
		return false;
	}
	FMemory::Memcpy(Destination, Source.Get(), Source.Length());
	return true;
}

}

bool FCohtmlTextTransformationManager::CaseMapCharacters(CaseOperation Operation,
		const char* UTF8Text,
		unsigned BytesCount,
		char* Transformed,
		unsigned TransformedBytesCount) const
{
	bool bResult = false;
	if (BytesCount == 0)
	{
		return bResult;
	}

	FText WideText = FText::FromString(UTF8_TO_TCHAR(UTF8Text));

	switch (Operation)
	{
	case CaseOperation::Uppercase:
	{
		auto TransformedUTF8 = FTCHARToUTF8(*(WideText.ToUpper().ToString()));
		bResult = CopyToOutBuffer(Transformed, TransformedUTF8, TransformedBytesCount);
	}
	break;
	case CaseOperation::Lowercase:
	{
		auto TransformedUTF8 = FTCHARToUTF8(*(WideText.ToLower().ToString()));
		bResult = CopyToOutBuffer(Transformed, TransformedUTF8, TransformedBytesCount);
	}
	break;
	case CaseOperation::Capitalize:
	{
		auto WideCharArray = WideText.ToString().GetCharArray();
		bool bWasPreviousCharWordBreak = true;
		for (auto& Char : WideCharArray)
		{
			if (TChar<TCHAR>::IsAlnum(Char))
			{
				if (bWasPreviousCharWordBreak)
				{
					Char = TChar<TCHAR>::ToUpper(Char);
					bWasPreviousCharWordBreak = false;
				}
			}
			// Underscore is not considered a word break:
			// https://www.unicode.org/reports/tr29/tr29-31.html#Default_Word_Boundaries
			else if (!TChar<TCHAR>::IsUnderscore(Char))
			{
				bWasPreviousCharWordBreak = true;
			}
		}
		auto TransformedUTF8 = FTCHARToUTF8(WideCharArray.GetData());
		bResult = CopyToOutBuffer(Transformed, TransformedUTF8, TransformedBytesCount);
	}
	break;
	default:
		check(false && "Unhandled text-transform case operation!");
	}

	return bResult;
}