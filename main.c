#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "event.h"

char *landmark[] = {"      ", "      ", "  ", "  ", "  ", 

					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",

					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",

					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",

					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",
					
					"      ", "      ", "  ", "  ", "  ",
				    
                    "                                     ",
					
					"******** ******** ******** ******** ******** ********", "********                                     ********" };



void printLand();
void printPlayerLocation(int p1Location, int p2Location);
void buildingStructure(Building *b);
void endGame(struct Player *p1, struct Player *p2,  struct Building *b);
void move(struct Player *player);

int main()
{
	char nameOfPlayer1[101], nameOfPlayer2[101];
	char game_switch = 'y';
	puts("Please enter the name of player 1: ");
    fgets(nameOfPlayer1,100,stdin);
    puts("Please enter the name of player 2: ");
	fgets(nameOfPlayer2,100,stdin);
	
	Player p1 =
	{
		.money = 10000,
		.name = nameOfPlayer1,
		.location = 0,
		.gameStatus = 0,
		.player_number = 1
	};
	
	Player p2 =
	{
		.money = 10000,
		.name = nameOfPlayer2,
		.location = 0,
		.gameStatus = 0,
		.player_number = 2
	};
	
	Building b[18] = 
    	{
		{0, -1},
		{0, -1, 1000},
		{0, -1},
		{0, -1, 1400},
		{0, -1, 1800},
		{0, -1},
		{0, -1, 2200},
		{0, -1, 2600},
		{0, -1, 3000},
		{0, -1},
		{0, -1, 3400},
		{0, -1},
		{0, -1, 3800},
		{0, -1, 4200},
		{0, -1},
		{0, -1, 4600},
		{0, -1, 5000},
		{0, -1, 5400},
   	};
	
	printPlayerLocation(p1.location, p2.location);
	printLand();
	printf("Player1 %s now have %d money.\n", p1.name, p1.money);
	printf("Player2 %s now have %d money.\n", p2.name, p2.money);
	//Sleep(3000);
	
	//game start
	puts("Whether open the next round? (Enter y to continue, n to end the game.)");
	fgets(&game_switch, 2, stdin);
	while (game_switch == 'y') {
		
		if (p1.gameStatus >= 0) {
			move(&p1);
			printPlayerLocation(p1.location, p2.location);
			printLand();
			event(&p1, &b[p1.location]);
			printPlayerLocation(p1.location, p2.location);
			printLand();
		}
		else {
			continue;
		}
		if (p2.gameStatus >= 0) {
			move(&p2);
			printPlayerLocation(p1.location, p2.location);
			printLand();
			event(&p2, &b[p2.location]);
			printPlayerLocation(p1.location, p2.location);
			printLand();
		}
		else {
			continue;
		}
		puts("Whether open the next round? (Enter y to continue, n to end the game.)");
		fgets(&game_switch, 2, stdin);

	}
}

void printLand()
{
	//system("CLS");
	puts("---------------");
	printf("%s\n*%s* *%s* *%s* *%s* *%s* *%s*\n*%s* *%s* *%s* *%s* *%s* *%s*\n*%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s*\n%s\n",

        	landmark[91],
		landmark[0], landmark[5], landmark[10], landmark[15], landmark[20], landmark[25],
        	landmark[1], landmark[6], landmark[11], landmark[16], landmark[21], landmark[26],
        	landmark[2], landmark[3], landmark[4], landmark[7], landmark[8], landmark[9], landmark[12], landmark[13], landmark[14], landmark[17], landmark[18], landmark[19], landmark[22], landmark[23], landmark[24], landmark[27], landmark[28], landmark[29],
		landmark[91]);

   	printf("%s\n*%s*%s*%s*\n*%s*%s*%s*\n*%s%s%s*%s*%s%s%s*\n%s\n", landmark[92], landmark[85], landmark[90], landmark[30], landmark[86], landmark[90], landmark[31], landmark[87], landmark[88], landmark[89], landmark[90], landmark[32], landmark[33], landmark[34], landmark[92]);
    	printf("%s\n*%s*%s*%s*\n*%s*%s*%s*\n*%s%s%s*%s*%s%s%s*\n%s\n", landmark[92], landmark[80], landmark[90], landmark[35], landmark[81], landmark[90], landmark[36], landmark[82], landmark[83], landmark[84], landmark[90], landmark[37], landmark[38], landmark[39], landmark[92]);
    	printf("%s\n*%s*%s*%s*\n*%s*%s*%s*\n*%s%s%s*%s*%s%s%s*\n%s\n", landmark[92], landmark[75], landmark[90], landmark[40], landmark[76], landmark[90], landmark[41], landmark[77], landmark[78], landmark[79], landmark[90], landmark[42], landmark[43], landmark[44], landmark[92]);

    	printf("%s\n*%s* *%s* *%s* *%s* *%s* *%s*\n*%s* *%s* *%s* *%s* *%s* *%s*\n*%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s*\n%s\n",

        	landmark[91],
		landmark[70], landmark[65], landmark[60], landmark[55], landmark[50], landmark[45],
        	landmark[71], landmark[66], landmark[61], landmark[56], landmark[51], landmark[46],
        	landmark[72], landmark[73], landmark[74], landmark[67], landmark[68], landmark[69], landmark[62], landmark[63], landmark[64], landmark[57], landmark[58], landmark[59], landmark[52], landmark[53], landmark[54], landmark[47], landmark[48], landmark[49],
		landmark[91]);
}

void printPlayerLocation(int p1Location, int p2Location)
{
	int i;
	for(i=2; i<=87; i+=5)
		landmark[i] = "  ";
	for(i=4; i<=89; i+=5)
		landmark[i] = "  ";
	
	landmark[p1Location * 5 + 2] = " 1";
	landmark[p2Location * 5 + 4] = "2 ";
}

void buildingStructure(Building *b)
{
	b -> buildPrice = 0.5 * b -> buyPrice;
	b -> finalPrice = 1.5 * b -> buyPrice + (1.5 * b -> buildPrice) * b -> condition;
	b -> fee = 0.5 * b -> finalPrice;
	b -> buyPriceFromTheOpponent = 2 * b -> finalPrice;
}

void endGame(struct Player *p1, struct Player *p2,  struct Building *b){
    int i, counter=0, player1Count=0, player2Count=0;
    for (i=0; i<18; i++){
        if (b[i].owner == 1) {
            player1Count += (1.5 * b[i].buyPrice + (1.5 * b[i].buildPrice) * b[i].condition);
        }
        else if (b[i].owner == 2){
            player2Count += (1.5 * b[i].buyPrice + (1.5 * b[i].buildPrice) * b[i].condition);
        }
    }
    if (player1Count > player2Count){
        printf ("Congradulate!! Player %s wins the game.\n", p1->name);
        printf ("Toltal asset: %s: %d, %s: %d", p1->name, player1Count, p2->name, player2Count);
    }
    else if (player1Count < player2Count){
        printf ("Congradulate!! Player %s wins the game.", p2->name);
        printf ("Toltal asset: %s: %d, %s: %d", p1->name, player1Count, p2->name, player2Count);
    }
    else if (player1Count == player2Count){
        puts ("There is no winner in the game!");
    }
}

void move(struct Player *player) {
	srand(time(NULL)); //set random number seeds
	int diceFace = 1 + (rand() % 6); //roll the dice
	printf("Your dice roll is %d.\n", diceFace);
	player->location += diceFace;

	if (player->location > 17) { //pass the start point
		player->location -= 18;
		player->money += 10000;
	}
}