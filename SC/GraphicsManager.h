#pragma once
#include "DeviceManager.h"
#include "SwapChainManager.h"
#include "RenderTargetManager.h"
#include <memory>            // std::shared_ptr

class Mesh;
class PipelineManager;
class ConstantBufferManager;
class GraphicsManager {
public:
    void SetHWND(HWND hwnd); // �O������HWND��n��
    void Initialize();       // �e�}�l�[�W���[������
    void BeginFrame();       // �`�揀��
    void EndFrame();         // �`��I���EPresent
    void Cleanup();          // ���
    ID3D12Device* GetDevice() const;
    // �O�p�`�`��p�̊֐��iMesh��PipelineManager���󂯎��j
    void DrawQuad(std::shared_ptr<Mesh> QuadMesh, PipelineManager* pipelineManager,ConstantBufferManager* constantBuffer);
    ID3D12GraphicsCommandList* GetCommandList();

private:
    HWND m_hWnd = nullptr;

    DeviceManager m_deviceManager;
    SwapChainManager m_swapChainManager;
    RenderTargetManager m_renderTargetManager;

    int m_width = 1280;
    int m_height = 720;

};
