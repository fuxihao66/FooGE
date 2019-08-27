#pragma once
#include <windows.h>
#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <cassert>
#include <assert.h>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <functional>

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#include "Input.hpp"
#include "MTimer.hpp"
#include "../Foo2D/Canvas.hpp"
#include "../Foo2D/D2DRender.hpp"
#include "../FooMath/utility.hpp"
//#include "../Foo3D/Scene.hpp"

using Microsoft::WRL::ComPtr;
// using namespace std;

using namespace FooGE::Foo2D;

namespace FooGE{
	class AppFramework{
	public:
		virtual bool Run();
		virtual void onCreate();

		AppFramework();
		~AppFramework();


		void SetEntryCanvas(Canvas * canvas);
		//void SetEntryScene(Scene * scene);
	protected:
		bool Initialize();
		bool InitMainWindow();
		HRESULT InitDeviceIndependentRes();
		HRESULT InitDeviceRes();

		HWND GetWindowHandler();

		virtual void onResize();
		virtual void onDestroy();



		static AppFramework* mApp;

		bool enablePhysics = false;
		UINT m_PhysicsFrame = 50;

		MTimer mTimer;
		//Scene * m_currScene;
		Canvas * m_currCanvas;
		D2DRender * m_D2DRender;
		// D3DRender * m_D3DRender;

		ID2D1Factory*			m_pD2DFactory		= nullptr;		// D2D工厂
		ID2D1HwndRenderTarget*	m_pMainRT			= nullptr;		// renderTarget
		IDWriteFactory*			m_pDWriteFactory	= nullptr;		// DWrite工厂   字体
		IWICImagingFactory*		m_pWICFactory		= nullptr;		// WIC工厂  工具类

		HINSTANCE m_hAppInst = nullptr; // application instance handle
		HWND      m_hMainWnd = nullptr; // main window handle
		bool      m_AppPaused = false;  // is the application paused?
		bool      m_Minimized = false;  // is the application minimized?
		bool      m_Maximized = false;  // is the application maximized?
		bool      m_Resizing = false;   // are the resize bars being dragged?
		bool      m_FullscreenState = false;// fullscreen enabled
		// Set true to use 4X MSAA (?.1.8).  The default is false.
		// bool      m4xMsaaState = false;    // 4X MSAA enabled
		// UINT      m4xMsaaQuality = 0;      // quality level of 4X MSAA




		UINT mClientWidth = 1000;
		UINT mClientHeight = 900;
	private:
		LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}


