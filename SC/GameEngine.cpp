#include "GameEngine.h"
#include "MeshManager.h"
#include "Mesh.h"
#include "GraphicsManager.h"
#include "PipelineManager.h"
#include "EngineManager.h"
void GameEngine::Initialize() {
    // MeshManager, PipelineManager, GraphicsManager�̎Q�Ƃ��擾���Ă���
    auto* meshManager = EngineManager::GetInstance().GetMeshManager();
    auto* pipelineManager = EngineManager::GetInstance().GetPipelineManager();
    auto* graphicsManager = EngineManager::GetInstance().GetGraphicsManager();

    m_triangleMesh = meshManager->CreateTriangleMesh();
    m_pipelineManager = pipelineManager;
    m_graphicsManager = graphicsManager;
}

void GameEngine::Draw() {
    // �O�p�`�`��
    m_graphicsManager->DrawTriangle(m_triangleMesh, m_pipelineManager);
}


void GameEngine::Update() {
    // �Q�[�����W�b�N�i����͋�j
}
