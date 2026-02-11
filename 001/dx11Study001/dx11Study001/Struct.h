#pragma once

#include "Types.h"

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
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};