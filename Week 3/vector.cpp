#include<iostream>
#include<vector>

int main() {
    int i{0};
    std::vector<int> v1(10,++i);
    std::vector<int> v2{4,2,8};
    std::cout << v1.size()<< " " << v2.size() << std::endl;
    for(int i : v1) std::cout << i << std::endl;
}