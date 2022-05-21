#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<event.h>

void move(int location, int money) {
	srand(time(NULL)); //set random number seeds
	int diceFace = 1 + (rand() % 6); //roll the dice
	location += diceFace;
	if (location == 0) {
		money += 10000;
	}
}