#pragma once


namespace JWMath
{
	//혜성이의 코드 쿼터니언에서, 오일러각 뽑는 함수
	
	void QuatToEuler(OUT float& eX, OUT float& eY, OUT float& eZ, IN float&& qX, IN float&& qY, IN float&& qZ, IN float&& qW);

}