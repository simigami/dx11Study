#pragma once

class GameObject;

class Component
{
public:
    Component();;
    ~Component();
    
    virtual void Init() abstract;
    virtual void Update() abstract;
    
    shared_ptr<GameObject> GetGameObject() { return _owner; }
    
protected:
    // shared? weaK?
    shared_ptr<GameObject> _owner;
};
