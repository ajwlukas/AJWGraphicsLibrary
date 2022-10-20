
struct VSout
{
    float4 pos : SV_POSITION;
};

float4 PS(VSout input) : SV_TARGET
{
    float4 output = { 1, 1, 1, 1 };
    
    
    return output;
}