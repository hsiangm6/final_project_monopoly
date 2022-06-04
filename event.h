typedef struct
{
	int money;   //current cash
	char *name;   //player name
	int location;   //player location
	int gameStatus;   //check whether the player is in jail now
	int player_number;   //player number
	int debt_counter;   //count the number of rounds in which the player is continuously in debt
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

void event(Player* player, Player* receive, Building *b,char **landmark, char **building);   //activity in monopoly
void draw(Player *player, Player* receive, Building *b, char **landmark, char **building);   //chance
void casino(Player *player);   //casino game
void casinoCoin (Player *player);	//casino coin game
void casinoPirate (Player *player);	//casino pirate game
void buy(Player *player, Player* receive, Building *b, char **landmark, char **building);   //purchase behaviour
void buildingStructure(Building *b);   //Real estate purchase price, market value, toll
