#include "MushRoom.h"
#include "debug.h"
#include "PlayScene.h"
#include "Block.h"

CMushRoom::CMushRoom(int type) {
	SetAppear(false);
	typeMushRoom = type;
}

void CMushRoom::Render() {
	if (isAppear && !isDeleted) {
		if (typeMushRoom == MUSHROOM_GREEN) {
			animation_set->at(1)->Render(x, y);
		}
		else
		animation_set->at(0)->Render(x, y);
	}
	RenderBoundingBox();
}

void CMushRoom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (isDeleted) return;

	if (state == MUSHROOM_STATE_UP)
	{
		//DebugOut(L"state up here \n");
		y += vy * dt;
		if (start_y - y >= MUSHROOM_BBOX_HEIGHT)
		{
			vy = 0;
			y = start_y - MUSHROOM_BBOX_HEIGHT - 0.1f;
			SetState(MUSHROOM_STATE_RIGHT);
		}
	}

	// for handle mushroom with block
	for (int i = 0; i < coObjects->size(); i++) {
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CBlock*>(obj))
		{
			if (obj->getY() > this->y) {
				obj->SetIsBlocking(1);
			}
			else {
				obj->SetIsBlocking(0);
			}
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushRoom::SetState(int state) {
	CGameObject::SetState(state);
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (state)
	{
	case MUSHROOM_STATE_IDLE:
		vy = vx = 0;
		break;
	case MUSHROOM_STATE_UP:
		vy = -0.05f;
		start_y = y;
		//DebugOut(L"set state up here: %d \n", y);
		break;
	case MUSHROOM_STATE_RIGHT:
		vy = MUSHROOM_GRAVITY;
		vx = mario-> nx * MUSHROOM_SPEED;
		break;
	}
}

void CMushRoom::OnNoCollision(DWORD dt) {
	// mushroom fall when over brick, block
	if (state == MUSHROOM_STATE_RIGHT) {
		x += vx * dt;
		y += vy * dt;
		vy = MUSHROOM_GRAVITY;
	}
}

void CMushRoom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == MUSHROOM_STATE_RIGHT) {
		// blocking y
		if (e->ny != 0 && e->obj->IsBlocking())
		{
			vy = 0;
		}
		else
			// blocking x
			if (e->nx != 0 && e->obj->IsBlocking())
			{
				vx = -vx;
			}
	}
}