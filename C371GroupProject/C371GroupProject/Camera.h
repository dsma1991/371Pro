#pragma once
class Camera
{
public:
	Camera(void);
	~Camera(void);

	enum CameraMode
	{
		Pan,
		Rotate,
	};

	void moveCameraTo(double x, double y, double z, CameraMode mode); // move camera smoothly to destination
	void snapCameraTo(double x, double y, double z, CameraMode mode); // move camera instantly to destination

	void displayCamera(); // do the actual gluLookAt and calculations
	void idle();

private:
	double eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ;
	double destinationX, destinationY, destinationZ;
};

