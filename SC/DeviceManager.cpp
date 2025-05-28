#include "DeviceManager.h"
#include <cassert>
#include <windows.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

using Microsoft::WRL::ComPtr;

void DeviceManager::Initialize() {
#ifdef _DEBUG
    ComPtr<ID3D12Debug> debug;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug)))) {
        debug->EnableDebugLayer();
    }
#endif

    // �f�o�C�X����
    HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_device));
    assert(SUCCEEDED(hr));

    // �R�}���h�A���P�[�^
    hr = m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));
    assert(SUCCEEDED(hr));

    // �R�}���h���X�g
    hr = m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), nullptr, IID_PPV_ARGS(&m_commandList));
    assert(SUCCEEDED(hr));

    // �R�}���h�L���[
    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    hr = m_device->CreateCommandQueue(&desc, IID_PPV_ARGS(&m_commandQueue));
    assert(SUCCEEDED(hr));

    // �t�F���X
    hr = m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
    assert(SUCCEEDED(hr));
    m_fenceEvent = CreateEventEx(nullptr, FALSE, FALSE, EVENT_ALL_ACCESS);
    assert(m_fenceEvent != nullptr);
    m_fenceValue = 1;
}
void DeviceManager::WaitForGPU() {
    // �R�}���h�L���[�ɃV�O�i���𑗂�
    HRESULT hr = m_commandQueue->Signal(m_fence.Get(), m_fenceValue);
    assert(SUCCEEDED(hr));

    // �O���FenceValue���I����Ă��Ȃ���Α҂�
    if (m_fence->GetCompletedValue() < m_fenceValue) {
        hr = m_fence->SetEventOnCompletion(m_fenceValue, m_fenceEvent);
        assert(SUCCEEDED(hr));
        WaitForSingleObject(m_fenceEvent, INFINITE);
    }

    m_fenceValue++;
}

void DeviceManager::ResetCommandList() {
    HRESULT hr;

    hr = m_commandAllocator->Reset();
    assert(SUCCEEDED(hr));

    hr = m_commandList->Reset(m_commandAllocator.Get(), nullptr); // PSO�͌�ŃZ�b�g
    assert(SUCCEEDED(hr));
}


void DeviceManager::Cleanup() {
    if (m_fenceEvent) {
        CloseHandle(m_fenceEvent);
        m_fenceEvent = nullptr;
    }
    // ComPtr��������Release����̂ŁA���ʂȏ����͕s�v
}
