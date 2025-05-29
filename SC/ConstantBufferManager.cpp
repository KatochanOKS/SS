#include "ConstantBufferManager.h"
#include <cassert>

// --------- 初期化（リソースとヒープを作成・マッピングする） -------------
void ConstantBufferManager::Initialize(ID3D12Device* device, UINT bufferSize) {
    // 1. CBVリソース（定数バッファ本体）を作成
    D3D12_HEAP_PROPERTIES prop = {};
    prop.Type = D3D12_HEAP_TYPE_UPLOAD;  // CPU書き込み用アップロードヒープ
    D3D12_RESOURCE_DESC desc = {};
    desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Width = bufferSize;  // 256バイトアライン必須
    desc.Height = 1;
    desc.DepthOrArraySize = 1;
    desc.MipLevels = 1;
    desc.Format = DXGI_FORMAT_UNKNOWN;
    desc.SampleDesc.Count = 1;
    desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    desc.Flags = D3D12_RESOURCE_FLAG_NONE;

    HRESULT hr = device->CreateCommittedResource(
        &prop, D3D12_HEAP_FLAG_NONE, &desc,
        D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
        IID_PPV_ARGS(&m_constBuffer)
    );
    assert(SUCCEEDED(hr)); // 作成失敗はプログラム停止

    // 2. バッファをCPU側からマップして書き込みできるようにする
    hr = m_constBuffer->Map(0, nullptr, &m_mappedPtr);
    assert(SUCCEEDED(hr)); // 失敗ならプログラム停止

    // 3. ディスクリプタヒープ（CBVビューを置く場所）を作成
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    heapDesc.NumDescriptors = 1; // 今回はCBVひとつ
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // シェーダから参照可
    hr = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_cbvHeap));
    assert(SUCCEEDED(hr));

    // 4. 定数バッファビュー（CBV）の作成
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation = m_constBuffer->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes = bufferSize; // 256バイトアライン必須
    // 作成したディスクリプタヒープの先頭にCBVを作成
    device->CreateConstantBufferView(&cbvDesc, m_cbvHeap->GetCPUDescriptorHandleForHeapStart());
}

// ------- 書き込み用ポインタ取得（mat更新などに使う） ----------
void* ConstantBufferManager::Map() {
    return m_mappedPtr;
}

// ------- ディスクリプタヒープのGPUハンドル取得（ルートシグネチャにセット用） -------
D3D12_GPU_DESCRIPTOR_HANDLE ConstantBufferManager::GetGPUHandle() const {
    return m_cbvHeap->GetGPUDescriptorHandleForHeapStart();
}

// ------- 解放処理（リソースとヒープの開放＆アンマップ） -------
void ConstantBufferManager::Cleanup() {
    if (m_constBuffer) {
        m_constBuffer->Unmap(0, nullptr);  // マップ解除
        m_constBuffer.Reset();
    }
    m_cbvHeap.Reset();
    m_mappedPtr = nullptr;
}
