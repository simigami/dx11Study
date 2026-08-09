#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
    : _device(device), _deviceContext(deviceContext)
{
    _geometry = make_shared<Geometry<VertexTextureData>>();
    GeometryHelper::CreateRectangle(_geometry);
    
    _vertexBuffer = make_shared<VertexBuffer>(device);
    _vertexBuffer->Create(_geometry->GetVertex());
    
    _indexBuffer = make_shared<IndexBuffer>(device);
    _indexBuffer->Create(_geometry->GetIndice());
    
    _vertexShader = make_shared<VertexShader>(device);
    _vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

    _inputLayout = make_shared<InputLayout>(device);
    _inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

    _pixelShader = make_shared<PixelShader>(device);
    _pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");
    
    _rasterizerState = make_shared<RasterizerState>(device);
    _rasterizerState->Create();
    
    // State
    _samplerState = make_shared<SamplerState>(device);
    _samplerState->Create();
    
    _blendState = make_shared<BlendState>(device);
    _blendState->Create();
    
    _constantBuffer = make_shared<ConstantBuffer<TransformData>>(device, deviceContext);
    _constantBuffer->Create();
    
    // Texture, Init SRV Data
    _texture = make_shared<Texture>(device);
    _texture->Create(L"Skeleton.png");
}

void GameObject::Update()
{
    Vector3 pos = _transform->GetWorldPosition();
    pos.x += 0.001f;
    
    _transform->SetWorldPosition(pos);
    _transformData.matWorld = _transform->GetWorldMatrix();

    _constantBuffer->CopyData(_transformData);
}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
{
    PipelineInfo info;
    info.inputLayout = _inputLayout;
    info.vertexShader = _vertexShader;
    info.pixelShader = _pixelShader;
    info.rasterizerState = _rasterizerState;
    info.blendState = _blendState;
      
    pipeline->UpdatePipeline(info);

    // IA
    pipeline->SetVertexBuffer(_vertexBuffer);
    pipeline->SetIndexBuffer(_indexBuffer);

    // VS
    pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
       
    // RS
       
    // PS
    pipeline->SetTexture(0, SS_PixelShader, _texture);
    pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);
       
    // OM
    pipeline->DrawIndexed(_geometry->GetIndiceCount(), 0, 0);
}
