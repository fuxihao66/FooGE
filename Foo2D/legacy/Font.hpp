#pragma once
#include <string>
#include "FontLoader.hpp"
namespace FooGE{
    namespace Foo2D{
        class Font{
        public:
            Font();  // default font family
            Font(std::wstring fontName);   // use font name
            Font(std::wstring fontName, std::wstring fontPath); // custom font path
            ~Font(); // delete resource
            void LoadFont(std::wstring);
        private:
            std::string fontFamily;
            unsigned int fontSize;
            


            IDWriteFactory* pDWriteFactory;
            IDWriteFontCollection *fCollection;
            IDWriteTextFormat* pTextFormat;
        };
    }
};