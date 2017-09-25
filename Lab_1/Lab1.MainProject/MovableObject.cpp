#include "stdafx.h"

class MovableObjecct
{
public:
	int x1, y1, x2, y2;
	int oldX1, oldX2, oldY1, oldY2;
	bool toRight = false, toLeft = false, toDown = false, toUp = false;

	int verticalSpeed = 0, horizontalSpeed = 0;
	int braking = 1;
	int acceleration = 2;
	int maxWidth = 0, maxHeight = 0;


	explicit MovableObjecct(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;

		this->oldX1 = x1;
		this->oldY1 = y1;
		this->oldX2 = x2;
		this->oldY2 = y2;
	}

	void AssignOldValues()
	{
		oldX1 = x1;
		oldY1 = y1;
		oldX2 = x2;
		oldY2 = y2;
	}

	bool IsPositionChanged() const
	{
		if (x1 == oldX1 && y1 == oldY1)
		{
			return false;
		}
		return true;
	}

	void SetMaxCoordinates(int maxWidth, int maxHeight)
	{
		this->maxWidth = maxWidth;
		this->maxHeight = maxHeight;
	}

	void ProcessKeys()
	{
		if (toRight)
		{
			horizontalSpeed += acceleration;
		}
		if (toLeft)
		{
			horizontalSpeed -= acceleration;
		}

		if (toDown)
		{
			verticalSpeed += acceleration;
		}
		if (toUp)
		{
			verticalSpeed -= acceleration;
		}
	}

	void Draw()
	{
		if (x1 < 0)
		{
			horizontalSpeed = -horizontalSpeed;
		}
		if (x2 > maxWidth)
		{
			horizontalSpeed = -horizontalSpeed;
		}
		if (y1 < 0)
		{
			verticalSpeed = -verticalSpeed;
		}
		if (y2 > maxHeight)
		{
			verticalSpeed = -verticalSpeed;
		}


		this->x1 += horizontalSpeed;
		this->x2 += horizontalSpeed;

		this->y1 += verticalSpeed;
		this->y2 += verticalSpeed;

		if (verticalSpeed > 0)
		{
			verticalSpeed -= braking;
		}
		if (verticalSpeed < 0)
		{
			verticalSpeed += braking;
		}

		if (horizontalSpeed > 0)
		{
			horizontalSpeed -= braking;
		}
		if (horizontalSpeed < 0)
		{
			horizontalSpeed += braking;
		}
	}

	void Stop()
	{
		toDown = toUp = toRight = toLeft = false;
	}
};