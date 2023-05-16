#include<iostream>
#include<string>

void StringTest(){
    std::string str("Hello Linux");
    str.resize(5);
    std::string::size_type sz = str.size();
    std::cout << sz << std::endl;
    std::cout << str << std::endl;
    std::cout << "Capacity:" << str.capacity() << std::endl;
    str.resize(20, 'x');
    std::cout << "Capacity:" << str.capacity() << std::endl;
    std::cout << str << std::endl;
}

int main(){
    StringTest();
    return 0;
}
