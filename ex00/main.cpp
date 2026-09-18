#include "BitcoinExchange.hpp"

int main(int ac, char  **av){
    if (ac != 2){
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }
    std::ifstream file(av[1]);
    if (!file.is_open()){
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }
    BitcoinExchange btc;
    std::string line;
    datainput input;
    getline(file, line);
    while (getline(file, line)){
        if (line.empty())
            continue;
        std::string::size_type i = line.find('|');
        if (i ==  std::string::npos){
            std::cerr << "Error: bad input => " << line << std::endl;
        }
        else {
            try{
                input.date = line.substr(0, i);
                std::string num = line.substr(i + 1);
                input.number = static_cast<float>(std::atof(num.c_str()));
            }catch (std::out_of_range &e){
                std::cerr << "Error : "<< e.what() << std::endl;
            }
            btc.parseTheInput(input);
        }   
    }
}