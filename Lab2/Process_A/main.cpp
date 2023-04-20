#include <iostream>

int main() {
    std::cerr<<"Process A\n";
    int number;
    while(std::cin>>number) {
        std::cout << number + 1;
        if(std::cin.good()) std::cout<<" ";
        else std::cout<<'\n';
    }
    return 0;
}