#pragma once

// struct VertexTextureData
// {
// 	Vector3 position = {0, 0, 0};
// 	Vector2 uv = {0, 0};
//
// 	std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
// };
//
// struct VertexColorData
// {
// 	Vector3 position = {0, 0, 0};
// 	Color color = {0, 0, 0, 0};
//
// 	std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
// };

struct TransformData
{
    Matrix matWorld = Matrix::Identity;
};

struct CameraData
{
    Matrix matView = Matrix::Identity;
    Matrix matProjection = Matrix::Identity;
};

struct AnimationData
{
    // 16바이트 맞춰줘야 함 -> 왜?
    Vector2 spriteOffset;
    Vector2 spriteSize;
    Vector2 textureSize;
    float useAnimation;
    float padding;
};

class RenderHelper
{
public:
    
};