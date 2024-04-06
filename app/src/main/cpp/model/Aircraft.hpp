#ifndef MESH_ROTATOR_AIRCRAFT_HPP
#define MESH_ROTATOR_AIRCRAFT_HPP

#include "NDKHelper.hpp"
#include "../Controller.hpp"
#include <map>

namespace model {
    using AssetManager = ndk_helper::assetmgr::AssetManager;
    using ModelManager = ndk_helper::mdlmgr::ModelManager;
    using Model = ndk_helper::mdl::Model;
    using Shader = ndk_helper::shdr::Shader;

    class Aircraft : public Model, public ctrl::Controller {
    public:
        Aircraft(AAssetManager* aAssetManager);
        ~Aircraft() override = default;

        void draw(Shader& shader) const override;
        void setPosition(const glm::vec3& position) override;
        void setScale(const glm::vec3& scale) override;
        void rotate() override;

    private:
        AAssetManager* aAssetManager_;

        Model fuselage_;
        Model aileronLeft_;
        Model aileronRight_;
        Model elevator_;

        std::map<ndk_helper::mesh::TextureType, std::string> textures_;

        void initTextures();
        void initFuselage();
        void initAilerons();
        void initElevator();
    };
}

#endif //MESH_ROTATOR_AIRCRAFT_HPP
