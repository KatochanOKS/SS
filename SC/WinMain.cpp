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
    auto* engine = new GameEngine();  // �� ������ GameEngine ��OK�I
	auto* windowManager = new WindowManager();
	auto* meshManager = new MeshManager();
	auto* deviceManager = new DeviceManager();
	auto* constantBufferManager = new ConstantBufferManager(); // �萔�o�b�t�@�}�l�[�W���[�̃C���X�^���X���쐬

    // �V���O���g����Manager�o�^
	EngineManager::GetInstance().SetWindowManager(windowManager); // WindowManager�o�^
    EngineManager::GetInstance().SetApplicationManager(applicationManager);
    EngineManager::GetInstance().SetGraphicsManager(graphicsManager);
    EngineManager::GetInstance().SetPipelineManager(pipeLineManager);
    EngineManager::GetInstance().SetGameEngine(engine);  // �� GameEngine�o�^�I
	EngineManager::GetInstance().SetMeshManager(meshManager); // MeshManager�o�^
	EngineManager::GetInstance().SetDeviceManager(deviceManager); // DeviceManager�o�^
	EngineManager::GetInstance().SetConstantBufferManager(constantBufferManager); // �萔�o�b�t�@�}�l�[�W���[�o�^

    int result = applicationManager->Run(engine, hInstance, nCmdShow);

    // �� �I�����ɉ��
    delete windowManager;
    delete applicationManager;
    delete graphicsManager;
    delete pipeLineManager;
    delete engine;
	delete meshManager;
	delete deviceManager;
	delete constantBufferManager; // �萔�o�b�t�@�}�l�[�W���[�̉��
    return result;
}
