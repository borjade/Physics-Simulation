#pragma once
#include "Vector3.h"
#include <vector>
#include "Entity.h"
/*
**	Plane struct:
**	The aim of this struct is to simply simulate an infinite plane, which is immovable (so no velocity and infinite mass)
**  All it has really is 4 points to use for normal, a normal and an ID
*/
struct Plane
	{
		Vector3 a;
		Vector3 b;
		Vector3 c;
		Vector3 d;
		int id;
		Vector3 normal;
	};

using namespace std;
//This is the amount of spheres in our world
#define ENTITY_NUMBER 20

//how much do we want stuff to bounce? (more or less)
#define elasticity 0.9f


/*	SimulationWorld class:
**	This is the class where the simulation really happens, it includes collision detection and response for spheres and planes
**  It also implements a 3D world cube partitioning, and tracks the positions of each entity within the cube, allowing to handle
**  collision detection in localized areas and some of the nearby locations.
**
*/
class SimulationWorld
	{
	public:
		SimulationWorld(void);
		~SimulationWorld(void);

		void Init(); // initialise the entities in the world

		void Update(float dt); //update our word!

		void CheckCollisions(Entity* lhs, Entity* rhs); //S-S colisions

		void CheckPlaneCollision(Entity* lhs, Plane plane);  //S-P colisions

		void CollisionResponse(float p, Vector3 N, Vector3 P, Entity* a, Entity* b); //respond to collisions!
		 
		void HandleCell(int x, int y, int z); //handle collision detection in cell

		void Destroy(); // destroy our simulation world

		void Add(Entity* entity); //add to our game cube

		void Move(Entity* entity, Vector3 position); //move from a cell to another cell

		void HandleMovement(Entity* entity, float dt); //handle movement for cell

		//CONSTANTS TO USE FOR WORLD PARTITIONING
		static const int  NUM_CELLS = 10;
		static const int  CELL_SIZE = 20;
	private: 

		//the entity cube
		Entity* cells[NUM_CELLS][NUM_CELLS][NUM_CELLS];

		Plane left;
		Plane top;
		Plane bottom;
		Plane right;
		Plane front;
		Plane back;
	};

