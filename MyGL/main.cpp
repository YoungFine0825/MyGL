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

void TestScene() 
{
	Scene* scene = Scene::LoadSceneFormFile("res/test.blend");
	if (scene != nullptr) 
	{
		printf("Scene Hierarchy: \n");
		PrintSceneNodes(scene->root,1);
		//
		printf("**测试SceneNode的空间变换矩阵 \n");
		SceneNode* cubeNode = scene->root->GetChildWithName("Cube");
		SceneNode* lightNode = scene->root->GetChildWithName("Light");
		if (cubeNode != nullptr && lightNode != nullptr)
		{
			Vector4 cubeWorldPos = cubeNode->GetLocalToWorldMatrix() * VEC4_POINT;
			//取世界坐标到Cube局部空间的矩阵
			Matrix4x4 worldToCubeLocal = cubeNode->GetWorldToLocalMatrix();
			//根据Light节点的世界矩阵算出Light节点的世界坐标
			Vector4 lightWorldPos = lightNode->GetLocalToWorldMatrix() * VEC4_POINT;
			//根据Cube的局部空间矩阵算出Light节点在Cube局部空间下的坐标
			Vector4 localPosInCube = worldToCubeLocal * lightWorldPos;
			//
			printf("  Cube Position In World Space = x=%f y=%f z=%f", cubeWorldPos.x, cubeWorldPos.y, cubeWorldPos.z);
			printf("\n");
			printf("  Light Position In World Space = x=%f y=%f z=%f", lightWorldPos.x, lightWorldPos.y, lightWorldPos.z);
			printf("\n");
			printf("  Light Position In Cube Node Space = x=%f y=%f z=%f", localPosInCube.x, localPosInCube.y, localPosInCube.z);
			printf("\n");
		}
	}
}

int main() 
{
	//TestTexture();
	TestScene();
	return 0;
}