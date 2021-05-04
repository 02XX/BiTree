#ifndef BITREEEXCEPTION_H_
#define BITREEEXCEPTION_H_
#include<exception>
#include<string>
class valueError : public std::exception
{
private:
    std::string message;
public:
    valueError() : message("valueError."){}
    valueError(std::string msg) : message("valueError:" + msg){}
    const char* what() const throw()
    {
        return message.c_str();
    }
};

#endif