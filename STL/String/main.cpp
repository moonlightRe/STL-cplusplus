#include"mString.hpp"
using namespace std;
int main(){
    moon::mString str("Hello");

    //模拟迭代器
    moon::mString::iterator it = str.begin();
    while(it != str.end()){
        cout << *it << endl;
        it++;
    }

    //范围for 系统底层使用迭代器实现 模拟实现要和底层相同
//    for(auto ch : str){
//        cout << ch << " ";
//    }

    moon::mString str1("Linux");
    str1.insert(0, "Hello");
    cout << str1 << endl;

    cout << str1.erase(1,3) << endl;
    return 0;
}