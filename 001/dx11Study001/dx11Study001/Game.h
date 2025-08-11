#pragma once
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

// 렌더링을 위한 함수
private:
	void RenderBegin();
	void RenderEnd();

private:
	void CreateDeviceAndSwapChain();

	// D3D11CreateDeviceAndSwapChain으로 만들어진 후면 버퍼에 렌더링을 하기 위한 지시 함수
	void CreateRenderTargetView();

	// 뷰포트 설정하는 Setter
	void SetViewport();

private:
	/* Interface D3D11 Device */

	//ID3D11Device* _device; new가 아닌, D3D11CreateDevice함수를 통해 생성
	//ID3D11DeviceContext* _deviceContext;

	// 스마트 포인터로 Device를 관리하는 방법
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	ComPtr<IDXGISwapChain> _swapChain = nullptr;

	// GPU 모델이 많아지는데 디바이스가 어떻게 다 지원할까?
	// DX에서는 인터페이스만 만들어 주고, Internal은 MSFT와 NVDA에서 하도록 하자

	/* Device & DeviceContext 
	* https://learn.microsoft.com/ko-kr/windows/win32/direct3d11/overviews-direct3d-11-devices-intro
	*/
	// Device : 소스를 만들어주는 총사령관
	// CreateDevice, CreateDeviceWithSwapChain 으로 생성
	// DeviceContext : 만들어진 소스들의 상호작용을 지시하는 총사령관

	/* DXGI */
	// 그래픽의 일부가 다른 부분보다 더 느리게 진화하여, 독립된 라이브러리를 제작함
	// 

	/* SwapChain */
	// double buffering과 같이 활성화 해야 하는 버퍼의 비트 블링크를 해주는 주체

	/* Render Target View */
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	/* Misc - Viewport */
	D3D11_VIEWPORT _viewport = {0};
	float _clearColor[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
};