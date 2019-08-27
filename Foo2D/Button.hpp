#pragma once
#include "Widget.hpp"
#include "Text.hpp"

#include <string>


namespace FooGE{
    namespace Foo2D{
        class Button: public Widget{
        public:
            Button();
            Button(std::string idle, std::string hover, std::string click);

            virtual void onHover();
            virtual void onLeave();
            virtual void onClick();
            virtual void onPress();
            virtual void onRelease();
            virtual void onDisabled();
            virtual void onActivated();

            virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
            virtual void onCreate();  // 加载资源
            virtual void Update();
            virtual void UpdateAnimation(const MTimer& gt);
        private:
            Text* btnTxt;

            

            std::string idleImg;
            std::string hoverImg;
            std::string clickImg;
            std::string disableImg;

            ID2D1Bitmap* pIdleBitmap = nullptr;
            ID2D1Bitmap* pHoverBitmap = nullptr;
            ID2D1Bitmap* pClickBitmap = nullptr;
            ID2D1Bitmap* pDisableBitmap = nullptr;

            ID2D1Bitmap* pCurrentBitmap = nullptr;

            /*关键帧动画关键变量*/
            float Scale = 1;
            vec2<float> Translate;
            float Rotate = 0;
        };
    }
}
