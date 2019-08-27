#include <Windows.h>
#include <assert.h>
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <functional>

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#include <iostream>

#include "Canvas.hpp"
#include "Font.hpp"


#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWrite.lib")



/*
D2DRender:  view
RenderState: data
EventListener: logic
*/

namespace FooGE{
    namespace Foo2D{
        class D2DRender{
        public:
            D2DRender();
            D2DRender(ID2D1Factory* pD2DFactory, ID2D1HwndRenderTarget* pMainRT, IDWriteFactory* pDWriteFactory, IWICImagingFactory* pWICFactory);
            ~D2DRender();

            void Render(const Canvas& currCanvas);
            void Stop();


            void SetFont(Font* font);
        private:  
            ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
            ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
            ID2D1Factory*			m_pD2DFactory		= nullptr;		// D2D工厂
            ID2D1HwndRenderTarget*	m_pMainRT			= nullptr;		// renderTarget

            IDWriteFactory*			m_pDWriteFactory	= nullptr;		// DWrite工厂   字体
            IWICImagingFactory*		m_pWICFactory		= nullptr;		// WIC工厂  工具类
            

            Canvas* currCanvas = nullptr;

        };
    }
}
