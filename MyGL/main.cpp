#include "mygl.h"

using namespace std;

int main() 
{
	const int wid = 600;
	const int height = 600;
	const int channels = 3;
	Texture *myTex = LoadTextureFromFile("res/awesomeface.png");
	//
	if (myTex != NULL) 
	{
		for (int h = 0; h < myTex->height / 2; h++) 
		{
			for (int w = 0; w < myTex->width; w++) 
			{
				myTex->SetPixel(w, h, RED);
			}
		}
		//
		myTex->SaveToBMPFile("framebuffer.bmp");
		//
		myTex->Destroy();
		//
		system("mspaint.exe framebuffer.bmp");
	}

	return 0;
}