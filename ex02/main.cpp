#include "PmergeMe.hpp"

static int ft_atoi(const std::string& str){
    if (str.empty())
        throw std::runtime_error("Error");
    size_t i = 0;
    int sign = 1;
    long int result = 0;
    if (str[i] == '+' || str[i] == '-'){
        if (str[i] == '-')
            sign = -1;
        ++i;
    }
    if (i == str.size())
        throw std::runtime_error("Error");
    for (; i < str.size(); ++i){
        if (str[i] < '0' || str[i] > '9')
            throw std::runtime_error("Error");
        result = result * 10 + (str[i] - '0');
        if (sign == 1 && result > INT_MAX)
            throw std::runtime_error("Error");
        if (sign == -1 && -result < INT_MIN)
            throw std::runtime_error("Error");
    }
    return static_cast<int>(result * sign);
}

static void printVector(const std::vector<int>& vec){
    for (size_t i = 0; i < vec.size(); ++i){
        if (i != 0)
            std::cout << ' ';

        std::cout << vec[i];
    }
    std::cout << std::endl;
}
int main(int argc, char **argv){
    if (argc < 2){
        std::cerr << "Error" << std::endl;
        return 1;
    }
    try{
        std::vector<int> vec;
        std::deque<int> deq;
        for (int i = 1; i < argc; ++i)
        {
            int value = ft_atoi(argv[i]);
            if (value <= 0)
                throw std::runtime_error("Error");
            vec.push_back(value);
            deq.push_back(value);
        }
        std::cout << "Before: ";
        printVector(vec);
        PmergeMe pmerge;
        double vectorTime = pmerge.sortVector(vec);
        double dequeTime = pmerge.sortDeque(deq);
        std::cout << "After: ";
        printVector(vec);
        std::cout << std::fixed << std::setprecision(5);
        std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : "
                  << vectorTime << " us" << std::endl;
        std::cout << "Time to process a range of " << deq.size()
                  << " elements with std::deque : " << dequeTime << " us" << std::endl;
    }catch (const std::exception& e){
        std::cerr << "Error" << std::endl;
        return 1;
    }
    return 0;
}