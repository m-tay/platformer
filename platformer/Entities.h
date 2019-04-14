#pragma once
#include "Game.h"

// class for the moving platforms
class MovingPlatform
{
public:

	Game *game;
	float posX;	// position
	float posY;
	float velX = 0.0f;	// velocity
	float velY = 0.0f;
	float newPosX;
	float newPosY;
	char tileTL;	// holds the 4 tiles around the entity
	char tileTR;
	char tileBL;
	char tileBR;
	int tilesWide = 3;
	int platformWidth;
	bool movingPosX = true;

	// constructor
	MovingPlatform(Game& gameObj, float x, float y);

	// calculates the tiles around the entity
	void findSurroundingTiles();

	// check for collisions with tilemap on x axis
	bool isCollidingX();

	// check for collisions with tilemap on y axis
	bool isCollidingY();

	// update entity position based on velocity
	void updatePosition();

	// draws the entity
	void draw();
};

// class for character entities
class Entity {
public:

	// constructor
	Entity(Game& gameObj, float x, float y);

	Game *game;
	float posX;	// position
	float posY;
	float velX = 0.0f;	// velocity
	float velY = 0.0f;
	float newPosX;
	float newPosY;
	char tileTL;	// holds the 4 tiles around the entity
	char tileTR;
	char tileBL;
	char tileBR;
	bool onGround;	// holds whether entity is on ground
	bool jumping;	// holds whether entity is in process of jumping
	bool alive = true;	// holds whether entity is alive
	int jumpTime;	// holds how long entity has been in air
	float playerSpriteFrame = 0.0f; // tracks the playerSpriteFrame for animating the sprite
	char facing = 'r'; // holds direction entity is facing (for sprite mirroring)

	// holds tile coords surrounding entity (x,y)
	int tileLeft, tileRight, tileTop, tileBottom;

	// spriteSet holds all a vector of GLuint arrays to store all the textures
	vector<vector<GLuint> >spriteSet;

	// calculates the cartesian coords of surrounding tiles
	void calculateSurroundingTiles();

	// calculates the tiles around the entity
	void checkSpecialTiles();

	// check for collisions with tilemap on x axis
	bool isCollidingX();

	// check for collisions with tilemap on y axis
	bool isCollidingY();

	// check for collisions with moving platforms 
	bool isCollidingWithMovingPlatform();

	// update entity position if standing on top of a moving platform
	void trackMovingPlatforms();

	// check for collisions with enemies
	bool isCollidingWithEnemies();

	// update entity position based on velocity
	void updatePosition();

	// draws the entity
	void draw();
};

// class for character entities
class Enemy {
public:

	// constructor
	Enemy(Game& gameObj, float x, float y);

	Game *game;
	float posX;	// position
	float posY;
	float velX = 0.0f;	// velocity
	float velY = 0.0f;
	float newPosX;
	float newPosY;
	char tileTL;	// holds the 4 tiles around the entity
	char tileTR;
	char tileBL;
	char tileBR;
	bool onGround;	// holds whether entity is on ground
	bool jumping;	// holds whether entity is in process of jumping
	bool alive = true; // holds whether entity is alive
	int jumpTime;	// holds how long entity has been in air
	float spriteFrame = 0.0f; // tracks the enemy1 sprite frame for animating the sprite
	char facing = 'r'; // holds direction entity is facing (for sprite mirroring)
	bool movingPosX = true;

	// holds tile coords surrounding entity (x,y)
	int tileLeft, tileRight, tileTop, tileBottom;

	// spriteSet holds all a vector of GLuint arrays to store all the textures
	// vector[0] - walking animation	
	vector<vector<GLuint> >spriteSet;

	// calculates the cartesian coords of surrounding tiles
	void calculateSurroundingTiles();

	// check for collisions with tilemap on x axis
	bool isCollidingX();

	// check for collisions with tilemap on y axis
	bool isCollidingY();

	// checks if hit by bullet
	bool isCollidingWithProjectile();

	// update entity position based on velocity
	void updatePosition();

	// draws the entity
	void draw();
};

// class for projectiles
class Projectile {
public:

	// constructor
	Projectile(Game& gameObj, float x, float y, char dir);

	Game *game;
	float posX;	// position
	float posY;
	float velX = 0.0f;	// velocity
	float velY = 0.0f;
	float newPosX;
	float newPosY;
	char tileTL;	// holds the 4 tiles around the entity
	char tileTR;
	char tileBL;
	char tileBR;
	float bulletSpriteFrame = 0.0f; // tracks the playerSpriteFrame for animating the sprite
	char direction;
	bool active = true;

   // holds tile coords surrounding entity (x,y)
	int tileLeft, tileRight, tileTop, tileBottom;

	// spriteSet holds all a vector of GLuint arrays to store all the textures
	vector<vector<GLuint> >spriteSet;

	// calculates the cartesian coords of surrounding tiles
	void calculateSurroundingTiles();

	// check for collisions with tilemap on x axis
	bool isCollidingX();

	// check for collisions with enemies
	bool isCollidingWithEnemies();

	// update entity position based on velocity
	void updatePosition();

	// draws the entity
	void draw();
};
