#include "GraphicsManager.h"
#include <cassert>
#include "Mesh.h"
#include "PipelineManager.h"
#include <memory>       // �O�̂���
#include <d3d12.h>      // DX12�R�}���h

// �E�B���h�E�n���h�����O������󂯎��A�ێ�����
void GraphicsManager::SetHWND(HWND hwnd) {
    m_hWnd = hwnd;
}
ID3D12Device* GraphicsManager::GetDevice() const {
    return m_deviceManager.GetDevice();
}
// �e�`��p�}�l�[�W���[������������i�f�o�C�X �� �X���b�v�`�F�C�� �� �����_�[�^�[�Q�b�g�̏��j
void GraphicsManager::Initialize() {
    // DirectX 12 �̃f�o�C�X�A�R�}���h�����������
    m_deviceManager.Initialize();

    // �E�B���h�E�ɕ`�悷�邽�߂̃X���b�v�`�F�C����������
    m_swapChainManager.Initialize(m_hWnd, m_deviceManager.GetDevice(), m_deviceManager.GetCommandQueue());

    // �o�b�N�o�b�t�@�ɕ`�悷�邽�߂�RTV�i�����_�[�^�[�Q�b�g�r���[�j������
    m_renderTargetManager.Initialize(m_deviceManager.GetDevice(), m_swapChainManager.GetSwapChain());
}

// ���t���[���Ă΂��F�`��̏����iRenderTarget�̐ݒ�ƃN���A�j���s��
void GraphicsManager::BeginFrame() {
    auto* cmdList = m_deviceManager.GetCommandList(); // �R�}���h���X�g�擾
    auto backBufferIndex = m_swapChainManager.GetCurrentBackBufferIndex(); // ���݂̃o�b�N�o�b�t�@�̃C���f�b�N�X

    // �����_�[�^�[�Q�b�g�̐ݒ�ƃN���A
    m_renderTargetManager.BeginRender(cmdList, backBufferIndex);
}

// ���t���[���Ă΂��F�`��̊���������GPU�ւ̎��s�˗����s��
void GraphicsManager::EndFrame() {
    auto* cmdList = m_deviceManager.GetCommandList();
    auto backBufferIndex = m_swapChainManager.GetCurrentBackBufferIndex();

    // �o�b�N�o�b�t�@��`��^�[�Q�b�g����Present��Ԃ֖߂�
    m_renderTargetManager.EndRender(cmdList, backBufferIndex);

    // �R�}���h���X�g�̋L�^���I�����AGPU�Ɏ��s������
    cmdList->Close();
    ID3D12CommandList* lists[] = { cmdList };
    m_deviceManager.GetCommandQueue()->ExecuteCommandLists(1, lists);

    

    // ��ʂɕ\���i�o�b�N�o�b�t�@���t�����g�o�b�t�@�ɐ؂�ւ���j
    m_swapChainManager.Present();
    // GPU����������܂Ńt�F���X�őҋ@�iCPU��GPU�̓����j
    m_deviceManager.WaitForGPU();
    // �R�}���h���X�g�ƃA���P�[�^���ď����i���̃t���[���̂��߂Ɂj
    m_deviceManager.ResetCommandList();
}

// �l�p�`�i�C���f�b�N�X�o�b�t�@����j�p�̕`��֐�
void GraphicsManager::DrawQuad(std::shared_ptr<Mesh> quadMesh, PipelineManager* pipelineManager) {
    auto* cmdList = m_deviceManager.GetCommandList();

    // �p�C�v���C�������[�g�V�O�l�`���̃Z�b�g
    cmdList->SetPipelineState(pipelineManager->GetPipeline("Basic"));
    cmdList->SetGraphicsRootSignature(pipelineManager->GetRootSignature());

    // �r���[�|�[�g�E�V�U�[��`�i�����ł͉�ʑS�̂Ɖ���j
    D3D12_VIEWPORT viewport = { 0, 0, (float)m_width, (float)m_height, 0, 1 };
    D3D12_RECT scissorRect = { 0, 0, (LONG)m_width, (LONG)m_height };
    cmdList->RSSetViewports(1, &viewport);
    cmdList->RSSetScissorRects(1, &scissorRect);

    // �o�b�t�@�Z�b�g
    cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    cmdList->IASetVertexBuffers(0, 1, &quadMesh->VertexBufferView);

    // �C���f�b�N�X�o�b�t�@������ꍇ�͎l�p�`�Ƃ��ĕ`��
    if (quadMesh->IndexBuffer && quadMesh->IndexCount > 0) {
        cmdList->IASetIndexBuffer(&quadMesh->IndexBufferView);
        cmdList->DrawIndexedInstanced(quadMesh->IndexCount, 1, 0, 0, 0);
    }
    else {
        // ������C���f�b�N�X���Ȃ��ꍇ�͒ʏ�`��
        cmdList->DrawInstanced(quadMesh->VertexCount, 1, 0, 0);
    }
}


// �I�����̉������
void GraphicsManager::Cleanup() {

    m_renderTargetManager.Cleanup();
    m_deviceManager.Cleanup(); // �� SwapChainManager �͎����ŉ�������̂ŏȗ���
}

// �O������R�}���h���X�g���g�������Ƃ��̎擾�֐�
ID3D12GraphicsCommandList* GraphicsManager::GetCommandList() {
    return m_deviceManager.GetCommandList();
}

