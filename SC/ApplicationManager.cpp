#include "ApplicationManager.h"
#include "WindowManager.h"
#include "GraphicsManager.h"
#include "GameEngine.h"
#include <Windows.h>
#include "EngineManager.h"
#include "MeshManager.h"
#include"PipelineManager.h"
#include "ConstantBufferManager.h"
int ApplicationManager::Run(GameEngine* engine, HINSTANCE hInstance, int nCmdShow) {
    // �E�B���h�E�쐬
    auto* window = EngineManager::GetInstance().GetWindowManager();
    window->Initialize(hInstance, nCmdShow);
    m_hWnd = window->GetHWnd();

    // �O���t�B�b�N�X�}�l�[�W���[�̏�����
    auto* graphics = EngineManager::GetInstance().GetGraphicsManager();
    graphics->SetHWND(m_hWnd);
    graphics->Initialize();
    // 3. PipelineManager�������i������PSO�⃋�[�g�V�O�l�`�������I�j
    EngineManager::GetInstance().GetPipelineManager()->Initialize(graphics->GetDevice());
    // �y�ǉ��zDevice�擾 �� MeshManager������
      // GetDevice()��GraphicsManager�Ɏ���
    EngineManager::GetInstance().GetMeshManager()->Initialize(graphics->GetDevice());
	auto* cbManager = EngineManager::GetInstance().GetConstantBufferManager();
    cbManager->Initialize(graphics->GetDevice(), 256); // 256�o�C�g�P��
    // �Q�[���G���W��������
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
