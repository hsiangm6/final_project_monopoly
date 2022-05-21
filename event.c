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
		printf("You get a ticket to broken Dokodemo Door, so you will be teleported to random location: %d", target);
		p1-> location = target;
		event(p1);
		break;
	case 7:
		p1-> location += 1;
		event(p1);
		break;
	case 8:
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
	char ch, ch2;
	int coin, temp;
	coin = rand () % 2;	//random front back
	printf ("Spend $2000 playing game.\n");
	printf ("Input odds selection. (a)x2 (b)x3 (c)x4\n>");
	scanf ("%c", &ch);
	getchar();	//clean scanf
	printf ("Input front back selection. (f)front (b)back.\n>");
	scanf ("%c", &ch2);
	if (ch2 == 102) temp = 0;	//front(f)
	if (ch2 == 98) temp = 1;	//back(b)

	if (temp == coin){
		p1->money += (2000*(ch-95));
		printf ("You Win!\nGet $%d.", (2000*(ch-95)));
	}
	else {
		p1->money -= 2000;
		printf ("You Loose.\nLoose $2000.");
	}
}
