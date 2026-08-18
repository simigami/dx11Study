#pragma once
#include <array>

class MeshRenderer;
class Camera;
class Animator;
class MonoBehaviour;

class GameObject : public enable_shared_from_this<GameObject>
{
public:
    GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);

    void Start();
    void Awake();
    void Update();
    void FixedUpdate();
    void LateUpdate();
    void Render(shared_ptr<Pipeline> pipeline);

    shared_ptr<Transform> GetTransform();
    shared_ptr<Transform> GetOrAddTransform();

    shared_ptr<Camera> GetCamera();
    shared_ptr<MeshRenderer> GetMeshRenderer();

    shared_ptr<Animator> GetAnimator();

    shared_ptr<Component> GetFixedComponent(ComponentType Type);

    void AddComponent(shared_ptr<Component> component);


private:
    ComPtr<ID3D11Device> _device;

// // Components
// shared_ptr<Transform> _transform = make_shared<Transform>();
protected:
    std::array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
    vector<shared_ptr<MonoBehaviour>> _scripts;
};