//g++ -ggdb -std=c++0x testrobot.cpp -I/home/adam/test/strike2014/server/proto/client -I/home/adam/test/strike2014/server/online/src -L/home/adam/test/strike2014/server/proto/client -L/usr/local/lib/ -I/usr/include/libxml2/ -L/usr/local/lib/ -lssl  -lclientproto -lhiredis  -lprotobuf -lxml2 -o testrobot.linux

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
//#include <random>
extern "C" {
#include <libxml/tree.h>
}


#define STRCPY_SAFE(buf, str) \
    do { \
        int buflen = sizeof(buf); \
        buf[buflen - 1] = '\0';\
        strncpy(buf, str, buflen - 1); \
    } while (0);


#define DECODE_XML_PROP(cur, prop, str)								\
	do {															\
		str = xmlGetProp(cur, (xmlChar*)prop);						\
		if (!str) {													\
			std::cerr << "xml parse error: prop=%s" << std::endl;	\
			return -1;												\
		}															\
	} while (0)


#define DECODE_XML_PROP_STR(v, cur, prop)		\
	do {										\
		xmlChar* str;							\
		DECODE_XML_PROP(cur, prop, str);		\
		STRCPY_SAFE(v, (const char *)str);		\
		v[sizeof(v) - 1] = '\0';				\
		xmlFree(str);							\
	} while (0)


int load_xmlconf(const char* file, int (*parser)(xmlNodePtr cur_node)) {
	int err = -1;

	xmlDocPtr doc = xmlParseFile(file);
	if (!doc) {
		std::cerr << "Failed to Load:" << file << std::endl;
	}

	xmlNodePtr cur = xmlDocGetRootElement(doc); 
	if (!cur) {
		std::cerr << "xmlDocGetRootElement error when loading file: " << file << std::endl;
		goto fail;
	}

	err = parser(cur);
fail:
	xmlFreeDoc(doc);
	std::cerr << err << "Load File: " << file  << std::endl;
	return 0;
}

struct name_conf_t {
	std::string name1;
	std::string name2;
};

// class name_manager_t {
// public:
	
// private:
// 	std::
// };

std::vector<name_conf_t> g_name_vec;

int load_name_conf(xmlNodePtr root) {
    xmlNodePtr cur = root->xmlChildrenNode;
	// name_manager_t tmp;

    while (cur) {
        if (xmlStrEqual(cur->name, (const xmlChar *)("CfgRobotName"))) {

			name_conf_t conf;
			char name1[100] = {0};
			char name2[100] = {0};
			DECODE_XML_PROP_STR(name1, cur, "Name01");
			DECODE_XML_PROP_STR(name2, cur, "Name02");

			conf.name1.assign(name1);
			conf.name2.assign(name2);
			// tmp.add_name_conf(conf);
			g_name_vec.push_back(conf);
		}
		
		cur = cur->next;
    }

	// g_name_conf_mgr.copy_from(tmp);	
	// if(g_name_conf_mgr.empty()) {
	// 	ERROR_TLOG("g_name_conf_mgr empty");
	// 	return -1;
	// }

	if(g_name_vec.empty()) {
		std::cerr<< "g_name_vec empty";
		return -1;
	}	

	return 0;
}


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


	// if(0 != load_xmlconf("/home/adam/test/strike2014/server/conf/CfgRobotName.xml", &load_name_conf)) {
	if(0 != load_xmlconf("./CfgRobotName.xml", &load_name_conf)) {		
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

	std::vector<uint32_t> hero_id_vec = {1001, 1002, 1003, 1004, 1005,
										 1006, 1007, 1008, 1009, 1010,
										 1013, 1014, 1016, 1017, 1018,
										 1020, 1021, 1022, 1024, 1026,
										 1030, 1033, 1038, 1043, 1045,
										 1046, 1047, 1048, 1049, 1050};
	
	int uid_beg = 80000;
	int uid;
	int robot_sum = 60000;
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
	//top1-3
	{
		
		for(int i=0; i<3; ++i) {
			uint32_t btl_val = 0;
			commonproto::pb_challenge_player_t challenge_player_top1;
			uint32_t uid = 80000+i;
			challenge_player_top1.set_uid(uid);
			
			uint32_t name_index1 = f_range_random(0, g_name_vec.size()-1);
			uint32_t name_index2 = f_range_random(0, g_name_vec.size()-1);

			std::stringstream ss_nick;
			ss_nick << g_name_vec[name_index1].name1 << g_name_vec[name_index2].name2; 
			challenge_player_top1.set_nick(ss_nick.str());
			uint32_t lv = 49-i;
			challenge_player_top1.set_lv(lv);
		
			challenge_player_top1.set_win_count(f_range_random(500, 600));
			challenge_player_top1.set_rank(i+1);
			commonproto::pb_hero_t* challenge_hero_top1;			

			uint32_t u_array[30] = {0};
			
			for(int j=0; j<4; ++j) {
				challenge_hero_top1 = challenge_player_top1.add_chal_hero();

				uint32_t index = f_range_random(0, 30-j-1);
				uint32_t hero_id;
				if(0 == u_array[index]) {
					hero_id = hero_id_vec[index];
				} else {
					hero_id = hero_id_vec[u_array[index]];
				}
				u_array[index] = 30-j-1;
				
				challenge_hero_top1->set_hero_id(hero_id);

				uint32_t hero_lv = 49-i;
				challenge_hero_top1->set_lv(hero_lv);
			
				challenge_hero_top1->set_exp(random()%lv+1);
				uint32_t hero_rating = 6;
				challenge_hero_top1->set_rating(hero_rating);
				uint32_t hero_star_rating = 3;
				challenge_hero_top1->set_star_rating(hero_star_rating);

				commonproto::pb_hero_equip_t* hero_equip;
				uint32_t equip_num = 0;
				for(int k=0; k<6; ++k) {
					hero_equip = challenge_hero_top1->add_hero_equips();
					hero_equip->set_lv(2);
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
						hero_skill_lv = 48-i;
						hero_skill_rating = 1;					
						break;
					case commonproto::SKILL_COMBO:
						hero_skill_lv = 18-i;
						hero_skill_rating = 1;					
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
		}
	}
	
		
	//top4-50
	{
		
		for(int i=0; i<47; ++i) {
			uint32_t btl_val = 0;
			commonproto::pb_challenge_player_t challenge_player_top4;
			uint32_t uid = 80000+3+i;
			challenge_player_top4.set_uid(uid);

			uint32_t name_index1 = f_range_random(0, g_name_vec.size()-1);
			uint32_t name_index2 = f_range_random(0, g_name_vec.size()-1);

			std::stringstream ss_nick;
			ss_nick << g_name_vec[name_index1].name1 << g_name_vec[name_index2].name2; 
			challenge_player_top4.set_nick(ss_nick.str());
			
			// std::stringstream ss_nick;
			// ss_nick << "Jack_" << uid;
			// challenge_player_top4.set_nick(ss_nick.str());

			uint32_t rank = 4+i;
			challenge_player_top4.set_rank(rank);
			uint32_t lv = uint32_t(46.25-rank/4.0) +1;		
			challenge_player_top4.set_lv(lv);		
			challenge_player_top4.set_win_count(f_range_random(500, 550));

			commonproto::pb_hero_t* challenge_hero_top4;

			uint32_t u_array[30] = {0};
			
			for(int j=0; j<4; ++j) {
				challenge_hero_top4 = challenge_player_top4.add_chal_hero();

				uint32_t index = f_range_random(0, 30-j-1);
				uint32_t hero_id;
				if(0 == u_array[index]) {
					hero_id = hero_id_vec[index];
				} else {
					hero_id = hero_id_vec[u_array[index]];
				}
				u_array[index] = 30-j-1;
				
				challenge_hero_top4->set_hero_id(hero_id);

				uint32_t hero_lv = 49-i;
				challenge_hero_top4->set_lv(uint32_t(46.25-rank/4.0));
			
				challenge_hero_top4->set_exp(random()%lv+1);
				uint32_t hero_rating = uint32_t(hero_lv/5-3.5);
				challenge_hero_top4->set_rating(hero_rating);
				uint32_t hero_star_rating = uint32_t(ceil(hero_lv/15.0-0.5));
				challenge_hero_top4->set_star_rating(hero_star_rating);

				commonproto::pb_hero_equip_t* hero_equip; 
				uint32_t equip_num = 0;
				for(int k=0; k<6; ++k) {
					hero_equip = challenge_hero_top4->add_hero_equips();
					hero_equip->set_lv(2);
					hero_equip->set_exp(0);
					++equip_num;
				}

				commonproto::pb_skill_t* skill;
				uint32_t sum_hero_skill_lv = 0;
				for(int k=0; k<4; ++k) {
					skill = challenge_hero_top4->add_skills();
					commonproto::pb_skill_type_t skill_index = commonproto::pb_skill_type_t(commonproto::SKILL_ACTIVE+k);
					skill->set_skill_index(skill_index);
					uint32_t hero_skill_lv = 0;					
					uint32_t hero_skill_rating = 0;					

					uint32_t skill_lv_revise = 0;
					switch(skill_index) {
					case commonproto::SKILL_ACTIVE:
					case commonproto::SKILL_FRIEND:
						hero_skill_lv = hero_lv;
						hero_skill_rating = 1;					
						break;
					case commonproto::SKILL_COMBO:
						hero_skill_lv = hero_lv-30;
						hero_skill_rating = 1;					
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
		
			challenge_player_top4.set_btl_val(btl_val);

			seri_str.clear();
			challenge_player_top4.SerializeToString(&seri_str);
		
			redisAppendCommand(g_redis, "HSET %s %d %b", chal_key, challenge_player_top4.rank(), seri_str.c_str(), seri_str.size());
			redisAppendCommand(g_redis, "HSET %s %d %d", uid2rank_key, challenge_player_top4.uid(), challenge_player_top4.rank());
			redisAppendCommand(g_redis, "ZADD %s %d %d", exped2uid_key, challenge_player_top4.btl_val(), challenge_player_top4.uid());
		}
	}	

	for(int i=0; i<49950; ++i) {
		uint32_t btl_val = 0;		
		commonproto::pb_challenge_player_t challenge_player_top51;
		uint32_t uid = 80000+51+i;
		challenge_player_top51.set_uid(uid);

		uint32_t name_index1 = f_range_random(0, g_name_vec.size()-1);
		uint32_t name_index2 = f_range_random(0, g_name_vec.size()-1);

		std::stringstream ss_nick;
		ss_nick << g_name_vec[name_index1].name1 << g_name_vec[name_index2].name2; 
		challenge_player_top51.set_nick(ss_nick.str());
			
		// std::stringstream ss_nick;
		// ss_nick << "Jack_" << uid;
		// challenge_player_top51.set_nick(ss_nick.str());

		uint32_t rank = 51+i;
		uint32_t lv = 33 - (33-10)*rank/(50000-50);
		challenge_player_top51.set_lv(lv);
		challenge_player_top51.set_win_count(f_range_random(500, 600));
		challenge_player_top51.set_rank(rank);
		
		commonproto::pb_hero_t* challenge_hero_top51;

		uint32_t u_array[30] = {0};
			
		for(int j=0; j<4; ++j) {
			challenge_hero_top51 = challenge_player_top51.add_chal_hero();

			uint32_t index = f_range_random(0, 30-j-1);
			uint32_t hero_id;
			if(0 == u_array[index]) {
				hero_id = hero_id_vec[index];
			} else {
				hero_id = hero_id_vec[u_array[index]];
			}
			u_array[index] = 30-j-1;
				
			challenge_hero_top51->set_hero_id(hero_id);

			uint32_t hero_lv = uint32_t(33-rank/2500);
			challenge_hero_top51->set_lv(hero_lv);
			
			challenge_hero_top51->set_exp(random()%lv+1);
			uint32_t hero_rating = hero_lv/10;
			challenge_hero_top51->set_rating(hero_rating);
			uint32_t hero_star_rating = uint32_t(ceil(hero_lv/15.0));
			challenge_hero_top51->set_star_rating(hero_star_rating);

			uint32_t equip_num = 0;
			commonproto::pb_hero_equip_t* hero_equip;
			for(int k=0; k<6; ++k) {
				hero_equip = challenge_hero_top51->add_hero_equips();
				hero_equip->set_lv(2);
				hero_equip->set_exp(0);
				++equip_num;
			}

			commonproto::pb_skill_t* skill;
			uint32_t sum_hero_skill_lv = 0;
			for(int k=0; k<4; ++k) {
				skill = challenge_hero_top51->add_skills();
				commonproto::pb_skill_type_t skill_index = commonproto::pb_skill_type_t(commonproto::SKILL_ACTIVE+k);
				skill->set_skill_index(skill_index);
				uint32_t hero_skill_lv = 0;					
				uint32_t hero_skill_rating = 0;					

				uint32_t skill_lv_revise = 0;
				switch(skill_index) {
				case commonproto::SKILL_ACTIVE:
				case commonproto::SKILL_FRIEND:
					hero_skill_lv = hero_lv;
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
		
		challenge_player_top51.set_btl_val(btl_val);

		seri_str.clear();
		challenge_player_top51.SerializeToString(&seri_str);
		
		redisAppendCommand(g_redis, "HSET %s %d %b", chal_key, challenge_player_top51.rank(), seri_str.c_str(), seri_str.size());
		redisAppendCommand(g_redis, "HSET %s %d %d", uid2rank_key, challenge_player_top51.uid(), challenge_player_top51.rank());
		redisAppendCommand(g_redis, "ZADD %s %d %d", exped2uid_key, challenge_player_top51.btl_val(), challenge_player_top51.uid());
	}
		
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
