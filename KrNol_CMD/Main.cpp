#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <locale.h>
#include <Windows.h>

const int Sz = 11;

int syssettings();
int begin(std::vector<short int>& Land); 
int menu(std::vector<short int>& Land, bool& AppClose);
int otrisovka_menu(const int Сh); 
int otrisovka(std::vector<short int>& Land);  
int key(std::vector<short int>& Land); 
int choose(std::vector<short int>& Land, bool& NonEmpty);
int check_end(std::vector<short int>& Land, bool& ChEnd); 
int check(std::vector<short int>& Land, int& Сh); 
int check_enemy(std::vector <short int>& Land, int& Сh); 
int ai(std::vector<short int>& Land);  

int main()
{
	int ChIErr = 0;
	bool AppClose = 0;
	std::vector<short int> Land(Sz);
	ChIErr = syssettings();
	if (ChIErr != 0)
	{
		printf("Error 1\n");
		return 1;
	}
	do
	{
		ChIErr = menu(Land, AppClose);
		if (ChIErr != 0)
		{
			printf("Error 2\n");
			return 2;
		}
	} while (!AppClose);
	return 0;
}

int syssettings()
{
	bool ChBErr = 0;
	char* ChCPErr = 0;
	CONSOLE_CURSOR_INFO cursinf;
	HANDLE h0ut = GetStdHandle(STD_OUTPUT_HANDLE);
	if ((h0ut == INVALID_HANDLE_VALUE) || (h0ut == NULL))
	{
		printf("Error 1\n");
		return 1;
	}
	ChBErr = GetConsoleCursorInfo(h0ut, &cursinf);
	if (ChBErr == 0)
	{
		printf("Error 2\n");
		return 2;
	}
	cursinf.bVisible = 0;
	ChBErr = SetConsoleCursorInfo(h0ut, &cursinf);
	if (ChBErr == 0)
	{
		printf("Error 3\n");
		return 3;
	}
	ChBErr = SetConsoleTextAttribute(h0ut, 0x00F0);
	if (ChBErr == 0)
	{
		printf("Error 4\n");
		return 4;
	}
	ChCPErr = setlocale(LC_ALL, "RUS");
	if (ChCPErr == NULL)
	{
		printf("Error 5\n");
		return 5;
	}
	return 0;
}

int begin(std::vector<short int>& Land)
{
	if (Land.size() < Sz)
	{
		printf("Error 1\n");
		return 1;
	}
	for (size_t i = 0; i < Sz; ++i) Land.at(i) = 0;
	Land.at(0) = 10;  
	Land.at(10) = 1; 
	return 0;
}

int menu(std::vector<short int>& Land, bool& AppClose) 
{	
	if (Land.size() < Sz)
	{
		printf("Error 1\n");
		return 1;
	}
	int c = 0;
	int Ch = 0;
	int ChIErr = 0;
	ChIErr = otrisovka_menu(Ch);
	if (ChIErr > 0)
	{
		printf("Error 3\n");
		return 3;
	}
	while (c!=13) 
	{
		c = getch();  
		if (c == 72)
		{
			if (Ch - 1 >= 0) --Ch;
			else Ch = 3;
			ChIErr = otrisovka_menu(Ch);
			if (ChIErr > 0)
			{
				printf("Error 4\n");
				return 4;
			}
		}
		else if (c == 80)  
		{
			if (Ch + 1 <= 3) ++Ch;
			else Ch = 0;
			ChIErr = otrisovka_menu(Ch);
			if (ChIErr > 0)
			{
				printf("Error 5\n");
				return 5;
			}
		}
		else if ((c != 224)&&(c!=13))
		{
			ChIErr = printf("<KrNULL>: Используйте только стрелки вверх или вниз и enter\n");
			if (ChIErr < 0)
			{
				printf("Error 6\n");
				return 6;
			}
		}
	}
	switch (Ch)
	{
	case 0:  
		ChIErr = begin(Land);
		if (ChIErr > 0)
		{
			printf("Error 7\n");
			return 7;
		}
		ChIErr = key(Land);
		if (ChIErr > 0)
		{
			printf("Error 8\n");
			return 8;
		}
		break;
	case 1:  
		ChIErr = begin(Land);
		if (ChIErr > 0)
		{
			printf("Error 9\n");
			return 9;
		}
		ChIErr = ai(Land);
		if (ChIErr > 0)
		{
			printf("Error 10");
			return 10;
		}
		ChIErr = key(Land);
		if (ChIErr > 0)
		{
			printf("Error 11\n");
			return 11;
		}
		break;
	case 2:
		ChIErr = system("cls");
		if (ChIErr == -1)
		{
			printf("Error 12\n");
			return 12;
		}
		ChIErr = system("IF EXIST readme.txt ( readme.txt) ELSE (echo Файл справки не найдён, попробуйте переустановить приложение && pause)");
		if (ChIErr == -1)
		{
			printf("Error 13\n");
			return 13;
		}
		ChIErr = begin(Land);
		if (ChIErr > 0)
		{
			printf("Error 14\n");
			return 14;
		}
		ChIErr = key(Land);
		if (ChIErr > 0)
		{
			printf("Error 15\n");
			return 15;
		}
		break; 
	case 3:
		AppClose = 1;
		return 0;
		break;
	default:
		ChIErr = begin(Land);
		if (ChIErr > 0)
		{
			printf("Error 16\n");
			return 16;
		}
		ChIErr = key(Land);
		if (ChIErr > 0)
		{
			printf("Error 17\n");
			return 17;
		}
		break;
	}
	AppClose = 0;
	return 0; 
}

int otrisovka_menu(const int Сh)
{
	if ((Сh < 0) || (Сh > 3))
	{
		printf("Error 1\n");
		return 1;
	}
	int ChIErr = 0;
	bool ChBErr = 0;
	HANDLE h0ut = GetStdHandle(STD_OUTPUT_HANDLE);
	if ((h0ut == INVALID_HANDLE_VALUE) || (h0ut == NULL))
	{
		printf("Error 2\n");
		return 2;
	}
	ChIErr=system("cls");
	if (ChIErr == -1)
	{
		printf("Error 3\n");
		return 3;
	}
	ChIErr = printf("KrNULL_CMD\n\n");
	if (ChIErr < 0)
	{
		printf("Error 4\n");
		return 4;
	}
	if (Сh == 0)
	{
		ChBErr = SetConsoleTextAttribute(h0ut, 0x000F);
		if (ChBErr == 0)
		{
			printf("Error 5\n");
			return 5;
		}
		ChIErr = printf("Играть за крестики");
		if (ChIErr < 0)
		{
			printf("Error 6\n");
			return 6;
		}
		ChBErr = SetConsoleTextAttribute(h0ut, 0x00F0);
		if (ChBErr == 0)
		{
			printf("Error 7\n");
			return 7;
		}
		ChIErr = printf("\nИграть за нолики\nСправка\nВыход\n");
		if (ChIErr < 0)
		{
			printf("Error 8\n");
			return 8;
		}
	}
	if (Сh == 1)
	{	
		ChIErr = printf("Играть за крестики\n");
		if (ChIErr < 0)
		{
			printf("Error 9\n");
			return 9;
		}
		ChBErr = SetConsoleTextAttribute(h0ut, 0x000F);
		if (ChBErr == 0)
		{
			printf("Error 10\n");
			return 10;
		}
		ChIErr = printf("Играть за нолики");
		if (ChIErr < 0)
		{
			printf("Error 11\n");
			return 11;
		}
		ChBErr = SetConsoleTextAttribute(h0ut, 0x00F0);
		if (ChBErr == 0)
		{
			printf("Error 12\n");
			return 12;
		}
		ChIErr = printf("\nСправка\nВыход\n");
		if (ChIErr < 0)
		{
			printf("Error 13\n");
			return 13;
		}
	}
	if (Сh == 2)
	{
		ChIErr = printf("Играть за крестики\nИграть за нолики\n");
		if (ChIErr < 0)
		{
			printf("Error 14\n");
			return 14;
		}
		ChBErr = SetConsoleTextAttribute(h0ut, 0x000F);
		if (ChBErr == 0)
		{
			printf("Error 15\n");
			return 15;
		}
		ChIErr = printf("Справка");
		if (ChIErr < 0)
		{
			printf("Error 16\n");
			return 16;
		}
		ChBErr = SetConsoleTextAttribute(h0ut, 0x00F0);
		if (ChBErr == 0)
		{
			printf("Error 17\n");
			return 17;
		}
		ChIErr = printf("\nВыход\n");
		if (ChIErr < 0)
		{
			printf("Error 18\n");
			return 18;
		}
	}
	if (Сh == 3)
	{
		ChIErr = printf("Играть за крестики\nИграть за нолики\nСправка\n");
		if (ChIErr < 0)
		{
			printf("Error 19\n");
			return 19;
		}
		ChBErr = SetConsoleTextAttribute(h0ut, 0x000F);
		if (ChBErr == 0)
		{
			printf("Error 20\n");
			return 20;
		}
		ChIErr = printf("Выход");
		if (ChIErr < 0)
		{
			printf("Error 21\n");
			return 21;
		}
		ChBErr = SetConsoleTextAttribute(h0ut, 0x00F0);
		if (ChBErr == 0)
		{
			printf("Error 22\n");
			return 22;
		}
		ChIErr = printf("\n");
		if (ChIErr < 0)
		{
			printf("Error 23\n");
			return 23;
		}
	}
	ChIErr = printf("------------------ \n");  
	if (ChIErr < 0)
	{
		printf("Error 24\n");
		return 24;
	}
	return 0;
}

int otrisovka(std::vector<short int>& Land)
{
	if (Land.size() < Sz)
	{
		printf("Error 1\n");
		return 1;
	}
	int ChIErr = 0;
	bool ChBErr = 0;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if ((h == INVALID_HANDLE_VALUE) || (h == NULL))
	{
		printf("Error 2\n");
		return 2;
	}
	ChIErr=system("cls");
	if (ChIErr == -1)
	{
		printf("Error 3\n");
		return 3;
	}
	for (size_t i = 1; i < 10; ++i)
	{
		if (Land.at(10) != i) 
		{
			if (Land.at(i) == 0)
			{
				ChIErr = printf("|_|");
				if (ChIErr < 0)
				{
					printf("Error 4\n");
					return 4;
				}
			}
			else if (Land.at(i) == 10)
			{
				ChIErr = printf("|X|");
				if (ChIErr < 0)
				{
					printf("Error 5\n");
					return 5;
				}
			}
			else if (Land.at(i) == -10)
			{
				ChIErr = printf("|0|");
				if (ChIErr < 0)
				{
					printf("Error 6\n");
					return 6;
				}
			}
		}
		else
		{
			ChBErr=SetConsoleTextAttribute(h, 0x000F); 
			if (ChBErr == 0)
			{
				printf("Error 7\n");
				return 7;
			}
			if (Land.at(i) == 0)
			{
				ChIErr = printf("|_|");
				if (ChIErr < 0)
				{
					printf("Error 8\n");
					return 8;
				}
			}
			else if (Land.at(i) == 10)
			{
				ChIErr = printf("|X|");
				if (ChIErr < 0)
				{
					printf("Error 9\n");
					return 9;
				}
			}
			else if (Land.at(i) == -10)
			{
				ChIErr = printf("|0|");
				if (ChIErr < 0)
				{
					printf("Error 10\n");
					return 10;
				}
			}
			ChBErr = SetConsoleTextAttribute(h, 0x00F0);
			if (ChBErr == 0)
			{
				printf("Error 11\n");
				return 11;
			}
		}
		if (i % 3 == 0)
		{
			ChIErr = printf("\n"); 
			if (ChIErr < 0)
			{
				printf("Error 12\n");
				return 12;
			}
		}
	}
	ChIErr = printf("------------------ \n"); 
	if (ChIErr < 0)
	{
		printf("Error 13\n");
		return 13;
	}
	return 0;
}

int key(std::vector<short int>& Land)
{
	if (Land.size() < Sz)
	{
		printf("Error 1\n");
		return 1;
	}
	int ChIErr = 0;
	int c = 0;
	bool ChEnd = 0;
	bool NonEmpty = 0;
	ChIErr = otrisovka(Land);
	if (ChIErr > 0)
	{
		printf("Error 2\n");
		return 2;
	}
	do
	{
		c = getch();
		if (c == 72)
		{
			if ((Land.at(10) - 3) > 0)Land.at(10) = Land.at(10) - 3;
			else Land.at(10) = Land.at(10) + 6;
			ChIErr = otrisovka(Land);
			if (ChIErr > 0)
			{
				printf("Error 3\n");
				return 3;
			}
		}
		else if (c == 80) 
		{
			if ((Land.at(10) + 3) < 10)Land.at(10) = Land.at(10) + 3;
			else Land.at(10) = Land.at(10) - 6;
			ChIErr = otrisovka(Land);
			if (ChIErr > 0)
			{
				printf("Error 4\n");
				return 4;
			}
		}
		else if (c == 75)  
		{
			if ((Land.at(10) != 1) && (Land.at(10) != 4) && (Land.at(10) != 7))Land.at(10) = Land.at(10) - 1;
			else Land.at(10) = Land.at(10) + 2;
			ChIErr = otrisovka(Land);
			if (ChIErr > 0)
			{
				printf("Error 5\n");
				return 5;
			}
		}
		else if (c == 77) 
		{
			if ((Land.at(10) % 3) != 0)Land.at(10) = Land.at(10) + 1;
			else Land.at(10) = Land.at(10) - 2;
			ChIErr = otrisovka(Land);
			if (ChIErr > 0)
			{
				printf("Error 6\n");
				return 6;
			}
		}
		else if (c == 13) 
		{
			ChIErr = choose(Land, NonEmpty);
			if (ChIErr > 0)
			{
				printf("Error 7\n");
				return 7;
			}
			if (NonEmpty)
			{
				ChIErr = printf("<KrNULL>: Ячейка несвободна\n");
				if (ChIErr < 0)
				{
					printf("Error 8\n");
					return 8;
				}
			}
			ChIErr = check_end(Land, ChEnd);
			if (ChIErr > 0)
			{
				printf("Error 9\n");
				return 9;
			}
			else if (ChEnd) break;
			else if ((ChIErr == 0) && (!NonEmpty))
			{
				ChIErr = ai(Land);
				if (ChIErr > 0)
				{
					printf("Error 10\n");
					return 10;
				}
			}
		}
		else if (c != 224) 
		{
			ChIErr = printf("<KrNULL>: Используйте стрелочки или enter\n");
			if (ChIErr < 0)
			{
				printf("Error 11\n");
				return 11;
			}
		}
		ChIErr = check_end(Land, ChEnd);
		if (ChIErr > 0)
		{
			printf("Error 12\n");
			return 12;
		}
	} while (!ChEnd);
	ChIErr = printf("<KrNULL>: Нажмите *any key* для продолжения\n");
	if (ChIErr < 0)
	{
		printf("Error 13\n");
		return 13;
	}
	c = getch();
	return 0;
}

int choose(std::vector<short int>& Land, bool& NonEmpty) 
{
	if (Land.size() < Sz)
	{
		printf("Error 1\n");
		return 1;
	}
	int ChIErr = 0;
	if (Land.at(Land.at(10)) == 0)
	{
		Land.at(Land.at(10)) = Land.at(0);
		if (Land.at(0) == -10) Land.at(0) = 10;
		else Land.at(0) = -10;
		ChIErr = otrisovka(Land);
		if (ChIErr > 0)
		{
			printf("Error 3\n");
			return 3;
		}
		NonEmpty = 0;
		return 0;
	}
	else NonEmpty = 1;
	return 0;
}

int check_end(std::vector<short int>& Land, bool& ChEnd) 
{
	if (Land.size() < Sz)
	{
		printf("Error 1\n");
		return 1;
	}
	int ChIErr = 0;
	if (
		(abs(Land.at(1) + Land.at(2) + Land.at(3)) == 30) ||
		(abs(Land.at(1) + Land.at(5) + Land.at(9)) == 30) ||
		(abs(Land.at(1) + Land.at(4) + Land.at(7)) == 30) ||
		(abs(Land.at(2) + Land.at(5) + Land.at(8)) == 30) ||
		(abs(Land.at(3) + Land.at(5) + Land.at(7)) == 30) ||
		(abs(Land.at(3) + Land.at(6) + Land.at(9)) == 30) ||
		(abs(Land.at(4) + Land.at(5) + Land.at(6)) == 30) ||
		(abs(Land.at(7) + Land.at(8) + Land.at(9)) == 30))
	{
		if (Land.at(0) == -10)
		{
			ChIErr = printf("<KrNULL>: Кресты победили !\n");
			if (ChIErr < 0)
			{
				printf("Error 3\n");
				return 3;
			}
		}
		else if (Land.at(0) == 10)
		{
			ChIErr = printf("<KrNULL>: Нолики победили ! \n");
			if (ChIErr < 0)
			{
				printf("Error 4\n");
				return 4;
			}
		}
		else
		{
			ChIErr = printf("Error 5\n");
			return 5;
		}
		ChEnd = 1;
	}
	else
	{
		int tmp = 0;
		for (size_t i = 1; i < 10; ++i) if (Land.at(i) == 0)++tmp;
		if (tmp == 0)
		{
			ChIErr = printf("<KrNULL>: Победила Дружба \n");
			if (ChIErr < 0)
			{
				printf("Error 6\n");
				return 6;
			}
			ChEnd = 1;
		}
		else ChEnd = 0;
	}
	return 0;
}

int check(std::vector <short int>& Land, int& Ch)
{
	if (Land.size() < Sz)
	{
		printf("Error 1\n");
		return 1;
	}
	size_t len = 0;
	time_t tm;
	bool Empty = 0; 
	std::vector<short int> wn;
	Ch = 0;
	if (Land.at(1) == 0)
	{
		Empty = 1;
		if ((Land.at(2) == Land.at(3)) && (Land.at(2) == Land.at(0))) wn.push_back(1); 
		else if ((Land.at(5) == Land.at(9)) && (Land.at(5) == Land.at(0))) wn.push_back(1);
		else if ((Land.at(4) == Land.at(7)) && (Land.at(4) == Land.at(0))) wn.push_back(1);
	}
	if (Land.at(2) == 0)
	{
		Empty = 1;
		if ((Land.at(1) == Land.at(3)) && (Land.at(1) == Land.at(0))) wn.push_back(2);
		else if ((Land.at(5) == Land.at(8)) && (Land.at(5) == Land.at(0))) wn.push_back(2);
	}
	if (Land.at(3) == 0)
	{
		Empty = 1;
		if ((Land.at(1) == Land.at(2)) && (Land.at(1) == Land.at(0))) wn.push_back(3);
		else if ((Land.at(6) == Land.at(9)) && (Land.at(6) == Land.at(0))) wn.push_back(3);
		else if ((Land.at(5) == Land.at(7)) && (Land.at(5) == Land.at(0))) wn.push_back(3);
	}
	if (Land.at(4) == 0)
	{
		Empty = 1;
		if ((Land.at(1) == Land.at(7)) && (Land.at(1) == Land.at(0))) wn.push_back(4);
		else if ((Land.at(5) == Land.at(6)) && (Land.at(5) == Land.at(0))) wn.push_back(4);
	}
	if (Land.at(5) == 0)
	{
		Empty = 1;
		if ((Land.at(1) == Land.at(9)) && (Land.at(1) == Land.at(0))) wn.push_back(5);
		else if ((Land.at(2) == Land.at(8)) && (Land.at(2) == Land.at(0))) wn.push_back(5);
		else if ((Land.at(3) == Land.at(7)) && (Land.at(3) == Land.at(0))) wn.push_back(5);
		else if ((Land.at(4) == Land.at(6)) && (Land.at(4) == Land.at(0))) wn.push_back(5);
	}
	if (Land.at(6) == 0)
	{
		Empty = 1;
		if ((Land.at(3) == Land.at(9)) && (Land.at(3) == Land.at(0))) wn.push_back(6);
		else if ((Land.at(4) == Land.at(5)) && (Land.at(4) == Land.at(0))) wn.push_back(6);
	}
	if (Land.at(7) == 0)
	{
		Empty = 1;
		if ((Land.at(1) == Land.at(4)) && (Land.at(1) == Land.at(0))) wn.push_back(7);
		else if ((Land.at(3) == Land.at(5)) && (Land.at(3) == Land.at(0))) wn.push_back(7);
		else if ((Land.at(8) == Land.at(9)) && (Land.at(8) == Land.at(0))) wn.push_back(7);
	}
	if (Land.at(8) == 0)
	{
		Empty = 1;
		if ((Land.at(2) == Land.at(5)) && (Land.at(2) == Land.at(0))) wn.push_back(8);
		else if ((Land.at(7) == Land.at(9)) && (Land.at(7) == Land.at(0))) wn.push_back(8);
	}
	if (Land.at(9) == 0)
	{
		Empty = 1;
		if ((Land.at(1) == Land.at(5)) && (Land.at(1) == Land.at(0))) wn.push_back(9);
		else if ((Land.at(3) == Land.at(6)) && (Land.at(3) == Land.at(0))) wn.push_back(9);
		else if ((Land.at(7) == Land.at(8)) && (Land.at(7) == Land.at(0))) wn.push_back(9);
	}
	len = wn.size();
	if (len > 0)
	{
		if (len > 1)
		{
			tm = time(NULL);
			if (tm == -1)
			{
				printf("Error 3\n");
				return 3;
			}
			srand(tm);
			Ch = wn.at(rand() % len);
		}
		else if (len == 1) Ch = wn.at(0);
	}
	else if (Empty == 0) Ch = -1;
	else if (len == 0) Ch = 0;
	else
	{
		printf("Error 4\n");
		return 4;
	}
	return 0;
}

int check_enemy(std::vector <short int>& Land, int& Сh)
{
	if (Land.size() < Sz)
	{
		printf("Error 1\n");
		return 1;
	}
	size_t len = 0;
	time_t tm = 0;
	std::vector<short int> lose; 
	Сh = 0;
	if (Land.at(1) == 0)
	{
		if ((Land.at(2) == Land.at(3)) && (Land.at(2) * Land.at(0) < 0)) lose.push_back(1);  
		else if ((Land.at(5) == Land.at(9)) && (Land.at(5) * Land.at(0) < 0)) lose.push_back(1);
		else if ((Land.at(4) == Land.at(7)) && (Land.at(4) * Land.at(0) < 0)) lose.push_back(1);
	}
	if (Land.at(2) == 0)
	{
		if ((Land.at(1) == Land.at(3)) && (Land.at(1) * Land.at(0) < 0)) lose.push_back(2);
		else if ((Land.at(5) == Land.at(8)) && (Land.at(5) * Land.at(0) < 0)) lose.push_back(2);
	}
	if (Land.at(3) == 0)
	{
		if ((Land.at(1) == Land.at(2)) && (Land.at(1) * Land.at(0) < 0)) lose.push_back(3);
		else if ((Land.at(6) == Land.at(9)) && (Land.at(6) * Land.at(0) < 0)) lose.push_back(3);
		else if ((Land.at(5) == Land.at(7)) && (Land.at(5) * Land.at(0) < 0)) lose.push_back(3);
	}
	if (Land.at(4) == 0)
	{
		if ((Land.at(1) == Land.at(7)) && (Land.at(1) * Land.at(0) < 0)) lose.push_back(4);
		else if ((Land.at(5) == Land.at(6)) && (Land.at(5) * Land.at(0) < 0)) lose.push_back(4);
	}
	if (Land.at(5) == 0)
	{
		if ((Land.at(1) == Land.at(9)) && (Land.at(1) * Land.at(0) < 0)) lose.push_back(5);
		else if ((Land.at(2) == Land.at(8)) && (Land.at(2) * Land.at(0) < 0)) lose.push_back(5);
		else if ((Land.at(3) == Land.at(7)) && (Land.at(3) * Land.at(0) < 0)) lose.push_back(5);
		else if ((Land.at(4) == Land.at(6)) && (Land.at(4) * Land.at(0) < 0)) lose.push_back(5);
	}
	if (Land.at(6) == 0)
	{
		if ((Land.at(3) == Land.at(9)) && (Land.at(3) * Land.at(0) < 0)) lose.push_back(6);
		else if ((Land.at(4) == Land.at(5)) && (Land.at(4) * Land.at(0) < 0)) lose.push_back(6);
	}
	if (Land.at(7) == 0)
	{
		if ((Land.at(1) == Land.at(4)) && (Land.at(1) * Land.at(0) < 0)) lose.push_back(7);
		else if ((Land.at(3) == Land.at(5)) && (Land.at(3) * Land.at(0) < 0)) lose.push_back(7);
		else if ((Land.at(8) == Land.at(9)) && (Land.at(8) * Land.at(0) < 0)) lose.push_back(7);
	}
	if (Land.at(8) == 0)
	{
		if ((Land.at(2) == Land.at(5)) && (Land.at(2) * Land.at(0) < 0)) lose.push_back(8);
		else if ((Land.at(7) == Land.at(9)) && (Land.at(7) * Land.at(0) < 0)) lose.push_back(8);
	}
	if (Land.at(9) == 0)
	{
		if ((Land.at(1) == Land.at(5)) && (Land.at(1) * Land.at(0) < 0)) lose.push_back(9);
		else if ((Land.at(3) == Land.at(6)) && (Land.at(3) * Land.at(0) < 0)) lose.push_back(9);
		else if ((Land.at(7) == Land.at(8)) && (Land.at(7) * Land.at(0) < 0)) lose.push_back(9);
	}
	len = lose.size();
	if (len > 0)
	{
		if (len == 1) Сh = lose.front();
		else
		{
			tm = time(NULL);
			if (tm == -1)
			{
				printf("Error 3\n");
				return 3;
			}
			srand(tm);
			Сh = lose.at(rand() % len);
		}
	}
	else if (len == 0) Сh = 0;
	else
	{
		printf("Error 4\n");
		return 4;
	}
	return 0;
}

int ai(std::vector <short int>& Land)
{
	if (Land.size() < Sz)
	{
		printf("Error 1\n");
		return 1;
	}
	time_t tm = 0;
	int ChIErr = 0;
	int Сh = 0;
	bool NonEmpty = 0;	
	ChIErr = check(Land, Сh);
	if (ChIErr > 0)
	{
		printf("Error 2\n");
		return 2;
	}
	if (Сh != -1)
	{
		if (Сh != 0)
		{
			Land.at(10) = Сh;
			ChIErr = otrisovka(Land);
			if (ChIErr > 0)
			{
				printf("Error 3\n");
				return 3;
			}
			ChIErr = choose(Land, NonEmpty);
			if (ChIErr > 0)
			{
				printf("Error 4\n");
				return 4;
			}
			if (NonEmpty)
			{
				printf("Error 5\n");
				return 5;
			}
			return 0;
		}
		ChIErr = check_enemy(Land, Сh);
		if (ChIErr > 0)
		{
			printf("Error 6\n");
			return 6;
		}
		if (Сh != 0)
		{
			Land.at(10) = Сh;
			ChIErr = otrisovka(Land);
			if (ChIErr > 0)
			{
				printf("Error 7\n");
				return 7;
			}
			ChIErr = choose(Land, NonEmpty);
			if (ChIErr > 0)
			{
				printf("Error 8\n");
				return 8;
			}
			if (NonEmpty)
			{
				printf("Error 9\n");
				return 9;
			}
			return 0;
		}
		if (Land.at(5) == 0)
		{
			Land.at(10) = 5;
			ChIErr = otrisovka(Land);
			if (ChIErr > 0)
			{
				printf("Error 10\n");
				return 10;
			}
			ChIErr = choose(Land, NonEmpty);
			if (ChIErr > 0)
			{
				printf("Error 11\n");
				return 11;
			}
			if (NonEmpty)
			{
				printf("Error 12\n");
			}
			return 0;
		}
		else if (Land.at(5) == Land.at(0))
		{
			if ((Land.at(0) == -10) && (Land.at(2) != -10) && (Land.at(4) != -10) && (Land.at(6) != -10) && (Land.at(8) != -10))
			{
				do
				{
					tm = time(NULL);
					if (tm == -1)
					{
						printf("Error 13\n");
						return 13;
					}
					srand(tm);
					Land.at(10) = 2 * (1 + rand() % 4);
					if (((Land.at(2) != Land.at(8))) && (Land.at(4) != Land.at(6)))
					{
						Сh = -1;
						break;
					}
					else if ((((Land.at(10) == 2) || (Land.at(10) == 8)) && (Land.at(2) != Land.at(8))) ||
						(((Land.at(10) == 4) || (Land.at(10) == 6)) && (Land.at(4) != Land.at(6))))
						Land.at(10) = 5;
					ChIErr = choose(Land, NonEmpty);
					if (ChIErr > 0)
					{
						printf("Error 14\n");
						return 14;
					}
				} while (NonEmpty);
				if (Сh != -1)
				{
					ChIErr = otrisovka(Land);
					if (ChIErr > 0)
					{
						printf("Error 15\n");
						return 15;
					}
					return 0;
				}
			}
		}
		if ((Land.at(1) == 0) || (Land.at(3) == 0) || (Land.at(7) == 0) || (Land.at(9) == 0))
		{
			do
			{
				tm = time(NULL);
				if (tm == -1)
				{
					printf("Error 16\n");
					return 16;
				}
				srand(tm);
				Сh = 1 + rand() % 4;
				if (Сh % 2 == 0) Сh = Сh + 5;
				Land.at(10) = Сh;
				if((Land.at(5)==-10)&&(Land.at(0)==Land.at(5)))
				if (((Land.at(10) == 1) && ((Land.at(Land.at(10) + 1) != 10) && (Land.at(Land.at(10) + 3) != 10)))
					|| ((Land.at(10) == 3) && ((Land.at(Land.at(10) - 1) != 10) && (Land.at(Land.at(10) + 3) != 10)))
					|| ((Land.at(10) == 7) && ((Land.at(Land.at(10) + 1) != 10) && (Land.at(Land.at(10) - 3) != 10)))
					|| ((Land.at(10) == 9) && ((Land.at(Land.at(10) - 1) != 10) && (Land.at(Land.at(10) - 3) != 10))))
					Land.at(10) = 5;
				ChIErr = choose(Land, NonEmpty);
				if (ChIErr > 0)
				{
					printf("Error 17\n");
					return 17;
				}
			} while (NonEmpty);
			ChIErr = otrisovka(Land);
			if (ChIErr > 0)
			{
				printf("Error 18\n");
				return 18;
			}
			return 0;
		}
		else
		{
			do
			{
				tm = time(NULL);
				if (tm == -1)
				{
					printf("Error 19\n");
					return 19;
				}
				srand(tm);
				Land.at(10) = 2 * (1 + rand() % 4);
				ChIErr = choose(Land, NonEmpty);
				if (ChIErr > 0)
				{
					printf("Error 20\n");
					return 20;
				}
			} while (NonEmpty);
			ChIErr = otrisovka(Land);
			if (ChIErr != 0)
			{
				printf("Error 21\n");
				return 21;
			}
			return 0;
		}
	}
	else if (Сh == -1) return 0;
}


/*
         1 2 3
		 4 5 6
		 7 8 9
		 
		 1 -> 1
		 2 -> 7
		 3 -> 3
		 4 -> 9

		 1 -> 2
		 2 -> 4
		 3 -> 6
		 4 -> 8
		 чтобы инвертировать знак 10 нужно ксорить с -4



123 - 1
159 - 2
147 - 3
258 - 4
357 - 5 
369 - 6
456 - 7
789 - 8
*/



























































































/*#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<vector>
#include<Windows.h>

std::vector <short int> land;
bool chod = 0;

void otrisovka(int a);
short key();
void decod(int i);
void choose(int a, short int i);
void check();
void win();
void up(int i);
void down(int i);
void right(int i);
void left(int i);

int main()
{
	CONSOLE_CURSOR_INFO cursinf;
	HANDLE h0ut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(h0ut, &cursinf);
	cursinf.bVisible = 0;
	SetConsoleCursorInfo(h0ut, &cursinf);
	for (int i = 0; i < 9; ++i) land.push_back(0);
	otrisovka(0);
	return 0;

}

void otrisovka(int a)
{
	short int b=0;
	for (int i = 0; b==0; ++i)
		{
			system("cls");
			printf("Move: Gamer num%d \n", chod);
			for (int j = 0; j < 9; ++j)
			{
				if (j % 3 == 0) printf("\n");
				decod(j);
			}
			if (land.at(a) == 0)
			{
				Sleep(500);
				system("cls");
				printf("Move: Gamer num%d \n", chod);
				for (int j = 0; j < 9; ++j)
				{
					if (j % 3 == 0) printf("\n");
					if (j == a)printf("  ");
					else decod(j);
				}
			}
			check();
			b = key();
		}
	choose(b,a);
		
}

short key()
{
	char c = 0;
	while (2 + 2 == 4)
	{
		c = _getch();
		if (c == 72) return 72;
		else if (c == 80) return 80;
		else if (c == 75)return 75;
		else if (c == 77)return 77;
		else if (c == 13)return 13;
		else if (c == 27)exit(0);
		else return 0;
	}
}

void decod(int i)
{
	if (land.at(i) == 0)printf("_ ");
	else if (land.at(i) == 1)printf("X ");
	else if (land.at(i) == 2)printf("0 ");
}

void choose(int a, short int i)
{

	if (a == 72)
	{
		if (((i - 3) >= 0) && ((i - 3) <= 8))
			otrisovka(i - 3);
		else if ((i - 3) < 0)otrisovka(i + 6);
	}
	else if (a == 80)
	{
		if (((i + 3) >= 0) && ((i + 3) <= 8))
			otrisovka(i + 3);
		else if ((i + 3) > 8)otrisovka(i - 6);
	}
	else if (a == 75)
	{
		if (((i - 1) >= 0) && ((i - 1) <= 8))
			otrisovka(i - 1);
		else if ((i - 3) < 0)otrisovka(i + 2);
	}
	else if (a == 77)
	{
		if (((i + 1) >= 0) && ((i + 1) <= 8))
			otrisovka(i + 1);
		else if ((i + 1) > 8)otrisovka(i - 2);
	}
	else if (a == 13)
	{

		if (chod == 0)
		{
			land.at(i) = 1;
			chod = 1;
		}
		else if (chod == 1)
		{
			land.at(i) = 2;
			chod = 0;
		}
		if (i != 8) otrisovka(i + 1);
		else otrisovka(0);
	}
}

void check()
{
	if (land.at(0) != 0)
	{
		if (land.at(0) == land.at(1) && land.at(0) == land.at(2)) win();
		else if (land.at(0) == land.at(3) && land.at(0) == land.at(6)) win();
		else if (land.at(0) == land.at(4) && land.at(0) == land.at(8)) win();
	}
	else if(land.at(1)!=0)
	{
		if (land.at(1) == land.at(4) && land.at(1) == land.at(7)) win();
	}
	else if (land.at(2) != 0)
	{
		if (land.at(2) == land.at(4) && land.at(2) == land.at(6)) win();
		else if (land.at(2) == land.at(5) == land.at(8))win();
	}
	else if (land.at(3) != 0)
	{
		if (land.at(3) == land.at(4) && land.at(3) == land.at(5)) win();
	}
	else if (land.at(6) != 0)
	{
		if (land.at(6) == land.at(7) && land.at(6) == land.at(8)) win();
	}
}

void win()
{
	printf("\n Gamer_%d win ! \n", !chod);
	getchar();
	exit(0);
}

void up(int i)
{
	if ((i - 3 >= 0)&&(land.at(i-3)==0))otrisovka(i - 3);
	else if ((i - 3 >= 0) && (land.at(i - 3) == 0)) otrisovka(i - 6);
	else
	{
		while(land.at(i)!=0)
		{
			++i;
			if (i > 8)i = 0;
		}
		otrisovka(i);
	}
}
void down(int i);
void right(int i);
void left(int i);*/