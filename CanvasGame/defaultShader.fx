//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
	float4 LightColour;
	float4 LightPosition;
	float4 CameraPosition;
	float4 Colour;
	//float4 Time;
}

//cbuffer ConstantBufferUniform : register (b1)
//{
//	float4 LightPosition[5];
//	float4 LightColour[5];
//	uint4 NumberOfLights;
//}

//Texture2D txDiffuse : register(t0);

//SamplerState txSampler : register(s0);

//--------------------------------------------------------------------------------------
// Shader Inputs
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float3 Pos : POSITION;
	float3 Normal : NORMAL;
	//float3 Tangent : TANGENT;
	//float3 Binormal : BINORMAL;
	float2 TexCoord : TEXCOORD0;
	//float3 InstancePos : INSTANCEPOS;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float3 Normal: NORMAL;
	float4 PosWorld : TEXCOORD0;
	//float2 TexCoord : TEXCOORD1;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = mul(float4(input.Pos, 1.0f), World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.Normal = mul(World, float4(input.Normal, 1.0f)).xyz;
	output.Normal = normalize(output.Normal);
	output.PosWorld = mul(float4(input.Pos, 1.0f), World);
	//output.TexCoord = float2(1,1);

	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	float4 matDiffuse = float4(0.8, 0.8, 0.8, 1.0);
	float4 matSpec = float4(1.0, 1.0, 1.0, 1.0);
	float4 ambient = float4(0.5, 0.5, 0.5, 1.0);

	//float4 texColour = txDiffuse.Sample(txSampler, input.TexCoord);
	float3 viewDirection = normalize(CameraPosition - input.PosWorld).xyz;
	float4 light = ambient;

	//for (int i = 0; i < NumberOfLights.x; ++i)
	//{
		float3 lightDir = normalize(LightPosition - input.PosWorld).xyz;
		float diffuse = max(0.0, dot(lightDir, input.Normal));
		float3 R = normalize(reflect(-lightDir, input.Normal));
		float spec = pow(max(0.0, dot(viewDirection, R)), 50);
		light += saturate(((matDiffuse*diffuse) + (matSpec*spec)) * LightColour);
	//}

	return  light * Colour;
}
