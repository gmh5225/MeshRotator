#include "Aircraft.hpp"
#include <jni.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/euler_angles.hpp>

constexpr float TO_RADIANS = M_PI / 180.0f;

// Angle constants
constexpr float MAX_PITCH = 25.0f * TO_RADIANS;
constexpr float MAX_ROLL = 75.0f * TO_RADIANS;
constexpr float MAX_AILERON_PITCH = 35.0f * TO_RADIANS;
constexpr float MAX_ELEVATOR_PITCH = 45.0f * TO_RADIANS;

// Axis
static const glm::vec3 WORLD_Z = glm::vec3(0.0f, 0.0f, 1.0f);

glm::quat fuselageQuat = glm::angleAxis(0.0f, WORLD_Z);
glm::quat aileronLeftQuat = glm::angleAxis(0.0f, WORLD_Z);
glm::quat aileronRightQuat = -aileronLeftQuat;
glm::quat elevatorQuat = glm::angleAxis(0.0f, WORLD_Z);

model::Aircraft::Aircraft(AAssetManager* aAssetManager) : Model(), aAssetManager_{aAssetManager} {
    initTextures();
    initFuselage();
    initAilerons();
    initElevator();
}

void model::Aircraft::draw(Shader& shader) const {
    glm::mat4 modelMat =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3{
                getPosition().x,
                getPosition().y,
                getPosition().z
            }
        )  * glm::mat4_cast(fuselageQuat)
                * glm::scale(glm::mat4(1.0f), getScale());
    shader.activate();
    shader.set_mat4("MODEL", modelMat);
    fuselage_.draw(shader);

    modelMat =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3{
                getPosition().x,
                getPosition().y,
                getPosition().z
            }
        ) * glm::mat4_cast(aileronLeftQuat)
                * glm::scale(glm::mat4(1.0f), getScale());
    shader.set_mat4("MODEL", modelMat);
    aileronLeft_.draw(shader);

    modelMat =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3{
                getPosition().x,
                getPosition().y,
                getPosition().z
            }
        ) * glm::mat4_cast(aileronRightQuat)
                * glm::scale(glm::mat4(1.0f), getScale());
    shader.set_mat4("MODEL", modelMat);
    aileronRight_.draw(shader);

    modelMat =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3{
                getPosition().x,
                getPosition().y,
                getPosition().z
            }
        ) * glm::mat4_cast(elevatorQuat)
                * glm::scale(glm::mat4(1.0f), getScale());
    shader.set_mat4("MODEL", modelMat);
    elevator_.draw(shader);
}

void model::Aircraft::setPosition(const glm::vec3& position) {
    Model::setPosition(position);
    fuselage_.setPosition(position);
    aileronLeft_.setPosition(position);
    aileronRight_.setPosition(position);
    elevator_.setPosition(position);
}

void model::Aircraft::setScale(const glm::vec3& scale) {
    Model::setScale(scale);
    fuselage_.setScale(scale);
    aileronLeft_.setScale(scale);
    aileronRight_.setScale(scale);
    elevator_.setScale(scale);
}

void model::Aircraft::rotate() {

}

void model::Aircraft::initTextures() {
    textures_ = std::map<ndk_helper::mesh::TextureType, std::string>{
        {ndk_helper::mesh::TextureType::DIFFUSE, "model/aircraft/piper_diffuse.jpg"},
        {ndk_helper::mesh::TextureType::NORMAL, "model/aircraft/piper_diffuse.jpg"}
    };
}

void model::Aircraft::initFuselage() {
    ModelManager& modelManager = ModelManager::instance(AssetManager::instance(aAssetManager_));
    fuselage_ = modelManager.getModelFromPath("model/aircraft/fuselage.obj");
    modelManager.applyTextures(fuselage_, textures_);
}

void model::Aircraft::initAilerons() {
    ModelManager& modelManager = ModelManager::instance(AssetManager::instance(aAssetManager_));
    aileronLeft_ = modelManager.getModelFromPath("model/aircraft/aileronL.obj");
    aileronRight_ = modelManager.getModelFromPath("model/aircraft/aileronR.obj");
    modelManager.applyTextures(aileronLeft_, textures_);
    modelManager.applyTextures(aileronRight_, textures_);
}

void model::Aircraft::initElevator() {
    ModelManager& modelManager = ModelManager::instance(AssetManager::instance(aAssetManager_));
    elevator_ = modelManager.getModelFromPath("model/aircraft/elevator.obj");
    modelManager.applyTextures(elevator_, textures_);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_mistersomov_meshrotator_MainActivity_updateAircraftAngle(
    JNIEnv *env,
    jobject thiz,
    jfloat x,
    jfloat y
) {
    float pitch = M_PI_2 * y;
    float roll = -M_PI_2 * x;
    float aileronLeftPitch = M_PI_2 * x;
    if (x == 0.0f && y == 0.0f) {
        pitch = 0.0f;
        roll = 0.0f;
        aileronLeftPitch = 0.0f;
    }
    float clampedPitch = glm::clamp(pitch, -MAX_PITCH, MAX_PITCH);
    float clampedRoll = glm::clamp(roll, -MAX_ROLL, MAX_ROLL);
    float clampedAileronLeftPitch = glm::clamp(aileronLeftPitch, -MAX_AILERON_PITCH, MAX_AILERON_PITCH);
    float clampedElevatorPitch = glm::clamp(pitch, -MAX_ELEVATOR_PITCH, MAX_ELEVATOR_PITCH);

    fuselageQuat = glm::quat_cast(glm::yawPitchRoll(0.0f, clampedPitch, clampedRoll));
    aileronLeftQuat =
        fuselageQuat
            * glm::quat_cast(glm::yawPitchRoll(0.0f, clampedAileronLeftPitch, 0.0f));
    aileronRightQuat =
        fuselageQuat
            * glm::quat_cast(glm::yawPitchRoll(0.0f, -clampedAileronLeftPitch, 0.0f));
    elevatorQuat =
        fuselageQuat
            *glm::quat_cast(glm::yawPitchRoll(0.0f, -clampedElevatorPitch, 0.0f));
}
