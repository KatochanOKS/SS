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
    // MeshManager, PipelineManager, GraphicsManager�̎Q�Ƃ��擾���Ă���
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
    // �O�p�`�`��
   m_graphicsManager->DrawQuad(m_quadMesh, m_pipelineManager, m_constantBufferManager);

}


void GameEngine::Update() {
    static float radian = 0;
    radian += 0.0f;
    float Aspect = 1280.0f / 720.0f; 

    XMMATRIX world = XMMatrixRotationY();  // Y����]�̂�

    // �r���[�͐��ʌŒ�
    XMVECTOR eye = { 0, 0, -2.0f };     // �J�����ʒu
    XMVECTOR focus = { 0, 0, 0 };       // �����_�i���_�j
    XMVECTOR up = { 0, 1, 0 };          // �����
    XMMATRIX view = XMMatrixLookAtLH(eye, focus, up);


    // �v���W�F�N�V�������ʏ�ʂ�
    XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, Aspect, 1.0f, 10.0f);

    // �萔�o�b�t�@�f�[�^
    ConstBufferData cbData;
    XMMATRIX mvp = world * view * proj;
    XMStoreFloat4x4(&cbData.mat, XMMatrixTranspose(mvp));

    // ��������
    auto* p = reinterpret_cast<ConstBufferData*>(m_constantBufferManager->Map());
    *p = cbData;


}
