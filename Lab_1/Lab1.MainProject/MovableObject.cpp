#include "stdafx.h"
#include "MovableObject.h"

MovableObject::MovableObject(int x1, int y1, int width, int height)
{
	_x1 = x1;
	_y1 = y1;
	_width = width;
	_height = height;
}

int MovableObject::GetX1() const
{
	return _x1;
}

int MovableObject::GetX2() const
{
	return _x1 + _width;
}

int MovableObject::GetY1() const
{
	return _y1;
}

int MovableObject::GetY2() const
{
	return _y1 + _height;
}

int MovableObject::GetWidth() const
{
	return _width;
}

int MovableObject::GetHeight() const
{
	return _height;
}

void MovableObject::SetX1(int x1)
{
	_x1 = x1;
}
void MovableObject::SetY1(int y1)
{
	_y1 = y1;
}
void MovableObject::SetWidth(int width)
{
	_width = width;
}
void MovableObject::SetHeight(int height)
{
	_height = height;
}

void MovableObject::SetMaxCoordinates(int maxWidth, int maxHeight)
{
	_maxWidth = maxWidth;
	_maxHeight = maxHeight;
}

void  MovableObject::AddSpeed(Direction direction)
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

void  MovableObject::StartAcceleration(Direction direction)
{
	switch (direction)
	{
	case Left:
	{
		_toLeft = true;
	}
	break;
	case Right:
	{
		_toRight = true;
	}
	break;
	case Top:
	{
		_toUp = true;
	}
	break;
	case Bottom:
	{
		_toDown = true;
	}
	break;
	default:;
	}
}

void  MovableObject::StopAcceleration(Direction direction)
{
	switch (direction)
	{
	case Left:
	{
		_toLeft = false;
	}
	break;
	case Right:
	{
		_toRight = false;
	}
	break;
	case Top:
	{
		_toUp = false;
	}
	break;
	case Bottom:
	{
		_toDown = false;
	}
	break;
	default:;
	}
}

void  MovableObject::ProcessKeys()
{
	if (_toRight)
	{
		_horizontalSpeed += _acceleration;
	}
	if (_toLeft)
	{
		_horizontalSpeed -= _acceleration;
	}

	if (_toDown)
	{
		_verticalSpeed += _acceleration;
	}
	if (_toUp)
	{
		_verticalSpeed -= _acceleration;
	}
}

void  MovableObject::Draw()
{
	if (_x1 < 0 || _x1 + _width > _maxWidth)
	{
		_horizontalSpeed = -_horizontalSpeed;
	}
	if (_y1 < 0 || _y1 + _height > _maxHeight)
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
