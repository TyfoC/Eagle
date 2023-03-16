#pragma once
#ifndef EAGLE_ENGINE_H
#define EAGLE_ENGINE_H

#include "EagleGraphics.h"

namespace Eagle {
	class Engine : public Canvas {
	public:
		Engine();
		Engine(Canvas& canvas);
		bool DrawObject(const Object2D& object, const Color& color);
	};
}

#endif