//g++ -ggdb -std=c++0x final_test_robot.cpp xml_utils.cpp conf.cpp  -I/home/adam/test/strike2014/server/proto/client -I/home/adam/test/strike2014/server/online/src -L/home/adam/test/strike2014/server/proto/client -L/usr/local/lib/ -I/usr/include/libxml2/ -L/usr/local/lib/ -lssl  -lclientproto -lhiredis  -lprotobuf -lxml2 -o final_test_robot.linux

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
//#include <random>


#include "conf.h"
#include "xml_utils.h"


#include <hiredis/hiredis.h>

#include "common.pb.h"

uint32_t f_range_random(uint32_t beg, uint32_t end) {
	assert(beg <= end);
	return beg + random()%(end-beg+1);  
}


int main(int argc, char* argv[]) {

	if(2 != argc) {
		std::cout << "usage: " << argv[0] << " redis_dbno(%d)" << std::endl;
		return -1;
	}


	if(0 != load_xmlconf("./CfgRobotName.xml", &load_name_conf)
	   // || 0 != load_xmlconf("Cfg", &load_skill_lv_config)
	   || 0 != load_xmlconf("CfgBattlePoint", &load_battle_point_conf)) {		
		std::cerr << "load_xml_conf faild!!" << std::endl;
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

	// std::vector<uint32_t> hero_id_vec = {1001, 1002, 1003, 1004, 1005,
	// 									 1006, 1007, 1008, 1009, 1010,
	// 									 1013, 1014, 1016, 1017, 1018,
	// 									 1020, 1021, 1022, 1024, 1026,
	// 									 1030, 1033, 1038, 1043, 1045,
	// 									 1046, 1047, 1048, 1049, 1050};

	//remove 1008 1045 1047
	std::vector<uint32_t> hero_id_vec = {1001, 1002, 1003, 1004, 1005,
										 1006, 1007, 1009, 1010,
										 1013, 1014, 1016, 1017, 1018,
										 1020, 1021, 1022, 1024, 1026,
										 1030, 1033, 1038, 1043, 
										 1046, 1048, 1049, 1050};
	
	int uid_beg = 80000;
	int uid;
	int robot_sum = 60000;
	std::stringstream ss;
	commonproto::pb_challenge_player_t challenge_player;
	commonproto::pb_hero_t* challenge_hero;
	
	srandom(time(NULL));

	int lv_max = 70;
	//int win_count_max = 30;
	const char* chal_key = "ARENA_RANK50K";
	const char* uid2rank_key = "ARENA_UID2RANK";
	const char* rank2uid_key = "ARENA_RANK2UID";
	const char* exped2uid_key = "EXPED_BTL2UID";

	std::string seri_str;
		
	for(int i=0; i<robot_sum; ++i) {
		uint32_t btl_val = 0;
		commonproto::pb_challenge_player_t challenge_player_top1;
		uint32_t uid = 80000+i;
		challenge_player_top1.set_uid(uid);
			
		uint32_t name_index1 = f_range_random(0, g_name_vec.size()-1);
		uint32_t name_index2 = f_range_random(0, g_name_vec.size()-1);

		std::stringstream ss_nick;
		ss_nick << g_name_vec[name_index1].name1 << g_name_vec[name_index2].name2; 
		challenge_player_top1.set_nick(ss_nick.str());

		challenge_player_top1.set_win_count(f_range_random(500, 600));
		challenge_player_top1.set_rank(i+1);
		
		uint32_t lv = 15-(15-8)*challenge_player_top1.rank()/50000;
		challenge_player_top1.set_lv(lv);

		
		commonproto::pb_hero_t* challenge_hero_top1;			

		std::vector<uint32_t> u_array(hero_id_vec.size(), 0);//[30] = {0};
			
		for(int j=0; j<4; ++j) {
			challenge_hero_top1 = challenge_player_top1.add_chal_hero();

			uint32_t index = f_range_random(0, hero_id_vec.size()-j-1);
			uint32_t hero_id;
			if(0 == u_array[index]) {
				hero_id = hero_id_vec[index];
			} else {
				hero_id = hero_id_vec[u_array[index]];
			}
			u_array[index] = hero_id_vec.size()-j-1;
				
			challenge_hero_top1->set_hero_id(hero_id);

			uint32_t hero_lv = challenge_player_top1.lv()-1;
			challenge_hero_top1->set_lv(hero_lv);
			
			challenge_hero_top1->set_exp(random()%lv+1);
			uint32_t hero_rating = 1;
			challenge_hero_top1->set_rating(hero_rating);
			uint32_t hero_star_rating = 1;
			challenge_hero_top1->set_star_rating(hero_star_rating);

			commonproto::pb_hero_equip_t* hero_equip;
			uint32_t equip_num = 0;
			for(int k=0; k<6; ++k) {
				hero_equip = challenge_hero_top1->add_hero_equips();
				hero_equip->set_lv(0);
				hero_equip->set_exp(0);
				++equip_num;
			}

			commonproto::pb_skill_t* skill;
			uint32_t sum_hero_skill_lv = 0;
				
			for(int k=0; k<4; ++k) {
				skill = challenge_hero_top1->add_skills();
				commonproto::pb_skill_type_t skill_index = commonproto::pb_skill_type_t(commonproto::SKILL_ACTIVE+k);
				skill->set_skill_index(skill_index);
				uint32_t hero_skill_lv = 0;					
				uint32_t hero_skill_rating = 0;					

				switch(skill_index) {
				case commonproto::SKILL_ACTIVE:
				case commonproto::SKILL_FRIEND:
					hero_skill_lv = 1;
					hero_skill_rating = 1;					
					break;
				case commonproto::SKILL_COMBO:
					break;
				case commonproto::SKILL_PASSIVE:
					break;		
				}

				sum_hero_skill_lv = sum_hero_skill_lv + hero_skill_lv;
				skill->set_skill_lv(hero_skill_lv);
				skill->set_skill_rating(hero_skill_rating);
			}

			uint32_t equip_btl_val = 0;
			uint32_t x = hero_rating;
			equip_btl_val = hero_rating;
			btl_val = btl_val + (100*(1+hero_lv*0.8) * (1+(hero_star_rating-1)*0.5) + x + equip_num*equip_btl_val) * (0.33+0.66*(1+sum_hero_skill_lv*0.01));
		}
		
		challenge_player_top1.set_btl_val(btl_val);

		seri_str.clear();
		challenge_player_top1.SerializeToString(&seri_str);
		
		redisAppendCommand(g_redis, "HSET %s %d %b", chal_key, challenge_player_top1.rank(), seri_str.c_str(), seri_str.size());
		redisAppendCommand(g_redis, "HSET %s %d %d", uid2rank_key, challenge_player_top1.uid(), challenge_player_top1.rank());
		redisAppendCommand(g_redis, "ZADD %s %d %d", exped2uid_key, challenge_player_top1.btl_val(), challenge_player_top1.uid());



		//splice redis command.

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


		
	// for(int ii=0; ii<robot_sum; ++ii) {
	// 	redisGetReply(g_redis, (void**)&reply);
	// 	if(reply) {
	// 		freeReplyObject(reply);
	// 	} else {
	// 		std::cout << "redisGetReply error" << std::endl;
	// 		return -1;
	// 	}

	// 	redisGetReply(g_redis, (void**)&reply);
	// 	if(reply) {
	// 		freeReplyObject(reply);
	// 	} else {
	// 		std::cout << "redisGetReply error" << std::endl;
	// 		return -1;
	// 	}

	// 	redisGetReply(g_redis, (void**)&reply);
	// 	if(reply) {
	// 		freeReplyObject(reply);
	// 	} else {
	// 		std::cout << "redisGetReply error" << std::endl;
	// 		return -1;
	// 	}
	// }

	redisFree(g_redis);
	return EXIT_SUCCESS;
}
