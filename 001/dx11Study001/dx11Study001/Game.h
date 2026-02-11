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
	HWND _hwnd;
	shared_ptr<Graphics> _graphics;

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();

private:
	void CreateGeometry();
	void CreateConstantBuffer();
	void CreateInputLayout();
	void CreateVS();
	void CreatePS();

	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

private:
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	
 	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	shared_ptr<InputLayout> _inputLayout = nullptr;

	// RS
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob> _vsBlob = nullptr;

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;

// TODO 004: png
private:
	// Shader Resource View
	void CreateSRV();
	
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView2;
	
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
