
struct VSin
{
    float2 pos : POSITION;
};

struct VSout
{
    float4 pos : SV_POSITION;
};

VSout VS(VSin input) : SV_POSITION
{
    VSout output;
    
    output.pos = float4(input.pos, 0, 1);
    
    return output;
}

float4 PS(VSout input) : SV_TARGET
{
    float4 output = { 1, 1, 1, 1 };
    
    
    return output;
}