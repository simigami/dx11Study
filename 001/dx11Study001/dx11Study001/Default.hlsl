
struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

// IA - VS - RS - PS - OM
VS_OUTPUT VS(VS_INPUT input)
{
    // 좌표 변환, 애니메이션 등의 역할이 여기에서 수행되게 된다
    VS_OUTPUT output;
    output.position = input.position;
    output.color = input.color;

    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    // 레스터 과정 이후 나오게 된 픽셀 정보를 최종 후처리 하게 된다
    return input.color;
}