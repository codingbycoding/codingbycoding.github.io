//g++ r_p_s.cpp -o r_p_s.linux  -ggdb -std=c++11 -Wall -fdiagnostics-color=always

//this is a test of game Rock, Paper, Scissors.

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <map>
#include <vector>
#include <functional>



enum GameOption {
	kGameOptionUnknown = 0,
	kRock = 1,
	kPaper = 2,
	kScissors = 3
};

enum GameResult {
	kGameResultUnknown = 0,
	kWin = 1,
	kLose = 2,
	kTie = 3,
};

std::ostream& operator<<(std::ostream& os, const GameResult& rhs) {
	switch(rhs) {
	case kGameResultUnknown:
		os << "GameResultUnknown";
		break;
	case kWin:
		os << "Win";
		break;
	case kLose:
		os << "Lose";
		break;
	case kTie:
		os << "Tie";
		break;		
	}
			
	return os;
}

class GameOptionPair {
public:
private:
	std::pair<GameOption, GameOption> option_pair_;
};


// namespace std {
// template<>
// struct less<GameOption> : public binary_function<GameOption, GameOption, bool>
// {
// bool
// operator()(const GameOption& __x, const GameOption& __y) const
// { return __x < __y; }
// };

// }

//static std::map<GameOptionPair, GameResult> g_resultMap;
static std::map<std::pair<GameOption, GameOption>, GameResult> g_resultMap;

GameResult game_once_2(const GameOption& lhs, const GameOption& rhs) {	
	return kWin;
}

GameResult game_once_pair(const std::pair<GameOption, GameOption>& rhs) {	
	return g_resultMap[rhs];
}

std::vector<GameResult> game_once_vec(const std::vector<GameOption>& rhs) {
	std::vector<GameResult> game_esult_vec;
	// for(auto i : rhs) {

	// }
	
	return game_esult_vec;
}

static void init_game_option_pair2result_map() {
	g_resultMap = {
		{std::pair<GameOption, GameOption>(kRock, kRock), kTie},
		{std::pair<GameOption, GameOption>(kRock, kPaper), kLose},
		{std::pair<GameOption, GameOption>(kRock, kScissors), kWin},
		{std::pair<GameOption, GameOption>(kPaper, kRock), kWin},
		{std::pair<GameOption, GameOption>(kPaper, kPaper), kTie},
		{std::pair<GameOption, GameOption>(kPaper, kScissors), kLose},
		{std::pair<GameOption, GameOption>(kScissors, kRock), kLose},
		{std::pair<GameOption, GameOption>(kScissors, kPaper), kWin},
		{std::pair<GameOption, GameOption>(kScissors, kScissors), kTie},
	};
	
}

int main(int argc, char**) {
	init_game_option_pair2result_map();

	std::cout << game_once_pair(std::pair<GameOption, GameOption>(kPaper, kPaper)) << std::endl;
	std::cout << game_once_pair(std::pair<GameOption, GameOption>(kPaper, kScissors)) << std::endl;
	
	return EXIT_SUCCESS;
}
