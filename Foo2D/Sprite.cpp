#include "Sprite.hpp"

using namespace FooGE::Foo2D;

void Sprite::SetImgPath(std::string& path){
    imgPath = path;
}


void Sprite::Render(ID2D1RenderTarget* pRenderTarget){
    pRenderTarget->DrawBitmap(pCurrentBitmap, drawRect); 
}