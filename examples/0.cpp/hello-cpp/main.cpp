
#include <iostream>

#include <vector> // error C2679: binary '<<': no operator found which takes a right-hand operand of type 'std::string'

class A{
    public:
    A(){}
    int a = 0;
}

class B{
    
}
int main(){
    std::string msg = "hello cpp";
    std::string msg2 = msg;
    A a;
    std::vector<int> arr{1,2,3};
    const char* cstr= msg.c_str();
    std::cout << cstr << std::endl;
}