//    IPC 144  MILESTONE 2  //
//    Student Name: QI BAO ZHENG //
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
char getTileType(unsigned int index, unsigned int playerPosition, char playerName)  // This fuction is for getting the type of the tile//
{
	char tile;
	if (index == 0)
	{
		if (playerPosition == index)            // return the player name when posiotion == index //
			tile = playerName;
		else
			tile = 'C';
	}
	else if (index % 3 == 0 && index % 7 != 0 && index % 5 != 0)
	{
		if (playerPosition == index)
		{
			tile = playerName;
		}
		else
			tile = 'W';
	}
	else if (index % 7 == 0)
	{
		if (playerPosition == index)
			tile = playerName;
		else
			tile = 'G';
	}
	else if (index % 5 == 0 && index % 7 != 0)
	{
		if (playerPosition == index)
			tile = playerName;
		else
			tile = 'L';
	}
	else if (index % 3 != 0 && index % 7 != 0 && index % 5 != 0)
	{
		if (playerPosition == index)
			tile = playerName;
		else
			tile = ' ';
	}
	return tile;
}
void displayboard(unsigned int size, unsigned int playerPosition, char playerName)
{
	int i, index;
	playerPosition = playerPosition % ((size - 1) * 4);           // calculate the player position should be on the board //
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
				printf("| %c |", getTileType(index, playerPosition, playerName));
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
int getValidInteger(int low, int high)   // 1 - 3 //
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
int getRandom(int low, int high)   // 1 - 6 //
{
	int random = low + rand() % (high + 1 - low);
	return random;
}
unsigned int playerRoll()  // get the toal number //
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
char getValidCharacter(char low, char high)   // get the charater name from low index character ~ high index character //
{
	char c = ' ';
	printf("Enter player ID: ");
	while (c > high || c < low)
	{
		scanf("%c", &c);   
		while (getchar() != '\n');
	}
	return c;
}
void winPrize(int playerPrizes[], unsigned int* prizeCount)
{
	(*prizeCount)++;
	int add = 10 + rand() % (100 + 1 - 10);               
	printf("you won a prize of %d\n", add);
	int i;
	for (i = 0; i < 10; i++)
		if (playerPrizes[i] == 0)               // add the prize  when the playerprizes[i] elemoent is 0 //
		{
			playerPrizes[i] = add;
			break;
		}
		
}
void winGrandPrize(int playerPrizes[], unsigned int* prizeCount)
{
	(*prizeCount)++;
	int add = 100 + rand() % (200 + 1 - 100);
	printf("you won a grand prize of %d\n", add);
	int i;
	for ( i = 0; i < 10; i++)
		if (playerPrizes[i] == 0)
		{
			playerPrizes[i] = add;            // add the prize when the palyerprizes[i] elemoent is 0 //
			break;
		}
}
int loseItem(int playerPrizes[], unsigned int* prizeCount)   // lose item fuction //
{
	int i = 0;
	printf("You lose an item\n");
	if (*prizeCount > 0)
	{
		(*prizeCount)--;
		while (i < 10)
		{
			i = getRandom(0, 9);         // chose random nuber from 0 - 9 if the prizes[0-9] is > 0 return the element nuber then set to 0 //
			if (playerPrizes[i] > 0)
				break;
		}
	}
	return i;  
}
int checkout(int* playerScore, int playerPrizes[], unsigned int* prizeCount)
{
	int win;
	*prizeCount = 0;
	int i;
	for ( i = 0; i < 10; i++)
	{
		*playerScore += playerPrizes[i];
	}
	if (*playerScore >= 200)    // check out when scroe >= 200 return true //
		win = 1;
	else
		win = 0;          // else return false //
	printf("You checkedout for $%d score is now: $%d\n", *playerScore, *playerScore);
	return win;
}
void playGame(unsigned int boardSize, int *playerScore, int playerPrizes[],unsigned int* prizeCount, char * playerName, int* playerPosition)
{
	char step = 'a';
	int lose;
	int position = *playerPosition;
	while (*prizeCount <= 10 && step != 'C')
	{
		displayboard(boardSize, position, *playerName);                              // display board //
		printf("scroe : %d  invantory(%d items): ", *playerScore, *prizeCount);
		int i;
		for ( i = 0; i < 10; i++)                  // displayer the item index //
		{
			if (playerPrizes[i] > 0)
			{
				printf("%d ", playerPrizes[i]);
			}
		}
		printf("\n");
		*playerPosition+= playerRoll();
		position = (*playerPosition) % ((boardSize - 1) * 4);    // calculate the posiont for win or lose price //
		if (position == 0 || *prizeCount == 10)
		{

			*prizeCount = 0;
			*playerPosition = 0;
			if ((checkout(playerScore, playerPrizes, prizeCount)) == 1)
				printf("You won the game!\n");
			else
				printf("You lose\n");
			step = 'C';
		}
		else if (position % 3 == 0 && position % 5 != 0 && position % 7 != 0)
		{
			winPrize(playerPrizes, prizeCount);
		}
		else if (position % 5 == 0 && position % 7 != 0)
		{
			lose = loseItem(playerPrizes, prizeCount);
			playerPrizes[lose] = 0;
		}
		else if (position % 7 == 0)
		{
			winGrandPrize(playerPrizes, prizeCount);
		}
		else if (position % 7 != 0 && position % 5 != 0 && position % 3 != 0)
			printf("Nothing happen go again.\n");
	}
}
void initPlayer(int* playerScore, int playerPrizes[], unsigned int *prizeCount, char * playerName, int* playerPosition)  // intitial the player infor all to 0 //
{
	*playerScore = 0;
	int i;
	for ( i = 0; i < 10; i++)
		playerPrizes[i] = 0;
	*prizeCount = 0;
	*playerName = '?';
	*playerPosition = 0;
}
int main(void)
{
	srand(time(NULL));
	int prizeCount = 0;
	char select='a';
	int score = 0;
	int highscore = 0;       // store the high scroe //
	int position = 0;
	int playerPrizes[10] = { 0,0,0,0,0,0,0,0,0,0 };
	char playerName = '?';
	char highplayer = '?';   // store the hight scroe player name //
	printf("Welcome to CHECKOUT\n");
	while (select != 'q')
	{
		int boardSize = 0;
		printf("Main Menu\n\n");
		printf("p-(p)lay q-(q)uit r-inst(r)uctions s-HI(s)core:\n");
		scanf("%c", &select);
		while (getchar() != '\n');
		if (select == 'p')                  // play game //
		{
			initPlayer(&score, playerPrizes, &prizeCount, &playerName, &position);
			printf("Number of Players is 1 \n");
			playerName = getValidCharacter('!', '~');
			printf("Enter Board Size: ");
			scanf("%d", &boardSize);
			while (getchar() != '\n');
			playGame(boardSize, &score, playerPrizes, &prizeCount, &playerName, &position);
			if (score > highscore)
			{
				highscore = score;
				highplayer = playerName;
			}
		}
		else if (select == 's')            // check out //
		{
			printf("__\n");
			printf("  \\_______ \n");
			printf("   \\++++++|\n");
			printf("    \\=====|\n");
			printf("    0---  0\n");
			printf("HI SCORE: %d Player Name: %c\n", highscore, highplayer);
		}
		else if(select!='q'&&select!='p'&&select!='r')
			printf("Invalid Input\n");
		else if (select == 'r')                                // instructions //
		{
			printf("Full Game Rules: \n");
			printf("   - Up to 8 players compete to be the first to obtain $1000\n ");
			printf("  - Game takes place on a square board with 5 tile types\n");
			printf("        Empty Tile – No effect\n");
			printf("        Win Tile – Win a random prize\n");
			printf("        Lose Tile – Lose a random prize\n");
			printf("        Grand Prize Tile – Win a grand prize\n");
			printf("        Checkout Tile – Sells all your prizes for cash\n");
			printf("   - Players can roll 1 - 3 dice to determine how many tiles they move each turn\n");
			printf("   - If a player lands on the same tile as another player, that player steals a prize and moves 1 tile back \n");
		}
	}
	printf("This game is much more fun than bash...\n");
	return 0;
}
