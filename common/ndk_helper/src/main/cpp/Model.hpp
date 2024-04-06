#ifndef MESHROTATOR_MODEL_HPP
#define MESHROTATOR_MODEL_HPP

#include "Mesh.hpp"
#include "Shader.hpp"

namespace ndk_helper {
    namespace mdl {
        using Shader = shdr::Shader;

        class Model {
        public:
            Model();
            Model(
                const mesh::Mesh& mesh,
                const glm::vec3& position = {0.0f, 0.0f, 0.0f},
                const glm::vec3& scale = {1.0f, 1.0f, 1.0f}
            );
            virtual ~Model() = default;

            virtual void addMesh(mesh::Mesh& mesh);
            virtual std::vector<mesh::Mesh> getMeshes() const;
            virtual void addTexture(mesh::Texture texture);
            virtual void draw(Shader& shader) const;
            virtual void setPosition(const glm::vec3& position);
            virtual glm::vec3 getPosition() const;
            virtual void setScale(const glm::vec3& scale);
            virtual glm::vec3 getScale() const;

        private:
            std::vector<mesh::Mesh> meshes_;
            std::vector<mesh::Texture> textures_;
            glm::vec3 position_;
            glm::vec3 scale_;
        };
    }
}

#endif //MESHROTATOR_MODEL_HPP