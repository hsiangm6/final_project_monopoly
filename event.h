typedef struct
{
	int money;
	char *name;
	int location;
	int gameStatus;
	int player_number;

} Player;

typedef struct
{
	int owner; // The land is occupied by whom, 1 is for player 1, 2 is for player 2, 0 is colonized by no one.
	int condition; // The current status of the land, 0 is a flag, 1 is structure, while -1 is the place.
	int buyPrice; // The price of occupying this place with a flag.
	int buildPrice; // The price of building this flag to the structure.
	int finalPrice; // The eventual price of this land.
	int fee; // The fee that the opponent being through be supposed to pay.
	int buyPriceFromTheOpponent; // The price of this land buying from the opponent.

} Building;

void event(Player* player, Player* receive, Building *b,char landmark[], char building[]);
void draw(Player *player, Player* receive, Building *b, char landmark[], char building[]);
void casino(Player *player);
void buy(Player *player, Player* receive, Building *b, char landmark[], char building[]);
void buildingStructure(Building *b);

