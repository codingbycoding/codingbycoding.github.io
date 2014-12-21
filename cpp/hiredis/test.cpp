//g++ -ggdb -std=c++0x test.cpp -I/home/adam/test/strike2014/server/proto/client -I/home/adam/test/strike2014/server/online/src -L/home/adam/test/strike2014/server/proto/client -L/usr/local/lib/ -L/usr/local/lib/ -lssl  -lclientproto -lhiredis  -lprotobuf -o test.linux

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
//#include <random>

#include <hiredis/hiredis.h>

#include "common.pb.h"


int main(int argc, char* argv[]) {

	if(2 != argc) {
		std::cout << "usage: " << argv[0] << " redis_dbno(%d)" << std::endl;
		return -1;
	}

	uint32_t redis_dbno = atoi(argv[1]);
	
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
	// enum {
	// 	REDIS_DBNO_TEST = 1,
	// 	REDIS_DBNO_DEV = 2,
	// };
	
	// uint32_t redis_dbno = REDIS_DBNO_DEV;
	//uint32_t redis_dbno = REDIS_DBNO_TEST;
	
	reply = (redisReply*)redisCommand(g_redis, "SELECT %d", redis_dbno);
	if(reply) {
		freeReplyObject(reply);
	} else {
		std::cout << "SELECT error" << std::endl;
		return -1;
	}

	reply = (redisReply*)redisCommand(g_redis, "flushdb");
	if(reply) {
		freeReplyObject(reply);
	} else {
		std::cout << "flushdb error" << std::endl;
		return -1;
	}
		
	int uid_beg = 80000;
	int uid;
	int robot_sum = 50000;
	std::stringstream ss;
	commonproto::pb_challenge_player_t challenge_player;
	commonproto::pb_hero_t* challenge_hero;
	
	srandom(time(NULL));

	int lv_max = 70;
	int win_count_max = 30;
	const char* chal_key = "ARENA_RANK50K";
	const char* uid2rank_key = "ARENA_UID2RANK";
	const char* rank2uid_key = "ARENA_RANK2UID";
	const char* exped2uid_key = "EXPED_BTL2UID";

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

		challenge_player.set_win_count(random()%win_count_max);
		challenge_player.set_rank(j+1);
		
		commonproto::pb_hero_equip_t* hero_equip;
		uint32_t btl_val = 0;
		
		for(int i=0; i<4; ++i) {
			challenge_hero = challenge_player.add_chal_hero();
			int hero_id = 1000+random()%50+1;
			challenge_hero->set_hero_id(hero_id);

			uint32_t hero_lv = random()%lv+1;
			challenge_hero->set_lv(hero_lv);
			
			challenge_hero->set_exp(random()%lv+1);
			uint32_t hero_rating = random()%3+1;
			challenge_hero->set_rating(hero_rating);
			uint32_t hero_star_rating = random()%3+1;
			challenge_hero->set_star_rating(hero_star_rating);

			uint32_t equip_num = 0;
			for(int j=0; j<6; ++j) {
				hero_equip = challenge_hero->add_hero_equips();
				hero_equip->set_lv(2);
				hero_equip->set_exp(0);
				++equip_num;
			}

			commonproto::pb_skill_t* skill;
			uint32_t sum_hero_skill_lv = 0;
			for(int k=0; k<4; ++k) {
				skill = challenge_hero->add_skills();
				commonproto::pb_skill_type_t skill_index = commonproto::pb_skill_type_t(commonproto::SKILL_ACTIVE+k);
				skill->set_skill_index(skill_index);
				uint32_t hero_skill_lv = 3;
				skill->set_skill_lv(hero_skill_lv);
				uint32_t hero_skill_rating = 1;
				skill->set_skill_rating(hero_skill_rating);

				uint32_t skill_lv_revise = 0;
				switch(skill_index) {
				case commonproto::SKILL_ACTIVE:
					break;
				case commonproto::SKILL_FRIEND:
					skill_lv_revise = (hero_skill_rating-1)*20;
					break;
				case commonproto::SKILL_COMBO:
					skill_lv_revise = hero_skill_rating*30;
					break;
				case commonproto::SKILL_PASSIVE:
					skill_lv_revise = hero_skill_rating*50;
					break;		
				}

				sum_hero_skill_lv = sum_hero_skill_lv + skill_lv_revise + hero_skill_lv;					
			}

			uint32_t equip_btl_val = 0;
			uint32_t x = hero_rating;
			equip_btl_val = hero_rating;
			btl_val = btl_val + (100*(1+hero_lv*0.8) * (1+(hero_star_rating-1)*0.5) + x + equip_num*equip_btl_val) * (0.33+0.66*(1+sum_hero_skill_lv*0.01));
		}

		
		challenge_player.set_btl_val(btl_val);

		seri_str.clear();
		challenge_player.SerializeToString(&seri_str);
		redisAppendCommand(g_redis, "HSET %s %d %b", chal_key, challenge_player.rank(), seri_str.c_str(), seri_str.size());

		redisAppendCommand(g_redis, "HSET %s %d %d", uid2rank_key, challenge_player.uid(), challenge_player.rank());

		redisAppendCommand(g_redis, "ZADD %s %d %d", exped2uid_key, challenge_player.btl_val(), challenge_player.uid());

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
		} else {
			std::cout << "redisGetReply error" << std::endl;
			return -1;
		}

		redisGetReply(g_redis, (void**)&reply);
		if(reply) {
			freeReplyObject(reply);
		} else {
			std::cout << "redisGetReply error" << std::endl;
			return -1;
		}

		redisGetReply(g_redis, (void**)&reply);
		if(reply) {
			freeReplyObject(reply);
		} else {
			std::cout << "redisGetReply error" << std::endl;
			return -1;
		}
	}

	redisFree(g_redis);
	return EXIT_SUCCESS;
}
