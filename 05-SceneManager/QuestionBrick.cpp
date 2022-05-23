#include "QuestionBrick.h"
#include "Coin.h"
#include "PlayScene.h"
#include "Game.h"
#include "Mario.h"


QuestionBrick::QuestionBrick(int tag) : CGameObject() {
	state = QUESTION_BRICK_NORMAL;
	this->tag = tag;
}

void QuestionBrick::Render() {
	int ani = -1;

	if (state == QUESTION_BRICK_NORMAL) {
		ani = QUESTION_BRICK_ANI_NORMAL;
	}
	if (state == QUESTION_BRICK_HIT) {
		ani = QUESTION_BRICK_ANI_HIT;
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void QuestionBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void QuestionBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void QuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);

	x += vx * dt;
	y += vy * dt;

	if (state == QUESTION_BRICK_HIT) {
		if (isBeingPushedUp && ((start_y - y) >= QUESTIONBRICK_PUSH_MAX_HEIGHT)) {
			DebugOut(L"Start falling\n");
			DebugOut(L"[max height]::%d\n", QUESTIONBRICK_PUSH_MAX_HEIGHT);
			DebugOut(L"[y ]::%d\n", y);
			DebugOut(L"[start_y ]::%d\n", start_y);
			stopPushedUp();
		}
		if (isFallingDown && y >= start_y) {
			DebugOut(L"Start falling end\n");
			y = start_y;
			isFallingDown = false;
			vy = 0;
		}
		//SetState(QUESTION_BRICK_HITTED);
	}
	//if (state == QUESTION_BRICK_HITTED) {
	//	DebugOut(L"hitted");
	//	isFallingDown = false;
	//	start_y = 352;
	//	y = start_y;
	//	DebugOut(L"start y hitted %d \n", start_y);
	//	isBeingPushedUp = false;
	//}
}

void QuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	t = y;
	r = x + 16;
	b = y + 16;
}

void QuestionBrick::startPushedUp() {
	isBeingPushedUp = true;
	vy = -QUESTIONBRICK_SPEED;
	DebugOut(L"Question brick push up \n");
}

void QuestionBrick::stopPushedUp() {
	isBeingPushedUp = false;
	isFallingDown = true;
	vy = QUESTIONBRICK_SPEED;
	DebugOut(L"[QBRICK vy]::%f\n", vy);
}

void QuestionBrick::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTION_BRICK_NORMAL:
		vy = 0;
		break;

	case QUESTION_BRICK_HIT:
		//DebugOut(L"startPushedUp Render \n");
		startPushedUp();
		break;
	}
	//case QUESTION_BRICK_HITTED:
	//	startPushedUp();
	//	break;
	//}
}