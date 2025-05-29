#include "MeshManager.h"
#include "Mesh.h"
#include <memory>        // std::shared_ptr, std::make_shared
#include <cassert>       // assert
#include <cstring>       // memcpy
#include <d3d12.h>
#include <wrl.h>

void MeshManager::Initialize(ID3D12Device* device) {
    m_device = device;
}

std::shared_ptr<Mesh> MeshManager::CreateTriangleMesh() {
    // 三角形の頂点データ
    struct Vertex { float x, y, z; };
    Vertex vertices[] = {
        { -0.5f, -0.5f, 0.0f },
        {  0.0f,  0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f }
    };

    auto mesh = std::make_shared<Mesh>();
    mesh->VertexCount = 3;

    // バッファ生成…
    D3D12_HEAP_PROPERTIES heapProps = {};
    heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;

    D3D12_RESOURCE_DESC resDesc = {};
    resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resDesc.Alignment = 0;
    resDesc.Width = sizeof(vertices);
    resDesc.Height = 1;
    resDesc.DepthOrArraySize = 1;
    resDesc.MipLevels = 1;
    resDesc.Format = DXGI_FORMAT_UNKNOWN;
    resDesc.SampleDesc.Count = 1;
    resDesc.SampleDesc.Quality = 0;
    resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;


    HRESULT hr = m_device->CreateCommittedResource(
        &heapProps, D3D12_HEAP_FLAG_NONE, &resDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
        IID_PPV_ARGS(&mesh->VertexBuffer)
    );
    assert(SUCCEEDED(hr));

    // データコピー
    void* mapped = nullptr;
    mesh->VertexBuffer->Map(0, nullptr, &mapped);
    memcpy(mapped, vertices, sizeof(vertices));
    mesh->VertexBuffer->Unmap(0, nullptr);

    // ビューセット
    mesh->VertexBufferView.BufferLocation = mesh->VertexBuffer->GetGPUVirtualAddress();
    mesh->VertexBufferView.SizeInBytes = sizeof(vertices);
    mesh->VertexBufferView.StrideInBytes = sizeof(Vertex);

    return mesh;
}
