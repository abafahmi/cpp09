#ifndef BI_HPP
#define BI_HPP

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

struct datainput{
    std::string date;
    float number;
};

class BitcoinExchange{
    private:
        std::map<std::string, float> data;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        void parseTheInput(datainput input);
        void addDateAndPrice(std::string date, float price);
        void printeData();
};
#endif