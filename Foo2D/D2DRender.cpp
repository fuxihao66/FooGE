#include "D2DRender.hpp"


using namespace FooGE::Foo2D;


D2DRender::D2DRender()
: 	m_hwnd(NULL),
	m_pDirect2dFactory(NULL), m_pRenderTarget(NULL), 
	m_pLightSlateGrayBrush(NULL), m_pCornflowerBlueBrush(NULL)
{

}


D2DRender::D2DRender(ID2D1Factory* pD2DFactory, ID2D1HwndRenderTarget* pMainRT, 
					 IDWriteFactory* pDWriteFactory, IWICImagingFactory* pWICFactory){
	ID2D1Factory*			m_pD2DFactory		= pD2DFactory;		// D2D工厂
	ID2D1HwndRenderTarget*	m_pMainRT			= pMainRT;		// renderTarget
	IDWriteFactory*			m_pDWriteFactory	= pDWriteFactory;		// DWrite工厂   字体
	IWICImagingFactory*		m_pWICFactory		= pWICFactory;		// WIC工厂  工具类
}

D2DRender::~D2DRender(){
	// SafeRelease(&m_pDirect2dFactory);
	// SafeRelease(&m_pRenderTarget);
	// SafeRelease(&m_pLightSlateGrayBrush);
	// SafeRelease(&m_pCornflowerBlueBrush);
}




void D2DRender::Render(const Canvas* currCanvas){
    std::vector<Widget*>& renderQueue = currCanvas->GetRenderQueue();

	for (auto item : renderQueue){
		item->Render(m_pMainRT);
	}
	
}