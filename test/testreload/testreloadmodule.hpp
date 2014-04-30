#include <iostream>

// #define PRINT_DEBUG_INFO std::cout<< "Time:" << __TIME__ << " Func:" << __FUNCTION__ << std::endl
#define PRINT_DEBUG_INFO std::cout<< "Time:" << __TIME__ << " Func:" << __PRETTY_FUNCTION__ << std::endl

class BaseCar {
public:
    BaseCar() {
    }

    virtual ~BaseCar() {
    }

    virtual void Print() {
        PRINT_DEBUG_INFO;
    }

    void NewPrint() {
        PRINT_DEBUG_INFO;
    }
};


class SportCar : public BaseCar {
public:
    void Print();
    void NewPrint();
};


typedef BaseCar (*MakeCar)(); 
typedef BaseCar* (*MakeCarPtr)();
