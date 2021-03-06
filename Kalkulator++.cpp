#include <iostream>
#include <vector>
#include <math.h>

bool anErrorOccured = false;
std::vector<std::string> ErrorList;

void ERROR_report(std::string reportNote)
{
	anErrorOccured = true;
	ErrorList.push_back(reportNote);
}


typedef long double S;
S fSqrt(S& numb, S lvl) //root
{
	return pow(numb, (1 / lvl));
}
S fLog(int baseNumb, int power) //Logarithm
{
	if (baseNumb > 0 && baseNumb != 1)
	{
		int exponent = 0;
		while (pow(baseNumb, exponent) < power)
		{
			exponent += 1;
		}

		if ((pow(baseNumb, exponent) != power))
		{
			ERROR_report("ERROR::Logarithm exponent isn't Natural Number");
		}

		return exponent;
	}
	else ERROR_report("ERROR::Base of logarithm must be bigger than zero and can't be one");
}
S Calculator(std::vector<S>& tabNum, std::vector<char>& tabChar)
{
	S ktNaj = 1;
	for (;;)
	{

		if (tabNum.size() == 1)
		{
			if (!anErrorOccured)
			{
				std::cout << "\n" << tabNum[0];
				break;
			}
			else
			{
				for (int i = 0; i < ErrorList.size(); i++)
				{
					std::cout << ErrorList[i]<<std::endl;
				}
				break;
			}
		}
		for (int i = 0; i < tabChar.size();) //power, root and log
		{
			char tz = tabChar[i];
			switch (tz)
			{
			case '^':
				tabNum[i] = pow(tabNum[i], tabNum[i + 1]);
				tabChar.erase(tabChar.begin() + i);
				tabNum.erase(tabNum.begin() + (i + 1));
				break;
			case '!':
				tabNum[i] = fSqrt(tabNum[i], tabNum[i + 1]);
				tabChar.erase(tabChar.begin() + i);
				tabNum.erase(tabNum.begin() + (i + 1));
				break;
			case 'L':
				tabNum[i] = fLog(tabNum[i], tabNum[i + 1]);
				tabChar.erase(tabChar.begin() + i);
				tabNum.erase(tabNum.begin() + (i + 1));
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
				tabNum[i] *= tabNum[i + 1];
				tabChar.erase(tabChar.begin() + i);
				tabNum.erase(tabNum.begin() + (i + 1));
				break;
			case '/':
				tabNum[i] /= tabNum[i + 1];
				tabChar.erase(tabChar.begin() + i);
				tabNum.erase(tabNum.begin() + (i + 1));
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
				tabNum[i] += tabNum[i + 1];
				tabChar.erase(tabChar.begin() + i);
				tabNum.erase(tabNum.begin() + (i + 1));
				break;
			case '-':
				tabNum[i] -= tabNum[i + 1];
				tabChar.erase(tabChar.begin() + i);
				tabNum.erase(tabNum.begin() + (i + 1));
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
				tabNum[i] = (tabNum[i] *= tabNum[i + 1]) / 100;
				tabChar.erase(tabChar.begin() + i);
				tabNum.erase(tabNum.begin() + (i + 1));
				break;
			case '?':
				if (tabNum[i] < tabNum[i + 1])
				{
					std::cout << tabNum[i] << '<' << tabNum[i + 1] << "  Result of operation nr." << ktNaj << " is bigger" << std::endl;
					ktNaj += 1;
				}
				else if (tabNum[i] > tabNum[i + 1])
				{
					std::cout << tabNum[i] << '>' << tabNum[i + 1] << "  Result of operation nr." << ktNaj << " is bigger" << std::endl;
				}
				else if (tabNum[i] == tabNum[i + 1])
				{
					std::cout << tabNum[i] << '=' << tabNum[i + 1] << "  Operations are equal" << ktNaj << std::endl;
					ktNaj += 1;
				}

				if (tabNum[i] <= tabNum[i + 1]) tabNum[i] = tabNum[i + 1];
				tabChar.erase(tabChar.begin() + i);
				tabNum.erase(tabNum.begin() + (i + 1));
				break;
			default:
				i += 1;
				break;
			}
		}
	}
	return tabNum[0];
}
int main()
{
	std::cout << "Welcome in C++ulator, calculator which respect proper order of operations! \n+ addition(2 + 2 == 4), - subtraction(4 - 2 == 2) \n* multiply(3 * 3 == 9), / division(2 / 2 == 1) \n^ power (2 ^ 2 == 4), ! root (4!2 == 2), L  logarithm (2L8 == 3) \nAnd special operations: \n% percent(20 % 100 == 20) \n? Operation comparison(2 + 2 ? 3 - 1, result : operation nr.1 is bigger) \nOn end of operations always put 'n' or any other letter, after operation press Enter to restart \n  Brackets not supported (yet) ";
	
	for (;;)
	{
		std::vector<S> tabNum;
		std::vector<char> tabChar;
		char cha;
		S number;
		
		do
		{
			std::cin >> number >> cha;
			tabNum.push_back(number);
			tabChar.push_back(cha);
		} while (cha == '+' || cha == '-' || cha == '*' || cha == '/' || cha == '^' || cha == '%' || cha == '!' || cha == '?' || cha == 'L');

		Calculator(tabNum, tabChar);

		std::cin.get();
		std::cin.get();
		system("cls");
	}
}