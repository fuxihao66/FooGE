#include "Actor.hpp"

class CameraActor:public Actor{

private:
    bool mainCamera = false;
public:
    void setToMain();
    bool isMain();

    CameraActor();
    ~CameraActor();
};
