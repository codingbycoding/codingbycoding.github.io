#ifndef __CONF_H__
#define __CONF_H__

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


extern skill_lv_conf_mgr_t g_skill_lv_conf_mgr;
extern std::vector<name_conf_t> g_name_vec;
extern std::map<uint32_t, skill_lv_conf_t> g_skill_lv_conf_map;
extern std::vector<battle_point_conf_t> g_battle_point_conf_vec;

#endif
