#pragma once

class ApplicationManager;
class GraphicsManager;
class PipelineManager;
class GameEngine;
class WindowManager;
// �K�v�Ȃ炱���ɑ���Manager���ǉ��iSceneManager�Ȃǁj

class EngineManager {
public:
    static EngineManager& GetInstance() {
        static EngineManager instance;
        return instance;
    }
    // �R�s�[�E����֎~
    EngineManager(const EngineManager&) = delete;
    EngineManager& operator=(const EngineManager&) = delete;

    // �Z�b�^�[�^�Q�b�^�[
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

    // ��Manager�������ɒǉ��\

private:
    EngineManager() = default;
    ApplicationManager* m_appManager = nullptr;
    GraphicsManager* m_graphicsManager = nullptr;
    PipelineManager* m_pipelineManager = nullptr;
	EngineManager* m_engineManager = nullptr;
	GameEngine* m_gameEngine = nullptr;  // GameEngine�̃|�C���^
	WindowManager* m_windowManager = nullptr;  // WindowManager�̃|�C���^
    // ����Manager�̃|�C���^
};
