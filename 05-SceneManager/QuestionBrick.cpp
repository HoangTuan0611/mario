#include "QuestionBrick.h"
#include "Coin.h"
#include "PlayScene.h"
#include "Game.h"
#include "Mario.h"

#include "Utils.h"
#include "MushRoom.h"
#include "Leaf.h"


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

	float mLeft, mTop, mRight, mBottom;
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario != NULL && totalItems > 0 && state != QUESTION_BRICK_HIT && mario->isTuring) {
		mario->tail->GetBoundingBox(mLeft, mTop, mRight, mBottom);
		if (isColliding(mLeft, mTop, mRight, mBottom)) {
			DebugOut(L"Mario tail hit qBrick \n");
			SetState(QUESTION_BRICK_HIT);
		}
	}

	if (state == QUESTION_BRICK_HIT) {
		if (isBeingPushedUp && ((start_y - y) >= QUESTIONBRICK_PUSH_MAX_HEIGHT)) {
			//DebugOut(L"Start falling\n");
			//DebugOut(L"[max height]::%d\n", QUESTIONBRICK_PUSH_MAX_HEIGHT);
			//DebugOut(L"[y ]::%d\n", y);
			//DebugOut(L"[start_y ]::%d\n", start_y);
			stopPushedUp();
		}
		if (isFallingDown && y >= start_y) {
			//DebugOut(L"Start falling end\n");
			y = start_y;
			isFallingDown = false;
			vy = 0;
			if (tag != ITEM_COIN_QUESTION_BRICK_COIN) {
				ShowItem(tag);
				// for mushroom
			}
		}
		if (tag == ITEM_COIN_QUESTION_BRICK_COIN) {
			//DebugOut(L"Start coin \n");
			ShowItem(tag);
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
	//DebugOut(L"Question brick push up \n");
}

void QuestionBrick::stopPushedUp() {
	isBeingPushedUp = false;
	isFallingDown = true;
	vy = QUESTIONBRICK_SPEED;
	//DebugOut(L"[QBRICK vy]::%f\n", vy);
}

void QuestionBrick::ShowItem(int itemType) {
	this->obj = SetUpItem(itemType);
	if (this->obj == NULL) {
		//DebugOut(L"Coin, mushroom null \n");
		return;
	}
	CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	if (dynamic_cast<CCoin*>(this->obj)) {
		CCoin* obj = dynamic_cast<CCoin*>(this->obj);
		obj->SetAppear(true);
		obj->SetPosition(x, y - COIN_BBOX_HEIGHT - 1);
		obj->SetState(COIN_STATE_UP);
		currentScene->AddObject(obj);
		DebugOut(L"Coin create \n");
	}
	if (dynamic_cast<CMushRoom*>(this->obj)) {
		CMushRoom* obj = dynamic_cast<CMushRoom*>(this->obj);
		obj->SetAppear(true);
		obj->SetPosition(x, y);
		obj->SetState(MUSHROOM_STATE_UP);
		//obj->SetZIndex(-1);
		currentScene->AddObject(obj);
		DebugOut(L"Mushroom create \n");
	}
	if (dynamic_cast<CLeaf*>(this->obj)) {
		CLeaf* obj = dynamic_cast<CLeaf*>(this->obj);
		obj->SetPosition(x, y);
		obj->SetZIndex(-1);
		currentScene->AddObject(obj);
		DebugOut(L"Leaf create \n");
	}
}

CGameObject* QuestionBrick::SetUpItem(int itemType) {
	CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = currentScene->GetPlayer();
	int ani_set_id = -1;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	if (totalItems >= 1) {
		totalItems--;
		// limit item = 1 when hit 1 qBrick
	}
	else {
		return NULL;
	}
	if (itemType == ITEM_COIN_QUESTION_BRICK_COIN) {
		obj = new CCoin(COIN_TYPE_INBRICK);
		ani_set_id = COIN_ANI_SET_ID;
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	}
	if (itemType == ITEM_MUSHROOM) {
		obj = new CMushRoom();
		ani_set_id = ITEM_MUSHROOM_ANI_SET_ID;
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	}
	if (itemType == ITEM_LEAF) {
		obj = new CLeaf();
		ani_set_id = LEAF_ANI_SET_ID;
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	}
	return obj;
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