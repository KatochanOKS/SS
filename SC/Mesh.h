#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <memory>

class Mesh {
public:
    Microsoft::WRL::ComPtr<ID3D12Resource> VertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
    Microsoft::WRL::ComPtr<ID3D12Resource> IndexBuffer;
    D3D12_INDEX_BUFFER_VIEW IndexBufferView;
    UINT VertexCount = 0;
    UINT IndexCount = 0;
};
