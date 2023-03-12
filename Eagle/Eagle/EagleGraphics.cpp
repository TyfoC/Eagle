#include "EagleGraphics.h"

Eagle::Graphics::Color::Color() {
	m_value = 0;
}

Eagle::Graphics::Color::Color(unsigned char red, unsigned char green, unsigned char blue) {
	m_value = (unsigned int)(0xff000000 | (red << 16) | (green << 8) | blue);
}

Eagle::Graphics::Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
	m_value = (unsigned int)((alpha << 24) | (red << 16) | (green << 8) | blue);
}

Eagle::Graphics::Color::Color(unsigned char red, unsigned char green, unsigned char blue, float alpha) {
	unsigned char alphaByte = (unsigned char)((unsigned int)(alpha * 255) & 0xff);
	m_value = (unsigned int)((alphaByte << 24) | (red << 16) | (green << 8) | blue);
}

Eagle::Graphics::Color& Eagle::Graphics::Color::Blend(const Color& color) {
	unsigned int alpha = color.GetAlpha() + 1;
	unsigned int invertedAlpha = 256 - alpha;
	unsigned char red = (unsigned char)((alpha * color.GetRed() + invertedAlpha * GetRed()) >> 8);
	unsigned char green = (unsigned char)((alpha * color.GetGreen() + invertedAlpha * GetGreen()) >> 8);
	unsigned char blue = (unsigned char)((alpha * color.GetBlue() + invertedAlpha * GetBlue()) >> 8);
	m_value = (unsigned int)(0xff000000 | (red << 16) | (green << 8) | blue);
	return *this;
}

void Eagle::Graphics::Color::SetRed(unsigned char red) {
	m_value &= 0xff00ffff;
	m_value |= (unsigned int)(red << 16);
}

void Eagle::Graphics::Color::SetGreen(unsigned char green) {
	m_value &= 0xffff00ff;
	m_value |= (unsigned int)(green << 8);
}

void Eagle::Graphics::Color::SetBlue(unsigned char blue) {
	m_value &= 0xffffff00;
	m_value |= (unsigned int)blue;
}

void Eagle::Graphics::Color::SetAlpha(unsigned char alpha) {
	m_value &= 0x00ffffff;
	m_value |= (unsigned int)(alpha << 24);
}

unsigned char Eagle::Graphics::Color::GetRed() const {
	return (unsigned char)((m_value & 0x00ff0000) >> 16);
}

unsigned char Eagle::Graphics::Color::GetGreen() const {
	return (unsigned char)((m_value & 0x0000ff00) >> 8);
}

unsigned char Eagle::Graphics::Color::GetBlue() const {
	return (unsigned char)(m_value & 0x000000ff);
}

unsigned char Eagle::Graphics::Color::GetAlpha() const {
	return (unsigned char)((m_value & 0xff000000) >> 24);
}

Eagle::Graphics::Color& Eagle::Graphics::Color::operator()() {
	m_value = 0;
	return *this;
}

Eagle::Graphics::Color& Eagle::Graphics::Color::operator()(unsigned char red, unsigned char green, unsigned char blue) {
	m_value = (unsigned int)((red << 16) | (green << 8) | blue);
	return *this;
}

Eagle::Graphics::Color& Eagle::Graphics::Color::operator()(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
	m_value = (unsigned int)((alpha << 24) | (red << 16) | (green << 8) | blue);
	return *this;
}

Eagle::Graphics::Color& Eagle::Graphics::Color::operator()(unsigned char red, unsigned char green, unsigned char blue, float alpha) {
	unsigned char alphaByte = (unsigned char)((unsigned int)(alpha * 255) & 0xff);
	m_value = (unsigned int)((alphaByte << 24) | (red << 16) | (green << 8) | blue);
	return *this;
}

Eagle::Graphics::Color::operator unsigned int() const {
	return m_value;
}

Eagle::Graphics::Canvas::Canvas() {
	m_colors = 0;
	m_width = m_height = 0;
}

Eagle::Graphics::Canvas::Canvas(unsigned int width, unsigned int height) {
	unsigned int length = width * height;
	m_colors = new Color[length];
	if (m_colors) m_width = width, m_height = height;
	else m_width = m_height = 0;
}

Eagle::Graphics::Canvas::Canvas(const Canvas& canvas) {
	unsigned int length = canvas.m_width * canvas.m_height;
	m_colors = new Color[length];
	if (m_colors) {
		m_width = canvas.m_width, m_height = canvas.m_height;
		for (unsigned int i = 0; i < length; i++) m_colors[i] = canvas.m_colors[i];
	}
	else m_width = m_height = 0;
}

Eagle::Graphics::Canvas::~Canvas() {
	if (m_colors) {
		delete[] m_colors;
		m_width = m_height = 0;
	}
}

bool Eagle::Graphics::Canvas::Truncate(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	unsigned int truncatedLength = width * height;
	Color* truncatedColors = new Color[truncatedLength];
	if (!truncatedColors) return false;

	unsigned int destinationOffset = 0, sourceLineOffset = y * m_width, offsetX;
	while (destinationOffset < truncatedLength) {
		for (offsetX = 0; offsetX < width && destinationOffset < truncatedLength; offsetX++, destinationOffset++) truncatedColors[destinationOffset] = m_colors[sourceLineOffset + offsetX];
		sourceLineOffset += m_width;
	}

	delete[] m_colors;
	m_colors = truncatedColors;
	m_width = width, m_height = height;
	return true;
}

bool Eagle::Graphics::Canvas::DrawPointI(const Color& color, const IPoint2D point) {
	if (!m_colors) return false;
	m_colors[point.X + point.Y * m_width] = color;
	return true;
}

bool Eagle::Graphics::Canvas::DrawPointF(const Color& color, const FPoint2D point) {
	if (!m_colors) return false;
	int x = (int)Math::Double2Int(point.X), y = (int)Math::Double2Int(point.Y);
	m_colors[x + y * m_width] = color;
	return true;
}

bool Eagle::Graphics::Canvas::DrawRectangleI(const Color& color, const IPoint2D point1, const IPoint2D point2) {
	if (!m_colors) return false;
	int x1 = point1.X, y1 = point1.Y, x2 = point2.X, y2 = point2.Y;
	if (x1 > x2) Math::Swap(x1, x2);
	if (y1 > y2) Math::Swap(y1, y2);
	for (int y = y1; y < y2; y++) for (int x = x1; x < x2; x++) DrawPointI(color, { x, y });
	return true;
}

bool Eagle::Graphics::Canvas::DrawRectangleF(const Color& color, const FPoint2D point1, const FPoint2D point2) {
	if (!m_colors) return false;
	int x1 = (int)Math::Double2Int(point1.X), y1 = (int)Math::Double2Int(point1.Y), x2 = (int)Math::Double2Int(point2.X), y2 = (int)Math::Double2Int(point2.Y);
	if (x1 > x2) Math::Swap(x1, x2);
	if (y1 > y2) Math::Swap(y1, y2);
	for (int y = y1; y < y2; y++) for (int x = x1; x < x2; x++) DrawPointI(color, { x, y });
	return true;
}

bool Eagle::Graphics::Canvas::DrawLineI(const Color& color, const IPoint2D point1, const IPoint2D point2) {
	if (!m_colors) return false;

	int x1 = point1.X, y1 = point1.Y, x2 = point2.X, y2 = point2.Y;
	const int distanceX = Math::Absolute(x2 - x1), distanceY = Math::Absolute(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1, signY = y1 < y2 ? 1 : -1;

	DrawPointI(color, { x2, y2 });

	int differenceXY = distanceX - distanceY, tmp;
	while (x1 != x2 || y1 != y2) {
		DrawPointI(color, { x1, y1 });

		tmp = differenceXY << 1;
		if (tmp > -distanceY) {
			differenceXY -= distanceY;
			x1 += signX;
		}
		if (tmp < distanceX) {
			differenceXY += distanceX;
			y1 += signY;
		}
	}

	return true;
}

bool Eagle::Graphics::Canvas::DrawLineF(const Color& color, const FPoint2D point1, const FPoint2D point2) {
	if (!m_colors) return false;

	int x1 = (int)Math::Double2Int(point1.X), y1 = (int)Math::Double2Int(point1.Y), x2 = (int)Math::Double2Int(point2.X), y2 = (int)Math::Double2Int(point2.Y);
	const int distanceX = Math::Absolute(x2 - x1), distanceY = Math::Absolute(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1, signY = y1 < y2 ? 1 : -1;

	DrawPointI(color, { x2, y2 });

	int differenceXY = distanceX - distanceY, tmp;
	while (x1 != x2 || y1 != y2) {
		DrawPointI(color, { x1, y1 });

		tmp = differenceXY << 1;
		if (tmp > -distanceY) {
			differenceXY -= distanceY;
			x1 += signX;
		}
		if (tmp < distanceX) {
			differenceXY += distanceX;
			y1 += signY;
		}
	}

	return true;
}

bool Eagle::Graphics::Canvas::DrawCircleI(const Color& color, const IPoint2D center, int radius) {
	if (!m_colors) return false;

	int x = center.X, y = center.Y, offsetX = 0, offsetY = radius, f = 1 - radius;

	DrawLineI(color, { x, y }, { x + radius, y });
	DrawLineI(color, { x, y }, { x - radius, y });
	DrawLineI(color, { x, y }, { x, y + radius });
	DrawLineI(color, { x, y }, { x, y - radius });

	while (offsetX < offsetY) {
		offsetX += 1;
		if (f < 0) f += 2 * offsetX + 1;
		else {
			f += 2 * (offsetX - offsetY + 1);
			offsetY -= 1;
		}

		DrawLineI(color, { x + offsetX, y + offsetX }, { x + offsetX, y + offsetY });
		DrawLineI(color, { x - offsetX, y + offsetX }, { x - offsetX, y + offsetY });
		DrawLineI(color, { x + offsetX, y - offsetX }, { x + offsetX, y - offsetY });
		DrawLineI(color, { x - offsetX, y - offsetX }, { x - offsetX, y - offsetY });
		DrawLineI(color, { x + offsetX, y + offsetX }, { x + offsetY, y + offsetX });
		DrawLineI(color, { x + offsetX, y + offsetX }, { x - offsetY, y + offsetX });
		DrawLineI(color, { x + offsetX, y - offsetX }, { x + offsetY, y - offsetX });
		DrawLineI(color, { x + offsetX, y - offsetX }, { x - offsetY, y - offsetX });
	}

	return true;
}

bool Eagle::Graphics::Canvas::DrawCircleF(const Color& color, const FPoint2D center, float radius) {
	if (!m_colors) return false;

	int x = (int)Math::Double2Int(center.X), y = (int)Math::Double2Int(center.Y), offsetX = 0, offsetY = (int)Math::Double2Int(radius), f = (int)Math::Double2Int(1.0f - radius);

	DrawLineI(color, { x, y }, { x + offsetY, y });
	DrawLineI(color, { x, y }, { x - offsetY, y });
	DrawLineI(color, { x, y }, { x, y + offsetY });
	DrawLineI(color, { x, y }, { x, y - offsetY });

	while (offsetX < offsetY) {
		offsetX += 1;
		if (f < 0) f += 2 * offsetX + 1;
		else {
			f += 2 * (offsetX - offsetY + 1);
			offsetY -= 1;
		}

		DrawLineI(color, { x + offsetX, y + offsetX }, { x + offsetX, y + offsetY });
		DrawLineI(color, { x - offsetX, y + offsetX }, { x - offsetX, y + offsetY });
		DrawLineI(color, { x + offsetX, y - offsetX }, { x + offsetX, y - offsetY });
		DrawLineI(color, { x - offsetX, y - offsetX }, { x - offsetX, y - offsetY });
		DrawLineI(color, { x + offsetX, y + offsetX }, { x + offsetY, y + offsetX });
		DrawLineI(color, { x + offsetX, y + offsetX }, { x - offsetY, y + offsetX });
		DrawLineI(color, { x + offsetX, y - offsetX }, { x + offsetY, y - offsetX });
		DrawLineI(color, { x + offsetX, y - offsetX }, { x - offsetY, y - offsetX });
	}

	return true;
}

bool Eagle::Graphics::Canvas::DrawPolygonI(const Color& color, const IPoint2D* vertices, unsigned int count) {
	if (!m_colors) return false;
	else if (count < 3) return count == 2 ? DrawLineI(color, vertices[0], vertices[1]) : false;

	int minX = vertices[0].X, minY = vertices[0].Y;
	int maxX = minX, maxY = minY, tmpX, tmpY;
	for (size_t i = 1; i < count; i++) {
		tmpX = vertices[i].X;
		tmpY = vertices[i].Y;
		if (tmpX < minX) minX = tmpX;
		if (tmpX > maxX) maxX = tmpX;

		if (tmpY < minY) minY = tmpY;
		if (tmpY > maxY) maxY = tmpY;
	}

	int currentX = minX;
	for (; minY <= maxY;) {
		if (IsPointInPolygonI({ currentX, minY }, vertices, count)) DrawPointI(color, { currentX, minY });

		if (currentX <= maxX) ++currentX;
		else {
			currentX = 0;
			++minY;
		}
	}

	return true;
}

bool Eagle::Graphics::Canvas::DrawPolygonF(const Color& color, const FPoint2D* vertices, unsigned int count) {
	if (!m_colors) return false;
	else if (count < 3) return count == 2 ? DrawLineF(color, vertices[0], vertices[1]) : false;

	int minX = (int)Math::Double2Int(vertices[0].X), minY = (int)Math::Double2Int(vertices[0].Y);
	int maxX = minX, maxY = minY, tmpX, tmpY;
	for (size_t i = 1; i < count; i++) {
		tmpX = (int)Math::Double2Int(vertices[i].X), tmpY = (int)Math::Double2Int(vertices[i].Y);

		if (tmpX < minX) minX = tmpX;
		if (tmpX > maxX) maxX = tmpX;

		if (tmpY < minY) minY = tmpY;
		if (tmpY > maxY) maxY = tmpY;
	}

	int currentX = minX;
	for (; minY <= maxY;) {
		if (IsPointInPolygonF({ (float)currentX, (float)minY }, vertices, count)) DrawPointI(color, { currentX, minY });

		if (currentX <= maxX) ++currentX;
		else {
			currentX = 0;
			++minY;
		}
	}

	return true;
}

bool Eagle::Graphics::Canvas::IsPointInPolygonI(const IPoint2D point, const IPoint2D* vertices, unsigned int count) {
	int x = point.X, y = point.Y, slope, firstX, firstY, lastX, lastY;

	bool pointInPolygon = false;
	unsigned int j = count - 1;
	for (unsigned int i = 0; i < count; i++) {
		firstX = vertices[i].X, firstY = vertices[i].Y;
		lastX = vertices[j].X, lastY = vertices[j].Y;

		if (x == firstX && y == firstY) return true;
		else if ((firstY > y) != (lastY > y)) {
			slope = (x - firstX) * (lastY - firstY) - (lastX - firstX) * (y - firstY);

			if (!slope) return true;
			else if ((slope < 0) != (lastY < firstY)) pointInPolygon = !pointInPolygon;
		}
		j = i;
	}

	return pointInPolygon;
}

bool Eagle::Graphics::Canvas::IsPointInPolygonF(const FPoint2D point, const FPoint2D* vertices, unsigned int count) {
	int x = (int)Math::Double2Int(point.X), y = (int)Math::Double2Int(point.Y), slope, firstX, firstY, lastX, lastY;

	bool pointInPolygon = false;
	unsigned int j = count - 1;
	for (unsigned int i = 0; i < count; i++) {
		firstX = (int)Math::Double2Int(vertices[i].X), firstY = (int)Math::Double2Int(vertices[i].Y);
		lastX = (int)Math::Double2Int(vertices[j].X), lastY = (int)Math::Double2Int(vertices[j].Y);

		if (x == firstX && y == firstY) return true;
		else if ((firstY > y) != (lastY > y)) {
			slope = (x - firstX) * (lastY - firstY) - (lastX - firstX) * (y - firstY);

			if (!slope) return true;
			else if ((slope < 0) != (lastY < firstY)) pointInPolygon = !pointInPolygon;
		}
		j = i;
	}

	return pointInPolygon;
}

const Eagle::Graphics::Color* Eagle::Graphics::Canvas::GetColorsArray() const {
	return m_colors;
}

unsigned int Eagle::Graphics::Canvas::GetWidth() const {
	return m_width;
}

unsigned int Eagle::Graphics::Canvas::GetHeight() const {
	return m_height;
}

bool Eagle::Graphics::Canvas::Update(float alpha) {
	if (!m_colors) return false;
	// Content is different for each OS
	return true;
}

bool Eagle::Graphics::Canvas::Render(float alpha) {
	if (!m_colors) return false;
	// Content is different for each OS
	return true;
}

bool Eagle::Graphics::Canvas::IsWindowSizeChanged() const {
	// Content is different for each OS
	return false;
}

const Eagle::Graphics::Color& Eagle::Graphics::Canvas::operator[](unsigned int index) const {
	return m_colors[index];
}