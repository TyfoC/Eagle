#include "EagleWindowsRenderer.h"

Eagle::WindowsRenderer::WindowsRenderer() {
	m_destinationBuffer = 0;
	m_deviceContext = 0;
	m_dibSectionBitmap = 0;
	m_bitmapContext = 0;
	m_oldBitmapContext = 0;
}

Eagle::WindowsRenderer::WindowsRenderer(const HDC deviceContext) {
	RECT rect = {};
	GetWindowRect(WindowFromDC(deviceContext), &rect);

	m_destinationBuffer = 0;
	m_width = (unsigned int)(rect.right - rect.left);
	m_height = (unsigned int)(rect.bottom - rect.top);
	m_colors = new Color[(unsigned int)((unsigned long long)m_width * (unsigned long long)m_height)];
	if (!m_colors) {
		m_width = m_height = 0;
		m_deviceContext = 0;
		m_dibSectionBitmap = 0;
		m_bitmapContext = 0;
		m_oldBitmapContext = 0;
		return;
	}

	BITMAPINFO bmi = {};
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = (LONG)m_width;
	bmi.bmiHeader.biHeight = -(LONG)m_height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	m_deviceContext = deviceContext;
	m_dibSectionBitmap = CreateDIBSection(m_deviceContext, &bmi, DIB_RGB_COLORS, (void**)&m_destinationBuffer, 0, 0);
	m_bitmapContext = CreateCompatibleDC(m_deviceContext);
	m_oldBitmapContext = m_dibSectionBitmap ? SelectObject(m_bitmapContext, m_dibSectionBitmap) : 0;
}

Eagle::WindowsRenderer::~WindowsRenderer() {
	if (m_dibSectionBitmap) {
		SelectObject(m_bitmapContext, m_oldBitmapContext);
		DeleteDC(m_bitmapContext);
		DeleteObject(m_dibSectionBitmap);
	}
}

bool Eagle::WindowsRenderer::AreMetricsChanged() {
	RECT rect = {};
	GetWindowRect(WindowFromDC(m_deviceContext), &rect);
	unsigned int width = (unsigned int)(rect.right - rect.left), height = (unsigned int)(rect.bottom - rect.top);
	return m_width != width || m_height != height;
}

bool Eagle::WindowsRenderer::Update(float alpha) {
	if (!m_dibSectionBitmap) return false;

	BitBlt(m_bitmapContext, 0, 0, (int)m_width, (int)m_height, m_deviceContext, 0, 0, SRCCOPY);

	unsigned int length = m_width * m_height;
	for (unsigned int i = 0; i < length; i++) m_colors[i] = Color(m_destinationBuffer[i].rgbRed, m_destinationBuffer[i].rgbGreen, m_destinationBuffer[i].rgbBlue);

	return true;
}

bool Eagle::WindowsRenderer::Render(float alpha) {
	if (!m_dibSectionBitmap) return false;

	unsigned int length = m_width * m_height;
	for (unsigned int i = 0; i < length; i++) {
		m_destinationBuffer[i].rgbReserved = 0;
		m_destinationBuffer[i].rgbRed = m_colors[i].GetRed();
		m_destinationBuffer[i].rgbGreen = m_colors[i].GetGreen();
		m_destinationBuffer[i].rgbBlue = m_colors[i].GetBlue();
	}

	BitBlt(m_deviceContext, 0, 0, (int)m_width, (int)m_height, m_bitmapContext, 0, 0, SRCCOPY);
	return true;
}