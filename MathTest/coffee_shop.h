#ifndef COFFEE_SHOP_H
#define COFFEE_SHOP_H

#include <map>
#include <string>

class CoffeeShop {
private:
	std::map<std::string, double> m_DrinkPrices;

public:
	const std::map<std::string, double>& GetDrinkPrices() const noexcept;

	bool LoadDrinkPrices(const std::string &fileName);

	std::tuple<std::string, std::string, double> GetSalesStatistics(const std::string &fileName);

};

#endif //COFFEE_SHOP_H
