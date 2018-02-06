//    IPC 144  MILESTONE 3  //
//    Student Name: QI BAO ZHENG //
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define max 8
struct play{
	int invantory;
	int score;
	int position;
	int playerPrizes[10];
	char playerName;
	char name[35];
};
void displayInstructions(void)
{
	printf("        ********************\n           Full Game Rules\n        ******************** \n");
	printf("   - Up to 8 players compete to be the first to obtain $500\n ");
	printf("  - Game takes place on a square board with 5 tile types\n");
	printf("        Empty Tile ' ' No effect\n");
	printf("        Win Tile 'W'  Win a random prize\n");
	printf("        Lose Tile 'L' Lose a random prize\n");
	printf("        Grand Prize Tile 'G' Win a grand prize\n");
	printf("        Checkout Tile 'C' Sells all your prizes for cash\n");
	printf("   - Players can roll 1 - 3 dice to determine how many tiles they move each turn\n");
	printf("   - If a player lands on the same tile as another player, that player steals a prize and moves 1 tile back \n");

}
char getTileType(unsigned int index, struct play player[], int playercount)  // This fuction is for getting the type of the tile//
{
	char tile;
	int position;
	char name;
	int i;
	for (i = 0; i < playercount; i++)      // for loop for check the players position //
	{
		if (index == 0)
		{
			if (player[i].position == index)
			{                       
				tile = player[i].playerName;
				break;                        // if found the first player at the tile break //
			}
			else
				tile = 'C';
		}
		else if (index % 3 == 0 && index % 7 != 0 && index % 5 != 0)
		{
			if (player[i].position == index)
			{
				tile = player[i].playerName;
				break;
			}
			else
				tile = 'W';
		}
		else if (index % 7 == 0)
		{
			if (player[i].position == index)
			{
				tile = player[i].playerName;
				break;
			}
			else
				tile = 'G';
		}
		else if (index % 5 == 0 && index % 7 != 0)
		{
			if (player[i].position == index)
			{
				tile = player[i].playerName;
				break;
			}
			else
				tile = 'L';
		}
		else if (index % 3 != 0 && index % 7 != 0 && index % 5 != 0)
		{
			if (player[i].position == index)
			{
				tile = player[i].playerName;
				break;
			}
			else
				tile = ' ';
		}
	}
	return tile;
}
void displayboard(unsigned int size,struct play player[], int playercount)
{
	int i, index;
	int n;
	for (n = 0; n < playercount; n++)
	{
		player[n].position = player[n].position % ((size - 1) * 4);           // calculate the player position should be on the board //
	}
	for (i = 0; i < size; i++)
	{
		{
			int a;
			for ( a = 0; a < size; a++)                               //this for loop for  top:  ___  //
				if (i > 0 && i < size - 1 && a>0 && a < size - 1)
					printf("     ");
				else
					printf(" ___ ");
		}
		printf("\n");
		int b;
		for ( b = 0; b < size; b++)                  // this for loop for print the  Middle: | ? |  //
		{
			if (i == 0)                // this is getting the first line  index //
				index = b;


			else if (i == size - 1)     // this is getting the last line index
				index = 3 * (size - 1) - b;


			else if (i > 0 && i < size - 1)       // this is getting the middle line index //
			{
				if (b == 0)
					index = 4 * (size - 1) - i;
				else if (b == size - 1)
				{
					index = size - 1 + i;
				}
			}
			if (i > 0 && i < size - 1 && b>0 && b < size - 1)     // print the middle empty space //
				printf("     ");
			else
				printf("| %c |", getTileType(index, player,playercount));
		}
		printf("\n");
		int c;
		for ( c = 0; c < size; c++)                              //this for loop for |___| //
		{
			if (i > 0 && i < size - 1 && c>0 && c < size - 1)     // print the middle empty space //
				printf("     ");
			else
				printf("|___|");
		}
		printf("\n");
	}
}
int getValidInteger(int low, int high)   // Roll the dices must be 1 - 3 //
{
	int number;
	printf("your turn, how many dice will you roll? ");
	do {
		scanf("%d", &number);
		while (getchar() != '\n');
		if (number > high || number < low)
			printf("Invalid input, try again: ");
	} while (number > high || number < low);
	return number;
}
int getRandom(int low, int high)   // dice number must be 1 - 6 //
{
	int random = low + rand() % (high + 1 - low);
	return random;
}
unsigned int playerRoll()  // get the dices roll toal number //
{
	int total = 0;
	int number;
	int dices = getValidInteger(1, 3);
	printf("You rolled:");
	int i;
	for ( i = 0; i < dices; i++)
	{
		number = getRandom(1, 6);
		printf("%d ", number);
		total += number;
	}
	printf("\n");
	printf("Advancing %d spaces\n", total);
	return total;


}
void winPrize(struct play* player)
{
	if (player->invantory < 10)
	{
		(player->invantory)++;
		int add = 10 + rand() % (100 + 1 - 10);
		printf("you won a prize of %d\n", add);
		int i;
		for (i = 0; i < 10; i++)
			if (player->playerPrizes[i] == 0)               // add the prize  when the playerprizes[i] is 0 //
			{
				player->playerPrizes[i] = add;
				break;
			}
	}
	else {
		printf("Invantory is full\n");
	}
}
void winGrandPrize(struct play* player)
{
	if (player->invantory < 10)
	{
		(player->invantory)++;
		int add = 100 + rand() % (200 + 1 - 100);
		printf("you won a grand prize of %d\n", add);
		int i;
		for (i = 0; i < 10; i++)
			if (player->playerPrizes[i] == 0)
			{
				player->playerPrizes[i] = add;            // add the prize when the palyerprizes[i] elemoent is 0 //
				break;
			}
	}
	else {
		printf("Invantory is full\n");
	}
}
int loseItem(struct play* player)   // lose item fuction //
{
	int i = 0;
	if (player->invantory > 0)
	{
		(player->invantory)--;
		while (i < 10)
		{
			i = getRandom(0, 9);         // chose random nuber from 0 - 9 if the prizes[0-9] is > 0 return the element nuber then set to 0 //
			if (player->playerPrizes[i] > 0)
				break;
		}
	}
	else                                           // when the player dont have items //
	{
		printf("Player %c has no items nothing lose\n",player->playerName);
		i = -1;
	}
	return i;  
}
int checkout(struct play* player)
{
	player->invantory = 0;
	int i;
	int total = 0;
	printf("__\n");
	printf("  \\_______ \n");
	printf("   \\++++++|\n");
	printf("    \\=====|\n");
	printf("    0---  0\n");
	for ( i = 0; i < 10; i++)                          // add all the score //
	{
		player->score += player->playerPrizes[i];
		total += player->playerPrizes[i];
		player->playerPrizes[i] = 0;
	}
	printf("Player %s (%c) checkedout for $%d score \n",player->name, player->playerName, total);
	return player->score;
}
void playGame(unsigned int boardSize, struct play players[], unsigned int playerCount)
{
	char check = 'D';  // display board //
	int position = 0;
	while (check != 'C')
	{
		int i;
		for ( i = 0; i < playerCount; i++)
		{
			displayboard(boardSize, players, playerCount);   // display board //
			printf("scroe of player %s (%c) is : %d\nInvantory( %d items):",players[i].name,players[i].playerName, players[i].score, players[i].invantory);// print current inventory//
			int n;
			for ( n = 0; n < 10; n++)
			{
				if (players[i].playerPrizes[n] > 0)            // printf invantory item .//
					printf(" %d", players[i].playerPrizes[n]);
			}
			printf("\n");
			position = players[i].position;    // position for check when the player return back is equal original poistion or not //

			players[i].position += playerRoll();  // player position //
			for (n = 0; n < playerCount; n++)   // this loop for check the moving player lande the same tile with the other or not //
			{
				if (players[i].position == players[n].position && n != i)
				{
					if (players[i].position == 0)
					{
						players[i].position = (boardSize - 1) * 4 - 1; 
					}
					else
					{
						(players[i].position)--;
					}
					printf("You steal item from %c\n", players[n].playerName);   // if the move player lane the same tile with the others //
					int steal = loseItem(&players[n]);    // check the other player has an item or not //
					if (steal > -1)                    // if the other player has a item //
					{
						(players[i].invantory)++;         // player ivantory increase //
						int a;
						for (a = 0; a < 10; a++)
						{
							if (players[i].playerPrizes[a] == 0)    // add the item in the empty space //
							{
								players[i].playerPrizes[a] = players[n].playerPrizes[steal];
								break;
							}
							else if (a == 10)                   // if invatory is full //
								printf("Invantory is full\n");
						}
						players[n].playerPrizes[steal] = 0;      // set the other player item become 0 //
					}
					n = 0;
				}
			}
			if(players[i].position == position)
			{
				printf("Back to original place nothing happen \n");
			}
			else if ((players[i].position % ((boardSize - 1) * 4)) == 0)      // check out //
			{
				if (checkout(&players[i]) >= 500)             // player score > 200 win the game , else add the prize then contaniu the game//
				{
					printf("Congratulations %s (%c)! You win!\n", players[i].name, players[i].playerName);
					check = 'C';
					break;
				}

			}
			else if (players[i].position % 3 == 0 && players[i].position != 0 && players[i].position % 7 != 0)   // win prize //
				{
					winPrize(&players[i]);
				}
			else if (players[i].position % 5 == 0 && players[i].position % 7 != 0)      // lose a prize //
				{
					printf("You lose an item\n");
					int lose = loseItem(&players[i]);
					if (lose > -1) {
						players[i].playerPrizes[lose] = 0;
					}
				}
			else if (players[i].position % 7 == 0)      // win a grand prize //
				{
					winGrandPrize(&players[i]);
				}
			else if (players[i].position % 7 != 0 && players[i].position % 5 != 0 && players[i].position % 3 != 0)    // nothing happen //
					printf("Nothing happen go again.\n");
			
		}
	}
} 
void initPlayer(struct play* player)  // intitial the players infor all to 0 //
{
	printf("Please enter player name : ");
	gets(player->name);
	printf("player ID:");
	scanf("%c", &player->playerName);
	while (getchar() != '\n');
	player->invantory = 0;
	player->score = 0;
	player->position = 0;
	int i;
	for (i = 0; i < 10; i++)
		player->playerPrizes[i] = 0;
}
struct read      // create this struct for read the data //
{
	char game[10];
	char name[35];
	char id[5];
	char dash[5];
	int score;
};
void displayHighestScore(void)    // read the data //
{
	struct read data[100];
	int i = 0;
	int high;
	int check = 0;
	FILE* fp;
	if (fp = fopen("Leaderboard.dat", "r") == NULL)
	{
		fprintf(stderr,"Can not open the file \n");
	}
	else
	{
          	printf("*****************************\nPlayer With the Highest Score\n*****************************\n");
	       	printf("PlayerName       ID       Score\n");
		fp = fopen("Leaderboard.dat", "r");
		while (1)
		{
			fscanf(fp, "%[^ ] %[^(]%[^ ]%[^0-9]%d", &data[i].game[i], &data[i].name, &data[i].id, &data[i].dash[i], &data[i].score);
			i++;
			if (feof(fp))
				break;
		}
		fclose(fp);
		int n;
		for (n = 0; n < i; n++)
		{
			if (data[n].score > check)
			{
				check = data[n].score;
				high = n;
			}
		}
		printf("%s %8s%10d\n", data[high].name, data[high].id, data[high].score);
	}
}
void addToLeaderboard(int game, struct play* winner)     // save the data for the winner //
{
	FILE* fp;
	fp = fopen("Leaderboard.dat", "a");
	fprintf(fp, "Game:%d %s (%c) -%d\n", game, winner->name, winner->playerName, winner->score);
	fclose(fp);
}
int main(void)
{
	srand(time(NULL));
	int game = 0;
	int id = 0;
	struct play player[8];
	int playercount;
	char select = 'a';       // store the high scroe //
	char highplayer = '?';   // store the hight scroe player name //
	printf("Welcome to CHECKOUT\n");
	while (select != 'q')
	{
		int boardSize = 0;
		printf("Main Menu\n\n");
		printf("p-(p)lay q-(q)uit r-inst(r)uctions s-HI(s)core:\n");
		scanf("%c", &select);
		while (getchar() != '\n');  // clear the input buffer //
		if (select == 'p')     // play game //
		{
			int highscore = 0;
			printf("Please enter number of players: ");
			scanf("%d", &playercount);
			while (getchar() != '\n');
			printf("Number of players is %d\n", playercount);
			int i;
			for ( i = 0; i < playercount; i++)
			{
				printf("Please enter play %d Name and ID \n", i + 1);
				initPlayer(&player[i]);
			}
			printf("Enter board size:");
			scanf("%d",&boardSize);
			while( boardSize < 5 || boardSize > 15)    // make the board size big than the players //
			{
			printf("The boardSize must between 5 - 15 ");
			scanf("%d", &boardSize);
			}
			playGame(boardSize, player, playercount);
			game++;
			for (i = 0; i < playercount; i++)
			{
				if (player[i].score > highscore)
				{
					highscore = player[i].score;
					id = i;
				}
			}
			addToLeaderboard(game, &player[id]);
		}
		else if (select == 's')    // display high score player and score //
		{
			displayHighestScore();
		}
		else if (select != 'q'&&select != 'p'&&select != 'r')
			printf("Invalid Input\n");
		else if (select == 'r')                     // instrution //
		{
			displayInstructions();
		}
	}
	printf("This game is much more fun than bash...\n");
	return 0;
}
