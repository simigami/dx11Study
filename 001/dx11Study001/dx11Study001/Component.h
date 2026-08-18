#pragma once

class Transform;
class GameObject;

enum class ComponentType : uint8
{
    Transform               = 0,
    MeshRenderer,
    Camera,
    Animator,
    Script,
    //...
    End,
};

enum
{
    FIXED_COMPONENT_COUNT = static_cast<uint8>(ComponentType::End),
};

class Component
{
public:
    Component(ComponentType type);;
    ~Component();

    virtual void Start();
    virtual void Awake();;
    virtual void Update();;
    virtual void FixedUpdate();;
    virtual void LateUpdate();;

    ComponentType GetType() { return _type; };

    shared_ptr<GameObject> GetGameObject();
    shared_ptr<Transform> GetTransform();

private:
    friend class GameObject;
    void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject;; };

protected:
    // shared? weaK?
    ComponentType _type;
    weak_ptr<GameObject> _gameObject;
};