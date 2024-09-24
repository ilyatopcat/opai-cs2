#pragma once

#include "../imgui/imgui.h"

#include <cmath>

class Vector4D
{
public:
	float x, y, z, w;

	Vector4D(float _x = 0, float _y = 0, float _z = 0, float _w = 0) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	Vector4D& operator+=(const Vector4D& v)
	{
		x += v.x; y += v.y; z += v.z; w += v.w;
		return *this;
	}

	Vector4D& operator-=(const Vector4D& v)
	{
		x -= v.x; y -= v.y; z -= v.z; w -= v.w;
		return *this;
	}

	Vector4D& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		z *= fl;
		w *= fl;
		return *this;
	}

	Vector4D& operator*=(const Vector4D& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}

	Vector4D& operator/=(const Vector4D& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}

	Vector4D& operator+=(float fl)
	{
		x += fl;
		y += fl;
		z += fl;
		w += fl;
		return *this;
	}

	Vector4D& operator/=(float fl)
	{
		x /= fl;
		y /= fl;
		z /= fl;
		w /= fl;
		return *this;
	}
	Vector4D& operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		z -= fl;
		w -= fl;
		return *this;
	}
};

class Vector2D {
public:
	float x, y;

	Vector2D(float _x = 0, float _y = 0, float _z = 0) {
		x = _x;
		y = _y;
	}

	Vector2D operator+(Vector2D vec) {
		return Vector2D(x + vec.x, y + vec.y);
	}

	Vector2D operator+(float n) {
		return Vector2D(x + n, y + n);
	}

	Vector2D operator+=(Vector2D vec) {
		x += vec.x;
		y += vec.y;

		return *this;
	}

	Vector2D operator+=(float n) {
		x += n;
		y += n;

		return *this;
	}

	Vector2D operator-(Vector2D vec) {
		return Vector2D(x - vec.x, y - vec.y);
	}

	Vector2D operator-(float n) {
		return Vector2D(x - n, y - n);
	}

	Vector2D operator-=(Vector2D vec) {
		x -= vec.x;
		y -= vec.y;

		return *this;
	}

	Vector2D operator-=(float n) {
		x -= n;
		y -= n;

		return *this;
	}

	Vector2D operator/(Vector2D vec) {
		return Vector2D(x / vec.x, y / vec.y);
	}

	Vector2D operator/(float n) {
		return Vector2D(x / n, y / n);
	}

	Vector2D operator/=(Vector2D vec) {
		x /= vec.x;
		y /= vec.y;

		return *this;
	}

	Vector2D operator/=(float n) {
		x /= n;
		y /= n;

		return *this;
	}

	Vector2D operator*(Vector2D vec) {
		return Vector2D(x * vec.x, y * vec.y);
	}

	Vector2D operator*(float n) {
		return Vector2D(x * n, y * n);
	}

	Vector2D operator*=(Vector2D vec) {
		x *= vec.x;
		y *= vec.y;

		return *this;
	}

	Vector2D operator*=(float n) {
		x *= n;
		y *= n;

		return *this;
	}

	bool operator==(Vector2D vec) {
		return x == vec.x && y == vec.y;
	}

	bool operator!=(Vector2D vec) {
		return !(*this == vec);
	}
};

class Vector {
public:
	float x, y, z;

	Vector(float _x = 0, float _y = 0, float _z = 0) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector operator+(Vector& vec) {
		return Vector(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector operator+(const Vector& vec) {
		return Vector(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector operator+(const Vector& vec) const {
		return Vector(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector operator+(float n) {
		return Vector(x + n, y + n, z + n);
	}

	Vector operator+=(Vector vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	}

	Vector operator+=(float n) {
		x += n;
		y += n;
		z += n;

		return *this;
	}

	Vector operator-(Vector vec) {
		return Vector(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector operator-(float n) {
		return Vector(x - n, y - n, z - n);
	}

	Vector operator-=(Vector vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;

		return *this;
	}

	Vector operator-=(float n) {
		x -= n;
		y -= n;
		z -= n;

		return *this;
	}

	Vector operator/(Vector vec) {
		return Vector(x / vec.x, y / vec.y, z / vec.z);
	}

	Vector operator/(float n) {
		return Vector(x / n, y / n, z / n);
	}

	Vector operator/(int n) {
		return Vector(x / n, y / n, z / n);
	}

	Vector operator/=(Vector vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;

		return *this;
	}

	Vector operator/=(float n) {
		x /= n;
		y /= n;
		z /= n;

		return *this;
	}

	Vector operator*(Vector vec) {
		return Vector(x * vec.x, y * vec.y, z * vec.z);
	}

	Vector operator*(float n) {
		return Vector(x * n, y * n, z * n);
	}

	Vector operator*=(Vector vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;

		return *this;
	}

	Vector operator*=(float n) {
		x *= n;
		y *= n;
		z *= n;

		return *this;
	}

	bool operator==(Vector vec) {
		return x == vec.x && y == vec.y && z == vec.z;
	}

	bool operator!=(Vector vec) {
		return !(*this == vec);
	}

	void Clamp(float minVal, float maxVal) {
		x = (x < minVal) ? minVal : (x > maxVal) ? maxVal : x;
		y = (y < minVal) ? minVal : (y > maxVal) ? maxVal : y;
		z = (z < minVal) ? minVal : (z > maxVal) ? maxVal : z;
	}

	ImVec2 im()
	{
		// round up pixel positions
		// cuz in subpixels render fucks up and break bbox or just have "jiggly" positions
		// @MIRACLE - AURA
		return ImVec2(static_cast<int>(x), static_cast<int>(y));
	}

	float DotProduct(float* v)
	{
		return this->x * v[0] + this->y * v[1] + this->z * v[2];
	}

	float DotProduct(const Vector& v)
	{
		return this->x * v.x + this->y * v.y + this->z * v.z;
	}

	Vector Angles();
	Vector Angles(Vector);
	Vector Angles(float, float);

	Vector To(Vector);

	float Dist(Vector);
	float DistSqr(Vector);

	float Dist2D(Vector);
	float Dist2DSqr(Vector);

	float Length();
	float LengthSqr();

	float Length2D();
	float Length2DSqr();

	Vector Normalize();
	float NormilizeMovement();
	Vector NormalizeAngle();

	float Fov(Vector);
};

struct alignas(16) VectorAligned : Vector
{
	VectorAligned() = default;

	explicit VectorAligned(const Vector& vecBase)
	{
		this->x = vecBase.x;
		this->y = vecBase.y;
		this->z = vecBase.z;
		this->w = 0.0f;
	}

	constexpr VectorAligned& operator=(const Vector& vecBase)
	{
		this->x = vecBase.x;
		this->y = vecBase.y;
		this->z = vecBase.z;
		this->w = 0.0f;
		return *this;
	}

	float w = 0.0f;
};


#pragma pack(push, 4)
using Matrix3x3_t = float[3][3];

struct Matrix3x4_t
{
	Matrix3x4_t() = default;

	constexpr Matrix3x4_t(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23)
	{
		arrData[0][0] = m00;
		arrData[0][1] = m01;
		arrData[0][2] = m02;
		arrData[0][3] = m03;
		arrData[1][0] = m10;
		arrData[1][1] = m11;
		arrData[1][2] = m12;
		arrData[1][3] = m13;
		arrData[2][0] = m20;
		arrData[2][1] = m21;
		arrData[2][2] = m22;
		arrData[2][3] = m23;
	}

	constexpr Matrix3x4_t(const Vector& vecForward, const Vector& vecLeft, const Vector& vecUp, const Vector& vecOrigin)
	{
		SetForward(vecForward);
		SetLeft(vecLeft);
		SetUp(vecUp);
		SetOrigin(vecOrigin);
	}

	float* operator[](const int nIndex)
	{
		return arrData[nIndex];
	}

	const float* operator[](const int nIndex) const
	{
		return arrData[nIndex];
	}

	constexpr void SetForward(const Vector& vecForward)
	{
		arrData[0][0] = vecForward.x;
		arrData[1][0] = vecForward.y;
		arrData[2][0] = vecForward.z;
	}

	constexpr void SetLeft(const Vector& vecLeft)
	{
		arrData[0][1] = vecLeft.x;
		arrData[1][1] = vecLeft.y;
		arrData[2][1] = vecLeft.z;
	}

	constexpr void SetUp(const Vector& vecUp)
	{
		arrData[0][2] = vecUp.x;
		arrData[1][2] = vecUp.y;
		arrData[2][2] = vecUp.z;
	}

	constexpr void SetOrigin(const Vector& vecOrigin)
	{
		arrData[0][3] = vecOrigin.x;
		arrData[1][3] = vecOrigin.y;
		arrData[2][3] = vecOrigin.z;
	}

	Vector GetForward() const
	{
		return { arrData[0][0], arrData[1][0], arrData[2][0] };
	}

	Vector GetLeft() const
	{
		return { arrData[0][1], arrData[1][1], arrData[2][1] };
	}

	Vector GetUp() const
	{
		return { arrData[0][2], arrData[1][2], arrData[2][2] };
	}

	Vector GetOrigin() const
	{
		return { arrData[0][3], arrData[1][3], arrData[2][3] };
	}

	constexpr Matrix3x4_t ConcatTransforms(const Matrix3x4_t& matOther) const
	{
		return {
			arrData[0][0] * matOther.arrData[0][0] + arrData[0][1] * matOther.arrData[1][0] + arrData[0][2] * matOther.arrData[2][0],
			arrData[0][0] * matOther.arrData[0][1] + arrData[0][1] * matOther.arrData[1][1] + arrData[0][2] * matOther.arrData[2][1],
			arrData[0][0] * matOther.arrData[0][2] + arrData[0][1] * matOther.arrData[1][2] + arrData[0][2] * matOther.arrData[2][2],
			arrData[0][0] * matOther.arrData[0][3] + arrData[0][1] * matOther.arrData[1][3] + arrData[0][2] * matOther.arrData[2][3] + arrData[0][3],

			arrData[1][0] * matOther.arrData[0][0] + arrData[1][1] * matOther.arrData[1][0] + arrData[1][2] * matOther.arrData[2][0],
			arrData[1][0] * matOther.arrData[0][1] + arrData[1][1] * matOther.arrData[1][1] + arrData[1][2] * matOther.arrData[2][1],
			arrData[1][0] * matOther.arrData[0][2] + arrData[1][1] * matOther.arrData[1][2] + arrData[1][2] * matOther.arrData[2][2],
			arrData[1][0] * matOther.arrData[0][3] + arrData[1][1] * matOther.arrData[1][3] + arrData[1][2] * matOther.arrData[2][3] + arrData[1][3],

			arrData[2][0] * matOther.arrData[0][0] + arrData[2][1] * matOther.arrData[1][0] + arrData[2][2] * matOther.arrData[2][0],
			arrData[2][0] * matOther.arrData[0][1] + arrData[2][1] * matOther.arrData[1][1] + arrData[2][2] * matOther.arrData[2][1],
			arrData[2][0] * matOther.arrData[0][2] + arrData[2][1] * matOther.arrData[1][2] + arrData[2][2] * matOther.arrData[2][2],
			arrData[2][0] * matOther.arrData[0][3] + arrData[2][1] * matOther.arrData[1][3] + arrData[2][2] * matOther.arrData[2][3] + arrData[2][3]
		};
	}

	float arrData[3][4] = {};
};

#pragma pack(pop)

struct Quaternion_t
{
	constexpr Quaternion_t(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f, const float w = 0.0f) :
		x(x), y(y), z(z), w(w) { }

	bool IsValid() const
	{
		return (std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w));
	}

	Matrix3x4_t ToMatrix(const Vector& vecOrigin = {}) const
	{
		Matrix3x4_t matOut;

#ifdef _DEBUG // precalculate common multiplications
		const float x2 = this->x + this->x, y2 = this->y + this->y, z2 = this->z + this->z;
		const float xx = this->x * x2, xy = this->x * y2, xz = this->x * z2;
		const float yy = this->y * y2, yz = this->y * z2;
		const float zz = this->z * z2;
		const float wx = this->w * x2, wy = this->w * y2, wz = this->w * z2;

		matOut[0][0] = 1.0f - (yy + zz);
		matOut[1][0] = xy + wz;
		matOut[2][0] = xz - wy;

		matOut[0][1] = xy - wz;
		matOut[1][1] = 1.0f - (xx + zz);
		matOut[2][1] = yz + wx;

		matOut[0][2] = xz + wy;
		matOut[1][2] = yz - wx;
		matOut[2][2] = 1.0f - (xx + yy);
#else // let the compiler optimize calculations itself
		matOut[0][0] = 1.0f - 2.0f * this->y * this->y - 2.0f * this->z * this->z;
		matOut[1][0] = 2.0f * this->x * this->y + 2.0f * this->w * this->z;
		matOut[2][0] = 2.0f * this->x * this->z - 2.0f * this->w * this->y;

		matOut[0][1] = 2.0f * this->x * this->y - 2.0f * this->w * this->z;
		matOut[1][1] = 1.0f - 2.0f * this->x * this->x - 2.0f * this->z * this->z;
		matOut[2][1] = 2.0f * this->y * this->z + 2.0f * this->w * this->x;

		matOut[0][2] = 2.0f * this->x * this->z + 2.0f * this->w * this->y;
		matOut[1][2] = 2.0f * this->y * this->z - 2.0f * this->w * this->x;
		matOut[2][2] = 1.0f - 2.0f * this->x * this->x - 2.0f * this->y * this->y;
#endif

		matOut[0][3] = vecOrigin.x;
		matOut[1][3] = vecOrigin.y;
		matOut[2][3] = vecOrigin.z;
		return matOut;
	}

	float x, y, z, w;
};

struct alignas(16) QuaternionAligned : Quaternion_t
{
	QuaternionAligned& operator=(const Quaternion_t& quatOther)
	{
		this->x = quatOther.x;
		this->y = quatOther.y;
		this->z = quatOther.z;
		this->w = quatOther.w;
		return *this;
	}
};