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
    auto* engine = new GameEngine();  // © ‚±‚±‚Í GameEngine ‚ÅOKI
	auto* windowManager = new WindowManager();

    // ƒVƒ“ƒOƒ‹ƒgƒ“‚ÅManager“o˜^
	EngineManager::GetInstance().SetWindowManager(windowManager); // WindowManager“o˜^
    EngineManager::GetInstance().SetApplicationManager(applicationManager);
    EngineManager::GetInstance().SetGraphicsManager(graphicsManager);
    EngineManager::GetInstance().SetPipelineManager(pipeLineManager);
    EngineManager::GetInstance().SetGameEngine(engine);  // © GameEngine“o˜^I

    // Run‚É‚ÍGameEngine*‚ð“n‚·
    return applicationManager->Run(engine, hInstance, nCmdShow);
}
