#pragma once
#ifndef EAGLE_GRAPHICS_H
#define EAGLE_GRAPHICS_H
#include "./EagleMath.h"

namespace Eagle {
	class Color {
	public:
		Color();
		Color(unsigned char red, unsigned char green, unsigned char blue);
		Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
		Color(unsigned char red, unsigned char green, unsigned char blue, float alpha);

		Color& Blend(const Color& color);

		void SetRed(unsigned char red);
		void SetGreen(unsigned char green);
		void SetBlue(unsigned char blue);
		void SetAlpha(unsigned char alpha);

		unsigned char GetRed() const;
		unsigned char GetGreen() const;
		unsigned char GetBlue() const;
		unsigned char GetAlpha() const;

		Color& operator()();
		Color& operator()(unsigned char red, unsigned char green, unsigned char blue);
		Color& operator()(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
		Color& operator()(unsigned char red, unsigned char green, unsigned char blue, float alpha);
		operator unsigned int() const;
	protected:
		unsigned int m_value;
	};

	class Canvas {
	public:
		Canvas();
		Canvas(unsigned int width, unsigned int height);
		Canvas(const Canvas& canvas);
		~Canvas();

		bool Copy(const Canvas& canvas, unsigned int sourceX, unsigned int sourceY, unsigned int destinationX, unsigned int destinationY, unsigned int width, unsigned int height);
		bool Truncate(unsigned int x, unsigned int y, unsigned int width, unsigned int height);			//	CAN BE EXTENDED IN CHILD CLASS
		bool DrawPointI(const Color& color, const IPoint2D point);
		bool DrawPointF(const Color& color, const FPoint2D point);
		bool DrawRectangleI(const Color& color, const IPoint2D point1, const IPoint2D point2);
		bool DrawRectangleF(const Color& color, const FPoint2D point1, const FPoint2D point2);
		bool DrawLineI(const Color& color, const IPoint2D point1, const IPoint2D point2);
		bool DrawLineF(const Color& color, const FPoint2D point1, const FPoint2D point2);
		bool DrawCircleI(const Color& color, const IPoint2D center, int radius);
		bool DrawCircleF(const Color& color, const FPoint2D center, float radius);
		bool DrawPolygonI(const Color& color, const IPoint2D* vertices, unsigned int count);
		bool DrawPolygonF(const Color& color, const FPoint2D* vertices, unsigned int count);
		bool IsPointInPolygonI(const IPoint2D point, const IPoint2D* vertices, unsigned int count);
		bool IsPointInPolygonF(const FPoint2D point, const FPoint2D* vertices, unsigned int count);

		const Color* GetColorsArray() const;
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		bool Update(float alpha = 1.0);																	//	MUST BE IMPLEMENTED IN CHILD CLASS
		bool Render(float alpha = 1.0);																	//	MUST BE IMPLEMENTED IN CHILD CLASS
		bool IsWindowSizeChanged() const;																//	MUST BE IMPLEMENTED IN CHILD CLASS

		Color& operator[](unsigned int index);
		const Color& operator[](unsigned int index) const;
	protected:
		Color* m_colors;
		unsigned int m_width;
		unsigned int m_height;
	};
}

#endif