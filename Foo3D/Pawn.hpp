#include "Actor.hpp"
#include "Controller.hpp"
/*
可操控对象
*/
class Pawn:public Actor{
private:
    Controller * playerController;
    
};