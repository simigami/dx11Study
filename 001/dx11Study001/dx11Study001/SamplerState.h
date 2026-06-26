#pragma once

class SamplerState
{
public:
    SamplerState(ComPtr<ID3D11Device> device) : _device(device)
    {
        
    }
    
    ~SamplerState();
    
    ComPtr<ID3D11SamplerState> GetComPtr();

    void Create();
    
private:
    ComPtr<ID3D11Device> _device; 
    ComPtr<ID3D11SamplerState> _samplerState = nullptr;
};