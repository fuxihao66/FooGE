#pragma once
#include "Widget.hpp"


namespace FooGE{
    namespace Foo2D{
        class Container: public Widget{
        public:

            virtual void onHover();
            virtual void onLeave();
            virtual void onClick();
            virtual void onPress();
            virtual void onRelease();
        };
    }
}
