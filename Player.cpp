#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

namespace {
	const float PLAYER_MOVE_SPEED{ 0.05f };
}


Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hModel_(-1),speed_(PLAYER_MOVE_SPEED)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);
	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
}

void Player::Update()
{
	//enum Dir
	//{
	//	UP, LEFT, DOWN, RIGHT, NONE,
	//};
	//int moveDir = Dir::NONE;

	XMVECTOR vFront = { 0, 0, 1, 0 };
	XMVECTOR move{ 0, 0, 1, 0 };

	if (Input::IsKey(DIK_UP))
	{
		move = XMVECTOR{ 0, 0, 1, 0 };
		//moveDir = Dir::UP;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		move = XMVECTOR{ -1, 0, 0, 0 };
		//moveDir = Dir::LEFT;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		move = XMVECTOR{ 0, 0, -1, 0 };
		//moveDir = Dir::DOWN;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		move = XMVECTOR{1, 0, 0, 0 };
		//moveDir = Dir::RIGHT;
	}
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	pos = pos + speed_ * move;
	XMStoreFloat3(&(transform_.position_), pos);

	XMVECTOR vdot =  XMVector3Dot(vFront, move);
	float angle = acos(XMVectorGetX(vdot));

	XMVECTOR vCross = XMVector3Cross(vFront, move);
	if (XMVectorGetY(vCross) < 0)
	{
		angle *= -1;
	}

	transform_.rotate_.y = XMConvertToDegrees(angle);

	//float rotAngle[5]{ 0, -90, 180, 90, 180 };
	//transform_.rotate_.y = rotAngle[moveDir];

}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
