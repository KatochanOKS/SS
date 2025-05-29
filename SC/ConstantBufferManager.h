#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <DirectXMath.h>  // ������ǉ��I
using namespace DirectX;  // ��XMFLOAT4X4�p
struct ConstBufferData {
    XMFLOAT4X4 mat;
};
// --- �R���X�^���g�o�b�t�@�iCBV�j�ƃf�B�X�N���v�^�q�[�v�̊Ǘ��N���X ---
// �E�V�F�[�_�p�萔�o�b�t�@�imatrix�Ȃǁj������
// �E���t���[���l���X�V���AGPU�ɓn������
class ConstantBufferManager {
public:
   
    // CBV�ƃq�[�v�̏������idevice���烊�\�[�X�ƃf�B�X�N���v�^�q�[�v�𐶐��j
    void Initialize(ID3D12Device* device, UINT bufferSize = 256);
    // CPU������萔�o�b�t�@�̃������̈�ɃA�N�Z�X�i�l���������ޗp�j
    void* Map();
    // GPU���Q�Ƃ���f�B�X�N���v�^�q�[�v���̃n���h���i�o�C���h���Ɏg�p�j
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() const;
    // �f�B�X�N���v�^�q�[�v���̂��擾�iSetDescriptorHeaps�p�j
    ID3D12DescriptorHeap* GetHeap() const { return m_cbvHeap.Get(); }
    // �������
    void Cleanup();

private:
    // �R���X�^���g�o�b�t�@�{�́i�}�g���N�X���̃f�[�^���i�[����GPU���\�[�X�j
    Microsoft::WRL::ComPtr<ID3D12Resource> m_constBuffer;
    // CBV�i�萔�o�b�t�@�r���[�j��u�����߂̃f�B�X�N���v�^�q�[�v
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_cbvHeap;
    // �}�b�v�ς݃|�C���^�iCPU����f�[�^���������ނ��߂̃A�h���X�j
    void* m_mappedPtr = nullptr;
};
