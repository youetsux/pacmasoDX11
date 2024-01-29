#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	//�����ŃX�e�[�W��Instantiate�����
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
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
