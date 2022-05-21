#include <stdio.h>
#include <stdlib.h>

typedef struct Player
{
	int money;
	char *name;
	int location;
	
} Player;

char *landmark[] = {"      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ",

                    "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ",

                    "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ",

                    "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ",

                    "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ",

                    "      ", "      ", "      ", "      ", "                                          ", "                                        ",
					
					" ————  ————  ————  ————  ————  ————", " ————                                          ————" };

void printLand();
void printPlayerLocation(int p1Location, int p2Location);

int main()
{
	char nameOfPlayer1[100], nameOfPlayer2[100];
	printf("Please enter the name of player 1: ");
    scanf_s("%s", nameOfPlayer1,99);
    printf("Please enter the name of player 2: ");
    scanf_s("%s", nameOfPlayer2,99);
	
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
}

void printLand()
{
    printf("%s\n｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜\n｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜\n｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜\n%s\n",

        landmark[56],
		landmark[0], landmark[3], landmark[6], landmark[9], landmark[12], landmark[15],
        landmark[1], landmark[4], landmark[7], landmark[10], landmark[13], landmark[16],
        landmark[2], landmark[5], landmark[8], landmark[11], landmark[14], landmark[17],
		landmark[56]);

    printf("%s\n｜%s｜%s｜%s｜\n｜%s｜%s｜%s｜\n｜%s｜%s｜%s｜\n%s\n", landmark[57], landmark[18], landmark[55], landmark[21], landmark[19], landmark[55], landmark[22], landmark[20], landmark[55], landmark[23], landmark[57]);
    printf("%s\n｜%s｜%s｜%s｜\n｜%s｜%s｜%s｜\n｜%s｜%s｜%s｜\n%s\n", landmark[57], landmark[24], landmark[55], landmark[27], landmark[25], landmark[55], landmark[28], landmark[26], landmark[55], landmark[29], landmark[57]);
    printf("%s\n｜%s｜%s｜%s｜\n｜%s｜%s｜%s｜\n｜%s｜%s｜%s｜\n%s\n", landmark[57], landmark[30], landmark[55], landmark[33], landmark[31], landmark[55], landmark[34], landmark[32], landmark[55], landmark[35], landmark[57]);

    printf("%s\n｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜\n｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜\n｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜｜%s｜\n%s\n",

        landmark[56],
		landmark[36], landmark[39], landmark[42], landmark[45], landmark[48], landmark[51],
        landmark[37], landmark[40], landmark[43], landmark[46], landmark[49], landmark[52],
        landmark[38], landmark[41], landmark[44], landmark[47], landmark[50], landmark[53],
		landmark[56]);
}

void printPlayerLocation(int p1Location, int p2Location)
{
	if(p1Location == 0 && p2Location != 0)
		landmark[53] = " 1    ";
	else if(p1Location == 1 && p2Location != 1)
		landmark[50] = " 1    ";
	else if(p1Location == 2 && p2Location != 2)
		landmark[47] = " 1    ";
	else if(p1Location == 3 && p2Location != 3)
		landmark[44] = " 1    ";
	else if(p1Location == 4 && p2Location != 4)
		landmark[41] = " 1    ";
	else if(p1Location == 5 && p2Location != 5)
		landmark[38] = " 1    ";
	else if(p1Location == 6 && p2Location != 6)
		landmark[32] = " 1    ";
	else if(p1Location == 7 && p2Location != 7)
		landmark[26] = " 1    ";
	else if(p1Location == 8 && p2Location != 8)
		landmark[20] = " 1    ";
	else if(p1Location == 9 && p2Location != 9)
		landmark[2] = " 1    ";
	else if(p1Location == 10 && p2Location != 10)
		landmark[5] = " 1    ";
	else if(p1Location == 11 && p2Location != 11)
		landmark[8] = " 1    ";
	else if(p1Location == 12 && p2Location != 12)
		landmark[11] = " 1    ";
	else if(p1Location == 13 && p2Location != 13)
		landmark[14] = " 1    ";
	else if(p1Location == 14 && p2Location != 14)
		landmark[17] = " 1    ";
	else if(p1Location == 15 && p2Location != 15)
		landmark[23] = " 1    ";
	else if(p1Location == 16 && p2Location != 16)
		landmark[29] = " 1    ";
	else if(p1Location == 17 && p2Location != 17)
		landmark[35] = " 1    ";
		
	if(p2Location == 0 && p1Location != 0)
		landmark[53] = "    2 ";
	else if(p2Location == 1 && p1Location != 1)
		landmark[50] = "    2 ";
	else if(p2Location == 2 && p1Location != 2)
		landmark[47] = "    2 ";
	else if(p2Location == 3 && p1Location != 3)
		landmark[44] = "    2 ";
	else if(p2Location == 4 && p1Location != 4)
		landmark[41] = "    2 ";
	else if(p2Location == 5 && p1Location != 5)
		landmark[38] = "    2 ";
	else if(p2Location == 6 && p1Location != 6)
		landmark[32] = "    2 ";
	else if(p2Location == 7 && p1Location != 7)
		landmark[26] = "    2 ";
	else if(p2Location == 8 && p1Location != 8)
		landmark[20] = "    2 ";
	else if(p2Location == 9 && p1Location != 9)
		landmark[2] = "    2 ";
	else if(p2Location == 10 && p1Location != 10)
		landmark[5] = "    2 ";
	else if(p2Location == 11 && p1Location != 11)
		landmark[8] = "    2 ";
	else if(p2Location == 12 && p1Location != 12)
		landmark[11] = "    2 ";
	else if(p2Location == 13 && p1Location != 13)
		landmark[14] = "    2 ";
	else if(p2Location == 14 && p1Location != 14)
		landmark[17] = "    2 ";
	else if(p2Location == 15 && p1Location != 15)
		landmark[23] = "    2 ";
	else if(p2Location == 16 && p1Location != 16)
		landmark[29] = "    2 ";
	else if(p2Location == 17 && p1Location != 17)
		landmark[35] = "    2 ";
		
	if(p2Location == 0 && p1Location == 0)
		landmark[53] = " 1  2 ";
	else if(p2Location == 1 && p1Location == 1)
		landmark[50] = " 1  2 ";
	else if(p2Location == 2 && p1Location == 2)
		landmark[47] = " 1  2 ";
	else if(p2Location == 3 && p1Location == 3)
		landmark[44] = " 1  2 ";
	else if(p2Location == 4 && p1Location == 4)
		landmark[41] = " 1  2 ";
	else if(p2Location == 5 && p1Location == 5)
		landmark[38] = " 1  2 ";
	else if(p2Location == 6 && p1Location == 6)
		landmark[32] = " 1  2 ";
	else if(p2Location == 7 && p1Location == 7)
		landmark[26] = " 1  2 ";
	else if(p2Location == 8 && p1Location == 8)
		landmark[20] = " 1  2 ";
	else if(p2Location == 9 && p1Location == 9)
		landmark[2] = " 1  2 ";
	else if(p2Location == 10 && p1Location == 10)
		landmark[5] = " 1  2 ";
	else if(p2Location == 11 && p1Location == 11)
		landmark[8] = " 1  2 ";
	else if(p2Location == 12 && p1Location == 12)
		landmark[11] = " 1  2 ";
	else if(p2Location == 13 && p1Location == 13)
		landmark[14] = " 1  2 ";
	else if(p2Location == 14 && p1Location == 14)
		landmark[17] = " 1  2 ";
	else if(p2Location == 15 && p1Location == 15)
		landmark[23] = " 1  2 ";
	else if(p2Location == 16 && p1Location == 16)
		landmark[29] = " 1  2 ";
	else if(p2Location == 17 && p1Location == 17)
		landmark[35] = " 1  2 ";
}
