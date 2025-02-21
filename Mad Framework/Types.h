#pragma once

struct Vector3;
struct Vector4;

struct Vector2
{
	float x, y;

	float Length() const
	{
		return sqrtf(x * x + y * y);
	}

	static float Length(const Vector2 a)
	{
		return sqrtf(a.x * a.x + a.y * a.y);
	}

	float Dot(const Vector2 b) const
	{
		return x * b.x + y * b.y;
	}

	static float Dot(const Vector2 a, const Vector2 b)
	{
		return a.x * b.x + a.y * b.y;
	}

	float Distance(const Vector2 b) const
	{
		return sqrtf((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
	}

	static float Distance(const Vector2 a, const Vector2 b)
	{
		return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}

	Vector2 GetPitchTo(const Vector2 b) const
	{
		return { 1.f, (b.y - y) / (b.x - x) };
	}

	static Vector2 GetPitchTo(const Vector2 a, const Vector2 b)
	{
		return { 1.f, (b.y - a.y) / (b.x - a.x) };
	}

	Vector2 operator+(const Vector2 a) const
	{
		return { x + a.x, y + a.y };
	}

	void operator+=(const Vector2 a)
	{
		x += a.x;
		y += a.y;
	}

	Vector2 operator-(const Vector2 a) const
	{
		return { x - a.x, y - a.y };
	}

	void operator-=(const Vector2 a)
	{
		x -= a.x;
		y -= a.y;
	}

	Vector2 operator*(const Vector2 a) const
	{
		return { x * a.x, y * a.y };
	}

	void operator*=(const Vector2 a)
	{
		x *= a.x;
		y *= a.y;
	}

	Vector2 operator/(const Vector2 a) const
	{
		return { x / a.x, y / a.y };
	}

	void operator/=(const Vector2 a)
	{
		x /= a.x;
		y /= a.y;
	}
	Vector2 operator+(const float a) const
	{
		return { x + a, y + a };
	}

	void operator+=(const float a)
	{
		x += a;
		y += a;
	}

	Vector2 operator-(const float a) const
	{
		return { x - a, y - a };
	}

	void operator-=(const float a)
	{
		x -= a;
		y -= a;
	}

	Vector2 operator*(const float a) const
	{
		return { x * a, y * a };
	}

	void operator*=(const float a)
	{
		x *= a;
		y *= a;
	}

	Vector2 operator/(const float a) const
	{
		return { x / a, y / a };
	}

	void operator/=(const float a)
	{
		x /= a;
		y /= a;
	}

	bool operator==(const Vector2 a) const
	{
		return x == a.x && y == a.y;
	}

	bool operator!=(const Vector2 a) const
	{
		return !(*this == a);
	}

	bool operator==(const float a) const
	{
		return x == a && y == a;
	}

	bool operator!=(const float a) const
	{
		return !(*this == a);
	}

	bool operator>(const Vector2 a) const
	{
		return x > a.x && y > a.y;
	}

	bool operator>=(const Vector2 a) const
	{
		return x >= a.x && y >= a.y;
	}

	bool operator<(const Vector2 a) const
	{
		return x < a.x && y < a.y;
	}

	bool operator<=(const Vector2 a) const
	{
		return x <= a.x && y <= a.y;
	}

	bool operator>(const float a) const
	{
		return x > a && y > a;
	}

	bool operator>=(const float a) const
	{
		return x >= a && y >= a;
	}

	bool operator<(const float a) const
	{
		return x < a && y < a;
	}

	bool operator<=(const float a) const
	{
		return x <= a && y <= a;
	}

	inline operator Vector3() const;
	inline operator Vector4() const;
};

struct Vector3
{
	float x, y, z;

	float Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	static float Length(const Vector3& a)
	{
		return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
	}

	Vector3 Normalize() const
	{
		const float length = sqrtf(x * x + y * y + z * z);
		return length != 0 ? *this / length : *this;
	}

	static Vector3 Normalize(const Vector3& a)
	{
		const float length = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
		return length != 0 ? a / length : a;
	}

	float Dot(const Vector3& b) const
	{
		return x * b.x + y * b.y + z * b.z;
	}

	static float Dot(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	float Distance(const Vector3& b) const
	{
		return sqrtf((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z));
	}

	static float Distance(const Vector3& a, const Vector3& b)
	{
		return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
	}

	Vector3 GetPitchTo(const Vector3& b) const
	{
		return { 1.f, (b.y - y) / (b.x - x), (b.z - z) / (b.x - x) };
	}

	static Vector3 GetPitchTo(const Vector3& a, const Vector3& b)
	{
		return { 1.f, (b.y - a.y) / (b.x - a.x), (b.z - a.z) / (b.x - a.x) };
	}

	Vector3 operator+(const Vector3& a) const
	{
		return { x + a.x, y + a.y, z + a.z };
	}

	void operator+=(const Vector3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
	}

	Vector3 operator-(const Vector3& a) const
	{
		return { x - a.x, y - a.y, z - a.z };
	}

	void operator-=(const Vector3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}

	Vector3 operator*(const Vector3& a) const
	{
		return { x * a.x, y * a.y, z * a.z };
	}

	void operator*=(const Vector3& a)
	{
		x *= a.x;
		y *= a.y;
		z *= a.z;
	}

	Vector3 operator/(const Vector3& a) const
	{
		return { x / a.x, y / a.y, z / a.z };
	}

	void operator/=(const Vector3& a)
	{
		x /= a.x;
		y /= a.y;
		z /= a.z;
	}

	Vector3 operator+(const float a) const
	{
		return { x + a, y + a, z + a };
	}

	void operator+=(const float a)
	{
		x += a;
		y += a;
		z += a;
	}

	Vector3 operator-(const float a) const
	{
		return { x - a, y - a, z - a };
	}

	void operator-=(const float a)
	{
		x -= a;
		y -= a;
		z -= a;
	}

	Vector3 operator*(const float a) const
	{
		return { x * a, y * a, z * a };
	}

	void operator*=(const float a)
	{
		x *= a;
		y *= a;
		z *= a;
	}

	Vector3 operator/(const float a) const
	{
		return { x / a, y / a, z / a };
	}

	void operator/=(const float a)
	{
		x /= a;
		y /= a;
		z /= a;
	}

	bool operator==(const Vector2 a) const
	{
		return x == a.x && y == a.y;
	}

	bool operator!=(const Vector2 a) const
	{
		return !(*this == a);
	}

	bool operator==(const Vector3& a) const
	{
		return x == a.x && y == a.y && z == a.z;
	}

	bool operator!=(const Vector3& a) const
	{
		return !(*this == a);
	}

	bool operator==(const float a) const
	{
		return x == a && y == a && z == a;
	}

	bool operator!=(const float a) const
	{
		return !(*this == a);
	}

	bool operator>(const Vector2 a) const
	{
		return x > a.x && y > a.y;
	}

	bool operator>=(const Vector2 a) const
	{
		return x >= a.x && y >= a.y;
	}

	bool operator<(const Vector2 a) const
	{
		return x < a.x && y < a.y;
	}

	bool operator<=(const Vector2 a) const
	{
		return x <= a.x && y <= a.y;
	}

	bool operator>(const Vector3& a) const
	{
		return x > a.x && y > a.y && z > a.z;
	}

	bool operator>=(const Vector3& a) const
	{
		return x >= a.x && y >= a.y && z >= a.z;
	}

	bool operator<(const Vector3& a) const
	{
		return x < a.x && y < a.y && z < a.z;
	}

	bool operator<=(const Vector3& a) const
	{
		return x <= a.x && y <= a.y && z <= a.z;
	}

	bool operator>(const float a) const
	{
		return x > a && y > a;
	}

	bool operator>=(const float a) const
	{
		return x >= a && y >= a;
	}

	bool operator<(const float a) const
	{
		return x < a && y < a;
	}

	bool operator<=(const float a) const
	{
		return x <= a && y <= a;
	}

	operator Vector2() const
	{
		return { x, y };
	}

	inline operator Vector4() const;
};

Vector2::operator Vector3() const { return { x, y, 0.f }; }

struct Vector4
{
	float x, y, z, w;

	float Length() const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	static float Length(const Vector4& a)
	{
		return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
	}

	float Dot(const Vector4& b) const
	{
		return x * b.x + y * b.y + z * b.z + w * b.w;
	}

	static float Dot(const Vector4& a, const Vector4& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	float Distance(const Vector4& b) const
	{
		return sqrtf((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z) + (w - b.w) * (w - b.w));
	}

	static float Distance(const Vector4& a, const Vector4& b)
	{
		return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z) + (a.w - b.w) * (a.w - b.w));
	}

	Vector4 GetPitchTo(const Vector4& b) const
	{
		return { 1.f, (b.y - y) / (b.x - x), (b.z - z) / (b.x - x), (b.w - w) / (b.x - x) };
	}

	static Vector4 GetPitchTo(const Vector4& a, const Vector4& b)
	{
		return { 1.f, (b.y - a.y) / (b.x - a.x), (b.z - a.z) / (b.x - a.x), (b.w - a.w) / (b.x - a.x) };
	}

	Vector4 operator+(const Vector4& a) const
	{
		return { x + a.x, y + a.y, z + a.z, w + a.w };
	}

	void operator+=(const Vector4& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		w += a.w;
	}

	Vector4 operator-(const Vector4& a) const
	{
		return { x - a.x, y - a.y, z - a.z, w - a.w };
	}

	void operator-=(const Vector4& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		w -= a.w;
	}

	Vector4 operator*(const Vector4& a) const
	{
		return { x * a.x, y * a.y, z * a.z, w * a.w };
	}

	void operator*=(const Vector4& a)
	{
		x *= a.x;
		y *= a.y;
		z *= a.z;
		w *= a.w;
	}

	Vector4 operator/(const Vector4& a) const
	{
		return { x / a.x, y / a.y, z / a.z, w / a.w };
	}

	void operator/=(const Vector4& a)
	{
		x /= a.x;
		y /= a.y;
		z /= a.z;
		w /= a.w;
	}

	Vector4 operator+(const float a) const
	{
		return { x + a, y + a, z + a, w + a };
	}

	void operator+=(const float a)
	{
		x += a;
		y += a;
		z += a;
		w += a;
	}

	Vector4 operator-(const float a) const
	{
		return { x - a, y - a, z - a, w - a };
	}

	void operator-=(const float a)
	{
		x -= a;
		y -= a;
		z -= a;
		w -= a;
	}

	Vector4 operator*(const float a) const
	{
		return { x * a, y * a, z * a, w * a };
	}

	void operator*=(const float a)
	{
		x *= a;
		y *= a;
		z *= a;
		w *= a;
	}

	Vector4 operator/(const float a) const
	{
		return { x / a, y / a, z / a, w / a };
	}

	void operator/=(const float a)
	{
		x /= a;
		y /= a;
		z /= a;
		w /= a;
	}

	bool operator==(const Vector2 a) const
	{
		return x == a.x && y == a.y;
	}

	bool operator!=(const Vector2 a) const
	{
		return !(*this == a);
	}

	bool operator==(const Vector3& a) const
	{
		return x == a.x && y == a.y && z == a.z;
	}

	bool operator!=(const Vector3& a) const
	{
		return !(*this == a);
	}

	bool operator==(const Vector4& a) const
	{
		return x == a.x && y == a.y && z == a.z && w == a.w;
	}

	bool operator!=(const Vector4& a) const
	{
		return !(*this == a);
	}

	bool operator==(const float a) const
	{
		return x == a && y == a && z == a && w == a;
	}

	bool operator!=(const float a) const
	{
		return !(*this == a);
	}

	bool operator>(const Vector2 a) const
	{
		return x > a.x && y > a.y;
	}

	bool operator>=(const Vector2 a) const
	{
		return x >= a.x && y >= a.y;
	}

	bool operator<(const Vector2 a) const
	{
		return x < a.x && y < a.y;
	}

	bool operator<=(const Vector2 a) const
	{
		return x <= a.x && y <= a.y;
	}

	bool operator>(const Vector3& a) const
	{
		return x > a.x && y > a.y && z > a.z;
	}

	bool operator>=(const Vector3& a) const
	{
		return x >= a.x && y >= a.y && z >= a.z;
	}

	bool operator<(const Vector3& a) const
	{
		return x < a.x && y < a.y && z < a.z;
	}

	bool operator<=(const Vector3& a) const
	{
		return x <= a.x && y <= a.y && z <= a.z;
	}

	bool operator>(const Vector4& a) const
	{
		return x > a.x && y > a.y && z > a.z && w > a.w;
	}

	bool operator>=(const Vector4& a) const
	{
		return x >= a.x && y >= a.y && z >= a.z && w >= a.w;
	}

	bool operator<(const Vector4& a) const
	{
		return x < a.x && y < a.y && z < a.z && z < a.w;
	}

	bool operator<=(const Vector4& a) const
	{
		return x <= a.x && y <= a.y && z <= a.z && w < a.w;
	}

	bool operator>(const float a) const
	{
		return x > a && y > a;
	}

	bool operator>=(const float a) const
	{
		return x >= a && y >= a;
	}

	bool operator<(const float a) const
	{
		return x < a && y < a;
	}

	bool operator<=(const float a) const
	{
		return x <= a && y <= a;
	}

	operator Vector2() const
	{
		return { x, y };
	}
	operator Vector3() const
	{
		return { x, y, z };
	}
};

Vector2::operator Vector4() const { return { x, y, 0.f, 0.f }; }
Vector3::operator Vector4() const { return { x, y, z, 0.f }; }

using Color = Vector4;

struct Matrix4
{
	float m[4][4] {};

	Matrix4()
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] = 0.0f;
	}

	Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}

	Matrix4 operator*(const Matrix4& rhs) const
	{
		Matrix4 result;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result.m[i][j] = 0.0f;
				for (int k = 0; k < 4; ++k)
				{
					result.m[i][j] += m[i][k] * rhs.m[k][j];
				}
			}
		}
		return result;
	}

	Vector4 operator*(const Vector4& v) const
	{
		Vector4 result;
		result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
		result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
		result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
		result.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
		return result;
	}

	Matrix4 Transpose() const
	{
		Matrix4 result;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result.m[i][j] = m[j][i];
			}
		}
		return result;
	}

	float Determinant() const
	{
		float det = 0.0f;
		for (int i = 0; i < 4; ++i)
		{
			float subMatrix[3][3];
			for (int j = 1; j < 4; ++j)
			{
				int subCol = 0;
				for (int k = 0; k < 4; ++k)
				{
					if (k != i)
					{
						subMatrix[j - 1][subCol] = m[j][k];
						subCol++;
					}
				}
			}

			float minorDet = subMatrix[0][0] * (subMatrix[1][1] * subMatrix[2][2] - subMatrix[1][2] * subMatrix[2][1])
				- subMatrix[0][1] * (subMatrix[1][0] * subMatrix[2][2] - subMatrix[1][2] * subMatrix[2][0])
				+ subMatrix[0][2] * (subMatrix[1][0] * subMatrix[2][1] - subMatrix[1][1] * subMatrix[2][0]);

			det += (i % 2 == 0 ? 1 : -1) * m[0][i] * minorDet;
		}
		return det;
	}

	float* operator[](size_t index)
	{
		return m[index];
	}

	const float* operator[](size_t index) const
	{
		return m[index];
	}
};