#pragma once
#include "Font.hpp"
#include "Widget.hpp"
#include "FontLoader.hpp"

namespace FooGE{
    namespace Foo2D{
        class Text : public Widget{
        public:
            Text();
            Text(UINT fontSize, std::wstring content);
            Text(UINT fontSize, std::wstring content, std::wstring pathToFontFile);
            ~Text();

            virtual void onHover();
            virtual void onLeave();
            virtual void onClick();
            virtual void onPress();
            virtual void onRelease();

            bool IgnoreEvent();
            void SetFont(const Font& ff);

            virtual void Render(ID2D1RenderTarget*);
        private:
            void InitTextFormat();
            void InitTextFormat(IDWriteFactory* pDWriteFactory);       // IDWRITEFACTORY这几个使用单例，直接用静态方法获取实例

            IDWriteFontCollection * m_pFCollection;
            IDWriteTextFormat* m_pTextFormat;
            ID2D1SolidColorBrush* m_pCommonBrush;


            std::wstring m_FontFileFilePath
            std::wstring m_content;
            float m_fontSize;
            bool ignoreEvent = true;
            
        };
    }
}
