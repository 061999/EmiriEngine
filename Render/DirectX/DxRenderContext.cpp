//
// Created by primal on 24-9-21.
//
#include "DxRenderContext.h"
#include "dx_common.h"
#include <Core/utl/common.h>
#include <array>
#include <Core/logger/Logger.h>
#include <wrl.h>

IDXGIFactory7* Emiri::DxObject::m_Factory{};
ID3D12Device7* Emiri::DxObject::m_Device{};
ID3D12CommandQueue* Emiri::DxObject::m_DirectQueue{};
ID3D12CommandQueue* Emiri::DxObject::m_CopyQueue{};

typedef std::pair<D3D_FEATURE_LEVEL, const wchar_t*> DxLevel;

static constexpr std::array<DxLevel, 11> level_mapping
{
	DxLevel{D3D_FEATURE_LEVEL_1_0_CORE,L"D3D_FEATURE_LEVEL_1_0_CORE"},
	DxLevel{D3D_FEATURE_LEVEL_9_1,L"D3D_FEATURE_LEVEL_9_1"},
	DxLevel{D3D_FEATURE_LEVEL_9_2,L"D3D_FEATURE_LEVEL_9_2"},
	DxLevel{D3D_FEATURE_LEVEL_9_3,L"D3D_FEATURE_LEVEL_9_3"},
	DxLevel{D3D_FEATURE_LEVEL_10_0,L"D3D_FEATURE_LEVEL_10_0"},
	DxLevel{D3D_FEATURE_LEVEL_10_1,L"D3D_FEATURE_LEVEL_10_1"},
	DxLevel{D3D_FEATURE_LEVEL_11_0,L"D3D_FEATURE_LEVEL_11_0"},
	DxLevel{D3D_FEATURE_LEVEL_11_1,L"D3D_FEATURE_LEVEL_11_1"},
	DxLevel{D3D_FEATURE_LEVEL_12_0,L"D3D_FEATURE_LEVEL_12_0"},
	DxLevel{D3D_FEATURE_LEVEL_12_1,L"D3D_FEATURE_LEVEL_12_1"},
	DxLevel{D3D_FEATURE_LEVEL_12_2,L"D3D_FEATURE_LEVEL_12_2"},
};

bool Emiri::DxRenderContext::Initialize()
{
	u32 flags = 0;
#ifndef NDEBUG
	flags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
	if (S_OK != CreateDXGIFactory2(flags, DXUUID(DxObject::m_Factory)))
	{
		LOG_ERROR("Create Dxgi Factory Error!!");
		return false;
	}

#ifndef NDEBUG
	{
		Microsoft::WRL::ComPtr<ID3D12Debug> debug_interface{};
		if (S_OK != D3D12GetDebugInterface(IID_PPV_ARGS(debug_interface.GetAddressOf())))
		{
			LOG_ERROR("Create D3D12 Debug Interface Error!!");
			return false;
		}
		debug_interface->EnableDebugLayer();
	}
#endif // NDEBUG

	if (S_OK != DxObject::m_Factory->EnumAdapterByGpuPreference(0u, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, DXUUID(DxObject::m_Adapter)))
	{
		LOG_ERROR("Create Dxgi Adapter Error!!");
		return false;
	}

	for (auto item = level_mapping.rbegin(); item != level_mapping.rend(); ++item)
	{
		if (D3D12CreateDevice(DxObject::m_Adapter, item->first, DXUUID(DxObject::m_Device)) == S_OK)
		{
			break;
		}
		DxObject::m_Device = nullptr;
	}

	if (nullptr == DxObject::m_Device)
	{
		LOG_ERROR("Create D3D12 Device Error!!");
		return false;
	}

#ifndef NDEBUG
	{
		Microsoft::WRL::ComPtr<ID3D12InfoQueue> info_queue{};
		DxObject::m_Device->QueryInterface(info_queue.GetAddressOf());
		info_queue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		info_queue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
		info_queue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
	}
#endif // _DEBUG



	return true;
}

void Emiri::DxRenderContext::Shutdown()
{

}