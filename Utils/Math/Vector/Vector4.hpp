class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4()
	{}

	Vector4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{}

	Vector3 forward()
	{
		Vector3  point = { 0, 0, 1 };
		float num = x * 2;
		float num2 = y * 2;
		float num3 = z * 2;
		float num4 = x * num;
		float num5 = y * num2;
		float num6 = z * num3;
		float num7 = x * num2;
		float num8 = x * num3;
		float num9 = y * num3;
		float num10 = w * num;
		float num11 = w * num2;
		float num12 = w * num3;
		Vector3  result;
		result.x = (1 - (num5 + num6)) * point.x + (num7 - num12) * point.y +
			(num8 + num11) * point.z;
		result.y = (num7 + num12) * point.x + (1 - (num4 + num6)) * point.y +
			(num9 - num10) * point.z;
		result.z = (num8 - num11) * point.x + (num9 + num10) * point.y +
			(1 - (num4 + num5)) * point.z;
		return result;
	}



	inline float dot(const Vector4& vector)
	{
		return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
	}

	inline float distance(const Vector4& vector)
	{
		return sqrtf(
			(x - vector.x) * (x - vector.x) +
			(y - vector.y) * (y - vector.y) +
			(z - vector.z) * (z - vector.z) +
			(w - vector.w) * (w - vector.w));
	}

	bool operator==(const Vector4& vector) const
	{
		return x == vector.x && y == vector.y && z == vector.z && w == vector.w;
	}

	Vector4 operator*(const Vector4& v) const
	{
		return Vector4(this->x * v.x,
			this->y * v.y,
			this->z * v.z,
			this->w * v.w);
	}

	bool operator!=(const Vector4& vector) const
	{
		return x != vector.x || y != vector.y || z != vector.z || w != vector.w;
	}

	Vector3 vm(const Vector3& point)
	{
		float x = x * 2.f;
		float y = y * 2.f;
		float z = z * 2.f;
		float xx = x * x;
		float yy = y * y;
		float zz = z * z;
		float xy = x * y;
		float xz = x * z;
		float yz = y * z;
		float wx = w * x;
		float wy = w * y;
		float wz = w * z;

		Vector3 res;
		res.x = (1.f - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
		res.y = (xy + wz) * point.x + (1.f - (xx + zz)) * point.y + (yz - wx) * point.z;
		res.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.f - (xx + yy)) * point.z;
		return res;
	}
	static Vector4 Zero()
	{
		return Vector4(0, 0, 0, 0);
	}
	Vector4 LookRotation(Vector3& forward, Vector3& up)
	{
		/*
		forward = forward.normalize();

		Vector3 right = Vector3.Normalize(Vector3.Cross(up, forward));
		up = Vector3.Cross(forward, right);
		var m00 = right.x;
		var m01 = right.y;
		var m02 = right.z;
		var m10 = up.x;
		var m11 = up.y;
		var m12 = up.z;
		var m20 = forward.x;
		var m21 = forward.y;
		var m22 = forward.z;


		float num8 = (m00 + m11) + m22;
		var quaternion = new MyVector4();
		if (num8 > 0f)
		{
			var num = (float)System.Math.Sqrt(num8 + 1f);
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;
			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			var num7 = (float)System.Math.Sqrt(((1f + m00) - m11) - m22);
			var num4 = 0.5f / num7;
			quaternion.x = 0.5f * num7;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = (m12 - m21) * num4;
			return quaternion;
		}
		if (m11 > m22)
		{
			var num6 = (float)System.Math.Sqrt(((1f + m11) - m00) - m22);
			var num3 = 0.5f / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;
			return quaternion;
		}
		var num5 = (float)System.Math.Sqrt(((1f + m22) - m00) - m11);
		var num2 = 0.5f / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = (m01 - m10) * num2;
		return quaternion;
		*/
	}

	Vector4 operator+(const Vector4& vector) const
	{
		return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
	}

	Vector4 operator-(const Vector4& vector) const
	{
		return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
	}

	Vector4 operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}

	Vector4 operator*(float number) const
	{
		return Vector4(x * number, y * number, z * number, w * number);
	}

	Vector4 operator/(float number) const
	{
		return Vector4(x / number, y / number, z / number, w / number);
	}

	Vector4& operator+=(const Vector4& vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;
		return *this;
	}

	Vector4& operator-=(const Vector4& vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;
		return *this;
	}

	Vector4& operator*=(float number)
	{
		x *= number;
		y *= number;
		z *= number;
		w *= number;
		return *this;
	}

	Vector4& operator/=(float number)
	{
		x /= number;
		y /= number;
		z /= number;
		w /= number;
		return *this;
	}
};