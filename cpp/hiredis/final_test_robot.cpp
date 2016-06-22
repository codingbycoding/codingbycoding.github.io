///usr/bin/g++ -ggdb -std=c++0x final_test_robot.cpp xml_utils.cpp conf.cpp utils.cpp  -I/home/adam/test/strike2014/server/proto/client -I/home/adam/test/strike2014/server/online/src -L/home/adam/test/strike2014/server/proto/client -L/usr/local/lib/ -I/usr/include/libxml2/ -L/usr/local/lib/ -lssl  -lclientproto -lhiredis  -lprotobuf -lxml2 -o final_test_robot.linux

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
#include "utils.h"


#include <hiredis/hiredis.h>

#include "common.pb.h"

uint32_t f_range_random(uint32_t beg, uint32_t end) {
	assert(beg <= end);
	return beg + random()%(end-beg+1);  
}


uint32_t g_sum_total_btl_val = 0;


void f_calc_sum_btl_val(uint32_t val) {
	g_sum_total_btl_val += val;
}

int main(int argc, char* argv[]) {

	if(2 != argc) {
		std::cout << "usage: " << argv[0] << " redis_dbno(%d)" << std::endl;
		return -1;
	}


	if(0 != load_xmlconf("./CfgRobotName.xml", &load_name_conf) 
	   || 0 != load_xmlconf("./CfgRobot.xml", &load_robot_conf)
	   || 0 != load_xmlconf("./CfgBattlePoint.xml", &load_battle_point_conf)
	   || 0 != load_xmlconf("./CfgHeroSkill.xml",  &load_skill_lv_conf)
	   || 0 != load_xmlconf("./CfgHero.xml", &load_hero_conf)) {
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
	int robot_sum = 60000;
	std::stringstream ss;
	commonproto::pb_challenge_player_t challenge_player;
	commonproto::pb_rank_player_t rank_player; 
		
	srandom(time(NULL));

	//int win_count_max = 30;
	const char* chal_key = "ARENA_RANK50K";
	const char* uid2rank_key = "ARENA_UID2RANK";
	const char* exped2uid_key = "EXPED_BTL2UID";

	const char* rk_arena_rank_btl_val = "ARENA_RANK_BTL_VAL";

	const char* rk_rank_total_stars = "RANK_TOTAL_STARS";
	const char* rk_rank_total_btl_val = "RANK_TOTAL_BTL_VAL";
	const char* rk_rank_top4_btl_val = "RANK_TOP4_BTL_VAL";

	const char* rk_rank_player_info = "RANK_PLAYER_INFO";
	
	std::string seri_str;

		
	for(int robot_i=0; robot_i<robot_sum; ++robot_i) {
		uint32_t sum_stars = 0;
		g_sum_total_btl_val = 0;
		uint32_t sum_top4_btl_val = 0;
		std::vector<uint32_t> btl_val_vec;
		rank_player.Clear();
		
		commonproto::pb_challenge_player_t challenge_player_top1;
		uint32_t uid = uid_beg+robot_i;
		challenge_player_top1.set_uid(uid);


		std::cout << "[[[[[[[[[" << std::endl;
		std::cout << "uid:" << uid << std::endl;
		
		
		uint32_t name_index1 = f_range_random(0, g_name_vec.size()-1);
		uint32_t name_index2 = f_range_random(0, g_name_vec.size()-1);

		std::stringstream ss_nick;
		ss_nick << g_name_vec[name_index1].name1 << g_name_vec[name_index2].name2; 
		challenge_player_top1.set_nick(ss_nick.str());
		rank_player.set_nick(ss_nick.str());

		challenge_player_top1.set_win_count(f_range_random(500, 600));
		challenge_player_top1.set_rank(robot_i+1);


		const robot_conf_t* robot_conf = g_robot_conf_mgr.get_robot_conf(challenge_player_top1.rank());

		if(NULL == robot_conf) {
			std::cout << "NULL == robot_conf" << std::endl;
			return -1;
		}
		
		
		// uint32_t lv = 15-(15-8)*challenge_player_top1.rank()/50000;
		uint32_t lv = robot_conf->player_lv;
		challenge_player_top1.set_lv(lv);
		
		commonproto::pb_hero_t* challenge_hero_top1;			
		std::vector<uint32_t> u_array(hero_id_vec.size(), 0);//[30] = {0};

		uint32_t team_star_left = robot_conf->team_star;
		
		for(int j=0; j<4; ++j) {

			uint32_t single_btl_val = 0;
			
			challenge_hero_top1 = challenge_player_top1.add_chal_hero();

			uint32_t index = f_range_random(0, hero_id_vec.size()-j-1);
			uint32_t hero_id;
			if(0 == u_array[index]) {
				hero_id = hero_id_vec[index];
			} else {
				hero_id = hero_id_vec[u_array[index]];
			}
			u_array[index] = hero_id_vec.size()-j-1;

			const hero_conf_t* hero_conf = g_hero_conf_mgr.find_hero_conf(hero_id);
			if(NULL == hero_conf) {
				std::cerr << "hero_id:" << hero_id << " hero_conf not exist." << std::endl;
				return -1;
			}

			challenge_hero_top1->set_hero_id(hero_id);

			// uint32_t hero_lv = challenge_player_top1.lv()-1;
			uint32_t hero_lv = robot_conf->hero_lv;
			challenge_hero_top1->set_lv(hero_lv);			
			challenge_hero_top1->set_exp(random()%lv+1);
			uint32_t hero_rating = robot_conf->hero_rating;
			challenge_hero_top1->set_rating(hero_rating);

			uint32_t hero_star_avg = team_star_left/(4-j);
			uint32_t hero_star_rating = std::min(hero_conf->hero_star, hero_star_avg);
			
			if(4-j-1>0 && (team_star_left-hero_conf->hero_star)/(4-j-1) > 0) {
				hero_star_rating = hero_conf->hero_star;
			} 			
				
			team_star_left -= hero_star_rating;
			
			challenge_hero_top1->set_star_rating(hero_star_rating);
			sum_stars += hero_star_rating;
			commonproto::pb_hero_equip_t* hero_equip;
			for(int k=0; k<6; ++k) {
				hero_equip = challenge_hero_top1->add_hero_equips();
				hero_equip->set_lv(0);
				hero_equip->set_exp(0);
			}

			commonproto::pb_skill_t* skill;
				
			for(int k=0; k<4; ++k) {
				skill = challenge_hero_top1->add_skills();
				commonproto::pb_skill_type_t skill_index = commonproto::pb_skill_type_t(commonproto::SKILL_ACTIVE+k);
				skill->set_skill_index(skill_index);
				uint32_t hero_skill_lv = 0;					
				uint32_t hero_skill_rating = 0;					

				
				switch(skill_index) {
				case commonproto::SKILL_ACTIVE:
					hero_skill_lv = std::max(1, static_cast<int>(hero_lv)+robot_conf->hero_skill_lv_delta);		
					hero_skill_rating = 1;					
					break;
				case commonproto::SKILL_FRIEND:
					hero_skill_lv = std::max(1, static_cast<int>(hero_lv)+robot_conf->hero_skill_lv_delta);		
					hero_skill_rating = 1;					
					if(hero_skill_lv >= 21) {
						hero_skill_rating = 2;
						hero_skill_lv = hero_skill_lv-21+1;
					}
					
					break;
				case commonproto::SKILL_COMBO:
					hero_skill_lv = std::max(0, static_cast<int>(hero_lv)+robot_conf->hero_skill_lv_delta);		
					hero_skill_rating = 1;					
					if(hero_skill_lv >= 21) {
						hero_skill_rating = 2;
						hero_skill_lv = hero_skill_lv-21+1;
					} else {
						hero_skill_rating = 0;
						hero_skill_lv = 0;
					}
					
					break;
				case commonproto::SKILL_PASSIVE:
					break;		
				}

				skill->set_skill_lv(hero_skill_lv);
				skill->set_skill_rating(hero_skill_rating);
			}
			
			single_btl_val = HeroUtils::calc_hero_btl_val(*challenge_hero_top1);

			std::cout << "{{{" << std::endl;
			std::cout << "single_btl_val:" << single_btl_val << std::endl;
			std::string str = challenge_hero_top1->ShortDebugString();
			std::cout << str << std::endl;
			std::cout << "}}}" << std::endl;
	
			btl_val_vec.push_back(single_btl_val);

		}


		std::cout << "]]]]]]]]]" << std::endl;
		std::cout << std::endl << std::endl << std::endl;

		std::sort(btl_val_vec.begin(), btl_val_vec.end());
		std::for_each(btl_val_vec.begin(), btl_val_vec.end(), f_calc_sum_btl_val);

		rank_player.set_total_btl_val(g_sum_total_btl_val);
		rank_player.set_total_stars(sum_stars);
			
		uint32_t hero_i = 0;
		for(std::vector<uint32_t>::reverse_iterator rit=btl_val_vec.rbegin(); rit!=btl_val_vec.rend(); ++rit) {
			if(hero_i++ == 4) {
				break;
			}
			sum_top4_btl_val += *rit;			
		}

		rank_player.set_top4_btl_val(sum_top4_btl_val);
			
		challenge_player_top1.set_btl_val(g_sum_total_btl_val);

		seri_str.clear();
		challenge_player_top1.SerializeToString(&seri_str);
		
		redisAppendCommand(g_redis, "HSET %s %d %b", chal_key, challenge_player_top1.rank(), seri_str.c_str(), seri_str.size());
		redisAppendCommand(g_redis, "HSET %s %d %d", uid2rank_key, challenge_player_top1.uid(), challenge_player_top1.rank());
		redisAppendCommand(g_redis, "ZADD %s %d %d", exped2uid_key, challenge_player_top1.btl_val(), challenge_player_top1.uid());


		redisAppendCommand(g_redis, "ZADD %s %d %d", rk_arena_rank_btl_val, challenge_player_top1.btl_val(), challenge_player_top1.uid());


		redisAppendCommand(g_redis, "ZADD %s %d %d", rk_rank_total_stars, sum_stars, challenge_player_top1.uid());
		redisAppendCommand(g_redis, "ZADD %s %d %d", rk_rank_total_btl_val, g_sum_total_btl_val, challenge_player_top1.uid());
		redisAppendCommand(g_redis, "ZADD %s %d %d", rk_rank_top4_btl_val, sum_top4_btl_val, challenge_player_top1.uid());


		std::string str_rank_player;
		rank_player.SerializeToString(&str_rank_player);
		redisAppendCommand(g_redis, "HSET %s %d %b", rk_rank_player_info, challenge_player_top1.uid(), str_rank_player.c_str(), str_rank_player.size());

			
		//splice redis command.

		for(int i=0; i<8; ++i) {
			redisGetReply(g_redis, (void**)&reply);
			if(reply) {
				freeReplyObject(reply);
			} else {
				std::cout << "redisGetReply error" << std::endl;
				return -1;
			}
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
