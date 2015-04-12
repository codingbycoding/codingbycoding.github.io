//g++ c++11.cpp -o c++11.linux -ggdb -std=c++11 -Wall -lpthread -fdiagnostics-color=always


//because I install GCC 4.9.2 in /usr/local and the system also has an old version GCC 4.4.7 in /usr   
//export LD_LIBRARY_PATH=/usr/local/lib64/:${LD_LIBRARY_PATH}


//linux platform use c++11 thread should add -lpthread 

//g++ c++11.cpp -o c++11.linux -ggdb -std=c++11 -Wall

//g++ c++11.cpp -o c++11.linux -ggdb -std=c++11 -Wl,--no-as-needed -lpthread

//g++ (GCC) 4.9.2

#if __cplusplus < 201103L
#error "You should use a compiler that supports C++11 Standard." //pre compiler time
#endif


#include <iostream>
#include <atomic>
#include <cstdlib>
#include <cassert>
#include <mutex>
#include <thread>
#include <chrono>
#include <memory>
#include <vector>


enum class Phone_Type {kCellphone, kTelephone}; //strongly-typed enums


struct TPod {
	int number;
	char x;
};

struct alignas(8) T8Pod {
	int number;
	char x;
};

struct alignas(16) T16Pod {
	int number;
	char x;
};

std::mutex g_mutex;

int thread_local err_code; //thread_local variable.
std::atomic_llong g_total {0};

template<typename T>
void printT(T t) {
	static_assert(sizeof(t) == sizeof(int), "number > 0"); //compiler time assert
}

void th_func(int number) {

	
	assert(number > 0); //run time assert
	g_mutex.lock();
	std::cout << "number:" << number << std::endl;
	g_mutex.unlock();

	std::cout << "g_total:" << g_total++ << std::endl;
}



//auto used in function return type must use tail decltype 
auto add(int a, int b) -> decltype(a+b) {
	return a+b;
}

class Person {
public:
	Person() = default; // make it POD again.
	//rvalue reference(anonymous object). reduce unnecessary copy cost
	Person(Person&&);
	explicit Person(const std::string& name);
    explicit Person(const std::string&& name);

	Person(Person&) = delete; // dont generate default Copy ctor. 
	virtual void print();
	const std::string name() const;  
private:
	std::string name_;
};


class Student : public Person {
public:
	Student(const std::string& name);
	 //override means it is override one virtual function.(if there is no the same signature virtual function, error occurs.
	//final means it cannt to be overrided again. 
	virtual void print() override final;
	
};


Person::Person(const std::string& name) {
	name_ = name;
}

Person::Person(const std::string&& name) {
	std::cout << "Person rvalue reference "<< std::endl;
	name_ = std::move(name);
}

const std::string Person::name() const {
	return name_;
}

void Person::print() {
	std::cout << "Person: " << name() << std::endl;
}


Student::Student(const std::string& name) : Person(name) {
	
}

void Student::print() {
	std::cout << "Student: " << name() << std::endl;
}



int main() {

	auto xx = 8;
	std::cout << "xx:" << xx << std::endl;


	std::thread th1(th_func, 88);
	
	std::this_thread::sleep_for(std::chrono::milliseconds(2));

	th1.detach();

	std::cout << add(8, 8) << std::endl;


	std::shared_ptr<Person> p = std::make_shared<Person>("abc");
	p->print();

	p = std::make_shared<Student>("cba");
	p->print();

	p = std::make_shared<Person>("abc again");
	p->print();

	// Person p2(*p);// will failed because Person(Person&) = delete

	auto lambda_fun = [](const std::string& str) {std::cout << str << std::endl;};

	lambda_fun("jack");

	
	std::vector<std::string> str_vec = {"HIS", "IS", "AS", "THOSE"};
	for(const auto& it : str_vec) {
		lambda_fun(it);
	}
	

	int* pi = nullptr;
	pi = pi;


	std::function<int(int)> fib = [&fib](int n) {return n<2 ? 1 : fib(n-1)+fib(n-2); };

	std::cout << "fib(2):" << fib(2) << std::endl;
	std::cout << "fib(20):" << fib(20) << std::endl;

	int narr[] = {8, 80, 88};
	for(auto i=std::begin(narr); i!=std::end(narr); i++) {
		std::cout << *i << std::endl;
	}


	auto fun_lam =  [=](){std::cout << "xx:" << xx << std::endl;};
	fun_lam();
	
	printT(8);

	std::cout << "alignof(TPod):" << alignof(TPod) << std::endl;
	std::cout << "sizeof(TPod):" << sizeof(TPod) << std::endl;

	std::cout << "alignof(T8Pod):" << alignof(T8Pod) << std::endl;
	std::cout << "sizeof(T8Pod):" << sizeof(T8Pod) << std::endl;

	std::cout << "alignof(T16Pod):" << alignof(T16Pod) << std::endl;
	std::cout << "sizeof(T16Pod):" << sizeof(T16Pod) << std::endl;

	std::cout << R"(raw string
    continue...)" << std::endl; //raw string user R"()"

	char utf8[] = u8"这是 UTF8";
	char16_t utf16[] = u"这是 UTF16";
	char32_t utf32[] = U"这是 UTF32";	

	std::cout << utf8 << "  " << utf16 << "  " << utf32 << std::endl;

	
	return EXIT_SUCCESS;
}
