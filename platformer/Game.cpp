#include "Game.h"
#include "Entities.h"
#include <sstream>


// gets tile character at (x,y) coordinate
char Game::getTile(Game *game, int x, int y) {
	if (x >= 0 && x < game->levelWidth && y >= 0 && y < game->levelHeight) {
		return game->levelMap[y * game->levelWidth + x];
	}
	else {
		return '-';
	}
}

// empties tile character at (x,y) coordinate
void Game::emptyTile(Game *game, int x, int y) {
	if (x >= 0 && x < game->levelWidth && y >= 0 && y < game->levelHeight) {
		game->levelMap[y * game->levelWidth + x] = '-';
	}
}

// draws the player score
void Game::drawScore(Game* game) {
	std::stringstream sstr;
	std::string outputString;

	// set to projection mode to draw as a HUD
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();		// save matrix
		glLoadIdentity();	// reset matrix
		glOrtho(0, game->screenWidth, game->screenHeight, 0, 0, -1); // ortho transform to width/height of screen
		glMatrixMode(GL_MODELVIEW);  // set back to modelview
		glPushMatrix();
			glLoadIdentity();

			glDisable(GL_LIGHTING);
			glColor3f(0.1f, 0.1f, 0.1f);
			
			// text rendering code
			glRasterPos2i(20, 20);
			sstr << "Score : " << game->playerScore; // create string stream to print out
			outputString = sstr.str();

			//glDisable(GL_LIGHTING);
			glColor3f(1.0f, 1.0f, 1.0f);

			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)outputString.c_str());
			sstr.str(std::string()); // clears string stream
			

			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Game::activateGhosts(Game* game) {
	// loop through all ghosts
	for(int i = 0; i < game->ghosts.size(); i++) {
		// set them to active
		game->ghosts[i]->active = true;
	}
}

void Game::deactivateGhosts(Game* game) {
	// loop through all ghosts
	for (int i = 0; i < game->ghosts.size(); i++) {
		// set them to active
		game->ghosts[i]->active = false;
	}
}
