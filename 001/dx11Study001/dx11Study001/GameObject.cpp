#include "pch.h"
#include "GameObject.h"

#include "Animator.h"
#include "Camera.h"
#include "Component.h"
#include "MeshRenderer.h"
#include "MonoBehaviour.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
    : _device(device)
{
}

void GameObject::Start()
{
    for (const shared_ptr<Component> c : _components)
    {
        if (c)
           c->Start();
    }

    for (const shared_ptr<MonoBehaviour> script : _scripts)
    {
        script->Start();
    }
}

void GameObject::Awake()
{
    for (const shared_ptr<Component> c : _components)
    {
        if (c)
            c->Awake();
    }

    for (const shared_ptr<MonoBehaviour> script : _scripts)
    {
        script->Awake();
    }
}

void GameObject::FixedUpdate()
{
    for (const shared_ptr<Component> c : _components)
    {
        if (c)
            c->FixedUpdate();
    }

    for (const shared_ptr<MonoBehaviour> script : _scripts)
    {
        script->FixedUpdate();
    }
}

void GameObject::LateUpdate()
{
    for (const shared_ptr<Component> c : _components)
    {
        if (c)
            c->LateUpdate();
    }

    for (const shared_ptr<MonoBehaviour> script : _scripts)
    {
        script->LateUpdate();
    }
}

void GameObject::Update()
{
    for (const shared_ptr<Component> c : _components)
    {
        if (c)
            c->Update();
    }

    for (const shared_ptr<MonoBehaviour> script : _scripts)
    {
        script->Update();
    }

    // TEMP
    if (GetCamera())
    {
        return;
    }
}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
{

}

shared_ptr<Transform> GameObject::GetTransform()
{
    shared_ptr<Component> component = GetFixedComponent(ComponentType::Transform);
    return static_pointer_cast<Transform>(component);
}

shared_ptr<Transform> GameObject::GetOrAddTransform()
{
    if (!GetTransform())
    {
        auto transform = make_shared<Transform>();
        AddComponent(transform);
    }

    return GetTransform();
}

shared_ptr<Camera> GameObject::GetCamera()
{
    shared_ptr<Component> component = GetFixedComponent(ComponentType::Camera);
    return static_pointer_cast<Camera>(component);
}

shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
    shared_ptr<Component> component = GetFixedComponent(ComponentType::MeshRenderer);
    return static_pointer_cast<MeshRenderer>(component);
}

shared_ptr<Animator> GameObject::GetAnimator()
{
    shared_ptr<Component> component = GetFixedComponent(ComponentType::Animator);
    return static_pointer_cast<Animator>(component);
}

shared_ptr<Component> GameObject::GetFixedComponent(ComponentType Type)
{
    const uint8 index = static_cast<uint8>(Type);
    assert(index < FIXED_COMPONENT_COUNT);
    return _components[index];
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
}