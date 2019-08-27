#pragma once
#include "Widget.hpp"
#include "../FooCore/Input.hpp"
#include "../FooCore/MTimer.hpp"
#include <vector>
#include <d2d1.h>
#include <dwrite.h>

/*
轮循 currentCanvas上面的元素
根据鼠标状态来出发ui元素的事件
*/

namespace FooGE{
    namespace Foo2D{
        class Canvas{
        public:
            Canvas();
            ~Canvas();

            void Render(ID2D1HwndRenderTarget*	pMainRT);
            void Update(MTimer& timer);
            void AddWidget(Widget* w);   // 内存管理
            void EnableScaleWithScreenSize();
            void DisableScaleWithScreenSize();

            std::vector<Widget*>& GetRenderQueue();
        private:
            std::vector<Widget*> uiElements;
            bool ScaleWithScreenSize;
        };
    }
}
