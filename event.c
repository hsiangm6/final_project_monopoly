#include "event.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void event(Player* player, Player* receive, Building *b, char **landmark, char **building)
{
	srand(time(NULL));
    switch(player->location)
	{
	case 5://jail
		player->gameStatus = -1;
		break;
	case 2:
	case 11://draw cards
		draw(player, receive, b, landmark, building);
		break;
	case 9://casino
		casino(player);
			break;
	case 14://go to start
		player->location = 0;
		player->money += 10000;
		break;
	case 0:
		break;
	default:
		buy(player,receive, &b[player->location], landmark, building);
		break;
   	 }
}

void draw(Player *player, Player* receive, Building *b, char **landmark, char **building)
{
		int card = rand() % 11;
    	int target = rand() % 18;
		char trans[3]  = "";   //trans = string to int
    	switch(card)
		{
			case 0:
			case 1:
			case 2:
				printf("The newly hired supervisor has good performance management, increasing the overall turnover by %d NT dollars.\n", 1000 + card * 2000);
				player-> money += 1000 + card * 2000;
				break;
			case 3:
			case 4:
			case 5:
				printf("You are unqualified by the health bureau, so you are fined %d NT dollars.\n", -(1000 + (card - 2) * 2000));
				player-> money -= (1000 + (card - 2) * 2000);
				break;
			case 6:
				printf("You get a ticket to broken Dokodemo Door, so you will be teleported to random location: %d\n", target);
				player-> location = target;
				event(player, receive, b, landmark, building);
				break;
			case 7:
				printf("You become an honorary real estate tycoon, so the people invite you to the next location: %d\n", player->location + 1);
				player-> location += 1;
				event(player, receive, b, landmark, building);
				break;
			case 8:
				printf("You became a jewel thief and stole 50,000 worth of jewels, you were captured and deported from the country. \nYou are forced to go to the previous location: %d\n", player->location - 1);
				player-> location -= 1;
				event(player, receive, b,landmark, building);
				break;
			case 9:
				printf("You bad. Go to jail.\n");
				player-> location = 5;
				event(player, receive, b, landmark, building);
				break;
			case 10:
				target=0;
				puts("You get a ticket to Dokodemo Door, please enter the location you want to go to (0 ~17)(only one chance to enter): ");
				gets(trans);
				target=atoi(trans);
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

void casino(Player *player)
{
	char ch[2] = "\0", ch2[2] = "\0", ch3[2] = "\0";
	int coin=0, temp=0, round=1, playCondition=1, ip=0;
	while (playCondition == 1)
	{
		if (player->money <2000) //Do you have enough money?
		{
			puts ("You don\'t have enough money!");
			break;
		}

		printf ("Welcome to Casino Game. This is round %d. \n", round);
		printf ("You have $%d. Basic cost is $2000.\n", player->money);
		coin = rand () % 2;	//random front back

		ip = 1;
		while (ip == 1){	//fool-proof
			puts ("Please input your odds selection. (a)x1 (b)x2 (c)x3 (d)x4 (e)exit game.");
			gets(ch);
			if (ch[0] <= 100 && ch[0] >= 97){
				ip = 0;
				if (player->money <(2000*ch[0])){	//Do you have money?
					puts ("You don\'t have enough money!");
					ip=1;
				}
			}
			else if (ch[0] ==101) {
				ip = 2;
			}
			else {
				puts ("Please enter correct content!");
				ip=1;
			}
		}

		if (ip == 2) break;

		ip =1;
		while (ip == 1) //fool-proof
		{
			puts("Please input front back selection. (f)front (b)back.");
			gets(ch2);

			if (ch2[0] == 102)
			{
				temp = 0;
				ip =0;
			}	//front(f)
			else if (ch2[0] == 98)
			{
				temp = 1;
				ip=0;
			}	//back(b)
			else
			{
				puts("Please enter correct content!");
				ip =1;
			}
		}

		if (temp == coin)
		{
			player->money += (2000*(ch[0] - 96));
			printf ("You Win!\nGet $%d.\n", (2000*(ch[0] - 96)));
		}
		else
		{
			player->money -= (2000*(ch[0] - 96));
			printf ("You Loose.\nLoose $%d.\n", (2000*(ch[0] - 96)));
		}

		if (round == 3) break;

		ip =1;
		while (ip ==1) //fool-proof
		{
			puts("Do you want to play again? Enter 'y' to continue, 'n' to leave the game.");
			gets(ch3);
			if (ch3[0] == 121)
			{
				playCondition = 1;
				round ++;
				ip =0;
			}
			else if (ch3[0] == 110)
			{
				playCondition = 0;
				ip =0;
			}
			else
			{
				puts("Please enter correct content!");
				ip =1;
			}
		}
	}
}

void buy(Player *player, Player* receive, Building *b, char **landmark, char **building)
{
	char buy_switch[2] = "y";
	switch (b->condition) 
	{
		//land
		case -1:
			puts("Are you going to buy the land? (only y/n):");
			gets(buy_switch);
			while (buy_switch[0] != 'y' && buy_switch[0] != 'n') //fool?proof design
			{  
				puts("Are you going to buy the land? (only y/n):");
				gets(buy_switch);
			}
			if (buy_switch[0] == 'y') //buy the land
			{   
				b->condition = 0;
				printf("buy price:%d\n", b->buyPrice);
				player->money -= b->buyPrice;
				landmark[(player->location)*5] = player->player_number == 1? "  1>  " : "  2>  ";
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
				puts("Are you going to build the structure? (only y/n):");
				gets(buy_switch);

				//fool?proof design
				while (buy_switch[0] != 'y' && buy_switch[0] != 'n') 
				{
					puts("Are you going to build the structure? (only y/n):");
					gets(buy_switch);
				}

				if (buy_switch[0] == 'y') 
				{
					b->condition = 1;
					player->money -= b->buildPrice;
					landmark[(player->location)*5] = player->player_number == 1 ? building[player->location] : building[player->location+18];
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
				puts("Are you going to buy the flag from your opponent? (only y/n):");
				gets(buy_switch);

				//fool?proof design
				while (buy_switch[0] != 'y' && buy_switch[0] != 'n') 
				{
					puts("Are you going to buy the flag from your opponent? (only y/n):");
					gets(buy_switch);
				}
				
				//buy someone else's flag
				if (buy_switch[0] == 'y') 
				{
					b->owner = player->player_number;
					landmark[(player->location)*5] = player->player_number == 1 ? "2>" : "1>";
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
				puts("Are you going to buy the structure from your opponent? (only y/n):");
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
					landmark[(player->location) * 5] = player->player_number == 1 ? building[player->location+18] : building[player->location];
				}

				else 
				{
					puts("What a shame! You didn't buy the structure.\n");
				}
			}
			break;
	}
}

void buildingStructure(Building *b)
{
	b->buildPrice = 0.5 * b->buyPrice;
	b->finalPrice = b->buyPrice + (b->buildPrice) * b->condition;
	b->fee = 0.5 * b->finalPrice;
	b->buyPriceFromTheOpponent = 2 * b->finalPrice;
}