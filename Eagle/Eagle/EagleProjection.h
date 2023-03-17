#pragma once
#ifndef EAGLE_PROJECTION_H
#define EAGLE_PROJECTION_H

#include "EagleTypes.h"

namespace Eagle {
	class Projection {
	public:
		static Matrix BuildOrthographicProjectionMatrix(double fieldOfViewHorizontal, double fieldOfViewVertical, double planeNear, double planeFar);
	};
}

#endif