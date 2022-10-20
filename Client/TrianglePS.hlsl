
struct VSout
{
    float4 pos : SV_POSITION;
};

float4 main(VSout input) : SV_Target
{
    float4 output = { 1, 1, 1, 1 };
    
    
    return output;
}