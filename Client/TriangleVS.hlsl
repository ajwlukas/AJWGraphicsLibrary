
struct VSin
{
    float2 pos : POSITION;
};

struct VSout
{
    float4 pos : SV_POSITION;
};

VSout main(VSin input) : SV_POSITION
{
    VSout output;
    
    output.pos = float4(input.pos, 0, 1);
    
    return output;
}
