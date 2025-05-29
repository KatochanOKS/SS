#include "GameEngine.h"
#include "MeshManager.h"
#include "Mesh.h"
#include "GraphicsManager.h"
#include "PipelineManager.h"
#include "EngineManager.h"
void GameEngine::Initialize() {
    // MeshManager, PipelineManager, GraphicsManagerの参照を取得しておく
    auto* meshManager = EngineManager::GetInstance().GetMeshManager();
    auto* pipelineManager = EngineManager::GetInstance().GetPipelineManager();
    auto* graphicsManager = EngineManager::GetInstance().GetGraphicsManager();

    m_triangleMesh = meshManager->CreateTriangleMesh();
    m_pipelineManager = pipelineManager;
    m_graphicsManager = graphicsManager;
}

void GameEngine::Draw() {
    // 三角形描画
    m_graphicsManager->DrawTriangle(m_triangleMesh, m_pipelineManager);
}


void GameEngine::Update() {
    // ゲームロジック（今回は空）
}
