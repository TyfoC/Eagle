#include "EagleEngine.h"

Eagle::Engine::Engine() : Canvas() { }
Eagle::Engine::Engine(Canvas& canvas) {
	m_colors = canvas.GetColors();
	m_width = canvas.GetWidth();
	m_height = canvas.GetHeight();
}

bool Eagle::Engine::DrawObject(const Object2D& object, const Color& color) {
	Point* points = object.ProducePoints();
	bool result = DrawPolygon(color, points, object.GetVectorsCount());
	delete[] points;
	return result;
}