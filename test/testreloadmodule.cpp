//g++ -shared -fPIC testreloadmodule.cpp -o testreloadmodule.so
#include <map>

#include "testreloadmodule.hpp"

void printBeforeTest() {
    PRINT_DEBUG_INFO;
}

void printTest() {
    return;
}



void SportCar::Print() {
        PRINT_DEBUG_INFO;
        std::cout << "-------------------------------------------------------------" << std::endl;
        std::cout << "test append. Jack" << std::endl;
        std::cout << "new test append. Rose" << std::endl;
        // std::cout << "*********************************" << std::endl;

        printBeforeTest();
        printTest();


        std::cout << "##########################" << std::endl;
        std::cout << "##########################" << std::endl;
        std::cout << "##########################" << std::endl;
        std::cout << "88888888888888888888888888" << std::endl;
        std::cout << "88888888888888888888888888" << std::endl;
        std::cout << "88888888888888888888888888" << std::endl;
    }


void SportCar::NewPrint() {
        PRINT_DEBUG_INFO;
    }

BaseCar MakeSportCar() {
    return SportCar();   
}


BaseCar* MakeSportCarPtr() {
    return new SportCar();   
}

extern std::map<std::string, MakeCarPtr> g_CarMap;
extern int g_Counter;

class Proxy {
public:
    Proxy() {
        g_CarMap["SportCar"] = MakeSportCarPtr;
        std::cout << "g_Counter:" << g_Counter << std::endl;
        g_Counter += 1000;
        std::cout << "Now g_Counter:" << g_Counter << std::endl;
    }
};


Proxy g_proxy;

    
void Plane::Fly() {
    BaseVehicle::SetInternal(new AnotherPlaneInternal);
    std::cout << "Yes Yes Plane Can Fly." << std::endl;
    std::cout << "Yes Plane Can Fly." << std::endl;
    pBaseVehicleInternal_->Fly(BaseVehicle::speed_);
}
