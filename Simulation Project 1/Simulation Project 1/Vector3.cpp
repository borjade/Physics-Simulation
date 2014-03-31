#include "Vector3.h"
#include <cmath>


Vector3::Vector3(void)
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}


Vector3::~Vector3(void)
	{
	}

Vector3::Vector3(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
	}

Vector3::Vector3(const Vector3 &obj)
	{
     	x = obj.x;
		y = obj.y;
		z = obj.z;
	}

#pragma region Operators 
//======================OPERATOR OVERLOADS======================================

Vector3 Vector3::operator=(Vector3 rhs)
	{
		x = rhs.getX();
		y = rhs.getY();
		z = rhs.getZ();

		return *this;
	}

Vector3 Vector3::operator+(Vector3 rhs)
	{
		return add(rhs);
	}

Vector3 Vector3::operator-(Vector3 rhs)
	{
		return subtract(rhs);
	}

Vector3 Vector3::operator*(float n)
	{
		return Vector3(x*n,y*n,z*n);
	}

Vector3 Vector3::operator/(float n)
	{
		return Vector3(x/n,y/n,z/n);
	}

// not really a way to see if a vector is smaller than the other, but i only need it to check versus a threshold (for rest)
bool Vector3::operator<(Vector3 rhs)
	{
		if(x < rhs.getX() && y < rhs.getY() && z < rhs.getZ())
			{
				return true;
			}
		else
			{
				return false;
			}
	}

//=======================END OPERATOR OVERLOAD=======================
#pragma endregion Operators

#pragma region Functions
float Vector3::magnitude()
	{
		return (float)pow((double)((x * x) + (y * y) + (z * z)),0.5);
	}

Vector3 Vector3::normalise(float length)
	{
		return Vector3(x/length,y/length,z/length);
	}
//=================GETTER FUCTIONS===============================
float& Vector3::getX()
	{
		return x;
	}

float& Vector3::getY()
	{
		return y;
	}

float& Vector3::getZ()
	{
		return z;
	}
//================END GETTER FUNCTIONS===========================

Vector3 Vector3::add(Vector3 rhs)
	{
		Vector3 answer (x+rhs.getX(),y+rhs.getY(),z+rhs.getZ());
		return answer;
	}

Vector3 Vector3::subtract(Vector3 rhs)
	{
		Vector3 answer (x-rhs.getX(),y-rhs.getY(),z-rhs.getZ());
		return answer;
	}
#pragma region LEFTOVERS
//NOTE THESE ARE PRETTY MUCH LEFT OVER FROM SEM 1 ASSIGNMENT FOR PROGRAMMING FOR GAMES
//I tried cleaning it all up, but can't assure some of these are pretty much the same as others. 
void Vector3::scalarMulti(float scalar)
	{
		x *=  scalar;
		y *=  scalar;
		z *=  scalar;
	}

Vector3 Vector3::vectorProduct(Vector3 rhs)
	{
		return Vector3((y*rhs.getZ())-(z * rhs.getY()),(z*rhs.getX())-(x*rhs.getZ()),(x*rhs.getY())-(y*rhs.getX()));
	}

void Vector3::scalarDiv(float scalar)
	{
		x /=  scalar;
		y /=  scalar;
		z /=  scalar;
	}

float Vector3::calcScalar(Vector3 rhs)
	{
		return ((rhs.getX()-x)+(rhs.getY()-y)+(rhs.getZ()-z));
	}

Vector3 Vector3::prodUnitVector()
	{
		Vector3 answer (x/magnitude(),y/magnitude(),z/magnitude());
		return answer;
	}

float Vector3::dot(Vector3 rhs)
	{
		return (	(x * rhs.getX())	+	(y * rhs.getY())	+	(z * rhs.getZ())	);
	}

#pragma endregion LEFTOVERS

#pragma endregion Functions

ostream& operator <<(ostream& outStream, Vector3 out)
	{
		outStream << "Vector(" << out.getX() << "," << out.getY() << "," << out.getZ() << ")";
		return outStream;
	}