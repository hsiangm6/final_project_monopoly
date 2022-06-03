#include "event.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//activity in monopoly
void event(Player* player, Player* receive, Building *b, char **landmark, char **building)
{
	int draw_switch = 0;
	srand(time(NULL));
    switch(player->location)
	{
	case 5://jail
		player->gameStatus = -1;
		puts("Welcome to the jail !\nYou are forbidden to roll the dice for one round !\n");
		break;
	case 2:
	case 11://draw cards
		puts("Press space to draw the card...\n");
		while (draw_switch = getch()) {
			if (draw_switch == ' ') {
				break;
			}
		}
		draw(player, receive, b, landmark, building);
		break;
	case 9://casino
		casino(player);
			break;
	case 14://go to start
		puts("You find a tunnel back to the \"Go\"");
		player->location = 0;
		player->money += 10000;
		break;
	case 0:
		break;
	default: //buy estate or pay the fee
		buy(player,receive, &b[player->location], landmark, building);
		break;
   	 }
}

//chance
void draw(Player *player, Player* receive, Building *b, char **landmark, char **building)
{
		int card = rand() % 11;  // 11 cards
    	int target = rand() % 18;   //delivery location
		char trans[3]  = "";   //trans = string to int
    	switch(card)
		{
			//plus money
			case 0:
			case 1:
			case 2:
				printf("The newly hired supervisor has good performance management, increasing the overall turnover by %d NT dollars.\n", 1000 + card * 2000);
				player-> money += 1000 + card * 2000;
				break;

			//minus money
			case 3:
			case 4:
			case 5:
				printf("You are unqualified by the health bureau, so you are fined %d NT dollars.\n", -(1000 + (card - 3) * 2000));
				player-> money -= (1000 + (card - 3) * 2000);
				break;
			//deliver to random location
			case 6:
				printf("You get a ticket to broken Dokodemo Door, so you will be teleported to random location: %d\n", target);
				//pass the start
				if (target < player->location) {
					player->money += 10000;
				}
				player-> location = target;
				event(player, receive, b, landmark, building);
				break;
			//player location + 1
			case 7:
				printf("You become an honorary real estate tycoon, so the people invite you to the next location: %d\n", player->location + 1);
				player-> location += 1;
				event(player, receive, b, landmark, building);
				break;
			//player location -1
			case 8:
				printf("You became a jewel thief and stole 50,000 worth of jewels, you were captured and deported from the country. \nYou are forced to go to the previous location: %d\n", player->location - 1);
				player-> location -= 1;
				event(player, receive, b,landmark, building);
				break;
			//do to jail
			case 9:
				printf("You bad. Go to jail.\n");
				player-> location = 5;
				event(player, receive, b, landmark, building);
				break;
			//go to the location player points
			case 10:
				target=0;
				puts("You get a ticket to Dokodemo Door, please enter the location you want to go to (0 ~17)(only one chance to enter): ");
				gets(trans);
				target=atoi(trans);
				//pass the start
				if (target < player->location) {
					player->money += 10000;
				}
				if(target>=0 && target<=17)
				{
					printf("You will be teleported to specified location: %d\n", target);
					player-> location = target;
					event(player, receive, b, landmark, building);
				}
				break;
			default:
				break;
	    }
}

//casino game
void casino (Player *player)
{
	char odds[2] = "\0", coinStatus[2] = "\0", gameStatus[2] = "\0";
	int coin=0, FrontBack=0, round=1, playCondition=1;
	while (playCondition == 1)
	{
		if (player->money <2000) //Do you have enough money?
		{
			puts ("You don\'t have enough money!");
			break;
		}

		printf ("Welcome to Casino Game. Basic cost is $2000.\n");
		printf ("This is round %d. Your current money is $%d.\n", round, player->money);
		coin = rand () % 2;	//random front back


		puts ("Please input your odds selection. (a)x1 (b)x2 (c)x3 (d)x4 (e)exit game.");
		gets(odds);
		while (odds[0] > 101 || odds[0] < 97 )	//fool-proof
		{
			puts ("Please enter correct content!");
			gets(odds);
		}
		if (odds[0] != 101){	
			while (player->money < (2000*(odds[0]-96))){  //Do you have money?
				puts ("You don\'t have enough money!");
				puts ("Please input your odds selection again. (a)x1 (b)x2 (c)x3 (d)x4 (e)exit game.");
				gets(odds);
			}
		}
		else break;		//exit the game
		
		puts("Please input front back selection. (f)front (b)back.");
		gets(coinStatus);
		while (coinStatus[0] != 102 && coinStatus[0] != 98)	//fool-proof
		{
			puts("Please enter correct content!");
			gets(coinStatus);
		}
		if (coinStatus[0] == 102) FrontBack = 0;
		else if (coinStatus[0] == 98) FrontBack = 1;

		//win(the casino)
		if (FrontBack == coin)
		{
			player->money += (2000*(odds[0] - 96));
			printf ("You Win $%d!\n", (2000*(odds[0] - 96)));
		}
		//lose(the casino) 
		else
		{
			player->money -= (2000*(odds[0] - 96));
			printf ("You Loose $%d.\n", (2000*(odds[0] - 96)));
		}
		//up to 3 rounds
		if (round == 3) 
		{
			puts ("This is the end of the game!");
			break;
		}

		puts("Do you want to play again? Enter 'y' to continue, 'n' to leave the game.");
		gets(gameStatus);
		while (gameStatus[0] != 'y' && gameStatus[0] != 'n')	//fool-proof
		{
			puts("Please enter correct content!");
			gets(gameStatus);
		}
		if (gameStatus[0] == 'y')
		{
			playCondition = 1;
			round ++;
		}
		else if (gameStatus[0] == 'n')
		{
			playCondition = 0;
		}
	}
}

//purchase behaviour
void buy(Player *player, Player* receive, Building *b, char **landmark, char **building)
{
	char buy_switch[2] = "y";   //the switch know whether the player buys the items
	switch (b->condition) //condition: -1=land, 0=flag, 1=structure
	{
		//land
		case -1:
			printf("buy price: %d\n", b->buyPrice);
			puts("Are you going to buy the land? (only y/n):");
			gets(buy_switch);

			//fool?proof design
			while (buy_switch[0] != 'y' && buy_switch[0] != 'n') 
			{  
				puts("Are you going to buy the land? (only y/n):");
				gets(buy_switch);
			}

			//buy the land
			if (buy_switch[0] == 'y') 
			{   
				b->condition = 0;
				player->money -= b->buyPrice;
				landmark[(player->location)*5] = player->player_number == 1? "  1>  " : "  2>  ";   //set up th flag
				b->owner = player->player_number;
				buildingStructure(b);
			}
			else 
			{
				puts("What a shame! You didn't buy the land.\n");
			}
			break;

		//flag
		case 0:
			//arrive the own flag
			if (b->owner == player->player_number) 
			{
				//whether build structure on own flag
				printf("building price: %d\n", b->buildPrice);
				puts("Are you going to build the structure? (only y/n):");
				gets(buy_switch);

				//fool-proof
				while (buy_switch[0] != 'y' && buy_switch[0] != 'n') 
				{
					puts("Are you going to build the structure? (only y/n):");
					gets(buy_switch);
				}

				if (buy_switch[0] == 'y') 
				{
					b->condition = 1;
					player->money -= b->buildPrice;
					landmark[(player->location)*5] = player->player_number == 1 ? building[player->location] : building[player->location+18];   //set up structure
					buildingStructure(b);
				}
				else 
				{
					puts("What a shame! You didn't build the structure.\n");
				}

			}

			//arrive someone else's flag
			else 
			{   
				printf("You are supposed to pay the fee: %d\n", b->fee);
				player->money -= b->fee;
				receive->money += b->fee;

				printf("Are you going to buy the flag from your opponent for %d? (only y/n):", b->buyPriceFromTheOpponent);
				gets(buy_switch);

				//fool-proof 
				while (buy_switch[0] != 'y' && buy_switch[0] != 'n') 
				{
					puts("Are you going to buy the flag from your opponent? (only y/n):");
					gets(buy_switch);
				}
				
				//buy someone else's flag
				if (buy_switch[0] == 'y') 
				{
					b->owner = player->player_number;
					landmark[(player->location)*5] = player->player_number == 1 ? "  1>  " : "  2>  ";
					player->money -= b->buyPriceFromTheOpponent;
					receive->money += b->buyPriceFromTheOpponent;
				}

				else 
				{
					puts("What a shame! You didn't buy the flag.\n");
				}
			}
			break;

		//structure
		case 1: 
			//arrive the own estate
			if (b->owner == player->player_number) 
			{
				puts("You arrive your own estate!\n");
				break;
			}

			//arrive someone else's structure
			else 
			{
				printf("You are supposed to pay the fee: %d\n", b->fee);
				player->money -= b->fee;
				receive->money += b->fee;

				//The ability to purchase other's structures
				/*printf("Are you going to buy the structure from your opponent for %d? (only y/n):", b->buyPriceFromTheOpponent);
				gets(buy_switch);

				//fool-proof design
				while (buy_switch[0] != 'y' && buy_switch[0] != 'n') 
				{
					puts("Are you going to buy the structure from your opponent? (only y/n):");
					gets(buy_switch);
				}

				//buy someone else's structure
				if (buy_switch[0] == 'y') 
				{
					b->owner = player->player_number;
					player->money -= b->buyPriceFromTheOpponent;
					receive->money+= b->buyPriceFromTheOpponent;
					landmark[(player->location) * 5] = player->player_number == 1 ? building[player->location] : building[player->location+18];
				}

				else 
				{
					puts("What a shame! You didn't buy the structure.\n");
				}*/
			}
			break;
	}
}

//Real estate price of building structure, market value, toll, purchace price of other's flag
void buildingStructure(Building *b)
{
	b->buildPrice = 0.5 * b->buyPrice;   //price of building structure
	b->finalPrice = b->buyPrice + (b->buildPrice) * b->condition;   //market value
	b->fee = 0.5 * b->finalPrice;   //toll
	b->buyPriceFromTheOpponent = 1.5 * b->finalPrice;   //purchace price of other's flag
}
