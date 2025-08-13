
struct VS_INPUT
{
    float4 position : POSITION;
    //float4 color : COLOR;
    
    // uv 사용
    float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    //float4 color : COLOR;
    
    float2 uv : TEXCOORD;
};

// IA - VS - RS - PS - OM
VS_OUTPUT VS(VS_INPUT input)
{
    // 좌표 변환, 애니메이션 등의 역할이 여기에서 수행되게 된다
    VS_OUTPUT output;
    output.position = input.position;
    output.uv = input.uv;

    return output;
}

// 텍스처와 샘플러 정의
Texture2D texture0 : register(t0);
Texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color = texture0.Sample(sampler0, input.uv);
    
// 레스터 과정 이후 나오게 된 픽셀 정보를 최종 후처리 하게 된다
    return color;
}