#pragma once
#include <d3d12.h>
#include <wrl.h>

using namespace Microsoft::WRL; // For ComPtr
using Microsoft::WRL::ComPtr;
class DeviceManager {
public:
    void Initialize();
    void Cleanup();
    void WaitForGPU();
    void ResetCommandList();

    ID3D12Device* GetDevice() const { return m_device.Get(); }
    ID3D12GraphicsCommandList* GetCommandList() const { return m_commandList.Get(); }
    ID3D12CommandQueue* GetCommandQueue() const { return m_commandQueue.Get(); }
    ID3D12CommandAllocator* GetCommandAllocator() const { return m_commandAllocator.Get(); }

private:
    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> m_commandList;
    ComPtr<ID3D12CommandQueue> m_commandQueue;
    ComPtr<ID3D12Fence> m_fence;
    HANDLE m_fenceEvent = nullptr;
    UINT64 m_fenceValue = 0;
};
