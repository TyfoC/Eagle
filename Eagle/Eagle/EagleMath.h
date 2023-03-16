#pragma once
#ifndef EAGLE_MATH_H
#define EAGLE_MATH_H

#include "EagleDefinitions.h"

/*
	Signle-precision floating-point format:
		[----------][Sign|exponent|fraction]
		[Bits count][ 1  |   8    |   23   ]
		value = ((-1) ^ sign) * (2 ^ (exponent - 127)) * 1.(Bit[22] | ... | Bit[1] | Bit[0])

	Double-precision floating-point format:
		[----------][Sign|exponent|fraction]
		[Bits count][ 1  |   11   |   52   ]
		value = ((-1) ^ sign) * (2 ^ (exponent - 1023)) * 1.(Bit[51] | ... | Bit[1] | Bit[0])
*/

namespace Eagle {
	template <typename T> static inline void Swap(T& first, T& second) {
		T tmp = first;
		first = second;
		second = tmp;
	}

	template <typename T> static inline T Absolute(const T value) {
		return value >= 0 ? value : -value;
	}

	static inline double Power(double value, double power) {
		union {
			double	DoublePart;
			int		IntPart[2];
		} tmp = { };

		tmp.DoublePart = value;
		tmp.IntPart[1] = (int)(power * (int)((unsigned long long)tmp.IntPart[1] - 0x3fef127f) + 0x3fef127f);
		tmp.IntPart[0] = 0;
		return tmp.DoublePart;
	}

	//	converting the exponent and clearing the sign, exponent, and last fraction bits
	static inline long long Double2Int(double value) {
		union {
			double		DoublePart;
			long long	LongLongPart;
		} tmp = { };

		tmp.DoublePart = value + 6755399441055744.0;		//	exponent[0] and fraction[51] bits
		tmp.LongLongPart <<= 13;
		tmp.LongLongPart >>= 13;
		return tmp.LongLongPart;
	}

	static inline double Deg2Rad(double degrees) {
		return degrees * OneRadian;
	}

	static inline double Rad2Deg(double radians) {
		return radians * OneDegree;
	}

	static inline double Round(double value, long long digitsAfterPoint) {
		const double factor = Power(10, (double)digitsAfterPoint);
		return (double)Double2Int(value * factor) / factor;
	}

	static inline double Ceil(double value) {
		long long lvalue = (long long)value;
		return (double)(value == (double)lvalue ? lvalue : (value >= 0.0 ? lvalue + 1.0 : lvalue));
	}

	static inline double Floor(double value) {
		if (value >= 0.0 && value < 0.4) return 0.0;

		double n = 1;
		double valueCopy = value < 0 ? 0 - value : value;
		unsigned int zeros = 0;

		for (n = 1; valueCopy > n * 10; n *= 10, ++zeros);
		for (valueCopy -= n; zeros != -1; valueCopy -= n) if (valueCopy < 0) {
			valueCopy += n;
			n /= 10;
			zeros -= 1;
		}

		valueCopy += n;
		return value < 0 ? (valueCopy == 0 ? value : value - (1 - valueCopy)) : value - valueCopy;
	}

	static inline double Truncate(double value) {
		return value > 0.0 ? Floor(value) : Ceil(value);
	}

	static inline double Mod(double first, double second) {
		return first - second * Floor(first / second);
	}

	static inline double Factorial(int value) {
		double result = 1;
		for (; value >= 1; value--) result = value * result;
		return result;
	}

	//	optimized Quake 3 algorithm
	static inline float InverseSqrt32(float value) {
		union {
			float	FloatPart;
			int		IntPart;
		} tmp = {};

		tmp.FloatPart = value;
		tmp.IntPart = 0x5f1ffff9 - (tmp.IntPart >> 1);
		tmp.FloatPart *= 0.703952253f * (2.38924456f - value * tmp.FloatPart * tmp.FloatPart);

		return tmp.FloatPart;
	}

	//	Quake 3 algorithm for x64
	static inline double InverseSqrt64(double value) {
		union {
			double		DoublePart;
			long long	LongLongPart;
		} tmp = {};

		tmp.DoublePart = value;
		tmp.LongLongPart = 0x5fe6eb50c7b537a9 - (tmp.LongLongPart >> 1);
		tmp.DoublePart *= (1.5 - (0.5 * value * tmp.DoublePart * tmp.DoublePart));

		return tmp.DoublePart;
	}

	static inline double InverseSqrt(double value, bool betterPrecision = true) {
		return betterPrecision ? InverseSqrt64(value) : InverseSqrt32((float)value);
	}

	static inline double Sqrt(double value, bool betterPrecise = true) {
		return Power(InverseSqrt(value, betterPrecise), -1);
	}

	//	Taylor series
	static inline double Cosine(double radians, double precision = SineCosinePrecision) {
		if (radians >= PiTwo || radians <= 0 - PiTwo) radians = Mod(radians, PiTwo);
		double t = 1.0, result = 1.0, radiansSquare = radians * radians;
		long long p = 0;

		while (Absolute(t / result) > precision) {
			p += 1;
			t = ((0.0 - t) * radiansSquare) / (double)((2 * p - 1) * (2 * p));
			result += t;
		}

		return result;
	}

	//	sin(x) = cos(x - Pi / 2)
	static inline double Sine(double radians, double precision = SineCosinePrecision) {
		if (radians >= PiTwo || radians <= 0 - PiTwo) radians = Mod(radians, PiTwo);
		return Cosine(radians - PiHalf, precision);
	}

	//	sin(x) = cos(x - Pi / 2)
	static inline double SineFromCosine(double radians, double precision = SineCosinePrecision) {
		return Cosine(radians - PiHalf, precision);
	}

	//	cos(x) = sin(Pi / 2 - x)
	static inline double CosineFromSine(double radians, double precision = SineCosinePrecision) {
		return Sine(PiHalf - radians, precision);
	}

	static inline double Tangent(double radians) {
		return Sine(radians) / Cosine(radians);
	}

	static inline double Cotangent(double radians) {
		return Cosine(radians) / Sine(radians);
	}
}
#endif