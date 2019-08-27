#include "Widget.hpp"

using namespace FooGE::Foo2D;

void Widget::Click(){
    onClick();
}
void Widget::Press(){
    onPress();
}
void Widget::Release(){
    onRelease();
}
void Widget::Hover(){
    onHover();
}
void Widget::Leave(){
    onLeave();
}

void Widget::Activate(){
    onActivate(); 
}  
void Widget::Disable(){
    onDisable();
}

bool Widget::ifCursorInBox(const vec2<UINT>& cursorPos){
    if (cursorPos.x < hitBox.x)
        return false;
    else if (cursorPos.x > hitBox.y)
        return false;
    else if (cursorPos.y < hitBox.z)
        return false;
    else if (cursorPos.y > hitBox.w)
        return false;
    else
        return true;
}

//void Widget::AddAnimator(const Animator& ani){
//
//}
//
//void Widget::UpdateAnimation(const Timer& gt){
//
//}

void Widget::setClickCallback(const Callback& cb){
    clickCB = cb;
}
void Widget::setPressCallback(const Callback& cb){
    pressCB = cb;
}
void Widget::setReleaseCallback(const Callback& cb){
    releaseCB = cb;
}
void Widget::setHoverCallback(const Callback& cb){
    hoverCB = cb;
}
void Widget::setLeaveCallback(const Callback& cb){
    leaveCB = cb;
}

bool Widget::ifClicked(){
    return clicked;
}
bool Widget::ifPressed(){
    return pressed;
}
bool Widget::ifReleased(){
    return released;
}
bool Widget::ifHovered(){
    return hovered;
}
bool Widget::ifLeaved(){
    return leaved;
}
bool Widget::ifActivated(){
    return activated;
}
bool Widget::ifDisabled(){
    return disabled;
}


void Widget::onActivate(){
    activateCB();
}

void Widget::onDisable(){
    disableCB();
}

void Widget::onHover(){
    hovered = true;
    hoverCB();
}
void Widget::onLeave(){
    leaved = true;
    pressed = false;
    leaveCB();
}
void Widget::onClick(){
    clickCB();       
}    // 按下后放开

void Widget::onPress(){
    pressCB();
}
            
void Widget::onRelease(){
    releaseCB();
}