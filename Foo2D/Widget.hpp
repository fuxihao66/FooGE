#pragma once
#include<functional>
#include <d2d1.h>
#include <dwrite.h>

#include "../FooMath/utility.hpp"
#include "Animator.hpp"

using Callback = std::function<void()>;
/*
TODO
1. 规定 ss的xy，原点
2. 分辨率自适应   随画面拉伸
*/
namespace FooGE{
    namespace Foo2D{
        class Widget{
        public:
            void setClickCallback(const Callback& cb);
            void setPressCallback(const Callback& cb);
            void setReleaseCallback(const Callback& cb);
            void setHoverCallback(const Callback& cb);
            void setLeaveCallback(const Callback& cb);

            void Click();
            void Press();
            void Release();
            void Hover();
            void Leave();
            void Activate();
            void Disable();

            bool ifClicked();
            bool ifPressed();
            bool ifReleased();
            bool ifHovered();
            bool ifLeaved();
            bool ifActivated();
            bool ifDisabled();

            //void AddAnimator(const Animator& ani);
            //virtual void UpdateAnimation(const Timer& gt);

            bool ifCursorInBox(const vec2<UINT>& cursorPos);

            virtual void Render(ID2D1HwndRenderTarget* pMainRT) = 0;
            virtual void Update() = 0;       // call when canvas update
        protected:
            virtual void onHover();
            virtual void onLeave();
            virtual void onClick();    // 按下后放开
            virtual void onPress();
            virtual void onRelease();

            Callback clickCB;           // 统一？？
            Callback pressCB;
            Callback releaseCB;
            Callback hoverCB;
            Callback leaveCB;

            vec2<float> anchor;      // 0-1  锚点在元素的哪个位置    默认锚点(0,0)左上角
            vec2<float> position;    // anchor的位置
            vec2<float> size;
            vec4<float> hitBox;      // left  top right bottom(上小下大)
            D2D1::RectF drawRect;

            //Animator m_animator;

            float opacity;

            bool hovered;   //
            bool leaved = true;
            bool pressed;   //
            bool released;  
            bool disabled;  //
            bool activated;
            bool clicked;
        };
    }
}
