#pragma once
#ifndef EAGLE_WINDOWS_RENDERER
#define EAGLE_WINDOWS_RENDERER

#include "EagleRenderer.h"
#include <Windows.h>

namespace Eagle {
	class WindowsRenderer : public Renderer {
	public:
		WindowsRenderer();
		WindowsRenderer(const HDC deviceContext);
		~WindowsRenderer();

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		bool AreMetricsChanged();
		bool Update(float alpha = 1.0f);
		bool Render(float alpha = 1.0f);
	protected:
		RGBQUAD* m_destinationBuffer;
		HDC m_deviceContext;
		HBITMAP m_dibSectionBitmap;
		HDC m_bitmapContext;
		HGDIOBJ m_oldBitmapContext;
	};
}

#endif