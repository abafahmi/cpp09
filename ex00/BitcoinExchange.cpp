#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){
    std::ifstream file("data.csv");
    std::string line;
    std::getline(file, line);
    while(std::getline(file, line)){
        std::string::size_type i = line.find(',');
        if (i != std::string::npos){
            std::string date = line.substr(0, i);
            std::string value = line.substr(i + 1);
            float price = static_cast<float>(std::atof(value.c_str()));
            data[date] = price;
        }
    }
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){
    *this = other;
}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other){
    if (this != &other){
        data = other.data;
    }
    return *this;
}
BitcoinExchange::~BitcoinExchange(){}
bool parcethedate(std::string date){
    if (date.length() != 11)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++){
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return false;
    int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month - 1])
        return false;
    return true;
}
void BitcoinExchange::parseTheInput(datainput input){
    if (parcethedate(input.date) == false){
        std::cerr << "Error: bad input => " << input.date << std::endl;
        return ;
    }
    if (input.number < 0){
        std::cerr << "Error: not a positive number." << std::endl;
        return ;
    }else if (input.number > 1000){
        std::cout << "Error: too large a number." << std::endl;
        return ;
    }
    std::map<std::string, float>::iterator it;
    for (it = data.begin(); it != data.end(); it++){
        if (it->first == input.date){
            std::cout << input.date << " => " 
            << input.number << " = " 
            << it->second *  input.number << std::endl;
            return ;
        }
        if (it->first > input.date){
            if (it == data.begin()){
                std::cerr << "Error: date too early." << std::endl;
                return ;
            }
            --it;
            std::cout << input.date << " => " 
            << input.number << " = " 
            << it->second *  input.number << std::endl;
            return ;
        }
    }
}


