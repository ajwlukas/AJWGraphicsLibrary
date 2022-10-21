struct PSInput
{
	float4 position : POSITION;
	float4 color : COLOR;
};


float4 PS(PSInput input) : SV_Target
{
	
	return input.color;
}