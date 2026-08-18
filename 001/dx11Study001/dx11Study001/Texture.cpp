#include "pch.h"
#include "Texture.h"

Texture::Texture(ComPtr<ID3D11Device> device): Super(ResourceType::Texture), _device(device)
{
}

Texture::~Texture()
{
}

void Texture::Load(const wstring& path)
{
    ResourceBase::Load(path);
}

void Texture::Save(const wstring& path)
{
    ResourceBase::Save(path);
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

    _size.x = md.width;
    _size.y = md.height;
}