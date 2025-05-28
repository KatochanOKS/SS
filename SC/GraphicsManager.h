#pragma once
#include "DeviceManager.h"
#include "SwapChainManager.h"
#include "RenderTargetManager.h"

class GraphicsManager {
public:
    void SetHWND(HWND hwnd); // �O������HWND��n��
    void Initialize();       // �e�}�l�[�W���[������
    void BeginFrame();       // �`�揀��
    void EndFrame();         // �`��I���EPresent
    void Cleanup();          // ���

    ID3D12GraphicsCommandList* GetCommandList();

private:
    HWND m_hWnd = nullptr;

    DeviceManager m_deviceManager;
    SwapChainManager m_swapChainManager;
    RenderTargetManager m_renderTargetManager;
};
