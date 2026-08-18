#include "pch.h"
#include "Scene.h"

#include "GameObject.h"

void Scene::Start()
{
    for (const shared_ptr<GameObject> GO : _gameObjects)
    {
        GO->Start();
    }
}

void Scene::Awake()
{
    for (const shared_ptr<GameObject> GO : _gameObjects)
    {
        GO->Awake();
    }
}

void Scene::Update()
{
    for (const shared_ptr<GameObject> GO : _gameObjects)
    {
        GO->Update();
    }
}

void Scene::FixedUpdate()
{
    for (const shared_ptr<GameObject> GO : _gameObjects)
    {
        GO->FixedUpdate();
    }
}

void Scene::LateUpdate()
{
    for (const shared_ptr<GameObject> GO : _gameObjects)
    {
        GO->LateUpdate();
    }
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
    _gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
    _gameObjects.erase(std::remove(_gameObjects.begin(), _gameObjects.end(), gameObject), _gameObjects.end());
}