cbuffer ConstantBuffer  : register(b1)
{
    float4 color;
};

float4 main() : SV_TARGET
{
    return color;
}