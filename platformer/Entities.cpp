#include "Entities.h"
#include <iostream>

MovingPlatform::MovingPlatform(Game& gameObj, float x, float y) {
	posX = x;
	posY = y;
	game = &gameObj;
	platformWidth = tilesWide * game->tileWidth; // how many tiles wide the platform is
}

MovingPlatform::MovingPlatform(Game& gameObj, float x, float y, bool isLift) {
	posX = x;
	posY = y;
	game = &gameObj;
	platformWidth = tilesWide * game->tileWidth; // how many tiles wide the platform is
	lift = isLift;	// set platform to be a lift
	movingPosX = false;
	movingPosY = true;
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
		tileTL == 'D' || tileTR == 'D' || tileBL == 'D' || tileBR == 'D' ||
		tileTL == 'M' || tileTR == 'M' || tileBL == 'M' || tileBR == 'M') {

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
	int tileRight = (int)(posX / game->tileWidth) + tilesWide;
	int tileTop = (int)(newPosY / game->tileHeight) + 1;
	int tileBottom = (int)newPosY / game->tileHeight;

	// get the actual tile values from tilemap
	char tileTL = game->getTile(game, tileLeft, tileTop);
	char tileTR = game->getTile(game, tileRight, tileTop);
	char tileBL = game->getTile(game, tileLeft, tileBottom);
	char tileBR = game->getTile(game, tileRight, tileBottom);

	// if any collisions detected...
	if (tileTL == '#' || tileTR == '#' || tileBL == '#' || tileBR == '#' ||
		tileTL == 'D' || tileTR == 'D' || tileBL == 'D' || tileBR == 'D' ||
		tileTL == 'M' || tileTR == 'M' || tileBL == 'M' || tileBR == 'M') {

		// invert direction of movement flag
		if (movingPosY)
			movingPosY = false;
		else
			movingPosY = true;

		return true;
	}

	// if not colliding, return false
	return false;
}

// update entity position based on velocity
void MovingPlatform::updatePosition() {
	// add velocity to platform
	if (!lift) {
		if (movingPosX)
			velX = 0.2f;
		else
			velX = -0.2f;
	}

	if (lift) {
		if (movingPosY)
			velY = 0.2f;
		else
			velY = -0.2f;
	}

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
void Entity::checkSpecialTiles() {
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

	// hitting water
	if (tileTL == 'W') {
		velY = 1.5f;		// add a big jump before falling off screen dead
		onGround = false;	// set onGround flag so gravity applies
		alive = false;
	}

	if (tileTR == 'W') {
		velY = 1.5f;		// add a big jump before falling off screen dead
		onGround = false;	// set onGround flag so gravity applies
		alive = false;
	}

	if (tileBL == 'W') {
		velY = 1.5f;		// add a big jump before falling off screen dead
		onGround = false;	// set onGround flag so gravity applies
		alive = false;
	}

	if (tileBR == 'W') {
		velY = 1.5f;		// add a big jump before falling off screen dead
		onGround = false;	// set onGround flag so gravity applies
		alive = false;
	}


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

	if (tileTL == 'G') {
		game->playerScore += 10;	// update score
		game->emptyTile(game, tileLeft, tileTop);
		game->gemCollected = true;
		game->activateGhosts(game);
	}

	if (tileTR == 'G') {
		game->playerScore += 10;	// update score
		game->emptyTile(game, tileRight, tileTop);
		game->gemCollected = true;
		game->activateGhosts(game);
	}

	if (tileBL == 'G') {
		game->playerScore += 10;	// update score
		game->emptyTile(game, tileLeft, tileBottom);
		game->gemCollected = true;
		game->activateGhosts(game);
	}

	if (tileBR == 'G') {
		game->playerScore += 10;	// update score
		game->emptyTile(game, tileRight, tileBottom);
		game->gemCollected = true;
		game->activateGhosts(game);
	}

	// if gem is collected, check for level exit collision
	if (game->gemCollected) {

		// check tile collision with door
		if (tileTL == 'd' || tileTR == 'd' || tileBL == 'd' || tileBR == 'd') {

			// check if player is on final level
			if (game->onLevel == game->maxLevels)
				game->gameStage = "theend";
			else 
				game->gameStage = "levelcomplete";
		}
	}
}

// checks if player is on ground and updates status (needed if player walks off edge)
bool Entity::isOnGround() {
	// calculate x,y coords of surrounding tiles
	// assumes entities are no bigger than 1 standard tile width
	tileLeft = (int)newPosX / game->tileWidth;
	tileRight = (int)(newPosX / game->tileWidth) + 1;
	tileBottom = (int)posY / game->tileHeight;

	// get the actual tile values from tilemap
	char tileBL = game->getTile(game, tileLeft, tileBottom);
	char tileBR = game->getTile(game, tileRight, tileBottom);

	if (tileBL != '#' && tileBR != '#')
		return false;

	return true;
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
			newPosY + game->tileHeight >= game->movingPlatforms.at(i)->posY								&&
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
		if ((posX + game->halfTileW) >= game->movingPlatforms.at(i)->posX && (posX + game->halfTileW) < (game->movingPlatforms.at(i)->posX + game->movingPlatforms.at(i)->platformWidth)) {

			// check if close enough to surface of moving platform to track movement
			if ((game->movingPlatforms.at(i)->posY - posY + 32) > -0.6f && (game->movingPlatforms.at(i)->posY - posY + 32) < 0.6f) {
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
// check for collisions with enemies - uses circle to circle collision detection for performance
// purposes, there are lots of collisions to make. This will just be used for tile-sized enemies, 
// as bounding circles are excellent approximations for the sprites used
bool Entity::isCollidingWithEnemies() {

	// offset x,y pos by half tile widths to calc bounding circle
	float entityX = posX + game->halfTileW;
	float entityY = posY + game->halfTileH;

	// for each enemy
	for(int i = 0; i < game->enemies.size(); i++) {

		// offset x,y pos by half tile widths to calc bounding circle
		float enemyX = game->enemies.at(i)->posX + game->halfTileW;
		float enemyY = game->enemies.at(i)->posY + game->halfTileH;

		// debug mode - draw collision detection distance
		if(game->debug) {
			glBegin(GL_LINES);
				glVertex2f(entityX, entityY);
				glVertex2f(enemyX, enemyY);
			glEnd();
		}

		// calculate distance between circles
		float distX = entityX - enemyX;
		float distY = entityY - enemyY;
		float dist = sqrt((distX * distX) + (distY * distY));

		// collision detection - check if distance between circles is less than sum of radius (tile width)
		if (dist <= game->tileWidth) {	// technically it is halfTileW + halfTileW but this just takes a calc out
			velY = 1.5f;				// add a big jump before falling off screen dead
			onGround = false;			// set onGround flag so gravity applies
			return true;				// collision detected
		}
	}

	// check if ghosts are active (when gem is collected)
	if (game->gemCollected)
	{
		// for each ghost
		for (int i = 0; i < game->ghosts.size(); i++) {

			// offset x,y pos by half tile widths to calc bounding circle
			float enemyX = game->ghosts.at(i)->posX + game->halfTileW;
			float enemyY = game->ghosts.at(i)->posY + game->halfTileH;

			// debug mode - draw collision detection distance
			if (game->debug) {
				glBegin(GL_LINES);
				glVertex2f(entityX, entityY);
				glVertex2f(enemyX, enemyY);
				glEnd();
			}

			// calculate distance between circles
			float distX = entityX - enemyX;
			float distY = entityY - enemyY;
			float dist = sqrt((distX * distX) + (distY * distY));

			// collision detection - check if distance between circles is less than sum of radius (tile width)
			if (dist <= game->tileWidth) {	// technically it is halfTileW + halfTileW but this just takes a calc out
				velY = 1.5f;				// add a big jump before falling off screen dead
				onGround = false;			// set onGround flag so gravity applies
				return true;				// collision detected
			}
		}
	}

	// if no collisions detected for any enemy, return false
	return false;
}


// update entity position based on velocity
void Entity::updatePosition() {

	// check for on-ground-ness
	if (isOnGround())
		onGround = true;
	else
		onGround = false;

	// calculate proposed new position
	newPosX = posX + (velX * game->deltaTime);
	newPosY = posY + (velY * game->deltaTime);

	// update playing facing position (does not matter if blocked)
	if (velX > 0) {
		facing = 'r';
		idle = false;
	}
	if (velX < 0) {
		facing = 'l';
		idle = false;
	}

	if (velX == 0)
		idle = true;

	// perform collision detection if player is alive
	if (alive) {

		if (!isCollidingWithMovingPlatform()) {
			// check for collision with tilemap in x axis
			if (!isCollidingX())
				posX = newPosX;

			// check for collision in with tilemap y axis
			if (!isCollidingY())
				posY = newPosY;
		}

		// check for collisions with enemies
		if (isCollidingWithEnemies()) {
			alive = false;
		}

		// deceleration on x axis
		velX = 0;

		// also update position on moving platforms
		trackMovingPlatforms();

		// update for collisions with collectibles, update them
		checkSpecialTiles();
	}
	// if player is not alive
	else { 
		// update player position with no collision detection
		posX = newPosX;
		posY = newPosY;

		// check if player death animation should trigger game over screen
		if (posY < -1000)
			game->gameStage = "gameover";
	}

	// apply gravity 
	if (!onGround) {
		velY -= (game->gravityRate * game->deltaTime);

		// set terminal velocity (cap falling speed)
		if (velY < -0.7f)
			velY = -0.7f;

	}
}

// draws the entity
void Entity::draw() {
	updatePosition();				// updates the entity position, including collision detection
	
	// checks if all sprite frames are used up and resets the animation
	if (playerSpriteFrame > spriteSet[0].size())
		playerSpriteFrame = 0;

	// enable textures and bind the texture from [0] in spriteSet (running texture)
	glEnable(GL_TEXTURE_2D);

	// set running or idle texture set based on player's x velocity
	if(idle) {
		if ((int)playerSpriteFrame > (spriteSet[1].size() - 1))
			playerSpriteFrame = 0;

		// player = moving, set "running" texture
		glBindTexture(GL_TEXTURE_2D, spriteSet[1][(int)playerSpriteFrame]);
	}
	else {
		if ((int)playerSpriteFrame > spriteSet[0].size())
			playerSpriteFrame = 0;

		// player = still, set "idle" texture
		glBindTexture(GL_TEXTURE_2D, spriteSet[0][(int)playerSpriteFrame]);
	}

	// draw and texture the entity
	glBegin(GL_QUADS);
		if(facing == 'r')
			glTexCoord2d(0.0, 1.0);
		else
			glTexCoord2d(1.0, 1.0);
		glVertex2f(posX, posY);

		if(facing == 'r')
			glTexCoord2d(1.0, 1.0);
		else
			glTexCoord2d(0.0, 1.0);
		glVertex2f(posX + game->tileWidth, posY);

		if (facing == 'r')
			glTexCoord2d(1.0, 0.0);
		else
			glTexCoord2d(0.0, 0.0);
		glVertex2f(posX + game->tileWidth, posY + game->tileHeight);

		if (facing == 'r')
			glTexCoord2d(0.0, 0.0);
		else
			glTexCoord2d(1.0, 0.0);
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
		// shift x,y by half a tile, because entity position is stored from bottom left
		game->drawCircle(posX + game->halfTileW, posY + game->halfTileW, game->halfTileW);

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

// check for collisions with enemies - uses circle to circle collision detection for performance
// purposes, there are lots of collisions to make. This will just be used for tile-sized enemies, 
// as bounding circles are excellent approximations for the sprites used
bool Enemy::isCollidingWithProjectile() {

	// offset x,y pos by half tile widths to calc bounding circle
	float entityX = posX + game->halfTileW;
	float entityY = posY + game->halfTileH;

	// for each enemy
	for (int i = 0; i < game->projectiles.size(); i++) {

		// offset x,y pos by half tile widths to calc bounding circle
		float enemyX = game->projectiles.at(i).posX + game->halfTileW;
		float enemyY = game->projectiles.at(i).posY + game->halfTileH;

		// debug mode - draw collision detection distance
		if (game->debug) {
			glBegin(GL_LINES);
			glVertex2f(entityX, entityY);
			glVertex2f(enemyX, enemyY);
			glEnd();
		}

		// calculate distance between circles
		float distX = entityX - enemyX;
		float distY = entityY - enemyY;
		float dist = sqrt((distX * distX) + (distY * distY));

		// collision detection - check if distance between circles is less than sum of radius (tile width)
		if (dist <= game->tileWidth) {	// technically it is halfTileW + halfTileW but this just takes a calc out
			velY = 1.5f;				// add a big jump before falling off screen dead
			return true;				// collision detected
		}
	}

	// if no collisions detected for any enemy, return false
	return false;
}

// update entity position based on velocity
void Enemy::updatePosition() {
	// add velocity to enemy
	if (movingPosX)
		velX = 0.05f;
	else
		velX = -0.05f;

	// calculate proposed new position
	newPosX = posX + (velX * game->deltaTime);
	newPosY = posY + (velY * game->deltaTime);

	// update enemy facing position (does not matter if blocked)
	if (velX > 0)
		facing = 'r';

	if (velX < 0)
		facing = 'l';

	// check for collision with tilemap in x axis
	if (!isCollidingX())
		posX = newPosX;

	// check for collision in with tilemap y axis
	if (!isCollidingY())
		posY = newPosY;

	// deceleration on x axis
	velX = 0;


	// apply gravity 
	//if (!onGround)
	//	velY -= game->gravityRate;


}

// draws the entity
void Enemy::draw() {

	updatePosition();

	// check if being hit by bullet
	if(isCollidingWithProjectile()) {
		alive = false;	// set alive status to false
	}

	if (spriteFrame > spriteSet[0].size()) // cycle playerSpriteFrame animation back to start
		spriteFrame = 0;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteSet[0][(int)spriteFrame]);

	// draw and texture the entity
	glBegin(GL_QUADS);
	if (facing == 'r')
		glTexCoord2d(0.0, 1.0);
	else
		glTexCoord2d(1.0, 1.0);
	glVertex2f(posX, posY);

	if (facing == 'r')
		glTexCoord2d(1.0, 1.0);
	else
		glTexCoord2d(0.0, 1.0);
	glVertex2f(posX + game->tileWidth, posY);

	if (facing == 'r')
		glTexCoord2d(1.0, 0.0);
	else
		glTexCoord2d(0.0, 0.0);
	glVertex2f(posX + game->tileWidth, posY + game->tileHeight);

	if (facing == 'r')
		glTexCoord2d(0.0, 0.0);
	else
		glTexCoord2d(1.0, 0.0);
	glVertex2f(posX, posY + game->tileHeight);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// debug mode - draw surrounding tiles
	if (game->debug) {
		calculateSurroundingTiles();	// calculates surrounding tiles

		// draw detected surrounding tiles
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
		// shift x,y by half a tile, because entity position is stored from bottom left
		game->drawCircle(posX + game->halfTileW, posY + game->halfTileW, game->halfTileW);

	}
}

// constructor
Projectile::Projectile(Game& gameObj, float x, float y, char dir) {
	posX = x;
	posY = y;
	game = &gameObj;
	direction = dir;
	spriteSet.push_back(game->bulletSprite);
	velX = 0;
	velY = 0;
}

// calculates the cartesian coords of surrounding tiles
void Projectile::calculateSurroundingTiles() {
	tileLeft = (int)posX / game->tileWidth;
	tileRight = (int)(posX / game->tileWidth) + 1;
	tileTop = (int)(posY / game->tileHeight) + 1;
	tileBottom = (int)posY / game->tileHeight;
}

// check for collisions with tilemap on x axis
bool Projectile::isCollidingX() {
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


// check for collisions with enemies - uses circle to circle collision detection for performance
// purposes, there are lots of collisions to make. This will just be used for tile-sized enemies, 
// as bounding circles are excellent approximations for the sprites used
bool Projectile::isCollidingWithEnemies() {

	// offset x,y pos by half tile widths to calc bounding circle
	float entityX = posX + game->halfTileW;
	float entityY = posY + game->halfTileH;

	// for each enemy
	for (int i = 0; i < game->enemies.size(); i++) {

		// offset x,y pos by half tile widths to calc bounding circle
		float enemyX = game->enemies.at(i)->posX + game->halfTileW;
		float enemyY = game->enemies.at(i)->posY + game->halfTileH;

		// debug mode - draw collision detection distance
		if (game->debug) {
			glBegin(GL_LINES);
			glVertex2f(entityX, entityY);
			glVertex2f(enemyX, enemyY);
			glEnd();
		}

		// calculate distance between circles
		float distX = entityX - enemyX;
		float distY = entityY - enemyY;
		float dist = sqrt((distX * distX) + (distY * distY));

		// collision detection - check if distance between circles is less than sum of radius (tile width)
		if (dist <= game->tileWidth) {	// technically it is halfTileW + halfTileW but this just takes a calc out
			velY = 1.5f;				// add a big jump before falling off screen dead
			return true;				// collision detected
		}
	}

	// if no collisions detected for any enemy, return false
	return false;
}


// update entity position based on velocity
void Projectile::updatePosition() {

	// calculate proposed new position
	newPosX = posX + (velX * game->deltaTime);
	newPosY = posY + (velY * game->deltaTime);

	posX = newPosX;
	posY = newPosY;

	// check for collision with tilemap in x axis (hitting a wall)
	if (isCollidingX())
		active = false; // set to inactive, so it can be destroyed in main thread


	// check for collisions with enemies
	if (isCollidingWithEnemies()) {
		game->playerScore += 3;	// increase score for killing enemy
		active = false;			// set to inactive, so it can be destroyed in main thread
	}

	// deceleration on x axis
	velX = 0;
}

// draws the entity
void Projectile::draw() {
	if (active) {
		if (direction == 'r')
			velX = 0.65f;
		if (direction == 'l')
			velX = -0.655f;

		// updates the entity position, including collision detection
		updatePosition();

		// enable textures and bind the texture from [0] in spriteSet (running texture)
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, spriteSet[0][0]);

		// draw and texture the entity
		glBegin(GL_QUADS);
		glTexCoord2d(1.0, 1.0);
		glVertex2f(posX, posY);

		glTexCoord2d(0.0, 1.0);
		glVertex2f(posX + game->tileWidth, posY);

		glTexCoord2d(0.0, 0.0);
		glVertex2f(posX + game->tileWidth, posY + game->tileHeight);

		glTexCoord2d(1.0, 0.0);
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
			// shift x,y by half a tile, because entity position is stored from bottom left
			game->drawCircle(posX + game->halfTileW, posY + game->halfTileW, game->halfTileW);

		}
	}
}

// constructor
Ghost::Ghost(Game& gameObj, Entity& player, float x, float y) {
	posX = x;
	posY = y;
	game = &gameObj;
	playerEntity = &player;
}


// update entity position based on velocity
void Ghost::updatePosition() {

	// track the player and move towards it
	if (posX < playerEntity->posX)
		velX = ghostSpeed;

	if (posX > playerEntity->posX)
		velX = -ghostSpeed;

	if (posY < playerEntity->posY)
		velY = ghostSpeed;

	if (posY > playerEntity->posY)
		velY = -ghostSpeed;

	// calculate proposed new position
	newPosX = posX + (velX * game->deltaTime);
	newPosY = posY + (velY * game->deltaTime);

	// update enemy facing position (does not matter if blocked)
	if (velX > 0)
		facing = 'r';

	if (velX < 0)
		facing = 'l';

	// update position
	posX = newPosX;
	posY = newPosY;
}

// draws the entity
void Ghost::draw() {

	// only draw if active
	if (active) {

		updatePosition();

		if (spriteFrame > spriteSet[0].size()) // cycle playerSpriteFrame animation back to start
			spriteFrame = 0;

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, spriteSet[0][(int)spriteFrame]);

		// draw and texture the entity
		glBegin(GL_QUADS);
		if (facing == 'r')
			glTexCoord2d(0.0, 1.0);
		else
			glTexCoord2d(1.0, 1.0);
		glVertex2f(posX, posY);

		if (facing == 'r')
			glTexCoord2d(1.0, 1.0);
		else
			glTexCoord2d(0.0, 1.0);
		glVertex2f(posX + game->tileWidth, posY);

		if (facing == 'r')
			glTexCoord2d(1.0, 0.0);
		else
			glTexCoord2d(0.0, 0.0);
		glVertex2f(posX + game->tileWidth, posY + game->tileHeight);

		if (facing == 'r')
			glTexCoord2d(0.0, 0.0);
		else
			glTexCoord2d(1.0, 0.0);
		glVertex2f(posX, posY + game->tileHeight);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		// debug mode - draw surrounding tiles
		if (game->debug) {

			// draw detected surrounding tiles
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
			// shift x,y by half a tile, because entity position is stored from bottom left
			game->drawCircle(posX + game->halfTileW, posY + game->halfTileW, game->halfTileW);

		}
	}
}