#include "mathlib.h"
#include "stdio.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

using namespace std;



int main() 
{
	const int imgWid = 600;
	const int imgHei = 400;
	const int channels = 3;
	unsigned char imgData[imgWid * imgHei * channels];
	
	int pixelCount = imgWid * imgHei * channels;
	for (int w = 0; w < imgWid; w++)
	{
		imgData[w * channels + 0] = (unsigned char)255;
		imgData[w * channels + 1] = (unsigned char)0;
		imgData[w * channels + 2] = (unsigned char)0;
	}
	int successful = stbi_write_bmp("framebuffer.bmp", imgWid, imgHei, channels, &imgData);
	system("mspaint.exe framebuffer.bmp");
	return 0;
}