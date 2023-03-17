#include "EagleProjection.h"

Eagle::Matrix Eagle::Projection::BuildOrthographicProjectionMatrix(double fieldOfViewHorizontal, double fieldOfViewVertical, double planeNear, double planeFar) {
	const double right = Tangent(fieldOfViewHorizontal / 2), top = Tangent(fieldOfViewVertical / 2);
	const double left = 0 - right, bottom = 0 - top;
	const double deltaFarNear = planeFar - planeNear;
	const double projectionValues[16] = {
		2 / (right - left), 0.0,				0.0,										0.0,
		0.0,				2 / (top - bottom), 0.0,										0.0,
		0.0,				0.0,				(planeFar + planeNear) / deltaFarNear,		1.0,
		0.0,				0.0,				-2 * planeFar * planeNear / deltaFarNear,	0.0
	};

	return Matrix(4, 4, projectionValues);
}
