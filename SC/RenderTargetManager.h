#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
using Microsoft::WRL::ComPtr;
class RenderTargetManager {
public:
    void Initialize(ID3D12Device* device, IDXGISwapChain4* swapChain);
    void BeginRender(ID3D12GraphicsCommandList* cmdList, UINT backBufferIndex);
    void EndRender(ID3D12GraphicsCommandList* cmdList, UINT backBufferIndex);
    void Cleanup();

private:
    ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    ComPtr<ID3D12Resource> m_backBuffers[2];
    UINT m_rtvDescriptorSize = 0;
};
