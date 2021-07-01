// Kalkulator++.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <vector>
#include <math.h>
typedef long double S;
//Pierwiastki
S fSqrt(S &numb, S lvl)
{
	return pow(numb, (1 / lvl));
}
S Kalk(std::vector<S>& tabLiczb, std::vector<char>& tabChar )
{
	S ktNaj = 1;
	for (;;)
	{

		if (tabLiczb.size() == 1)
		{
			std::cout << "\n" << tabLiczb[0];
			break;
		}
		for (int i = 0; i < tabChar.size();) //power and root
		{
			char tz = tabChar[i];
			switch (tz)
			{
			case '^':
				tabLiczb[i] = pow(tabLiczb[i], tabLiczb[i + 1]);
				tabChar.erase(tabChar.begin() + i);
				tabLiczb.erase(tabLiczb.begin() + (i + 1));
				break;
			case '!':
				tabLiczb[i] = fSqrt(tabLiczb[i], tabLiczb[i + 1]);
				tabChar.erase(tabChar.begin() + i);
				tabLiczb.erase(tabLiczb.begin() + (i + 1));
				break;
			default:
				i += 1;
				break;
			}
		}
		for (int i = 0; i < tabChar.size();) // multiply and division
		{
			char tz = tabChar[i];
			switch (tz)
			{
			case '*':
				tabLiczb[i] *= tabLiczb[i + 1];
				tabChar.erase(tabChar.begin() + i);
				tabLiczb.erase(tabLiczb.begin() + (i + 1));
				break;
			case '/':
				tabLiczb[i] /= tabLiczb[i + 1];
				tabChar.erase(tabChar.begin() + i);
				tabLiczb.erase(tabLiczb.begin() + (i + 1));
				break;
			default:
				i += 1;
				break;
			}

		}
		for (int i = 0; i < tabChar.size();) //addition and subtraction
		{
			char tz = tabChar[i];
			switch (tz)
			{
			case '+':
				tabLiczb[i] += tabLiczb[i + 1];
				tabChar.erase(tabChar.begin() + i);
				tabLiczb.erase(tabLiczb.begin() + (i + 1));
				break;
			case '-':
				tabLiczb[i] -= tabLiczb[i + 1];
				tabChar.erase(tabChar.begin() + i);
				tabLiczb.erase(tabLiczb.begin() + (i + 1));
				break;
			default:
				i += 1;
				break;
			}
		}
		for (int i = 0; i < tabChar.size();) //Specjal operations: percent and comprasion		
		{
			char tz = tabChar[i];
			switch (tz)
			{
			case '%':
				tabLiczb[i] = (tabLiczb[i] *= tabLiczb[i + 1]) / 100;
				tabChar.erase(tabChar.begin() + i);
				tabLiczb.erase(tabLiczb.begin() + (i + 1));
				break;
			case '?':
				if (tabLiczb[i] < tabLiczb[i + 1])
				{
					std::cout << tabLiczb[i] << '<' << tabLiczb[i + 1] << "  Result of operation nr." << ktNaj << " is bigger" << std::endl;
					ktNaj += 1;
				}
				else if (tabLiczb[i] > tabLiczb[i + 1])
				{
					std::cout << tabLiczb[i] << '>' << tabLiczb[i + 1] << "  Result of operation nr." << ktNaj << " is bigger" << std::endl;
				}
				else if (tabLiczb[i] == tabLiczb[i + 1])
				{
					std::cout << tabLiczb[i] << '=' << tabLiczb[i + 1] << "  Operations are equal" << ktNaj << std::endl;
					ktNaj += 1;
				}
				
				if (tabLiczb[i] <= tabLiczb[i + 1]) tabLiczb[i] = tabLiczb[i + 1];
				tabChar.erase(tabChar.begin() + i);
				tabLiczb.erase(tabLiczb.begin() + (i + 1));
				break;
			default:
				i += 1;
				break;
			}
		}
	}
	return tabLiczb[0];
}
int main()
{
	//std::cout << "Witaj w kalkulatorze! Oblicze wszystko w odpowiedniej kolejności \nZnaki których powinieneś/aś użyć do posługiwania się kalkulatorem: + dodaj, - odejmij, * pomnóż, / podziel, % procent z (100 % 20 = 20), ! pierwiastek (np. 4!2 = 2), ^ potęga (np. 2^3 = 8), ? Sprawdza które działania zwrócą większy wynik (np. 10+20 ? 25, 10+20 będzie większe), \nPamiętaj by na końcu swoich działań dać znak 'n' \n Gdy dostaniesz wynik naciśnij 'enter' aby zrestartoać kalkulator \n";
	std::cout<<"Welcome in C++ulator, calculator which respect proper order of operations! \n+ addition(2 + 2 == 4), -subtraction(4 - 2 == 2) \n* multiply(3 * 3 == 9), / division(2 / 2 == 1) \n^ power(2 ^ 2 == 4), ! root (4!2 == 2) \nAnd special operations : \n% percent(20 % 100 == 20) \n? Operation comparison(2 + 2 ? 3 - 1, result : operation nr.1 is bigger) \nOn end of operations always put 'n' or any other letter \n ";

	for (;;)
	{
		std::vector<S> tabLiczb;
		std::vector<char> tabChar;
		char znak;
		S liczba;
		do 
		{
			std::cin >> liczba >> znak;
			tabLiczb.push_back(liczba);
			tabChar.push_back(znak);
		} while (znak == '+' || znak == '-' || znak == '*' || znak == '/' || znak == '^' || znak == '%' || znak == '!' || znak == '?');

		std::vector<S> tabIntNawiasy;
		std::vector<char>tabCharNawiasy;
		Kalk(tabLiczb, tabChar);
		
		std::cin.get();
		std::cin.get();
		system("cls");
	}
}