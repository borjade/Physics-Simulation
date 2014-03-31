#pragma once
#include "Vector3.h"
#include <cmath>
#include "GameTimer.h"
#define DAMPING_FACTOR 0.47;
#define GRAVITY_ACCEL -9.81f;

/*
** Entity Class
** Simple entity class to simulate our spheres.
** Included are two different integration methods, however I've only really used Symplectic, more than anything because
** I ran out of time to try to see if the verlet worked out ok or not.
** Includes methods to retrieve some of the information store (position, velocity etc...) as well
**
*/

using namespace std;
class Entity
	{
		friend class SimulationWorld;
	public:
		
		Entity(void);

		~Entity(void);

		Entity(float x, float y, float z, float m,float r, int i,Vector3 f);

		inline float getRadius(){return radius;}

		inline void updatePos(float &x, float& y, float& z){position = Vector3(x,y,z);};
		inline Vector3 getPos(){return position;};

		void verletIntegration(float deltaT);
		void SymplecticEuler(float dt);

		inline void setForce(Vector3 f) {force = f;};

		inline Vector3 getV(){return currentVelocity;};
		inline void setV(Vector3 v) {currentVelocity = v;};

		inline float getMass(){return mass;};

		inline int getID(){return id;};

		inline bool getRestStatus(){return atRest;};

		inline Vector3 getPreviousPos(){return previousPosition;};


	
	private:

		//Position of the entity
		Vector3 position;
		//Last position of the entity, for Verlet
		Vector3 previousPosition;

		//Mass of the entity
		float mass;

		//Current Velocity = vx
		Vector3 currentVelocity;

		//Next Velocity = vx+1
		Vector3 nextVelocity;
		
		Vector3 previousVelocity;

		Vector3 acceleration;

		float radius;
		
		int id;

		//Force affecting the entity?
		Vector3 force;

		bool atRest;

		Entity* prev_;
		Entity* next_;
	};

