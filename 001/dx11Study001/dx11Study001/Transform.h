#pragma once
#include "Component.h"

class Transform : public Component
{
    using Super = Component;
public:
    Transform();
    ~Transform();
    
    void Awake() override;
    void Update() override;
    
    bool HasParent() const { return _parent != nullptr; }
    shared_ptr<Transform> GetParent() const { return _parent; }
    void SetParent(shared_ptr<Transform> parent) { _parent = parent; }
    
    const vector<shared_ptr<Transform>>& GetChildren() const { return _children; }
    void AddChild(shared_ptr<Transform> child) { _children.push_back(child); }
    shared_ptr<Transform> GetChildren(const size_t index) const { return _children[index]; };

    // Local Functions
    Vector3 GetLocalPosition() const { return _localPosition; }
    void SetLocalPosition(const Vector3& position) { _localPosition = position; UpdateTransform(); }
    
    Vector3 GetLocalRotation() const { return _localRotation; }
    void SetLocalRotation(const Vector3& rotation) { _localRotation = rotation; UpdateTransform();}
    
    Vector3 GetLocalScale() const { return _localScale; }
    void SetLocalScale(const Vector3& scale) { _localScale = scale; UpdateTransform(); }

    // World Transform Functions
    Vector3 GetWorldPosition() const;
    void SetWorldPosition(const Vector3& position);

    Vector3 GetLook() { return _matWorld.Backward();};
    Vector3 GetUp() { return _matWorld.Up(); };
    Vector3 GetRight() { return _matWorld.Right(); };

    Vector3 GetWorldRotation() const;
    void SetWorldRotation(const Vector3& rotation);
    
    Vector3 GetWorldScale() const;
    void SetWorldScale(const Vector3& scale);
    
    Matrix GetLocalMatrix() const { return _matLocal; };
    Matrix GetWorldMatrix() const { return _matWorld; };
    
    void UpdateTransform();
    
private:
    // SRT
    Vector3 _localPosition = {0.f, 0.f, 0.f,};
    Vector3 _localRotation = {0.f, 0.f, 0.f,};
    Vector3 _localScale = {.1, .1f, .1f,};
    
    // Cache
    Vector3 _worldPosition = {0.f, 0.f, 0.f,};
    Vector3 _worldRotation = {0.f, 0.f, 0.f,};
    Vector3 _worldScale = {.1, .1f, .1f,};
    
    // Matrix
    Matrix _matLocal = Matrix::Identity;
    Matrix _matWorld = Matrix::Identity;
    
private:
    shared_ptr<Transform> _parent;
    vector<shared_ptr<Transform>> _children;
};