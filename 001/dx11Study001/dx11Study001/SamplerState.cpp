#include "pch.h"
#include "SamplerState.h"

SamplerState::~SamplerState()
{
}

ComPtr<ID3D11SamplerState> SamplerState::GetComPtr()
{
    return _samplerState;
}

void SamplerState::Create()
{
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc,sizeof(desc));

    desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
    
    // RGBA Color
    desc.BorderColor[0] = 1;
    desc.BorderColor[1] = 1;
    desc.BorderColor[2] = 1;
    desc.BorderColor[3] = 1;

    desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    desc.MaxAnisotropy = 16;
    desc.MaxLOD = FLT_MAX;
    desc.MinLOD = FLT_MAX;
    desc.MipLODBias = 0.0f;

    _device->CreateSamplerState(
       &desc, 
       _samplerState.GetAddressOf()
    );
}
