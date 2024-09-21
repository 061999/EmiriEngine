//
// Created by primal on 24-9-21.
//
#pragma once
#ifndef DX_COMMON_H
#define DX_COMMON_H

#include <directx/d3d12.h>
#include <dxgi1_6.h>

#define DXUUID(x) get_guid((x)),((void**)(&x))

namespace Emiri
{
	using ID3D12DeviceN = ID3D12Device7;
	using ID3D12GraphicsCommandListN = ID3D12GraphicsCommandList6;
	using IDXGIFactoryN = IDXGIFactory7;
	using IDXGISwapChainN = IDXGISwapChain4;
	using IDXGIAdapterN = IDXGIAdapter4;

	template<typename T>
	constexpr inline GUID get_guid(const T*)
	{
		return __uuidof(T);
	}

	struct DxObject
	{
		static IDXGIFactoryN* m_Factory;
		static IDXGIAdapterN* m_Adapter;
		static ID3D12DeviceN* m_Device;
		static ID3D12CommandQueue* m_DirectQueue;
		static ID3D12CommandQueue* m_CopyQueue;

	};


}

#endif //DX_COMMON_H
