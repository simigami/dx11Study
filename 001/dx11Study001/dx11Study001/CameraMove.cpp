#include "pch.h"
#include "CameraMove.h"

void CameraMove::Update()
{
    MonoBehaviour::Update();

    auto pos = GetTransform()->GetLocalPosition();
    pos.x += 0.1f;
    GetTransform()->SetLocalPosition(pos);
}