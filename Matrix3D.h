#pragma once

#include <YRPPCore.h>
#include <GeneralStructures.h>

#include <Helpers/CompileTime.h>

class Quaternion;

template <typename T>
class Vector4D
{
public:
	static const Vector4D Empty;

	//no constructor, so this class stays aggregate and can be initialized using the curly braces {}
	T X, Y, Z, W;

	// TODO add Vector4 methods
};

template <typename T>
const Vector4D<T> Vector4D<T>::Empty = { T(), T(), T(), T() };

class Matrix3D
{
public:

	//Constructor

	Matrix3D() = default;

	// plain floats ctor
	Matrix3D(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		row[0][0] = m00; row[0][1] = m01; row[0][2] = m02; row[0][3] = m03;
		row[1][0] = m10; row[1][1] = m11; row[1][2] = m12; row[1][3] = m13;
		row[2][0] = m20; row[2][1] = m21; row[2][2] = m22; row[2][3] = m23;
		// JMP_THIS(0x5AE630);
	}

	// column vector ctor
	Matrix3D(
		Vector3D<float> const& x,
		Vector3D<float> const& y,
		Vector3D<float> const& z,
		Vector3D<float> const& pos)
	{
		row[0][0] = x.X; row[0][1] = y.X; row[0][2] = z.X; row[0][3] = pos.X;
		row[1][0] = x.Y; row[1][1] = y.Y; row[1][2] = z.Y; row[1][3] = pos.Y;
		row[2][0] = x.Z; row[2][1] = y.Z; row[2][2] = z.Z; row[2][3] = pos.Z;
		// JMP_THIS(0x5AE690);
	}

	// Terrain ramp
	Matrix3D(float rotate_z, float rotate_x) { JMP_THIS(0x5AE6F0); }

	// rotation along axis
	Matrix3D(Vector3D<float>* axis, float angle) { JMP_THIS(0x5AE750); }

	// copy ctor
	Matrix3D(const Matrix3D& another)
	{
		std::memcpy(this, &another, sizeof(Matrix3D));
		// JMP_THIS(0x5AE610);
	}

	Matrix3D(Matrix3D&& another) = default;

	Matrix3D& operator=(const Matrix3D& another)
	{
		std::memcpy(this, &another, sizeof(Matrix3D));
		return *this;
	}

	Matrix3D& operator=(Matrix3D&& another) = default;

	// Non virtual

	// operators

	static Matrix3D* __fastcall __MatrixMultiply(Matrix3D* ret, const Matrix3D* A, const Matrix3D* B) { JMP_STD(0x5AF980); }
	Matrix3D operator*(const Matrix3D& B) const
	{
		Matrix3D ret;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
				ret.row[i][j] =
				this->row[i][0] * B.row[0][j] +
				this->row[i][1] * B.row[1][j] +
				this->row[i][2] * B.row[2][j];

			ret.row[i][3] =
				this->row[i][0] * B.row[0][3] +
				this->row[i][1] * B.row[1][3] +
				this->row[i][2] * B.row[2][3] +
				this->row[i][3];
		}

		return ret;
	}
	
	void operator*=(const Matrix3D& another)
	{
		*this = *this * another;
	}

	static Vector3D<float>* __fastcall __MatrixMultiply(Vector3D<float>* ret, const Matrix3D* mat, const Vector3D<float>* vec) { JMP_STD(0x5AFB80); }
	Vector3D<float> operator*(const Vector3D<float>& point) const
	{
		return RotateVector(point) + Vector3D<float>{row[0][3], row[1][3], row[2][3]};
	}

	void MakeIdentity()// { JMP_THIS(0x5AE860); } // 1-matrix
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 4; j++)
				row[i][j] = i == j ? 1.f : 0.f;
	}

	void Translate(float x, float y, float z) //{ JMP_THIS(0x5AE890); }
	{
		TranslateX(x);
		TranslateY(y);
		TranslateZ(z);
	}

	void Translate(Vector3D<float> const& vec) //{ JMP_THIS(0x5AE8F0); }
	{
		Translate(vec.X, vec.Y, vec.Z);
	}

	void TranslateX(float x) //{ JMP_THIS(0x5AE980); }
	{
		for (int i = 0; i < 3; i++)
			row[i][3] += x * row[i][0];
	}

	void TranslateY(float y) //{ JMP_THIS(0x5AE9B0); }
	{
		for (int i = 0; i < 3; i++)
			row[i][3] += y * row[i][1];
	}

	void TranslateZ(float z) //{ JMP_THIS(0x5AE9E0); }
	{
		for (int i = 0; i < 3; i++)
			row[i][3] += z * row[i][2];
	}

	void Scale(float factor) //{ JMP_THIS(0x5AEA10); }
	{
		for (float& i : Data)
			i *= factor;
	}

	void Scale(float x, float y, float z) //{ JMP_THIS(0x5AEA70); }
	{
		ScaleX(x);
		ScaleY(y);
		ScaleZ(z);
	}

	void ScaleX(float factor) //{ JMP_THIS(0x5AEAD0); }
	{
		for (int i = 0; i < 3; i++)
			row[i][0] *= factor;
	}

	void ScaleY(float factor) //{ JMP_THIS(0x5AEAF0); }
	{
		for (int i = 0; i < 3; i++)
			row[i][1] *= factor;
	}

	void ScaleZ(float factor) //{ JMP_THIS(0x5AEB20); }
	{
		for (int i = 0; i < 3; i++)
			row[i][2] *= factor;
	}

	void ShearYZ(float y, float z) { JMP_THIS(0x5AEB50); }
	void ShearXY(float x, float y) { JMP_THIS(0x5AEBA0); }
	void ShearXZ(float x, float z) { JMP_THIS(0x5AEBF0); }
	void PreRotateX(float theta) { JMP_THIS(0x5AEC40); }
	void PreRotateY(float theta) { JMP_THIS(0x5AED50); }
	void PreRotateZ(float theta) { JMP_THIS(0x5AEE50); }
	void RotateX(float theta) { JMP_THIS(0x5AEF60); }
	void RotateX(float Sin, float Cos) { JMP_THIS(0x5AF000); }
	void RotateY(float theta) { JMP_THIS(0x5AF080); }
	void RotateY(float Sin, float Cos) { JMP_THIS(0x5AF120); }
	void RotateZ(float theta) { JMP_THIS(0x5AF1A0); }
	void RotateZ(float Sin, float Cos) { JMP_THIS(0x5AF240); }

	float GetXVal() const //{ JMP_THIS(0x5AF2C0); }
	{
		return row[0][3];
	}

	float GetYVal() const //{ JMP_THIS(0x5AF310); }
	{
		return row[1][3];
	}

	float GetZVal() const //{ JMP_THIS(0x5AF360); }
	{
		return row[2][3];
	}

	Vector3D<float> GetTranslation()  const
	{
		return {row[0][3],row[1][3],row[2][3] };
	}

	float GetXRotation() const { JMP_THIS(0x5AF3B0); }
	float GetYRotation() const { JMP_THIS(0x5AF410); }
	float GetZRotation() const { JMP_THIS(0x5AF470); }

	Vector3D<float>* __RotateVector(Vector3D<float>* ret, Vector3D<float>* rotate) const { JMP_THIS(0x5AF4D0); }
	Vector3D<float> RotateVector(Vector3D<float> const& rotate) const
	{
		return {
			row[0][0] * rotate.X + row[0][1] * rotate.Y + row[0][2] * rotate.Z,
			row[1][0] * rotate.X + row[1][1] * rotate.Y + row[1][2] * rotate.Z,
			row[2][0] * rotate.X + row[2][1] * rotate.Y + row[2][2] * rotate.Z,
		};
	}

	void LookAt1(Vector3D<float>& p, Vector3D<float>& t, float roll) { JMP_THIS(0x5AF550); }
	void LookAt2(Vector3D<float>& p, Vector3D<float>& t, float roll) { JMP_THIS(0x5AF710); }

	static Matrix3D* __fastcall TransposeMatrix(Matrix3D* buffer, const Matrix3D* mat) { JMP_STD(0x5AFC20); }
	static Matrix3D TransposeMatrix(const Matrix3D& mat)
	{
		Matrix3D buffer;
		TransposeMatrix(&buffer, &mat);
		return buffer;
	}
	void Transpose()
	{
		*this = TransposeMatrix(*this);
	}

	static Matrix3D* __fastcall FromQuaternion(Matrix3D* mat, const Quaternion* q) { JMP_STD(0x646980); }
	static Matrix3D FromQuaternion(const Quaternion& q)
	{
		Matrix3D buffer;
		FromQuaternion(&buffer, &q);
		return buffer;
	}
	void ApplyQuaternion(const Quaternion& q)
	{
		*this = FromQuaternion(q) * *this;
	}

	static constexpr reference<Matrix3D, 0xB44318> VoxelDefaultMatrix{};
	static constexpr reference<Matrix3D, 0xB45188, 21> VoxelRampMatrix{};

	static Matrix3D GetIdentity()
	{
		Matrix3D mtx;
		mtx.MakeIdentity();
		return mtx;
	}

	//Properties
public:
	union
	{
		Vector4D<float> Row[3];
		float row[3][4];
		float Data[12] = {};
	};
};
