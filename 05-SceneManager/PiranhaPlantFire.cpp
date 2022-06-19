#include "PiranhaPlantFire.h"
#include "PlayScene.h"

PiranhaPlantFire::PiranhaPlantFire(int tag) {
	this->tag = tag;
	SetState(PIRANHAPLANT_STATE_DARTING);
}

void PiranhaPlantFire::Render()
{
	int ani = PIRANHAPLANT_STATE_DARTING;
	// update render for PiraFire
	if (state == PIRANHAPLANT_STATE_DARTING)
	{
		if (Up)
			if (Right)
				ani = PIRANHAPLANT_ANI_RIGHT_UP;
			else
				ani = PIRANHAPLANT_ANI_LEFT_UP;
		else
			if (Right)
				ani = PIRANHAPLANT_ANI_RIGHT_DOWN;
			else
				ani = PIRANHAPLANT_ANI_LEFT_DOWN;
	}
	animation_set->at(ani)->Render(x, y);
}

void PiranhaPlantFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt);

	// limit Y
	if (y <= limitY && vy < 0)
	{
		y = limitY;
		vy = 0;
		DebugOut(L"start delay \n");
		StartDelay();
	}
	if (y >= limitY + BBHeight && vy > 0)
	{
		y = limitY + BBHeight + 12;
		SetState(PIRANHAPLANT_STATE_INACTIVE);
	}
	if (GetTickCount64() - delay_start >= PIRANHAPLANT_DELAY_TIME && delay_start != 0)
	{
		if (y == limitY) {
			DebugOut(L"start turn off \n");
			vy = PIRANHAPLANT_DARTING_SPEED;
		}
		delay_start = 0;
	}
	if (y > limitY && vy == 0)
	{
		// start darting when turn off success
		SetState(PIRANHAPLANT_STATE_DARTING);
	}

	y += vy * dt;

	// die
	if (GetTickCount64() - dying_start >= PIRANHAPLANT_DIYING_TIME && dying_start != 0)
		isDeleted = true;

	if (state == PIRANHAPLANT_STATE_DEATH)
		return;

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
			SetState(PIRANHAPLANT_STATE_DEATH);
		}
	}
}


void PiranhaPlantFire::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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
	case PIRANHAPLANT_STATE_INACTIVE:
		vy = 0;
		StartDelay();
		break;
	case PIRANHAPLANT_STATE_DEATH:
		vy = 0;
		StartDying();
		break;
	}
}