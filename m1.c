//    IPC 144  MILESTONE 1  //
//    Student Name: QI BAO ZHENG //
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
char getTileType(unsigned int index)  // This fuction is for getting the type of the tile//
{
	char price;
	if (index == 0)
		price = 'C';
	else if (index % 3 == 0 && index % 7 != 0 && index % 5 != 0)
		price = 'W';
	else if (index % 7 == 0)
		price = 'G';
	else if (index % 5 == 0 && index % 7 != 0)
		price = 'L';
	else
		price = ' ';
	return price;
}
void displayboard(unsigned int size)
{
	int i, index;
	for (i = 0; i < size; i++)
	{
		{
			for (int a = 0; a < size; a++)                               //this for loop for  top: “ ___ “  //
				if (i > 0 && i < size - 1 && a>0 && a < size - 1)
					printf("     ");
				else
					printf(" ___ ");
		}
		printf("\n");
		for (int b = 0; b < size; b++)                  // this for loop for print the  Middle: “| ? |”   //
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
				printf("| %c |", getTileType(index));
		}
		printf("\n");
		for (int c = 0; c < size; c++)                              //this for loop for “|___| //
		{
			if (i > 0 && i < size - 1 && c>0 && c < size - 1)     // print the middle empty space //
				printf("     ");
			else
				printf("|___|");
		}
		printf("\n");
	}
}
int main(void)
{
	int s = 1;
	if (getTileType(153) != 'W') printf("153 should return W");      // These are for test the program //
	else if (getTileType(65) != 'L') printf("65 should return L");
	else if (getTileType(49) != 'G') printf("49 should return G");
	else if (getTileType(0) != 'C') printf("0 should return C");
	else if (getTileType(105) != 'G') printf("105 should be G");
	else if (getTileType(79) != ' ') printf("79 should be space");
	else
	{
		printf("getTileType test passed!\nEnter board size: ");
		scanf("%d", &s);
		displayboard(s);	}
	return 0;
}