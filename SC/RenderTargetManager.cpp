#include "RenderTargetManager.h"
#include <cassert>
#include <cmath>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

void RenderTargetManager::Initialize(ID3D12Device* device, IDXGISwapChain4* swapChain) {
    // �f�B�X�N���v�^�q�[�v�iRTV�j�쐬
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.NumDescriptors = 2;
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    HRESULT hr = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_rtvHeap));
    assert(SUCCEEDED(hr));

    m_rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    // �o�b�N�o�b�t�@�擾 & RTV�쐬
    D3D12_CPU_DESCRIPTOR_HANDLE handle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
    for (UINT i = 0; i < 2; ++i) {
        hr = swapChain->GetBuffer(i, IID_PPV_ARGS(&m_backBuffers[i]));
        assert(SUCCEEDED(hr));
        device->CreateRenderTargetView(m_backBuffers[i].Get(), nullptr, handle);
        handle.ptr += m_rtvDescriptorSize;
    }
}

void RenderTargetManager::BeginRender(ID3D12GraphicsCommandList* cmdList, UINT backBufferIndex) {
    // �o���A: Present �� RenderTarget
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = m_backBuffers[backBufferIndex].Get();
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    cmdList->ResourceBarrier(1, &barrier);

    // �`��^�[�Q�b�g�ݒ�
    D3D12_CPU_DESCRIPTOR_HANDLE handle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
    handle.ptr += backBufferIndex * m_rtvDescriptorSize;
    cmdList->OMSetRenderTargets(1, &handle, FALSE, nullptr);

    // �`��N���A�i�F���A�j���[�V����������j
    static float radian = 0.0f;
    float r = std::cos(radian) * 0.5f + 0.5f;
    float g = 0.25f;
    float b = 0.5f;
    const float clearColor[] = { r, g, b, 1.0f };
    radian += 0.01f;

    cmdList->ClearRenderTargetView(handle, clearColor, 0, nullptr);
}

void RenderTargetManager::EndRender(ID3D12GraphicsCommandList* cmdList, UINT backBufferIndex) {
    // �o���A: RenderTarget �� Present
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = m_backBuffers[backBufferIndex].Get();
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    cmdList->ResourceBarrier(1, &barrier);
}

void RenderTargetManager::Cleanup() {
    for (auto& buf : m_backBuffers) {
        if (buf) buf.Reset();
    }
    if (m_rtvHeap) m_rtvHeap.Reset();
}
