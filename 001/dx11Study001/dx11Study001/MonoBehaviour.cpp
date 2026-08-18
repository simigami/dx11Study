#include "pch.h"
#include "MonoBehaviour.h"

MonoBehaviour::MonoBehaviour() : Super(ComponentType::Script)
{
}

MonoBehaviour::~MonoBehaviour()
{
}

void MonoBehaviour::Awake()
{
    Component::Awake();
}

void MonoBehaviour::Start()
{
    Component::Start();
}

void MonoBehaviour::Update()
{
    Component::Update();
}

void MonoBehaviour::FixedUpdate()
{
    Component::FixedUpdate();
}

void MonoBehaviour::LateUpdate()
{
    Component::LateUpdate();
}