#include "SwapChainManager.h"
#include <cassert>
using Microsoft::WRL::ComPtr;
void SwapChainManager::Initialize(HWND hwnd, ID3D12Device* device, ID3D12CommandQueue* commandQueue) {
    ComPtr<IDXGIFactory4> dxgiFactory;
    HRESULT hr = CreateDXGIFactory2(0, IID_PPV_ARGS(&dxgiFactory));
    assert(SUCCEEDED(hr));

    DXGI_SWAP_CHAIN_DESC1 desc = {};
    desc.BufferCount = 2;
    desc.Width = 1280;
    desc.Height = 720;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.SampleDesc.Count = 1;

   ComPtr<IDXGISwapChain1> swapChain1;
    hr = dxgiFactory->CreateSwapChainForHwnd(
        commandQueue, hwnd, &desc, nullptr, nullptr, &swapChain1);
    assert(SUCCEEDED(hr));

    hr = swapChain1->QueryInterface(IID_PPV_ARGS(&m_swapChain));
    assert(SUCCEEDED(hr));
}

void SwapChainManager::Present() {
    m_swapChain->Present(1, 0);
}

UINT SwapChainManager::GetCurrentBackBufferIndex() const {
    return m_swapChain->GetCurrentBackBufferIndex();
}
