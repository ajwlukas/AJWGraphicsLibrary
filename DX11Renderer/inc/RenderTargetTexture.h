#pragma once

class RenderTargetTexutre
{
public:
	RenderTargetTexutre();
	~RenderTargetTexutre();

	void OnResize();
	void Resize(UINT width, UINT height);

	Resource<ID3D11Texture2D> texture;
	Resource<ID3D11ShaderResourceView> srv;
	Resource<ID3D11RenderTargetView> rtv;
};