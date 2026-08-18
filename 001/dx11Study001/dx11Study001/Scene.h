#pragma once

class Scene
{
public:
    void Start();
    void Awake();
    void Update();
    void FixedUpdate();
    void LateUpdate();

public:
    void AddGameObject(shared_ptr<GameObject> gameObject);
    void RemoveGameObject(shared_ptr<GameObject> gameObject);

    const vector<shared_ptr<GameObject>>& GetGameObjects() const { return _gameObjects; };

private:
    vector<shared_ptr<GameObject>> _gameObjects;
};