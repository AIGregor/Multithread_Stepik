#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

enum class OUTPUT_CODES
{
	ERROR
};

class Member
{
public:
	Member() : index(1), variable(""), power(1) {};
	Member(std::string& strPart) 
	{
		index = mmParser.getIndex(strPart);
		variable = mmParser.getVariable(strPart);
		power = mmParser.getPower(strPart);
	};
	
	int index;
	std::string variable;
	int power;
	
private:

	class MemberParser
	{
	public:
		int getIndex(std::string& strVal) {
			size_t pos = strVal.find('*');

			if (pos == std::string::npos)
				if (strVal[0] == '-')
					return -1;
				else
					return 1;

			std::string temp = strVal.substr(0, pos);
			return std::stoi(temp);
		};

		std::string getVariable(std::string& strVal) {
			size_t posPow = strVal.find('^');
			size_t posInd = strVal.find('*');
			std::string temp;

			if (posPow == std::string::npos)
			{
				if (posInd != std::string::npos)
				{
					temp = strVal.substr(posInd + 1);	
					return temp;
				}
				return strVal;
			}
			else
			{
				if (posInd == std::string::npos)
				{
					size_t posMinus = strVal.find('-');
					if (posMinus == std::string::npos)
						temp = strVal.substr(0, posPow);
					else
						temp = strVal.substr(posMinus + 1, posPow - 1);
					return temp;
				}
			}
			if (posPow >= posInd)
				temp = strVal.substr(posInd + 1, posPow - posInd - 1);
			return temp;
		};

		int getPower(std::string& strVal) {
			size_t pos = strVal.find('^');

			if (pos == std::string::npos)
				return 1;

			std::string temp = strVal.substr(pos + 1);
			return std::stoi(temp);
		};
	};

	OUTPUT_CODES code;
	MemberParser mmParser;
};

class Polynom
{
private:
	std::string stringReplacer(const std::string& inputStr, const std::string& src, const std::string& dst)
	{
		std::string result(inputStr);

		size_t pos = result.find(src);
		while (pos != std::string::npos) {
			result.replace(pos, src.size(), dst);
			pos = result.find(src, pos);
		}

		return result;
	}

	std::vector<std::string> split(const std::string& s, char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}

public:
	Polynom(std::string& strInput)
	{
		polynomParts = pasreInputString(strInput);
	};

	std::vector<Member> pasreInputString(std::string& strInput)
	{
		std::vector<Member> polynomParts;

		// Привести к нормальному виду
		// -x^2-x = 0 ->-> +=x^2+=x = 0
		std::string strRes = stringReplacer(strInput, "-", "+=");
		std::vector<std::string> line_parts{ split(strRes, '+') };

		for (auto part : line_parts)
		{
			if (part == "")
				continue;
			std::string tempPart = stringReplacer(part, "=", "-");

			Member mmPart(tempPart);
			polynomParts.emplace_back(mmPart);
		}

		return polynomParts;
	}
	
	// Вывод в поряке убывания степеней
	void calcDerivative() {
		for (auto& part : polynomParts)
		{
			if (part.power > 1)
			{
				part.index *= part.power;
				--part.power;
			}
			else if (part.power == 1)
			{
				// constant
				if (isdigit(part.variable[0]))
				{
					part.variable = "0";	
					continue;
				}
				else // valiable
				{
					part.variable = std::to_string( part.index );
				}
			}
		}

		simplifyConstant();
	};

	void simplifyConstant()
	{
		int constant = 0;
		for (auto& part : polynomParts)
		{
			if (isdigit(part.variable[0]) || part.variable[0] == '-')
			{
				constant += std::stoi(part.variable);
				part.variable = "0";
			}		
		}
		polynomParts.erase(	
			std::remove_if(polynomParts.begin(), polynomParts.end(),
						[](Member a) { return a.variable == "0";} ), 
			polynomParts.end());

		if (constant != 0)
		{
			Member mmPart;
			mmPart.variable = std::to_string( constant );
			polynomParts.emplace_back(mmPart);
		}
	};

	void sortByPower()
	{
		std::sort(polynomParts.begin(), polynomParts.end(),
			[](Member a, Member b) { return a.power > b.power; });
	};

	std::string print()
	{
		std::string result = "";
		for (size_t i= 0; i < polynomParts.size(); ++i)
		{
			auto part = polynomParts[i];

			std::string plus = i == 0 ? "" : "+";

			//std::string minus = part.index < 0 ? "" : "-";
			std::string power = part.power == 1 ? "" : "^";			
			std::string sign = part.index < 0 ? "" : plus;
			std::string res;
			
			if (!isdigit(part.variable[0]) && part.variable[0] != '-')
			{
				res = sign + (part.index == -1 ? "" : std::to_string(part.index));

				if (!isdigit(part.variable[0]))
					res += (res == "" ? "" : "*") + part.variable;
				if (power != "")
					res += power + std::to_string(part.power);
			}
			else
			{
				if (part.variable[0] == '-')
					sign = "";
				res = sign + part.variable;
			}

			result += res;
		}
		return result;
	}

	std::vector<Member> polynomParts;
};

std::string derivative(std::string polynomial) {

	Polynom poly(polynomial);

	poly.calcDerivative();
	poly.sortByPower();
	poly.print();

	return poly.print();
}

int main()
{
	while (std::cin)
	{
		std::string line;
		std::getline(std::cin, line);

		std::cout << derivative(line) << std::endl;
	}
    return 0;
}