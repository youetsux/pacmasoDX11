#pragma once
#include "Engine/GameObject.h"

class Stage;

class PacRect
{
public:
	PacRect();
	void SetRectCenter(float _cx,float _cy, float _width, float _height);
	void SetRectTopBottom(float _left, float _top, float _width, float _height);
	~PacRect() {};
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();
	float GetCenterX();
	float GetCenterY();
	float GetWidth();
	float GetHeight();
	float top;
	float bottom;
	float left;
	float right;
	float centerx;
	float centery;
	float width;
	float height;
};

class Player :
    public GameObject
{
	int hModel_;
	float speed_;
	Stage* pStage_;
	PacRect rec;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

