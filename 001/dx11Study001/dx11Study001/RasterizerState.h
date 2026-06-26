#pragma once

class RasterizerState
{
public:
    RasterizerState(ComPtr<ID3D11Device> device) : _device(device)
    {
        
    }
    
    ~RasterizerState();
    
    ComPtr<ID3D11RasterizerState> GetComPtr() { return _rasterizerState; }
    
    void Create();
    void Create(D3D11_RASTERIZER_DESC desc);
    
private:
    ComPtr<ID3D11Device> _device = nullptr;
    ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;
};
