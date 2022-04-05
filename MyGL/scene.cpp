#include "scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"


SceneNode::SceneNode(){}

SceneNode::SceneNode(std::string name) : name(name) {}

int SceneNode::AddChild(SceneNode* child) 
{
	this->children.push_back(child);
	return 0;
}

SceneNode* SceneNode::GetChildWithIndex(int index) 
{
	return this->children[index];
}

SceneNode* SceneNode::GetChildWithName(std::string name) 
{
	SceneNode* ret = NULL;
	for (size_t i = 0; i < this->children.size(); i++) 
	{
		if (this->children[i]->name == name) 
		{
			ret = this->children[i];
			break;
		}
	}
	return ret;
}

Matrix4x4 SceneNode::GetLocalMatrix()
{
	Matrix4x4 identity = MAT4_IDENTITY;
	Matrix4x4 scaling = glm::scale(identity, this->localScale);
	Matrix4x4 rotateZ = glm::rotate(identity,this->localRotation.z,VEC3_FORWARD);
	Matrix4x4 rotateX = glm::rotate(identity, this->localRotation.x, VEC3_RIGHT);
	Matrix4x4 rotateY = glm::rotate(identity, this->localRotation.y, VEC3_UP);
	Matrix4x4 translate = glm::translate(identity, this->localPositon);
	Matrix4x4 ret = this->metaLocalMat * ( translate * ( rotateY * rotateX * rotateZ ) * scaling);
	return ret;
}

Matrix4x4 SceneNode::GetLocalMatrixFromParent(SceneNode* parent)
{
	if (parent == nullptr) 
	{
		return MAT4_IDENTITY;
	}
	//
	Matrix4x4 localMat = parent->GetLocalMatrix();
	//
	return localMat * GetLocalMatrixFromParent(parent->parent);
}

Matrix4x4 SceneNode::GetLocalToWorldMatrix()
{
	return GetLocalMatrix() * GetLocalMatrixFromParent(this->parent);
}

Matrix4x4 SceneNode::GetWorldToLocalMatrix()
{
	Matrix4x4 localToWorld = GetLocalToWorldMatrix();
	return inverse(localToWorld);
}


/// /////////////
/// /////////////
/// /// /////////////
/// 
/// 


void CopySceneNode(aiNode* aiSceneNode, SceneNode* sceneNode) 
{
	aiMatrix4x4 aiLocalMat = aiSceneNode->mTransformation;
	Matrix4x4 localMat;
	localMat[0] = { aiLocalMat.a1,aiLocalMat.b1,aiLocalMat.c1,aiLocalMat.d1 };
	localMat[1] = { aiLocalMat.a2,aiLocalMat.b2,aiLocalMat.c2,aiLocalMat.d2 };
	localMat[2] = { aiLocalMat.a3,aiLocalMat.b3,aiLocalMat.c3,aiLocalMat.d3 };
	localMat[3] = { aiLocalMat.a4,aiLocalMat.b4,aiLocalMat.c4,aiLocalMat.d4 };
	sceneNode->metaLocalMat = localMat;
}

void CreateSceneHierarchy(aiNode* aiSceneNode, SceneNode* sceneNode)
{
	for (size_t i = 0; i < aiSceneNode->mNumChildren; i++)
	{
		aiNode* aiChild = aiSceneNode->mChildren[i];
		//
		SceneNode* child = new SceneNode(aiChild->mName.C_Str());
		//
		CopySceneNode(aiChild, child);
		//
		sceneNode->children.push_back(child);
		//
		CopySceneNode(aiChild, child);
	}
}

Scene* Scene::LoadSceneFormFile(const char* filePath) 
{
	Assimp::Importer *importer = new Assimp::Importer();
	const aiScene *loadedScene = importer->ReadFile(filePath, aiProcess_ValidateDataStructure);
	if (loadedScene == nullptr) { return nullptr; }
	Scene* newScene = new Scene();
	newScene->root = new SceneNode("SceneRoot");
	CreateSceneHierarchy(loadedScene->mRootNode, newScene->root);
	return newScene;
}