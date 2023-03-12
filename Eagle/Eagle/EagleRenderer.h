#pragma once
#ifndef EAGLE_RENDERER_H
#define EAGLE_RENDERER_H
#include "./EagleGraphics.h"

#ifdef EAGLE_OS_WINDOWS
#include <Windows.h>

namespace Eagle {
	class OSWindowsRenderer : public Graphics::Canvas {
	public:
		OSWindowsRenderer() : Canvas() {
			m_destinationBuffer = 0;
			m_deviceContext = 0;
			m_dibSectionBitmap = 0;
			m_bitmapContext = 0;
			m_oldBitmapContext = 0;
		}

		OSWindowsRenderer(const HDC deviceContext) {
			RECT rect = {};
			GetWindowRect(WindowFromDC(deviceContext), &rect);

			m_destinationBuffer = 0;
			m_width = rect.right - rect.left;
			m_height = rect.bottom - rect.top;
			m_colors = new Graphics::Color[m_width * m_height];
			if (!m_colors) {
				m_width = m_height = 0;
				m_deviceContext = 0;
				m_dibSectionBitmap = 0;
				m_bitmapContext = 0;
				m_oldBitmapContext = 0;
				return;
			}

			BITMAPINFO bmi;
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

		~OSWindowsRenderer() {
			if (m_dibSectionBitmap) {
				SelectObject(m_bitmapContext, m_oldBitmapContext);
				DeleteDC(m_bitmapContext);
				DeleteObject(m_dibSectionBitmap);
			}
		}

		bool Truncate(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
			if (!Canvas::Truncate(x, y, width, height)) return false;

			if (m_dibSectionBitmap) {
				SelectObject(m_bitmapContext, m_oldBitmapContext);
				DeleteDC(m_bitmapContext);
				DeleteObject(m_dibSectionBitmap);
				m_dibSectionBitmap = 0;
			}

			BITMAPINFO bmi;
			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth = (LONG)m_width;
			bmi.bmiHeader.biHeight = -(LONG)m_height;
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;
			bmi.bmiHeader.biCompression = BI_RGB;

			m_dibSectionBitmap = CreateDIBSection(m_deviceContext, &bmi, DIB_RGB_COLORS, (void**)&m_destinationBuffer, 0, 0);
			m_bitmapContext = CreateCompatibleDC(m_deviceContext);
			m_oldBitmapContext = m_dibSectionBitmap ? SelectObject(m_bitmapContext, m_dibSectionBitmap) : 0;
			return true;
		}

		bool Update(float alpha = 1.0) {
			if (!m_dibSectionBitmap) return false;

			BitBlt(m_bitmapContext, 0, 0, (int)m_width, (int)m_height, m_deviceContext, 0, 0, SRCCOPY);
			
			unsigned int length = m_width * m_height;
			for (unsigned int i = 0; i < length; i++) m_colors[i] = Graphics::Color(m_destinationBuffer[i].rgbRed, m_destinationBuffer[i].rgbGreen, m_destinationBuffer[i].rgbBlue);

			return true;
		}

		bool Render(float alpha = 1.0) {
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

		bool IsWindowSizeChanged() const {
			RECT rect = {};
			GetWindowRect(WindowFromDC(m_deviceContext), &rect);
			unsigned int width = (unsigned int)(rect.right - rect.left), height = (unsigned int)(rect.bottom - rect.top);
			return m_width != width || m_height != height;
		}
	protected:
		RGBQUAD* m_destinationBuffer;
		HDC m_deviceContext;
		HBITMAP m_dibSectionBitmap;
		HDC m_bitmapContext;
		HGDIOBJ m_oldBitmapContext;
	};
}
#endif

#endif