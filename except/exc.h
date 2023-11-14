#include <exception>
#include <string>
#include <iostream>

class TMyException: std::exception {
    std::string msg;

public:
    TMyException(): msg("Error occured: ") {}
    explicit TMyException(const char* m): msg(m) {}
    explicit TMyException(const std::string& m): msg(m) {}
    const char* what () { // для визуальной проверки рабочести кода
        std::cout << msg << std::endl;
        return msg.data();
    }
    friend TMyException& operator<< (TMyException& Exc, const std::string& m);
};

TMyException& operator<< (TMyException& Exc, const std::string& m) {
    Exc.msg += m;
    return Exc;
}

class First: public TMyException {};

class Second: public TMyException {};