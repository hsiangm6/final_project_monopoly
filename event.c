#include "event.h"
#include<stdlib.h>
void event(struct Player* p1){
    switch(p1->location){
        case 5://jail
            p1->gamestatus = -1 ;
        case 2:
        case 11://draw cards
            draw(&p1);
        case 9://casino
            casino(&p1);
        case 14://go to start
            p1->location = 0;
            p1->money += 10000;
            
    }
}

void draw(struct Player** p1){
    card = rand() % 10;
    switch(card){
        
    }
}

void casino(struct Player** p1){
    
}
