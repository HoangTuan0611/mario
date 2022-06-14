#include "PiranhaPlantFire.h"
#include "PlayScene.h"

PiranhaPlantFire::PiranhaPlantFire(int tag) {
	this->tag = tag;
	SetState(PIRANHAPLANT_STATE_DARTING);
}

void PiranhaPlantFire::Render()
{
	int ani = PIRANHAPLANT_STATE_DARTING;
	animation_set->at(ani)->Render(x, y);
}

void PiranhaPlantFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt);
	y += vy * dt;
	y = limitY;

	//CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//if (mario != NULL) {
	//	float mLeft, mTop, mRight, mBottom;
	//	float mWidth = mario->GetWidth();
	//	mario->GetBoundingBox(mLeft, mTop, mRight, mBottom);
	//	//DebugOut(L"Mario not null \n");
	//	if (isColliding(floor(mLeft), mTop, ceil(mRight), mBottom)) {
	//		//DebugOut(L"Get collision with piranhaPlant \n");
	//		if (mario->GetLevel() != MARIO_LEVEL_SMALL)
	//		{
	//			mario->SetLevel(mario->GetLevel() - 1);
	//		}
	//		else
	//		{
	//			DebugOut(L">>> Mario die by piranhaPlantFire >>> \n");
	//			//mario->SetState(MARIO_STATE_DIE);
	//		}
	//	}
	//}
	float mLeft, mTop, mRight, mBottom;
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetLevel() == MARIO_LEVEL_TAIL) {
		mario->tail->GetBoundingBox(mLeft, mTop, mRight, mBottom);

		if (isColliding(floor(mLeft), mTop, ceil(mRight), mBottom) && mario->isTuring) {
			DebugOut(L"PiranhaPlantFire die by mario tail \n");
			//SetState();
		}
	}
}


void PiranhaPlantFire::GetBoundingBox(float& left, float& top,
	float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PIRANHAPLANT_BBOX_WIDTH;
	bottom = y + PIRANHAPLANT_BBOX_HEIGHT;
}

void PiranhaPlantFire::SetState(int state) {
	CGameObject::Update(state);
	switch (state)
	{
	case PIRANHAPLANT_STATE_DARTING:
		vy = -PIRANHAPLANT_DARTING_SPEED;
		break;
	}
}