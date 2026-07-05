#include "Vector.h"

namespace geometry
{
	Vector3& Vector3::operator=(const Vector3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	bool Vector3::operator==(const Vector3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vector3::operator!=(const Vector3& other)
	{
		return !(x == other.x && y == other.y && z == other.z);
	}

	Vector3 Vector3::operator*(int value)
	{
		Vector3 temp;

		temp.setX(x * value);
		temp.setY(y * value);
		temp.setZ(z * value);

		return temp;
	}

	Vector3 Vector3::operator-(const Vector3& other)
	{
		Vector3 temp;

		temp.setX(x - other.x);
		temp.setY(y - other.y);
		temp.setZ(z - other.z);

		return temp;
	}

	Vector3 Vector3::operator+(const Vector3& other)
	{
		Vector3 temp;

		temp.setX(x + other.x);
		temp.setY(y + other.y);
		temp.setZ(z + other.z);

		return temp;
	}

	std::string Vector3::info()
	{
		return "( " + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + " )";
	}
}
