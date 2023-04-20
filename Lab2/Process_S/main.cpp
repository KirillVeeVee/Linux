#include <iostream>

int main() {
    std::cerr<<"Process S\n";
    int number=0;
    int sum=0;
    while(std::cin>>number)
        sum+=number;
    std::cout<<sum<<'\n';
    return 0;
}