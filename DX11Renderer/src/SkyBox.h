#pragma once

class Part;
class Camera;

class Skybox : public Object
{
public:
	Skybox(Camera* camera);

	virtual void Update() override;
	virtual void Render() override;

private:
	void CreateSkyBox();
	void CreateRasterState();
	void CreateDepthStencilState();

	Camera* cam;

	Resource<ID3D11RasterizerState> rasterizerState;
	Resource<ID3D11RasterizerState> defaultRasterizerState;//다시 돌려줄 용도
	Resource<ID3D11DepthStencilState> depthStencilState;
	Resource<ID3D11DepthStencilState> defaultDepthStencilState;//다시 돌려줄 용도


	Resource<ID3D11ShaderResourceView> srvSkyBox;
};