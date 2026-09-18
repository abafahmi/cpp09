#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}
PmergeMe::PmergeMe(const PmergeMe& other)
{
    (void)other;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        (void)other;
    }

    return *this;
}
PmergeMe::~PmergeMe()
{
}
double PmergeMe::getCurrentTime()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return static_cast<double>(tv.tv_sec) * 1000000.0
         + static_cast<double>(tv.tv_usec);
}

std::vector<size_t> PmergeMe::generateJacobsthalOrder(size_t size)
{
    std::vector<size_t> order;
    if (size == 0)
        return order;
    order.push_back(0);
    if (size == 1)
        return order;
    size_t prevJacobsthal = 1;
    size_t previous = 1;
    while (previous < size)
    {
        size_t jacobsthal = previous + 2 * prevJacobsthal;
        if (jacobsthal > size)
            jacobsthal = size;
        order.push_back(jacobsthal - 1);
        size_t k = jacobsthal - 1;
        while (k > previous)
        {
            --k;
            order.push_back(k);
        }
        prevJacobsthal = previous;
        previous = jacobsthal;
        if (previous == size)
            break;
    }

    return order;
}
size_t PmergeMe::findIdVector(const std::vector<Node>& arr, int id)
{
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (arr[i].id == id)
            return i;
    }
    return arr.size();
}
size_t PmergeMe::findIdDeque(const std::deque<Node>& arr, int id)
{
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (arr[i].id == id)
            return i;
    }
    return arr.size();
}
size_t PmergeMe::binarySearchVector(const std::vector<Node>& arr, int value, size_t end)
{
    size_t left = 0;
    size_t right = end;

    while (left < right)
    {
        size_t middle = left + (right - left) / 2;
        if (arr[middle].value < value)
            left = middle + 1;
        else
            right = middle;
    }
    return left;
}
size_t PmergeMe::binarySearchDeque(const std::deque<Node>& arr, int value, size_t end)
{
    size_t left = 0;
    size_t right = end;

    while (left < right)
    {
        size_t middle = left + (right - left) / 2;
        if (arr[middle].value < value)
            left = middle + 1;
        else
            right = middle;
    }
    return left;
}
void PmergeMe::fordJohnsonVector(std::vector<Node>& arr)
{
    if (arr.size() <= 1)
        return;
    std::vector<Node> main;
    std::vector<Pending> pend;
    size_t i = 0;
    for (; i + 1 < arr.size(); i += 2)
    {
        Node first = arr[i];
        Node second = arr[i + 1];

        if (first.value > second.value)
            std::swap(first, second);
        pend.push_back(Pending(first, second.id));
        main.push_back(second);
    }
    bool hasLeftover = false;
    Node leftover;
    if (i < arr.size())
    {
        leftover = arr[i];
        hasLeftover = true;
    }
    fordJohnsonVector(main);
    std::vector<size_t> order = generateJacobsthalOrder(pend.size());
    for (size_t j = 0; j < order.size(); ++j)
    {
        size_t pendingIndex = order[j];
        if (pendingIndex >= pend.size())
            continue;
        Pending p = pend[pendingIndex];
        size_t winnerPos = findIdVector(main, p.boundId);
        size_t end = winnerPos + 1;
        size_t pos = binarySearchVector(main, p.value.value, end);
        main.insert(main.begin() + pos, p.value);
    }
    if (hasLeftover)
    {
        size_t pos = binarySearchVector(main, leftover.value, main.size());
        main.insert(main.begin() + pos, leftover);
    }
    arr.swap(main);
}
void PmergeMe::fordJohnsonDeque(std::deque<Node>& arr)
{
    if (arr.size() <= 1)
        return;
    std::deque<Node> main;
    std::vector<Pending> pend;
    size_t i = 0;
    for (; i + 1 < arr.size(); i += 2)
    {
        Node first = arr[i];
        Node second = arr[i + 1];
        if (first.value > second.value)
            std::swap(first, second);
        pend.push_back(Pending(first, second.id));
        main.push_back(second);
    }
    bool hasLeftover = false;
    Node leftover;
    if (i < arr.size())
    {
        leftover = arr[i];
        hasLeftover = true;
    }
    fordJohnsonDeque(main);
    std::vector<size_t> order = generateJacobsthalOrder(pend.size());
    for (size_t j = 0; j < order.size(); ++j)
    {
        size_t pendingIndex = order[j];

        if (pendingIndex >= pend.size())
            continue;
        Pending p = pend[pendingIndex];
        size_t winnerPos = findIdDeque(main, p.boundId);
        size_t end = winnerPos + 1;
        size_t pos =
            binarySearchDeque(main,
                              p.value.value,
                              end);
        main.insert(main.begin() + pos, p.value);
    }
    if (hasLeftover)
    {
        size_t pos = binarySearchDeque(main, leftover.value, main.size());
        main.insert(main.begin() + pos, leftover);
    }
    arr.swap(main);
}
double PmergeMe::sortVector(std::vector<int>& vec)
{
    std::vector<Node> data;
    double start = getCurrentTime();
    for (size_t i = 0; i < vec.size(); ++i)
        data.push_back(Node(vec[i], static_cast<int>(i)));
    fordJohnsonVector(data);
    for (size_t i = 0; i < data.size(); ++i)
        vec[i] = data[i].value;
    double end = getCurrentTime();
    return end - start;
}
double PmergeMe::sortDeque(std::deque<int>& deq)
{
    std::deque<Node> data;
    double start = getCurrentTime();
    for (size_t i = 0; i < deq.size(); ++i)
        data.push_back(Node(deq[i], static_cast<int>(i)));
    fordJohnsonDeque(data);
    for (size_t i = 0; i < data.size(); ++i)
        deq[i] = data[i].value;
    double end = getCurrentTime();
    return end - start;
}
std::string PmergeMe::toString(const std::vector<int>& vec) const
{
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (i != 0)
            oss << ' ';
        oss << vec[i];
    }
    return oss.str();
}
std::string PmergeMe::toString(const std::deque<int>& deq) const
{
    std::ostringstream oss;
    for (size_t i = 0; i < deq.size(); ++i)
    {
        if (i != 0)
            oss << ' ';
        oss << deq[i];
    }
    return oss.str();
}