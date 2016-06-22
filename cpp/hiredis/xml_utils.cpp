#include "xml_utils.h"
#include "conf.h"


int load_name_conf(xmlNodePtr root) {
    xmlNodePtr cur = root->xmlChildrenNode;

    while (cur) {
        if (xmlStrEqual(cur->name, (const xmlChar *)("CfgRobotName"))) {

			name_conf_t conf;
			char name1[100] = {0};
			char name2[100] = {0};
			DECODE_XML_PROP_STR(name1, cur, "Name01");
			DECODE_XML_PROP_STR(name2, cur, "Name02");

			conf.name1.assign(name1);
			conf.name2.assign(name2);
			g_name_vec.push_back(conf);
		}
		
		cur = cur->next;
    }

	if(g_name_vec.empty()) {
		std::cerr<< "g_name_vec empty";
		return -1;
	}	

	return 0;
}


int load_battle_point_conf(xmlNodePtr root) {
	xmlNodePtr cur = root->xmlChildrenNode;

    while (cur) {
        if (xmlStrEqual(cur->name, (const xmlChar *)("CfgBattlePoint"))) {

			battle_point_conf_t conf;
			DECODE_XML_PROP_UINT32(conf.cont_rating, cur, "ContRating");
			decode_xml_prop_float_default(&(conf.cont_equip), cur, "ContEquip", 0.0f);
			g_battle_point_conf_vec.push_back(conf);
		}
		
		cur = cur->next;
    }

	if(0 == g_battle_point_conf_vec.size()) {
		std::cerr << "0 == g_battle_point_conf_vec.size()" << std::endl;
		return -1;
	}

    return 0;
}


int load_skill_lv_conf(xmlNodePtr root) {
    xmlNodePtr cur = root->xmlChildrenNode;
    while (cur) {
        if (!xmlStrEqual(cur->name, (const xmlChar *)("CfgHeroSkill"))) {
            cur = cur->next;
            continue;
        }
        skill_lv_conf_t skill_lv_conf;

		uint32_t type;
		uint32_t rank;
		DECODE_XML_PROP_UINT32(type, cur, "Type");
		DECODE_XML_PROP_UINT32(rank, cur, "Rank");
		skill_lv_conf.type_rank = type*100+rank;		
		
        DECODE_XML_PROP_UINT32(skill_lv_conf.LVLimit, cur, "LVLimit");
		DECODE_XML_PROP_UINT32(skill_lv_conf.skill_lv, cur, "LV");
        DECODE_XML_PROP_UINT32(skill_lv_conf.RatingLimit, cur, "RatingLimit");
		DECODE_XML_PROP_UINT32(skill_lv_conf.RankUpCost, cur, "RankUpCost");
		DECODE_XML_PROP_UINT32(skill_lv_conf.LVUpCostBase, cur, "LVUpCostBase");
		DECODE_XML_PROP_UINT32(skill_lv_conf.LVUpCostAdd, cur, "LVUpCostAdd");
        
        if (g_skill_lv_conf_mgr.is_skill_lv_conf_exist(skill_lv_conf.type_rank)) {
			std::cerr << "Duplicate skill_lv_conf type_rank[ ]" << skill_lv_conf.type_rank << "]" << std::endl;
            return -1;
        }

        g_skill_lv_conf_mgr.add_skill_lv_conf(skill_lv_conf);
        cur = cur->next;
    }
    return 0;
}


int load_robot_conf(xmlNodePtr root) {
    xmlNodePtr cur = root->xmlChildrenNode;
    while (cur) {
        if (!xmlStrEqual(cur->name, (const xmlChar *)("CfgRobot"))) {
            cur = cur->next;
            continue;
        }
        robot_conf_t robot_conf;

		DECODE_XML_PROP_UINT32(robot_conf.entry, cur, "entry");
		DECODE_XML_PROP_UINT32(robot_conf.rank_beg, cur, "rank_beg");
		DECODE_XML_PROP_UINT32(robot_conf.rank_end, cur, "rank_end");
        DECODE_XML_PROP_UINT32(robot_conf.player_lv, cur, "player_level");
		DECODE_XML_PROP_UINT32(robot_conf.hero_lv, cur, "hero_level");
        DECODE_XML_PROP_UINT32(robot_conf.hero_rating, cur, "hero_rank");
		DECODE_XML_PROP_UINT32(robot_conf.hero_star, cur, "hero_star");
		DECODE_XML_PROP_INT_DEFAULT(robot_conf.hero_skill_lv_delta, cur, "hero_skill_lv", 0);
		DECODE_XML_PROP_UINT32(robot_conf.team_star , cur, "team_star");
        
        g_robot_conf_mgr.add_robot_conf(robot_conf);
        cur = cur->next;
    }
    return 0;
}


int load_hero_conf(xmlNodePtr root) {
    xmlNodePtr cur = root->xmlChildrenNode;
    while (cur) {
        if (!xmlStrEqual(cur->name, (const xmlChar *)("CfgHero"))) {
            cur = cur->next;
            continue;
        }
        hero_conf_t hero_conf;

		DECODE_XML_PROP_UINT32(hero_conf.id, cur, "id");
        DECODE_XML_PROP_UINT32(hero_conf.hero_rating, cur, "rating");
		DECODE_XML_PROP_UINT32(hero_conf.hero_star, cur, "star");
        
        if (g_hero_conf_mgr.is_hero_conf_exist(hero_conf.id)) {
			std::cerr << "Duplicate hero_conf id[ ]" << hero_conf.id << "]" << std::endl;
            return -1;
        }

        g_hero_conf_mgr.add_hero_conf(hero_conf);
        cur = cur->next;
    }
    return 0;
}


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
