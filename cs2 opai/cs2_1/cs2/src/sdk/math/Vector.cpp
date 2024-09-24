#include "Vector.h"
#include "math.h"

Vector Vector::Angles() {
    float distance2D = this->Length2D();

    float pitch = Math::RAD2DEG(std::atan2f(z, distance2D));
    float yaw = Math::RAD2DEG(std::atan2f(y, x));

    return Vector(-pitch, yaw, 0);
}

Vector Vector::Angles(float pitch, float yaw) {
    float pitchRadians = Math::DEG2RAD(pitch);
    float yawRadians = Math::DEG2RAD(yaw);

    float x = std::cosf(pitchRadians) * std::cosf(yawRadians);
    float y = std::cosf(pitchRadians) * std::sinf(yawRadians);
    float z = -std::sinf(pitchRadians);

    return Vector(x, y, z);
}

Vector Vector::Angles(Vector vec) {
    return this->Angles(vec.x, vec.y);
}

Vector Vector::To(Vector vec) {
    Vector direction = vec - *this;

    return direction.Normalize();
}

float Vector::Dist(Vector vec) {
    return (*this - vec).Length();
}

float Vector::DistSqr(Vector vec) {
    return (*this - vec).LengthSqr();
}

float Vector::Dist2D(Vector vec) {
    return (*this - vec).Length2D();
}

float Vector::Dist2DSqr(Vector vec) {
    return (*this - vec).Length2DSqr();
}

float Vector::Length() {
    return std::sqrtf(this->LengthSqr());
}

float Vector::LengthSqr() {
    return x * x + y * y + z * z;
}

float Vector::Length2D() {
    return std::sqrtf(this->Length2DSqr());
}

float Vector::Length2DSqr() {
    return x * x + y * y;
}

Vector Vector::Normalize() {
    float length = this->Length();

    return *this / length;
}

float Vector::NormilizeMovement()
{
    Vector res = *this;
    float l = res.Length();
    if (l != 0.0f)
    {
        res /= l;
    }
    else
    {
        res.x = res.y = res.z = 0.0f;
    }
    return l;
}

Vector Vector::NormalizeAngle() {
    while (y < 180)
        y += 360;

    while (y > 180)
        y -= 360;

    if (x > 89)
        x = 89;

    if (x < -89)
        x = -89;

    return *this;
}

float Vector::Fov(Vector vec) {
    return (*this - vec).NormalizeAngle().Length();
}