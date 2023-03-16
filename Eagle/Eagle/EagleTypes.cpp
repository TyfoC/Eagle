#include "EagleTypes.h"

Eagle::Point& Eagle::Point::operator+=(const double value) {
	X += value;
	Y += value;
	return *this;
}

Eagle::Point& Eagle::Point::operator-=(const double value) {
	X -= value;
	Y -= value;
	return *this;
}

Eagle::Point& Eagle::Point::operator*=(const double value) {
	X *= value;
	Y *= value;
	return *this;
}

Eagle::Point& Eagle::Point::operator/=(const double value) {
	X /= value;
	Y /= value;
	return *this;
}

Eagle::Point& Eagle::Point::operator%=(const double value) {
	X = Mod(X, value);
	Y = Mod(Y, value);
	return *this;
}

Eagle::Point& Eagle::Point::operator+=(const Point point) {
	X += point.X;
	Y += point.Y;
	return *this;
}

Eagle::Point& Eagle::Point::operator-=(const Point point) {
	X -= point.X;
	Y -= point.Y;
	return *this;
}

Eagle::Point& Eagle::Point::operator*=(const Point point) {
	X *= point.X;
	Y *= point.Y;
	return *this;
}

Eagle::Point& Eagle::Point::operator/=(const Point point) {
	X /= point.X;
	Y /= point.Y;
	return *this;
}

Eagle::Point& Eagle::Point::operator%=(const Point point) {
	X = Mod(X, point.X);
	Y = Mod(Y, point.Y);
	return *this;
}

Eagle::Point Eagle::Point::operator+(const double value) const {
	return { X + value, Y + value };
}

Eagle::Point Eagle::Point::operator-(const double value) const {
	return { X - value, Y - value };
}

Eagle::Point Eagle::Point::operator*(const double value) const {
	return { X * value, Y * value };
}

Eagle::Point Eagle::Point::operator/(const double value) const {
	return { X / value, Y / value };
}

Eagle::Point Eagle::Point::operator%(const double value) const {
	return { Mod(X, value), Mod(Y, value) };
}

Eagle::Point Eagle::Point::operator+(const Point point) const {
	return { X + point.X, Y + point.Y };
}

Eagle::Point Eagle::Point::operator-(const Point point) const {
	return { X - point.X, Y - point.Y };
}

Eagle::Point Eagle::Point::operator*(const Point point) const {
	return { X * point.X, Y * point.Y };
}

Eagle::Point Eagle::Point::operator/(const Point point) const {
	return { X / point.X, Y / point.Y };
}

Eagle::Point Eagle::Point::operator%(const Point point) const {
	return { Mod(X, point.X), Mod(Y, point.Y) };
}

Eagle::Matrix::Matrix() {
	m_values = 0;
	m_width = m_height = m_length = 0;
}

Eagle::Matrix::Matrix(unsigned int width, unsigned int height) {
	unsigned int length = width * height;
	m_values = new double[length];
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

Eagle::Matrix Eagle::Matrix::GetIdentityMatrix(unsigned int width) {
	Matrix matrix(width, width);
	if (!matrix.m_values) return matrix;

	const unsigned int length = width * width;
	for (unsigned int i = 0; i < length; i++) matrix[i] = 0;
	for (unsigned int i = 0; i < width; i++) matrix(i, i) = 1;

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
	if (m_width != matrix.m_height) return matrixCopy;

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
	if (m_width != matrix.m_height) return *this;

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

Eagle::Vector2D Eagle::Vector2D::operator*(const Matrix& matrix) const {
	unsigned int matrixWidth = matrix.GetWidth(), matrixHeight = matrix.GetHeight();
	if (3 != matrixWidth) return *this;

	const double values[] = { X, Y, W };
	Matrix vector(3, 1, values);
	vector *= matrix;

	Vector2D vec = Vector2D();
	return { vector[0], vector[1], vector[2] };
}

Eagle::Vector2D::Vector2D() {
	X = Y = 0;
	W = 1.0;
}

Eagle::Vector2D::Vector2D(double x, double y, double w) {
	X = x;
	Y = y;
	W = w;
}

Eagle::Vector2D& Eagle::Vector2D::operator+=(const double value) {
	X += value;
	Y += value;
	return *this;
}

Eagle::Vector2D& Eagle::Vector2D::operator-=(const double value) {
	X -= value;
	Y -= value;
	return *this;
}

Eagle::Vector2D& Eagle::Vector2D::operator*=(const double value) {
	X *= value;
	Y *= value;
	return *this;
}

Eagle::Vector2D& Eagle::Vector2D::operator/=(const double value) {
	X /= value;
	Y /= value;
	return *this;
}

Eagle::Vector2D& Eagle::Vector2D::operator%=(const double value) {
	X = Mod(X, value);
	Y = Mod(Y, value);
	return *this;
}

Eagle::Vector2D& Eagle::Vector2D::operator+=(const Vector2D vector) {
	X += vector.X;
	Y += vector.Y;
	return *this;
}

Eagle::Vector2D& Eagle::Vector2D::operator-=(const Vector2D vector) {
	X -= vector.X;
	Y -= vector.Y;
	return *this;
}

Eagle::Vector2D& Eagle::Vector2D::operator*=(const Vector2D vector) {
	X *= vector.X;
	Y *= vector.Y;
	return *this;
}

Eagle::Vector2D& Eagle::Vector2D::operator/=(const Vector2D vector) {
	X /= vector.X;
	Y /= vector.Y;
	return *this;
}

Eagle::Vector2D& Eagle::Vector2D::operator%=(const Vector2D vector) {
	X = Mod(X, vector.X);
	Y = Mod(Y, vector.Y);
	return *this;
}

Eagle::Vector2D& Eagle::Vector2D::operator*=(const Matrix& matrix) {
	unsigned int matrixWidth = matrix.GetWidth(), matrixHeight = matrix.GetHeight();
	if (3 != matrixWidth) return *this;

	const double values[] = { X, Y, W };
	Matrix vectorMatrix(3, 1, values);
	vectorMatrix *= matrix;

	X = vectorMatrix[0], Y = vectorMatrix[1], W = vectorMatrix[2];
	return *this;
}

Eagle::Vector2D Eagle::Vector2D::operator+(const double value) const {
	return { X + value, Y + value, W };
}

Eagle::Vector2D Eagle::Vector2D::operator-(const double value) const {
	return { X - value, Y - value, W };
}

Eagle::Vector2D Eagle::Vector2D::operator*(const double value) const {
	return { X * value, Y * value, W };
}

Eagle::Vector2D Eagle::Vector2D::operator/(const double value) const {
	return { X / value, Y / value, W };
}

Eagle::Vector2D Eagle::Vector2D::operator%(const double value) const {
	return { Mod(X, value), Mod(Y, value), W };
}

Eagle::Vector2D Eagle::Vector2D::operator+(const Vector2D vector) const {
	return { X + vector.X, Y + vector.Y, W };
}

Eagle::Vector2D Eagle::Vector2D::operator-(const Vector2D vector) const {
	return { X - vector.X, Y - vector.Y, W };
}

Eagle::Vector2D Eagle::Vector2D::operator*(const Vector2D vector) const {
	return { X * vector.X, Y * vector.Y, W };
}

Eagle::Vector2D Eagle::Vector2D::operator/(const Vector2D vector) const {
	return { X / vector.X, Y / vector.Y, W };
}

Eagle::Vector2D Eagle::Vector2D::operator%(const Vector2D vector) const {
	return { Mod(X, vector.X), Mod(Y, vector.Y), W };
}

Eagle::Object2D::Object2D() {
	m_count = 0;
	m_vertices = 0;
	m_position = m_scale = {};
	m_rotation = 0;
}

Eagle::Object2D::Object2D(const Object2D& object) {
	m_vertices = new Vector2D[object.m_count];
	if (!m_vertices) {
		m_count = 0;
		m_vertices = 0;
		m_position = m_scale = {};
		m_rotation = 0;
		return;
	}

	m_count = object.m_count;
	m_position = object.m_position;
	m_scale = object.m_scale;
	m_rotation = object.m_rotation;

	for (unsigned int i = 0; i < m_count; i++) m_vertices[i] = object.m_vertices[i];
}

Eagle::Object2D::Object2D(const Vector2D* vertices, unsigned int count, const Vector2D position, const Vector2D scale, double rotation) {
	m_vertices = new Vector2D[count];
	if (!m_vertices) {
		m_count = 0;
		m_vertices = 0;
		m_position = m_scale = {};
		m_rotation = 0;
		return;
	}

	m_count = count;
	m_position = position;
	m_scale = scale;
	m_rotation = rotation;

	for (unsigned int i = 0; i < count; i++) m_vertices[i] = vertices[i];
}

Eagle::Object2D::Object2D(const Point* points, unsigned int count, const Vector2D position, const Vector2D scale, double rotation) {
	m_vertices = new Vector2D[count];
	if (!m_vertices) {
		m_count = 0;
		m_vertices = 0;
		m_position = m_scale = {};
		m_rotation = 0;
		return;
	}

	m_count = count;
	m_position = position;
	m_scale = scale;
	m_rotation = rotation;

	for (unsigned int i = 0; i < count; i++) {
		m_vertices[i].X = points[i].X;
		m_vertices[i].Y = points[i].Y;
		m_vertices[i].W = 1.0;
	}
}

Eagle::Object2D::~Object2D() {
	if (m_vertices) delete[] m_vertices;
	m_count = 0;
	m_position = m_scale = {};
	m_rotation = 0;
}

Eagle::Object2D Eagle::Object2D::ProduceTranslated() const {
	Object2D translated(*this);
	for (unsigned int i = 0; i < translated.m_count; i++) translated[i] += translated.m_position;
	return translated;
}

Eagle::Object2D Eagle::Object2D::ProduceScaled() const {
	Object2D scaled(*this);
	for (unsigned int i = 0; i < scaled.m_count; i++) scaled.m_vertices[i] *= scaled.m_scale;
	return scaled;
}

Eagle::Object2D Eagle::Object2D::ProduceRotated() const {
	Object2D rotated(*this);
	const double sineAngle = Sine(m_rotation), cosineAngle = Cosine(m_rotation);
	for (unsigned int i = 0; i < rotated.m_count; i++) {
		rotated.m_vertices[i].X = m_vertices[i].X * cosineAngle - m_vertices[i].Y * sineAngle;
		rotated.m_vertices[i].Y = m_vertices[i].X * sineAngle + m_vertices[i].Y * cosineAngle;
	}
	return rotated;
}

Eagle::Object2D Eagle::Object2D::ProduceTransformed() const {
	return ProduceScaled().ProduceRotated().ProduceTranslated();
}

void Eagle::Object2D::SetPosition(const Vector2D position) {
	m_position = position;
}

void Eagle::Object2D::SetScale(const Vector2D scale) {
	m_scale = scale;
}

void Eagle::Object2D::SetRotation(double rotation) {
	m_rotation = rotation;
}

Eagle::Vector2D Eagle::Object2D::GetPosition() const {
	return m_position;
}

Eagle::Vector2D Eagle::Object2D::GetScale() const {
	return m_scale;
}

double Eagle::Object2D::GetRotation() const {
	return m_rotation;
}

Eagle::Vector2D Eagle::Object2D::GetCenter() const {
	Vector2D center = { 0.0, 0.0 };
	for (unsigned int i = 0; i < m_count; i++) center += m_vertices[i];
	center.X /= m_count;
	center.Y /= m_count;
	return center;
}

Eagle::Vector2D* Eagle::Object2D::GetVectors() {
	return m_vertices;
}

const Eagle::Vector2D* Eagle::Object2D::GetVectors() const {
	return m_vertices;
}

Eagle::Point* Eagle::Object2D::ProducePoints() const {
	Point* points = new Point[m_count];
	if (!points) return 0;

	for (unsigned int i = 0; i < m_count; i++) {
		points[i].X = m_vertices[i].X;
		points[i].Y = m_vertices[i].Y;
	}

	return points;
}

unsigned int Eagle::Object2D::GetVectorsCount() const {
	return m_count;
}

Eagle::Object2D& Eagle::Object2D::operator=(const Object2D& object) {
	m_vertices = new Vector2D[object.m_count];
	if (!m_vertices) {
		m_count = 0;
		m_vertices = 0;
		m_position = m_scale = {};
		m_rotation = 0;
		return *this;
	}

	m_count = object.m_count;
	m_position = object.m_position;
	m_scale = object.m_scale;
	m_rotation = object.m_rotation;

	for (unsigned int i = 0; i < m_count; i++) m_vertices[i] = object.m_vertices[i];
	return *this;
}

Eagle::Vector2D& Eagle::Object2D::operator[](unsigned int index) {
	return m_vertices[index];
}

const Eagle::Vector2D& Eagle::Object2D::operator[](unsigned int index) const {
	return m_vertices[index];
}