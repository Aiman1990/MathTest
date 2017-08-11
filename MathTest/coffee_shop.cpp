#include <sstream>
#include "coffee_shop.h"
#include "file_not_found_exception.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <map>


using namespace std;

std::string line, newline;
std::string row;
std::string category;
std::string word;
const char delim = ' ';
long count;
double  sales;

std::string blend;
std::map<std::string, double> m_CoffeeBlends, coffeequanity;

const std::map<std::string, double> &CoffeeShop::GetDrinkPrices() const noexcept
{
	return m_DrinkPrices;
}

bool CoffeeShop::LoadDrinkPrices(const std::string &fileName)
{
	std::ifstream ifstream{ "price.txt" };

	if (!ifstream.is_open()) {
		throw FileNotFoundException();
	}

	std::string line;

	//skip the first line.
	std::getline(ifstream, line);
	while (std::getline(ifstream, line)) {

		std::stringstream stringstream{ line };

		//split using comma as a delimiter.
		
		std::getline(stringstream, blend, ',');

		double price;

		stringstream >> price;

		// insert values into the map.
		m_DrinkPrices[blend] = price;
	}

	return true;
}

std::tuple<std::string, std::string, double> CoffeeShop::GetSalesStatistics(const std::string &fileName)
{
	std::ifstream ifstream{ "Sales.txt" };

	if (!ifstream.is_open()) {
		throw FileNotFoundException();
	}

	std::string line;
	std::getline(ifstream, line);

	std::map<std::string, int> roasts;

	std::map<std::string, int> extras;
	int totalOrders{ 0 };
	int totalExtrasCount{ 0 };
	int extraNullCount{ 0 };

	while (std::getline(ifstream, line)) {

		std::stringstream stringstream{ line };

		//drink
		std::getline(stringstream, line, ',');

		//roast
		std::getline(stringstream, line, ',');

		int quantity{ 0 };

		stringstream >> quantity;

		roasts[line] += quantity;

		//extra
		std::getline(stringstream, line, ',');

		if (line != "null") {
			extras[line] += quantity;
			totalExtrasCount += quantity;
		}
		else {
			//amount of drinks with no extras.
			++extraNullCount;
		}

		//total amount of ordered drinks
		totalOrders += quantity;

		sales += m_DrinkPrices[blend] * quantity;
	}

	std::sort(roasts.begin(), roasts.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
	std::sort(extras.begin(), extras.end(), [](const auto& a, const auto& b) { return a.second > b.second; });

	double percentageOfExtrasPurchase{
		static_cast<double>(extraNullCount) /
		static_cast<double >(totalOrders)
	};



	return std::make_tuple((*roasts.begin()).first,
		(*extras.begin()).first,
		percentageOfExtrasPurchase);
}
