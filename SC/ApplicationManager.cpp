#include "ApplicationManager.h"
#include "WindowManager.h"
#include "GraphicsManager.h"
#include "GameEngine.h"
#include <Windows.h>
#include "EngineManager.h"

int ApplicationManager::Run(GameEngine* engine, HINSTANCE hInstance, int nCmdShow) {
    // �E�B���h�E�쐬
    auto* window = EngineManager::GetInstance().GetWindowManager();
    window->Initialize(hInstance, nCmdShow);
    m_hWnd = window->GetHWnd();

    // �O���t�B�b�N�X�}�l�[�W���[�̏�����
    auto* graphics = EngineManager::GetInstance().GetGraphicsManager();
    graphics->SetHWND(m_hWnd);
    graphics->Initialize();

    // �Q�[���G���W���������i�����ł͋�ł�OK�j
    engine->Initialize();

    // ���C�����[�v
    MSG msg = {};
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            graphics->BeginFrame();
            engine->Update();  // ���OK
            engine->Draw();    // ���OK
            graphics->EndFrame();
        }
    }

    graphics->Cleanup();
    return (int)msg.wParam;
}
