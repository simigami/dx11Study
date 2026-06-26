#pragma once

class Texture
{
public:
    Texture(ComPtr<ID3D11Device> device);

    ~Texture();

    ComPtr<ID3D11ShaderResourceView> GetComPtr();

    void Create(const wstring& path);
    
private:
    ComPtr<ID3D11Device> _device = nullptr;
    ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;
};
