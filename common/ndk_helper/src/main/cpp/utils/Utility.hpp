#ifndef MESHROTATOR_UTILITY_HPP
#define MESHROTATOR_UTILITY_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#include <memory>

namespace ndk_helper {
    namespace utils {
        constexpr float FOV_ANGLE = 45.0f;
        constexpr float Z_NEAR = 0.1f;
        constexpr float Z_FAR = 50.0f;

        glm::mat4 get_projection_matrix(const float width, const float height) {
            auto aspect = width / height;

            return glm::perspective(
                glm::radians(FOV_ANGLE),
                aspect,
                Z_NEAR,
                Z_FAR
            );;
        }

        glm::vec3 get_light_dir() {
            return glm::vec3{0.0f, 1.0f, -2.0f};
        }

        glm::vec3 get_light_color() {
            return glm::vec3{0.5f, 0.5f, 0.5f};
        }

        float get_aspect_ratio(const float width, const float height) {
            return width / height;
        }

        template<typename T, typename ... Args>
        std::unique_ptr<T> make_unique(Args&& ... args) {
            return std::unique_ptr<T>{new T{args...}};
        }
    }
}

#endif //MESHROTATOR_UTILITY_HPP