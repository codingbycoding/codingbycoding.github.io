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



class BaseVehicleInternal {
public:
    
    virtual std::string DriverName(std::string& inDriverName) {
        return inDriverName;
    }

    virtual void Fly(float inSpeed) {
        std::cout << "BaseVehicleInternal void Fly" << std::endl;
    }
        
};


//TODO reload need suspend all operations before SetInternal succeed.
class BaseVehicle {
public:

    BaseVehicle() : driverName_(""), speed_(0), pBaseVehicleInternal_(new BaseVehicleInternal) {
        
    }
    
    bool SetInternal(BaseVehicleInternal* inBaseVehicleInternal) {
        std::cout << "SetInternal:::::::" <<std::endl;
        if(NULL == inBaseVehicleInternal) {
            return false;
        }

        delete pBaseVehicleInternal_;
        pBaseVehicleInternal_ = inBaseVehicleInternal;
        return true;        
    }
    
    virtual std::string DriverName() {
        pBaseVehicleInternal_->DriverName(driverName_);
    }

    virtual void Fly() {
        std::cout << "Dont Know How To Fly..." << std::endl;
        pBaseVehicleInternal_->Fly(speed_);
    }
    
public:
    BaseVehicleInternal* pBaseVehicleInternal_;

public:
    std::string driverName_;
    float speed_;
};


class PlaneInternal : public BaseVehicleInternal {
public:
    virtual void Fly(float inSpeed) {
        std::cout << "Fly Speed is: " << inSpeed << std::endl;
    }    
    
};


class AnotherPlaneInternal : public BaseVehicleInternal {
public:
    virtual void Fly(float inSpeed) {
        std::cout << "AnotherPlaneInternal " << std::endl; 
        std::cout << "Fly Speed is: " << inSpeed << std::endl;
    }    
    
};


class Plane : public BaseVehicle {
public:
    Plane() {
        BaseVehicle::SetInternal(new PlaneInternal); 
    }
    
    void Fly();

};
