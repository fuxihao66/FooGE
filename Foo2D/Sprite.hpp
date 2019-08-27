#pragma once
#include "Widget.hpp"
#include <string>
namespace FooGE{
    namespace Foo2D{
        class Sprite:public Widget{
        public:
            virtual void onHover();
            virtual void onLeave();
            virtual void onClick();
            virtual void onPress();
            virtual void onRelease();

            virtual void Render(ID2D1RenderTarget*);


            void SetImgPath(std::string& path);
        private:
            ID2D1Bitmap* pCurrentBitmap = nullptr;
            std::string imgPath;
        };
    }
}