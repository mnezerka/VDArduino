#define WiFiLogoWidth 60
#define WiFiLogoHeight 36
const char WiFiLogoBits[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00,
0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
0xFF, 0x03, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xC0, 0x83, 0x01, 0x80, 0xFF, 0xFF, 0xFF,
0x01, 0x00, 0x07, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0C, 0x00,
0xC0, 0xFF, 0xFF, 0x7C, 0x00, 0x60, 0x0C, 0x00, 0xC0, 0x31, 0x46, 0x7C,
0xFC, 0x77, 0x08, 0x00, 0xE0, 0x23, 0xC6, 0x3C, 0xFC, 0x67, 0x18, 0x00,
0xE0, 0x23, 0xE4, 0x3F, 0x1C, 0x00, 0x18, 0x00, 0xE0, 0x23, 0x60, 0x3C,
0x1C, 0x70, 0x18, 0x00, 0xE0, 0x03, 0x60, 0x3C, 0x1C, 0x70, 0x18, 0x00,
0xE0, 0x07, 0x60, 0x3C, 0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C,
0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00,
0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00, 0xE0, 0x8F, 0x71, 0x3C,
0x1C, 0x70, 0x18, 0x00, 0xC0, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x08, 0x00,
0xC0, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x0C, 0x00, 0x80, 0xFF, 0xFF, 0x1F,
0x00, 0x00, 0x06, 0x00, 0x80, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x07, 0x00,
0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0xF8, 0xFF, 0xFF,
0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00,
0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00,
0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

#define computerWidth 32
#define computerHeight 32
static char computerBits[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0xff,0xff,0x03,0x40,0x00,0x00,0x04,0x40,0xff,0xff,0x04,0x40,0xad,
0x6a,0x05,0x40,0x07,0xc0,0x05,0x40,0x01,0x00,0x05,0x40,0x03,0x80,0x05,0x40,
0x01,0x00,0x05,0x40,0x03,0x80,0x05,0x40,0x01,0x00,0x05,0x40,0x03,0x80,0x05,
0x40,0x07,0xc0,0x05,0x40,0x7d,0x7c,0x05,0x40,0x7e,0xfe,0x04,0x40,0x40,0x06,
0x04,0xc0,0x7f,0xff,0x07,0x80,0x7f,0xff,0x03,0x00,0x80,0x01,0x00,0xf0,0xff,
0xff,0x1f,0x08,0x00,0x00,0x20,0xa4,0xaa,0xaa,0x4a,0x52,0x55,0x55,0x95,0x02,
0x00,0x00,0x80,0xfe,0xff,0xff,0xff,0xfc,0xff,0xff,0x7f,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

#define bombWidth 64
#define bombHeight 64
static char bombBits[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x04, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x18, 0x85, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x64, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1e, 0x20, 0x00,
0x00, 0x00, 0x00, 0x00, 0x36, 0xf1, 0xf1, 0x00, 0x00, 0x00, 0x00, 0x00,
0x9f, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x60, 0xcd, 0x00,
0x00, 0x00, 0x00, 0x80, 0xff, 0x31, 0x93, 0x01, 0x00, 0x00, 0xc0, 0xff,
0xff, 0x09, 0x22, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0x00, 0x62, 0x00,
0x00, 0x00, 0xae, 0xaa, 0x7f, 0x00, 0x02, 0x00, 0x00, 0x00, 0xff, 0xff,
0xff, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xab, 0xaa, 0xfe, 0x01, 0x00, 0x00,
0x00, 0xe0, 0xfe, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x70, 0xac, 0xaa,
0xfa, 0x07, 0x00, 0x00, 0x00, 0x38, 0xf8, 0xff, 0xff, 0x0f, 0x00, 0x00,
0x00, 0x68, 0xac, 0xaa, 0xfa, 0x0f, 0x00, 0x00, 0x00, 0xfc, 0xfe, 0xff,
0xff, 0x1f, 0x00, 0x00, 0x00, 0xaa, 0xab, 0xaa, 0xea, 0x3f, 0x00, 0x00,
0x00, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0xab, 0xaa, 0xaa,
0xea, 0x7f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00,
0x00, 0xab, 0xaa, 0xaa, 0xea, 0x7f, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff,
0xff, 0xff, 0x00, 0x00, 0x80, 0xaa, 0xaa, 0xaa, 0xea, 0xff, 0x00, 0x00,
0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x80, 0xaa, 0xaa, 0xaa,
0xea, 0xff, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
0x80, 0xaa, 0xaa, 0xaa, 0xfa, 0xff, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff,
0xff, 0xff, 0x00, 0x00, 0x80, 0xaa, 0xaa, 0xaa, 0xfa, 0xff, 0x00, 0x00,
0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x80, 0xaa, 0xaa, 0xaa,
0xfe, 0xff, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
0x00, 0xab, 0xaa, 0xaa, 0xff, 0x7f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
0xff, 0x7f, 0x00, 0x00, 0x00, 0xaf, 0xaa, 0xea, 0xff, 0x7f, 0x00, 0x00,
0x00, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0xfe, 0xaa, 0xfe,
0xff, 0x3f, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00,
0x00, 0xf8, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff,
0xff, 0x0f, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00,
0x00, 0xe0, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff,
0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00,
0x00, 0x00, 0xfe, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff,
0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
