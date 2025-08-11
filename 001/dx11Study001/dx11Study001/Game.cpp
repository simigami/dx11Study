#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_width = GWinSizeX;
	_height = GWinSizeY;

	// TODO
	CreateDeviceAndSwapChain	();
	CreateRenderTargetView();
	SetViewport();

	// 수동으로 디바이스 관리하기 (권장 X)
	//_device->AddRef(); 스마트 포인터처럼 Device 포인터를 참조하는 ref count 개수를 재는 요소. 0되면 자동 소멸
	//_device->Release(); 

	// Comptr 스마트 포인터로 디바이스를 관리해야 함

}

void Game::Update()
{
}

void Game::Render()
{
	RenderBegin();

	// TODO - 모든 객체를 그림
	// IA - VS - RS - PS - OM

	RenderEnd();
}

void Game::RenderBegin()
{
	// OutputMerge Render Target 초기 작업
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);

	// 렌더뷰를 특정 Color로 초기화 시켜주는 부분
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);
	
	// 레스터가 보여줄 뷰포트의 개수와 포인터를 설정하는 부분
	_deviceContext->RSSetViewports(1, &_viewport);
}

void Game::RenderEnd()
{
	HRESULT hr =  _swapChain->Present(1, 0); // 스왑 체인이 실제로 출력 요청을 하는 중요한 함수
	CHECK(hr);
}

void Game::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	{
		swapChainDesc.BufferDesc.Width = _width;
		swapChainDesc.BufferDesc.Height = _height;

		// 주사율 관련 옵션
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		// 샘플러 관련 옵션
		swapChainDesc.SampleDesc.Count = 1; // 안티-알리아싱에 대한 값
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 이 버퍼는 최종 결과물을 그려주는 역할을 설정
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = _hwnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	_device.Get(); // ID3D11Device*
	_device.GetAddressOf(); // ID3D11Device**

	// D3D11CreateDeviceAndSwapChain로 한번에 삼총사 만들기 : https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/nf-d3d11-d3d11createdeviceandswapchain
	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE, // 드라이버의 타입을 GPU로 한다
		nullptr,
		0,
		nullptr, // DX 버전 별 기능을 지원해야 하는 명시적 배열
		0,
		D3D11_SDK_VERSION, // SDK 버전
		&swapChainDesc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	CHECK(hr);
}

void Game::CreateRenderTargetView()
{
	HRESULT hr;

	// ID3D11Texture2D -> PNG 같은 2D 데이터를 담고 있는 파일
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK(hr);

	_device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
}

void Game::SetViewport()
{
	_viewport.TopLeftX = 0.f;
	_viewport.TopLeftY = 0.f;
	_viewport.Width = static_cast<float>(_width);
	_viewport.Height = static_cast<float>(_height);
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;
}
