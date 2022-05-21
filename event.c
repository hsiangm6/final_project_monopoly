#include "event.h"
#include<stdlib.h>
#include<time.h>
void event(struct Player* p1,struct Building* b){
	srand(time(NULL));
    switch(p1->location){
        case 5://jail
            p1->gameStatus = -1;
			break;
        case 2:
        case 11://draw cards
            draw(p1);
			break;
        case 9://casino
            casino(p1);
			break;
        case 14://go to start
            p1->location = 0;
            p1->money += 10000;
			break;
		case 0:
			break;
		default:
			buy(p1,b);
			break;
    }
}

void draw(struct Player* p1){
    card = rand() % 11;
    switch(card){
	case 0:
	case 1:
	case 2:
		printf("The newly hired supervisor has good performance management, increasing the overall turnover by %d NT dollars.\n", 1000 + card * 2000);
		p1-> money += 1000 + card * 2000;
		break;
	case 3:
	case 4:
	case 5:
		printf("You are unqualified by the health bureau, so you are fined %d NT dollars.\n", -(1000 + (card - 2) * 2000));
		p1-> money -= (1000 + (card - 2) * 2000);
		break;
	case 6:
		target = rand()% 18;
		printf("You get a ticket to broken Dokodemo Door, so you will be teleported to random location: %d\n", target);
		p1-> location = target;
		event(p1);
		break;
	case 7:
		printf("You become an honorary real estate tycoon, so the people invite you to the next location: %d", p1->location + 1)
		p1-> location += 1;
		event(p1);
		break;
	case 8:
		printf("You became a jewel thief and stole 50,000 worth of jewels, you were captured and deported from the country. \nYou are forced to go to the previous location: %d\n", p1->location - 1);
		p1-> location -= 1;
		event(p1);
		break;
	case 9:
		p1-> location = 5;
		event(p1);
		break;
	case 10:
		target=0;
		printf("You get a ticket to Dokodemo Door, please enter the location you want to go to (0 ~17)(only one chance to enter): "); 
		scanf_d("%d",target);
		if(target>=0 && target<=17){
			printf("You will be teleported to specified location: %d", target);
			p1-> location = target;
			event(p1);
		}
		break; 
	default:
		break;
    }
}

void casino (struct player* p1){
	char ch, ch2, ch3;
	int coin, temp, round=1, playCondition=1, ip;
	while (playCondition == 1){
		if (p1->money <2000){	//Do you have money?
			printf ("You don't have enough money!");
			break;
		}

		printf ("Welcom to Casino Game. This round %d. \n", round);
		coin = rand () % 2;	//random front back

		ip =1;
		while (ip == 1){	//Fundai
			printf ("Basic cost is $2000.\nPlease input odds selection. (a)x2 (b)x3 (c)x4\n>");
			scanf ("%c", &ch);
			getchar();	//clean scanf
			if (ch <= 99 && ch >= 97) ip = 0;
			else {
				printf ("Please enter correct content!\n");
				ip=1;
			}
		}

		ip =1;
		while (ip == 1){	//Fundai
			printf ("Please input front back selection. (f)front (b)back.\n>");
			scanf ("%c", &ch2);
			getchar();	//clean scanf

			if (ch2 == 102){
				temp = 0;
				ip =0;
			}	//front(f)
			else if (ch2 == 98){
				temp = 1;
				ip=0;
			}	//back(b)
			else {
				printf ("Please enter correct content!\n");
				ip =1;
			}
		}

		if (temp == coin){
			p1->money += (2000*(ch-95));
			printf ("You Win!\nGet $%d.\n", (2000*(ch-95)));
		}
		else {
			p1->money -= (2000*(ch-95));
			printf ("You Loose.\nLoose $%d.\n", (2000*(ch-95)));
		}

		if (round == 3) break;

		ip =1;
		while (ip =1){	//防呆
			printf ("Do you want to play again? Enter 'Y' to continue, 'n' to leave the game.\n>");
			scanf ("%c", &ch3);
			getchar();	//clean scanf
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
				printf ("Please enter correct content!\n");
				ip =1;
			}
		}
	}
}

void buy(struct Player* p1, struct Building* b) {
	char buy_switch = "y";
	switch (b[p1->location]->condition) {
		
		//land
		case -1:
			printf("Your current cash is %d.", p1->money);
			printf("Are you going to buy the land?(only y/n):");
			scanf("%c", buy_switch);
			while (buy_switch != "y" && buy_switch != "n") {  //fool‑proof design
				printf("Are you going to buy the land?(only y/n):");
				scanf("%c", buy_switch);
			}
			if (buy_switch == "y") {   //buy the land
				b[p1->location]->condition = 0;
				p1->money -= b[p1->location]->buyPrice;
				b[p1->location]->owner = p1->player_number;
				printf("Your current cash is %d.", p1->money);
			}
			else {
				printf("What a shame! You didn't buy the land\n")
			}
			break;

		//flag
		case 0:
			//arrive the own flag
			if (b[p1->location]->owner == p1->player_number) {  

				//whether buy house on own flag
				printf("Your current cash is %d.", p1->money);
				printf("Are you going to buy the house?(only y/n):");
				scanf("%c", buy_switch);

				//fool‑proof design
				while (buy_switch != "y" && buy_switch != "n") {  
					printf("Are you going to buy the house?(only y/n):");
					scanf("%c", buy_switch);
				}

				if (buy_switch == "y") {
					b[p1->location]->condition = 1;
					p1->money -= b[p1->location]->buildPrice;
					printf("Your current cash is %d.", p1->money);
				}
				else {
					printf("What a shame! You didn't buy the house\n");
				}
			}

			//arrive someone else's flag
			else {   
				printf("Your current cash is %d.", p1->money);
				printf("Are you going to buy the land of your opponent?(only y/n):");
				scanf("%c", buy_switch);

				//fool‑proof design
				while (buy_switch != "y" && buy_switch != "n") {  
					printf("Are you going to buy the land of your opponent?(only y/n):");
					scanf("%c", buy_switch);
				}

				//buy someone else's flag
				if (buy_switch == "y") {
					b[p1->location]->owner = p1->player_number;
					p1->money -= b[p1->location]->finalPrice;
					printf("Your current cash is %d.", p1->money);
				}

				//pay the fee
				else {
					printf("What a shame! You didn't buy the house\n")
					printf("Please pay the fee!\n");
					p1->money -= b[p1->location]->fee;
					printf("Your current cash is %d.", p1->money);
				}
			}
			
			break;

		//structure
		case 1: 
			//arrive the own estate
			if (b[p1->location]->owner == p1->player_number) {
				printf("You arrive your own estate!\n");
				break;
			}

			//arrive someone else's structure
			else {
				printf("Your current cash is %d.", p1->money);
				printf("Are you going to buy the estate?(only y/n):");
				scanf("%c", buy_switch);

				//fool‑proof design
				while (buy_switch != "y" && buy_switch != "n") {
					printf("Are you going to buy the estate?(only y/n):");
					scanf("%c", buy_switch);
				}

				//buy someone else's land
				if (buy_switch == "y") {
					b[p1->location]->owner = p1->player_number;
					p1->money -= b[p1->location]->finalPrice;
					printf("Your current cash is %d.", p1->money);
				}

				//pay the fee
				else {
					printf("What a shame! You didn't buy the house\n");
					printf("Please pay the fee!");
					p1->money -= b[p1->location]->fee;
					printf("Your current cash is %d.", p1->money);
				}
			}
			break;
	}
}

