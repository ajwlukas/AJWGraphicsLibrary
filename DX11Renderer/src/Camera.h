#pragma once

class Camera //: public Object
{
public:
	Camera();
	~Camera();

	//virtual void Update() override;
	//virtual void Render() override;
	
	void Update() ;
	void Render() ;

	void OnResize(UINT height, UINT width);

	void Move();
	bool bMovable;

	void ScreenPointToRay(IN UINT screenX, UINT screenY, OUT Vector3& rayPos, OUT Vector3& dir);

private:
	float camMovSpeed, camRotSpeed;

private:
	struct Data
	{
		Matrix view;
		Matrix proj;
		float3 camPos;
	}viewproj;

	ID3D11Buffer* viewprojBuffer;

	Matrix view, proj;

	float fov;//½Ã¾ß°¢
	float fovInDegree;
};