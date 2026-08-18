#include "pch.h"
#include "SceneManager.h"

#include "Animator.h"
#include "Mesh.h"
#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "Scene.h"

SceneManager::SceneManager(shared_ptr<Graphics> graphics)
    : _graphics(graphics)
{
}

void SceneManager::Init()
{
    if (_activeScene == nullptr)
    {
        return;
    }

    _activeScene->Awake();
    _activeScene->Start();
}

void SceneManager::Update()
{
    if (_activeScene == nullptr)
    {
        return;
    }

    _activeScene->Update();
    _activeScene->LateUpdate();

    _activeScene->FixedUpdate();
}

void SceneManager::LoadScene(wstring sceneName)
{
    // TODO

    // TEST
    _activeScene =  LoadTestScene();
    Init();
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
    shared_ptr<Scene> scene = make_shared<Scene>();

    // TODO
    shared_ptr<GameObject> _camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
    {
        _camera->GetOrAddTransform();
        _camera->AddComponent(make_shared<Camera>());
        // _camera->AddComponent(make_shared<CameraMove>());

        scene->AddGameObject(_camera);
    }

    const int32 MAX_SPAWN = 10;
    for (int32 i = 0; i < MAX_SPAWN; ++i)
    {
        const float RandomPositionX = (float)rand() / (float)RAND_MAX * 1024.f - 512.f;
        const float RandomPositionY = (float)rand() / (float)RAND_MAX * 768.f - 384.f;
        const float RandomPositionZ = (float)rand() / (float)RAND_MAX * 200.f - 100.f;

        shared_ptr<GameObject> monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
        monster->GetOrAddTransform()->SetLocalScale(Vector3(100.f, 100.f, 1.f));
        monster->GetOrAddTransform()->SetLocalPosition(Vector3(RandomPositionX, RandomPositionY, RandomPositionZ));
        {
            auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
            monster->AddComponent(meshRenderer);

            auto material = RESOURCES->Get<Material>(L"Default");
            meshRenderer->SetMaterial(material);

            auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
            meshRenderer->SetMesh(mesh);
        }
        {
            auto animator = make_shared<Animator>();
            monster->AddComponent(animator);
            auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
            animator->SetAnimation(anim);
        }

        scene->AddGameObject(monster);
    }

    return scene;
}