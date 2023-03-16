#pragma once
#ifndef EAGLE_TYPES_H
#define EAGLE_TYPES_H

#include "EagleMath.h"

namespace Eagle {
	struct Point {
		Point& operator+=(const double value);
		Point& operator-=(const double value);
		Point& operator*=(const double value);
		Point& operator/=(const double value);
		Point& operator%=(const double value);
		Point& operator+=(const Point point);
		Point& operator-=(const Point point);
		Point& operator*=(const Point point);
		Point& operator/=(const Point point);
		Point& operator%=(const Point point);
		Point operator+(const double value) const;
		Point operator-(const double value) const;
		Point operator*(const double value) const;
		Point operator/(const double value) const;
		Point operator%(const double value) const;
		Point operator+(const Point point) const;
		Point operator-(const Point point) const;
		Point operator*(const Point point) const;
		Point operator/(const Point point) const;
		Point operator%(const Point point) const;

		double X;
		double Y;
	};

	class Matrix {
	public:
		Matrix();
		Matrix(unsigned int width, unsigned int height);
		Matrix(unsigned int width, unsigned int height, const double* data);
		Matrix(const Matrix& matrix);
		~Matrix();

		bool Resize(unsigned int width, unsigned int height);
		bool Copy(const Matrix& matrix);
		bool Fill(unsigned int row, unsigned int column, const double* values, unsigned int count);
		static Matrix GetIdentityMatrix(unsigned int width);

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		unsigned int GetLength() const;

		double& operator()(int row, int column);
		const double& operator()(int row, int column) const;
		double& operator[](unsigned int index);
		const double& operator[](unsigned int index) const;
		Matrix operator+(const double& value) const;
		Matrix operator-(const double& value) const;
		Matrix operator*(const double& value) const;
		Matrix operator/(const double& value) const;
		Matrix operator%(const double& value) const;
		Matrix& operator+=(const double& value);
		Matrix& operator-=(const double& value);
		Matrix& operator*=(const double& value);
		Matrix& operator/=(const double& value);
		Matrix& operator%=(const double& value);
		Matrix operator+(const Matrix& matrix) const;
		Matrix operator-(const Matrix& matrix) const;
		Matrix operator*(const Matrix& matrix) const;
		Matrix& operator+=(const Matrix& matrix);
		Matrix& operator-=(const Matrix& matrix);
		Matrix& operator*=(const Matrix& matrix);
		Matrix& operator=(const Matrix& matrix);
	protected:
		double* m_values;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_length;
	};

	//	for homogeneous coordinate system
	struct Vector2D : public Point {
		Vector2D();
		Vector2D(double x, double y, double w = 1.0);
		Vector2D& operator+=(const double value);
		Vector2D& operator-=(const double value);
		Vector2D& operator*=(const double value);
		Vector2D& operator/=(const double value);
		Vector2D& operator%=(const double value);
		Vector2D& operator+=(const Vector2D vector);
		Vector2D& operator-=(const Vector2D vector);
		Vector2D& operator*=(const Vector2D vector);
		Vector2D& operator/=(const Vector2D vector);
		Vector2D& operator%=(const Vector2D vector);
		Vector2D& operator*=(const Matrix& matrix);
		Vector2D operator+(const double value) const;
		Vector2D operator-(const double value) const;
		Vector2D operator*(const double value) const;
		Vector2D operator/(const double value) const;
		Vector2D operator%(const double value) const;
		Vector2D operator+(const Vector2D vector) const;
		Vector2D operator-(const Vector2D vector) const;
		Vector2D operator*(const Vector2D vector) const;
		Vector2D operator/(const Vector2D vector) const;
		Vector2D operator%(const Vector2D vector) const;
		Vector2D operator*(const Matrix& matrix) const;

		double W = 1.0;
	};

	class Object2D {
	public:
		Object2D();
		Object2D(const Object2D& object);
		Object2D(const Vector2D* vertices, unsigned int count, const Vector2D position = { 0.0, 0.0 }, const Vector2D scale = { 1.0, 1.0 }, double rotation = 0.0);
		Object2D(const Point* points, unsigned int count, const Vector2D position = { 0.0, 0.0 }, const Vector2D scale = { 1.0, 1.0 }, double rotation = 0.0);
		~Object2D();

		Object2D ProduceTranslated() const;
		Object2D ProduceScaled() const;
		Object2D ProduceRotated() const;
		Object2D ProduceTransformed() const;

		void SetPosition(const Vector2D position);
		void SetScale(const Vector2D scale);
		void SetRotation(double rotation);

		Vector2D GetPosition() const;
		Vector2D GetScale() const;
		double GetRotation() const;

		Vector2D GetCenter() const;

		Vector2D* GetVectors();
		const Vector2D* GetVectors() const;
		Point* ProducePoints() const;
		unsigned int GetVectorsCount() const;

		Object2D& operator=(const Object2D& object);
		Vector2D& operator[](unsigned int index);
		const Vector2D& operator[](unsigned int index) const;
	protected:
		unsigned int m_count;
		Vector2D* m_vertices;
		Vector2D m_position;
		Vector2D m_scale;
		double m_rotation;
	};
}

#endif