#pragma once
#ifndef EAGLE_GRAPHICS_H
#define EAGLE_GRAPHICS_H

#include "EagleTypes.h"

namespace Eagle {
	class Color {
	public:
		Color();
		Color(unsigned char red, unsigned char green, unsigned char blue);
		Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
		Color(unsigned char red, unsigned char green, unsigned char blue, double alpha);

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
		Color& operator()(unsigned char red, unsigned char green, unsigned char blue, double alpha);
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

		void Redraw(const Color color = Color(0, 0, 0));
		bool Copy(const Canvas& canvas, unsigned int sourceX, unsigned int sourceY, unsigned int destinationX, unsigned int destinationY, unsigned int width, unsigned int height);
		bool Truncate(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		bool DrawPoint(const Color& color, const Point point);
		bool DrawRectangle(const Color& color, const Point point1, const Point point2);
		bool DrawLine(const Color& color, const Point point1, const Point point2);
		bool DrawCircle(const Color& color, const Point center, double radius);
		bool DrawPolygon(const Color& color, const Point* vertices, unsigned int count);
		bool IsPointInPolygon(const Point point, const Point* vertices, unsigned int count);

		Color* GetColors();
		const Color* GetColors() const;
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		Color& operator[](unsigned int index);
		const Color& operator[](unsigned int index) const;
	protected:
		Color* m_colors;
		unsigned int m_width;
		unsigned int m_height;
	};
}

#endif