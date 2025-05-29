#include <Windows.h>
#include "ApplicationManager.h"
#include "GameEngine.h"
#include "EngineManager.h"
#include "GraphicsManager.h"
#include "PipelineManager.h"
#include "WindowManager.h"
#include "MeshManager.h"
#include"DeviceManager.h"
#include"ConstantBufferManager.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    auto* applicationManager = new ApplicationManager();
    auto* graphicsManager = new GraphicsManager();
    auto* pipeLineManager = new PipelineManager();
    auto* engine = new GameEngine();  // ← ここは GameEngine でOK！
	auto* windowManager = new WindowManager();
	auto* meshManager = new MeshManager();
	auto* deviceManager = new DeviceManager();
	auto* constantBufferManager = new ConstantBufferManager(); // 定数バッファマネージャーのインスタンスを作成

    // シングルトンでManager登録
	EngineManager::GetInstance().SetWindowManager(windowManager); // WindowManager登録
    EngineManager::GetInstance().SetApplicationManager(applicationManager);
    EngineManager::GetInstance().SetGraphicsManager(graphicsManager);
    EngineManager::GetInstance().SetPipelineManager(pipeLineManager);
    EngineManager::GetInstance().SetGameEngine(engine);  // ← GameEngine登録！
	EngineManager::GetInstance().SetMeshManager(meshManager); // MeshManager登録
	EngineManager::GetInstance().SetDeviceManager(deviceManager); // DeviceManager登録
	EngineManager::GetInstance().SetConstantBufferManager(constantBufferManager); // 定数バッファマネージャー登録

    int result = applicationManager->Run(engine, hInstance, nCmdShow);

    // ★ 終了時に解放
    delete windowManager;
    delete applicationManager;
    delete graphicsManager;
    delete pipeLineManager;
    delete engine;
	delete meshManager;
	delete deviceManager;
	delete constantBufferManager; // 定数バッファマネージャーの解放
    return result;
}
