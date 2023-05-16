#include<iostream>
#include<string>
#include <algorithm>

using namespace std;

namespace moon{
    //模拟实现
    template<class T>
    class basic_string{
    private:
        T* _str;
        size_t _size;
        size_t _capacity;
    };
    typedef basic_string<char> string;
}

int main(){
    std::string str("Hello C++");
    std::cout << str.size() << std::endl;
    size_t begin = 0;
    size_t end = str.size() - 1;
    while(begin < end){
        swap(str[begin++], str[end--]);
    }
    cout << str << endl;
    reverse(str.begin(), str.end());
    cout << str << endl;
    //cout << str[end - 1] << endl;
    return 0;
}