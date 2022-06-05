#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "event.h"
#include <string.h>

//map coordinates and content
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
						
						"                                     ",   //status bar 1
						
						"                                     ",   //status bar 2
						
						"                                     ",   //status bar 3
						
						"                                     ",   //status bar 4
						
						"                                     ",   //status bar 5
						
						"  ---------------------------------  ",   //status bar 6
						
						"                                     ",   //status bar 7
						
						"                                     ",   //status bar 8
						
						"                                     ",   //status bar 9
						
						"  ---------------------------------  ",   //status bar 10
						
						"                                     ",   //status bar 11
						
						"                                     ",   //status bar 12
						
						"                                     ",   //status bar 13
						
						"                                     ",   //status bar 14
						
						"                                     "};  //status bar 15

//structure mark
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

int diceFace = 15;   //the number of dice used to know the step player moved 
int playerNow = 1;   //current operated player


void delay(int seconds);   //let the program sleep for assigned seconds
void delayms(int seconds);   //let the program sleep for assigned milliseconds
void printLand();   //map
void printPlayerLocation(Player* p1, Player* p2);   //the players' position on the map
void printPlayerInfo(Player *p1, Player *p2);   //change the row of the player status in the middle of the map
void endGame(Player *p1, Player *p2,  Building *b);   //the last player asset settlement in the game
void move(Player *player,Player *receive);   //according to the player in this segment, deciding whose location will change

int main()
{
	char nameOfPlayer1[16], nameOfPlayer2[16]; // The maximum length of player's name is 15
	char game_switch[2]= "y";   //ask player whether the game is continue
	int dice_switch = 0;   //ask player whether they roll the dice
	int event_switch = 0;   //check player whether they know the information
	
    system ("stty -icanon"); //for linux only
	puts("Welcome to the Smile Monopoly ! ");
	delay(2);
	printf("\033[0;0H\033[2J");
	
	//enter the name of the player
	puts("Please enter the name of player 1: ");
    fgets(nameOfPlayer1, 16, stdin);
    if(nameOfPlayer1[strlen(nameOfPlayer1) - 1] == '\n')
        nameOfPlayer1[strlen(nameOfPlayer1) - 1] = '\0';
    puts("Please enter the name of player 2: ");
	fgets(nameOfPlayer2, 16, stdin);
	if(nameOfPlayer2[strlen(nameOfPlayer2) - 1] == '\n')
        nameOfPlayer2[strlen(nameOfPlayer2) - 1] = '\0';
	printf("\033[0;0H\033[2J");    //clean console
	
	//player 1 structure
	Player p1 =
	{
		.money = 15000,   //current cash
		.name = nameOfPlayer1,   //player name
		.location = 0,   //player location
		.gameStatus = 0,   //check whether the player is in jail now
		.player_number = 1,   //player number
		.debt_counter=0   //count the number of rounds in which the player is continuously in debt 
	};
	//player 2 structure
	Player p2 =
	{
		.money = 15000,
		.name = nameOfPlayer2,
		.location = 0,
		.gameStatus = 0,
		.player_number = 2,
		.debt_counter = 0
	};
	//building structure
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
	//print the state, map, location of the player 
	printPlayerInfo(&p1, &p2);
	printPlayerLocation(&p1, &p2);
	printLand();

	delay(1);
	printf("\033[0;0H\033[2J");

	//game start
	while (game_switch[0] == 'y')
	{
		//player 1 round
		playerNow = 1;
		if (p1.gameStatus >= 0)   //prevent the player is in jail now
		{	
			diceFace = 15;
			printPlayerInfo(&p1, &p2);   //update status bar
			printLand();   //print land

			//user experience
			puts("Press space to roll the dice.\n");
			while (dice_switch = getchar()) {   //fool-proof
				if (dice_switch == ' ') {
					srand(time(NULL)); //set random number seeds
					diceFace = 0;
					diceFace = 1 + (rand() % 6); //roll the dice
					break;
				}
			}
			printf("\033[0;0H\033[2J");
			//print current map ,status, location
			printPlayerInfo(&p1, &p2);
			printPlayerLocation(&p1, &p2);
			printLand();
			delay(1);

			//move and update layout
			move(&p1, &p2);
			printPlayerInfo(&p1, &p2);
			printPlayerLocation(&p1, &p2);
			printLand();

			//execute related activity in monopoly
			event(&p1, &p2, b, landmark, building);

			
			printf("\033[0;0H\033[2J");
			//update the layout
			printPlayerInfo(&p1, &p2);
			printPlayerLocation(&p1, &p2);
			printLand();
		}
		//pleyer is in jail now and will be released next round
		else
		{
			p1.gameStatus += 1;
		}

		//count the number of rounds in which the player is continuously in debt
		if (p1.money < 0) {
			p1.debt_counter++;
		}
		else{
			p1.debt_counter=0;
		}

		//player 2 round
		playerNow = 2;
		delayms(2);
		printf("\033[0;0H\033[2J");

		if (p2.gameStatus >= 0)  //prevent player is in jail now
		{
			diceFace = 15;

			//update layout
			printPlayerInfo(&p1, &p2);
			printLand();

			//user experience
			puts("Press space to roll the dice.\n");
			while (dice_switch = getchar()) {
				if (dice_switch == ' ') {
					srand(time(NULL)); //set random number seeds
					diceFace = 0;
					diceFace = 1 + (rand() % 6); //roll the dice
					break;
				}
			}
			printf("\033[0;0H\033[2J");

			//update layout
			printPlayerInfo(&p1, &p2);
			printPlayerLocation(&p1, &p2);
			printLand();
			delay(1);

			//move location
			move(&p2, &p1);

			//update layout
			printPlayerInfo(&p1, &p2);
			printPlayerLocation(&p1, &p2);
			printLand();

			//execute the activity in monopoly
			event(&p2, &p1, b, landmark, building);

			//update layout
			printf("\033[0;0H\033[2J");
			printPlayerInfo(&p1, &p2);
			printPlayerLocation(&p1, &p2);
			printLand();
		}
		//pleyer is in jail now and will be released next round
		else
		{
			p2.gameStatus += 1;
		}
		printf("\033[0;0H\033[2J");
		//update layout
		printPlayerInfo(&p1, &p2);
		printLand();
		//count the number of rounds in which the player is continuously in debt
		if (p2.money < 0) {
			p2.debt_counter++;
		}
		else {
			p2.debt_counter = 0;
		}
		//if the number of rounds in which the player is continuously in debt is 3, the player lose
		if (p1.debt_counter == 1) {
			printf("Sorry, %s is in a manner of continuous liability.\n", p1.name);
			printf("Congratulate!! Player %s wins the game.\n", p2.name);
			break;
		}
		else if (p2.debt_counter == 1) {
			printf("Sorry, %s is in a manner of continuous liability.\n", p2.name);
			printf("Congratulate!! Player %s wins the game.\n", p1.name);
			break;
		}
		//prevent ask whether players open the next round repeatedly when players are all in jail
		if (p1.gameStatus < 0 && p2.gameStatus < 0) {
			printf("\033[0;0H\033[2J");
			continue;
		}
		//open the next round or end the game
		puts("Whether open the next round? (Enter y to continue, n to end the game.)");
		while (game_switch[0] = getchar()) {
			if (game_switch[0] == 'y' || game_switch[0] == 'n') {
				break;
			}
		}
		printf("\033[0;0H\033[2J");

		//know who is winner
		if (game_switch[0] == 'n') {
			endGame(&p1, &p2, b);
			break;
		}
	}
}

//map
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

//the players' position on the map
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


//the last player asset settlement in the game
void endGame(Player *p1, Player *p2,  Building *b)
{   
    int i, counter=0, player1Count=p1->money, player2Count=p2->money;
    for (i=0; i<18; i++)
    {
        if (b[i].owner == 1)
	{
            player1Count += b[i].finalPrice;   //player1Count = cash + building price
        }
        else if (b[i].owner == 2)
	{
            player2Count += b[i].finalPrice;   //player2Count = cash + building price
        }
    }
	//player 1 win
    if (player1Count > player2Count)
    {
        printf ("Congratulate!! Player %s wins the game.\n", p1->name);
        printf ("Toltal asset: %s: %d, %s: %d", p1->name, player1Count, p2->name, player2Count);
    }
	//player 2 win
    else if (player1Count < player2Count)
    {
        printf ("Congratulate!! Player %s wins the game.\n", p2->name);
        printf ("Toltal asset: %s: %d, %s: %d", p1->name, player1Count, p2->name, player2Count);
    }
	//tie
    else if (player1Count == player2Count)
    {
    puts ("Draw ! Everyone is winner in the game!");
    }
}

//according to the player in this segment, deciding whose location will change.
void move(Player *now_player, Player *wait_player) {  //move(moving player,waiting player, 
	size_t i = 0; //for-loop count
	int Go_money = rand()% 3;
	printf("\033[0;0H\033[2J");   //clear up the layout
	for (i = 0; i < diceFace; i++) {   //change the player's location step by step.
		now_player->location += 1;
		if (now_player->location > 17){   //pass the start point
			now_player->location -= 18;
			now_player->money += (5000+ 2500 * Go_money);
		}
		//In order to match the input settings of printPlayerLocation(p1,p2)
		if(playerNow == 1)
			printPlayerLocation(now_player, wait_player);   //printPlayerLocation(p1,p2)
		else
			printPlayerLocation(wait_player, now_player);   //printPlayerLocation(p1,p2)
		printLand();   //print the map and the player status
		delayms(3);
		printf("\033[0;0H\033[2J");
	}
}

//change the row of the player status in the middle of the map
void printPlayerInfo(Player* p1, Player* p2)
{
	//player 1
	char static str93[38] = "";
	snprintf(str93, sizeof(str93), "         Player 1: %-18s", p1->name);
	landmark[93] = str93;
   
	char static str95[38] = "";
	snprintf(str95, sizeof(str95), "            Money: %-18d", p1->money);
	landmark[95] = str95;

	//show whose turn + the number of move steps rolled by the dice 
	char static str98[38] = "";
	snprintf(str98, sizeof(str98), "    It's round for %-18s", playerNow == 1 ? p1->name : p2->name);
	landmark[98] = str98;
	
	char static str100[38] = "";
	snprintf(str100, sizeof(str100), "         Your roll dice is %-10c", (char)diceFace + 48);
	landmark[100] = str100;

	//player 2
	char static str103[38] = "";
	snprintf(str103, sizeof(str103), "         Player 2: %-18s", p2->name);
	landmark[103] = str103;

	char static str105[38] = "";
	snprintf(str105, sizeof(str105), "            Money: %-18d", p2->money);
	landmark[105] = str105;
}

void delay(int seconds)
{
	clock_t start = clock();
	clock_t lay = (clock_t)seconds * CLOCKS_PER_SEC;
	while((clock()-start) < lay);
}

void delayms(int seconds)
{
	clock_t start = clock();
	clock_t lay = (clock_t)seconds * CLOCKS_PER_SEC * 0.25;
	while((clock()-start) < lay);
}
