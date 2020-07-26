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
#include "CohtmlMeshData.h"

#include "Model.h"
#include "StaticMeshResources.h"
#include "Engine/StaticMesh.h"

namespace
{
#if !defined(COHTML_UE4_418_SUPPORT)
	uint32 GetUVStride(const FStaticMeshVertexBuffer& VertexBuffer)
	{
		uint32 UVStride;
		if (VertexBuffer.GetUseFullPrecisionUVs())
		{
			typedef TStaticMeshVertexUVsDatum<typename TStaticMeshVertexUVsTypeSelector<EStaticMeshVertexUVType::HighPrecision>::UVsTypeT> UVType;
			UVStride = sizeof(UVType) * VertexBuffer.GetNumTexCoords();
		}
		else
		{
			typedef TStaticMeshVertexUVsDatum<typename TStaticMeshVertexUVsTypeSelector<EStaticMeshVertexUVType::Default>::UVsTypeT> UVType;
			UVStride = sizeof(UVType) * VertexBuffer.GetNumTexCoords();
		}
		return UVStride;
	}
#endif

	void LoadMeshLODIndices(const FStaticMeshLODResources& LODResources, TArray<uint32>& Indices)
	{
		auto& IndexBuffer = LODResources.IndexBuffer;
		if (IsVulkanPlatform(GMaxRHIShaderPlatform))
		{
			// The Vulkan RHI doesn't currently implement LockBuffer with Mode RLM_ReadOnly, so we have to access the CPU data if it is available.
			IndexBuffer.GetCopy(Indices);
		}
		else
		{
			const auto Is32Bit = IndexBuffer.Is32Bit();
			const auto NumIndices = LODResources.GetNumTriangles() * 3;
			auto IndexBufferData = RHILockIndexBuffer(IndexBuffer.IndexBufferRHI, 0, Is32Bit ? NumIndices * 4 : NumIndices * 2, RLM_ReadOnly);

			Indices.AddUninitialized(NumIndices);
			if (Is32Bit)
			{
				FMemory::Memcpy(Indices.GetData(), IndexBufferData, Indices.GetAllocatedSize());
			}
			else
			{
				auto IndexBufferUInt16 = static_cast<const uint16*>(IndexBufferData);
				for (auto i = 0; i != NumIndices; ++i)
				{
					Indices[i] = IndexBufferUInt16[i];
				}
			}

			RHIUnlockIndexBuffer(IndexBuffer.IndexBufferRHI);
		}
	}

#if defined(COHTML_UE4_418_SUPPORT)
	void LoadMeshLODUVs(const FStaticMeshLODResources& LODResources, TArray<FCohtmlVertexUV>& UVs)
	{
		if (IsVulkanPlatform(GMaxRHIShaderPlatform))
		{
			COHTML_UE_LOG(Error, TEXT("Pointer Events with Vulkan are currently not supported with this version of the engine"));
			return;
		}

		auto& VertexBuffer = LODResources.VertexBuffer;
		const auto NumVertices = LODResources.GetNumVertices();
		const bool bUseFullUVs = VertexBuffer.GetUseFullPrecisionUVs();
		const auto Stride = VertexBuffer.GetStride();
		auto VertexBufferData = static_cast<uint8*>(RHILockVertexBuffer(VertexBuffer.VertexBufferRHI, 0, NumVertices * Stride, RLM_ReadOnly));

		UVs.AddUninitialized(NumVertices);
		const auto NumTexCoords = VertexBuffer.GetNumTexCoords();

		for (auto Index = 0u; Index != NumVertices; ++Index)
		{
			auto Vertex = VertexBufferData + Index * Stride;
			for (auto Channel = 0; Channel != NumTexCoords; ++Channel)
			{
#ifdef COHTML_UE4_411_SUPPORT
				if (!bUseFullUVs)
				{
					UVs[Index].Channels[Channel] = ((TStaticMeshFullVertexFloat16UVs<MAX_STATIC_TEXCOORDS>*)Vertex)->UVs[Channel];
				}
				else
				{
					UVs[Index].Channels[Channel] = ((TStaticMeshFullVertexFloat32UVs<MAX_STATIC_TEXCOORDS>*)Vertex)->UVs[Channel];
				}
#else
				if (!bUseFullUVs)
				{
					using FStaticMeshFullVertex = TStaticMeshFullVertex<EStaticMeshVertexTangentBasisType::Default,
						EStaticMeshVertexUVType::Default, MAX_STATIC_TEXCOORDS>;
					UVs[Index].Channels[Channel] = ((FStaticMeshFullVertex*)Vertex)->UVs[Channel];
				}
				else
				{
					using FStaticMeshFullVertex = TStaticMeshFullVertex<EStaticMeshVertexTangentBasisType::HighPrecision,
						EStaticMeshVertexUVType::HighPrecision, MAX_STATIC_TEXCOORDS>;
					UVs[Index].Channels[Channel] = ((FStaticMeshFullVertex*)Vertex)->UVs[Channel];
				}
#endif
			}
		}
		RHIUnlockVertexBuffer(VertexBuffer.VertexBufferRHI);
	}
#else
	void LoadMeshLODUVs(FStaticMeshLODResources& LODResources, TArray<FCohtmlVertexUV>& UVs)
	{
		auto& VertexBuffer = LODResources.VertexBuffers.StaticMeshVertexBuffer;
		const auto NumVertices = LODResources.GetNumVertices();
		const bool bUseFullUVs = VertexBuffer.GetUseFullPrecisionUVs();
		auto Stride = GetUVStride(VertexBuffer);

		uint8* TexcoordDataPtr = nullptr;
		if (IsVulkanPlatform(GMaxRHIShaderPlatform))
		{
			// The Vulkan RHI doesn't currently implement LockBuffer with Mode RLM_ReadOnly, so we have to access the CPU data if it is available.
			TexcoordDataPtr = static_cast<uint8*>(VertexBuffer.GetTexCoordData());
		}
		else
		{
			TexcoordDataPtr = static_cast<uint8*>(RHILockVertexBuffer(VertexBuffer.TexCoordVertexBuffer.VertexBufferRHI, 0, NumVertices * Stride, RLM_ReadOnly));
		}

		UVs.AddUninitialized(NumVertices);
		const auto NumTexCoords = VertexBuffer.GetNumTexCoords();

		for (auto Index = 0u; Index != NumVertices; ++Index)
		{
			for (auto Channel = 0; Channel != NumTexCoords; ++Channel)
			{
				if (!bUseFullUVs)
				{
					typedef TStaticMeshVertexUVsDatum<typename TStaticMeshVertexUVsTypeSelector<EStaticMeshVertexUVType::Default>::UVsTypeT> UVType;
					UVType* ElementData = reinterpret_cast<UVType*>(TexcoordDataPtr + (Index * Stride));
					UVs[Index].Channels[Channel] = ElementData[Channel].GetUV();
				}
				else
				{
					typedef TStaticMeshVertexUVsDatum<typename TStaticMeshVertexUVsTypeSelector<EStaticMeshVertexUVType::HighPrecision>::UVsTypeT> UVType;
					UVType* ElementData = reinterpret_cast<UVType*>(TexcoordDataPtr + (Index * Stride));
					UVs[Index].Channels[Channel] = ElementData[Channel].GetUV();
				}
			}
		}

		if (!IsVulkanPlatform(GMaxRHIShaderPlatform))
		{
			RHIUnlockVertexBuffer(VertexBuffer.TexCoordVertexBuffer.VertexBufferRHI);
		}
	}
#endif

	void LoadMeshLODPositions(FStaticMeshLODResources& LODResources, TArray<FVector>& Positions)
	{
#if defined(COHTML_UE4_418_SUPPORT)
		auto& PositionVertex = LODResources.PositionVertexBuffer;
#else
		auto& PositionVertex = LODResources.VertexBuffers.PositionVertexBuffer;
#endif
		const auto NumVertices = LODResources.GetNumVertices();
		const auto Stride = PositionVertex.GetStride();
		const uint8* PositionBufferData = nullptr;

		if (IsVulkanPlatform(GMaxRHIShaderPlatform))
		{
			// The Vulkan RHI doesn't currently implement LockBuffer with Mode RLM_ReadOnly, so we have to access the CPU data if it is available.
			PositionBufferData = static_cast<const uint8*>(PositionVertex.GetVertexData());
		}
		else
		{
			PositionBufferData = static_cast<const uint8*>(RHILockVertexBuffer(PositionVertex.VertexBufferRHI, 0, NumVertices * Stride, RLM_ReadOnly));
		}

		Positions.AddUninitialized(NumVertices);
		for (auto Index = 0u; Index != NumVertices; ++Index)
		{
			auto Vertex = (FPositionVertex*)(PositionBufferData + Index * Stride);
			Positions[Index] = Vertex->Position;
		}

		if (!IsVulkanPlatform(GMaxRHIShaderPlatform))
		{
			RHIUnlockVertexBuffer(PositionVertex.VertexBufferRHI);
		}
	}

	void LoadMeshLOD(FStaticMeshLODResources& LODResources, FCohtmlMeshLOD& LODData)
	{
		if (IsVulkanPlatform(GMaxRHIShaderPlatform) && !LODResources.VertexBuffers.StaticMeshVertexBuffer.GetAllowCPUAccess())
		{
			// The Vulkan RHI doesn't currently implement LockBuffer with Mode RLM_ReadOnly, so we have to access the CPU data if it is available.
			COHTML_UE_LOG(Error, TEXT("Unable to get texture coordinates data for static mesh and therefore pointer events for inworld views won't work!"
				" The Allow CPU Access option in the Static Mesh settings should be enabled for pointer events to work with Vulkan!"));
			return;
		}

		LoadMeshLODIndices(LODResources, LODData.Indices);
		LoadMeshLODUVs(LODResources, LODData.UVs);
		LoadMeshLODPositions(LODResources, LODData.Positions);
	}

}

FCohtmlMeshData LoadCohtmlMeshData(const UStaticMeshComponent* MeshComponent)
{
#if defined(COHTML_UE4_413_SUPPORT)
	UStaticMesh* StaticMesh = MeshComponent->StaticMesh;
#else
	UStaticMesh* StaticMesh = MeshComponent->GetStaticMesh();
#endif
	auto& LODs = StaticMesh->RenderData->LODResources;
	auto NumLODs = LODs.Num();
	FCohtmlMeshData Data;
	Data.Mesh = MeshComponent;
	Data.LODs.Reserve(NumLODs);
	for (auto LOD = 0u; LOD != NumLODs; ++LOD)
	{
		FCohtmlMeshLOD MeshLOD;
		LoadMeshLOD(LODs[LOD], MeshLOD);
		Data.LODs.Add(MeshLOD);
	}
	return Data;
}
