#ifndef MESH_ROTATOR_CONTROLLER_HPP
#define MESH_ROTATOR_CONTROLLER_HPP

namespace ctrl {
    class Controller {
    public:
        virtual ~Controller() = default;

        virtual void rotate() = 0;
    };
}

#endif //MESH_ROTATOR_CONTROLLER_HPP
