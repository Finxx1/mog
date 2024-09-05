#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#include <stdio.h>

#include "font.h"

static uint8_t* ttf_data;
static uint64_t ttf_data_len;
static stbtt_fontinfo ttf_info;

void font_choose(char* font) {
	char* fontdir = "/usr/local/share/fonts/";
	char* chosenfont = malloc(strlen(font) + strlen(fontdir) + 1);
	strcpy(chosenfont, fontdir);
	strcat(chosenfont, font);
	FILE* fp = fopen(chosenfont, "rb");
	fseek(fp, 0, SEEK_END);
	ttf_data_len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fread(ttf_data, 1, ttf_data_len, fp);
	fclose(fp);
	free(chosenfont);
	stbtt_InitFont(&ttf_info, ttf_data, stbtt_GetFontOffsetForIndex(ttf_data, 0));
}

Font_Bitmap font_get_chr(int32_t chr) {
	Font_Bitmap r;
	r.pixels = stbtt_GetCodepointBitmap(&ttf_info, 0, stbtt_ScaleForPixelHeight(&font, 20), chr, &r.width, &r.height, 0 0);
	return r;
}

