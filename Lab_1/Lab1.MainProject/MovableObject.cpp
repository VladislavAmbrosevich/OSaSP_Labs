#include "stdafx.h"

class MovableObjecct
{
	int _x1, _y1, _width, _height;
	int _oldX1, _oldY1, _oldWidth, _oldHeight;
	int _acceleration = 2;
	int _maxWidth = 0, _maxHeight = 0;
	int _braking = 1;
	int _verticalSpeed = 0, _horizontalSpeed = 0;

public:
	
	enum Direction {Left, Right, Top, Bottom};
	bool toRight = false, toLeft = false, toDown = false, toUp = false;

	explicit MovableObjecct(int x1 = 0, int y1 = 0, int width = 0, int height = 0)
	{
		this->_x1 = x1;
		this->_y1 = y1;
		this->_width = width;
		this->_height = height;

		AssignOldValues();
	}

	void AssignOldValues()
	{
		_oldX1 = _x1;
		_oldY1 = _y1;
		_oldWidth = _width;
		_oldHeight = _height;
	}

	int GetX1() const
	{
		return _x1;
	}
	int GetX2() const
	{
		return _x1 + _width;
	}
	int GetY1() const
	{
		return _y1;
	}
	int GetY2() const
	{
		return _y1 + _height;
	}
	int GetWidth() const
	{
		return _width;
	}
	int GetHeight() const
	{
		return _height;
	}

	void SetX1(int x1) 
	{
		this->_x1 = x1;
	}
	void SetY1(int y1)
	{
		this->_y1 = y1;
	}
	void SetWidth(int width)
	{
		this->_width = width;
	}
	void SetHeight(int height)
	{
		this->_height = height;
	}

	bool IsPositionChanged() const
	{
		if (_x1 == _oldX1 && _y1 == _oldY1)
		{
			return false;
		}
		return true;
	}

	void SetMaxCoordinates(int maxWidth, int maxHeight)
	{
		this->_maxWidth = maxWidth;
		this->_maxHeight = maxHeight;
	}

	void AddSpeed(Direction direction)
	{
		switch (direction)
		{
		case Left:
		{
			_horizontalSpeed += _acceleration;
		}
		break;
		case Right:
		{
			_horizontalSpeed -= _acceleration;
		}
		break;
		case Top:
		{
			_verticalSpeed += _acceleration;
		}
		break;
		case Bottom:
		{
			_verticalSpeed -= _acceleration;
		}
		break;
		default:;
		}
	}

	void ProcessKeys()
	{
		if (toRight)
		{
			_horizontalSpeed += _acceleration;
		}
		if (toLeft)
		{
			_horizontalSpeed -= _acceleration;
		}

		if (toDown)
		{
			_verticalSpeed += _acceleration;
		}
		if (toUp)
		{
			_verticalSpeed -= _acceleration;
		}
	}

	void Draw()
	{
		if (_x1 < 0)
		{
			_horizontalSpeed = -_horizontalSpeed;
		}
		if (_x1+_width > _maxWidth)
		{
			_horizontalSpeed = -_horizontalSpeed;
		}
		if (_y1 < 0)
		{
			_verticalSpeed = -_verticalSpeed;
		}
		if (_y1+_height > _maxHeight)
		{
			_verticalSpeed = -_verticalSpeed;
		}

		this->_x1 += _horizontalSpeed;
		this->_y1 += _verticalSpeed;

		if (_verticalSpeed > 0)
		{
			_verticalSpeed -= _braking;
		}
		if (_verticalSpeed < 0)
		{
			_verticalSpeed += _braking;
		}

		if (_horizontalSpeed > 0)
		{
			_horizontalSpeed -= _braking;
		}
		if (_horizontalSpeed < 0)
		{
			_horizontalSpeed += _braking;
		}
	}
};