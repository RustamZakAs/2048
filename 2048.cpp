#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>

using namespace std;

const short size_i = 4, size_j = 4;
short arr2048[size_i][size_j] = {8,16,128,32,
				2,8,32,16,
				4,0,4,0,
				4,0,0,0};

short arr2048_2[size_i][size_j] = {0,0,0,0,
				   0,0,0,0,
				   0,0,0,0,
				   0,0,0,0};
short arr_help[2] = {2,4};

short temp = 0;
short key = 0;
short max_ij = 0;
int best_score = 0;
int score = 0;

void SetColor(short color)		//Цвет
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, color);
}

void start_game(short arr2048[size_i][size_j]);
void draw_game(short arr[size_i][size_j]);
void move_game(short arr2048[size_i][size_j], short key);
void chech_add_element(short arr2048[size_i][size_j]);
void chech(short arr2048[size_i][size_j]);

void move_up(short arr2048[size_i][size_j]);
void move_down(short arr2048[size_i][size_j]);
void move_left(short arr2048[size_i][size_j]);
void move_right(short arr2048[size_i][size_j]);

int main() {
	srand(time(0));
	score = 0;
	for (short i = 0; i < size_i; i++) {
		for (short j = 0; j < size_j; j++) {
			arr2048[i][j] = 0;
		}
	}
	start_game(arr2048);
	do {
		for (short i = 0; i < size_i; i++)
		{
			for (short j = 0; j < size_j; j++)
			{
				arr2048_2[i][j] = arr2048[i][j];
			}
		}
		draw_game(arr2048);
		//chech(arr2048);
		do{
			key = getch();
		} while (key == 224);
		cout << key;
		cout << "\n\nColculate";
		for (short i = 0; i < 7; i++)
		{
			cout << ".";
			Sleep(27);
		}
		move_game(arr2048, key);
		chech_add_element(arr2048);
	} while (true);
}

void chech(short arr2048[size_i][size_j]) {
	short count = 0;
	for (short i = 0; i < size_i; i++)
	{
		for (short j = 0; j < size_j; j++)
		{
			if (arr2048[i][j] != arr2048[i+1][j])
			{
				count++;
			}
			else if (arr2048[i][j] != arr2048[i][j+1])
			{
				count++;
			}
		}
	}
	if (count == size_i*size_j)
	{
		cout << "Game win !";
		system("pause");
		main();
	}
	return;
}

void chech_add_element(short arr2048[size_i][size_j]) {
	short count = 0;
	for (short i = 0; i < size_i; i++)
	{
		for (short j = 0; j < size_j; j++)
		{
			if (arr2048_2[i][j] != arr2048[i][j]) 
			{
				start_game(arr2048);
				return;	
			}
			if (arr2048[i][j] != 0)
			{
				count++;
			}
		}
	}
	if (count == size_i*size_j) cout << "Game win !";
	return;
}

void start_game(short arr2048[size_i][size_j]) {
	short rand_row = 0, rand_col = 0, element = 0;
	do
	{
		rand_row = rand()%4;
		rand_col = rand()%4;
		element = arr2048[rand_row][rand_col];
		if (arr2048[rand_row][rand_col] == 0)
		{
			arr2048[rand_row][rand_col] = arr_help[rand()%2];
		}
	} while (element != 0);
//  arr2048[0][0] = 2;
//	arr2048[1][0] = 2;
//	arr2048[2][0] = 4;
//	arr2048[3][0] = 4;
//	arr2048[0][2] = 32;
	return;
}

void draw_game(short arr[size_i][size_j]) {
	system("cls");
	cout << endl << endl << endl;
	setlocale(LC_ALL, "Russian");
	cout << "\tËó÷øèé ñ÷¸ò: " << best_score << "   Ñ÷¸ò: " << score;
	setlocale(LC_ALL, "C");
	cout << endl << endl;
	for	(short i = 0; i < size_i; i++)
	{
		cout << "\t";
		for	(short j = 0; j < size_j; j++)
		{
			if (arr2048[i][j] == 0) SetColor(119); else
			if (arr2048[i][j] == 2) SetColor(31); else
			if (arr2048[i][j] == 4) SetColor(47); else
			if (arr2048[i][j] == 8) SetColor(63); else
			if (arr2048[i][j] == 16) SetColor(79); else
			if (arr2048[i][j] == 32) SetColor(95); else
			if (arr2048[i][j] == 64) SetColor(111); else
			if (arr2048[i][j] == 128) SetColor(159); else
			if (arr2048[i][j] >= 256) SetColor(192); 
			
			cout << ' ' << arr2048[i][j] << "\t";
			SetColor(7);
			cout << ' ';
			SetColor(119);
		}
		SetColor(7);
		cout << endl << endl;	
	}
	SetColor(7);
	return;
}

void move_game(short arr2048[size_i][size_j], short key) {
	if ((key == 72 || key == 119 /*w*/ || key == 87)) //up
	{
		move_up(arr2048);
		// Slojeniye odinakovix
		for (short i = 0; i < size_i; i++)
		{
			for (short j = 0; j < size_j - 1; j++)
			{
				if (arr2048[j][i] == arr2048[j+1][i])
				{
					arr2048[j][i] = arr2048[j][i]*2;
					arr2048[j+1][i] = 0;
					
					score += arr2048[j][i];
					if (best_score < score)
					{
						best_score = score;
					}
				}
			}
		}
		move_up(arr2048);
		return;
	}
	else if ((key == 80 || key == 115 /*s*/ || key == 83)) //down
	{
		move_down(arr2048);
		// Slojeniye odinakovix
		for (short i = 0; i < size_i; i++)
		{
			for (short j = size_j-1; j >= 0; j--)
			{
				if (arr2048[j][i] == arr2048[j-1][i] && arr2048[j][i] != 0)
				{
					arr2048[j][i] = arr2048[j][i]*2;
					arr2048[j-1][i] = 0;
					
					score += arr2048[j][i];
					if (best_score < score)
					{
						best_score = score;
					}
				}
			}
		}
		move_down(arr2048);	
		return;	
	}
	else if ((key == 75 || key == 97 /*a*/ || key == 65)) //left
	{
		move_left(arr2048);
		// Slojeniye odinakovix
		for (short i = 0; i < size_i; i++)
		{
			for (short j = 0; j < size_j - 1; j++)
			{
				if (arr2048[i][j] == arr2048[i][j+1] && arr2048[i][j] != 0)
				{
					arr2048[i][j] = arr2048[i][j+1]*2;
					arr2048[i][j+1] = 0;
					
					score += arr2048[i][j];
					if (best_score < score)
					{
						best_score = score;
					}
				}
			}
		}
		move_left(arr2048);
		return;
	}
	else if ((key == 77 || key == 100 /*d*/ || key == 68)) //right
	{
		move_right(arr2048);
		// Slojeniye odinakovix
		for (short i = 0; i < size_i; i++)
		{
			for (short j = size_j-1; j >= 0; j--)
			{
				if (arr2048[i][j] == arr2048[i][j-1] && arr2048[i][j] != 0)
				{
					arr2048[i][j] = arr2048[i][j]*2;
					arr2048[i][j-1] = 0;
					
					score += arr2048[i][j];
					if (best_score < score)
					{
						best_score = score;
					}
				}
			}
		}
		move_right(arr2048);
		return;
	}
}

void move_up(short arr2048[size_i][size_j]) {
	for (short i = 0; i < size_i; i++)
	{
	for (short k = 0; k < 3; k++)
	{
		if (arr2048[0][i] == 0) //1
		{
			if (arr2048[1][i] == 0) //2
			{
				if (arr2048[2][i] == 0) //3
				{
					if (arr2048[3][i] == 0) //4
					{
					}
					else 
					{
						arr2048[0][i] = arr2048[3][i];
						arr2048[3][i] = 0;
					}
				}
				else 
				{
					arr2048[0][i] = arr2048[2][i];
					arr2048[2][i] = 0;
				}
			}
			else 
			{
				arr2048[0][i] = arr2048[1][i];
				arr2048[1][i] = 0;
			}
		}
		else 
		{
			if (arr2048[1][i] == 0) //2
			{
				if (arr2048[2][i] == 0) //3
				{
					arr2048[2][i] = arr2048[3][i];
					arr2048[3][i] = 0;
				}
				else
				{
					arr2048[1][i] = arr2048[2][i];
					arr2048[2][i] = 0;
				}
			}
			else
			{
				if (arr2048[2][i] == 0) //3
				{
					arr2048[2][i] = arr2048[3][i];
					arr2048[3][i] = 0;
				}
				else
				{
				}
			}
		}
	}
	}
	return;
}

void move_down(short arr2048[size_i][size_j]) {
	for (short i = size_i-1; i >= 0; i--)
	{
	for (short k = 0; k < 3; k++)
	{
		if (arr2048[3][i] == 0) //1
		{
			if (arr2048[2][i] == 0) //2
			{
				if (arr2048[1][i] == 0) //3
				{
					if (arr2048[0][i] == 0) //4
					{
					}
					else 
					{
						arr2048[3][i] = arr2048[0][i];
						arr2048[0][i] = 0;
					}
				}
				else 
				{
					arr2048[3][i] = arr2048[1][i];
					arr2048[1][i] = 0;
				}
			}
			else 
			{
				arr2048[3][i] = arr2048[2][i];
				arr2048[2][i] = 0;
			}
		}
		else 
		{
			if (arr2048[2][i] == 0) //2
			{
				if (arr2048[1][i] == 0) //3
				{
					arr2048[1][i] = arr2048[0][i];
					arr2048[0][i] = 0;
				}
				else
				{
					arr2048[2][i] = arr2048[1][i];
					arr2048[1][i] = 0;
				}
			}
			else
			{
				if (arr2048[1][i] == 0) //3
				{
					arr2048[1][i] = arr2048[0][i];
					arr2048[0][i] = 0;
				}
				else
				{
				}
			}
		}
	}
	}
	return;
}

void move_left(short arr2048[size_i][size_j]) {
	for (short i = 0; i < size_i; i++)
	{
	for (short k = 0; k < 3; k++)
	{
		if (arr2048[i][0] == 0) //1
		{
			if (arr2048[i][1] == 0) //2
			{
				if (arr2048[i][2] == 0) //3
				{
					if (arr2048[i][3] == 0) //4
					{
					}
					else 
					{
						arr2048[i][0] = arr2048[i][3];
						arr2048[i][3] = 0;
					}
				}
				else 
				{
					arr2048[i][0] = arr2048[i][2];
					arr2048[i][2] = 0;
				}
			}
			else 
			{
				arr2048[i][0] = arr2048[i][1];
				arr2048[i][1] = 0;
			}
		}
		else 
		{
			if (arr2048[i][1] == 0) //2
			{
				if (arr2048[i][2] == 0) //3
				{
					arr2048[i][2] = arr2048[i][3];
					arr2048[i][3] = 0;
				}
				else
				{
					arr2048[i][1] = arr2048[i][2];
					arr2048[i][2] = 0;
				}
			}
			else
			{
				if (arr2048[i][2] == 0) //3
				{
					arr2048[i][2] = arr2048[i][3];
					arr2048[i][3] = 0;
				}
				else
				{
				}
			}
		}
	}
	}
	return;
}

void move_right(short arr2048[size_i][size_j]) {
	for (short i = size_i-1; i >= 0; i--)
	{
	for (short k = 0; k < 3; k++)
	{
		if (arr2048[i][3] == 0) //1
		{
			if (arr2048[i][2] == 0) //2
			{
				if (arr2048[i][1] == 0) //3
				{
					if (arr2048[i][0] == 0) //4
					{
					}
					else 
					{
						arr2048[i][3] = arr2048[i][0];
						arr2048[i][0] = 0;
					}
				}
				else 
				{
					arr2048[i][3] = arr2048[i][1];
					arr2048[i][1] = 0;
				}
			}
			else 
			{
				arr2048[i][3] = arr2048[i][2];
				arr2048[i][2] = 0;
			}
		}
		else 
		{
			if (arr2048[i][2] == 0) //2
			{
				if (arr2048[i][1] == 0) //3
				{
					arr2048[i][1] = arr2048[i][0];
					arr2048[i][0] = 0;
				}
				else
				{
					arr2048[i][2] = arr2048[i][1];
					arr2048[i][1] = 0;
				}
			}
			else
			{
				if (arr2048[i][1] == 0) //3
				{
					arr2048[i][1] = arr2048[i][0];
					arr2048[i][0] = 0;
				}
				else
				{
				}
			}
		}
	}
	}
	return 0;
}
