#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "move.h"

void move(struct Player *player) {
	srand(time(NULL)); //set random number seeds
	int diceFace = 1 + (rand() % 6); //roll the dice
	player->location += diceFace;
	if (player->location > 17) {
		player->location -= 18;
		player->money += 10000;
	}
}