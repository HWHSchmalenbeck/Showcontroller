#include <avr/pgmspace.h>

const unsigned char logobody []PROGMEM ={
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3c,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x7f,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3,0x80,0xff,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3,0xe1,0xf7,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0xf1,0xf1,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xfb,0xf1,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xe,0x7f,0xf1,0xcf,0xe1,0xf8,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1e,0x1f,0xf1,0xff,0xff,0xf8,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xf,0xfc,0xf,0xf0,0xff,0xff,0xf8,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xf,0xfc,0xf,0xf8,0xff,0x3f,0x1f,0xf8,0x0,0x0,
0x0,0xf,0xe0,0x0,0xf,0xf8,0xf,0xf8,0xff,0x1f,0x1f,0xff,0xc0,0x0,
0x0,0x1f,0xff,0x9f,0xe,0x1c,0x7,0xf8,0xff,0x1f,0x1f,0xff,0xc0,0x0,
0x0,0x1f,0xff,0xff,0xfe,0x1c,0x7,0xf8,0xff,0x9f,0x8e,0xf,0xc0,0x0,
0x0,0x3e,0x3f,0xff,0xfe,0x1c,0x7,0xf8,0x7f,0x9f,0x8f,0x1,0xe0,0x0,
0x0,0x3e,0x0,0x78,0xfe,0x1e,0x7,0xf8,0x7f,0x8f,0x8f,0x0,0xe0,0x0,
0x0,0x3f,0x0,0x78,0xe,0x1e,0x7,0xfc,0x7f,0x8f,0xcf,0x80,0xe0,0x0,
0x1,0xff,0x0,0x78,0xe,0x1f,0x3,0xfc,0x7f,0x8f,0xc7,0x80,0xe0,0x0,
0xf,0xff,0x80,0x7c,0xe,0xf,0x3,0xfc,0x7f,0xcf,0xc7,0xc0,0xe0,0x0,
0xf,0xff,0x80,0x7c,0xf,0xf,0x83,0xfc,0x7f,0xcf,0xe7,0xc0,0xfc,0x0,
0x1f,0x3f,0xc0,0x7e,0xf,0xf,0x83,0xfc,0x3f,0xc7,0xe7,0xe0,0xff,0x0,
0x1c,0x3f,0xe0,0x7e,0xf,0xf,0xc1,0xfc,0x3f,0xc7,0xe7,0xe0,0xff,0xe0,
0x1c,0x3f,0xe0,0x7f,0xf,0x8f,0xc1,0xfc,0x3f,0xc7,0xf7,0xf0,0x77,0xe0,
0x3c,0x3f,0xf0,0x7f,0xf,0x8f,0xe1,0xfe,0x3f,0xe7,0xf3,0xf0,0x70,0xe0,
0x3c,0x1f,0xf0,0x7f,0xf,0x87,0xe1,0xfe,0x3f,0xe7,0xf3,0xf0,0x71,0xe0,
0x3e,0x1f,0xf8,0x7f,0x8f,0xc7,0xf1,0xfe,0x1f,0xe7,0xfb,0xf8,0x71,0xc0,
0x3e,0x1f,0xf8,0x7f,0x8f,0xc7,0xf0,0xfe,0x1f,0xe3,0xfb,0xf8,0x71,0xe0,
0x7f,0x1f,0xfc,0x7f,0xcf,0xc7,0xff,0xff,0xdf,0xf3,0xfb,0xfc,0x71,0xf0,
0x7f,0x1f,0xfe,0x3f,0xcf,0xff,0xff,0xff,0xff,0xf3,0xff,0xfc,0x71,0xf8,
0x7f,0x1f,0xfe,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x79,0xf8,
0x7f,0x9f,0xff,0xff,0xff,0xff,0x8e,0xe,0x3f,0xff,0xff,0xfe,0x39,0xfc,
0xff,0xff,0xff,0xff,0xfe,0x0,0xe,0xe,0x0,0x1f,0xff,0xff,0xfd,0xfc,
0xff,0xff,0xff,0xf8,0x0,0x0,0xe,0xe,0x0,0x0,0xf,0xff,0xff,0xfc,
0x7f,0xff,0xe0,0x0,0x0,0x0,0xe,0xe,0x0,0x0,0x0,0xf,0xff,0xf8,
0x7f,0xff,0xf0,0x0,0x0,0x0,0xe,0xe,0x0,0x0,0x1,0xff,0xff,0xf8,
0x7f,0xff,0xff,0xfe,0x0,0x0,0xe,0xe,0x0,0xf,0xff,0xff,0xff,0xf8,
0x3f,0xff,0xff,0xff,0xff,0x80,0xe,0x8e,0x3f,0xff,0xff,0xff,0xff,0xf0,
0x3f,0xf0,0x1f,0xff,0xff,0xff,0xfe,0x8f,0xff,0xff,0xff,0x0,0x1f,0xf0,
0x1f,0xf8,0x0,0x3,0xff,0xff,0xfc,0x8f,0xff,0xf8,0x0,0x0,0x7f,0xe0,
0x1f,0xfe,0x0,0x0,0x0,0x7f,0xfc,0x8f,0xe0,0x0,0x0,0x0,0xfd,0xe0,
0xf,0xff,0x80,0x0,0x0,0x0,0x1c,0x8e,0x0,0x0,0x0,0x3,0xf1,0xc0,
0xf,0xff,0xc0,0x0,0x0,0x0,0x1c,0x8e,0x0,0x0,0x0,0x7,0xc3,0xc0,
0x7,0xff,0xf0,0x0,0x0,0x0,0x1c,0x8e,0x0,0x0,0x0,0x1f,0x83,0x80,
0x7,0xff,0xfc,0x0,0x0,0x0,0x1c,0x8e,0x0,0x0,0x0,0x7e,0x7,0x80,
0x3,0xff,0xfe,0x0,0x0,0x0,0x1c,0x8e,0x0,0x0,0x0,0xfc,0x7,0x0,
0x3,0xff,0xff,0x80,0x0,0x0,0x1c,0x8e,0x0,0x0,0x3,0xf0,0xf,0x0,
0x1,0xff,0xff,0xe0,0x0,0x0,0x1c,0x8e,0x0,0x0,0x7,0xc0,0xe,0x0,
0x1,0xff,0xff,0xf0,0x0,0x0,0x1c,0x8e,0x0,0x0,0x1f,0x80,0x1e,0x0,
0x0,0xff,0xff,0xfc,0x0,0x0,0x3d,0x8e,0x0,0x0,0x7e,0x0,0x1c,0x0,
0x0,0xff,0xff,0xfe,0x0,0x0,0x39,0x8e,0x0,0x0,0xfc,0x0,0x1c,0x0,
0x0,0xff,0xff,0xff,0x80,0x0,0x39,0x8e,0x0,0x3,0xf0,0x0,0x38,0x0,
0x0,0x7f,0xff,0xff,0xe0,0x0,0x39,0xe,0x0,0x7,0xc0,0x0,0x38,0x0,
0x0,0x7f,0xff,0xff,0xf0,0x0,0x39,0xe,0x0,0x1f,0x80,0x0,0x70,0x0,
0x0,0x3f,0xff,0xff,0xfc,0x0,0x39,0xe,0x0,0x7e,0x0,0x0,0x70,0x0,
0x0,0x3f,0xff,0xff,0xff,0x0,0x39,0xe,0x0,0xfc,0x0,0x0,0xe0,0x0,
0x0,0x1f,0xff,0xff,0xff,0x80,0x39,0xe,0x3,0xf0,0x0,0x0,0xe0,0x0,
0x0,0x1f,0xff,0xff,0xff,0xe0,0x39,0xe,0x7,0xe0,0x0,0x1,0xe0,0x0,
0x0,0xf,0xff,0xff,0xff,0xf8,0x39,0xe,0x1f,0x80,0x0,0x1,0xc0,0x0,
0x0,0xf,0xff,0xff,0xff,0xfc,0x39,0xe,0x7e,0x0,0x0,0x3,0xc0,0x0,
0x0,0x7,0xff,0xff,0xff,0xff,0x39,0xe,0xfc,0x0,0x0,0x3,0x80,0x0,
0x0,0x7,0xff,0xff,0xff,0xff,0xfb,0xf,0xf8,0x0,0x0,0x7,0x80,0x0,
0x0,0x3,0xff,0xff,0xff,0xff,0xf3,0xf,0xf0,0x0,0x0,0x7,0x0,0x0,
0x0,0x3,0xff,0xff,0xff,0xff,0xf3,0xf,0xf0,0x0,0x0,0xf,0x0,0x0,
0x0,0x3,0xff,0xff,0xff,0xfe,0x73,0xf,0xe0,0x0,0x0,0xe,0x0,0x0,
0x0,0x1,0xff,0xff,0xff,0xfe,0x13,0xd,0xe0,0x0,0x0,0x1e,0x0,0x0,
0x0,0x1,0xff,0xff,0xff,0xff,0x3,0x1,0xc0,0x0,0x0,0x1c,0x0,0x0,
0x0,0x0,0xff,0xff,0xff,0xff,0x3,0x3,0xc0,0x0,0x0,0x3c,0x0,0x0,
0x0,0x0,0xff,0xff,0xff,0xff,0x93,0x3,0x80,0x0,0x0,0x38,0x0,0x0,
0x0,0x0,0x7f,0xff,0xff,0xff,0x8b,0x7,0x80,0x0,0x0,0x78,0x0,0x0,
0x0,0x0,0x7f,0xff,0xff,0xff,0xcf,0x7,0x0,0x0,0x0,0x70,0x0,0x0,
0x0,0x0,0x3f,0xff,0xff,0xff,0xc6,0x7,0x0,0x0,0x0,0xf0,0x0,0x0,
0x0,0x0,0x3f,0xff,0xff,0xff,0xe6,0xe,0x0,0x0,0x0,0xe0,0x0,0x0,
0x0,0x0,0x1f,0xff,0xff,0xff,0xe2,0xe,0x0,0x0,0x0,0xe0,0x0,0x0,
0x0,0x0,0x1f,0xff,0xff,0xff,0xf0,0x1e,0x0,0x0,0x1,0xc0,0x0,0x0,
0x0,0x0,0xf,0xff,0xff,0xff,0xf0,0x1c,0x0,0x0,0x1,0xc0,0x0,0x0,
0x0,0x0,0xf,0xff,0xff,0xff,0xf8,0x3c,0x0,0x0,0x3,0xc0,0x0,0x0,
0x0,0x0,0x7,0xff,0xff,0xff,0xf8,0x38,0x0,0x0,0x3,0x80,0x0,0x0,
0x0,0x0,0x7,0xff,0xff,0xff,0xf8,0x78,0x0,0x0,0x7,0x80,0x0,0x0,
0x0,0x0,0x7,0xff,0xff,0xff,0xfc,0x70,0x0,0x0,0x7,0x0,0x0,0x0,
0x0,0x0,0x3,0xff,0xff,0xff,0xfc,0xf0,0x0,0x0,0xf,0x0,0x0,0x0,
0x0,0x0,0x3,0xff,0xff,0xff,0xfe,0xe0,0x0,0x0,0xe,0x0,0x0,0x0,
0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x1e,0x0,0x0,0x0,
0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x1c,0x0,0x0,0x0,
0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0xc0,0x0,0x0,0x3c,0x0,0x0,0x0,
0x0,0x0,0x0,0x1f,0xff,0xff,0xff,0x80,0x0,0x0,0x78,0x0,0x0,0x0,
0x0,0x0,0x0,0xf,0xff,0xff,0xff,0x80,0x0,0x1,0xf8,0x0,0x0,0x0,
0x0,0x0,0x0,0x3,0xff,0xff,0xff,0x80,0x0,0x7,0xe0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xff,0xff,0xff,0x80,0x0,0xf,0xc0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xff,0xff,0xff,0x80,0x0,0x3f,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xff,0xff,0xff,0x80,0x0,0xfc,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0x80,0x1,0xf8,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0x80,0x7,0xf8,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0x0,0x1f,0x90,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0x0,0x3f,0x90,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3c,0x7f,0xff,0x0,0xfc,0xa0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x18,0x3f,0xff,0x3,0xf0,0xe0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x18,0x1f,0xff,0x7,0xe0,0x60,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x10,0xf,0xff,0x1f,0xc0,0x40,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xff,0x7e,0x80,0x40,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0xc,0x0,0xf,0xff,0xfc,0x80,0x0,0x80,0x0,0x0,0x0,
0x0,0x0,0x0,0x6,0x0,0xf,0x7f,0xf6,0x88,0x3,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x7,0x0,0x4e,0x3f,0xc3,0xc,0x7,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x7,0xc0,0xc6,0x1c,0xc3,0xe,0xe,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x3,0xe1,0xc4,0x1c,0x81,0xb,0x3e,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x3,0xfb,0xc4,0xd,0x80,0x1b,0xfc,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xff,0xc0,0xd,0x0,0x11,0xfc,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xff,0xc0,0xd,0x20,0x13,0xf8,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xff,0xc0,0x86,0x30,0x1f,0xf8,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xff,0xe1,0x84,0x38,0x1f,0x70,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xff,0xf3,0x80,0x28,0x7e,0x70,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7f,0xff,0x80,0x2c,0xf8,0xf0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7f,0xff,0x80,0x27,0xf0,0xe0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7f,0xff,0xc0,0x2f,0xc1,0xe0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3f,0xff,0xe0,0x3f,0x81,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3f,0xff,0xf0,0x7e,0x3,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1f,0xff,0xf8,0x7c,0x3,0x80,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xf0,0x7,0x80,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xe0,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xf,0xff,0xff,0x80,0xf,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xf,0xff,0xff,0x0,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0xff,0xfe,0x0,0x1e,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0xff,0xfe,0x0,0x1c,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0xff,0xfe,0x0,0x3c,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3,0xff,0xfe,0x0,0x38,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3,0xff,0xfe,0x0,0x78,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1,0xff,0xfc,0x0,0x70,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1,0xff,0xfc,0x0,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1,0xff,0xfc,0x0,0xe0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xff,0xfc,0x1,0xe0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xff,0xfc,0x1,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7f,0xfc,0x3,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7f,0xfc,0x3,0x80,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7f,0xfc,0x3,0x80,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3f,0xfc,0x7,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3f,0xfc,0x7,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0xe,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0xe,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xf8,0x1c,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x1c,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x38,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0xf8,0x38,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0xf8,0x78,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0xf8,0x70,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3,0xf8,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3,0xf8,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0xf9,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0xf9,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0xfb,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0xfb,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7e,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x3e,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x3c,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1c,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x18,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x18,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

const unsigned char logoeye []PROGMEM ={
0x78,
0xfc,
0xfc,
0xfc,
0xfc,
0x78
};

const unsigned char heart []PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 
0x7f, 0xc0, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x7f, 0xc0, 
0x00, 0x01, 0xff, 0xfe, 0x03, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xfe, 0x03, 0xff, 0xfc, 0x00, 0x01, 
0xff, 0xfe, 0x03, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xfe, 0x03, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 
0x8f, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 0x8f, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 0x8f, 0xff, 
0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 
0xff, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 
0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 
0x01, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x1f, 
0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 
0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfe, 0x00, 
0x00, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 
0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f, 
0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00
};

const unsigned char heartout []PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 
0x7f, 0xc0, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x7f, 0xc0, 
0x00, 0x01, 0xe0, 0x0e, 0x03, 0x80, 0x3c, 0x00, 0x01, 0xe0, 0x0e, 0x03, 0x80, 0x3c, 0x00, 0x01, 
0xe0, 0x0e, 0x03, 0x80, 0x3c, 0x00, 0x01, 0xe0, 0x0e, 0x03, 0x80, 0x3c, 0x00, 0x0f, 0x00, 0x01, 
0x8c, 0x00, 0x03, 0x80, 0x0f, 0x00, 0x01, 0x8c, 0x00, 0x03, 0x80, 0x0f, 0x00, 0x01, 0x8c, 0x00, 
0x03, 0x80, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 
0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x70, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x0e, 0x00, 0x00, 
0x00, 0x00, 0x03, 0x80, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x0e, 0x00, 0x00, 0x00, 0x00, 
0x03, 0x80, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x3c, 0x00, 
0x01, 0xe0, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x1c, 
0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 
0x0e, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x0e, 0x00, 
0x00, 0x00, 0x00, 0x70, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x70, 0x00, 0x00, 0x00, 
0x00, 0x70, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0e, 
0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x03, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00
};

const unsigned char eye_small []PROGMEM = {
	0x00, 0x00
};

const unsigned char otto_small []PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xe0, 0xff, 0xff, 
	0xfc, 0x33, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0xe1, 0x30, 0x43, 0xff, 0xe0, 0xff, 0xf0, 0x05, 0xb3, 
	0x4d, 0xff, 0xe0, 0xff, 0xe7, 0x75, 0xbb, 0x6d, 0xff, 0xe0, 0xff, 0xc7, 0x75, 0xbb, 0x6c, 0xff, 
	0xe0, 0xff, 0xb7, 0x75, 0xbb, 0x6d, 0x7f, 0xe0, 0xff, 0xb7, 0x75, 0xbb, 0x6d, 0xbf, 0xe0, 0xff, 
	0xb7, 0x00, 0x00, 0x0d, 0xbf, 0xe0, 0xff, 0x80, 0xff, 0x6f, 0xe0, 0x3f, 0xe0, 0xff, 0x8f, 0xff, 
	0x6f, 0xfe, 0x3f, 0xe0, 0xff, 0x80, 0x00, 0x60, 0x00, 0x3f, 0xe0, 0xff, 0xc3, 0xff, 0x6f, 0xf8, 
	0x3f, 0xe0, 0xff, 0xc0, 0xff, 0x6f, 0xe6, 0x7f, 0xe0, 0xff, 0xef, 0x3f, 0x6f, 0xde, 0xff, 0xe0, 
	0xff, 0xe7, 0x9f, 0x6f, 0x3c, 0xff, 0xe0, 0xff, 0xf7, 0xe7, 0x6c, 0xfd, 0xff, 0xe0, 0xff, 0xf3, 
	0xf8, 0x61, 0xf9, 0xff, 0xe0, 0xff, 0xfb, 0xfe, 0x67, 0xfb, 0xff, 0xe0, 0xff, 0xf9, 0xfe, 0xf7, 
	0xf3, 0xff, 0xe0, 0xff, 0xfd, 0xfe, 0xf7, 0xf7, 0xff, 0xe0, 0xff, 0xfc, 0xfe, 0xef, 0xe7, 0xff, 
	0xe0, 0xff, 0xfe, 0xff, 0x4f, 0xcf, 0xff, 0xe0, 0xff, 0xfe, 0x7f, 0x5f, 0xcf, 0xff, 0xe0, 0xff, 
	0xff, 0x3f, 0x1f, 0xdf, 0xff, 0xe0, 0xff, 0xff, 0x9f, 0xbf, 0x9f, 0xff, 0xe0, 0xff, 0xff, 0xcf, 
	0xbf, 0x3f, 0xff, 0xe0, 0xff, 0xff, 0xe7, 0xbc, 0x7f, 0xff, 0xe0, 0xff, 0xff, 0xe1, 0xb9, 0xff, 
	0xff, 0xe0, 0xff, 0xff, 0xec, 0xa7, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xbe, 0x0d, 0x7f, 0xff, 0xe0, 
	0xff, 0xff, 0x8a, 0xec, 0x7f, 0xff, 0xe0, 0xff, 0xff, 0xc2, 0xac, 0x7f, 0xff, 0xe0, 0xff, 0xff, 
	0xc1, 0xb8, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xec, 0xa4, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xee, 0x0d, 
	0xff, 0xff, 0xe0, 0xff, 0xff, 0xf7, 0x39, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xf7, 0xfb, 0xff, 0xff, 
	0xe0, 0xff, 0xff, 0xf3, 0xf3, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xfb, 0xf7, 0xff, 0xff, 0xe0, 0xff, 
	0xff, 0xf9, 0xe7, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xfd, 0xef, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xfd, 
	0xcf, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xfc, 0xdf, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xfe, 0x9f, 0xff, 
	0xff, 0xe0, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xe0, 
	0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0
};
