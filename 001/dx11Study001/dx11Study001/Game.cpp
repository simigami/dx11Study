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

	// �������� ����̽� �����ϱ� (���� X)
	//_device->AddRef(); ����Ʈ ������ó�� Device �����͸� �����ϴ� ref count ������ ��� ���. 0�Ǹ� �ڵ� �Ҹ�
	//_device->Release(); 

	// Comptr ����Ʈ �����ͷ� ����̽��� �����ؾ� ��

}

void Game::Update()
{
}

void Game::Render()
{
	RenderBegin();

	// TODO - ��� ��ü�� �׸�
	// IA - VS - RS - PS - OM

	RenderEnd();
}

void Game::RenderBegin()
{
	// OutputMerge Render Target �ʱ� �۾�
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);

	// �����並 Ư�� Color�� �ʱ�ȭ �����ִ� �κ�
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);
	
	// �����Ͱ� ������ ����Ʈ�� ������ �����͸� �����ϴ� �κ�
	_deviceContext->RSSetViewports(1, &_viewport);
}

void Game::RenderEnd()
{
	HRESULT hr =  _swapChain->Present(1, 0); // ���� ü���� ������ ��� ��û�� �ϴ� �߿��� �Լ�
	CHECK(hr);
}

void Game::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	{
		swapChainDesc.BufferDesc.Width = _width;
		swapChainDesc.BufferDesc.Height = _height;

		// �ֻ��� ���� �ɼ�
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		// ���÷� ���� �ɼ�
		swapChainDesc.SampleDesc.Count = 1; // ��Ƽ-�˸��ƽ̿� ���� ��
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // �� ���۴� ���� ������� �׷��ִ� ������ ����
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = _hwnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	_device.Get(); // ID3D11Device*
	_device.GetAddressOf(); // ID3D11Device**

	// D3D11CreateDeviceAndSwapChain�� �ѹ��� ���ѻ� ����� : https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/nf-d3d11-d3d11createdeviceandswapchain
	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE, // ����̹��� Ÿ���� GPU�� �Ѵ�
		nullptr,
		0,
		nullptr, // DX ���� �� ����� �����ؾ� �ϴ� ����� �迭
		0,
		D3D11_SDK_VERSION, // SDK ����
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

	// ID3D11Texture2D -> PNG ���� 2D �����͸� ��� �ִ� ����
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
