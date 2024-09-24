#include "math.h"
#include <algorithm>

float Math::DEG2RAD(float x) {
    static float value = (M_PI / 180);

    return x * value;
}

float Math::RAD2DEG(float x) {
    static float value = (180 / M_PI);

    return x * value;
}

Vector Math::AimDirection(Vector angles, Vector dst)
{
    Vector result;
    Vector delta = dst - angles;
    VectorAngles(delta, result);

    return result;
}

float Math::DeltaAngle(float first, float second)
{
    const float delta = first - second;
    float res = std::isfinite(delta) ? std::remainder(delta, 6.283f) : 0.0f;

    if (first > second)
    {
        if (res >= 3.1415f)
            res -= 6.283f;
    }
    else
    {
        if (res <= -3.1415f)
            res += 6.283f;
    }

    return res;
};

void Math::VectorAngles(Vector vec_forward, Vector& vec_angles)
{
    if (vec_forward.x == 0.f && vec_forward.y == 0.f)
    {
        vec_angles.y = 0.f;
        vec_angles.x = vec_forward.z > 0.f ? 270.f : 90.f;
    }
    else
    {
        vec_angles.y = Math::RAD2DEG(std::atan2(vec_forward.y, vec_forward.x));
        if (vec_angles.y < 0.f)
            vec_angles.y += 360.f;

        vec_angles.x = Math::RAD2DEG(std::atan2(-vec_forward.z, vec_forward.Length2D()));
        if (vec_angles.x < 0.f)
            vec_angles.x += 360.f;
    }

    vec_angles.x = std::remainder(vec_angles.x, 360.f);
    vec_angles.y = std::remainder(vec_angles.y, 360.f);
    vec_angles.z = std::remainder(vec_angles.z, 360.f);
}

void Math::AngleVectors(Vector& angles, Vector& forward)
{
    float sp, sy, cp, cy;

    DirectX::XMScalarSinCos(&sp, &cp, Math::DEG2RAD(angles.x));
    DirectX::XMScalarSinCos(&sy, &cy, Math::DEG2RAD(angles.y));

    forward.x = cp * cy;
    forward.y = cp * sy;
    forward.z = -sp;
}

void Math::AngleVectors(Vector angles, Vector forward, Vector right, Vector up)
{
    float			angle;
    static float	sr, sp, sy, cr, cp, cy;

    angle = angles.y * (M_PI * 2 / 360);
    sy = sin(angle);
    cy = cos(angle);

    angle = angles.x * (M_PI * 2 / 360);
    sp = sin(angle);
    cp = cos(angle);

    angle = angles.z * (M_PI * 2 / 360);
    sr = sin(angle);
    cr = cos(angle);

    forward.x = cp * cy;
    forward.y = cp * sy;
    forward.z = -sp;

    right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
    right.y = (-1 * sr * sp * sy + -1 * cr * cy);
    right.z = -1 * sr * cp;

    up.x = (cr * sp * cy + -sr * -sy);
    up.y = (cr * sp * sy + -sr * cy);
    up.z = cr * cp;
}

float Math::AngleNormilize(float angle)
{
    angle = fmodf(angle, 360.0f);
    if (angle > 180)
    {
        angle -= 360;
    }
    if (angle < -180)
    {
        angle += 360;
    }
    return angle;
}

void Math::AngleNormilize(Vector& angle) {
    angle.x = std::clamp(angle.x, -89.0f, 89.0f);

    while (angle.y < -180.f) angle.y += 360.f;
    while (angle.y > 180.f) angle.y -= 360.f;

    angle.z = 0.0f;
}

Vector Math::VectorTransform(Vector& in1, const Matrix3x4_t& in2)
{
    return {
        in1.DotProduct(Vector(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3],
        in1.DotProduct(Vector(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3],
        in1.DotProduct(Vector(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3]
    };
}