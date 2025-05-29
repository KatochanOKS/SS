#include "GameEngine.h"
#include "MeshManager.h"
#include "Mesh.h"
#include "GraphicsManager.h"
#include "PipelineManager.h"
#include "EngineManager.h"
#include"ConstantBufferManager.h"
#include <DirectXMath.h>

using namespace DirectX;
void GameEngine::Initialize() {
    // MeshManager, PipelineManager, GraphicsManagerの参照を取得しておく
    auto* meshManager = EngineManager::GetInstance().GetMeshManager();
    auto* pipelineManager = EngineManager::GetInstance().GetPipelineManager();
    auto* graphicsManager = EngineManager::GetInstance().GetGraphicsManager();
	auto* constantBufferManager = EngineManager::GetInstance().GetConstantBufferManager();
    m_quadMesh = meshManager->CreateQuadMesh();
    m_pipelineManager = pipelineManager;
    m_graphicsManager = graphicsManager;
	m_constantBufferManager = constantBufferManager;
}

void GameEngine::Draw() {
    // 三角形描画
   m_graphicsManager->DrawQuad(m_quadMesh, m_pipelineManager, m_constantBufferManager);

}


void GameEngine::Update() {
    static float radian = 0;
    radian += 0.0f;
    float Aspect = 1280.0f / 720.0f; 

    XMMATRIX world = XMMatrixRotationY();  // Y軸回転のみ

    // ビューは正面固定
    XMVECTOR eye = { 0, 0, -2.0f };     // カメラ位置
    XMVECTOR focus = { 0, 0, 0 };       // 注視点（原点）
    XMVECTOR up = { 0, 1, 0 };          // 上方向
    XMMATRIX view = XMMatrixLookAtLH(eye, focus, up);


    // プロジェクションも通常通り
    XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, Aspect, 1.0f, 10.0f);

    // 定数バッファデータ
    ConstBufferData cbData;
    XMMATRIX mvp = world * view * proj;
    XMStoreFloat4x4(&cbData.mat, XMMatrixTranspose(mvp));

    // 書き込み
    auto* p = reinterpret_cast<ConstBufferData*>(m_constantBufferManager->Map());
    *p = cbData;


}
