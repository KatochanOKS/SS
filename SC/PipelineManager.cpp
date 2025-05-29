#include "PipelineManager.h"
#include <cassert>
#include "d3dx12.h"
#include "BIN_FILE12.h"
using Microsoft::WRL::ComPtr;
void PipelineManager::Initialize(ID3D12Device* device) {
    m_device = device;

    //ディスクリプタレンジ。ディスクリプタヒープとシェーダを紐づける役割をもつ。
    D3D12_DESCRIPTOR_RANGE  range[1] = {};
    UINT b0 = 0;
    range[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
    range[0].BaseShaderRegister = b0;
    range[0].NumDescriptors = 1;
    range[0].RegisterSpace = 0;
    range[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    //ルートパラメタをディスクリプタテーブルとして使用
    D3D12_ROOT_PARAMETER rootParam[1] = {};
    rootParam[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParam[0].DescriptorTable.pDescriptorRanges = range;
    rootParam[0].DescriptorTable.NumDescriptorRanges = _countof(range);
    rootParam[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    //ルートシグニチャの記述
    D3D12_ROOT_SIGNATURE_DESC desc = {};
    desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    desc.pParameters = rootParam;
    desc.NumParameters = _countof(rootParam);
    ComPtr<ID3DBlob> blob;
    ComPtr<ID3DBlob> errorBlob;
    HRESULT hr = D3D12SerializeRootSignature(
        &desc, D3D_ROOT_SIGNATURE_VERSION_1, &blob, &errorBlob
    );
    assert(SUCCEEDED(hr));

    // デバイスからルートシグネチャ作成
    hr = m_device->CreateRootSignature(
        0, blob->GetBufferPointer(), blob->GetBufferSize(),
        IID_PPV_ARGS(&m_rootSignature)
    );
    assert(SUCCEEDED(hr));
    // パイプライン作成
    CreateBasicPipeline();
}


void PipelineManager::CreateBasicPipeline() {
    BIN_FILE12 vs("asset/VertexShader.cso");
    assert(vs.succeeded());
    BIN_FILE12 ps("asset/PixelShader.cso");
    assert(ps.succeeded());

    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };

    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.InputLayout = { inputLayout, _countof(inputLayout) };
    psoDesc.pRootSignature = m_rootSignature.Get();
    psoDesc.VS = { vs.code(), vs.size() };
    psoDesc.PS = { ps.code(), ps.size() };
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;

    ComPtr<ID3D12PipelineState> pipeline;
    HRESULT hr = m_device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipeline));
    assert(SUCCEEDED(hr));

    m_pipelineStates["Basic"] = pipeline;
}

ID3D12PipelineState* PipelineManager::GetPipeline(const std::string& name) {
    return m_pipelineStates[name].Get();
}

ID3D12RootSignature* PipelineManager::GetRootSignature() {
    return m_rootSignature.Get();
}
