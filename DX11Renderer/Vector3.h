#pragma once

#include "pch_dx_11.h"
#include "DXTK/SimpleMath.h"

class Vector3
{
public:
	Vector3(float x = 0, float y = 0, float z = 0, float w = 1.0f);
	~Vector3();

	operator const float3 () const { return float3(data.x,data.y,data.z); }
	//operator const float3* () const { return &data; }

	operator const float4&() const { return data; }
	operator float4*() { return &data; }
	operator const XMVECTOR() const { return XMLoadFloat4(&data); }
	operator SimpleMath::Vector3() { return XMLoadFloat4(&data); }
	//operator XMVECTOR() { return XMLoadFloat4(&data); }

	Vector3(const XMVECTOR& other);
	Vector3(const Vector3& other);
	Vector3(const float3& other);

	//Vector3& operator= (const Vector3& other);

public:
	float& GetX() { return data.x; }
	float& GetY() { return data.y; }
	float& GetZ() { return data.z; }
	float& GetW() { return data.w; }

	void SetX(float x) { data.x = x; }
	void SetY(float y) { data.y = y; }
	void SetZ(float z) { data.z = z; }
	void SetW(float w) { data.w = w; }

	__declspec(property(get = GetX, put = SetX)) float x;
	__declspec(property(get = GetY, put = SetY)) float y;
	__declspec(property(get = GetZ, put = SetZ)) float z;
	__declspec(property(get = GetW, put = SetW)) float w;

	float4 data;
public:
	//const Vector3 operator=(const Vector3& other) { this->data = other.data; };

	static const float Dot(const Vector3& a,const Vector3& b);//order doesn't matter
	static const Vector3 Cross(const Vector3& a,const Vector3& b);//order does matter

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(const float& multiplier) const;
	Vector3 operator/(const float& divider) const;

	void operator+=(const Vector3& other);
	void operator-=(const Vector3& other);
	void operator*=(const float& multiplier);
	void operator/=(const float& divider);

	const Vector3 operator*(const XMMATRIX& matrix) const;
	void operator*=(const XMMATRIX& matrix);

	void Normalize();//doesn't change data
	const Vector3 Normalized();//does change data

	float Length();
};