#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <DirectXMath.h>  // ←これ追加！
using namespace DirectX;  // ←XMFLOAT4X4用
struct ConstBufferData {
    XMFLOAT4X4 mat;
};
// --- コンスタントバッファ（CBV）とディスクリプタヒープの管理クラス ---
// ・シェーダ用定数バッファ（matrixなど）を扱う
// ・毎フレーム値を更新し、GPUに渡す役割
class ConstantBufferManager {
public:
   
    // CBVとヒープの初期化（deviceからリソースとディスクリプタヒープを生成）
    void Initialize(ID3D12Device* device, UINT bufferSize = 256);
    // CPU側から定数バッファのメモリ領域にアクセス（値を書き込む用）
    void* Map();
    // GPUが参照するディスクリプタヒープ内のハンドル（バインド時に使用）
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() const;
    // ディスクリプタヒープ自体を取得（SetDescriptorHeaps用）
    ID3D12DescriptorHeap* GetHeap() const { return m_cbvHeap.Get(); }
    // 解放処理
    void Cleanup();

private:
    // コンスタントバッファ本体（マトリクス等のデータを格納するGPUリソース）
    Microsoft::WRL::ComPtr<ID3D12Resource> m_constBuffer;
    // CBV（定数バッファビュー）を置くためのディスクリプタヒープ
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_cbvHeap;
    // マップ済みポインタ（CPUからデータを書き込むためのアドレス）
    void* m_mappedPtr = nullptr;
};
