#include "GraphicsManager.h"
#include <cassert>
#include "Mesh.h"
#include "PipelineManager.h"
#include <memory>       // 念のため
#include <d3d12.h>      // DX12コマンド

// ウィンドウハンドルを外部から受け取り、保持する
void GraphicsManager::SetHWND(HWND hwnd) {
    m_hWnd = hwnd;
}
ID3D12Device* GraphicsManager::GetDevice() const {
    return m_deviceManager.GetDevice();
}
// 各描画用マネージャーを初期化する（デバイス → スワップチェイン → レンダーターゲットの順）
void GraphicsManager::Initialize() {
    // DirectX 12 のデバイス、コマンド周りを初期化
    m_deviceManager.Initialize();

    // ウィンドウに描画するためのスワップチェインを初期化
    m_swapChainManager.Initialize(m_hWnd, m_deviceManager.GetDevice(), m_deviceManager.GetCommandQueue());

    // バックバッファに描画するためのRTV（レンダーターゲットビュー）を準備
    m_renderTargetManager.Initialize(m_deviceManager.GetDevice(), m_swapChainManager.GetSwapChain());
}

// 毎フレーム呼ばれる：描画の準備（RenderTargetの設定とクリア）を行う
void GraphicsManager::BeginFrame() {
    auto* cmdList = m_deviceManager.GetCommandList(); // コマンドリスト取得
    auto backBufferIndex = m_swapChainManager.GetCurrentBackBufferIndex(); // 現在のバックバッファのインデックス

    // レンダーターゲットの設定とクリア
    m_renderTargetManager.BeginRender(cmdList, backBufferIndex);
}

// 毎フレーム呼ばれる：描画の完了処理とGPUへの実行依頼を行う
void GraphicsManager::EndFrame() {
    auto* cmdList = m_deviceManager.GetCommandList();
    auto backBufferIndex = m_swapChainManager.GetCurrentBackBufferIndex();

    // バックバッファを描画ターゲットからPresent状態へ戻す
    m_renderTargetManager.EndRender(cmdList, backBufferIndex);

    // コマンドリストの記録を終了し、GPUに実行させる
    cmdList->Close();
    ID3D12CommandList* lists[] = { cmdList };
    m_deviceManager.GetCommandQueue()->ExecuteCommandLists(1, lists);

    

    // 画面に表示（バックバッファをフロントバッファに切り替える）
    m_swapChainManager.Present();
    // GPUが完了するまでフェンスで待機（CPUとGPUの同期）
    m_deviceManager.WaitForGPU();
    // コマンドリストとアロケータを再準備（次のフレームのために）
    m_deviceManager.ResetCommandList();
}

// 四角形（インデックスバッファあり）用の描画関数
void GraphicsManager::DrawQuad(std::shared_ptr<Mesh> quadMesh, PipelineManager* pipelineManager) {
    auto* cmdList = m_deviceManager.GetCommandList();

    // パイプライン＆ルートシグネチャのセット
    cmdList->SetPipelineState(pipelineManager->GetPipeline("Basic"));
    cmdList->SetGraphicsRootSignature(pipelineManager->GetRootSignature());

    // ビューポート・シザー矩形（ここでは画面全体と仮定）
    D3D12_VIEWPORT viewport = { 0, 0, (float)m_width, (float)m_height, 0, 1 };
    D3D12_RECT scissorRect = { 0, 0, (LONG)m_width, (LONG)m_height };
    cmdList->RSSetViewports(1, &viewport);
    cmdList->RSSetScissorRects(1, &scissorRect);

    // バッファセット
    cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    cmdList->IASetVertexBuffers(0, 1, &quadMesh->VertexBufferView);

    // インデックスバッファがある場合は四角形として描画
    if (quadMesh->IndexBuffer && quadMesh->IndexCount > 0) {
        cmdList->IASetIndexBuffer(&quadMesh->IndexBufferView);
        cmdList->DrawIndexedInstanced(quadMesh->IndexCount, 1, 0, 0, 0);
    }
    else {
        // 万が一インデックスがない場合は通常描画
        cmdList->DrawInstanced(quadMesh->VertexCount, 1, 0, 0);
    }
}


// 終了時の解放処理
void GraphicsManager::Cleanup() {

    m_renderTargetManager.Cleanup();
    m_deviceManager.Cleanup(); // ※ SwapChainManager は自動で解放されるので省略可
}

// 外部からコマンドリストを使いたいときの取得関数
ID3D12GraphicsCommandList* GraphicsManager::GetCommandList() {
    return m_deviceManager.GetCommandList();
}

