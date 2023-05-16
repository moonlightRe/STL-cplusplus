
#ifndef STL_MSTRING_HPP
#define STL_MSTRING_HPP

#include<iostream>
#include <cstdio>
#include <cstring>
#include <cassert>

namespace moon{
    class mString {

    public:
        //迭代器
        typedef char* iterator;

        iterator begin(){
            return _str;
        }

        iterator end(){
            return _str + _size;
        }

        //默认构造函数
        mString()
        :_str(new char[1]),
        _size(0),
        _capacity(0){}

        //普通构造函数
        explicit mString(const char* str = ""){
            _size = strlen(str);
            _capacity = _size;
            _str = new char[strlen(str) + 1];
            strcpy(_str, str);
        }
        //析构函数
        ~mString(){
            if(_str){
                free(_str);
                _size = _capacity = 0;
                _str = nullptr;
            }
        }

        const char* c_str(){
            return _str;
        }

        [[nodiscard]] size_t size() const{
            return _size;
        }

        char& operator[](size_t pos){
            assert(pos < _size);
            return _str[pos];
        }

        //扩容
        void reserve(size_t n){
            if(n > _capacity){
                char* data = new char[n + 1];
                strcpy(data, _str);
                delete[] _str;
                _str = data;
                _capacity = n;
            }
        }

        void resize(size_t n, char ch = '\0'){
            if(n > _capacity){
                reserve(n);
                for(size_t i = _size; i < n; i++){
                    _str[i] = ch;
                }
                _size = n;
                _str[_size] = '\0';
            }
            else{
                _str[n] ='\0';
                _size = n;
            }

        }

        //模拟实现尾插
        void push_back(char ch){
            if(_size == _capacity){
                size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
                reserve(newCapacity);
            }
            _str[_size] = ch;
            _size++;
            _str[_size] = '\0';
        }

        void append(const char* str){
            size_t len = strlen(str);
            if(_size + len > _capacity){
                reserve(_size + len);
            }
            strcpy(_str + _size, str);
            _size += len;

        }

        mString& operator+=(char ch){
            push_back(ch);
            return *this;
        }

        mString& operator+=(const char* str){
            append(str);
            return *this;
        }

        //插入字符
        mString& insert(size_t pos, char ch){
            assert(pos <= _size);
            if(_size == _capacity){
                size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
                reserve(newCapacity);
            }

            //挪动数据
            size_t end = _size;
            while(end >= pos){
                _str[end + 1] = _str[end];
                //防止size_t减小到-1导致死循环
                //使用break语句或者将end向后移动一位，取消=条件
                if(end == 0) break;
                end--;
            }
            _str[pos] = ch;
            _size++;
            return *this;
        }

        mString& insert(size_t pos, const char* str){
            size_t len = strlen(str);
            if(_size + len > _capacity){
                reserve(_size + len);
            }

            size_t end1 = _size;
            //将从pos位置开始的字符均向后挪动len个单位
            //len为str有效字符的长度 且在此挪动过程中，将源字符串的'\0'也一并移动至结尾 后续无需考虑
            while(end1 >= pos){
                _str[end1 + len] = _str[end1];
                //使用size_t需要特别注意
                if(end1 == 0) break;
                end1--;
            }

            //strncpy(_str + pos, str, len);

            size_t begin = pos;
            size_t end2 = 0;
            while(end2 < len){
                _str[begin] = str[end2];
                begin++;
                end2++;
            }

            _size += len;
            return *this;
        }

        mString& erase(size_t pos, size_t len = npos){
            assert(_size > 0);
            assert(pos < _size);

            //删除pos之后的全部字符
            if(len == npos || pos + len >= _size - pos){
                _str[pos] = '\0';
                _size = pos;
            }
            else{
                size_t begin = pos + len;
                while(begin <= _size){
                    _str[begin - len] = _str[begin];
                    begin++;
                }
                _size -= len;
            }
            return *this;
        }

        size_t find(const char& ch, size_t pos = 0){
            assert(pos < _size);
            while(pos < _size){
                if(_str[pos] == ch){
                    return pos;
                    pos++;
                }
            }
            return npos;
        }

        size_t find(const char* str, size_t pos = 0){
            assert(pos < _size);
            const char* ptr = strstr(_str + pos, str);
            if(ptr == nullptr){
                return npos;
            }else{
                return ptr - _str;
            }
        }

    private:
        char* _str;
        size_t _size;
        size_t _capacity;
        const static size_t npos = -1;
    };

}

//重载<<输出运算符
std::ostream& operator<<(std::ostream& cout, moon::mString& str){
    cout << str.c_str();
    return cout;
}

#endif //STL_MSTRING_HPP
