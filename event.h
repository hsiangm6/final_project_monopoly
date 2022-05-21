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
