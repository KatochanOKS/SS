#pragma once
#include <d3d12.h>
#include <wrl/client.h>
#include <string>
#include <unordered_map>
#include "BIN_FILE12.h"
using Microsoft::WRL::ComPtr;
class PipelineManager {
public:
    void Initialize(ID3D12Device* device);

    ID3D12PipelineState* GetPipeline(const std::string& name);
    ID3D12RootSignature* GetRootSignature();

private:
    void CreateBasicPipeline();

    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12RootSignature> m_rootSignature;
    std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> m_pipelineStates;
};