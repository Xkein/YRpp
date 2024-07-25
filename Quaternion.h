#pragma once

#include <Matrix3D.h>
#include <YRMathVector.h>

class Quaternion
{
public:
	Quaternion() {};
	Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

	void Normalize()
	{
		float mag = X * X + Y * Y + Z * Z + W * W;
		if (mag != 0.0)
		{
			X /= mag;
			Y /= mag;
			Z /= mag;
			W /= mag;
		}
	}

	void Scale(float scale)
	{
		X *= scale;
		Y *= scale;
		Z *= scale;
		W *= scale;
	}

	float& operator[](int idx)
		{ return (&X)[idx]; }

	const float& operator[](int idx) const
		{ return (&X)[idx]; }

	Quaternion& operator=(const Quaternion& another)
	{
		X = another.X;
		Y = another.Y;
		Z = another.Z;
		W = another.W;
		return *this;
	}

	Quaternion Inverse()
		{ return Quaternion{ -X,-Y,-Z,-W }; }

	Quaternion Conjugate() 
		{ return Quaternion{ -X,-Y,-Z,W }; }

	static Quaternion __fastcall Trackball(float x0, float y0, float x1, float y1, float radius)
		{ JMP_STD(0x646160); }

	static Quaternion __fastcall FromAxis(const Vector3D<float>& src, float phi)
		{ JMP_STD(0x646480); }

	static Quaternion __fastcall Slerp(const Quaternion& a, const Quaternion& b, float alpha)
		{ JMP_STD(0x646590); }


	static Quaternion __fastcall FromMatrix3D(const Matrix3D& mat)
		{ JMP_STD(0x646730); }

	static Matrix3D __fastcall ToMatrix3D(const Quaternion& qua)
		{ JMP_STD(0x646980); }

	float X{ 0.0f };
	float Y{ 0.0f };
	float Z{ 0.0f };
	float W{ 0.0f };
};
