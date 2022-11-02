
struct VSout
{
    float4 pos : SV_POSITION;
};

float4 main(VSout input) : SV_Target
{
    
    return float4(0, 1, 0, 1);
}