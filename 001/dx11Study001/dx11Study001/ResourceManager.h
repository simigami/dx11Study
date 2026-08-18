#pragma once
#include <array>

#include "Animation.h"
#include "Material.h"
#include "Mesh.h"
#include "ResourceBase.h"
#include "Shader.h"
#include "Texture.h"

class ResourceManager
{
    DECLARE_SINGLE(ResourceManager);

public:
    ResourceManager(ComPtr<ID3D11Device> device);

    void Init();

    template<typename T>
    shared_ptr<T> Load(const wstring& key, const wstring& path);

    template<typename T>
    bool Add(const wstring& key, shared_ptr<T> obj);

    template<typename T>
    shared_ptr<T> Get(const wstring& key);

    template<typename T>
    ResourceType GetResourceType();

private:
    ComPtr<ID3D11Device> _device;

    using KeyObjMap = map<wstring/*key*/, shared_ptr<ResourceBase>>;
    array<KeyObjMap, RESOURCE_TYPE_COUNT> _resources;

private:
    void CreateDefaultTexture();
    void CreateDefaultMesh();
    void CreateDefaultMaterial();
    void CreateDefaultAnimation();
    void CreateDefaultShader();
};

template <typename T>
shared_ptr<T> ResourceManager::Load(const wstring& key, const wstring& path)
{
    ResourceType resourceType = GetResourceType<T>();
    KeyObjMap& keyObjMap = _resources[static_cast<uint8>(resourceType)];

    auto findIt = keyObjMap.find(key);
    if (findIt != keyObjMap.end())
    {
        return static_pointer_cast<T>(findIt->second);
    }

    shared_ptr<T> obj = make_shared<T>();
    obj->Load(path);
    keyObjMap[key] = obj;

    return obj;
}

template <typename T>
bool ResourceManager::Add(const wstring& key, shared_ptr<T> obj)
{
    ResourceType resourceType = GetResourceType<T>();
    KeyObjMap& keyObjMap = _resources[static_cast<uint8>(resourceType)];

    auto findIt = keyObjMap.find(key);
    if (findIt != keyObjMap.end())
    {
        return false;
    }

    keyObjMap[key] = obj;
    return true;
}

template <typename T>
shared_ptr<T> ResourceManager::Get(const wstring& key)
{
    ResourceType resourceType = GetResourceType<T>();
    KeyObjMap& keyObjMap = _resources[static_cast<uint8>(resourceType)];

    auto findIt = keyObjMap.find(key);
    if (findIt != keyObjMap.end())
    {
        return static_pointer_cast<T>(findIt->second);
    }

    return nullptr;
}

template <typename T>
ResourceType ResourceManager::GetResourceType()
{
    if (std::is_same_v<T, Texture>)
    {
        return ResourceType::Texture;
    }
    if (std::is_same_v<T, Mesh>)
    {
        return ResourceType::Mesh;
    }
    if (std::is_same_v<T, Material>)
    {
        return ResourceType::Material;
    }
    if (std::is_same_v<T, Animation>)
    {
        return ResourceType::Animation;
    }
    if (std::is_same_v<T, Shader>)
    {
        return ResourceType::Shader;
    }

    assert(false);
    return ResourceType::None;
}
