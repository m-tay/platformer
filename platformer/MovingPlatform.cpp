#include "MovingPlatform.h"

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
	newPosX = posX + velX;
	newPosY = posY + velY;

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

