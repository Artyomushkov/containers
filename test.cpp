#include <iostream>
#include <set>

int main(void) {

    std::set<const int> test;
    test.insert(1);
    test.insert(20);
    std::set<const int>::const_iterator iter = test.begin();
    while (iter != test.end())
    {
        std::cout << *iter;
        iter++;
    }
}
