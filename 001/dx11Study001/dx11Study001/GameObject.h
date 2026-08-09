#pragma once

class GameObject
{
public:
    GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
    
    void Update();
    void Render(shared_ptr<Pipeline> pipeline);
    
private:
    ComPtr<ID3D11Device> _device;
    ComPtr<ID3D11DeviceContext> _deviceContext;
    
    // Buffers
    shared_ptr<Geometry<VertexTextureData>> _geometry;
    shared_ptr<VertexBuffer> _vertexBuffer;
    shared_ptr<IndexBuffer> _indexBuffer;
    shared_ptr<InputLayout> _inputLayout = nullptr;

    // VS
    shared_ptr<VertexShader> _vertexShader = nullptr;
    // RS
    shared_ptr<RasterizerState> _rasterizerState = nullptr;
    // PS
    shared_ptr<PixelShader> _pixelShader = nullptr;

    // Texture Data
    shared_ptr<Texture> _texture;
	
    shared_ptr<SamplerState> _samplerState = nullptr;
    shared_ptr<BlendState> _blendState = nullptr;

    // Constant Buffer
    TransformData _transformData;
    shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;
    
    // Components
    shared_ptr<Transform> _transform = make_shared<Transform>();
};
