#include "Input.hpp"
using namespace FooGE;


Input* Input::m_Input = new Input();

Input& Input::Instance(){
    return *m_Input;
}

vec2<UINT> Input::GetMousePos(){
    return m_MousePos;
}
void Input::SetMousePos(UINT x, UINT y){
    m_MousePos.x = x;
    m_MousePos.y = y;
}



/*
error
*/
bool Input::GetMouseDown(UINT m){
    return mouseDown[m];
}
bool Input::GetKeyDown(UINT k){
    return keyDown[k];
}
void Input::SetMouseDown(UINT m){
    mouseDown[m] = true;
}
void Input::SetMouseUp(UINT m){
    mouseDown[m] = false;
}
void Input::SetKeyDown(UINT k){
    keyDown[k] = true;
}
void Input::SetKeyUp(UINT k){
    keyDown[k] = false;
}