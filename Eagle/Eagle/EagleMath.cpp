#include "EagleMath.h"

Eagle::IVector2D::IVector2D() {
	X = Y = 0;
}

Eagle::IVector2D::IVector2D(int x, int y) {
	X = x;
	Y = y;
}

Eagle::IVector2D Eagle::IVector2D::operator+(const int& value) const {
	return { X + value, Y + value };
}

Eagle::IVector2D Eagle::IVector2D::operator-(const int& value) const {
	return { X - value, Y - value };
}

Eagle::IVector2D Eagle::IVector2D::operator*(const int& value) const {
	return { X * value, Y * value };
}

Eagle::IVector2D Eagle::IVector2D::operator/(const int& value) const {
	return { X / value, Y / value };
}

Eagle::IVector2D Eagle::IVector2D::operator%(const int& value) const {
	return { X % value, Y % value };
}

Eagle::IVector2D& Eagle::IVector2D::operator+=(const int& value) {
	X += value;
	Y += value;
	return *this;
}

Eagle::IVector2D& Eagle::IVector2D::operator-=(const int& value) {
	X -= value;
	Y -= value;
	return *this;
}

Eagle::IVector2D& Eagle::IVector2D::operator*=(const int& value) {
	X *= value;
	Y *= value;
	return *this;
}

Eagle::IVector2D& Eagle::IVector2D::operator/=(const int& value) {
	X /= value;
	Y /= value;
	return *this;
}

Eagle::IVector2D& Eagle::IVector2D::operator%=(const int& value) {
	X %= value;
	Y %= value;
	return *this;
}

Eagle::IVector2D Eagle::IVector2D::operator+(const IVector2D& value) const {
	return { X + value.X, Y + value.Y };
}

Eagle::IVector2D Eagle::IVector2D::operator-(const IVector2D& value) const {
	return { X - value.X, Y - value.Y };
}

Eagle::IVector2D Eagle::IVector2D::operator*(const IVector2D& value) const {
	return { X * value.X, Y * value.Y };
}

Eagle::IVector2D Eagle::IVector2D::operator/(const IVector2D& value) const {
	return { X / value.X, Y / value.Y };
}

Eagle::IVector2D Eagle::IVector2D::operator%(const IVector2D& value) const {
	return { X % value.X, Y % value.Y };
}

Eagle::IVector2D& Eagle::IVector2D::operator+=(const IVector2D& value) {
	X += value.X;
	Y += value.Y;
	return *this;
}

Eagle::IVector2D& Eagle::IVector2D::operator-=(const IVector2D& value) {
	X -= value.X;
	Y -= value.Y;
	return *this;
}

Eagle::IVector2D& Eagle::IVector2D::operator*=(const IVector2D& value) {
	X *= value.X;
	Y *= value.Y;
	return *this;
}

Eagle::IVector2D& Eagle::IVector2D::operator/=(const IVector2D& value) {
	X /= value.X;
	Y /= value.Y;
	return *this;
}

Eagle::IVector2D& Eagle::IVector2D::operator%=(const IVector2D& value) {
	X %= value.X;
	Y %= value.Y;
	return *this;
}

Eagle::FVector2D::FVector2D() {
	X = Y = 0;
}

Eagle::FVector2D::FVector2D(float x, float y) {
	X = x;
	Y = y;
}

Eagle::FVector2D Eagle::FVector2D::operator+(const float& value) const {
	return { X + value, Y + value };
}

Eagle::FVector2D Eagle::FVector2D::operator-(const float& value) const {
	return { X - value, Y - value };
}

Eagle::FVector2D Eagle::FVector2D::operator*(const float& value) const {
	return { X * value, Y * value };
}

Eagle::FVector2D Eagle::FVector2D::operator/(const float& value) const {
	return { X / value, Y / value };
}

Eagle::FVector2D Eagle::FVector2D::operator%(const float& value) const {
	return { (float)Mod(X, value), (float)Mod(Y, value) };
}

Eagle::FVector2D& Eagle::FVector2D::operator+=(const float& value) {
	X += value;
	Y += value;
	return *this;
}

Eagle::FVector2D& Eagle::FVector2D::operator-=(const float& value) {
	X -= value;
	Y -= value;
	return *this;
}

Eagle::FVector2D& Eagle::FVector2D::operator*=(const float& value) {
	X *= value;
	Y *= value;
	return *this;
}

Eagle::FVector2D& Eagle::FVector2D::operator/=(const float& value) {
	X /= value;
	Y /= value;
	return *this;
}

Eagle::FVector2D& Eagle::FVector2D::operator%=(const float& value) {
	X = (float)Mod(X, value);
	Y = (float)Mod(Y, value);
	return *this;
}

Eagle::FVector2D Eagle::FVector2D::operator+(const FVector2D& value) const {
	return { X + value.X, Y + value.Y };
}

Eagle::FVector2D Eagle::FVector2D::operator-(const FVector2D& value) const {
	return { X - value.X, Y - value.Y };
}

Eagle::FVector2D Eagle::FVector2D::operator*(const FVector2D& value) const {
	return { X * value.X, Y * value.Y };
}

Eagle::FVector2D Eagle::FVector2D::operator/(const FVector2D& value) const {
	return { X / value.X, Y / value.Y };
}

Eagle::FVector2D Eagle::FVector2D::operator%(const FVector2D& value) const {
	return { (float)Mod(X, value.X), (float)Mod(Y, value.Y) };
}

Eagle::FVector2D& Eagle::FVector2D::operator+=(const FVector2D& value) {
	X += value.X;
	Y += value.Y;
	return *this;
}

Eagle::FVector2D& Eagle::FVector2D::operator-=(const FVector2D& value) {
	X -= value.X;
	Y -= value.Y;
	return *this;
}

Eagle::FVector2D& Eagle::FVector2D::operator*=(const FVector2D& value) {
	X *= value.X;
	Y *= value.Y;
	return *this;
}

Eagle::FVector2D& Eagle::FVector2D::operator/=(const FVector2D& value) {
	X /= value.X;
	Y /= value.Y;
	return *this;
}

Eagle::FVector2D& Eagle::FVector2D::operator%=(const FVector2D& value) {
	X = (float)Mod(X, value.X);
	Y = (float)Mod(Y, value.Y);
	return *this;
}

Eagle::Matrix::Matrix() {
	m_values = 0;
	m_width = m_height = m_length = 0;
}

Eagle::Matrix::Matrix(unsigned int width, unsigned int height) {
	unsigned int length = width * height;
	m_values = new double[width * height];
	if (m_values) m_width = width, m_height = height, m_length = length;
	else m_width = m_height = m_length = 0;
}

Eagle::Matrix::Matrix(unsigned int width, unsigned int height, const double* data) {
	unsigned int length = width * height;
	m_values = new double[length];
	if (m_values) {
		for (unsigned int i = 0; i < length; i++) m_values[i] = data[i];
		m_width = width, m_height = height, m_length = length;
	}
	else m_width = m_height = m_length = 0;
}

Eagle::Matrix::Matrix(const Matrix& matrix) {
	unsigned int length = matrix.m_width * matrix.m_height;
	m_values = new double[length];
	if (m_values) {
		for (unsigned int i = 0; i < length; i++) m_values[i] = matrix.m_values[i];
		m_width = matrix.m_width, m_height = matrix.m_height, m_length = length;
	}
	else m_width = m_height = m_length = 0;
}

Eagle::Matrix::~Matrix() {
	if (m_values) delete[] m_values;
	m_width = m_height = m_length = 0;
}

bool Eagle::Matrix::Resize(unsigned int width, unsigned int height) {
	if (!width || !height) return false;

	unsigned int length = width * height;
	double* newValues = new double[length];
	if (newValues) {
		for (unsigned int i = 0; i < length; i++) newValues[i] = m_values[i];
		m_width = width, m_height = height, m_length = length;
		if (m_values) delete[] m_values;
		m_values = newValues;
	}
	else m_width = m_height = m_length = 0;

	return true;
}

bool Eagle::Matrix::Copy(const Matrix& matrix) {
	double* newValues = new double[matrix.m_length];
	if (!newValues) return false;

	for (unsigned int i = 0; i < matrix.m_length; i++) newValues[i] = matrix.m_values[i];
	m_width = matrix.m_width, m_height = matrix.m_height, m_length = matrix.m_length;
	if (m_values) delete[] m_values;
	m_values = newValues;

	return true;
}

bool Eagle::Matrix::Fill(unsigned int row, unsigned int column, const double* values, unsigned int count) {
	unsigned int offset = column + row * m_width;
	unsigned int limit = offset + count;
	if (limit > m_length) return false;

	for (; offset < limit; offset++) m_values[offset] = values[count];

	return true;
}

Eagle::Matrix Eagle::Matrix::Identity() {
	Matrix matrix(m_width, m_width);
	if (!matrix.m_values) return matrix;

	for (unsigned int i = 0; i < m_length; i++) m_values[i] = 0;
	for (unsigned int i = 0; i < m_height; i++) matrix(i, i) = 1;

	return matrix;
}

unsigned int Eagle::Matrix::GetWidth() const {
	return m_width;
}

unsigned int Eagle::Matrix::GetHeight() const {
	return m_height;
}

unsigned int Eagle::Matrix::GetLength() const {
	return m_length;
}

double& Eagle::Matrix::operator()(int row, int column) {
	return m_values[column + row * m_width];
}

const double& Eagle::Matrix::operator()(int row, int column) const {
	return m_values[column + row * m_width];
}

double& Eagle::Matrix::operator[](unsigned int index) {
	return m_values[index];
}

const double& Eagle::Matrix::operator[](unsigned int index) const {
	return m_values[index];
}

Eagle::Matrix Eagle::Matrix::operator+(const double& value) const {
	Matrix matrixCopy(*this);
	for (unsigned int i = 0; i < matrixCopy.m_length; i++) matrixCopy.m_values[i] += value;
	return matrixCopy;
}

Eagle::Matrix Eagle::Matrix::operator-(const double& value) const {
	Matrix matrixCopy(*this);
	for (unsigned int i = 0; i < matrixCopy.m_length; i++) matrixCopy.m_values[i] -= value;
	return matrixCopy;
}

Eagle::Matrix Eagle::Matrix::operator*(const double& value) const {
	Matrix matrixCopy(*this);
	for (unsigned int i = 0; i < matrixCopy.m_length; i++) matrixCopy.m_values[i] *= value;
	return matrixCopy;
}

Eagle::Matrix Eagle::Matrix::operator/(const double& value) const {
	Matrix matrixCopy(*this);
	for (unsigned int i = 0; i < matrixCopy.m_length; i++) matrixCopy.m_values[i] /= value;
	return matrixCopy;
}

Eagle::Matrix Eagle::Matrix::operator%(const double& value) const {
	Matrix matrixCopy(*this);
	for (unsigned int i = 0; i < matrixCopy.m_length; i++) matrixCopy.m_values[i] = Mod(matrixCopy.m_values[i], value);
	return matrixCopy;
}

Eagle::Matrix& Eagle::Matrix::operator+=(const double& value) {
	for (unsigned int i = 0; i < m_length; i++) m_values[i] += value;
	return *this;
}

Eagle::Matrix& Eagle::Matrix::operator-=(const double& value) {
	for (unsigned int i = 0; i < m_length; i++) m_values[i] -= value;
	return *this;
}

Eagle::Matrix& Eagle::Matrix::operator*=(const double& value) {
	for (unsigned int i = 0; i < m_length; i++) m_values[i] *= value;
	return *this;
}

Eagle::Matrix& Eagle::Matrix::operator/=(const double& value) {
	for (unsigned int i = 0; i < m_length; i++) m_values[i] /= value;
	return *this;
}

Eagle::Matrix& Eagle::Matrix::operator%=(const double& value) {
	for (unsigned int i = 0; i < m_length; i++) m_values[i] = Mod(m_values[i], value);
	return *this;
}

Eagle::Matrix Eagle::Matrix::operator+(const Matrix& matrix) const {
	Matrix matrixCopy(*this);
	if (matrix.m_width != m_width || matrix.m_height != m_height) return matrixCopy;

	for (unsigned int i = 0; i < m_length; i++) matrixCopy.m_values[i] += matrix.m_values[i];
	return matrixCopy;
}

Eagle::Matrix Eagle::Matrix::operator-(const Matrix& matrix) const {
	Matrix matrixCopy(*this);
	if (matrix.m_width != m_width || matrix.m_height != m_height) return matrixCopy;

	for (unsigned int i = 0; i < m_length; i++) matrixCopy.m_values[i] -= matrix.m_values[i];
	return matrixCopy;
}

//	[!]	MUST BE OPTIMIZED IN NEWER VERSIONS
Eagle::Matrix Eagle::Matrix::operator*(const Matrix& matrix) const {
	Matrix matrixCopy(m_height, matrix.m_width);
	if (m_height != matrix.m_width || m_width != matrix.m_height) return matrixCopy;

	for (unsigned int i = 0; i < m_height; ++i) {
		for (unsigned int j = 0; j < matrix.m_width; ++j) {
			matrixCopy(i, j) = 0;
			for (unsigned int k = 0; k < m_width; ++k) matrixCopy(i, j) += (*this)(i, k) * matrix(k, j);
		}
	}

	return matrixCopy;
}

Eagle::Matrix& Eagle::Matrix::operator+=(const Matrix& matrix) {
	if (matrix.m_width != m_width || matrix.m_height != m_height) return *this;
	for (unsigned int i = 0; i < m_length; i++) m_values[i] += matrix.m_values[i];
	return *this;
}

Eagle::Matrix& Eagle::Matrix::operator-=(const Matrix& matrix) {
	if (matrix.m_width != m_width || matrix.m_height != m_height) return *this;
	for (unsigned int i = 0; i < m_length; i++) m_values[i] -= matrix.m_values[i];
	return *this;
}

Eagle::Matrix& Eagle::Matrix::operator*=(const Matrix& matrix) {
	Matrix matrixCopy(m_height, matrix.m_width);
	if (m_height != matrix.m_width || m_width != matrix.m_height) return *this;

	for (unsigned int i = 0; i < m_height; ++i) {
		for (unsigned int j = 0; j < matrix.m_width; ++j) {
			matrixCopy(i, j) = 0;
			for (unsigned int k = 0; k < m_width; ++k) matrixCopy(i, j) += (*this)(i, k) * matrix(k, j);
		}
	}

	Copy(matrixCopy);
	return *this;
}

Eagle::Matrix& Eagle::Matrix::operator=(const Matrix& matrix) {
	Copy(matrix);
	return *this;
}