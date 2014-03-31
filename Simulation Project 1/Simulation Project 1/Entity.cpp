#include "Entity.h"


Entity::Entity(void)
	{
		position = Vector3(0,0,0);
		radius = 0.0f;
		mass = 0.0f;
		previousPosition = position;
	}

Entity::Entity(float x, float y, float z, float m,float r, int i,Vector3 f)
	{
		position = Vector3(x,y,z);
		mass = m;
		radius = r;
		id = i;
		force = f;
		prev_ = NULL;
		next_ = NULL;
		currentVelocity = f;
	}

Entity::~Entity(void)
	{
	}
//Symplectic Euler integration
void Entity::SymplecticEuler(float dt)
	{
		Vector3 nextPos;
		acceleration = (force/mass);

		acceleration.getY() += GRAVITY_ACCEL; 
		//Apply drag to our velocity
		currentVelocity = currentVelocity * DAMPING_FACTOR;

		nextVelocity = currentVelocity + (acceleration*dt);
		nextPos = position + (nextVelocity * dt);
		currentVelocity = nextVelocity;

		//if we are less V than this, we're resting!
		if((currentVelocity < Vector3(0.001f,0.001f,0.001f)) == true)
			{
				currentVelocity = Vector3(0.00f,0.00f,0.00f);
			}

		//Not part of SE but, need it to keep track of a previous position for the Grid (Might mean that in my case it's better to use Verlet anyway);
		previousPosition = position;
		position = nextPos;

		//Call the symplecticEuler method of the next in the linked list
		if((next_ == NULL) == false)
			{
				next_->SymplecticEuler(dt);
			}
	}

// Verlet Integration Function
void Entity::verletIntegration(float deltaT)
	{
		Vector3 nextPos;
		//Our next position is equal to = Our current position + (Our Current Pos - Our last Pos) + (Acceleration (Which is force/mass) * deltaT squared)
		nextPos = position +(position - previousPosition) + ((force/mass) * (deltaT * deltaT));

		//Next, we set our previous position as our current position
		previousPosition = position;

		//and we update our position to the new position
		position = nextPos;

		if(next_ != NULL)
			{
				next_->verletIntegration(deltaT);
			}
	}
