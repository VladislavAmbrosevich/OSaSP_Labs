#pragma once

class MovableObject
{
	int _x1, _y1, _width, _height;
	int _acceleration = 2;
	int _maxWidth = 0, _maxHeight = 0;
	int _braking = 1;
	int _verticalSpeed = 0, _horizontalSpeed = 0;
	bool _toRight = false, _toLeft = false, _toDown = false, _toUp = false;

public:
	enum Direction { Left, Right, Top, Bottom };

	explicit MovableObject(int x1 = 0, int y1 = 0, int width = 0, int height = 0);

	int GetX1() const;
	int GetX2() const;
	int GetY1() const;
	int GetY2() const;
	int GetWidth() const;
	int GetHeight() const;

	void SetX1(int x1);
	void SetY1(int y1);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetMaxCoordinates(int maxWidth, int maxHeight);

	void AddSpeed(Direction direction);
	void StartAcceleration(Direction direction);
	void StopAcceleration(Direction direction);
	void ProcessKeys();

	void Draw();
};
