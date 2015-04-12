#include "utils.h"
#include "conf.h"


uint32_t HeroUtils::calc_hero_btl_val(const commonproto::pb_hero_t& hero) {	
	// SKILL_ACTIVE = 1;//主动技能	
	// SKILL_FRIEND = 2;//友情技能
	// SKILL_COMBO = 3;//连续技能	
	// SKILL_PASSIVE = 4;//被动技能
	uint32_t skill_lv_sum = 0;
	for(int i=0; i<4; ++i) {		
		uint32_t type_rank = (i+1)*100 + hero.skills(i).skill_rating();
		//const skill_lv_conf_t skill_lv_conf = g_skill_lv_conf_map[type_rank];

		const skill_lv_conf_t* skill_lv_conf = g_skill_lv_conf_mgr.find_skill_lv_conf(type_rank);

		if(NULL == skill_lv_conf) {
			continue;
		}
		
		skill_lv_sum += skill_lv_conf->LVLimit + hero.skills(i).skill_lv() - 1;		
	}

	const battle_point_conf_t* conf;
	if(0 != hero.rating() && hero.rating() <= g_battle_point_conf_vec.size()) {
		conf = &(g_battle_point_conf_vec[hero.rating()-1]);
	} else {
		conf = &(g_battle_point_conf_vec[g_battle_point_conf_vec.size()-1]);
	}

	uint32_t hero_equip_count = hero.hero_equips_size();
	float hero_btl_val = 100.0f * (1 + hero.lv() * 0.08f) * (1 + (hero.star_rating() - 1) * 0.5f) + conf->cont_rating + conf->cont_equip * hero_equip_count;
	hero_btl_val = hero_btl_val *(0.33f + 0.66f * (1 + skill_lv_sum * 0.02f));

	

	
	return (uint32_t)hero_btl_val;
}
