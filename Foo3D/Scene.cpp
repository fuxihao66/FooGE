#include "Scene.hpp"

using namespace FooGE;


void Scene::Update(){
    for each in actorList{
        each.Update();
    }
}
void Scene::AddActor(const Actor& obj){

}