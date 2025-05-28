#pragma once
#include <memory>

class Mesh;
class PipelineManager;
class GraphicsManager;

class GameEngine {
public:
    // 初期化用
    void Initialize();

    // 毎フレーム呼ばれる
    void Update();
    void Draw();

private:
    std::shared_ptr<Mesh> m_triangleMesh;        // 三角形Mesh
    GraphicsManager* m_graphicsManager = nullptr;
    PipelineManager* m_pipelineManager = nullptr;
};
