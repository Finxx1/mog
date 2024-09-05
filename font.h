#include <stdint.h>

typedef struct {
	uint32_t width;
	uint32_t height;
	uint32_t pixels;
} Font_Bitmap;

void font_choose(char* font);
Font_Bitmap font_get_chr(int32_t chr);

