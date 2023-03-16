#pragma once
#ifndef EAGLE_RENDERER_H
#define EAGLE_RENDERER_H
#include "./EagleGraphics.h"

namespace Eagle {
	class Renderer : public Canvas {
	public:
		Renderer();
		Renderer(unsigned int width, unsigned int height);

		virtual bool AreMetricsChanged() = 0;
		virtual bool Update(float alpha = 1.0f) = 0;
		virtual bool Render(float alpha = 1.0f) = 0;
	};
}

#endif