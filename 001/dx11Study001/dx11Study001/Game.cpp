#include "pch.h"
#include "Game.h"

#include "GameObject.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
    _graphics = make_shared<Graphics>(hwnd);
    _pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());

    // GO
    _gameObject = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
}

void Game::Update()
{
    // GO
    _gameObject->Update();
}

void Game::Render()
{
    _graphics->RenderBegin();
    
    {
        // GO
        if (_gameObject) 
        {
            _gameObject->Render(_pipeline);
        }
    }
    
    _graphics->RenderEnd();
}