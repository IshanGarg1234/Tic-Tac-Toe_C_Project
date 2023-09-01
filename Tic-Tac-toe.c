#include<stdio.h>
#include<stdbool.h>

void printBoard(char board[])
{
	printf(" %c | %c | %c \n",board[0],board[1],board[2]);
	printf("---+---+---\n");
	printf(" %c | %c | %c \n",board[3],board[4],board[5]);
	printf("---+---+---\n");
	printf(" %c | %c | %c \n",board[6],board[7],board[8]);
	printf("\n");
}

bool hasWon(char board[],int index,char player)
{
	int row = index/3;
	int col = index%3;
	
	if(board[3*row] == player && board[3*row+1] == player && board[3*row+2] == player)
	{
		return true;
	}
	else if(board[col] == player && board[3+col] == player && board[6+col] == player)
	{
		return true;
	}
	else if(board[0] == player && board[4] == player && board[8] == player)
	{
		return true;
	}
	else if(board[2] == player && board[4] == player && board[6] == player)
	{
		return true;
	}
	return false;
	
}

int max(int a,int b)
{
	int ans =(a>b)?a:b;
	return ans;
}

int min(int a,int b)
{
	int ans =(a>b)?b:a;
	return ans;
}

int validIntInput(char player,char line[],int s,int e)
{
	int i;
	while(1)
	{
		if(line == "index")
		{
			printf("For undo Enter 0\n");
		}
		if(line == "index" || line == "turn")
		{
			printf("Player %c turn\n",player);
			printf("Enter %s\n",line);
		}
		
		if(scanf("%d",&i)==1)
		{
			if(i>=s && i<=e)
			{
				break;
			}
			else{
				printf("Enter the valid %s range (%d - %d)\n",line,s,e);
			}

		}
		else
		{
			int c;
			while((c = getchar())!='\n');
			printf("Enter the valid %s range (%d - %d)\n",line,s,e);
		}
	}	
	return i;
}

int minimax(char board[],char player,int index,int count)
{
	char prevPlayer = (player=='X')?'O':'X';
	bool won = hasWon(board,index,prevPlayer);
	
	if(won)
	{
		return (prevPlayer == 'X')?1:-1;
	}
	
	if(count == 9)
	{
		return 0;
	}
	
	if(player == 'X')
	{
		int bestScore = -1;
		for(int i=0;i<9;i++)
		{
			if(board[i] == ' ')
			{
				board[i] = player;
				int score = minimax(board,'O',i,count+1);
				board[i] = ' ';
				bestScore = max(bestScore,score);
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = 1;
		for(int i=0;i<9;i++)
		{
			if(board[i] == ' ')
			{
				board[i] = player;
				int score = minimax(board,'X',i,count+1);
				board[i] = ' ';
				bestScore = min(bestScore,score);
			}
		}
		return bestScore;
	}	
}

int AI(char board[],char player,int count)
{	
	if(player == 'X')
	{
		int bestScore = -2;
		int index = -1;
		for(int i=0;i<9;i++)
		{
			if(board[i] == ' ')
			{
				board[i] = 'X';
				int score = minimax(board,'O',i,count+1);
				board[i] = ' ';
				
				if(score > bestScore)
				{
					bestScore = score;
					index = i;
				}
			}
		}
		return index;
	}
	else
	{
		int bestScore = 2;
		int index = -1;
		for(int i=0;i<9;i++)
		{
			if(board[i] == ' ')
			{
				board[i] = 'O';
				int score = minimax(board,'X',i,count+1);
				board[i] = ' ';
				
				if(score < bestScore)
				{
					bestScore = score;
					index = i;
				}
			}
		}
		return index;
	}
}


int main()
{
	printf("Do You want to play with Computer(1) or Player(2)\n");
	int game = validIntInput('X',"game",1,2);
	
	char history[9][9];
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			history[i][j] = ' ';
		}
	}
		
	char board[9];
	for(int i=0;i<9;i++)
	{
		board[i] = ' ';
	}

	char player='X';
	int count = 0;
	bool won = false;
		
	
	if(game == 1)
	{
		printf("Enter your player X(1) or O(2)\n");
		int playerIndex = validIntInput('O',"playerIndex",1,2);
		
		char ai = (playerIndex == 1)? 'O':'X';
		char human = (playerIndex == 1)? 'X':'O';
		
		printBoard(board);
		
		while(!won && count < 9)
		{
			int i;
			if(player == ai)
			{
				i = AI(board,ai,count);
			}
			else if(player == human)
			{
				i = validIntInput(player,"index",0,9);
		
				if(i == 0)
				{
					int turn = validIntInput(player,"turn",0,count);
					for(int i=0;i<9;i++)
					{
						board[i] = history[turn][i];
					}
					count = turn;
					player = (count%2)==0 ? 'X':'O';
					printBoard(board);
					continue;
				}
				
				i=i-1;
				
				if(board[i]!=' ')
				{
					printf("space is already filled\n\n");
					printBoard(board);
					continue;
				}
			}
			
			board[i] = player;
			
			won = hasWon(board,i,player);
			
			if(count<8)
			{
				for(int i=0;i<9;i++)
				{
					history[count+1][i] = board[i];
				}
			}
			
			printBoard(board);
			
			if(won)
			{
				printf("player %c Won\n" ,player);
				break;
			}
			
			player = (player == 'X')?'O':'X';
			count++;
		}
	}
	
	else
	{	
		printBoard(board);
		while(!won && count < 9)
		{		
			int i = validIntInput(player,"index",0,9);
			
			if(i == 0)
			{
				int turn = validIntInput(player,"turn",0,count);
				for(int i=0;i<9;i++)
				{
					board[i] = history[turn][i];
				}
				count = turn;
				player = (count%2)==0 ? 'X':'O';
				printBoard(board);
				continue;
			}
			
			i=i-1;
			
			if(board[i]!=' ')
			{
				printf("space is already filled\n\n");
				printBoard(board);
				continue;
			}
			
			board[i] = player;
			won = hasWon(board,i,player);
			
			if(count<8)
			{
				for(int i=0;i<9;i++)
				{
					history[count+1][i] = board[i];
				}
			}
			
			printBoard(board);
			
			if(won)
			{
				printf("player %c Won\n" ,player);
				break;
			}
			
			player = (player == 'X')?'O':'X';
			count++;
		}	
	}
	
	if(!won)
	{
		printf("Game Draw\n");
	}
	printf("Game End\n");
}


