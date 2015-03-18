#ifndef __UTILS_H__
#define __UTILS_H__

#include <cstdint>

#include "common.pb.h"

class HeroUtils {
static uint32_t calc_hero_btl_val(const commonproto::pb_hero_t& hero); 	
};

#endif
