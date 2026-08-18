#pragma once

class Scene;

class SceneManager
{
public:
    SceneManager(shared_ptr<Graphics> graphics);

    void Init();
    void Update();

public:
    shared_ptr<Scene> GetActiveScene() { return _activeScene; };
    void LoadScene(wstring sceneName);

private:
    shared_ptr<Scene> LoadTestScene();

private:
    shared_ptr<Graphics> _graphics;

private:
    shared_ptr<Scene> _activeScene;
};