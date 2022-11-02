
struct VSin
{
    float2 pos : POSITION;
};

struct VSout
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

cbuffer Color : register(b0)
{
    float4 color;
}

VSout main(VSin input)
{
    VSout output;
    
    output.pos = float4(input.pos, 0, 1);
    
    output.color = color;
    
    return output;
}
