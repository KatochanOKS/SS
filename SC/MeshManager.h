#pragma once
#include <d3d12.h>
#include <memory>
#include "Mesh.h"

class MeshManager {
public:
    void Initialize(ID3D12Device* device); // デバイス保持

    // 四角形メッシュを生成
    std::shared_ptr<Mesh> CreateQuadMesh();

private:
    ID3D12Device* m_device = nullptr;
};
