

cbuffer World : register(b0)
{
	float4x4 world;
};

struct VSInput
{
	float dummy : DUMMY;
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PSInput
{
	float4 position : POSITION;
	float4 color : COLOR;
};

PSInput VS(VSInput input)
{
	PSInput output;
	
	output.position = input.position;
	output.color = input.
	color;
	
	return
	output;
}
