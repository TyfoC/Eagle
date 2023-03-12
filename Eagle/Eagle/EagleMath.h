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

			unsigned char* destBuff = (unsigned char*)&tmp;
			unsigned char* srcBuff = (unsigned char*)&value;
			for (unsigned int i = 0; i < sizeof(tmp.DoublePart); i++) destBuff[i] = srcBuff[i];

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

		static inline double Ceil(double value) {														//	naive way
			long long lvalue = (long long)value;
			return (double)(value == (double)lvalue ? lvalue : (value >= 0.0 ? lvalue + 1.0 : lvalue));
		}

		static inline double Floor(double value) {
			if (value >= 0.0 && value < 0.4) return 0.0;

			double n = 1;
			double valueCopy = value < 0 ? -value : value;
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

		static inline float Sqrt(float value) {							//	only for 32-bit signed value
			unsigned int i = *(unsigned int*)&value;
			i += 127 << 23;
			i >>= 1;
			return *(float*)&i;
		}

		static inline double Cosine(double radians, double precise = 0.000001) {
			double t = 1.0, result = 1.0;
			int p = 0;
			double radiansSquare = radians * radians;

			while (Absolute(t / result) > precise) {
				p += 1;
				t = (-t * radiansSquare) / ((2 * p - 1) * (2 * p));
				result += t;
			}

			return result;
		}

		static inline double Sine(double radians) {
			double cosResult = Cosine(radians);
			double result = (double)Sqrt((float)(1 - cosResult * cosResult));
			return radians > 0.0 ? result : -result;
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