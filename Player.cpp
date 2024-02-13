#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Stage.h"

namespace {
	const float PLAYER_MOVE_SPEED{ 0.1f };
}


Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), 
	hModel_(-1), speed_(PLAYER_MOVE_SPEED), pStage_(nullptr)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);
	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
	pStage_ = (Stage *)FindObject("Stage");
	rec.SetRectCenter(transform_.position_.x, transform_.position_.z, 1.0, 1.0);
	
}

void Player::Update()
{
	enum Dir
	{
		UP, LEFT, DOWN, RIGHT, NONE,
	};
	int moveDir = Dir::NONE;

	XMVECTOR vFront = { 0, 0, 1, 0 };
	XMVECTOR move{ 0, 0, 0, 0 };

	if (Input::IsKey(DIK_UP))
	{
		move = XMVECTOR{ 0, 0, 1, 0 };
		moveDir = Dir::UP;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		move = XMVECTOR{ -1, 0, 0, 0 };
		moveDir = Dir::LEFT;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		move = XMVECTOR{ 0, 0, -1, 0 };
		moveDir = Dir::DOWN;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		move = XMVECTOR{ 1, 0, 0, 0 };
		moveDir = Dir::RIGHT;
	}


	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	XMVECTOR posTmp = XMVectorZero(); //ゼロベクトルで初期化
	posTmp = pos + speed_ * move;

	int tx, ty;
	PacRect trec;
	trec.SetRectCenter(XMVectorGetX(posTmp), XMVectorGetZ(posTmp), 1.0, 1.0);

	switch (moveDir)
	{
	case UP:
		tx = (int)(trec.centerx + 0.5);
		ty = pStage_->GetStageWidth() - (int)(trec.top + 0.5);
		break;
	case DOWN:
		tx = (int)(trec.centerx + 0.5);
		ty = pStage_->GetStageWidth() - (int)(trec.bottom + 0.5);
		break;
	case LEFT:
		tx = (int)(trec.left + 0.5);
		ty = pStage_->GetStageWidth() - (int)(trec.top + 0.5);
		break;
	case RIGHT:
		tx = (int)(trec.right + 0.5);
		ty = pStage_->GetStageWidth() - (int)(trec.top + 0.5);
		break;
	case NONE:
		tx = (int)(trec.centerx + 0.5);
		ty = pStage_->GetStageWidth() - (int)(trec.centery + 0.5); 
		break;
	defaulet:
		break;
	}
	//tx = (int)(XMVectorGetX(posTmp) + 1.0f);
	//ty = pStage_->GetStageWidth() - (int)(XMVectorGetZ(posTmp) + 1.0f);
	
	
	if (!(pStage_->IsWall(tx, ty)))
	{
		pos = posTmp;
	}

	//posTmp.x, posTmp.z => int tx,ty :配列のインデックス
	//仮にmapの配列をmap[][]とする
	//移動先がフロア(STAGE_OBJ::FLOOR => 0)だったら動く
	//if (map[ty][tx] == STAGE_OBJ::FLOOR) {
	//	pos = posTemp;
	//}
	//Debug::Log("(X,Z)=");
	//Debug::Log(XMVectorGetX(pos));
	//Debug::Log(",");
	//Debug::Log(XMVectorGetZ(pos),true);

	Debug::Log("(iX,iZ)=");
	Debug::Log(tx);
	Debug::Log(",");
	Debug::Log(ty);
	Debug::Log(" : ");
	Debug::Log(pStage_->IsWall(tx,ty), true);

	static float angle = 0.0f;
	angle += 0.01f;
	if (!XMVector3Equal(move, XMVectorZero())) {
		XMStoreFloat3(&(transform_.position_), pos);

		//XMMATRIX rot = XMMatrixRotationY(angle);
		//XMVECTOR modVec = XMVector3Transform(vFront, rot);
		////XMVECTOR vdot = XMVector3Dot(vFront, move);
		////assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) >= -1);
		////float angle = acos(XMVectorGetX(vdot));
		//Debug::Log(XMVectorGetX(modVec));
		//Debug::Log(", ");
		//Debug::Log(XMVectorGetZ(modVec),true);
		////XMVECTOR vCross = XMVector3Cross(vFront, move);
		////if (XMVectorGetY(vCross) < 0)
		////{
		////	angle *= -1;
		////}
		//float retAngle = atan2(XMVectorGetZ(modVec), XMVectorGetX(modVec));
		//transform_.rotate_.y = XMConvertToDegrees(angle);
	}
	XMMATRIX rot = XMMatrixRotationY(angle);
	XMVECTOR modVec = XMVector3Transform(vFront, rot);

	//Debug::Log(XMVectorGetX(modVec));
	//Debug::Log(", ");
	//Debug::Log(XMVectorGetZ(modVec), true);

	float retAngle = atan2(XMVectorGetZ(modVec), XMVectorGetX(modVec));
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


PacRect::PacRect()
	: top(-1),
	  bottom(-1),
	  left(-1),
	  right(-1),
	  centerx(-1),
	  centery(-1),
	  width(-1),
	  height(-1)
{
}

void PacRect::SetRectCenter(float _cx, float _cy, float _width, float _height)
{
	centerx = _cx;
	centery = _cy;
	width = _width;
	height = _height;
	top = centery + height / 2.0;
	bottom = centery - height / 2.0;
	left = centerx - width / 2.0;
	right = centerx + width / 2.0;

}

void PacRect::SetRectTopBottom(float _left, float _top, float _width, float _height)
{
	left = _left;
	top = _top;
	width = _width;
	height = _height;
	centery = top - height / 2.0;
	bottom = top - height;
	centerx = left +  width / 2.0;
	right = left + width;
}

float PacRect::GetLeft()
{
	return left;
}

float PacRect::GetRight()
{
	return right;
}

float PacRect::GetTop()
{
	return top;
}

float PacRect::GetBottom()
{
	return bottom;
}

float PacRect::GetCenterX()
{
	return centerx;
}

float PacRect::GetCenterY()
{
	return centery;
}

float PacRect::GetWidth()
{
	return width;
}

float PacRect::GetHeight()
{
	return height;
}
