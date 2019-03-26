#include "Entities.h"
#include <iostream>

MovingPlatform::MovingPlatform(Game& gameObj, float x, float y) {
	posX = x;
	posY = y;
	game = &gameObj;
	platformWidth = tilesWide * game->tileWidth; // how many tiles wide the platform is
};

// calculates the tiles around the entity
void MovingPlatform::findSurroundingTiles() {
	// calculate x,y coords of surrounding tiles
	int tileLeft = (int)newPosX / game->tileWidth;
	int tileRight = (int)(newPosX / game->tileWidth) + platformWidth;
	int tileTop = (int)(newPosY / game->tileHeight) + platformWidth;
	int tileBottom = (int)newPosY / game->tileHeight;

	// get the actual tile values from tilemap
	char tileTL = game->getTile(game, tileLeft, tileTop);
	char tileTR = game->getTile(game, tileRight, tileTop);
	char tileBL = game->getTile(game, tileLeft, tileBottom);
	char tileBR = game->getTile(game, tileRight, tileBottom);
}

// check for collisions with tilemap on x axis
bool MovingPlatform::isCollidingX() {
	// calculate x,y coords of surrounding tiles
	// assumes entities are no bigger than 1 standard tile width
	int tileLeft = (int)newPosX / game->tileWidth;
	int tileRight = (int)(newPosX / game->tileWidth) + tilesWide;
	int tileTop = (int)(posY / game->tileHeight) + 1;
	int tileBottom = (int)posY / game->tileHeight;

	// get the actual tile values from tilemap
	char tileTL = game->getTile(game, tileLeft, tileTop);
	char tileTR = game->getTile(game, tileRight, tileTop);
	char tileBL = game->getTile(game, tileLeft, tileBottom);
	char tileBR = game->getTile(game, tileRight, tileBottom);

	// if any collisions detected...
	if (tileTL == '#' || tileTR == '#' || tileBL == '#' || tileBR == '#' ||
		tileTL == 'D' || tileTR == 'D' || tileBL == 'D' || tileBR == 'D') {

		// invert direction of movement flag
		if (movingPosX)
			movingPosX = false;
		else
			movingPosX = true;

		return true;
	}

	// if not colliding, return false
	return false;
}

// check for collisions with tilemap on y axis
bool MovingPlatform::isCollidingY() {
	// calculate x,y coords of surrounding tiles
	// assumes entities are no bigger than 1 standard tile width
	int tileLeft = (int)posX / game->tileWidth;
	int tileRight = (int)(posX / game->tileWidth) + 1;
	int tileTop = (int)(newPosY / game->tileHeight) + 1;
	int tileBottom = (int)newPosY / game->tileHeight;

	// get the actual tile values from tilemap
	char tileTL = game->getTile(game, tileLeft, tileTop);
	char tileTR = game->getTile(game, tileRight, tileTop);
	char tileBL = game->getTile(game, tileLeft, tileBottom);
	char tileBR = game->getTile(game, tileRight, tileBottom);

	// ceiling collision, set y velocity to 0
	if (tileTL == '#' || tileTR == '#' ||
		tileTL == 'D' || tileTR == 'D') {
		velY = 0;
		return true;
	}

	// ground collision, set jumping flag back to false
	if (tileBL == '#' || tileBR == '#' ||
		tileBL == 'D' || tileBR == 'D') {
		return true;
	}

	// if not colliding, return false
	return false;
}

// update entity position based on velocity
void MovingPlatform::updatePosition() {
	// add velocity to platform
	if (movingPosX)
		velX = 0.2f;
	else
		velX = -0.2f;

	// update entity's model of the tiles surrounding it
	findSurroundingTiles();

	// calculate proposed new position
	newPosX = posX + (velX * game->deltaTime);
	newPosY = posY + (velY * game->deltaTime);

	// check for collision in x axis
	if (!isCollidingX())
		posX = newPosX;

	// check for collision in y asis
	if (!isCollidingY())
		posY = newPosY;

}

// draws the entity
void MovingPlatform::draw() {

	updatePosition();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game->tileTextures[0]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 1.0);
	glVertex2f(posX, posY);

	glTexCoord2d(tilesWide, 1.0);
	glVertex2f(posX + platformWidth, posY);

	glTexCoord2d(tilesWide, 0.0);
	glVertex2f(posX + platformWidth, posY + game->tileHeight);

	glTexCoord2d(0.0, 0.0);
	glVertex2f(posX, posY + game->tileHeight);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

// constructor
Entity::Entity(Game& gameObj, float x, float y) { 
	posX = x;
	posY = y;
	game = &gameObj;
}

// calculates the cartesian coords of surrounding tiles
void Entity::calculateSurroundingTiles() {
	tileLeft = (int)posX / game->tileWidth;
	tileRight = (int)(posX / game->tileWidth) + 1;
	tileTop = (int)(posY / game->tileHeight) + 1;
	tileBottom = (int)posY / game->tileHeight;
}

// calculates the tiles around the entity
void Entity::checkUpdateCollectables() {
	// calculate x,y coords of surrounding tiles
	// assumes entities are no bigger than 1 standard tile width
	tileLeft = (int)newPosX / game->tileWidth;
	tileRight = (int)(newPosX / game->tileWidth) + 1;
	tileTop = (int)(newPosY / game->tileHeight) + 1;
	tileBottom = (int)newPosY / game->tileHeight;

	// get the actual tile values from tilemap
	char tileTL = game->getTile(game, tileLeft, tileTop);
	char tileTR = game->getTile(game, tileRight, tileTop);
	char tileBL = game->getTile(game, tileLeft, tileBottom);
	char tileBR = game->getTile(game, tileRight, tileBottom);

	// update player score, remove collectable
	if(tileTL == '1') {
		game->playerScore++;	// update score
		game->emptyTile(game, tileLeft, tileTop);
	}

	if (tileTR == '1') {
		game->playerScore++;	// update score
		game->emptyTile(game, tileRight, tileTop);
	}

	if (tileBL == '1') {
		game->playerScore++;	// update score
		game->emptyTile(game, tileLeft, tileBottom);
	}

	if (tileBR == '1') {
		game->playerScore++;	// update score
		game->emptyTile(game, tileRight, tileBottom);
	}
}

// check for collisions with tilemap on x axis
bool Entity::isCollidingX() {
	// calculate x,y coords of surrounding tiles
	// assumes entities are no bigger than 1 standard tile width
	tileLeft = (int)newPosX / game->tileWidth;
	tileRight = (int)(newPosX / game->tileWidth) + 1;
	tileTop = (int)(posY / game->tileHeight) + 1;
	tileBottom = (int)posY / game->tileHeight;

	// get the actual tile values from tilemap
	char tileTL = game->getTile(game, tileLeft, tileTop);
	char tileTR = game->getTile(game, tileRight, tileTop);
	char tileBL = game->getTile(game, tileLeft, tileBottom);
	char tileBR = game->getTile(game, tileRight, tileBottom);

	// if any collisions detected, return true
	if (tileTL == '#' || tileTR == '#' || tileBL == '#' || tileBR == '#' ||
		tileTL == 'D' || tileTR == 'D' || tileBL == 'D' || tileBR == 'D')
		return true;

	// if not colliding, return false
	return false;
}

// check for collisions with tilemap on y axis
bool Entity::isCollidingY() {
	// calculate x,y coords of surrounding tiles
	// assumes entities are no bigger than 1 standard tile width
	tileLeft = (int)posX / game->tileWidth;
	tileRight = (int)(posX / game->tileWidth) + 1;
	tileTop = (int)(newPosY / game->tileHeight) + 1;
	tileBottom = (int)newPosY / game->tileHeight;

	// get the actual tile values from tilemap
	char tileTL = game->getTile(game, tileLeft, tileTop);
	char tileTR = game->getTile(game, tileRight, tileTop);
	char tileBL = game->getTile(game, tileLeft, tileBottom);
	char tileBR = game->getTile(game, tileRight, tileBottom);

	// ceiling collision, set y velocity to 0
	if (tileTL == '#' || tileTR == '#' || tileTL == 'D' || tileTR == 'D') {
		velY = 0;
		return true;
	}

	// ground collision, set jumping flag back to false
	if (tileBL == '#' || tileBR == '#' || tileBL == 'D' || tileBR == 'D') {
		onGround = true;
		return true;
	}

	// if not colliding, return false
	return false;
}

bool Entity::isCollidingWithMovingPlatform() {
	// loop through all moving platforms
	for (int i = 0; i < game->movingPlatforms.size(); i++) {
		// AABB edge overlap checks
		if (newPosX + game->tileWidth >= game->movingPlatforms.at(i)->posX								&&
			newPosX <= game->movingPlatforms.at(i)->posX + game->movingPlatforms.at(i)->platformWidth	&&
			newPosY + game->tileHeight >= game->movingPlatforms.at(i)->posY							&&
			newPosY <= game->movingPlatforms.at(i)->posY + game->tileHeight) {

			// if AABB overlap, check if entity is hitting it from the bottom
			if ((newPosX + game->tileHeight) >= game->movingPlatforms.at(i)->posX &&
				(newPosX + game->tileHeight) < (game->movingPlatforms.at(i)->posX + game->tileHeight)) {
				velY = 0;
			}
			
			return true;
		}
	}

	// if no edge overlaps detected
	return false;
}

void Entity::trackMovingPlatforms() {

	// loop through all moving platforms
	for (int i = 0; i < game->movingPlatforms.size(); i++) {

		// check if within x axis of moving platform
		if (posX >= game->movingPlatforms.at(i)->posX && (posX + game->tileWidth) < (game->movingPlatforms.at(i)->posX + game->movingPlatforms.at(i)->platformWidth)) {

			// check if close enough to surface of moving platform to track movement
			if ((game->movingPlatforms.at(i)->posY - posY + 32) > -0.3f && (game->movingPlatforms.at(i)->posY - posY + 32) < 0.3f) {
				posX += game->movingPlatforms.at(i)->velX * game->deltaTime;
				velY = 0;
				onGround = true;

			}
		}
		// if out of bounds of moving platform and was on ground
		else {
			if (!onGround) {
				velY -= game->gravityRate;
			}
		}
	}
}
// check for collisions with enemies
bool Entity::isCollidingWithEnemies() {

	// for each enemy, check tile overlaps



	return false;
}


// update entity position based on velocity
void Entity::updatePosition() {
	// update for collisions with collectibles, update them
	checkUpdateCollectables();

	// calculate proposed new position
	newPosX = posX + (velX * game->deltaTime);
	newPosY = posY + (velY * game->deltaTime);  

	// check for collision with tilemap in x axis
	if (!isCollidingX() && !isCollidingWithMovingPlatform())
		posX = newPosX;

	// check for collision in with tilemap y axis
	if (!isCollidingY() && !isCollidingWithMovingPlatform())
		posY = newPosY;

	// deceleration on x axis
	velX = 0;

	trackMovingPlatforms();

	// apply gravity 
	if (!onGround)
		velY -= game->gravityRate;
}

// draws the entity
void Entity::draw() {
	updatePosition();				// updates the entity position, including collision detection
	
	// checks if all sprite frames are used up and resets the animation
	if (playerSpriteFrame > spriteSet[0].size())
		playerSpriteFrame = 0;

	// enable textures and bind the texture from [0] in spriteSet (running texture)
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteSet[0][(int)playerSpriteFrame]);

	// draw and texture the entity
	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex2f(posX, posY);

		glTexCoord2d(1.0, 1.0);
		glVertex2f(posX + game->tileWidth, posY);

		glTexCoord2d(1.0, 0.0);
		glVertex2f(posX + game->tileWidth, posY + game->tileHeight);

		glTexCoord2d(0.0, 0.0);
		glVertex2f(posX, posY + game->tileHeight);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);

	// debug mode - draw surrounding tiles
	if(game->debug) {
		calculateSurroundingTiles();	// calculates surrounding tiles

		// draw tile mapping 
		glBegin(GL_LINE_LOOP);
			glVertex2f(tileLeft * game->tileWidth, tileBottom * game->tileHeight);
			glVertex2f(tileLeft * game->tileWidth, tileBottom * game->tileHeight + game->tileHeight);
			glVertex2f(tileLeft * game->tileWidth + game->tileWidth, tileBottom * game->tileHeight + game->tileHeight);
			glVertex2f(tileLeft * game->tileWidth + game->tileWidth, tileBottom * game->tileHeight);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex2f(tileRight * game->tileWidth, tileBottom * game->tileHeight);
			glVertex2f(tileRight * game->tileWidth, tileBottom * game->tileHeight + game->tileHeight);
			glVertex2f(tileRight * game->tileWidth + game->tileWidth, tileBottom * game->tileHeight + game->tileHeight);
			glVertex2f(tileRight * game->tileWidth + game->tileWidth, tileBottom * game->tileHeight);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex2f(tileRight * game->tileWidth, tileTop * game->tileHeight);
			glVertex2f(tileRight * game->tileWidth, tileTop * game->tileHeight + game->tileHeight);
			glVertex2f(tileRight * game->tileWidth + game->tileWidth, tileTop * game->tileHeight + game->tileHeight);
			glVertex2f(tileRight * game->tileWidth + game->tileWidth, tileTop * game->tileHeight);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex2f(tileLeft * game->tileWidth, tileTop * game->tileHeight);
			glVertex2f(tileLeft * game->tileWidth, tileTop * game->tileHeight + game->tileHeight);
			glVertex2f(tileLeft * game->tileWidth + game->tileWidth, tileTop * game->tileHeight + game->tileHeight);
			glVertex2f(tileLeft * game->tileWidth + game->tileWidth, tileTop * game->tileHeight);
		glEnd();

		// draw collision circle
		glPointSize(10.0f);
		glBegin(GL_POINTS);
			glVertex2f(posX + game->halfTileW, posY + game->halfTileW);
		glEnd();

	}

}


// constructor
Enemy::Enemy(Game& gameObj, float x, float y) {
	posX = x;
	posY = y;
	game = &gameObj;
}

// calculates the cartesian coords of surrounding tiles
void Enemy::calculateSurroundingTiles() {
	tileLeft = (int)posX / game->tileWidth;
	tileRight = (int)(posX / game->tileWidth) + 1;
	tileTop = (int)(posY / game->tileHeight) + 1;
	tileBottom = (int)posY / game->tileHeight;
}

// check for collisions with tilemap on x axis
bool Enemy::isCollidingX() {
	// calculate x,y coords of surrounding tiles
	// assumes entities are no bigger than 1 standard tile width
	tileLeft = (int)newPosX / game->tileWidth;
	tileRight = (int)(newPosX / game->tileWidth) + 1;
	tileTop = (int)(posY / game->tileHeight) + 1;
	tileBottom = (int)posY / game->tileHeight;

	// get the actual tile values from tilemap
	char tileTL = game->getTile(game, tileLeft, tileTop);
	char tileTR = game->getTile(game, tileRight, tileTop);
	char tileBL = game->getTile(game, tileLeft, tileBottom);
	char tileBR = game->getTile(game, tileRight, tileBottom);

	// if any collisions detected, return true
	if (tileTL == '#' || tileTR == '#' || tileBL == '#' || tileBR == '#' ||
		tileTL == 'D' || tileTR == 'D' || tileBL == 'D' || tileBR == 'D') {
		
		// invert direction of movement flag
		if (movingPosX)
			movingPosX = false;
		else
			movingPosX = true;

		return true;
	}

	// if not colliding, return false
	return false;
}

// check for collisions with tilemap on y axis
bool Enemy::isCollidingY() {
	// calculate x,y coords of surrounding tiles
	// assumes entities are no bigger than 1 standard tile width
	tileLeft = (int)posX / game->tileWidth;
	tileRight = (int)(posX / game->tileWidth) + 1;
	tileTop = (int)(newPosY / game->tileHeight) + 1;
	tileBottom = (int)newPosY / game->tileHeight;

	// get the actual tile values from tilemap
	char tileTL = game->getTile(game, tileLeft, tileTop);
	char tileTR = game->getTile(game, tileRight, tileTop);
	char tileBL = game->getTile(game, tileLeft, tileBottom);
	char tileBR = game->getTile(game, tileRight, tileBottom);

	// ceiling collision, set y velocity to 0
	if (tileTL == '#' || tileTR == '#' || tileTL == 'D' || tileTR == 'D') {
		velY = 0;
		return true;
	}

	// ground collision, set jumping flag back to false
	if (tileBL == '#' || tileBR == '#' || tileBL == 'D' || tileBR == 'D') {
		onGround = true;
		return true;
	}

	// if not colliding, return false
	return false;
}

// update entity position based on velocity
void Enemy::updatePosition() {
	// add velocity to enemy
	if (movingPosX)
		velX = 0.2f;
	else
		velX = -0.2f;

	// calculate proposed new position
	newPosX = posX + (velX * game->deltaTime);
	newPosY = posY + (velY * game->deltaTime);

	// check for collision with tilemap in x axis
	if (!isCollidingX())
		posX = newPosX;

	// check for collision in with tilemap y axis
	if (!isCollidingY())
		posY = newPosY;

	// deceleration on x axis
	velX = 0;


	// apply gravity 
	if (!onGround)
		velY -= game->gravityRate;


}

// draws the entity
void Enemy::draw() {

	updatePosition();

	if (spriteFrame > spriteSet[0].size()) // cycle playerSpriteFrame animation back to start
		spriteFrame = 0;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteSet[0][(int)spriteFrame]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 1.0);
	glVertex2f(posX, posY);

	glTexCoord2d(1.0, 1.0);
	glVertex2f(posX + game->tileWidth, posY);

	glTexCoord2d(1.0, 0.0);
	glVertex2f(posX + game->tileWidth, posY + game->tileHeight);

	glTexCoord2d(0.0, 0.0);
	glVertex2f(posX, posY + game->tileHeight);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// debug mode - draw surrounding tiles
	if (game->debug) {
		calculateSurroundingTiles();	// calculates surrounding tiles

										// draw tile mapping 
		glBegin(GL_LINE_LOOP);
		glVertex2f(tileLeft * game->tileWidth, tileBottom * game->tileHeight);
		glVertex2f(tileLeft * game->tileWidth, tileBottom * game->tileHeight + game->tileHeight);
		glVertex2f(tileLeft * game->tileWidth + game->tileWidth, tileBottom * game->tileHeight + game->tileHeight);
		glVertex2f(tileLeft * game->tileWidth + game->tileWidth, tileBottom * game->tileHeight);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex2f(tileRight * game->tileWidth, tileBottom * game->tileHeight);
		glVertex2f(tileRight * game->tileWidth, tileBottom * game->tileHeight + game->tileHeight);
		glVertex2f(tileRight * game->tileWidth + game->tileWidth, tileBottom * game->tileHeight + game->tileHeight);
		glVertex2f(tileRight * game->tileWidth + game->tileWidth, tileBottom * game->tileHeight);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex2f(tileRight * game->tileWidth, tileTop * game->tileHeight);
		glVertex2f(tileRight * game->tileWidth, tileTop * game->tileHeight + game->tileHeight);
		glVertex2f(tileRight * game->tileWidth + game->tileWidth, tileTop * game->tileHeight + game->tileHeight);
		glVertex2f(tileRight * game->tileWidth + game->tileWidth, tileTop * game->tileHeight);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex2f(tileLeft * game->tileWidth, tileTop * game->tileHeight);
		glVertex2f(tileLeft * game->tileWidth, tileTop * game->tileHeight + game->tileHeight);
		glVertex2f(tileLeft * game->tileWidth + game->tileWidth, tileTop * game->tileHeight + game->tileHeight);
		glVertex2f(tileLeft * game->tileWidth + game->tileWidth, tileTop * game->tileHeight);
		glEnd();

		// draw collision circle
		glPointSize(10.0f);
		glBegin(GL_POINTS);
		glVertex2f(posX + game->halfTileW, posY + game->halfTileW);
		glEnd();

	}
}

