#pragma once
#include <cmath>
#include "QANGLE.h"

#define PI 3.14159265358979323846f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define square( x ) ( x * x )

typedef float vec_t;

struct Vector
{
	float x;
	float y;
	float z;

	inline void Init(float ix, float iy, float iz)
	{
		x = ix; y = iy; z = iz;
	}

	Vector() { x = 0; y = 0; z = 0; };
	Vector(float X, float Y, float Z) { x = X; y = Y; z = Z; };

	float operator[](int i) const { if (i == 1) return x; if (i == 2) return y; return z; };
	float& operator[](int i) { if (i == 1) return x; if (i == 2) return y; return z; };

	bool operator==(const Vector& v) { return true; }
	bool operator!=(const Vector& v) { return true; }

	inline Vector operator-(const Vector& v) const { return Vector(x - v.x, y - v.y, z - v.z); }
	inline Vector operator+(const Vector& v) { return Vector(x + v.x, y + v.y, z + v.z); }
	inline Vector operator+(const Vector& v) const { return Vector(x + v.x, y + v.y, z + v.z); }
	inline Vector operator*(const int n) { return Vector(x * n, y * n, z * n); }
	inline Vector& operator*=(float fl) { x *= fl; y *= fl; z *= fl; return *this; }
	inline Vector operator-() { return Vector(-x, -y, -z); }
	inline Vector& operator+=(const Vector& v) { x += v.x; y += v.y; z += v.z; return *this; }
	inline Vector operator/(float fl) { Vector res; res.x = x / fl; res.y = y / fl; res.z = z / fl; return res; }
	inline Vector operator/(const Vector& v) { Vector res; res.x = x / v.x; res.y = y / v.y; res.z = z / v.z; return res; }

	float Length(void) { return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z); }
	float LengthSqr(void) { return (x * x + y * y + z * z); }
	float Length2D(void) const { return sqrtf(x * x + y * y); }
};

static void veccpy(Vector& _Destination, Vector& _Source) { _Destination.x = _Source.x; _Destination.y = _Source.y; _Destination.z = _Source.z; }

static float AngleNormalize(float Yaw)
{
	while (Yaw < -180.0f) Yaw += 360.0f;
	while (Yaw > 180.0f) Yaw -= 360.0f;
	return Yaw;
}

static void SinCos(float radians, float* sine, float* cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

static void AngleVectors(const QAngle& angles, Vector& forward)
{
	float	sp, sy, cp, cy;
	SinCos(DEG2RAD(angles[1]), &sy, &cy);
	SinCos(DEG2RAD(angles[0]), &sp, &cp);
	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

class VectorAligned : public Vector
{
public:
	VectorAligned()
	{
		x = y = z = 0.0f;
	}

	VectorAligned(const Vector& v)
	{
		x = v.x; y = v.y; z = v.z;
	}

	float w;
};