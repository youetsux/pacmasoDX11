#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

namespace
{
	const int STAGE_X{ 15 };
	const int STAGE_Y{ 15 };
	const int sArray[STAGE_Y][STAGE_X]{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
}

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")
{


	for (int i = 0; i < STAGE_Y; i++)
	{
		vector<int> sdata(STAGE_X,0);//15å¬ÇÃîzóÒÇ0Ç≈èâä˙âª
		stageData_.push_back(sdata);
	}
	for (int j = 0; j < STAGE_Y; j++)
	{
		for (int i = 0; i < STAGE_X; i++)
		{
			stageData_[j][i] = sArray[j][i];
		}
	}
}

void Stage::Initialize()
{
	hFloor_ = Model::Load("floor.fbx");
	assert(hFloor_ >= 0);
	hBlock_ = Model::Load("wall.fbx");
	assert(hBlock_ >= 0);
	Camera::SetPosition({ 6.5, 15, -3 });
	Camera::SetTarget({ 6.5, 0, 5.5 });

}

void Stage::Update()
{

}

void Stage::Draw()
{
	Transform floorTrans;
	floorTrans.position_ = { 0,0,0 };
	
	for (int z = 0; z < 15; z++) {
		for (int x = 0; x < 15; x++) {
			floorTrans.position_ = { (float)x, 0, (float)z };
			//if (x == 0 || z == 0 || x == 14 || z == 14) {
			//	Model::SetTransform(hBlock_, floorTrans);
			//	Model::Draw(hBlock_);
			//}
			//else {
			//	Model::SetTransform(hFloor_, floorTrans);
			//	Model::Draw(hFloor_);
			//}
			if (stageData_[z][x] == 1) {
				Model::SetTransform(hBlock_, floorTrans);
				Model::Draw(hBlock_);
			}
			else {
				Model::SetTransform(hFloor_, floorTrans);
				Model::Draw(hFloor_);
			}
		}
	}
}

void Stage::Release()
{
}
