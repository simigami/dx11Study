#pragma once
#include "ResourceBase.h"

class Texture : public ResourceBase
{
    using Super = ResourceBase;

public:
    Texture(ComPtr<ID3D11Device> device);
    ~Texture();

    virtual void Load(const wstring& path) override;
    virtual void Save(const wstring& path) override;

    ComPtr<ID3D11ShaderResourceView> GetComPtr();

    void Create(const wstring& path);
    Vector2 GetSize() const { return _size; }

private:
    ComPtr<ID3D11Device> _device = nullptr;
    ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;

    Vector2 _size;
};