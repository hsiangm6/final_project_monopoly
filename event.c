#include "event.h"
#include<stdlib.h>
void event(struct Player* p1){
    switch(p1->location){
        case 5://jail
            p1->gamestatus = -1 ;
        case 2:
        case 11://draw cards
            draw(p1);
        case 9://casino
            casino(p1);
        case 14://go to start
            p1->location = 0;
            p1->money += 10000;
            
    }
}

void draw(struct Player* p1){
    card = rand() % 11;
    switch(card){
	case 0:
	case 1:
	case 2:
		p1-> money += 1000 + card * 2000;
	case 3:
	case 4:
	case 5:
		p1-> money += 1000 - (card - 3) * 2000;
	case 6:	    
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
