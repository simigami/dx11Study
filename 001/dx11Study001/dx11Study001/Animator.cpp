#include "pch.h"
#include "Animator.h"

#include "Animation.h"
#include "Game.h"
#include "TimeManager.h"

Animator::Animator() : Super(ComponentType::Animator)
{
}

Animator::~Animator()
{
}

void Animator::Init()
{
}

void Animator::Update()
{
    shared_ptr<Animation> anim = GetCurrentAnimation();
    if (anim == nullptr)
    {
        return;
    }

    const Keyframe& frame = anim->GetKeyframe(_currentKeyframeIdx);
    float deltaTime = TIME->GetDeltaTime();
    _sumTime += deltaTime;

    if (_sumTime >= frame.time)
    {
        _currentKeyframeIdx++;
        int32 totalCount = anim->GetKeyframeCount();

        if (_currentKeyframeIdx >= totalCount)
        {
            if (anim->IsLoop())
            {
                _currentKeyframeIdx = 0;
            }
            else
            {
                _currentKeyframeIdx = totalCount - 1;
            }
        }

        _sumTime = 0.f;
    }
    Component::Update();
}

const Keyframe& Animator::GetCurrentKeyframe()
{
    return _currentAnimation->GetKeyframe(_currentKeyframeIdx);
}