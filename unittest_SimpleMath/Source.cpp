#include <gtest/gtest.h>
#include <file_not_found_exception.h>
#include "coffee_shop.h"

/**
* A test fixture is a group of tests.
*/
class CoffeeShopFixture : public ::testing::Test {
protected:
	CoffeeShop m_CoffeeShop;

	void SetUp() {

	}

	void TearDown() {

	}
};

/**
* Happy path
* In the TEST_F (means TEST_FIXTURE) macro privide the name of the fixture class and the
* test name.
*/
TEST_F(CoffeeShopFixture, TestLoadCoffeeBlendPriceList_DataSetsMatch_ReturnsTrue)
{
	// We need to open the file with the prices
	std::string priceListFilePath = "/Price";

	// This is the correct expected data set.
	std::map<std::string, double> prices;
	prices["Espresso"] = 1.44;
	prices["Flat White"] = 2.40;
	prices["Double Espresso"] = 2.50;
	prices["Latte"] = 2.88;
	prices["Americano"] = 2.00;
	prices["White Americano"] = 2.10;

	// Call the actual method and get the result.
	bool result{ m_CoffeeShop.LoadDrinkPrices(priceListFilePath) };

	// We expect the result to be true.
	ASSERT_TRUE(result);

	// Get the actual map from the class to compare with the expected values above.
	std::map<std::string, double> actualPrices{ m_CoffeeShop.GetDrinkPrices() };

	//Make sure the prices map is not empty.
	ASSERT_FALSE(actualPrices.empty());

	//Data sets must match.
	//That thing inside the std::for_each is a C++ lambda function.
	std::for_each(prices.cbegin(), prices.cend(), [&](const auto& pair) -> void {
		auto it = prices.find(pair.first);

		ASSERT_NE(it, actualPrices.end()); //Make sure the key exists.
		ASSERT_DOUBLE_EQ(pair.second, actualPrices[pair.first]); //Make sure the value is what expected.
	});

}

/**
* Sad path.
*/
TEST_F(CoffeeShopFixture, TestLoadCoffeeBlendPriceList_WhenFilePathIsInvalid_ThrowsFileNotFoundException)
{
	ASSERT_THROW(m_CoffeeShop.LoadDrinkPrices("I should throw up..."), FileNotFoundException);
}
