#include <iostream>

int main() {
    std::cerr<<"Process M\n";
    int number;
    while(std::cin>>number) {
        std::cout << number * 7;
        if(std::cin.good()) std::cout<<" ";
        else std::cout<<'\n';
    }
    return 0;
}
