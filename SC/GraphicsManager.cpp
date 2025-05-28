#include "GraphicsManager.h"
#include <cassert>

// �E�B���h�E�n���h�����O������󂯎��A�ێ�����
void GraphicsManager::SetHWND(HWND hwnd) {
    m_hWnd = hwnd;
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

    // �R�}���h���X�g�ƃA���P�[�^���ď����i���̃t���[���̂��߂Ɂj
    m_deviceManager.ResetCommandList();
}

// �I�����̉������
void GraphicsManager::Cleanup() {
    // GPU����������܂Ńt�F���X�őҋ@�iCPU��GPU�̓����j
    m_deviceManager.WaitForGPU();
    m_renderTargetManager.Cleanup();
    m_deviceManager.Cleanup(); // �� SwapChainManager �͎����ŉ�������̂ŏȗ���
}

// �O������R�}���h���X�g���g�������Ƃ��̎擾�֐�
ID3D12GraphicsCommandList* GraphicsManager::GetCommandList() {
    return m_deviceManager.GetCommandList();
}
