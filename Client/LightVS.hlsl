cbuffer CameraBuffer : register(b0)
{
    float4x4 view;
    float4x4 proj;
    float3 camPos;
}

cbuffer World : register(b1)
{
    float4x4 world;
};

///버텍스용
float4 LocalToWorld(float3 localPos)//로컬 포지션을 월드로
{
    return mul(world, float4(localPos, 1.0f));
}

float4 WorldToNDC(float4 worldPos)
{
    float4 ret = mul(view, worldPos);
    ret = mul(proj, ret);
    
    return ret;
}
float4 LocalToNDC(float3 localPos)//로컬 포지션을 월드로
{
    float4 ret = LocalToWorld(localPos);
    ret = WorldToNDC(ret);
    
    return ret;
}

///벡터용
float3 LocalToWorldDirOnly(float3 localDir)//로컬 포지션을 월드로
{
    return mul((float3x3) world, localDir);
}

float3 WorldToNDCDirOnly(float3 worldDir)
{
    float3 ret = mul((float3x3) view, worldDir);
    ret = mul((float3x3) proj, ret);
    
    return ret;
}

float3 LocalToNDCDirOnly(float3 localDir)//로컬 포지션을 월드로
{
    float3 ret = LocalToWorldDirOnly(localDir);
    ret = WorldToNDCDirOnly(ret);
    
    return ret;
}

struct VSin
{
    float3 pos : POSITION;
};

struct VSout
{
    float4 pos : SV_POSITION;
};

VSout main(VSin input)
{
    VSout output;
    
    output.pos = LocalToNDC(input.pos);
    
    return output;
}
