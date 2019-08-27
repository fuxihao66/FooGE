#include "Text.hpp"

using namespace FooGE::Foo2D;


Text::Text(){

}

Text::Text(float fontSize, std::wstring content)
{
    m_fontSize = fontSize;
    m_content = content;
}
Text::Text(float fontSize, std::wstring content, std::wstring pathToFontFile){
    m_fontSize = fontSize;
    m_content = content;
    m_FontFileFilePath = pathToFontFile;
}

void Text::InitTextFormat(IDWriteFactory* pDWriteFactory){
    MFFontContext fContext(pDWriteFactory);
    std::vector<std::wstring> filePaths; // vector containing ABSOLUTE file paths of the font files which are to be added to the collection
    filePaths.push_back(m_FontFileFilePath);
    HRESULT hr = fContext.CreateFontCollection(filePaths, &m_pFCollection); // create custom font collection
    hr = pDWriteFactory->CreateTextFormat(
                L"Font Family",    // Font family name
                m_pFCollection,
                DWRITE_FONT_WEIGHT_REGULAR,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                m_fontSize,
                L"en-us",
                &m_pTextFormat       // IDWriteTextFormat object
    );
}

void Text::Render(ID2D1RenderTarget* pRenderTarget){
    pRenderTarget->DrawText(m_content.c_str(), m_content.length(), m_pTextFormat, drawRect, m_pCommonBrush);
}
