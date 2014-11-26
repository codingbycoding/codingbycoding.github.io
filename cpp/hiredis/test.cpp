//g++ -ggdb -std=c++0x test.cpp -I/home/adam/test/strike2014/server/proto/client -I/home/adam/test/strike2014/server/online/src -L/home/adam/test/strike2014/server/proto/client -L/usr/local/lib/ -L/usr/local/lib/ -lssl  -lclientproto -lhiredis  -lprotobuf -o test.linux

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
//#include <random>

#include <hiredis/hiredis.h>

#include "common.pb.h"


int main(int argc, char* argv[]) {

	redisContext  *g_redis = NULL;
	struct timeval timeout = { 2000, 500000 }; // 2.5 seconds
	
	g_redis = redisConnectWithTimeout("127.0.0.1", 6379, timeout);

	if (g_redis == NULL || g_redis->err) {
		if (g_redis) {
			std::cout << "Connection error:" <<  g_redis->errstr << std::endl;
			redisFree(g_redis);
		} else {
			std::cout << "Connection error: can't allocate redis context\n" << std::endl;
		}
		return -1;
	}


	redisReply* reply;
	enum {
		REDIS_DBNO_TEST = 1,
		REDIS_DBNO_DEV = 2,
	};
	
	uint32_t redis_dbno = REDIS_DBNO_DEV;
	
	reply = (redisReply*)redisCommand(g_redis, "SELECT %d", redis_dbno);
	if(reply) {
		freeReplyObject(reply);
	}
		
	

	int uid_beg = 80000;
	int uid;
	int robot_sum = 50000;
	std::stringstream ss;
	commonproto::pb_challenge_player_t challenge_player;
	commonproto::pb_challenge_hero_t* challenge_hero;
	
	srandom(time(NULL));

	int lv_max = 70;
	int win_count_max = 30;
	const char* chal_key = "ARENA_RANK50K";
	const char* uid2rank_key = "ARENA_UID2RANK";
	const char* rank2uid_key = "ARENA_RANK2UID";

	std::string seri_str;
	int reply_count = 0; 
	for(int j=0; j<robot_sum; ++j) {
		challenge_player.Clear();
		
		uid = uid_beg + j;
		challenge_player.set_uid(uid);

		ss.str("");
		ss.clear();
		ss << "Jack" << uid;
		challenge_player.set_nick(ss.str());
		int lv = random()%lv_max+1;
		challenge_player.set_lv(lv);
		challenge_player.set_btl_val(lv*100+random()%100);
		challenge_player.set_win_count(random()%win_count_max);
		challenge_player.set_rank(j+1);
		
		int hero_id = 1000+random()%50;
		for(int i=0; i<4; ++i) {
			challenge_hero = challenge_player.add_chal_hero();
			challenge_hero->set_hero_id(hero_id+i);
			challenge_hero->set_lv(random()%lv+1);
			challenge_hero->set_rating(random()%3+1);
			challenge_hero->set_star_rating(random()%3+1);			
		}

		seri_str.clear();
		challenge_player.SerializeToString(&seri_str);
		redisAppendCommand(g_redis, "HSET %s %d %b", chal_key, challenge_player.rank(), seri_str.c_str(), seri_str.size());

		redisAppendCommand(g_redis, "HSET %s %d %d", uid2rank_key, challenge_player.uid(), challenge_player.rank());

		++reply_count;
	
		// if(0 == reply_count%100) {			
		// 	for(int ii=0; ii<reply_count; ++ii) {
		// 		redisGetReply(g_redis, (void**)&reply);
		// 		freeReplyObject(reply);		
		// 	}
		// 	reply_count = 0; 
		// }

	}

	// for(int ii=0; ii<reply_count; ++ii) {
	// 	redisGetReply(g_redis, (void**)&reply);
	// 	freeReplyObject(reply);		
	// }

	for(int ii=0; ii<robot_sum; ++ii) {
		redisGetReply(g_redis, (void**)&reply);
		if(reply) {
			freeReplyObject(reply);
		}		

		redisGetReply(g_redis, (void**)&reply);
		if(reply) {
			freeReplyObject(reply);
		}
	}

	redisFree(g_redis);
	return EXIT_SUCCESS;
}
