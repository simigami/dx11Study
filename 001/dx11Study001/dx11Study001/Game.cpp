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

	CreateGeometry();
	CreateVS();
	CreateInputLayout();
	CreatePS();
}

void Game::Update()
{

}

void Game::Render()
{
	RenderBegin();

	{
		uint32 stride = sizeof(Vertex);
		uint32 offset = 0;
		
		// IA ����

		// ���� ���� ������ ���� ���� ���
		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset); 

		// ���ۿ� IL ����
		_deviceContext->IASetInputLayout(_inputLayout.Get());

		// ���� ���̸� ��� ���� �������� ���� �������� ����
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// VS ����
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);

		// RS ����

		// PS ����
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);

		// OM ����
		// ���������� ������ �� ������ �׸��� �κ�
		_deviceContext->Draw(_vertices.size(), 0);
	}

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

	// �ؽ�ó�� ������ �� Draw�� �׷� �ִ� ���� Ÿ�� ����
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

void Game::CreateGeometry()
{
	// ���� ����
	{
		_vertices.resize(3);

		_vertices[0].position = Vector3(-0.5f, -0.5f, 0.f);
		_vertices[0].color = Color(1.f, 0.f, 0.f, 1.f);

		_vertices[1].position = Vector3(0.f, 0.5f, 0.f);
		_vertices[1].color = Color(0.f, 1.f, 0.f, 1.f);

		_vertices[2].position = Vector3(0.5f, -0.5f, 0.f);
		_vertices[2].color = Color(0.f, 0.f, 1.f, 1.f);
	}
	
	// VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		// ���� ���� ����ü ����
		ZeroMemory(&desc, sizeof(desc));
		{
			// ������ CPU, GPU ��� ����� ����
			// D3D11_USAGE_DEFAULT = GPU RW
			// D3D11_USAGE_IMMUTABLE = GPU RO, CPU �ȵ�
			// D3D11_USAGE_DYNAMIC = GPU R, CPU O
			// D3D11_USAGE_STAGING = GPU -> CPU ���縸
			desc.Usage = D3D11_USAGE_IMMUTABLE;

			// ���۰� ���Ǵ� �뵵 = ���� �׸�����
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			// ���� �뿪
			desc.ByteWidth = (uint32)(sizeof(Vertex) * _vertices.size());
		}

		D3D11_SUBRESOURCE_DATA data;
		// Subresource ������ ����
		ZeroMemory(&data, sizeof(data));
		{
			data.pSysMem = _vertices.data();
		}

		// ���ҽ��� ���ۿ� �ִ� ����
		_device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
	}
}

void Game::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		// hlsl �󿡼� color�� position�� ���� offset 12byte�� �������� 12�� ����
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	// IL ����
	_device->CreateInputLayout(layout, count, _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
}

void Game::CreateVS()
{
	// ���̴� ���Ͽ��� Ư�� �Լ��� VS�� �����ϴ� �κ�
	LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0", _vsBlob);
 	HRESULT hr = _device->CreateVertexShader(
		_vsBlob->GetBufferPointer(), 
		_vsBlob->GetBufferSize(), 
		nullptr, 
		_vertexShader.GetAddressOf()
	);
	CHECK(hr);
}

void Game::CreatePS()
{
	// ���̴� ���Ͽ��� Ư�� �Լ��� PS�� �����ϴ� �κ�
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);
	HRESULT hr = _device->CreatePixelShader(
		_psBlob->GetBufferPointer(),
		_psBlob->GetBufferSize(), 
		nullptr, 
		_pixelShader.GetAddressOf()
	);
	CHECK(hr);
}

void Game::LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
{
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	HRESULT hr = ::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		blob.GetAddressOf(),
		nullptr);

	CHECK(hr);
}