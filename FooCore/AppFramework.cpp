#include "AppFramework.hpp"

using namespace FooGE;

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return AppFramework::getApp()->msgProc(hwnd, msg, wParam, lParam);
}

LRESULT AppFramework::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// WM_PAINT

	switch (msg)
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			m_AppPaused = true;
			mTimer.Stop();
		}
		else
		{
			m_AppPaused = false;
			mTimer.Start();
		}
		return 0;
		// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
		// Save the new client area dimensions.
		mClientWidth = LOWORD(lParam);
		mClientHeight = HIWORD(lParam);
		
		if (wParam == SIZE_MINIMIZED)
		{
			m_AppPaused = true;
			m_Minimized = true;
			m_Maximized = false;
		}
		else if (wParam == SIZE_MAXIMIZED)
		{
			m_AppPaused = false;
			m_Minimized = false;
			m_Maximized = true;
			onResize();
		}
		else if (wParam == SIZE_RESTORED)
		{

			// Restoring from minimized state?
			if (m_Minimized)
			{
				m_AppPaused = false;
				m_Minimized = false;
				onResize();
			}

			// Restoring from maximized state?
			else if (m_Maximized)
			{
				m_AppPaused = false;
				m_Maximized = false;
				onResize();
			}
			else if (m_Resizing)
			{
				// If user is dragging the resize bars, we do not resize 
				// the buffers here because as the user continuously 
				// drags the resize bars, a stream of WM_SIZE messages are
				// sent to the window, and it would be pointless (and slow)
				// to resize for each WM_SIZE message received from dragging
				// the resize bars.  So instead, we reset after the user is 
				// done resizing the window and releases the resize bars, which 
				// sends a WM_EXITSIZEMOVE message.
			}
			else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
			{
				onResize();
			}
			
		}
		return 0;

		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		m_AppPaused = true;
		m_Resizing = true;
		mTimer.Stop();
		return 0;

		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		m_AppPaused = false;
		m_Resizing = false;
		mTimer.Start();
		onResize();
		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;


	/*operate input*/
	case WM_LBUTTONDOWN:
		Input::Instance().SetMouseDown(LEFT);
		Input::Instance().SetMousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MBUTTONDOWN:
		Input::Instance().SetMouseDown(MIDDLE);
		Input::Instance().SetMousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_RBUTTONDOWN:
		Input::Instance().SetMouseDown(RIGHT);
		Input::Instance().SetMousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
		Input::Instance().SetMouseUp(LEFT);
		Input::Instance().SetMousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MBUTTONUP:
		Input::Instance().SetMouseUp(MIDDLE);
		Input::Instance().SetMousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_RBUTTONUP:
		Input::Instance().SetMouseUp(RIGHT);
		Input::Instance().SetMousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEMOVE:
		Input::Instance().SetMousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	
	case WM_MOUSEWHEEL:
		// return GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1 : -1;
		return 0;

	case WM_KEYUP:
		// if (wParam == VK_ESCAPE)
		// {
		// 	PostQuitMessage(0);
		// }

		Input::Instance().SetKeyUp(static_cast<UINT>(wParam));

		return 0;
	case WM_KEYDOWN:
		Input::Instance().SetKeyDown(static_cast<UINT>(wParam));
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void AppFramework::SetEntryCanvas(Canvas * canvas){
	m_currCanvas = canvas;
}
//void AppFramework::SetEntryScene(Scene * scene){
//	m_currScene = scene;
//}


HWND AppFramework::GetWindowHandler(){
	return m_hMainWnd;
}

bool AppFramework::Run()
{
	MSG msg = { 0 };

	mTimer.Start();

	if (enablePhysics){
		// 开始物理线程
		// mTimer.SetTimeout(PhysicsEngine.simulate, 0.02);
		// 上次call 时间 = 1/50时
		
	}

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);                // ����mainwinproc
		}
		// Otherwise, do animation/game stuff.
		else
		{

			if (!m_AppPaused)
			{
				//CalculateFrameStats();
				/*if (m_currScene)
					m_currScene->Update(mTimer);*/
				if (m_currCanvas)
					m_currCanvas->Update(mTimer);
				if (m_D2DRender)
					m_D2DRender->Render(m_currCanvas,mTimer);
				// if (m_D3DRender)
				// 	m_D2DRender->Render(m_currScene, mTimer);
			}
			else
			{
				Sleep(100);
			}
		}
	}

	this->onDestroy();
}

void AppFramework::onCreate()
{
	
}



bool AppFramework::InitMainWindow()
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hAppInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"MainWnd";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, mClientWidth, mClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	m_hMainWnd = CreateWindow(L"MainWnd", mMainWndCaption.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mhAppInst, 0);
	if (!m_hMainWnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);

	return true;
}


HRESULT AppFramework::InitDeviceIndependentRes(){
	HRESULT hr;
	ID2D1GeometrySink *pSink = NULL;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	if (SUCCEEDED(hr))
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pDWriteFactory), reinterpret_cast<IUnknown **>(&m_pDWriteFactory));

	CoInitialize(NULL);

	if (SUCCEEDED(hr))
		hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));

	return hr;
}
HRESULT AppFramework::InitDeviceRes(){
	HRESULT hr = S_OK;

	if (!m_pMainRT)
	{
		RECT rc;
		GetClientRect(m_hMainWnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(	rc.right - rc.left,	rc.bottom - rc.top);
		hr = m_pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hMainWnd, size), &m_pMainRT);
	}

	return hr;
}

void AppFramework::onResize(){
	m_pMainRT->Resize(D2D1::SizeU(mClientWidth, mClientHeight));

	// assert(md3dDevice);
	// assert(mSwapChain);
	// assert(mDirectCmdListAlloc);

	// // Flush before changing any resources.
	// FlushCommandQueue();

	// ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

	// // Release the previous resources we will be recreating.
	// for (int i = 0; i < SwapChainBufferCount; ++i)
	// 	mSwapChainBuffer[i].Reset();
	// mDepthStencilBuffer.Reset();

	// // Resize the swap chain.
	// ThrowIfFailed(mSwapChain->ResizeBuffers(
	// 	SwapChainBufferCount,
	// 	mClientWidth, mClientHeight,
	// 	mBackBufferFormat,
	// 	DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));

	// mCurrBackBuffer = 0;

	// CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart());
	// for (UINT i = 0; i < SwapChainBufferCount; i++)
	// {
	// 	ThrowIfFailed(mSwapChain->GetBuffer(i, IID_PPV_ARGS(&mSwapChainBuffer[i])));
	// 	md3dDevice->CreateRenderTargetView(mSwapChainBuffer[i].Get(), nullptr, rtvHeapHandle);
	// 	rtvHeapHandle.Offset(1, mRtvDescriptorSize);
	// }

	// // Create the depth/stencil buffer and view.
	// D3D12_RESOURCE_DESC depthStencilDesc;
	// depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	// depthStencilDesc.Alignment = 0;
	// depthStencilDesc.Width = mClientWidth;
	// depthStencilDesc.Height = mClientHeight;
	// depthStencilDesc.DepthOrArraySize = 1;
	// depthStencilDesc.MipLevels = 1;

	// // Correction 11/12/2016: SSAO chapter requires an SRV to the depth buffer to read from 
	// // the depth buffer.  Therefore, because we need to create two views to the same resource:
	// //   1. SRV format: DXGI_FORMAT_R24_UNORM_X8_TYPELESS
	// //   2. DSV Format: DXGI_FORMAT_D24_UNORM_S8_UINT
	// // we need to create the depth buffer resource with a typeless format.  
	// depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;

	// depthStencilDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	// depthStencilDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	// depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	// depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	// D3D12_CLEAR_VALUE optClear;
	// optClear.Format = mDepthStencilFormat;
	// optClear.DepthStencil.Depth = 1.0f;
	// optClear.DepthStencil.Stencil = 0;
	// ThrowIfFailed(md3dDevice->CreateCommittedResource(
	// 	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
	// 	D3D12_HEAP_FLAG_NONE,
	// 	&depthStencilDesc,
	// 	D3D12_RESOURCE_STATE_COMMON,
	// 	&optClear,
	// 	IID_PPV_ARGS(mDepthStencilBuffer.GetAddressOf())));

	// // Create descriptor to mip level 0 of entire resource using the format of the resource.
	// D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	// dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	// dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	// dsvDesc.Format = mDepthStencilFormat;
	// dsvDesc.Texture2D.MipSlice = 0;
	// md3dDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), &dsvDesc, DepthStencilView());

	// // Transition the resource from its initial state to be used as a depth buffer.
	// mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mDepthStencilBuffer.Get(),
	// 	D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));

	// // Execute the resize commands.
	// ThrowIfFailed(mCommandList->Close());
	// ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	// mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// // Wait until resize is complete.
	// FlushCommandQueue();

	// // Update the viewport transform to cover the client area.
	// mScreenViewport.TopLeftX = 0;
	// mScreenViewport.TopLeftY = 0;
	// mScreenViewport.Width = static_cast<float>(mClientWidth);
	// mScreenViewport.Height = static_cast<float>(mClientHeight);
	// mScreenViewport.MinDepth = 0.0f;
	// mScreenViewport.MaxDepth = 1.0f;

	// mScissorRect = { 0, 0, mClientWidth, mClientHeight };
}

bool AppFramework::Initialize()
{
	InitDeviceIndependentRes();
	InitMainWindow();
	InitDeviceRes();

	// Do the initial resize code.
	onResize();

	return true;
}
/*
bool AppFramework::initDirect3D()
{
#if defined(DEBUG) || defined(_DEBUG) 
	// Enable the D3D12 debug layer.
	{
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
	}
#endif

	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&mdxgiFactory)));

	// Try to create hardware device.
	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr,             // default adapter
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&md3dDevice));

	// Fallback to WARP device.
	if (FAILED(hardwareResult))
	{
		ComPtr<IDXGIAdapter> pWarpAdapter;
		ThrowIfFailed(mdxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)));

		ThrowIfFailed(D3D12CreateDevice(
			pWarpAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&md3dDevice)));
	}

	ThrowIfFailed(md3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE,
		IID_PPV_ARGS(&mFence)));

	mRtvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	mDsvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	mCbvSrvUavDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.

	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
	msQualityLevels.Format = mBackBufferFormat;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;
	ThrowIfFailed(md3dDevice->CheckFeatureSupport(
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
		&msQualityLevels,
		sizeof(msQualityLevels)));

	m4xMsaaQuality = msQualityLevels.NumQualityLevels;
	assert(m4xMsaaQuality > 0 && "Unexpected MSAA quality level.");

#ifdef _DEBUG
	LogAdapters();
#endif

	CreateCommandObjects();
	CreateSwapChain();
	CreateRtvAndDsvDescriptorHeaps();

	return true;
}
*/


AppFramework::AppFramework(){
	Initialize();
}


AppFramework::~AppFramework()
{
}
