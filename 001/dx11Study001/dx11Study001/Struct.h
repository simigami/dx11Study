#pragma once
#include "Types.h"


struct Vertex
{
	Vector3 position;
	//Color color;

	// 0~1 사이의 2차원 값 정의
	// 텍스처가 전체 렌더링에 차지할 xy 비율 값이 들어간다
	Vector2 uv;
};