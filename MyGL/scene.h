#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include "mathlib.h"
#include<vector>
#include<string>

const std::string DEFAULT_SCENE_NODE_NAME = "Scene Node";

class SceneNode 
{
public:
	Vector3 localPositon = VEC3_ZERO;
	Vector3 localRotation = VEC3_ZERO;
	Vector3 localScale = VEC3_ONE;
	std::string name = DEFAULT_SCENE_NODE_NAME;
	//
	SceneNode* parent;
	//
	std::vector<SceneNode*> children;
	//
	Matrix4x4 metaLocalMat = MAT4_IDENTITY;
	//
	SceneNode();
	SceneNode(std::string name);
	int AddChild(SceneNode* child);
	SceneNode* GetChildWithIndex(int index);
	SceneNode* GetChildWithName(std::string name);
	//
	Matrix4x4 GetLocalMatrix();
	Matrix4x4 GetLocalToWorldMatrix();
	Matrix4x4 GetWorldToLocalMatrix();
private:
	Matrix4x4 GetLocalMatrixFromParent(SceneNode* parent);
};

class Scene 
{
public:
	SceneNode* root;
	static Scene* LoadSceneFormFile(const char* filePath);
};
#endif // !_SCENE_H_
