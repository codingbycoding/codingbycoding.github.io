//g++ r_p_s.cpp -o r_p_s.linux  -ggdb -std=c++11 -Wall -fdiagnostics-color=always

//this is a test of game Rock, Paper, Scissors.

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <map>
#include <vector>
#include <functional>

#include "common.h"


std::ostream& operator<<(std::ostream& os, const GameResult& rhs) {
	switch(rhs) {
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


class GameOptionPairResult {
public:

	// GameOptionPairResult() = delete;
	
	static GameOptionPairResult& instance() {
		if(NULL == instance_) {
			instance_ = new GameOptionPairResult();  
		}
		
		return *instance_;
	}

	GameResult game_once_pair(const std::pair<GameOption, GameOption>& rhs) {	
		return game_option_pair2result_map_[rhs];	
	}
	
protected:
	GameOptionPairResult() {
		game_option_pair2result_map_ = {
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
	
private:
	static GameOptionPairResult* instance_;
	std::map<std::pair<GameOption, GameOption>, GameResult> game_option_pair2result_map_;
};


GameOptionPairResult* GameOptionPairResult::instance_ = nullptr;

int main(int argc, char**)  {
	// init_game_option_pair2result_map();
	
	GameOptionPairResult go_2_res = GameOptionPairResult::instance();
	std::cout << go_2_res.game_once_pair(std::pair<GameOption, GameOption>(kPaper, kPaper)) << std::endl;
	
	
	std::cout << game_once_pair(std::pair<GameOption, GameOption>(kPaper, kPaper)) << std::endl;
	std::cout << game_once_pair(std::pair<GameOption, GameOption>(kPaper, kScissors)) << std::endl;
	
	return EXIT_SUCCESS;
}
