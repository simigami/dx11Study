#include "pch.h"
#include "Texture.h"

Texture::Texture(ComPtr<ID3D11Device> device): _device(device)
{
}

Texture::~Texture()
{
}

ComPtr<ID3D11ShaderResourceView> Texture::GetComPtr()
{ return _shaderResourceView; }

void Texture::Create(const wstring& path)
{
    DirectX::TexMetadata md;
    DirectX::ScratchImage img;
    HRESULT hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &md, img);
    CHECK(hr);

    hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView.GetAddressOf());
    CHECK(hr);
}
