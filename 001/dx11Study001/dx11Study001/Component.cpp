#include "pch.h"
#include "Component.h"

#include "GameObject.h"

Component::Component(ComponentType type) : _type(type)
{
}

Component::~Component()
{
}

void Component::Start()
{

}

void Component::Awake()
{

}

void Component::Update()
{

}

void Component::FixedUpdate()
{

}

void Component::LateUpdate()
{

}

shared_ptr<GameObject> Component::GetGameObject()
{
    return _gameObject.lock();
}

shared_ptr<Transform> Component::GetTransform()
{
    if (!GetGameObject())
    {
        return nullptr;
    }

    return GetGameObject()->GetTransform();
}