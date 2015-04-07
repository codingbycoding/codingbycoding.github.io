#ifndef ADAM_HIREDIS_CONF_H_
#define ADAM_HIREDIS_CONF_H_

#include <vector>
#include <map>
#include <iostream>
#include <string.h>
#include <cstdint>


struct skill_lv_conf_t {
	/* skill_lv_conf_t() { */
    /*     skill_id = 0;         */
    /*     skill_level = 0; */
    /* } */

	uint32_t type_rank;//[type*100+rank]
	uint32_t LVLimit;//等级限制
	uint32_t RatingLimit;//品级限制	
    
	uint32_t skill_lv; //技能等级
	uint32_t RankUpCost;
	uint32_t LVUpCostBase; 
	uint32_t LVUpCostAdd;
	
};


struct robot_conf_t {
	uint32_t entry;
	uint32_t rank_beg;
	uint32_t rank_end;
	uint32_t player_lv;
	uint32_t hero_lv;
	uint32_t hero_rating;
	int hero_skill_lv_delta;
	uint32_t hero_star;
	uint32_t team_star;
};


struct hero_conf_t {
	uint32_t id;
	uint32_t hero_rating;
	uint32_t hero_star;
};


struct name_conf_t {
	std::string name1;
	std::string name2;
};

struct battle_point_conf_t {
    float cont_rating;
	float cont_equip;
};


class skill_lv_conf_mgr_t {
public:
    skill_lv_conf_mgr_t() {
        clear();
    }
	
    ~skill_lv_conf_mgr_t() {
        clear();
    }
	
    inline void clear() {
        skill_lv_conf_map_.clear();
    }
    
    inline const std::map<uint32_t, skill_lv_conf_t> &const_skill_lv_conf_map() const {
        return skill_lv_conf_map_;
    }
    
    inline void copy_from(const skill_lv_conf_mgr_t &m) {
        skill_lv_conf_map_ = m.const_skill_lv_conf_map();
    }
    
    inline bool is_skill_lv_conf_exist(uint32_t type_rank) {
        return skill_lv_conf_map_.count(type_rank) > 0 ? true : false;
    }
    
    inline bool add_skill_lv_conf(const skill_lv_conf_t &skill_lv_conf) {
        if (is_skill_lv_conf_exist(skill_lv_conf.type_rank)) return false;
        skill_lv_conf_map_[skill_lv_conf.type_rank] = skill_lv_conf; return true;
    }
    
    inline const skill_lv_conf_t *find_skill_lv_conf(uint32_t type_rank) {
        if (!is_skill_lv_conf_exist(type_rank)) return NULL;
        return &((skill_lv_conf_map_.find(type_rank))->second);
    }

private:
    std::map<uint32_t, skill_lv_conf_t> skill_lv_conf_map_;
};


class robot_conf_mgr_t {
public:
    robot_conf_mgr_t() {
        clear();
    }
	
    ~robot_conf_mgr_t() {
        clear();
    }
	
    inline void clear() {
        robot_conf_vec_.clear();
    }
    
    inline void copy_from(const robot_conf_mgr_t &m) {
        robot_conf_vec_ = m.get_const_robot_conf_vec();
    }

	inline const std::vector<robot_conf_t> get_const_robot_conf_vec() const {
        return robot_conf_vec_;
    }

		
    inline bool add_robot_conf(const robot_conf_t &robot_conf) {
        robot_conf_vec_.push_back(robot_conf);
		return true;
    }
    

	inline const robot_conf_t* get_robot_conf(uint32_t robot_rank) {
		int beg_i=0;
		int end_i=robot_conf_vec_.size()-1;
		int find_j=(beg_i + end_i)/2;
		
		for(; beg_i<end_i; find_j=(beg_i + end_i)/2) {
			
			if(robot_rank < robot_conf_vec_[find_j].rank_beg) {
				end_i = find_j-1;
				continue;
			} else if(robot_rank > robot_conf_vec_[find_j].rank_end) {
				beg_i = find_j+1;				
				continue;
			}

			break;
										
		}

		if(robot_rank < robot_conf_vec_[find_j].rank_beg
		   || robot_rank > robot_conf_vec_[find_j].rank_end) {
			return NULL;
		}
		
		return &robot_conf_vec_[find_j];
    }

private:
	std::vector<robot_conf_t> robot_conf_vec_;
};


class hero_conf_mgr_t {
public:
    hero_conf_mgr_t() {
        clear();
    }
	
    ~hero_conf_mgr_t() {
        clear();
    }
	
    inline void clear() {
        hero_conf_map_.clear();
    }
    
    inline const std::map<uint32_t, hero_conf_t> &const_hero_conf_map() const {
        return hero_conf_map_;
    }
    
    inline void copy_from(const hero_conf_mgr_t &m) {
        hero_conf_map_ = m.const_hero_conf_map();
    }
    
    inline bool is_hero_conf_exist(uint32_t id) {
        return hero_conf_map_.count(id) > 0 ? true : false;
    }
    
    inline bool add_hero_conf(const hero_conf_t &hero_conf) {
        if (is_hero_conf_exist(hero_conf.id)) return false;
        hero_conf_map_[hero_conf.id] = hero_conf; return true;
    }
    
    inline const hero_conf_t *find_hero_conf(uint32_t id) {
        if (!is_hero_conf_exist(id)) return NULL;
        return &((hero_conf_map_.find(id))->second);
    }

private:
    std::map<uint32_t, hero_conf_t> hero_conf_map_;
};


extern skill_lv_conf_mgr_t g_skill_lv_conf_mgr;
extern robot_conf_mgr_t g_robot_conf_mgr;
extern hero_conf_mgr_t g_hero_conf_mgr;
extern std::vector<name_conf_t> g_name_vec;
//extern std::map<uint32_t, skill_lv_conf_t> g_skill_lv_conf_map;
extern std::vector<battle_point_conf_t> g_battle_point_conf_vec;

#endif
