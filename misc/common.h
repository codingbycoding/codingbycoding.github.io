#ifndef R_P_S_COMMON_H_
#define R_P_S_COMMON_H_

enum GameOption {
	kRock = 1,
	kPaper = 2,
	kScissors = 3
};


enum GameResult {
	kWin = 1,
	kLose = 2,
	kTie = 3,
};

struct proto_header_t {
	uint32_t total_len;
};

#endif
