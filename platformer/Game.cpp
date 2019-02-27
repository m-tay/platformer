#include "Game.h"

// gets tile character at (x,y) coordinate
char Game::getTile(Game *game, int x, int y) {
	if (x >= 0 && x < game->levelWidth && y >= 0 && y < game->levelHeight) {
		return game->levelMap[y * game->levelWidth + x];
	}
	else {
		return '-';
	}
}