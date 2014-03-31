#include "SimulationWorld.h"





SimulationWorld::SimulationWorld(void)
	{
		//When we create the world, lets clear our grid
		for(int x = 0; x < NUM_CELLS; ++x)
			{
			for(int y = 0; y < NUM_CELLS; ++y)
				{
				for(int z = 0; z < NUM_CELLS; ++z)
					{
						cells[x][y][z] = NULL;
					}
				}
			}

		

		//initialise our planes
		left.a = Vector3(0,0,0); 
		left.b = Vector3(0,NUM_CELLS * CELL_SIZE,0); 
		left.c = Vector3(0,NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE); 
		left.d = Vector3(0,0,NUM_CELLS * CELL_SIZE); 
		left.normal = ((left.b-left.a).vectorProduct((left.c - left.a))).normalise((left.b-left.a).vectorProduct((left.c - left.a)).magnitude());
		left.id = 0;

		bottom.a = Vector3(0,0,0); 
		bottom.b = Vector3(0,0,NUM_CELLS * CELL_SIZE); 
		bottom.c = Vector3(NUM_CELLS * CELL_SIZE,0,0); 
		bottom.d = Vector3(NUM_CELLS * CELL_SIZE,0,NUM_CELLS * CELL_SIZE); 
		bottom.normal = ((bottom.b-bottom.a).vectorProduct((bottom.c - bottom.a))).normalise(((bottom.b-bottom.a).vectorProduct((bottom.c - bottom.a))).magnitude());
		bottom.id = 1;

		front.a = Vector3(0,0,0);
		front.b = Vector3(0,NUM_CELLS * CELL_SIZE,0); 
		front.c = Vector3(NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE,0); 
		front.d = Vector3(NUM_CELLS * CELL_SIZE,0,0); 
		front.normal = ((front.b-front.d).vectorProduct((front.c - front.d))).normalise(((front.b-front.d).vectorProduct((front.c - front.d))).magnitude());
		front.normal = front.normal * -1;
		front.id = 2;


		right.a = Vector3(NUM_CELLS * CELL_SIZE,0,0);
		right.b = Vector3(NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE,0); 
		right.c = Vector3(NUM_CELLS * CELL_SIZE,0,NUM_CELLS * CELL_SIZE); 
		right.d = Vector3(NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE); 
		right.normal = ((right.b-right.a).vectorProduct((right.c - right.a))).normalise(((right.b-right.a).vectorProduct((right.c - right.a))).magnitude());
		right.id = 3;

		back.a = Vector3(0,0,NUM_CELLS * CELL_SIZE);
		back.b = Vector3(0,NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE);
		back.c = Vector3(NUM_CELLS * CELL_SIZE,0,NUM_CELLS * CELL_SIZE);
		back.d = Vector3(NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE);
		back.normal = ((back.b-back.a).vectorProduct((back.c - back.a))).normalise(((back.b-back.a).vectorProduct((back.c - back.a))).magnitude());
		back.id = 4;

		top.a = Vector3(0,NUM_CELLS * CELL_SIZE,0);
		top.b = Vector3(NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE,0);
		top.c = Vector3(0,NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE);
		top.d = Vector3(NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE,NUM_CELLS * CELL_SIZE);
		top.normal = ((top.b-top.a).vectorProduct((top.c - top.a))).normalise(((top.b-top.a).vectorProduct((top.c - top.a))).magnitude());
		top.id = 5;
	}


SimulationWorld::~SimulationWorld(void)
	{
	}

void SimulationWorld::Init()
	{
		
		//Create the entities (spheres + planes);
		for(int i = 0; i < ENTITY_NUMBER; ++i)
			{
				Add(new Entity((float)(rand()%(NUM_CELLS * CELL_SIZE)),(float)(rand()%(NUM_CELLS * CELL_SIZE)),(float)(rand()%(NUM_CELLS * CELL_SIZE)),(float)(rand()%(NUM_CELLS * CELL_SIZE)/2)+1,(float)(rand()%(NUM_CELLS * CELL_SIZE)/5)+1,i,Vector3((float)(rand()%100),(float)(rand()%100),(float)(rand()%100))));
			}
	}

void SimulationWorld::Destroy()
	{
		delete [] cells;
	}

//Update function, this is the main physics loop.
void SimulationWorld::Update(float dt)
	{
		cout << "================================================\n";
		cout << "Dimensions of the Cube: " << NUM_CELLS * CELL_SIZE << " by " << NUM_CELLS * CELL_SIZE << "\n";
		cout << "================================================\n";
		for(int z = 0; z < NUM_CELLS; z++)
			{
				for(int y = 0; y < NUM_CELLS; y++)
				{
					for(int x = 0; x < NUM_CELLS; x++)
					{
						//for all the cells we handle the movement inside (if there is any!)
						HandleMovement(cells[x][y][z],dt);
						//then handle any collisions
						HandleCell(x,y,z);
					}
				}
			}					
		cout << "================================================";
		system("cls");
	}
//This function is used to handles all the collision detections of a specific cell
void SimulationWorld::HandleCell(int x, int y, int z)
	{
		//Look at the head entity
		Entity* entity = cells[x][y][z];
		//While it isn't null
		while (entity != NULL)
			{
				CheckCollisions(entity,entity->next_); //Collision detect for all in current cell
				
				//As well as some of the nearby cells, not all as we don't want to be doing calculations twice
				if(x>0 && y > 0 && z > 0) 
					{ 
						CheckCollisions(entity, cells[x-1][y-1][z-1]);
					}
				if(x>0)
					{
						CheckCollisions(entity, cells[x-1][y][z]);
					}
				if(y>0)
					{
						CheckCollisions(entity, cells[x][y-1][z]);
					}
				if(z>0)
					{
						CheckCollisions(entity, cells[x][y][z-1]);
					}

				//If we are in row of cells x == 0, check to see if we hit left etc..
				if(x == 0)
					{
						//Check collisions with left plane
						CheckPlaneCollision(entity,left);
					}
				if(x == NUM_CELLS-1)
					{
						//Check Collisions with the right plane	
						CheckPlaneCollision(entity,right);
					}
				if(y == 0)
					{
						//bottom
						CheckPlaneCollision(entity,bottom);
					}
				if(y == NUM_CELLS-1)
					{
						//top
						CheckPlaneCollision(entity,top);
					}
				if(z == 0)
					{
						//front
						CheckPlaneCollision(entity,front);
					}
			    if(z == NUM_CELLS-1)
					{
						//back
						CheckPlaneCollision(entity,back);
					}

				//Move to next entity in cell!
				entity = entity->next_;
			}
	}

//Method to check the collisions sphere-planes
void SimulationWorld::CheckPlaneCollision(Entity* lhs, Plane plane)
	{
		//calculate d
		float d = plane.normal.calcScalar(Vector3(0,0,0));

		//if we have intersected, then react
		if((plane.normal.dot(lhs->getPos()) + d ) < lhs->getRadius())
			{
				float p = lhs->getRadius() - (plane.normal.dot(lhs->getPos()) + d );
				Vector3 ContactPoint = lhs->getPos() - ( plane.normal * (lhs->getRadius() - p));
				cout << "\nSphere " << lhs->getID() << " collided with plane: " << plane.id  <<" \n";	
				
				if(p > NUM_CELLS * CELL_SIZE){
					p -= NUM_CELLS * CELL_SIZE; } //Bound p or in some instance we'll send our spheres outside the cube

				//Deal with the collision right here.
				lhs->position = (lhs->position +((plane.normal)*p)); //push our entity outside the plane
				Move(lhs,lhs->position); //check that we don't need to move to a different cell?
				lhs->setV((lhs->currentVelocity * elasticity) * -1); //reverse our velocity as we've just hit an immovable object
			}
	}

//Sphere-sphere collision detection algorithm
void SimulationWorld::CheckCollisions(Entity* lhs, Entity* rhs)
	{

	while (rhs != NULL)
		{
			float dist = ( (rhs->getPos().getX()-lhs->getPos().getX()) * (rhs->getPos().getX()-lhs->getPos().getX()) ) +
						 ( (rhs->getPos().getY()-lhs->getPos().getY()) * (rhs->getPos().getY()-lhs->getPos().getY()) ) +
						 ( (rhs->getPos().getZ()-lhs->getPos().getZ()) * (rhs->getPos().getZ()-lhs->getPos().getZ()) );

			if(dist < ( (lhs->getRadius()+rhs->getRadius()) * (lhs->getRadius()+rhs->getRadius()) ))
				{
					float p = (lhs->getRadius() + rhs->getRadius()) - rhs->getPos().calcScalar(lhs->getPos());
					Vector3 Normal = lhs->getPos() - rhs->getPos();
					Normal = Normal.normalise(Normal.magnitude());
					Vector3 ContactPoint = lhs->getPos() - (Normal* (lhs->getRadius() - p) );

					cout << "\nSphere" << lhs->getID() << " collided with " << rhs->getID() << " \n";

					CollisionResponse(p,Normal,ContactPoint,lhs,rhs);
				}
			rhs = rhs->next_;
		}
	}

//Sphere-sphere collision response algorithm
void SimulationWorld::CollisionResponse(float p, Vector3 N, Vector3 P, Entity* a, Entity* b)
	{
		Vector3 vaAFTER;
		Vector3 vbAFTER;

		Vector3 vab;

		a->position = (a->position +(N*p)); //"shunt" a in away from b

		vab = a->getV() + b->getV();
		float J = ( -1 * ( (1+elasticity) * (vab.dot(N)) ) ) / ( N.dot(N) * ( (1/a->getMass()) + (1/b->getMass()) ) ) ; 

		vaAFTER = a->getV() + ( N*(J/a->getMass()) ) ;
		vbAFTER = b->getV() - ( N*(J/b->getMass()) );

		a->setV(vaAFTER);
		b->setV(vbAFTER);

	}

//Method to add entities to the 3D world grid
void SimulationWorld::Add(Entity* entity)
	{
		//First determine which cell of the grid it is in
		int cellX = (int)(entity->getPos().getX() / SimulationWorld::CELL_SIZE);
		int cellY = (int)(entity->getPos().getY() / SimulationWorld::CELL_SIZE);
		int cellZ = (int)(entity->getPos().getZ() / SimulationWorld::CELL_SIZE);

		//Add to the front of the list for the cell it is going to be in
		entity->prev_ = NULL;
		entity->next_ = cells[cellX][cellY][cellZ];
		cells[cellX][cellY][cellZ] = entity;

		//lastly if it's not alone in the cell, connect the NEXT entity to this entity, by setting it's prev_ pointer to our current entity
		if (!(entity->next_ == NULL))
			{
				entity->next_->prev_ = entity;
			}
	}

/*	Method handles the movement of the entitities within our cube
/	The idea is to move our entities in game world first, 
/	and then to use that change in position to see if we need to update their position in the cube. */
void SimulationWorld::HandleMovement(Entity* entity, float dt)
	{
		//for all the entities in our sub-cube
		while(!(entity == NULL))
			{	
				
				//Integrate
				entity->SymplecticEuler(dt);
				//then actually move the entity accross different cells if needed, in respect with it's world position
				Move(entity,entity->getPos());	
				//then output
				cout << "|Sphere:" << entity->getID() << " |Position: " << entity->getPos() <<" |Radius: " << entity->getRadius() << "|Mass: " << entity->getMass() <<"|\n";
				//move to the next!
				
				entity = entity->next_;
			}
	}

//Function to actually move (if deemed necessary) accross our cells in he world.
void SimulationWorld::Move(Entity* entity, Vector3 position)
	{
		//Lets check which cell we were previously in
		int oldCellX = (int)(entity->getPreviousPos().getX()/ SimulationWorld::CELL_SIZE);
		int oldCellY = (int)(entity->getPreviousPos().getY()/ SimulationWorld::CELL_SIZE);
		int oldCellZ = (int)(entity->getPreviousPos().getZ()/ SimulationWorld::CELL_SIZE);

		//where are we going to?
		int cellX = (int)(position.getX() / SimulationWorld::CELL_SIZE);
		int cellY = (int)(position.getY() / SimulationWorld::CELL_SIZE);
		int cellZ = (int)(position.getZ() / SimulationWorld::CELL_SIZE);

		//No change so don't do anything
		if(oldCellX == cellX && oldCellY == cellY && oldCellZ == cellZ) 
			{
				return;
			} 


		//De-attach from the cell
		if(!(entity->prev_ == NULL) && !(entity->next_ == NULL)) 
			{
				entity->next_->prev_ = entity->prev_;
				entity->prev_->next_ = entity->next_;
			}

		//If we were the top of the list, make the head the next entity in the list
		if(cells[oldCellX][oldCellY][oldCellZ] == entity)
			{
				cells[oldCellX][oldCellY][oldCellZ] = entity->next_; 
			}

		//We don't want to be connected to anyone just yet
		entity->next_ = NULL;
		entity->prev_ = NULL;

		Add(entity);
	}