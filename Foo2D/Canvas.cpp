#include "Canvas.hpp"

using namespace FooGE::Foo2D;

void Canvas::Update(MTimer& timer){

	vec2<UINT> cursorPos = Input::Instance().GetMousePos();
    bool MouseDown = Input::Instance().GetMouseDown(0);

    // for each in widgetList{
    //     each.UpdateAnimation(Timer& timer);
        
    // }
    // 鼠标状态
    for (auto item : uiElements){
        if (item->ifCursorInBox(cursorPos)){
            item->Hover();
            if (MouseDown){
				item->Press();
            }
            if (!MouseDown && item->ifPressed()){
				item->Click();
				item->Release();
            }
        }
        if (!item->ifCursorInBox(cursorPos)){
            if (item->ifHovered()){
				item->Leave();
            }
                
        }
		item->Update();
    }
}

std::vector<Widget*>& Canvas::GetRenderQueue(){
    return uiElements;
}

void Canvas::Render(ID2D1HwndRenderTarget*	pMainRT){
    for (Widget* each : uiElements){
        each->Render(pMainRT);
    }
}

void Canvas::AddWidget(Widget* w){  // 内存管理
    uiElements.push_back(w);
}
void Canvas::EnableScaleWithScreenSize(){
    ScaleWithScreenSize = true;
}
void Canvas::DisableScaleWithScreenSize(){
    ScaleWithScreenSize = false;
}