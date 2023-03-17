#include "EagleGraphics.h"

Eagle::Color::Color() {
	m_value = 0;
}

Eagle::Color::Color(unsigned char red, unsigned char green, unsigned char blue) {
	m_value = (unsigned int)(0xff000000 | (red << 16) | (green << 8) | blue);
}

Eagle::Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
	m_value = (unsigned int)((alpha << 24) | (red << 16) | (green << 8) | blue);
}

Eagle::Color::Color(unsigned char red, unsigned char green, unsigned char blue, double alpha) {
	unsigned char alphaByte = (unsigned char)((unsigned int)(alpha * 255) & 0xff);
	m_value = (unsigned int)((alphaByte << 24) | (red << 16) | (green << 8) | blue);
}

Eagle::Color& Eagle::Color::Blend(const Color& color) {
	unsigned int alpha = color.GetAlpha() + 1;
	unsigned int invertedAlpha = 256 - alpha;
	unsigned char red = (unsigned char)((alpha * color.GetRed() + invertedAlpha * GetRed()) >> 8);
	unsigned char green = (unsigned char)((alpha * color.GetGreen() + invertedAlpha * GetGreen()) >> 8);
	unsigned char blue = (unsigned char)((alpha * color.GetBlue() + invertedAlpha * GetBlue()) >> 8);
	m_value = (unsigned int)(0xff000000 | (red << 16) | (green << 8) | blue);
	return *this;
}

void Eagle::Color::SetRed(unsigned char red) {
	m_value &= 0xff00ffff;
	m_value |= (unsigned int)(red << 16);
}

void Eagle::Color::SetGreen(unsigned char green) {
	m_value &= 0xffff00ff;
	m_value |= (unsigned int)(green << 8);
}

void Eagle::Color::SetBlue(unsigned char blue) {
	m_value &= 0xffffff00;
	m_value |= (unsigned int)blue;
}

void Eagle::Color::SetAlpha(unsigned char alpha) {
	m_value &= 0x00ffffff;
	m_value |= (unsigned int)(alpha << 24);
}

unsigned char Eagle::Color::GetRed() const {
	return (unsigned char)((m_value & 0x00ff0000) >> 16);
}

unsigned char Eagle::Color::GetGreen() const {
	return (unsigned char)((m_value & 0x0000ff00) >> 8);
}

unsigned char Eagle::Color::GetBlue() const {
	return (unsigned char)(m_value & 0x000000ff);
}

unsigned char Eagle::Color::GetAlpha() const {
	return (unsigned char)((m_value & 0xff000000) >> 24);
}

Eagle::Color& Eagle::Color::operator()() {
	m_value = 0;
	return *this;
}

Eagle::Color& Eagle::Color::operator()(unsigned char red, unsigned char green, unsigned char blue) {
	m_value = (unsigned int)((red << 16) | (green << 8) | blue);
	return *this;
}

Eagle::Color& Eagle::Color::operator()(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
	m_value = (unsigned int)((alpha << 24) | (red << 16) | (green << 8) | blue);
	return *this;
}

Eagle::Color& Eagle::Color::operator()(unsigned char red, unsigned char green, unsigned char blue, double alpha) {
	unsigned char alphaByte = (unsigned char)((unsigned int)(alpha * 255) & 0xff);
	m_value = (unsigned int)((alphaByte << 24) | (red << 16) | (green << 8) | blue);
	return *this;
}

Eagle::Color::operator unsigned int() const {
	return m_value;
}

Eagle::Canvas::Canvas() {
	m_colors = 0;
	m_width = m_height = 0;
}

Eagle::Canvas::Canvas(unsigned int width, unsigned int height) {
	unsigned int length = width * height;
	m_colors = new Color[length];
	if (m_colors) m_width = width, m_height = height;
	else m_width = m_height = 0;
}

Eagle::Canvas::Canvas(const Canvas& canvas) {
	unsigned int length = canvas.m_width * canvas.m_height;
	m_colors = new Color[length];
	if (m_colors) {
		m_width = canvas.m_width, m_height = canvas.m_height;
		for (unsigned int i = 0; i < length; i++) m_colors[i] = canvas.m_colors[i];
	}
	else m_width = m_height = 0;
}

Eagle::Canvas::~Canvas() {
	if (m_colors) {
		delete[] m_colors;
		m_width = m_height = 0;
	}
}

void Eagle::Canvas::Redraw(const Color color) {
	unsigned int length = m_width * m_height;
	for (unsigned int i = 0; i < length; i++) m_colors[i] = color;
}

bool Eagle::Canvas::Copy(const Canvas& canvas, unsigned int sourceX, unsigned int sourceY, unsigned int destinationX, unsigned int destinationY, unsigned int width, unsigned int height) {
	if (!m_colors) return false;
	if (sourceX >= m_width || sourceY >= m_height) return false;
	if (m_width < sourceX + width) width = m_width - sourceX + 1;
	if (m_height < sourceY + height) height = m_height - sourceY + 1;

	unsigned int sourceOffset = sourceX + sourceY * width, destinationOffset = destinationX + destinationY * m_width;
	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) m_colors[destinationOffset + x] = canvas.m_colors[sourceOffset + x];
		destinationOffset += m_width;
		sourceOffset += canvas.m_width;
	}
	return true;
}

bool Eagle::Canvas::Truncate(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
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

bool Eagle::Canvas::DrawPoint(const Color& color, const Point point) {
	int x = (int)Double2Int(point.X), y = (int)Double2Int(point.Y);
	if (!m_colors || (unsigned int)x >= m_width || (unsigned int)y >= m_height) return false;
	m_colors[x + y * m_width] = m_colors[x + y * m_width].Blend(color);
	return true;
}

bool Eagle::Canvas::DrawRectangle(const Color& color, const Point point1, const Point point2) {
	if (!m_colors) return false;
	double x1 = point1.X, y1 = point1.Y, x2 = point2.X, y2 = point2.Y;
	if (x1 > x2) Swap(x1, x2);
	if (y1 > y2) Swap(y1, y2);
	for (double y = y1; y < y2; y++) for (double x = x1; x < x2; x++) DrawPoint(color, { x, y });
	return true;
}

bool Eagle::Canvas::DrawLine(const Color& color, const Point point1, const Point point2) {
	if (!m_colors) return false;

	long long x1 = Double2Int(point1.X), y1 = Double2Int(point1.Y), x2 = Double2Int(point2.X), y2 = Double2Int(point2.Y);
	const long long distanceX = Absolute(x2 - x1), distanceY = Absolute(y2 - y1);
	const long long signX = x1 < x2 ? 1 : -1, signY = y1 < y2 ? 1 : -1;

	DrawPoint(color, { (double)x2, (double)y2 });

	long long deltaXY = distanceX - distanceY, tmp;
	while (x1 != x2 || y1 != y2) {
		DrawPoint(color, { (double)x1, (double)y1 });

		tmp = deltaXY * 2;
		if (tmp > -distanceY) {
			deltaXY -= distanceY;
			x1 += signX;
		}
		if (tmp < distanceX) {
			deltaXY += distanceX;
			y1 += signY;
		}
	}

	return true;
}

//	Warning: it is not recommended to change the color alpha parameter (this function does not provide the ability to draw shaded areas nicely)
bool Eagle::Canvas::DrawCircle(const Color& color, const Point center, double radius) {
	if (!m_colors) return false;

	double x = center.X, y = center.Y, currentX = radius, currentY = 0, offsetError = 0;

	while (currentX >= currentY) {
		DrawLine(color, { x - currentX, y + currentY }, { x + currentX, y + currentY });
		DrawLine(color, { x - currentX, y - currentY }, { x + currentX, y - currentY });
		DrawLine(color, { x - currentY, y + currentX }, { x + currentY, y + currentX });
		DrawLine(color, { x - currentY, y - currentX }, { x + currentY, y - currentX });

		if (offsetError <= 0) {
			currentY += 1;
			offsetError += 2 * currentY + 1;
		}

		if (offsetError > 0) {
			currentX -= 1;
			offsetError -= 2 * currentX + 1;
		}
	}

	return true;
}

bool Eagle::Canvas::DrawPolygon(const Color& color, const Point* vertices, unsigned int count) {
	if (!m_colors) return false;
	else if (count < 3) return count == 2 ? DrawLine(color, vertices[0], vertices[1]) : false;

	double minX = vertices[0].X, minY = vertices[0].Y;
	double maxX = minX, maxY = minY, tmpX, tmpY;
	for (unsigned int i = 1; i < count; i++) {
		tmpX = vertices[i].X, tmpY = vertices[i].Y;

		if (tmpX < minX) minX = tmpX;
		if (tmpX > maxX) maxX = tmpX;

		if (tmpY < minY) minY = tmpY;
		if (tmpY > maxY) maxY = tmpY;
	}

	double currentX = minX;
	for (; minY <= maxY;) {
		if (IsPointInPolygon({ currentX, minY }, vertices, count)) DrawPoint(color, { currentX, minY });

		if (currentX <= maxX) ++currentX;
		else {
			currentX = 0;
			++minY;
		}
	}

	return true;
}

bool Eagle::Canvas::IsPointInPolygon(const Point point, const Point* vertices, unsigned int count) {
	double x = point.X, y = point.Y, slope, firstX, firstY, lastX, lastY;

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

Eagle::Color* Eagle::Canvas::GetColors() {
	return m_colors;
}

const Eagle::Color* Eagle::Canvas::GetColors() const {
	return m_colors;
}

unsigned int Eagle::Canvas::GetWidth() const {
	return m_width;
}

unsigned int Eagle::Canvas::GetHeight() const {
	return m_height;
}

Eagle::Color& Eagle::Canvas::operator[](unsigned int index) {
	return m_colors[index];
}

const Eagle::Color& Eagle::Canvas::operator[](unsigned int index) const {
	return m_colors[index];
}