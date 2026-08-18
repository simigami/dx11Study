#pragma once
#include "Material.h"
#include "Shader.h"

class Material;
class Mesh;

class MeshRenderer : public Component
{
    using Super = Component;
public:
    MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
    virtual ~MeshRenderer();

    shared_ptr<Mesh> GetMesh() const { return _mesh; }
    void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }

    shared_ptr<Material> GetMaterial() const { return _material; }
    void SetMaterial(shared_ptr<Material> material) { _material = material; }

    shared_ptr<Texture> GetTexture() const { return _material->GetTexture(); };
    void SetTexture(shared_ptr<Texture> texture) { _material->SetTexture(texture); };

    auto GetInputLayout() { return _material->GetShader()->GetInputLayout(); };
    auto GetVertexShader() { return _material->GetShader()->GetVertexShader(); };
    auto GetPixelShader() { return _material->GetShader()->GetPixelShader(); };

private:
    friend class RenderManager; // TEMP

    ComPtr<ID3D11Device> _device;
    ComPtr<ID3D11DeviceContext> _deviceContext;
    shared_ptr<Pipeline> _pipeline;

    // Mesh
    shared_ptr<Mesh> _mesh = nullptr;
    // Material
    shared_ptr<Material> _material = nullptr;
};