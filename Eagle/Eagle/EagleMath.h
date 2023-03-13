#pragma once
#ifndef EAGLE_MATH_H
#define EAGLE_MATH_H

namespace Eagle {
	class Math {
	public:
		static constexpr double Pi = 3.14159265358979323846;
		static constexpr double PiDouble = 2 * Pi;
		static constexpr double PiSquare = Pi * Pi;
		static constexpr double PiQuarter = 4 / Pi;
		static constexpr double OneRadian = Pi / 180.0;
		static constexpr double OneDegree = 180.0 / Pi;
		static constexpr unsigned int IEEE754x86Quake3FloatRepresentation = 0x5f3759df;		//	Better for precise: 

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

		static inline long long Double2Int(double value) {
			union {
				double		DoublePart;
				long long	LongLongPart;
			} tmp;

			tmp.DoublePart = value + 6755399441055744.0;
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

		static inline float InverseSqrt32(float value) {
			union {
				float	FloatPart;
				int		IntPart;
			} tmp;

			tmp.FloatPart = value;
			tmp.IntPart = 0x5f1ffff9 - (tmp.IntPart >> 1);
			tmp.FloatPart *= 0.703952253f * (2.38924456f - value * tmp.FloatPart * tmp.FloatPart);

			return tmp.FloatPart;
		}

		static inline double InverseSqrt64(double value) {
			union {
				double		DoublePart;
				long long	LongLongPart;
			} tmp;

			tmp.DoublePart = value;
			tmp.LongLongPart = 0x5fe6eb50c7b537a9 - (tmp.LongLongPart >> 1);
			tmp.DoublePart *= (1.5 - (0.5 * value * tmp.DoublePart * tmp.DoublePart));

			return tmp.DoublePart;
		}

		static inline double InverseSqrt(double value, bool betterPrecise = true) {
			return betterPrecise ? InverseSqrt64(value) : InverseSqrt32((float)value);
		}

		static inline double Sqrt(double value, bool betterPrecise = true) {
			return Power(InverseSqrt(value, betterPrecise), -1);
		}

		static inline double Cosine(double radians, double precise = 0.000001) {
			double t = 1.0, result = 1.0, radiansSquare = radians * radians;
			int p = 0;

			while (Absolute(t / result) > precise) {
				p += 1;
				t = ((0 - t) * radiansSquare) / ((2 * p - 1) * (2 * p));
				result += t;
			}

			return result;
		}

		static inline double Sine(double radians) {
			double cosResult = Cosine(radians);
			double result = (double)Sqrt((float)(1 - cosResult * cosResult));
			return radians > 0.0 ? result : 0 - result;
		}

		static inline double Tangent(double radians) {
			return Sine(radians) / Cosine(radians);
		}

		static inline double Cotangent(double radians) {
			return Cosine(radians) / Sine(radians);
		}
	};
}

#endif