#pragma once
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
	shared_ptr<Pipeline> _pipeline;

private:
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	
	// Buffers
 	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout = nullptr;

	// RS
	shared_ptr<RasterizerState> _rasterizerState = nullptr;

	// // VS
	shared_ptr<VertexShader> _vertexShader = nullptr;

	// PS
	shared_ptr<PixelShader> _pixelShader = nullptr;

// TODO 004: png
private:
	shared_ptr<Texture> _texture1;
	shared_ptr<Texture> _texture2;
	
	shared_ptr<SamplerState> _samplerState = nullptr;
	shared_ptr<BlendState> _blendState = nullptr;

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
