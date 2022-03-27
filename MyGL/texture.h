#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "color.h"

class Texture 
{
public:
	int width = 0;
	int height = 0;
	int numChannels = 0;
	unsigned char* data;
	//
	Texture();
	Texture(const int width, const int height, const int channles);
	Texture(const int width, const int height, const int channles, unsigned char* data);
	//
	void Destroy();
	void Clear(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255);
	void Clear(Color color);
	void SetPixel(int x, int y, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255);
	void SetPixel(int x, int y, Color color);
	Color GetPixel(int x, int y);
	int SaveToBMPFile(const char* filePath);
private:
	int CalcuPixelStartIndex(int x, int y);
};


extern Texture* LoadTextureFromFile(const char* filePath);

#endif // !_TEXTURE_H_

