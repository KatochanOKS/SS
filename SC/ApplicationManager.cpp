#include "ApplicationManager.h"
#include "WindowManager.h"
#include "GraphicsManager.h"
#include "GameEngine.h"
#include <Windows.h>
#include "EngineManager.h"

int ApplicationManager::Run(GameEngine* engine, HINSTANCE hInstance, int nCmdShow) {
    // ウィンドウ作成
    auto* window = EngineManager::GetInstance().GetWindowManager();
    window->Initialize(hInstance, nCmdShow);
    m_hWnd = window->GetHWnd();

    // グラフィックスマネージャーの初期化
    auto* graphics = EngineManager::GetInstance().GetGraphicsManager();
    graphics->SetHWND(m_hWnd);
    graphics->Initialize();

    // ゲームエンジン初期化（ここでは空でもOK）
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
