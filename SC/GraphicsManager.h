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
    void SetHWND(HWND hwnd); // 外部からHWNDを渡す
    void Initialize();       // 各マネージャー初期化
    void BeginFrame();       // 描画準備
    void EndFrame();         // 描画終了・Present
    void Cleanup();          // 解放
    ID3D12Device* GetDevice() const;
    // 三角形描画用の関数（MeshとPipelineManagerを受け取る）
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
