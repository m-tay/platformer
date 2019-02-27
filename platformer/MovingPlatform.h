#pragma once
#include "Game.h"

class MovingPlatform
{
	public:
		// constructor
		MovingPlatform(Game& gameObj, float x, float y);

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


