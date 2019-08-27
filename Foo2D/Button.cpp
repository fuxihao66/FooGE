#include "Button.hpp"

using namespace FooGE::Foo2D;


Button::Button(std::string idle, std::string hover, std::string click){
    idleImg = idle;
    hoverImg = hover;
    clickImg = click;
}

void Button::onHover(){
    Widget::onHover();
    hovered = true;
}

void Button::onClick(){
    Widget::onClick();
    pressed = true;
}

void Button::onRelease(){
    Widget::onRelease();

}

void Button::onDisabled(){
    Widget::onDisabled();
    disabled = true;
    activated = false;
}

void Button::onActivated(){
    Widget::onActivated();
    activated = true;
    disabled = false;
}   

void Button::Render(ID2D1HwndRenderTarget* pRenderTarget){
    pRenderTarget->DrawBitmap(pCurrentBitmap, drawRect);   
    btnTxt->REnder(pRenderTarget);
}
void Button::Update(){

    /*状态：hover 按下 其他*/
    if (hovered){
        pCurrentBitmap = pHoverBitmap;
    }
    else if (pressed){
        pCurrentBitmap = pClickBitmap;
    }
    else if (disabled){
        pCurrentBitmap = pDisableBitmap;
    }
    else{ // idle
        pCurrentBitmap = pIdleBitmap;
    }
}

void Button::onCreate(){

}