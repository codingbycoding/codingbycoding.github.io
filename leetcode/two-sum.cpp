//g++ -std=c++0x two-sum.cpp -o two-sum.linux

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>


class Solution {
public:
	std::vector<int> twoSum(std::vector<int>& numbers, int target) {
		std::vector<int> int_vec;
		return int_vec;
	}
};

template<typename T>
void mprint(T t) {
	std::cout << t << std::endl;
}


int main(int argc, char* argv[]) {

	std::vector<int> int_vec = {100, 200, 3, 8, 208};

	std::for_each(int_vec.begin(), int_vec.end(), mprint<int>);
	return EXIT_SUCCESS;
}
