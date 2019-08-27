#include "BaseObject.hpp"


class Actor : public BaseObject{
public:
    Actor();
    ~Actor();

    vec3<float> Transform;

};