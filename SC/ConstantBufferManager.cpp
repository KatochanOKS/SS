#include "ConstantBufferManager.h"
#include <cassert>

// --------- �������i���\�[�X�ƃq�[�v���쐬�E�}�b�s���O����j -------------
void ConstantBufferManager::Initialize(ID3D12Device* device, UINT bufferSize) {
    // 1. CBV���\�[�X�i�萔�o�b�t�@�{�́j���쐬
    D3D12_HEAP_PROPERTIES prop = {};
    prop.Type = D3D12_HEAP_TYPE_UPLOAD;  // CPU�������ݗp�A�b�v���[�h�q�[�v
    D3D12_RESOURCE_DESC desc = {};
    desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Width = bufferSize;  // 256�o�C�g�A���C���K�{
    desc.Height = 1;
    desc.DepthOrArraySize = 1;
    desc.MipLevels = 1;
    desc.Format = DXGI_FORMAT_UNKNOWN;
    desc.SampleDesc.Count = 1;
    desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    desc.Flags = D3D12_RESOURCE_FLAG_NONE;

    HRESULT hr = device->CreateCommittedResource(
        &prop, D3D12_HEAP_FLAG_NONE, &desc,
        D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
        IID_PPV_ARGS(&m_constBuffer)
    );
    assert(SUCCEEDED(hr)); // �쐬���s�̓v���O������~

    // 2. �o�b�t�@��CPU������}�b�v���ď������݂ł���悤�ɂ���
    hr = m_constBuffer->Map(0, nullptr, &m_mappedPtr);
    assert(SUCCEEDED(hr)); // ���s�Ȃ�v���O������~

    // 3. �f�B�X�N���v�^�q�[�v�iCBV�r���[��u���ꏊ�j���쐬
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    heapDesc.NumDescriptors = 1; // �����CBV�ЂƂ�
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // �V�F�[�_����Q�Ɖ�
    hr = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_cbvHeap));
    assert(SUCCEEDED(hr));

    // 4. �萔�o�b�t�@�r���[�iCBV�j�̍쐬
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation = m_constBuffer->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes = bufferSize; // 256�o�C�g�A���C���K�{
    // �쐬�����f�B�X�N���v�^�q�[�v�̐擪��CBV���쐬
    device->CreateConstantBufferView(&cbvDesc, m_cbvHeap->GetCPUDescriptorHandleForHeapStart());
}

// ------- �������ݗp�|�C���^�擾�imat�X�V�ȂǂɎg���j ----------
void* ConstantBufferManager::Map() {
    return m_mappedPtr;
}

// ------- �f�B�X�N���v�^�q�[�v��GPU�n���h���擾�i���[�g�V�O�l�`���ɃZ�b�g�p�j -------
D3D12_GPU_DESCRIPTOR_HANDLE ConstantBufferManager::GetGPUHandle() const {
    return m_cbvHeap->GetGPUDescriptorHandleForHeapStart();
}

// ------- ��������i���\�[�X�ƃq�[�v�̊J�����A���}�b�v�j -------
void ConstantBufferManager::Cleanup() {
    if (m_constBuffer) {
        m_constBuffer->Unmap(0, nullptr);  // �}�b�v����
        m_constBuffer.Reset();
    }
    m_cbvHeap.Reset();
    m_mappedPtr = nullptr;
}
