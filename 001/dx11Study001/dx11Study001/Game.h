#pragma once
#include <string>
#include <memory>
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
	shared_ptr<Graphics> _Graphics;

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();

private:
	/* Interface D3D11 Device */

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

// TODO 003: �ﰢ�� �����
private:
	void CreateGeometry();
	void CreateConstantBuffer();
	void CreateInputLayout();
	void CreateVS();
	void CreatePS();

	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

private:
	// �⺻���� Geometry ������ ��� ��ü
	vector<Vertex> _vertices;

	// ���� ������ D3D���� ����Ǵ� ���� ��ü
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;

	// ���� ������ ������ ������������ �Է¿� ���޵Ǵ� ��ü
	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;

	// RS
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob> _vsBlob = nullptr;

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;


// TODO 004: Index Buffer�� �簢�� �����
private:
	vector<uint32> _indices;
	ComPtr<ID3D11Buffer> _indexBuffer;

// TODO 004: ���� png �ֱ�
private:
	// Shader Resource View
	void CreateSRV();

	// ���ҽ� �� ��ü
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView2;

	// ���÷� ����
	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	
	ComPtr<ID3D11BlendState> _blendState = nullptr;

// TODO 004: Constant Buffer
private:
	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;

// TODO 005 : SRT
private:
	Vector3 _localPosition = {0.f, 0.f, 0.f,};
	Vector3 _localRotation = {0.f, 0.f, 0.f,};
	Vector3 _localScale = {1.f, 1.f, 1.f,};
};