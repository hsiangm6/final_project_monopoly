void event(struct Player*);
void draw(struct Player*);
void casino(struct Player*);
typedef struct Player
{
	int money;
	char *name;
	int location;
	int gamestatus = 0;
} Player;
typedef struct Building
{
	int buyPrice; // The price of occupying this place with a flag.
	int buildPrice; // The price of building this flag to the structure.
	int finalPrice; // The eventual price of this land.
	int fee;// The fee that the opponent being through be supposed to pay. 
	int buyPriceFromTheOpponent; // The price of this land buying from the opponent.
	int condition; // The current status of the land, 0 is a flag, while 1 is structure.
	int owner; // The land is occupied by whom.
} Building;
