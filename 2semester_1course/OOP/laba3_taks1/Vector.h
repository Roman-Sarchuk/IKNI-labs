#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::to_string;

namespace geometry
{
	class Vector3
	{
		int x{}, y{}, z{};
		
	public:
		Vector3() {}
		Vector3(int x, int y, int z) : x(x), y(y), z(z) {}

		Vector3& operator = (const Vector3& other);
		bool operator == (const Vector3& other);
		bool operator != (const Vector3& other);
		Vector3 operator * (int value);
		Vector3 operator - (const Vector3& other);
		Vector3 operator + (const Vector3& other);

		inline int getX() { return x; }
		inline int getY() { return y; }
		inline int getZ() { return z; }
		inline void setX(int value) { x = value; }
		inline void setY(int value) { y = value; }
		inline void setZ(int value) { z = value; }

		std::string info();
	};
}
