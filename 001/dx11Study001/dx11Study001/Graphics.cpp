#include "pch.h"
#include "Graphics.h"

Graphics::Graphics(HWND hwnd)
{
    _hwnd = hwnd;
    CreateDeviceAndSwapChain();
    CreateRenderTargetView();
    SetViewport();
}

Graphics::~Graphics()
{
}

void Graphics::RenderBegin()
{
    _deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);
    
    _deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);
    
    _deviceContext->RSSetViewports(1, &_viewport);
}

void Graphics::RenderEnd()
{
    HRESULT hr =  _swapChain->Present(1, 0);
    CHECK(hr);
}

void Graphics::CreateDeviceAndSwapChain()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    {
        swapChainDesc.BufferDesc.Width = GWinSizeX;
        swapChainDesc.BufferDesc.Height = GWinSizeY;
        
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 1;
        swapChainDesc.OutputWindow = _hwnd;
        swapChainDesc.Windowed = true;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    }

    _device.Get(); // ID3D11Device*
    _device.GetAddressOf(); // ID3D11Device**
    
    HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE, 
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION, 
        &swapChainDesc,
        _swapChain.GetAddressOf(),
        _device.GetAddressOf(),
        nullptr,
        _deviceContext.GetAddressOf()
    );

    CHECK(hr);
}

void Graphics::CreateRenderTargetView()
{
    HRESULT hr;

    ComPtr<ID3D11Texture2D> backBuffer = nullptr;
    hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
    CHECK(hr);
    
    _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
}

void Graphics::SetViewport()
{
    _viewport.TopLeftX = 0.f;
    _viewport.TopLeftY = 0.f;
    _viewport.Width = static_cast<float>(GWinSizeX);
    _viewport.Height = static_cast<float>(GWinSizeY);
    _viewport.MinDepth = 0.f;
    _viewport.MaxDepth = 1.f;
}
