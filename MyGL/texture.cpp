#include "texture.h"
//stb库做图像资源的读写
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define __STDC_LIB_EXT1__
#include "stb/stb_image_write.h"

Texture::Texture() {}

Texture::Texture(const int width, const int height, const int channles)
	: width(width), height(height), numChannels(channles)
{
	this->data = (unsigned char*)calloc(width * height * numChannels, sizeof(unsigned char));
}

Texture::Texture(const int width, const int height, const int channles, unsigned char* rawData)
	: width(width),height(height),numChannels(channles),data(rawData)
{
	
}

void Texture::Destroy()
{
	if (this->data != NULL) 
	{
		free(this->data);
	}
}


int Texture::CalcuPixelStartIndex(int x, int y)
{
	int channels = this->numChannels;
	int starIdx = y * this->width * channels + x * channels;
	return starIdx;
}

/// <summary>
/// 
/// </summary>
/// <param name="r">值域0~255</param>
/// <param name="g">值域0~255</param>
/// <param name="b">值域0~255</param>
/// <param name="a">值域0~255</param>
void Texture::Clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	unsigned char color[4]{ r,g,b,a };
	//
	const int texWid = this->width;
	const int channels = this->numChannels;
	//
	for (int h = 0; h < this->height; h++)
	{
		for (int w = 0; w < texWid; w++)
		{
			int starIdx = h * texWid * channels + w * channels;
			for (int colorCom = 0; colorCom < 4; colorCom++)
			{
				if (colorCom < this->numChannels)
				{
					this->data[starIdx + colorCom] = color[colorCom];
				}
			}
		}
	}
}

void Texture::Clear(Color color) 
{
	//值域转到0~255
	this->Clear(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
}

/// <summary>
/// 
/// </summary>
/// <param name="x">值域0~width - 1</param>
/// <param name="y">值域0~height - 1</param>
/// <param name="r">值域0~255</param>
/// <param name="g">值域0~255</param>
/// <param name="b">值域0~255</param>
/// <param name="a">值域0~255</param>
void Texture::SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) 
{
	if (x > this->width || y > this->height || x < 0 || y < 0) { return; }
	//
	if (x == this->width) { x = this->width - 1; }
	if (y == this->height) { y = this->height - 1; }
	//
	int channels = this->numChannels;
	int starIdx = this->CalcuPixelStartIndex(x,y);
	unsigned char color[4]{ r,g,b,a };
	//
	for (int colorCom = 0; colorCom < 4; colorCom++)
	{
		if (colorCom < channels)
		{
			this->data[starIdx + colorCom] = color[colorCom];
		}
	}
}

void Texture::SetPixel(int x, int y, Color color) 
{
	//值域转到0~255
	this->SetPixel(x, y, color.r * 255, color.g * 255, color.b * 255,color.a * 255);
}

Color Texture::GetPixel(int x, int y)
{
	if (x > this->width || y > this->height || x < 0 || y < 0) { return BLACK; }
	//
	if (x == this->width) { x = this->width - 1; }
	if (y == this->height) { y = this->height - 1; }
	//
	int startIndex = this->CalcuPixelStartIndex(x, y);
	//
	Color ret = BLACK;
	//值域转到0~1
	ret.r = this->data[startIndex + 0] / 255;
	ret.g = this->data[startIndex + 1] / 255;
	ret.b = this->data[startIndex + 2] / 255;
	if (this->numChannels > 3) 
	{
		ret.a = this->data[startIndex + 3] / 255;
	}
	return ret;
}

int Texture::SaveToBMPFile(const char* filePath)
{
	return stbi_write_bmp(filePath, this->width, this->height, this->numChannels, this->data);
}

Texture* Texture::LoadTexture(const char* filePath)
{
	int width = 0;
	int height = 0;
	int numChannles = 0;
	unsigned char* data = stbi_load(filePath, &width, &height, &numChannles, 0);
	if (data == NULL) { return NULL; }
	Texture* tex = new Texture(width, height, numChannles, data);
	return tex;
}