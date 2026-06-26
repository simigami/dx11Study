#include "pch.h"
#include "RasterizerState.h"

RasterizerState::~RasterizerState()
{
}

void RasterizerState::Create()
{
    D3D11_RASTERIZER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_BACK;
    desc.FrontCounterClockwise = false;

    HRESULT hr = _device->CreateRasterizerState(
       &desc, _rasterizerState.GetAddressOf()
    );
    CHECK(hr);
}

void RasterizerState::Create(D3D11_RASTERIZER_DESC desc)
{
    HRESULT hr = _device->CreateRasterizerState(
       &desc, _rasterizerState.GetAddressOf()
    );
    CHECK(hr);
}