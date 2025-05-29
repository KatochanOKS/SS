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

// �l�p�`���b�V������
std::shared_ptr<Mesh> MeshManager::CreateQuadMesh() {
    // �l�p�`�̒��_�f�[�^�iXY���ʏ�AZ=0�j
    struct Vertex { float x, y, z; };
    Vertex vertices[] = {
        { -0.5f, -0.5f, 0.0f },  // ����
        { -0.5f,  0.5f, 0.0f },  // ����
        {  0.5f, -0.5f, 0.0f },  // �E��
        {  0.5f,  0.5f, 0.0f },  // �E��
    };
    // �C���f�b�N�X�z��i2�O�p�`���j
    unsigned short indices[] = {
        0, 1, 2,    // �����O�p�`
        2, 1, 3     // �E��O�p�`
    };

    auto mesh = std::make_shared<Mesh>();
    mesh->VertexCount = 4;
    mesh->IndexCount = 6;

    // --- ���_�o�b�t�@�쐬 ---
    {
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
        resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

        HRESULT hr = m_device->CreateCommittedResource(
            &heapProps, D3D12_HEAP_FLAG_NONE, &resDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
            IID_PPV_ARGS(&mesh->VertexBuffer)
        );
        assert(SUCCEEDED(hr));

        void* mapped = nullptr;
        mesh->VertexBuffer->Map(0, nullptr, &mapped);
        memcpy(mapped, vertices, sizeof(vertices));
        mesh->VertexBuffer->Unmap(0, nullptr);

        mesh->VertexBufferView.BufferLocation = mesh->VertexBuffer->GetGPUVirtualAddress();
        mesh->VertexBufferView.SizeInBytes = sizeof(vertices);
        mesh->VertexBufferView.StrideInBytes = sizeof(Vertex);
    }

    // --- �C���f�b�N�X�o�b�t�@�쐬 ---
    {
        D3D12_HEAP_PROPERTIES heapProps = {};
        heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
        D3D12_RESOURCE_DESC resDesc = {};
        resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        resDesc.Alignment = 0;
        resDesc.Width = sizeof(indices);
        resDesc.Height = 1;
        resDesc.DepthOrArraySize = 1;
        resDesc.MipLevels = 1;
        resDesc.Format = DXGI_FORMAT_UNKNOWN;
        resDesc.SampleDesc.Count = 1;
        resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

        HRESULT hr = m_device->CreateCommittedResource(
            &heapProps, D3D12_HEAP_FLAG_NONE, &resDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
            IID_PPV_ARGS(&mesh->IndexBuffer)
        );
        assert(SUCCEEDED(hr));

        void* mapped = nullptr;
        mesh->IndexBuffer->Map(0, nullptr, &mapped);
        memcpy(mapped, indices, sizeof(indices));
        mesh->IndexBuffer->Unmap(0, nullptr);

        mesh->IndexBufferView.BufferLocation = mesh->IndexBuffer->GetGPUVirtualAddress();
        mesh->IndexBufferView.SizeInBytes = sizeof(indices);
        mesh->IndexBufferView.Format = DXGI_FORMAT_R16_UINT;
    }

    return mesh;
}

