#pragma once
#include <iostream>

using namespace std;
class Vector3
	{
	public:

		Vector3(void);
		~Vector3(void);
		Vector3(float a,float b, float c);
		Vector3(const Vector3 &obj);

		

		//====================Functions================================
		float magnitude();
		float calcScalar(Vector3 rhs);
		Vector3 normalise(float length);

		Vector3 vectorProduct(Vector3 rhs);

		float& getX();
		float& getY();
		float& getZ();

		Vector3 add(Vector3 rhs);
		Vector3 subtract(Vector3 rhs);

		Vector3 prodUnitVector();

		Vector3 findOrtho(Vector3 rhs);


		float dot(Vector3 rhs);


		void scalarMulti(float scalar);
		void scalarDiv(float scalar);

		//===================Operators overload===========================
		Vector3 operator + (Vector3 rhs);
		Vector3 operator - (Vector3 rhs);
		Vector3 operator * (float n);
		Vector3 operator / (float n);
		Vector3 operator = (Vector3 rhs);
		bool operator <(Vector3 rhs);
		


	private:
		float x;
		float y;
		float z;
	};


ostream& operator << (ostream& outStream, Vector3 out);