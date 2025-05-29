#pragma once

class ApplicationManager;
class GraphicsManager;
class PipelineManager;
class GameEngine;
class WindowManager;
class MeshManager;  // MenuManagerは必要なら追加
class DeviceManager;  // DeviceManagerは必要なら追加
class ConstantBufferManager;  // ConstantBufferManagerは必要なら追加
// 必要ならここに他のManagerも追加（SceneManagerなど）

class EngineManager {
public:
    static EngineManager& GetInstance() {
        static EngineManager instance;
        return instance;
    }
    // コピー・代入禁止
    EngineManager(const EngineManager&) = delete;
    EngineManager& operator=(const EngineManager&) = delete;

    // セッター／ゲッター
	void SetWindowManager(WindowManager* mgr) { m_windowManager = mgr; }
	WindowManager* GetWindowManager() { return m_windowManager; }
	void SetEngineManager(EngineManager* mgr) { m_engineManager = mgr; }
	EngineManager* GetEngineManager() { return m_engineManager; }

	void SetGameEngine(GameEngine* engine) { m_gameEngine = engine; }
	GameEngine* GetGameEngine() { return m_gameEngine; }
    void SetApplicationManager(ApplicationManager* mgr) { m_appManager = mgr; }
    ApplicationManager* GetApplicationManager() { return m_appManager; }

    void SetGraphicsManager(GraphicsManager* mgr) { m_graphicsManager = mgr; }
    GraphicsManager* GetGraphicsManager() { return m_graphicsManager; }

    void SetPipelineManager(PipelineManager* mgr) { m_pipelineManager = mgr; }
    PipelineManager* GetPipelineManager() { return m_pipelineManager; }

	void SetMeshManager(MeshManager* mgr) { m_meshManager = mgr; }  // MenuManagerのセッター
	MeshManager* GetMeshManager() { return m_meshManager; }  // MenuManagerのゲッター
    // 他Managerもここに追加可能

	void SetDeviceManager(DeviceManager* mgr) { m_deviceManager = mgr; }  // DeviceManagerのセッター
	DeviceManager* GetDeviceManager() { return m_deviceManager; }  // DeviceManagerのゲッター

	void SetConstantBufferManager(ConstantBufferManager* mgr) { m_constantBufferManager = mgr; }  // ConstantBufferManagerのセッター
	ConstantBufferManager* GetConstantBufferManager() { return m_constantBufferManager; }  // ConstantBufferManagerのゲッター
private:
    EngineManager() = default;
    ApplicationManager* m_appManager = nullptr;
    GraphicsManager* m_graphicsManager = nullptr;
    PipelineManager* m_pipelineManager = nullptr;
	EngineManager* m_engineManager = nullptr;
	GameEngine* m_gameEngine = nullptr;  // GameEngineのポインタ
	WindowManager* m_windowManager = nullptr;  // WindowManagerのポインタ
	MeshManager* m_meshManager = nullptr;  // MenuManagerのポインタ（必要なら追加）
	DeviceManager* m_deviceManager = nullptr;  // DeviceManagerのポインタ（必要なら追加）
	ConstantBufferManager* m_constantBufferManager = nullptr;  // ConstantBufferManagerのポインタ（必要なら追加）
    // 他のManagerのポインタ
};
