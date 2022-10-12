#include "pch_common.h"
#include "JWMath.h"

#include <math.h>

using namespace JWMath;

void JWMath::QuatToEuler(OUT float& eX, OUT float& eY, OUT float& eZ, IN float&& qX, IN float&& qY, IN float&& qZ, IN float&& qW)
{
	float _sqx = qX * qX;
	float _sqy = qY * qY;
	float _sqz = qZ * qZ;
	float _sqw = qW * qW;

	float temp = 2.0f * (qW * qX - qY * qZ);

	temp = temp < -1 ? -1 : temp;
	temp = temp > 1 ? 1 : temp;

	eX = asinf(temp);

	eY = atan2f(2.0f * (qX * qZ + qW * qY), (-_sqx - _sqy + _sqz + _sqw));

	eZ = atan2f(2.0f * (qX * qY + qZ * qW), (-_sqx + _sqy - _sqz + _sqw));
}
