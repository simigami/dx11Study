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
    _graphics = make_shared<Graphics>(hwnd);
    _pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());
    _vertexBuffer = make_shared<VertexBuffer>(_graphics->GetDevice());
    _indexBuffer = make_shared<IndexBuffer>(_graphics->GetDevice());
    _inputLayout = make_shared<InputLayout>(_graphics->GetDevice());
    _geometry = make_shared<Geometry<VertexTextureData>>();
    _vertexShader = make_shared<VertexShader>(_graphics->GetDevice());
    _pixelShader = make_shared<PixelShader>(_graphics->GetDevice());
    _constantBuffer = make_shared<ConstantBuffer<TransformData>>(_graphics->GetDevice(), _graphics->GetDeviceContext());
    
    // Texture
    _texture1 = make_shared<Texture>(_graphics->GetDevice());
    
    // State
    _rasterizerState = make_shared<RasterizerState>(_graphics->GetDevice());
    _samplerState = make_shared<SamplerState>(_graphics->GetDevice());
    _blendState = make_shared<BlendState>(_graphics->GetDevice());
    
    // 기하학 적인 도형에 대한 메모리 정보 + 버텍스 버퍼에 넘겨줌
    GeometryHelper::CreateRectangle(_geometry);
    _vertexBuffer->Create(_geometry->GetVertex());
    _indexBuffer->Create(_geometry->GetIndice());

    _vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");
    _inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());
    _pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");
    
    _rasterizerState->Create();
    _samplerState->Create();
    _blendState->Create();
    
    // Init SRV Data
    _texture1->Create(L"Skeleton.png");
    
    _constantBuffer->Create();
}

void Game::Update()
{
    _localPosition.x += 0.001f;
    
    Matrix mS = Matrix::CreateScale(_localScale);
    Matrix mR = Matrix::CreateRotationX(_localRotation.x);
    mR *= Matrix::CreateRotationY(_localRotation.y);
    mR *= Matrix::CreateRotationZ(_localRotation.z);
    Matrix mT = Matrix::CreateTranslation(_localPosition);
    Matrix matWorld = mS * mR * mT;
    _transformData.matWorld = matWorld;

    _constantBuffer->CopyData(_transformData);
}

void Game::Render()
{
    _graphics->RenderBegin();
    
    {
        PipelineInfo info;
        info.inputLayout = _inputLayout;
        info.vertexShader = _vertexShader;
        info.pixelShader = _pixelShader;
        info.rasterizerState = _rasterizerState;
        info.blendState = _blendState;
      
        _pipeline->UpdatePipeline(info);

        // IA
        _pipeline->SetVertexBuffer(_vertexBuffer);
        _pipeline->SetIndexBuffer(_indexBuffer);

        // VS
        _pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
       
        // RS
       
        // PS
        _pipeline->SetTexture(0, SS_PixelShader, _texture1);
        _pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);
       
        // OM
        _pipeline->DrawIndexed(_geometry->GetIndiceCount(), 0, 0);
    }
    
    _graphics->RenderEnd();
}