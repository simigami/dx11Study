#pragma once
class Graphics
{
public:
	Graphics(HWND hwnd);
	~Graphics();

	void RenderBegin();
	void RenderEnd();
	
	ComPtr<ID3D11Device> GetDevice() { return _device; };
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; };

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();
	
private:
	HWND _hwnd;
	
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	ComPtr<IDXGISwapChain> _swapChain = nullptr;

	/* Render Target View */
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	/* Misc - Viewport */
	D3D11_VIEWPORT _viewport = {0};
	float _clearColor[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
};

