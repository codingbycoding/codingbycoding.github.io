//g++ testreloadmain.cpp -rdynamic -ldl -o testreloadmain.linux

#include <iostream>
#include <cstdlib>
#include <map>
#include <dlfcn.h>
#include <signal.h>
#include <cstring>
#include <unistd.h>

#include "testreloadmodule.hpp"


std::map<std::string, MakeCarPtr> g_CarMap;
BaseCar* g_pMyCar = NULL;


int funOne() {
    PRINT_DEBUG_INFO;    
}

enum ReloadEnum{
    SUCC_RELOAD = 0,
    ERR_RELOAD = -1    
};

class OperateWrapper {

public:
    OperateWrapper() : so_data_handle_(NULL), so_module_handle_(NULL), g_Counter_(NULL) {
        
    }

    ~OperateWrapper() {
        if(NULL == so_data_handle_) {
            dlclose(so_data_handle_);
        }
        if(NULL == so_module_handle_) {
            dlclose(so_module_handle_);
        }        
    }

    int init_load_so() {
        if(NULL == (so_data_handle_ = dlopen("testreloadglobaldata.so", RTLD_NOW|RTLD_GLOBAL))
           || NULL == (so_module_handle_ = dlopen("testreloadmodule.so", RTLD_NOW|RTLD_GLOBAL))) {
            std::cout << dlerror() << std::endl;
            return ERR_RELOAD;
        } else {            
            if(NULL != (g_Counter_ = dlsym(so_data_handle_, "g_Counter"))) {
                return SUCC_RELOAD;
            }
        }
    }

    void before_reload_so() {
        if(NULL != g_pMyCar) {
            delete g_pMyCar;
            g_pMyCar = NULL;
                
        }
    }
    int reload_so() {
        dlclose(so_data_handle_);
        dlclose(so_module_handle_);
        so_data_handle_ = NULL;
        so_module_handle_ = NULL;
        
        if(NULL == (so_data_handle_ = dlopen("testreloadglobaldata.so", RTLD_NOW|RTLD_GLOBAL))
           || NULL == (so_module_handle_ = dlopen("testreloadmodule.so", RTLD_NOW|RTLD_GLOBAL))) {
            std::cout << dlerror() << std::endl;
            return ERR_RELOAD;
        } else {            
            if(NULL != (g_Counter_ = dlsym(so_data_handle_, "g_Counter"))) {
                g_pMyCar = g_CarMap["SportCar"]();
                    
            }
            return SUCC_RELOAD;
            
        }
    }
    
    void PrintGlobalData() {
        if(NULL != so_data_handle_) {
            std::cout << "g_Counter:" << *(int*)g_Counter_ << std::endl;
        }
    }

    void SetGlobalCounter(int InCounter) {
        *(int*)g_Counter_ = InCounter;
    }

private:
    void* so_data_handle_;
    void* so_module_handle_;
    void* g_Counter_;
    SportCar* pSportCar_;
    
};


bool g_bNeedStop = false;    
OperateWrapper g_opWrap;


void sigaction_handle_fun(int signo, siginfo_t * siginfo, void * sigcontext) {
    std::cout << "sigaction_handle_fun signo:" << signo << std::endl;
    char* strsig = strsignal(signo);
    if(strsig != NULL) {
            std::cout << "strsig:" << strsig << std::endl;
    }
  
    if(SIGUSR1 == signo) {
        std::cout << "USR1 going to reload_so()" << std::endl;
        g_opWrap.reload_so();  
    } else if (SIGUSR2 == signo) {
        g_bNeedStop = true;
        return;
    }  
}



int main(int argc, char* argv[]) {
    
    PRINT_DEBUG_INFO;
    
    g_opWrap.init_load_so();
    
    g_opWrap.PrintGlobalData();
    g_opWrap.SetGlobalCounter(1080);
    g_opWrap.PrintGlobalData();

    // BaseCar* myCar = g_CarMap["SportCar"]();
    // myCar->Print();
    // myCar->NewPrint();

    g_pMyCar = g_CarMap["SportCar"]();
    g_pMyCar->Print();
    g_pMyCar->NewPrint();


    struct sigaction act, oact;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = sigaction_handle_fun;
    sigaction(SIGUSR1, &act, &oact);
    sigaction(SIGUSR2, &act, &oact);

    while(!g_bNeedStop) {
        sleep(3);
        // myCar->Print();
        // myCar->NewPrint();

        g_pMyCar->Print();
        g_pMyCar->NewPrint();
    }

    delete g_pMyCar;
    g_pMyCar = NULL;

    // delete myCar;
    // myCar = NULL;
    
    return EXIT_SUCCESS;
}
