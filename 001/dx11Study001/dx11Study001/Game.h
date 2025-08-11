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

// �������� ���� �Լ�
private:
	void RenderBegin();
	void RenderEnd();

private:
	void CreateDeviceAndSwapChain();

	// D3D11CreateDeviceAndSwapChain���� ������� �ĸ� ���ۿ� �������� �ϱ� ���� ���� �Լ�
	void CreateRenderTargetView();

	// ����Ʈ �����ϴ� Setter
	void SetViewport();

private:
	/* Interface D3D11 Device */

	//ID3D11Device* _device; new�� �ƴ�, D3D11CreateDevice�Լ��� ���� ����
	//ID3D11DeviceContext* _deviceContext;

	// ����Ʈ �����ͷ� Device�� �����ϴ� ���
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	ComPtr<IDXGISwapChain> _swapChain = nullptr;

	// GPU ���� �������µ� ����̽��� ��� �� �����ұ�?
	// DX������ �������̽��� ����� �ְ�, Internal�� MSFT�� NVDA���� �ϵ��� ����

	/* Device & DeviceContext 
	* https://learn.microsoft.com/ko-kr/windows/win32/direct3d11/overviews-direct3d-11-devices-intro
	*/
	// Device : �ҽ��� ������ִ� �ѻ�ɰ�
	// CreateDevice, CreateDeviceWithSwapChain ���� ����
	// DeviceContext : ������� �ҽ����� ��ȣ�ۿ��� �����ϴ� �ѻ�ɰ�

	/* DXGI */
	// �׷����� �Ϻΰ� �ٸ� �κк��� �� ������ ��ȭ�Ͽ�, ������ ���̺귯���� ������
	// 

	/* SwapChain */
	// double buffering�� ���� Ȱ��ȭ �ؾ� �ϴ� ������ ��Ʈ ��ũ�� ���ִ� ��ü

	/* Render Target View */
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	/* Misc - Viewport */
	D3D11_VIEWPORT _viewport = {0};
	float _clearColor[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
};