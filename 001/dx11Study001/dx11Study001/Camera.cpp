#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera)
{
}

Camera::~Camera()
{
}

void Camera::Awake()
{
    Component::Awake();
}

void Camera::Start()
{
    Component::Start();
}

void Camera::FixedUpdate()
{
    Component::FixedUpdate();
}

void Camera::LateUpdate()
{
    Component::LateUpdate();
}

void Camera::Update()
{
    Component::Update();
    UpdateMatrix();
}

void Camera::UpdateMatrix()
{
    Vector3 eyePosition = GetTransform()->GetLocalPosition();
    Vector3 focusPosition = eyePosition + GetTransform()->GetLook();
    Vector3 upDirection = GetTransform()->GetUp();
    S_MatView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

    // S_MatView = GetTransform()->GetWorldMatrix().Invert();

    if (GetMode() == CameraMode::Perspective)
    {
        S_MatProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);
    }
    else
    {
        S_MatProjection = ::XMMatrixOrthographicLH(800.f, 600.f, 0.f, 1.f);
    }
}