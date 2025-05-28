#pragma once
#include <memory>

class Mesh;
class PipelineManager;
class GraphicsManager;

class GameEngine {
public:
    // �������p
    void Initialize();

    // ���t���[���Ă΂��
    void Update();
    void Draw();

private:
    std::shared_ptr<Mesh> m_triangleMesh;        // �O�p�`Mesh
    GraphicsManager* m_graphicsManager = nullptr;
    PipelineManager* m_pipelineManager = nullptr;
};
