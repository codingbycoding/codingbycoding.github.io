//g++ r_p_s.cpp -o r_p_s.linux  -ggdb -std=c++11 -Wall -fdiagnostics-color=always

//this is a test of game Rock, Paper, Scissors.

#include <iostream>
#include <cstdlib>
#include <map>
#include <functional>



enum GameOption {
	kRock = 1,
	kPaper = 2,
	kScissors = 3
};

enum GameResult {	
	kSuccess = 1,
	kDefeat = 2,
	kDraw = 3,
};

std::ostream& operator<<(std::ostream& os, const GameResult& rhs) {
	switch(rhs) {
	case kSuccess:
		os << "Success";
		break;
	case kDefeat:
		os << "Defeat";
		break;
	case kDraw:
		os << "Draw";
		break;		
	}
			
	return os;
}

class GameOptionPair {
public:
	// bool operator<(const GameOptionPair& rhs) {
	// 	// return option_pair_.first rhs.option_pair_.first) != 0 ? std::less<GameOption>(option_pair_.first, rhs.option_pair_.first) : std::less<GameOption>(option_pair_.second, rhs.option_pair_.second);
				
	// 	return std::less<GameOption>(option_pair_.first, rhs.option_pair_.first) != 0 ? std::less<GameOption>(option_pair_.first, rhs.option_pair_.first) : std::less<GameOption>(option_pair_.second, rhs.option_pair_.second);

	// }

private:
	std::pair<GameOption, GameOption> option_pair_;
};

// bool operator<(GameOption lhs, GameOption rhs) {
	
// }
	
// class GameOptionVec {
// public:
// 	bool operator<(GameOptionVec rhs) {
		
// 	}
	
// private:
// };

// bool std::less<GameOption>(option_pair_.first, rhs.option_pair_.first) {
// 	std::less<GameOption>(option_pair_.first, rhs.option_pair_.first);
// }

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
	return kSuccess;
}

GameResult game_once_pair(const std::pair<GameOption, GameOption>& rhs) {	
	return g_resultMap[rhs];
}

static void init_game_option_pair2result_map() {
	g_resultMap = {
		{std::pair<GameOption, GameOption>(kRock, kRock), kDraw},
		{std::pair<GameOption, GameOption>(kRock, kPaper), kDefeat},
		{std::pair<GameOption, GameOption>(kRock, kScissors), kSuccess},
		{std::pair<GameOption, GameOption>(kPaper, kRock), kSuccess},
		{std::pair<GameOption, GameOption>(kPaper, kPaper), kDraw},
		{std::pair<GameOption, GameOption>(kPaper, kScissors), kDefeat},
		{std::pair<GameOption, GameOption>(kScissors, kRock), kDefeat},
		{std::pair<GameOption, GameOption>(kScissors, kPaper), kSuccess},
		{std::pair<GameOption, GameOption>(kScissors, kScissors), kDraw},
	};
	
}

int main(int argc, char**) {
	init_game_option_pair2result_map();

	std::cout << game_once_pair(std::pair<GameOption, GameOption>(kPaper, kPaper)) << std::endl;
	std::cout << game_once_pair(std::pair<GameOption, GameOption>(kPaper, kScissors)) << std::endl;
	
	return EXIT_SUCCESS;
}
