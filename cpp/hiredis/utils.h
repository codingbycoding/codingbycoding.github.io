#ifndef ADAM_HIREDIS_UTILS_H_
#define ADAM_HIREDIS_UTILS_H_


#include <cstdint>

#include "common.pb.h"

class HeroUtils {
public:	
	static uint32_t calc_hero_btl_val(const commonproto::pb_hero_t& hero); 	
};

#endif
