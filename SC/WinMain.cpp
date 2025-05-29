#include <Windows.h>
#include "ApplicationManager.h"
#include "GameEngine.h"
#include "EngineManager.h"
#include "GraphicsManager.h"
#include "PipelineManager.h"
#include "WindowManager.h"
#include "MeshManager.h"
#include"DeviceManager.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    auto* applicationManager = new ApplicationManager();
    auto* graphicsManager = new GraphicsManager();
    auto* pipeLineManager = new PipelineManager();
    auto* engine = new GameEngine();  // © ‚±‚±‚Í GameEngine ‚ÅOKI
	auto* windowManager = new WindowManager();
	auto* meshManager = new MeshManager();
	auto* deviceManager = new DeviceManager();
    // ƒVƒ“ƒOƒ‹ƒgƒ“‚ÅManager“o˜^
	EngineManager::GetInstance().SetWindowManager(windowManager); // WindowManager“o˜^
    EngineManager::GetInstance().SetApplicationManager(applicationManager);
    EngineManager::GetInstance().SetGraphicsManager(graphicsManager);
    EngineManager::GetInstance().SetPipelineManager(pipeLineManager);
    EngineManager::GetInstance().SetGameEngine(engine);  // © GameEngine“o˜^I
	EngineManager::GetInstance().SetMeshManager(meshManager); // MeshManager“o˜^
	EngineManager::GetInstance().SetDeviceManager(deviceManager); // DeviceManager“o˜^

    int result = applicationManager->Run(engine, hInstance, nCmdShow);

    // š I—¹‚É‰ğ•ú
    delete windowManager;
    delete applicationManager;
    delete graphicsManager;
    delete pipeLineManager;
    delete engine;

    return result;
}
