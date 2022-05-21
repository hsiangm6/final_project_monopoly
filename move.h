#pragma once
typedef struct Player
{
	int money;
	char* name;
	int location;

} Player;

void move(Player*);
