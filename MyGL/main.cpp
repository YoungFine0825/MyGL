#include "mygl.h"

using namespace std;

void TestTexture() 
{
	const int wid = 600;
	const int height = 600;
	const int channels = 3;
	Texture* myTex = Texture::LoadTexture("res/awesomeface.png");
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
}


void PrintSceneNodes(SceneNode *node,int layer)
{
	if (node == nullptr) { return; }
	for (int i = 0; i < layer; i++) 
	{
		printf("  ");
	}
	printf(node->name.c_str());
	Matrix4x4 localToWorld = node->GetWorldToLocalMatrix();
	Vector4 worldPos = localToWorld * VEC4_POINT;
	printf("  worldPos = x=%f y=%f z=%f", worldPos.x, worldPos.y, worldPos.z);
	printf("\n");
	size_t childrenNum = node->children.size();
	if (childrenNum > 0)
	{
		for (size_t i = 0; i < childrenNum; i++)
		{
			PrintSceneNodes(node->children[i],layer + 1);
		}
	}
}

void TestSceneLoading() 
{
	Scene* scene = Scene::LoadSceneFormFile("res/test.blend");
	if (scene != nullptr) 
	{
		PrintSceneNodes(scene->root,0);
	}
}

int main() 
{
	//TestTexture();
	TestSceneLoading();
	return 0;
}