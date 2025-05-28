#include "GraphicsManager.h"
#include <cassert>

// ウィンドウハンドルを外部から受け取り、保持する
void GraphicsManager::SetHWND(HWND hwnd) {
    m_hWnd = hwnd;
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

    // コマンドリストとアロケータを再準備（次のフレームのために）
    m_deviceManager.ResetCommandList();
}

// 終了時の解放処理
void GraphicsManager::Cleanup() {
    // GPUが完了するまでフェンスで待機（CPUとGPUの同期）
    m_deviceManager.WaitForGPU();
    m_renderTargetManager.Cleanup();
    m_deviceManager.Cleanup(); // ※ SwapChainManager は自動で解放されるので省略可
}

// 外部からコマンドリストを使いたいときの取得関数
ID3D12GraphicsCommandList* GraphicsManager::GetCommandList() {
    return m_deviceManager.GetCommandList();
}
