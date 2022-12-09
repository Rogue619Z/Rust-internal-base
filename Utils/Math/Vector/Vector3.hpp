class Vector3 {
public:
	float x, y, z;

	Vector3() { /* If no value has been set use 0.f */
		x = y = z = 0.f;
	}

	Vector3(float newX, float newY, float newZ) { /* If value has been set, set the Vector to the value. */
		x = newX;
		y = newY;
		z = newZ;
	}

	Vector3 operator+(float fInput) const {/* Allows Vector to add itself to a float */
		return Vector3{ x + fInput, y + fInput, z + fInput };
	}

	Vector3 operator-(float fInput) const { /* Allows Vector to subtract itself to a float */
		return Vector3{ x - fInput, y - fInput, z - fInput };
	}

	Vector3 operator/(float fInput) const {/* Allows Vector to divide itself from a float */
		return Vector3{ x / fInput, y / fInput, z / fInput };
	}

	Vector3 operator*(float fInput) const { /* Allows Vector to multiply itself from a float */
		return Vector3{ x * fInput, y * fInput, z * fInput };
	}

	Vector3 operator+(const Vector3& vInput) const {  /* Allows Vector to add itself to another Vector */
		return Vector3{ x + vInput.x, y + vInput.y, z + vInput.z };
	}

	Vector3 operator-(const Vector3& vInput) const { /* Allows Vector to subtract itself by another Vector */
		return Vector3{ x - vInput.x, y - vInput.y, z - vInput.z };
	}

	Vector3 operator*(Vector3 vInput) const { /* Allows Vector to multiply itself by another Vector */
		return Vector3{ x * vInput.x, y * vInput.y, z * vInput.z };
	}

	Vector3 operator/(Vector3 vInput) const { /* Allows Vector to divide itself by another Vector */
		return Vector3{ x / vInput.x, y / vInput.y, z / vInput.z };
	}

	Vector3& operator-=(const Vector3& vInput) {/* Allows Vector to be subtracted by another Vector */
		x -= vInput.x;
		y -= vInput.y;
		z -= vInput.z;

		return *this;
	}

	Vector3& operator+=(const Vector3& vInput) { /* Allows Vector to be added to another Vector */
		x += vInput.x;
		y += vInput.y;
		z += vInput.z;
		return *this;
	}

	Vector3& operator*=(const Vector3& vInput) { /* Allows Vector to be multiplied by another Vector */
		x *= vInput.x;
		y *= vInput.y;
		z *= vInput.z;
		return *this;
	}

	Vector3& operator/=(const Vector3& vInput) { /* Allows Vector to be multiplied by another Vector */
		x /= vInput.x;
		y /= vInput.y;
		z /= vInput.z;
		return *this;
	}

	Vector3& operator/=(float fInput) { /* Allows Vector to be divided by a float */
		x /= fInput;
		y /= fInput;
		z /= fInput;
		return *this;
	}

	Vector3& operator*=(float fInput) { /* Allows Vector to be multiplied by a float */
		x *= fInput;
		y *= fInput;
		z *= fInput;
		return *this;
	}

	Vector3& operator-=(float fInput) { /* Allows Vector to be subtracted by a float */
		x -= fInput;
		y -= fInput;
		z -= fInput;
		return *this;
	}
	bool is_nan() { return isnan(x) || isnan(x) || isnan(x); }
	Vector3& operator+=(float fInput) { /* Allows Vector to be added to a float */
		x += fInput;
		y += fInput;
		z += fInput;
		return *this;
	}
#define M_PI_2 1.57079632679489661923
#define M_PI 3.14159265358979323846
#define D3DXToRadian(degree) ((degree) * (M_PI / 180.0f))
#define RAD_TO_DEG 180 / 3.141592654f

	static double my_atan(double x)
	{
		// Return arctangent(x) given that 5/3 < x <= 2, with the same properties as atan.
		auto atani5 = [](double x) {
			constexpr double p00 = +0x1.124A85750FB5Cp+00;
			constexpr double p01 = +0x1.D59AE78C11C49p-03;
			constexpr double p02 = -0x1.8AD3C44F10DC3p-04;
			constexpr double p03 = +0x1.2B090AAD5F9DCp-05;
			constexpr double p04 = -0x1.881EC3D15241Fp-07;
			constexpr double p05 = +0x1.8CB82A74E0699p-09;
			constexpr double p06 = -0x1.3182219E21362p-12;
			constexpr double p07 = -0x1.2B9AD13DB35A8p-12;
			constexpr double p08 = +0x1.10F884EAC0E0Ap-12;
			constexpr double p09 = -0x1.3045B70E93129p-13;
			constexpr double p10 = +0x1.00B6A460AC05Dp-14;

			double y = x - 0x1.d555555461337p0;

			return ((((((((((+p10) * y + p09) * y + p08) * y + p07) * y + p06) * y +
				p05) *
				y +
				p04) *
				y +
				p03) *
				y +
				p02) *
				y +
				p01) *
				y +
				p00;
		};
		// Return arctangent(x) given that 4/3 < x <= 5/3, with the same properties as
		// atan.
		auto atani4 = [](double x) {
			constexpr double p00 = +0x1730BD281F69Dp-01;
			constexpr double p01 = +0x1.3B13B13B13B0Cp-02;
			constexpr double p02 = -0x1.22D719C06115Ep-03;
			constexpr double p03 = +0x1.C963C83985742p-05;
			constexpr double p04 = -0x1.135A0938EC462p-06;
			constexpr double p05 = +0x1.13A254D6E5B7Cp-09;
			constexpr double p06 = +0x1.DFAA5E77B7375p-10;
			constexpr double p07 = -0x14AC1342182D2p-10;
			constexpr double p08 = +0x1.25BAD4D85CBE1p-10;
			constexpr double p09 = -0x1.E4EEF429EB680p-12;
			constexpr double p10 = +0x1.B4E30D1BA3819p-14;
			constexpr double p11 = +0x1.0280537F097F3p-15;

			double y = x - 0x1.8000000000003p0;

			return (((((((((((+p11) * y + p10) * y + p09) * y + p08) * y + p07) * y +
				p06) *
				y +
				p05) *
				y +
				p04) *
				y +
				p03) *
				y +
				p02) *
				y +
				p01) *
				y +
				p00;
		};
		// Return arctangent(x) given that 1 < x <= 4 / 3, with the same properties as
		// atan.
		auto atani3 = [](double x) {
			constexpr double p00 = +0x1.B96E5A78C5C40p-01;
			constexpr double p01 = +0x1.B1B1B1B1B1B3Dp-02;
			constexpr double p02 = -0x1.AC97826D58470p-03;
			constexpr double p03 = +0x1.3FD2B9F586A67p-04;
			constexpr double p04 = -0x1.BC317394714B7p-07;
			constexpr double p05 = -0x1.2B01FC60CC37Ap-07;
			constexpr double p06 = +0x1.73A9328786665p-07;
			constexpr double p07 = -0x1.C0B993A09CE31p-08;
			constexpr double p08 = +0x1.2FCDACDD6E5B5p-09;
			constexpr double p09 = +0x1.CBD49DA316282p-13;
			constexpr double p10 = -0x1.0120E602F6336p-10;
			constexpr double p11 = +0x1.A89224FF69018p-11;
			constexpr double p12 = -0x1.883D8959134B3p-12;

			double y = x - 0x1.2aaaaaaaaaa96p0;

			return ((((((((((((+p12) * y + p11) * y + p10) * y + p09) * y + p08) * y +
				p07) *
				y +
				p06) *
				y +
				p05) *
				y +
				p04) *
				y +
				p03) *
				y +
				p02) *
				y +
				p01) *
				y +
				p00;
		};
		// Return arctangent(x) given that 3 / 4 < x <= 1, with the same properties as
		// atan.
		auto atani2 = [](double x) {
			constexpr double p00 = +0x1.700A7C580EA7Ep-01;
			constexpr double p01 = +0x1.21FB781196AC3p-01;
			constexpr double p02 = -0x1.1F6A8499714A2p-02;
			constexpr double p03 = +0x1.41B15E5E8DCD0p-04;
			constexpr double p04 = +0x1.59BC93F81895Ap-06;
			constexpr double p05 = -0x1.63B543EFFA4EFp-05;
			constexpr double p06 = +0x1.C90E92AC8D86Cp-06;
			constexpr double p07 = -0x1.91F7E2A7A338Fp-08;
			constexpr double p08 = -0x1.AC1645739E676p-08;
			constexpr double p09 = +0x1.152311B180E6Cp-07;
			constexpr double p10 = -0x1.265EF51B17DB7p-08;
			constexpr double p11 = +0x1.CA7CDE5DE9BD7p-14;

			double y = x - 0x1.c0000000f4213p-1;

			return (((((((((((+p11) * y + p10) * y + p09) * y + p08) * y + p07) * y +
				p06) *
				y +
				p05) *
				y +
				p04) *
				y +
				p03) *
				y +
				p02) *
				y +
				p01) *
				y +
				p00;
		};
		// Return arctangent(x) given that 1/2 < x <= 3/4, with the same properties as
		// atan.
		auto atani1 = [](double x) {
			constexpr double p00 = +0x1.1E00BABDEFED0p-1;
			constexpr double p01 = +0x1.702E05C0B8155p-1;
			constexpr double p02 = -0x1.4AF2B78215A1Bp-2;
			constexpr double p03 = +0x1.5D0B7E9E69054p-6;
			constexpr double p04 = +0x1.A1247CA5D9475p-4;
			constexpr double p05 = -0x1.519E110F61B54p-4;
			constexpr double p06 = +0x1.A759263F377F2p-7;
			constexpr double p07 = +0x1.094966BE2B531p-5;
			constexpr double p08 = -0x1.09BC0AB7F914Cp-5;
			constexpr double p09 = +0x1F3B7C531AA4Ap-8;
			constexpr double p10 = +0x1.950E69DCDD967p-7;
			constexpr double p11 = -0x1.D88D31ABC3AE5p-7;
			constexpr double p12 = +0x1.10F3E20F6A2E2p-8;

			double y = x - 0x1.4000000000027p-1;

			return ((((((((((((+p12) * y + p11) * y + p10) * y + p09) * y + p08) * y +
				p07) *
				y +
				p06) *
				y +
				p05) *
				y +
				p04) *
				y +
				p03) *
				y +
				p02) *
				y +
				p01) *
				y +
				p00;
		};
		// Return arctangent(x) given that 0x1p-27 < |x| <= 1/2, with the same properties
		// as atan.
		auto atani0 = [](double x) {
			constexpr double p03 = -0x1.555555555551Bp-2;
			constexpr double p05 = +0x1.99999999918D8p-3;
			constexpr double p07 = -0x1.2492492179CA3p-3;
			constexpr double p09 = +0x1.C71C7096C2725p-4;
			constexpr double p11 = -0x1.745CF51795B21p-4;
			constexpr double p13 = +0x1.3B113F18AC049p-4;
			constexpr double p15 = -0x1.10F31279EC05Dp-4;
			constexpr double p17 = +0x1.DFE7B9674AE37p-5;
			constexpr double p19 = -0x1.A38CF590469ECp-5;
			constexpr double p21 = +0x1.56CDB5D887934p-5;
			constexpr double p23 = -0x1.C0EB85F543412p-6;
			constexpr double p25 = +0x1.4A9F5C4724056p-7;

			// Square x.
			double x2 = x * x;

			return ((((((((((((+p25) * x2 + p23) * x2 + p21) * x2 + p19) * x2 + p17) *
				x2 +
				p15) *
				x2 +
				p13) *
				x2 +
				p11) *
				x2 +
				p09) *
				x2 +
				p07) *
				x2 +
				p05) *
				x2 +
				p03) *
				x2 * x +
				x;
		};
		// Return arctangent(x) given that 2 < x, with the same properties as atan.
		auto Tail = [](double x) {
			{
				constexpr double HalfPi = 0x3.243f6a8885a308d313198a2e037ap-1;

				// For large x, generate inexact and return pi/2.
				if (0x1p53 <= x)
					return HalfPi + DBL_EPSILON;
				if (x != x) // isnan
					return x - x;
			}

			constexpr double p03 = -0x1.5555555554A51p-2;
			constexpr double p05 = +0x1.999999989EBCAp-3;
			constexpr double p07 = -0x1.249248E1422E3p-3;
			constexpr double p09 = +0x1.C71C5EDFED480p-4;
			constexpr double p11 = -0x1.745B7F2D72663p-4;
			constexpr double p13 = +0x1.3AFD7A0E6EB75p-4;
			constexpr double p15 = -0x1.104146B1A1AE8p-4;
			constexpr double p17 = +0x1.D78252FA69C1Cp-5;
			constexpr double p19 = -0x1.81D33E401836Dp-5;
			constexpr double p21 = +0x1.007733E06CEB3p-5;
			constexpr double p23 = -0x1.83DAFDA7BD3FDp-7;

			constexpr double p000 = +0x1.921FB54442D18p0;
			constexpr double p001 = +0x1.1A62633145C07p-54;

			double y = 1 / x;

			// Square y.
			double y2 = y * y;

			return p001 -
				((((((((((((+p23) * y2 + p21) * y2 + p19) * y2 + p17) * y2 + p15) *
					y2 +
					p13) *
					y2 +
					p11) *
					y2 +
					p09) *
					y2 +
					p07) *
					y2 +
					p05) *
					y2 +
					p03) *
					y2 * y +
					y) +
				p000;
		};

		if (x < 0)
			if (x < -1)
				if (x < -5 / 3.)
					if (x < -2)
						return -Tail(-x);
					else
						return -atani5(-x);
				else if (x < -4 / 3.)
					return -atani4(-x);
				else
					return -atani3(-x);
			else if (x < -.5)
				if (x < -.75)
					return -atani2(-x);
				else
					return -atani1(-x);
			else if (x < -0x1.d12ed0af1a27fp-27)
				return atani0(x);
			else if (x <= -0x1p-1022)
				// Generate inexact and return x.
				return (DBL_EPSILON + 1) * x;
			else if (x == 0)
				return x;
			else
				// Generate underflow and return x.
				return x * DBL_EPSILON + x;
		else if (x <= +1)
			if (x <= +.5)
				if (x <= +0x1.d12ed0af1a27fp-27)
					if (x < +0x1p-1022)
						if (x == 0)
							return x;
						else
							// Generate underflow and return x.
							return x * DBL_EPSILON + x;
					else
						// Generate inexact and return x.
						return (DBL_EPSILON + 1) * x;
				else
					return atani0(x);
			else if (x <= +.75)
				return +atani1(+x);
			else
				return +atani2(+x);
		else if (x <= +5 / 3.)
			if (x <= +4 / 3.)
				return +atani3(+x);
			else
				return +atani4(+x);
		else if (x <= +2)
			return +atani5(+x);
		else
			return +Tail(+x);
	}

	static float my_sin(float x)
	{
		// useful to pre-calculate
		double x2 = x * x;
		double x4 = x2 * x2;

		// Calculate the terms
		// As long as abs(x) < sqrt(6), which is 2.45, all terms will be positive.
		// Values outside this range should be reduced to [-pi/2, pi/2] anyway for
		// accuracy. Some care has to be given to the factorials. They can be
		// pre-calculated by the compiler, but the value for the higher ones will exceed
		// the storage capacity of int. so force the compiler to use unsigned long longs
		// (if available) or doubles.
		double t1 = x * (1.0 - x2 / (2 * 3));
		double x5 = x * x4;
		double t2 = x5 * (1.0 - x2 / (6 * 7)) / (1.0 * 2 * 3 * 4 * 5);
		double x9 = x5 * x4;
		double t3 = x9 * (1.0 - x2 / (10 * 11)) / (1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9);
		double x13 = x9 * x4;
		double t4 = x13 * (1.0 - x2 / (14 * 15)) /
			(1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13);
		double x14 = x13 * x4;
		double t5 =
			x14 * (1.0 - x2 / (18 * 19)) /
			(1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17);
		double x15 = x14 * x4;
		double t6 = x15 * (1.0 - x2 / (22 * 23)) /
			(1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 *
				16 * 17 * 18 * 19 * 20 * 21);
		// add some more if your accuracy requires them.
		// But remember that x is smaller than 2, and the factorial grows very fast
		// so I doubt that 2^17 / 17! will add anything.
		// Even t4 might already be too small to matter when compared with t1.

		// Sum backwards
		double result = t6;
		result += t5;
		result += t4;
		result += t3;
		result += t2;
		result += t1;

		return result;
	}

	static Vector3 Zero() {
		return Vector3(0.0f, 0.0f, 0.0f);
	}
	static float my_sqrt(float number)
	{
		long        i;
		float       x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *(long*)&y; // floating point bit level hacking [sic]
		i = 0x5f3759df - (i >> 1); // Newton's approximation
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y)); // 1st iteration
		y = y * (threehalfs - (x2 * y * y)); // 2nd iteration

		return 1 / y;
	}
	static float my_atan2(float y, float x)
	{
		// https://en.wikipedia.org/wiki/Atan2#Definition (A compact expression with four
		// overlapping half-planes is: ...)
		if (x == 0) {
			if (y > 0.0f)
				return M_PI_2;
			else if (y < 0.0f)
				return -M_PI_2;
			return 0;
		}
		else if (x > 0)
			return my_atan(y / x);
		else if (x < 0)
			return M_PI + my_atan(y / x);
		else if (y > 0)
			return M_PI_2 - my_atan(y / x);
		else if (y < 0)
			return -M_PI_2 - my_atan(y / x);
		return 0;
	}
	static float Clamp01(float value)
	{
		if (value < 0.f)
			return 0.f;
		else if (value > 1.f)
			return 1.f;
		else
			return value;
	}
	float dot_product(Vector3 input) const {
		return (x * input.x) + (y * input.y) + (z * input.z);
	}
	static float my_cos(float x) { return my_sin(x + M_PI_2); }

	static float my_asin(float x) { return my_atan2(x, my_sqrt(1.0 - (x * x))); }


	static float InverseLerp(float a, float b, float value)
	{
		bool flag = a != b;
		float result;
		if (flag)
		{
			result = Clamp01((value - a) / (b - a));
		}
		else
		{
			result = 0.f;
		}
		return result;
	}
	static float LerpFloat(float a, float b, float t)
	{
		return a + (b - a) * Clamp01(t);
	}
	static Vector3 Lerp(Vector3 a, Vector3 b, float t)
	{
		t = Clamp01(t);
		return Vector3(
			a.x + (b.x - a.x) * t,
			a.y + (b.y - a.y) * t,
			a.z + (b.z - a.z) * t
		);
	}
	bool operator==(const Vector3& vInput) const { /* Checks if Vector is Equal with another Vector */
		return x == vInput.x && y == vInput.y && z == vInput.z;
	}
	static Vector3 move_towards(Vector3 current, Vector3 target, float maxDistanceDelta)
	{
		float toVector_x = target.x - current.x;
		float toVector_y = target.y - current.y;
		float toVector_z = target.z - current.z;

		float sqdist = toVector_x * toVector_x + toVector_y * toVector_y + toVector_z * toVector_z;

		if (sqdist == 0 || (maxDistanceDelta >= 0 && sqdist <= maxDistanceDelta * maxDistanceDelta))
			return target;
		auto dist = (float)sqrt(sqdist);

		return Vector3(current.x + toVector_x / dist * maxDistanceDelta,
			current.y + toVector_y / dist * maxDistanceDelta,
			current.z + toVector_z / dist * maxDistanceDelta);
	}

	bool operator!=(const Vector3& vInput) const {  /* Checks if Vector is NOT Equal with another Vector */
		if (x != vInput.x || y != vInput.y || z != vInput.z)
			return true;

		return false;
	}
	float UnityMagnitude()
	{
		return (float)sqrt((double)(this->x * this->x + this->y * this->y + this->z * this->z));
	}
	inline float UnityDot(Vector3 lhs, Vector3 rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}
	void UnityNormalize()
	{
		Vector3 tis(x, y, z);
		float num = Vector3(x, y, z).Magnitude();
		if (num > 1E-05f)
		{
			tis /= num;
		}
		else
		{
			tis = Vector3(0, 0, 0);
		}
		x = tis.x;
		y = tis.y;
		z = tis.z;
	}

	void Abs() {
		x = abs(x);
		y = abs(y);
		z = abs(z);
	}

	float LengthSqr() const {
		return (x * x) + (y * y) + (z * z);
	}

	float Length() const {
		return sqrt(LengthSqr());
	}

	float Length2D() const {
		return sqrt((x * x) + (y * y));
	}

	float Distance(Vector3 vInput) const {
		return (*this - vInput).Length();
	}

	float Distance2D(Vector3 vInput) const {
		return (*this - vInput).Length2D();
	}

	auto Dot(const Vector3& vector) -> float { return x * vector.x + y * vector.y + z * vector.z; }

	float Magnitude() {
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float Magnitude2D() {
		return sqrt(this->x * this->x + this->z * this->z);
	}

	Vector3 Normalized() const {
		return { x / Length(), y / Length(), z / Length() };
	}


	bool Empty() const {
		return x == 0.f && y == 0.f && z == 0.f;
	}
};