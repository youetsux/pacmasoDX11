#include "PlayScene.h"
#include "Stage.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	//�����ŃX�e�[�W��Instantiate�����
	Instantiate<Stage>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
