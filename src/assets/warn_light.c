
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#elif defined(LV_BUILD_TEST)
#include "../lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_WARN_LIGHT
#define LV_ATTRIBUTE_WARN_LIGHT
#endif

static const
LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_WARN_LIGHT
uint8_t warn_light_map[] = {

    0x4c,0x70,0x47,0x00,0xc1,0x71,0x4a,0x26,0xc1,0x72,0x4a,0xec,0xc2,0x73,0x4a,0x63,
    0xc1,0x72,0x49,0xae,0xc2,0x71,0x4a,0x75,0xc1,0x72,0x4a,0xa1,0xc1,0x73,0x49,0xa0,
    0xc0,0x72,0x49,0x33,0xc1,0x72,0x4a,0xd6,0xc1,0x72,0x49,0x86,0xc1,0x73,0x4a,0x0f,
    0xc2,0x72,0x4a,0xbc,0xc1,0x72,0x49,0x51,0xbf,0x80,0x40,0x08,0xc1,0x72,0x4a,0xff,

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0xac,0x92,0xff,0x2c,0xa8,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xcf,0xff,0xff,0xff,0xff,0xff,0x9d,0x00,0x00,0x00,0x00,
    0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x71,0xb9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x91,0x00,0x00,0x00,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x30,0x00,0x00,
    0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x41,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfa,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x50,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfd,0x00,
    0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x3b,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf2,0xb0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xa0,
    0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x28,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf3,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf4,
    0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x1e,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf9,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf2,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf2,
    0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x1e,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf9,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf4,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf3,
    0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x28,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xa0,
    0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x3b,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf2,0xb0,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfd,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x50,0x00,
    0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x41,0x5f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfa,0x00,0x00,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x30,0x00,0x00,
    0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x61,0xb9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x91,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xcf,0xff,0xff,0xff,0xff,0xff,0x9d,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0xac,0x92,0xf2,0x2c,0xa8,0x00,0x00,0x00,0x00,0x00,

};

const lv_image_dsc_t warn_light = {
  .header.magic = LV_IMAGE_HEADER_MAGIC,
  .header.cf = LV_COLOR_FORMAT_I4,
  .header.flags = 0,
  .header.w = 40,
  .header.h = 28,
  .header.stride = 20,
  .data_size = sizeof(warn_light_map),
  .data = warn_light_map,
};

