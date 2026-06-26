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
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	
 	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	shared_ptr<InputLayout> _inputLayout = nullptr;

	// RS
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

	// // VS
	shared_ptr<VertexShader> _vertexShader = nullptr;

	// PS
	shared_ptr<PixelShader> _pixelShader = nullptr;

// TODO 004: png
private:
	shared_ptr<Texture> _texture1;
	shared_ptr<Texture> _texture2;
	
	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	ComPtr<ID3D11BlendState> _blendState = nullptr;

// TODO 004: Constant Buffer
private:
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

// TODO 005 : SRT
private:
	Vector3 _localPosition = {0.f, 0.f, 0.f,};
	Vector3 _localRotation = {0.f, 0.f, 0.f,};
	Vector3 _localScale = {.25f, .25f, .25f,};
};
