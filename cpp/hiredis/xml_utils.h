#ifndef ADAM_HIREDIS_XML_UTILS_H_
#define ADAM_HIREDIS_XML_UTILS_H_

extern "C" {
#include <libxml/tree.h>
}

#include <iostream>
#include <string.h>
#include <cstdint>



#define STRCPY_SAFE(buf, str)					\
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


#define DECODE_XML_PROP_UINT32(v, cur, prop)	\
		do { \
			xmlChar *str; \
			DECODE_XML_PROP(cur, prop, str); \
			char* endpt; \
			v = strtoul((const char*)str, &endpt, 10); \
			xmlFree (str); \
		} while (0)


#define DECODE_XML_PROP_INT_DEFAULT(v, cur, prop, def) \
		do { \
			xmlChar *str; \
			if (!cur || !(str = xmlGetProp(cur, (xmlChar*)prop))) { \
				v = def; \
			} else { \
				v = atoi ((const char*)str); \
				xmlFree (str); \
			} \
		} while (0)


static inline void decode_xml_prop_float_default(float* val, xmlNodePtr cur, const void* prop, float def)
{
	xmlChar* str;
	if (!cur || !(str = xmlGetProp(cur, (const xmlChar *)(prop)))) {
		*val = def;
	} else {
		sscanf((char *)(str), "%f", val);
		xmlFree(str);
	}
}


int load_name_conf(xmlNodePtr root);
int load_battle_point_conf(xmlNodePtr root);
int load_robot_conf(xmlNodePtr root);
int load_hero_conf(xmlNodePtr root);
int load_skill_lv_conf(xmlNodePtr root);

int load_xmlconf(const char* file, int (*parser)(xmlNodePtr cur_node));

#endif
