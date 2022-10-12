#pragma once

/// <summary>
/// 카메라의 x, z 좌표를 따라다니는 2차원 물체,
/// 쉐이더에서 공식을 통해 pos.x % 10 ==0, pos.y % 10 == 0, 일때 픽셀을 칠해주는 식으로 구현
/// 
/// written by Ssreppa 22.06.22
/// </summary>

class Camera;

class Grid : public Object
{
public:
	Grid(Camera* camera);

	virtual void Update() override;
	virtual void Render() override;

private:
	void CreateGrid();

	Camera* cam;
};