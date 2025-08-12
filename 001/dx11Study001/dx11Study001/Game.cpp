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
		
		// IA 과정

		// 정점 정보 저장한 버퍼 설정 명령
		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset); 

		// 버퍼와 IL 연결
		_deviceContext->IASetInputLayout(_inputLayout.Get());

		// 정점 사이를 어떻게 이을 것인지에 대한 토폴로지 정의
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// VS 과정
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);

		// RS 과정

		// PS 과정
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);

		// OM 과정
		// 실질적으로 렌더링 된 정보를 그리는 부분
		_deviceContext->Draw(_vertices.size(), 0);
	}

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

	// 텍스처에 렌더링 된 Draw를 그려 넣는 렌더 타겟 설정
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
	// 정점 정보
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
		// 버퍼 설명 구조체 설정
		ZeroMemory(&desc, sizeof(desc));
		{
			// 버퍼의 CPU, GPU 통신 방법을 설정
			// D3D11_USAGE_DEFAULT = GPU RW
			// D3D11_USAGE_IMMUTABLE = GPU RO, CPU 안됨
			// D3D11_USAGE_DYNAMIC = GPU R, CPU O
			// D3D11_USAGE_STAGING = GPU -> CPU 복사만
			desc.Usage = D3D11_USAGE_IMMUTABLE;

			// 버퍼가 사용되는 용도 = 정점 그릴려고
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			// 버퍼 대역
			desc.ByteWidth = (uint32)(sizeof(Vertex) * _vertices.size());
		}

		D3D11_SUBRESOURCE_DATA data;
		// Subresource 데이터 설정
		ZeroMemory(&data, sizeof(data));
		{
			data.pSysMem = _vertices.data();
		}

		// 리소스를 버퍼에 넣는 과정
		_device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
	}
}

void Game::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		// hlsl 상에서 color가 position에 비해 offset 12byte를 가짐으로 12를 넣음
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	// IL 설정
	_device->CreateInputLayout(layout, count, _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
}

void Game::CreateVS()
{
	// 쉐이더 파일에서 특정 함수를 VS로 설정하는 부분
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
	// 쉐이더 파일에서 특정 함수를 PS로 설정하는 부분
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