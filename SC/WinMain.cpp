#include <Windows.h>
#include "ApplicationManager.h"
#include "GameEngine.h"
#include "EngineManager.h"
#include "GraphicsManager.h"
#include "PipelineManager.h"
#include "WindowManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    auto* applicationManager = new ApplicationManager();
    auto* graphicsManager = new GraphicsManager();
    auto* pipeLineManager = new PipelineManager();
    auto* engine = new GameEngine();  // �� ������ GameEngine ��OK�I
	auto* windowManager = new WindowManager();

    // �V���O���g����Manager�o�^
	EngineManager::GetInstance().SetWindowManager(windowManager); // WindowManager�o�^
    EngineManager::GetInstance().SetApplicationManager(applicationManager);
    EngineManager::GetInstance().SetGraphicsManager(graphicsManager);
    EngineManager::GetInstance().SetPipelineManager(pipeLineManager);
    EngineManager::GetInstance().SetGameEngine(engine);  // �� GameEngine�o�^�I

    // Run�ɂ�GameEngine*��n��
    return applicationManager->Run(engine, hInstance, nCmdShow);
}
