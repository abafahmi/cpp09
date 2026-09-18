#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iomanip>
#include <string>
#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <stdexcept>
#include <sys/time.h>
#include <algorithm>
#include <sstream>


class PmergeMe
{
private:
    struct Node
    {
        int value;
        int id;

        Node(int v = 0, int i = 0) : value(v), id(i) {}
    };

    struct Pending
    {
        Node value;
        int boundId;

        Pending(const Node& v = Node(), int b = -1)
            : value(v), boundId(b) {}
    };

    double getCurrentTime();

    std::vector<size_t> generateJacobsthalOrder(size_t size);

    void fordJohnsonVector(std::vector<Node>& arr);
    void fordJohnsonDeque(std::deque<Node>& arr);

    size_t binarySearchVector(const std::vector<Node>& arr,
                              int value,
                              size_t end);

    size_t binarySearchDeque(const std::deque<Node>& arr,
                             int value,
                             size_t end);

    size_t findIdVector(const std::vector<Node>& arr, int id);
    size_t findIdDeque(const std::deque<Node>& arr, int id);

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    double sortVector(std::vector<int>& vec);
    double sortDeque(std::deque<int>& deq);

    std::string toString(const std::vector<int>& vec) const;
    std::string toString(const std::deque<int>& deq) const;
};

#endif