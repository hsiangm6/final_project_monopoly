#include "event.h"

int event(Player* p1){
    switch(p1->location){
        case 5://jail
            p1->gamestatus = -1 ;
        case 2:
        case 11://draw cards
            draw();
        case 9://casino
            casino();
        case 14://go to start
            p1->location = 0;
            p1->money += 10000;
    }
}
