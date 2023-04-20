#include <iostream>

int main() {
    std::cerr<<"Process P\n";
    int number;
    while(std::cin>>number) {
        std::cout << number * number * number;
        if(std::cin.good()) std::cout<<" ";
        else std::cout<<'\n';
    }
    return 0;
}
