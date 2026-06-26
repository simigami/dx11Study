#pragma once

// Graphics Rendering Pipeline

struct PipelineInfo
{
    shared_ptr<InputLayout> inputLayout;
    shared_ptr<VertexShader> vertexShader; // General Shader
    shared_ptr<PixelShader> pixelShader; // General Shader
    shared_ptr<RasterizerState> rasterizerState;
    shared_ptr<BlendState> blendState;
    
    D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

class Pipeline
{
public:
    Pipeline(ComPtr<ID3D11DeviceContext> deviceContext) : _deviceContext(deviceContext) { };
    ~Pipeline();
    
    // Common pipelining function
    void UpdatePipeline(const PipelineInfo& info);
    
    // Specific pipelining
    void SetVertexBuffer(shared_ptr<VertexBuffer> vertexBuffer);
    void SetIndexBuffer(shared_ptr<IndexBuffer> indexBuffer);
    
    template<typename T>
    void SetConstantBuffer(uint32 slot, uint32 scope, shared_ptr<ConstantBuffer<T>> constantBuffer)
    {
        // Constant buffer can use both in VS and PS, so use bitmask
        if (scope & SS_VertexShader)
        {
            _deviceContext->VSSetConstantBuffers(slot, 1, constantBuffer->GetComPtr().GetAddressOf());
        }
        
        if (scope & SS_PixelShader)
        {
            _deviceContext->PSSetConstantBuffers(slot, 1, constantBuffer->GetComPtr().GetAddressOf());
        }
    };
    
    void SetTexture(uint32 slot, uint32 scope, shared_ptr<Texture> texture);
    void SetSamplerState(uint32 slot, uint32 scope, shared_ptr<SamplerState> samplerState);
    
    void Draw(uint32 vertexCount, uint32 startVertexLocation);
    void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, int32 baseVertexLocation);
    
private:
    ComPtr<ID3D11DeviceContext> _deviceContext;
};
