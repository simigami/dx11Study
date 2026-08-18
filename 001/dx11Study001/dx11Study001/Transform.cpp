#include "pch.h"
#include "Transform.h"

namespace 
{
    Vector3 QuaternionToEuler(const SimpleMath::Quaternion& q) {
        Vector3 angles;

        // Roll (x-axis rotation)
        float sinr_cosp = 2.0f * (q.w * q.x + q.y * q.z);
        float cosr_cosp = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
        angles.x = std::atan2(sinr_cosp, cosr_cosp);

        // Pitch (y-axis rotation)
        float sinp = 2.0f * (q.w * q.y - q.z * q.x);
        if (std::abs(sinp) >= 1.0f)
            angles.y = std::copysign(3.14159265358979323846 / 2.0f, sinp); // Use 90 degrees if out of range
        else
            angles.y = std::asin(sinp);

        // Yaw (z-axis rotation)
        float siny_cosp = 2.0f * (q.w * q.z + q.x * q.y);
        float cosy_cosp = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
        angles.z = std::atan2(siny_cosp, cosy_cosp);

        return angles;
    }
}

Transform::Transform() : Super(ComponentType::Transform)
{
}

Transform::~Transform()
{
}

void Transform::Awake()
{
    Component::Awake();
}

void Transform::Update()
{
    Component::Update();
}

Vector3 Transform::GetWorldPosition() const
{
    return _worldPosition;
}

void Transform::SetWorldPosition(const Vector3& position)
{
    if (HasParent())
    {
        Matrix worldToParentLocalMatrix = _parent->GetWorldMatrix().Invert();
        
        Vector3 _position;
        _position.Transform(position, worldToParentLocalMatrix);
        
        SetLocalPosition(_position);
    }
    else
    {
        SetLocalPosition(position);
    }
}

Vector3 Transform::GetWorldRotation() const
{
    return _worldRotation;
}

void Transform::SetWorldRotation(const Vector3& rotation)
{
    if (HasParent())
    {
        Matrix worldToParentLocalMatrix = _parent->GetWorldMatrix().Invert();
        
        Vector3 _rotation;
        _rotation.Transform(rotation, worldToParentLocalMatrix);
        
        SetLocalRotation(_rotation);
    }
    else
    {
        SetLocalRotation(rotation);
    }
}

Vector3 Transform::GetWorldScale() const
{
    return _worldScale;   
}

void Transform::SetWorldScale(const Vector3& scale)
{
    if (HasParent())
    {
        
    }
    else
    {
        Vector3 parentScale = GetParent()->GetWorldScale();
        SetLocalScale(scale / parentScale);
    }
}

void Transform::UpdateTransform()
{
    Matrix mS = Matrix::CreateScale(_localScale);
    Matrix mR = Matrix::CreateRotationX(_localRotation.x);
    mR *= Matrix::CreateRotationY(_localRotation.y);
    mR *= Matrix::CreateRotationZ(_localRotation.z);
    Matrix mT = Matrix::CreateTranslation(_localPosition);
    
    _matLocal = mS * mR * mT;
    
    if (HasParent())
    {
        _matWorld = _matLocal * _parent->GetWorldMatrix();
    }
    else
    {
        _matWorld = _matLocal;
    }
    
    // Set Caches via Matrix
    SimpleMath::Quaternion quat;
    _matWorld.Decompose(_worldScale, quat, _worldPosition);
    _worldRotation = QuaternionToEuler(quat);

    // TODO
    for (const auto& child : _children)
    {
        child->UpdateTransform();
    }
}