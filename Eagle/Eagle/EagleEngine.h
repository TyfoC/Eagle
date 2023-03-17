#pragma once
#ifndef EAGLE_ENGINE_H
#define EAGLE_ENGINE_H

#include "EagleGraphics.h"
#include "EagleProjection.h"

//	Local -> World -> Camera -> Projection -> Normalized -> Screen
namespace Eagle {
	class Camera {
	public:
		Camera();
		Camera(const Camera& camera);
		Camera(double fieldOfViewHorizontal, double fieldOfViewVertical, double planeNear = 0.1, double planeFar = 1000.0, const Vector3D position = {}, double movingSpeed = 0.1, double rotationSpeed = 0.03, double yaw = 0.0, double pitch = 0.0);

		void MoveX(double distance = 1.0);
		void MoveY(double distance = 1.0);
		void MoveZ(double distance = 1.0);
		void RotateYaw(bool direction = true);
		void RotatePitch(bool direction = true);

		Matrix GetTranslationMatrix();
		Matrix GetRotationMatrix();
		Matrix GetMatrix();

		double GetHorizontalFieldOfView();
		double GetVerticalFieldOfView();
		double GetNearPlane();
		double GetFarPlane();
		Vector3D GetPosition();
		double GetMovingSpeed();
		double GetRotationSpeed();
		double GetYaw();
		double GetPitch();

		void SetHorizontalFieldOfView(double fieldOfViewHorizontal = PiQuarter);
		void SetVerticalFieldOfView(double fieldOfViewVertical);
		void SetNearPlane(double planeNear = 0.1);
		void SetFarPlane(double planeFar = 1000.0);
		void SetPosition(const Vector3D position);
		void SetMovingSpeed(double movingSpeed = 0.1);
		void SetRotationSpeed(double rotationSpeed = 0.03);
		void SetYaw(double yaw);
		void SetPitch( double pitch);

		static double CalculateVerticalFieldOfView(double fieldOfViewHorizontal, unsigned int screenWidth, unsigned int screenHeight);
	protected:
		Vector3D m_position;
		Vector3D m_right;
		Vector3D m_up;
		Vector3D m_forward;
		double m_fieldOfViewHorizontal;
		double m_fieldOfViewVertical;
		double m_planeNear;
		double m_planeFar;
		double m_movingSpeed;
		double m_rotationSpeed;
		double m_yaw;
		double m_pitch;
	};

	class Engine2D : public Canvas {
	public:
		Engine2D();
		Engine2D(Canvas& canvas);
		~Engine2D();

		static Matrix GetTranslationMatrix(const Vector2D position);
		static Matrix GetScalingMatrix(const Vector2D scale);
		static Matrix GetRotationMatrix(const double rotation);
		static Object2D TransformLocalToWorld(const Object2D& object);

		bool DrawObject(const Object2D& object, const Color& color);
	};

	class Engine3D : public Engine2D {
	public:
		Engine3D();
		Engine3D(Canvas& canvas, Camera* camera, Matrix projectionMatrix);
		~Engine3D();

		static Matrix GetTranslationMatrix(const Vector3D position);
		static Matrix GetScaleMatrix(const Vector3D scale);
		static Matrix GetRotationXMatrix(const double rotationX);
		static Matrix GetRotationYMatrix(const double rotationY);
		static Matrix GetRotationZMatrix(const double rotationZ);
		static Object3D TransformLocalToWorld(const Object3D& object);

		Object3D ApplyTransformations(const Object3D& object);
		bool DrawObject(const Object3D& object, const Color& color);

		Camera* GetCamera();
		Matrix GetProjectionMatrix();
		Matrix GetScreenMatrix();

		void SetCamera(Camera* camera);
		void SetProjectionMatrix(Matrix projectionMatrix);
	protected:
		Camera* m_camera;
		Matrix m_projectionMatrix;
	};
}

#endif