#include "EagleEngine.h"

Eagle::Camera::Camera() {
	m_position = m_right = m_up = m_forward = {};
	m_fieldOfViewHorizontal = m_fieldOfViewVertical = m_planeNear = m_planeFar = m_movingSpeed = m_rotationSpeed = m_yaw = m_pitch = 0.0;
}

Eagle::Camera::Camera(const Camera& camera) {
	*this = camera;
}

Eagle::Camera::Camera(double fieldOfViewHorizontal, double fieldOfViewVertical, double planeNear, double planeFar, const Vector3D position, double movingSpeed, double rotationSpeed, double yaw, double pitch) {
	m_fieldOfViewHorizontal = fieldOfViewHorizontal;
	m_fieldOfViewVertical = fieldOfViewVertical;
	m_planeNear = planeNear;
	m_planeFar = planeFar;
	m_position = position;
	m_movingSpeed = movingSpeed;
	m_rotationSpeed = rotationSpeed;
	m_yaw = yaw;
	m_pitch = pitch;

	m_right = { 1.0, 0.0, 0.0 };
	m_up = { 0.0, 1.0, 0.0 };
	m_forward = { 0.0, 0.0, 1.0 };
	m_right.W = m_up.W = m_forward.W = 1.0;
}

void Eagle::Camera::MoveX(double distance) {
	m_position += m_right * distance * m_movingSpeed;
}

void Eagle::Camera::MoveY(double distance) {
	m_position += m_up * distance * m_movingSpeed;
}

void Eagle::Camera::MoveZ(double distance) {
	m_position += m_forward * distance * m_movingSpeed;
}

void Eagle::Camera::RotateYaw(bool direction) {
	m_yaw += m_rotationSpeed * (direction ? 1.0 : -1.0);
}

void Eagle::Camera::RotatePitch(bool direction) {
	m_pitch += m_rotationSpeed * (direction ? 1.0 : -1.0);
}

Eagle::Matrix Eagle::Camera::GetTranslationMatrix() {
	const double invX = 0 - m_position.X, invY = 0 - m_position.Y, invZ = 0 - m_position.Z;
	const double translationValues[16] = {
		1.0,		0.0,		0.0,		0.0,
		0.0,		1.0,		0.0,		0.0,
		0.0,		0.0,		1.0,		0.0,
		invX,		invY,		invZ,		1.0
	};

	return Matrix(4, 4, translationValues);
}

Eagle::Matrix Eagle::Camera::GetRotationMatrix() {
	m_right = { 1.0, 0.0, 0.0 }, m_up = { 0.0, 1.0, 0.0 }, m_forward = { 0.0, 0.0, 1.0 };
	Matrix planesRotationMatrix = Engine3D::GetRotationXMatrix(m_pitch) * Engine3D::GetRotationYMatrix(m_yaw);
	Vector3D right = m_right, up = m_up, forward = m_forward;

	right *= planesRotationMatrix;
	up *= planesRotationMatrix;
	forward *= planesRotationMatrix;

	const double rotationValues[16] = {
		right.X,	up.X,	forward.X,	0.0,
		right.Y,	up.Y,	forward.Y,	0.0,
		right.Z,	up.Z,	forward.Z,	0.0,
		0.0,	0.0,	0.0,			1.0
	};

	return Matrix(4, 4, rotationValues);
}

Eagle::Matrix Eagle::Camera::GetMatrix() {
	return GetRotationMatrix() * GetTranslationMatrix();
}

double Eagle::Camera::GetHorizontalFieldOfView() {
	return m_fieldOfViewHorizontal;
}

double Eagle::Camera::GetVerticalFieldOfView() {
	return m_fieldOfViewVertical;
}

double Eagle::Camera::GetNearPlane() {
	return m_planeNear;
}

double Eagle::Camera::GetFarPlane() {
	return m_planeFar;
}

Eagle::Vector3D Eagle::Camera::GetPosition() {
	return m_position;
}

double Eagle::Camera::GetYaw() {
	return m_yaw;
}

double Eagle::Camera::GetPitch() {
	return m_pitch;
}

double Eagle::Camera::GetMovingSpeed() {
	return m_movingSpeed;
}

double Eagle::Camera::GetRotationSpeed() {
	return m_rotationSpeed;
}

void Eagle::Camera::SetHorizontalFieldOfView(double fieldOfViewHorizontal) {
	m_fieldOfViewHorizontal = fieldOfViewHorizontal;
}

void Eagle::Camera::SetVerticalFieldOfView(double fieldOfViewVertical) {
	m_fieldOfViewVertical = fieldOfViewVertical;
}

void Eagle::Camera::SetNearPlane(double planeNear) {
	m_planeNear = planeNear;
}

void Eagle::Camera::SetFarPlane(double planeFar) {
	m_planeFar = planeFar;
}

void Eagle::Camera::SetPosition(const Vector3D position) {
	m_position = position;
}

void Eagle::Camera::SetYaw(double yaw) {
	m_yaw = yaw;
}

void Eagle::Camera::SetPitch(double pitch) {
	m_pitch = pitch;
}

void Eagle::Camera::SetMovingSpeed(double movingSpeed) {
	m_movingSpeed = movingSpeed;
}

void Eagle::Camera::SetRotationSpeed(double rotationSpeed) {
	m_rotationSpeed = rotationSpeed;
}

double Eagle::Camera::CalculateVerticalFieldOfView(double fieldOfViewHorizontal, unsigned int screenWidth, unsigned int screenHeight) {
	return fieldOfViewHorizontal * ((double)screenHeight / (double)screenWidth);
}

Eagle::Engine2D::Engine2D() : Canvas() {}
Eagle::Engine2D::Engine2D(Canvas& canvas) {
	m_colors = canvas.GetColors();
	m_width = canvas.GetWidth();
	m_height = canvas.GetHeight();
}

Eagle::Engine2D::~Engine2D() {
	m_colors = 0;
	m_width = m_height = 0;
}

Eagle::Matrix Eagle::Engine2D::GetTranslationMatrix(const Vector2D position) {
	const double translationValues[9] = {
		1.0,	0.0,	position.X,
		0.0,	1.0,	position.Y,
		0.0,	0.0,	1.0
	};

	return Matrix(3, 3, translationValues);
}

Eagle::Matrix Eagle::Engine2D::GetScalingMatrix(const Vector2D scale) {
	const double scalingValues[9] = {
		scale.X,	0.0,	0.0,
		0.0,	scale.Y,	0.0,
		0.0,	0.0,		1.0
	};

	return Matrix(3, 3, scalingValues);
}

Eagle::Matrix Eagle::Engine2D::GetRotationMatrix(const double rotation) {
	const double sineAngle = Sine(rotation), cosineAngle = Cosine(rotation);
	const double rotationValues[9] = {
		cosineAngle,	sineAngle,		0.0,
		0 - sineAngle,	cosineAngle,	0.0,
		0.0,			0.0,			1.0
	};

	return Matrix(3, 3, rotationValues);
}

Eagle::Object2D Eagle::Engine2D::TransformLocalToWorld(const Object2D& object) {
	Object2D worldObject(object);
	worldObject *= GetScalingMatrix(worldObject.GetScale());
	worldObject *= GetRotationMatrix(worldObject.GetRotation());
	worldObject *= GetTranslationMatrix(worldObject.GetPosition());
	return worldObject;
}

bool Eagle::Engine2D::DrawObject(const Object2D& object, const Color& color) {
	Object2D transformed = TransformLocalToWorld(object);
	Point* points = transformed.ProducePoints();
	bool result = DrawPolygon(color, points, transformed.GetVectorsCount());
	delete[] points;
	return result;
}

Eagle::Engine3D::Engine3D() : Engine2D(), m_camera(), m_projectionMatrix(4, 4) {}
Eagle::Engine3D::Engine3D(Canvas& canvas, Camera* camera, Matrix projectionMatrix) {
	m_colors = canvas.GetColors();
	m_width = canvas.GetWidth();
	m_height = canvas.GetHeight();
	m_camera = camera;
	m_projectionMatrix = projectionMatrix;
}

Eagle::Engine3D::~Engine3D() {
	m_colors = 0;
	m_width = m_height = 0;
	m_camera = 0;
}

Eagle::Matrix Eagle::Engine3D::GetTranslationMatrix(const Vector3D position) {
	const double translationValues[16] = {
		1.0,			0.0,			0.0,			0.0,
		0.0,			1.0,			0.0,			0.0,
		0.0,			0.0,			1.0,			0.0,
		position.X,		position.Y,		position.Z,		1.0
	};

	return Matrix(4, 4, translationValues);
}

Eagle::Matrix Eagle::Engine3D::GetScaleMatrix(const Vector3D scale) {
	const double scalingValues[16] = {
		scale.X,	0.0,		0.0,		0.0,
		0.0,		scale.Y,	0.0,		0.0,
		0.0,		0.0,		scale.Z,	0.0,
		0.0,		0.0,		0.0,		1.0
	};

	return Matrix(4, 4, scalingValues);
}

Eagle::Matrix Eagle::Engine3D::GetRotationXMatrix(const double rotationX) {
	const double sineAngleX = Sine(rotationX), cosineAngleX = Cosine(rotationX);
	const double rotationValuesX[16] = {
		1.0,	0.0,			0.0,			0.0,
		0.0,	cosineAngleX,	0 - sineAngleX,	0.0,
		0.0,	sineAngleX,		cosineAngleX,	0.0,
		0.0,	0.0,			0.0,			1.0
	};

	return Matrix(4, 4, rotationValuesX);
}

Eagle::Matrix Eagle::Engine3D::GetRotationYMatrix(const double rotationY) {
	const double sineAngleY = Sine(rotationY), cosineAngleY = Cosine(rotationY);
	const double rotationValuesY[16] = {
		cosineAngleY,	0.0,	sineAngleY,		0.0,
		0.0,			1.0,	0.0,			0.0,
		0 - sineAngleY,	0.0,	cosineAngleY,	0.0,
		0.0,			0.0,	0.0,			1.0
	};

	return Matrix(4, 4, rotationValuesY);
}

Eagle::Matrix Eagle::Engine3D::GetRotationZMatrix(const double rotationZ) {
	const double sineAngleZ = Sine(rotationZ), cosineAngleZ = Cosine(rotationZ);
	const double rotationValuesZ[16] = {
		cosineAngleZ,	0 - sineAngleZ,	0.0,	0.0,
		sineAngleZ,		cosineAngleZ,	0.0,	0.0,
		0.0,			0.0,			1.0,	0.0,
		0.0,			0.0,			0.0,	1.0
	};

	return Matrix(4, 4, rotationValuesZ);
}

Eagle::Object3D Eagle::Engine3D::TransformLocalToWorld(const Object3D& object) {
	Object3D worldObject(object);
	Vector3D rotation = object.GetRotation();
	worldObject *= GetScaleMatrix(worldObject.GetScale());
	worldObject *= GetRotationXMatrix(rotation.X);
	worldObject *= GetRotationYMatrix(rotation.Y);
	worldObject *= GetRotationZMatrix(rotation.Z);
	worldObject *= GetTranslationMatrix(worldObject.GetPosition());
	return worldObject;
}

Eagle::Object3D Eagle::Engine3D::ApplyTransformations(const Object3D& object) {
	const unsigned int trianglesCount = object.GetTrianglesCount();
	const unsigned int verticesCount = trianglesCount * 3;
	Point* points = new Point[verticesCount];
	if (!points) return object;

	Object3D transformedObject = TransformLocalToWorld(object);											//	local -> world
	transformedObject *= m_camera->GetMatrix();															//	world -> camera
	transformedObject *= m_projectionMatrix;															//	camera -> projection
	for (unsigned int i = 0; i < trianglesCount; i++) {													//	projecion -> normalized
		for (unsigned int j = 0; j < 3; j++) {
			transformedObject[i][j] /= transformedObject[i][j].W;
			transformedObject[i][j].W = 1;
		}
	}

	for (unsigned int i = 0; i < trianglesCount; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			if (transformedObject[i][j].X > 1 || transformedObject[i][j].Y > 1 || transformedObject[i][j].Z > 1 || transformedObject[i][j].W > 1 ||
				transformedObject[i][j].X < -1 || transformedObject[i][j].Y < -1 || transformedObject[i][j].Z < -1 || transformedObject[i][j].W < -1) transformedObject[i] = {};
		}
	}

	transformedObject *= GetScreenMatrix();
	return transformedObject;
}

bool Eagle::Engine3D::DrawObject(const Object3D& object, const Color& colorFaces, const Color& colorEdges, const Color& colorVertices, bool drawFaces, bool drawEdges, bool drawVertices) {
	const unsigned int trianglesCount = object.GetTrianglesCount();
	Object3D transformed = ApplyTransformations(object);
	Point trianglePoints[3];

	for (unsigned int i = 0; i < trianglesCount; i++) {
		for (unsigned int j = 0; j < 3; j++) trianglePoints[j] = { transformed[i][j].X, transformed[i][j].Y };
		if (drawFaces) DrawPolygon(colorFaces, trianglePoints, 3);
		if (drawEdges) {
			DrawLine(colorVertices, trianglePoints[0], trianglePoints[1]);
			DrawLine(colorVertices, trianglePoints[1], trianglePoints[2]);
			DrawLine(colorVertices, trianglePoints[2], trianglePoints[0]);
		}
		if (drawVertices) for (unsigned int j = 0; j < 3; j++) DrawCircle(colorVertices, trianglePoints[j], 5.0);
	}

	return true;
}

Eagle::Camera* Eagle::Engine3D::GetCamera() {
	return m_camera;
}

Eagle::Matrix Eagle::Engine3D::GetProjectionMatrix() {
	return m_projectionMatrix;
}

Eagle::Matrix Eagle::Engine3D::GetScreenMatrix() {
	double halfWidth = (double)m_width / 2, halfHeight = (double)m_height / 2;
	const double screenValues[16] = {
		halfWidth,		0.0,			0.0,	0,
		0.0,			0 - halfHeight,	0.0,	0,
		0.0,			0.0,			1.0,	0.0,
		halfWidth,		halfHeight,		0.0,	1.0
	};

	return Matrix(4, 4, screenValues);
}

void Eagle::Engine3D::SetCamera(Camera* camera) {
	m_camera = camera;
}

void Eagle::Engine3D::SetProjectionMatrix(Matrix projectionMatrix) {
	m_projectionMatrix = projectionMatrix;
}