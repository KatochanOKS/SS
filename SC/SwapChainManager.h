#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
using Microsoft::WRL::ComPtr;
class SwapChainManager {
public:
    void Initialize(HWND hwnd, ID3D12Device* device, ID3D12CommandQueue* commandQueue);
    void Present();
    IDXGISwapChain4* GetSwapChain() const { return m_swapChain.Get(); }
    UINT GetCurrentBackBufferIndex() const;

private:
    ComPtr<IDXGISwapChain4> m_swapChain;
};
