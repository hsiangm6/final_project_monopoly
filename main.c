#include <stdio.h>
#include <stdlib.h>
#include "move.h"
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

typedef struct Player
{
	int money;
	char *name;
	int location;
	int gameStatus;
} Player;

typedef struct Building
{
	int buyPrice; // The price of occupying this place with a flag.
	int buildPrice = 0.8 * buyPrice; // The price of building this flag to the structure.
	int finalPrice = 1.5 * buyPrice + (1.5 * buildPrice) * condition ; // The eventual price of this land.
	int fee = 0.5 * finalPrice // The fee that the opponent being through be supposed to pay. 
	int buyPriceFromTheOpponent = 2 * finalPrice; // The price of this land buying from the opponent.
	int condition; // The current status of the land, 0 is a flag, while 1 is structure.
	int owner; // The land is occupied by whom.
	
} Building;

void printLand();
void printPlayerLocation(int p1Location, int p2Location);

int main()
{
	char nameOfPlayer1[100], nameOfPlayer2[100];
	int game_mode = 1;
	char game_switch = "y";
	printf("Please enter the name of player 1: ");
    	scanf("%s", nameOfPlayer1);
    	printf("Please enter the name of player 2: ");
	scanf("%s", nameOfPlayer2);
	
	Player p1 =
    	{
    		.money = 10000,
    		.name = nameOfPlayer1,
    		.location = 0
	};
	
	Player p2 = 
	{
		.money = 10000,
		.name = nameOfPlayer2,
		.location = 0
	};
	
	printPlayerLocation(p1.location, p2.location);
	printLand();
	printf("Player1 %s now have %d money.\n", p1.name, p1.money);
	printf("Player2 %s now have %d money.\n", p2.name, p2.money);
	printf("Whether to open the round?(print y=yes, n=no and end the game)");
	while (scanf_c("%c\n", game_switch, 1) == "y") {
		move(&p1);
		printPlayerLocation(p1.location, p2.location);
		printLand();
		event(&p1);
		printPlayerLocation(p1.location, p2.location);
		printLand();
		move(&p2);
		printPlayerLocation(p1.location, p2.location);
		printLand();
		event(&p2);
		printPlayerLocation(p1.location, p2.location);
		printLand();

	}
}

void printLand()
{
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
		landmark[i] == "  ";
	for(i=3; i<=88; i+=5)
		landmark[i] == "  ";
	
	landmark[p1Location * 5 + 2] = " 1";
	landmark[p2Location * 5 + 4] = "2 ";
}
