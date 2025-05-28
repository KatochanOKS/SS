#include "ApplicationManager.h"
#include "WindowManager.h"
#include "GraphicsManager.h"
#include "GameEngine.h"
#include <Windows.h>
#include "EngineManager.h"
#include "MeshManager.h"
#include"PipelineManager.h"
int ApplicationManager::Run(GameEngine* engine, HINSTANCE hInstance, int nCmdShow) {
    // ウィンドウ作成
    auto* window = EngineManager::GetInstance().GetWindowManager();
    window->Initialize(hInstance, nCmdShow);
    m_hWnd = window->GetHWnd();

    // グラフィックスマネージャーの初期化
    auto* graphics = EngineManager::GetInstance().GetGraphicsManager();
    graphics->SetHWND(m_hWnd);
    graphics->Initialize();
    // 3. PipelineManager初期化（ここでPSOやルートシグネチャを作る！）
    EngineManager::GetInstance().GetPipelineManager()->Initialize(graphics->GetDevice());
    // 【追加】Device取得 → MeshManager初期化
    ID3D12Device* device = graphics->GetDevice();  // GetDevice()はGraphicsManagerに実装
    EngineManager::GetInstance().GetMeshManager()->Initialize(device);

    // ゲームエンジン初期化
    engine->Initialize();


    // メインループ
    MSG msg = {};
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            graphics->BeginFrame();
            engine->Update();  // 空でOK
            engine->Draw();    // 空でOK
            graphics->EndFrame();
        }
    }

    graphics->Cleanup();
    return (int)msg.wParam;
}
