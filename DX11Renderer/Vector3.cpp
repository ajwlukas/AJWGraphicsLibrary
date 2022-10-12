#include "pch_dx_11.h"
#include "Vector3.h"

Vector3::Vector3(float x, float y, float z, float w)
{
	data.x = x;
	data.y = y;
	data.z = z;
	data.w = w;
}

Vector3::~Vector3()
{
}

Vector3::Vector3(const XMVECTOR& other)
{
		this->data.x = other.m128_f32[0];
		this->data.y = other.m128_f32[1];
		this->data.z = other.m128_f32[2];
		this->data.w = other.m128_f32[3];
}

Vector3::Vector3(const Vector3& other)
{
	this->data.x = other.data.x;
	this->data.y = other.data.y;
	this->data.z = other.data.z;
	this->data.w = other.data.w;
}

Vector3::Vector3(const float3& other)
{
	this->data.x = other.x;
	this->data.y = other.y;
	this->data.z = other.z;
	this->data.w = 1.0f;
}

const float Vector3::Dot(const Vector3& a, const Vector3& b)
{
	return a.data.x * b.data.x + a.data.y * b.data.y + a.data.z * b.data.z;
}

const Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
	return Vector3(a.data.y * b.data.z - a.data.z * b.data.y, a.data.z * b.data.x - a.data.x * b.data.z, a.data.x * b.data.y - a.data.y * b.data.x);
}

 Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3({this->data.x + other.data.x, this->data.y + other.data.y, this->data.z + other.data.z});
}

 Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3({ this->data.x - other.data.x, this->data.y - other.data.y, this->data.z - other.data.z });
}

 Vector3 Vector3::operator*(const float& multiplier) const
{
	return Vector3({ this->data.x * multiplier, this->data.y * multiplier, this->data.z * multiplier });
}

 Vector3 Vector3::operator/(const float& divider) const
{
	return Vector3({ this->data.x / divider, this->data.y / divider, this->data.z / divider });
}

void Vector3::operator+=(const Vector3& other)
{
	this->data.x += other.data.x;
	this->data.y += other.data.y;
	this->data.z += other.data.z;
}

void Vector3::operator-=(const Vector3& other)
{
	this->data.x -= other.data.x;
	this->data.y -= other.data.y;
	this->data.z -= other.data.z;
}

void Vector3::operator*=(const float& multiplier)
{
	this->data.x *= multiplier;
	this->data.y *= multiplier;
	this->data.z *= multiplier;
}

void Vector3::operator/=(const float& divider)
{
	this->data.x /= divider;
	this->data.y /= divider;
	this->data.z /= divider;
}

const Vector3 Vector3::operator*(const XMMATRIX& matrix) const
{
	Vector3 ret;
	XMStoreFloat4(&ret.data,XMVector4Transform(XMLoadFloat4(&data), matrix));


	return ret;
}

void Vector3::operator*=(const XMMATRIX& matrix)
{
	XMStoreFloat4(&data, XMVector4Transform(XMLoadFloat4(&data), matrix));
}

void Vector3::Normalize()
{
	float len = Length();

	this->data.x /= len;
	this->data.y /= len;
	this->data.z /= len;
}

const Vector3 Vector3::Normalized()
{
	float len = Length();

	return Vector3(this->data.x / len,	this->data.y / len, this->data.z / len);
}

float Vector3::Length()
{
	return sqrtf(this->data.x * this->data.x + this->data.y * this->data.y + this->data.z * this->data.z);
}
