#pragma once

#include <cmath>
#include "../../sdk/math/Vector.h"  

#include <DirectXMath.h>
#include <xmmintrin.h>

#define M_PI 3.14159265358979323846

struct ViewMatrix_t {
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;

		};
		float m[4][4];
	};
};

namespace Math {
    float DEG2RAD(float);
    float RAD2DEG(float);
    Vector AimDirection(Vector angles, Vector dst);
	float DeltaAngle(float, float);
    void VectorAngles(Vector vec_forward, Vector& vec_angles);
    void AngleVectors(Vector& angles, Vector& forward);

	void AngleVectors(Vector angles, Vector forward, Vector right, Vector up);

    float AngleNormilize(float angle);
    void AngleNormilize(Vector& angle);

	template < typename t >
	t Interpolate(t from, t to, const float percent)
	{
		return to * percent + from * (1.f - percent);
	}

	Vector VectorTransform(Vector& in1, const Matrix3x4_t& in2);
}