#pragma once
#include <d3d12.h>
#include <wrl.h>
using Microsoft::WRL::ComPtr;
class Mesh {
public:
   ComPtr<ID3D12Resource> VertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
    UINT VertexCount = 0;
    // ����A�C���f�b�N�X�o�b�t�@��}�e���A���Ȃǂ������ɒǉ��\��
};
