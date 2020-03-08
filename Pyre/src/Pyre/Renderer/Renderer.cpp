#include "pyrepch.hpp"
#include "Pyre/Renderer/Renderer.hpp"

namespace Pyre {

    OrthographicCamera* Renderer::s_Camera;

    void Renderer::BeginScene(OrthographicCamera* camera) {
        s_Camera = camera;
    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {
        shader->Bind();
        shader->UploadUniformMat4("uViewProj", s_Camera->GetViewProjectionMatrix());
        shader->UploadUniformMat4("uTransform", transform);

        vertexArray->Bind();
        RenderCommand::DrawElement(vertexArray);
    }

}