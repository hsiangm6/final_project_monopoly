#include "event.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void event(struct Player* player,struct Building* b){
	srand(time(NULL));
    	switch(player->location){
        case 5://jail
			player->gameStatus = -1;
			break;
        case 2:
        case 11://draw cards
			draw(&player, &b[player->location]);
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
			buy(player,b);
			break;
    }
}

void draw(struct Player* player, struct Building* b){
    int card = rand() % 11;
    int target = rand() % 18;
    switch(card){
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
		event(&player, &b[player->location]);
		break;
	case 7:
		printf("You become an honorary real estate tycoon, so the people invite you to the next location: %d", player->location + 1);
		player-> location += 1;
		event(&player, &b[player->location]);
		break;
	case 8:
		printf("You became a jewel thief and stole 50,000 worth of jewels, you were captured and deported from the country. \nYou are forced to go to the previous location: %d\n", player->location - 1);
		player-> location -= 1;
		event(&player, &b[player->location]);
		break;
	case 9:
		player-> location = 5;
		event(&player, &b[player->location]);
		break;
	case 10:
		target=0;
		puts("You get a ticket to Dokodemo Door, please enter the location you want to go to (0 ~17)(only one chance to enter): "); 
		scanf_s("%d", &target);
		if(target>=0 && target<=17){
			printf("You will be teleported to specified location: %d", target);
			player-> location = target;
			event(&player,&b[player->location]);
		}
		break; 
	default:
		break;
    }
}

void casino (struct Player* player){
	char ch='\0', ch2 = '\0', ch3 = '\0';
	int coin, temp, round=1, playCondition=1, ip;
	while (playCondition == 1){
		if (player->money <2000){	//Do you have money?
			puts ("You don\'t have enough money!");
			break;
		}

		printf ("Welcome to Casino Game. This is round %d. \n", round);
		coin = rand () % 2;	//random front back

		ip = 1;
		while (ip == 1){	//Fundai
			puts ("Basic cost is $2000.\nPlease input odds selection. (a)x2 (b)x3 (c)x4\n>");
			fgets(ch, 2, stdin);
			if (ch <= 99 && ch >= 97) ip = 0;
			else {
				puts ("Please enter correct content!\n");
				ip=1;
			}
		}

		ip =1;
		while (ip == 1){	//Fundai
			puts("Please input front back selection. (f)front (b)back.\n>");
			fgets(ch2, 2, stdin);

			if (ch2 == 102){
				temp = 0;
				ip =0;
			}	//front(f)
			else if (ch2 == 98){
				temp = 1;
				ip=0;
			}	//back(b)
			else {
				puts("Please enter correct content!\n");
				ip =1;
			}
		}

		if (temp == coin){
			player->money += (2000*(ch-95));
			printf ("You Win!\nGet $%d.\n", (2000*(ch-95)));
		}
		else {
			player->money -= (2000*(ch-95));
			printf ("You Loose.\nLoose $%d.\n", (2000*(ch-95)));
		}

		if (round == 3) break;

		ip =1;
		while (ip =1){	//防呆
			puts("Do you want to play again? Enter 'Y' to continue, 'n' to leave the game.\n>");
			fgets(ch3, 2, stdin);
			if (ch3 == 89){
				playCondition = 1;
				round ++;
				ip =0;
			}
			else if (ch3 == 110){
				playCondition = 0;
				ip =0;
			}
			else {
				puts("Please enter correct content!\n");
				ip =1;
			}
		}
	}
}

void buy(struct Player* player, struct Building* b) {
	char buy_switch = 'y';
	switch (b[player->location].condition) {
		
		//land
		case -1:
			printf("Your current cash is %d.", player->money);
			puts("Are you going to buy the land?(only y/n):");
			fgets(buy_switch, 2, stdin);
			while (buy_switch != 'y' && buy_switch != 'n') {  //fool‑proof design
				puts("Are you going to buy the land?(only y/n):");
				fgets(buy_switch, 2, stdin);
			}
			if (buy_switch == 'y') {   //buy the land
				b[player->location].condition = 0;
				player->money -= b[player->location].buyPrice;
				b[player->location].owner = player->player_number;
				printf("Your current cash is %d.", player->money);
			}
			else {
				puts("What a shame! You didn't buy the land\n");
			}
			break;

		//flag
		case 0:
			//arrive the own flag
			if (b[player->location].owner == player->player_number) {

				//whether buy house on own flag
				printf("Your current cash is %d.", player->money);
				puts("Are you going to buy the house?(only y/n):");
				fgets(buy_switch, 2, stdin);

				//fool‑proof design
				while (buy_switch != 'y' && buy_switch != 'n') {
					puts("Are you going to buy the house?(only y/n):");
					fgets(buy_switch, 2, stdin);
				}

				if (buy_switch == 'y') {
					b[player->location].condition = 1;
					player->money -= b[player->location].buildPrice;
					printf("Your current cash is %d.", player->money);
				}
				else {
					puts("What a shame! You didn't buy the house\n");
				}
			}

			//arrive someone else's flag
			else {   
				printf("Your current cash is %d.", player->money);
				puts("Are you going to buy the land of your opponent?(only y/n):");
				fgets(buy_switch, 2, stdin);

				//fool‑proof design
				while (buy_switch != 'y' && buy_switch != 'n') {
					puts("Are you going to buy the land of your opponent?(only y/n):");
					fgets(buy_switch, 2, stdin);
				}

				//buy someone else's flag
				if (buy_switch == 'y') {
					b[player->location].owner = player->player_number;
					player->money -= b[player->location].finalPrice;
					printf("Your current cash is %d.", player->money);
				}

				//pay the fee
				else {
					puts("What a shame! You didn't buy the house\n");
					puts("Please pay the fee!\n");
					player->money -= b[player->location].fee;
					printf("Your current cash is %d.", player->money);
				}
			}
			
			break;

		//structure
		case 1: 
			//arrive the own estate
			if (b[player->location].owner == player->player_number) {
				puts("You arrive your own estate!\n");
				break;
			}

			//arrive someone else's structure
			else {
				printf("Your current cash is %d.", player->money);
				puts("Are you going to buy the estate?(only y/n):");
				fgets(buy_switch, 2, stdin);

				//fool‑proof design
				while (buy_switch != 'y' && buy_switch != 'n') {
					puts("Are you going to buy the estate?(only y/n):");
					fgets(buy_switch, 2, stdin);
				}

				//buy someone else's land
				if (buy_switch == 'y') {
					b[player->location].owner = player->player_number;
					player->money -= b[player->location].finalPrice;
					printf("Your current cash is %d.", player->money);
				}

				//pay the fee
				else {
					puts("What a shame!You didn't buy the house\n");
					puts("Please pay the fee!");
					player->money -= b[player->location].fee;
					printf("Your current cash is %d.", player->money);
				}
			}
			break;
	}
}

