#pragma once
#include "Types.h"
#include "Struct.h"
#include "Values.h"

// STL
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

using namespace std;

// WIN
#include <Windows.h>
#include <assert.h>

// UTILS
#include "tinyxml2.h"
using namespace tinyxml2;

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>

using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectxTex_Debug.lib")
#else
#pragma comment(lib, "DirectXTex\\DirectxTex.lib")
#endif // _DEBUG

#define CHECK(p) assert(SUCCEEDED(p));

#define         GAME                GGame
#define         SCENE              GAME->GetSceneManager()
#define         INPUT               GAME->GetInputManager()
#define         TIME                GAME->GetTimeManager()
#define         RESOURCES   GAME->GetResourceManager()
#define         RENDER        GAME->GetRenderManager()

#include "Graphics.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "VertexBuffer.h"
#include "Geometry.h"
#include "GeometryHelper.h"
#include "VertexData.h"
#include "ShaderBase.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "SamplerState.h"
#include "Pipeline.h"
#include "Transform.h"