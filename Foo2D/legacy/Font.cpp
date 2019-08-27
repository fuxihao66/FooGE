#include "Font.hpp"

using namespace FooGE::Foo2D;


Font::Font(){
    
}
Font::Font(std::wstring fontName){
    
}

Font::Font(std::wstring fontName, std::wstring fontPath){
    LoadFont(fontPath);
}

void LoadFont(std::wstring fontFileFilePath){
    MFFontContext fContext(pDWriteFactory);
    std::vector<std::wstring> filePaths; // vector containing ABSOLUTE file paths of the font files which are to be added to the collection
    filePaths.push_back(fontFileFilePath);
    HRESULT hr = fContext.CreateFontCollection(filePaths, &fCollection); // create custom font collection
    hr = pDWriteFactory->CreateTextFormat(
                L"Font Family",    // Font family name
                fCollection,
                DWRITE_FONT_WEIGHT_REGULAR,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                16.0f,
                L"en-us",
                &pTextFormat       // IDWriteTextFormat object
    );
}