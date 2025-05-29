#pragma once
#include <d3d12.h>
#include <memory>
#include "Mesh.h"

class MeshManager {
public:
    void Initialize(ID3D12Device* device); // �f�o�C�X�ێ�

    // �l�p�`���b�V���𐶐�
    std::shared_ptr<Mesh> CreateQuadMesh();

private:
    ID3D12Device* m_device = nullptr;
};
