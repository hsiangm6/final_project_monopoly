#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "event.h"
#include <string.h>

char *landmark[200] = { "      ", " Go-> ", "  ", "  ", "  ",   //location: 0

						"      ", "China ", "  ", "  ", "  ",   //location: 1
			
						"      ", "Chance", "  ", "  ", "  ",   //location: 2
			
						"      ", "Korea ", "  ", "  ", "  ",   //location: 3
			
						"      ", "India ", "  ", "  ", "  ",   //location: 4
			
						"      ", " Jail ", "  ", "  ", "  ",   //location: 5
			
						"      ", "Arabia", "  ", "  ", "  ",   //location: 6
			
						"      ", "Iraq  ", "  ", "  ", "  ",   //location: 7
			
						"      ", "Turkey", "  ", "  ", "  ",   //location: 8
			
						"      ", "Casino", "  ", "  ", "  ",   //location: 9
			
						"      ", "Greece", "  ", "  ", "  ",   //location: 10
			
						"      ", "Chance", "  ", "  ", "  ",   //location: 11
			
						"      ", "Italy ", "  ", "  ", "  ",   //location: 12
			
						"      ", "France", "  ", "  ", "  ",   //location: 13
			
						"      ", "Tunnel", "  ", "  ", "  ",   //location: 14
			
						"      ", "UK    ", "  ", "  ", "  ",   //location: 15
			
						"      ", "USA   ", "  ", "  ", "  ",   //location: 16
			
						"      ", "Canada", "  ", "  ", "  ",   //location: 17
			
						"******** ******** ******** ******** ******** ********", 
						
						"********",
						
						"                                     ",
						
						"                                     ",
						
						"                                     ",
						
						"                                     ",
						
						"                                     ",
						
						"  ---------------------------------  ",
						
						"                                     ",
						
						"                                     ",
						
						"                                     ",
						
						"  ---------------------------------  ",
						
						"                                     ",
						
						"                                     ",
						
						"                                     ",
						
						"                                     ",
						
						"                                     "};

char *building[36] = 
{
	" ",
	"1!@@!1",
	" ",
	"1#@@#1",
	"1$@@$1",
	" ",
	"1%@@%1",
	"1^@@^1",
	"1&@@&1",
	" ",
	"1*@@*1",
	" ",
	"1?@@?1",
	"1/@@\\1",
	" ",
	"1\\@@/1",
	"1w@@w1",
	"1s@@s1", // 17
	" ",
	"2!@@!2",
	" ",
	"2#@@#2",
	"2$@@$2",
	" ",
	"2%@@%2",
	"2^@@^2",
	"2&@@&2",
	" ",
	"2*@@*2",
	" ",
	"2?@@?2",
	"2/@@\\2",
	" ",
	"2\\@@/2",
	"2w@@w2",
	"2s@@s2" //35
};

int diceFace = 0;
int playerNow = 0;

void printLand();
void printPlayerLocation(Player* p1, Player* p2);
void printPlayerInfo(Player *p1, Player *p2, Building *b);
void endGame(Player *p1, Player *p2,  Building *b);
void move(Player *player,Player *receive, Building *b);

int main()
{
	char nameOfPlayer1[16], nameOfPlayer2[16]; // The maximum length of player's name is 15
	char game_switch[2]= "y";
	puts("Wellcome to the Smile Monopoly ! ");
	puts("11111111111111111");
	Sleep(1000);
	puts("------------------");
	//system("CLS");
	puts("Please enter the name of player 1: ");
    fgets(nameOfPlayer1, 16, stdin);
    if(nameOfPlayer1[strlen(nameOfPlayer1) - 1] == '\n')
        nameOfPlayer1[strlen(nameOfPlayer1) - 1] = '\0';
    puts("Please enter the name of player 2: ");
	fgets(nameOfPlayer2, 16, stdin);
	if(nameOfPlayer2[strlen(nameOfPlayer2) - 1] == '\n')
        nameOfPlayer2[strlen(nameOfPlayer2) - 1] = '\0';

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

	printPlayerLocation(&p1, &p2);
	printLand();
	puts("2222222222222");

	Sleep(2000);
	//system("CLS");
	puts("---------------");
	//game start
	while (game_switch[0] == 'y')
	{
		playerNow = 1;
		if (p1.gameStatus >= 0)
		{
			srand(time(NULL)); //set random number seeds
			diceFace = 1 + (rand() % 6); //roll the dice
			printPlayerInfo(&p1, &p2, b);
			printPlayerLocation(&p1, &p2);
			printLand();
			Sleep(2000);
			move(&p1, &p2, b);
			printPlayerInfo(&p1, &p2, b);
			printPlayerLocation(&p1, &p2);
			printLand();
			event(&p1, &p2, b, landmark, building);

			//system("CLS");
			puts("---------------");
			printPlayerInfo(&p1, &p2, b);
			printPlayerLocation(&p1, &p2);
			printLand();
		}
		else
		{
			p1.gameStatus += 1;
		}
		
		playerNow = 2;
		puts("22222222222222");
		Sleep(2000);
		//system("CLS");
		puts("---------------");
		if (p2.gameStatus >= 0)
		{
			srand(time(NULL)); //set random number seeds
			diceFace = 1 + (rand() % 6); //roll the dice
			printPlayerInfo(&p1, &p2, b);
			printPlayerLocation(&p1, &p2);
			printLand();
			Sleep(2000);
			move(&p2, &p1, b);
			printPlayerInfo(&p1, &p2, b);
			printPlayerLocation(&p1, &p2);
			printLand();
			event(&p2, &p1, b, landmark, building);

			//system("CLS");
			puts("---------------");
			printPlayerInfo(&p1, &p2, b);
			printPlayerLocation(&p1, &p2);
			printLand();
		}
		else
		{
			p2.gameStatus += 1;
		}
		//system("CLS");
		puts("---------------");
		puts("Whether open the next round? (Enter y to continue, n to end the game.)");
		gets(game_switch);
		if (game_switch == 'n') {
			endGame(&p1, &p2, b);
			break;
		}
		//system("CLS");
		puts("---------------");
	}
}

void printLand()
{
	printf("%s\n*%s* *%s* *%s* *%s* *%s* *%s*\n*%s* *%s* *%s* *%s* *%s* *%s*\n*%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s*\n%s\n",

    landmark[90],
	landmark[0], landmark[5], landmark[10], landmark[15], landmark[20], landmark[25],
    landmark[1], landmark[6], landmark[11], landmark[16], landmark[21], landmark[26],
    landmark[2], landmark[3], landmark[4], landmark[7], landmark[8], landmark[9], landmark[12], landmark[13], landmark[14], landmark[17], landmark[18], landmark[19], landmark[22], landmark[23], landmark[24], landmark[27], landmark[28], landmark[29],
	landmark[90]);

   	printf("%s%s%s\n*%s*%s*%s*\n*%s*%s*%s*\n*%s%s%s*%s*%s%s%s*\n%s%s%s\n", landmark[91], landmark[92], landmark[91], landmark[85], landmark[93], landmark[30], landmark[86], landmark[94], landmark[31], landmark[87], landmark[88], landmark[89], landmark[95], landmark[32], landmark[33], landmark[34], landmark[91], landmark[96], landmark[91]);
    printf("%s%s%s\n*%s*%s*%s*\n*%s*%s*%s*\n*%s%s%s*%s*%s%s%s*\n%s%s%s\n", landmark[91], landmark[97], landmark[91], landmark[80], landmark[98], landmark[35], landmark[81], landmark[99], landmark[36], landmark[82], landmark[83], landmark[84], landmark[100], landmark[37], landmark[38], landmark[39], landmark[91], landmark[101], landmark[91]);
    printf("%s%s%s\n*%s*%s*%s*\n*%s*%s*%s*\n*%s%s%s*%s*%s%s%s*\n%s%s%s\n", landmark[91], landmark[102], landmark[91], landmark[75], landmark[103], landmark[40], landmark[76], landmark[104], landmark[41], landmark[77], landmark[78], landmark[79], landmark[105], landmark[42], landmark[43], landmark[44], landmark[91], landmark[106], landmark[91]);

    printf("%s\n*%s* *%s* *%s* *%s* *%s* *%s*\n*%s* *%s* *%s* *%s* *%s* *%s*\n*%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s* *%s%s%s*\n%s\n",

    landmark[90],
	landmark[70], landmark[65], landmark[60], landmark[55], landmark[50], landmark[45],
    landmark[71], landmark[66], landmark[61], landmark[56], landmark[51], landmark[46],
    landmark[72], landmark[73], landmark[74], landmark[67], landmark[68], landmark[69], landmark[62], landmark[63], landmark[64], landmark[57], landmark[58], landmark[59], landmark[52], landmark[53], landmark[54], landmark[47], landmark[48], landmark[49],
	landmark[90]);
}

void printPlayerLocation(Player* p1, Player* p2)
{
	int i;
	for(i=2; i<=87; i+=5)
		landmark[i] = "  ";
	for(i=4; i<=89; i+=5)
		landmark[i] = "  ";

	landmark[p1->location * 5 + 2] = " 1";
	landmark[p2->location * 5 + 4] = "2 ";
}



void endGame(Player *p1, Player *p2,  Building *b)
{   
    int i, counter=0, player1Count=p1->money, player2Count=p2->money;
    for (i=0; i<18; i++)
    {
        if (b[i].owner == 1)
	{
            player1Count += (1.5 * b[i].buyPrice + (1.5 * b[i].buildPrice) * b[i].condition);
        }
        else if (b[i].owner == 2)
	{
            player2Count += (1.5 * b[i].buyPrice + (1.5 * b[i].buildPrice) * b[i].condition);
        }
    }
    if (player1Count > player2Count)
    {
        printf ("Congradulate!! Player %s wins the game.\n", p1->name);
        printf ("Toltal asset: %s: %d, %s: %d", p1->name, player1Count, p2->name, player2Count);
    }
    else if (player1Count < player2Count)
    {
        printf ("Congradulate!! Player %s wins the game.", p2->name);
        printf ("Toltal asset: %s: %d, %s: %d", p1->name, player1Count, p2->name, player2Count);
    }
    else if (player1Count == player2Count)
    {
    puts ("There is no winner in the game!");
    }
}

void move(Player *player, Player *receive, Building *b)
{
	size_t i = 0;
	
	for (i = 0; i < diceFace; i++) {
		player->location += 1;
		if (player->location > 17){ //pass the start point
			player->location -= 18;
			player->money += 10000;
		}
		
		if(playerNow == 1)
			printPlayerLocation(player, receive);
		else
			printPlayerLocation(receive, player);
		printLand();
		puts("111111111111111111");
		Sleep(1000);
		puts("-------------------");
		//system("CLS");
	}
}

void printPlayerInfo(Player* p1, Player* p2, Building* b)
{
	char static str93[38] = "";
	snprintf(str93, sizeof(str93), "         Player 1: %-18s", p1->name);
	landmark[93] = str93;
   
	char static str95[38] = "";
	snprintf(str95, sizeof(str95), "            Money: %-18d", p1->money);
	landmark[95] = str95;

	char static str98[38] = "";
	snprintf(str98, sizeof(str98), "    It's round for %-18s", playerNow == 1 ? p1->name : p2->name);
	landmark[98] = str98;
	
	char static str100[38] = "";
	snprintf(str100, sizeof(str100), "         Your roll dice is %-10d", diceFace);
	landmark[100] = str100;

	char static str103[38] = "";
	snprintf(str103, sizeof(str103), "         Player 2: %-18s", p2->name);
	landmark[103] = str103;

	char static str105[38] = "";
	snprintf(str105, sizeof(str105), "            Money: %-18d", p2->money);
	landmark[105] = str105;
}

