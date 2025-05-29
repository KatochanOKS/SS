#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "Mesh.h"
#include <memory>  
class MeshManager {
public:
    void Initialize(ID3D12Device* device);
    std::shared_ptr<Mesh> CreateTriangleMesh();
    // ç°å„ÅACreateCubeMesh()Ç»Ç«Ç‡í«â¡ó\íË

private:
    ID3D12Device* m_device = nullptr;
};
