#include "Koopas.h"
#include "PlayScene.h"
#include "Block.h"

CKoopas::CKoopas(int tag)
{
	this->start_x = x;
	this->start_y = y;
	this->nx = -1;
	this->SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0.002f;
		ay = vy;
	}
	else
	{ 
		// blocking x
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = -vx;
			nx = -nx;
		}
	}

	if (dynamic_cast<CBlock*>(e->obj))
	{
		//DebugOut(L"koopas on collision with block \n");
		OnCollisionWithBlock(e);
	}
	if (dynamic_cast<CGoomba*>(e->obj))
	{
		DebugOut(L"koopas on collision with goomba \n");
		OnCollisionWithGoomba(e);
	}
	if (dynamic_cast<CKoopas*>(e->obj)) {
		DebugOut(L"koopas on collision with koopas \n");
		OnCollisionWithKoopas(e);
	}
		
}

void CKoopas::OnCollisionWithBlock(LPCOLLISIONEVENT e) {

	vy = 0;
	if (state == KOOPAS_STATE_IN_SHELL)
		vx = 0;
	if (tag == KOOPAS_RED && state == KOOPAS_STATE_WALKING)
	{
		DebugOut(L"koopas on collision with block tag red and walking \n");
		if (this->nx > 0 && x >= e->obj->x + KOOPAS_SPIN_DIFF)
		{
			DebugOut(L"collision right \n");
			if (KoopasCollision(e->obj))
			{
				//DebugOut(L"collision right \n");
				this->nx = -1;
				vx = this->nx * KOOPAS_WALKING_SPEED;
			}
		}
		if (this->nx < 0 && x <= e->obj->x - KOOPAS_SPIN_DIFF)
		{
			DebugOut(L"collision left \n");
			if (KoopasCollision(e->obj))
			{
				//DebugOut(L"collision left \n");
				this->nx = 1;
				vx = this->nx * KOOPAS_WALKING_SPEED;
			}
		}
	}
}

void CKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (this->GetState() == KOOPAS_STATE_TURNING)
	{
		goomba->SetState(GOOMBA_STATE_DIE);
		DebugOut(L"goomba die by koopas \n");
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else {
		goomba->vx = -goomba->vx;
		goomba->nx = -goomba->nx;
		this->vx = -this->vx;
		this->nx = -this->nx;
	}
}

void CKoopas::OnCollisionWithKoopas(LPCOLLISIONEVENT e) {

	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	if (koopas->state == KOOPAS_STATE_WALKING)
	{
		this->vx = -this->vx;
		this->nx = -this->nx;
		koopas->vx = -koopas->vx;
		koopas->nx = -koopas->nx;
	}

	if (koopas->state == KOOPAS_STATE_TURNING)
	{
		DebugOut(L"Koopas die by koopas turning \n");
		//SetState();
	}
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;
	if (state == KOOPAS_STATE_IN_SHELL || state == KOOPAS_STATE_TURNING) {
		bottom = y + KOOPAS_BBOX_SHELL_HEIGHT;
	}
	else {
		bottom = y + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::Render()
{
	int ani = -1;
	if (state == KOOPAS_STATE_SHELL_UP)
		ani = KOOPAS_ANI_SHELL_UP;
	else if (state == KOOPAS_STATE_IN_SHELL)
		ani = KOOPAS_ANI_SHELL;
	else if (state == KOOPAS_STATE_TURNING)
	{
		if (vx < 0)
			ani = KOOPAS_ANI_SPIN_LEFT;
		else
			ani = KOOPAS_ANI_SPIN_RIGHT;
	}
	else {
		if (this->nx < 0)
			ani = KOOPAS_ANI_WALKING_LEFT;
		else
			ani = KOOPAS_ANI_WALKING_RIGHT;
	}

	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		vx = this->nx * KOOPAS_WALKING_SPEED;
		vy = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_TURNING:
		// turn
		vx = KOOPAS_WALKING_SPEED * 4;
		vy = KOOPAS_FALL_SPEED;
		ay = vy;
		break;
	case KOOPAS_STATE_IN_SHELL:
		// idle
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_SHELL_UP:
		// shell up and then walking
		vy = -KOOPAS_SHELL_DEFLECT_SPEED;
		vx = KOOPAS_WALKING_SPEED;
		break;
	}
}

bool CKoopas::KoopasCollision(LPGAMEOBJECT object)
{
	// check block koopas standing == rest
	CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	vector<LPGAMEOBJECT> coObjects = currentScene->GetObjects();
	for (UINT i = 0; i < coObjects.size(); i++)
		if (dynamic_cast<CBlock*>(coObjects[i]))
			if (abs(coObjects[i]->y == object->y))
			{
				if (nx > 0)
					if (coObjects[i]->x > object->x && coObjects[i]->x - 16 < object->x + 16)
					{
						DebugOut(L"next is block, right \n");
						return false;
					}
				if (nx < 0) 
					if (coObjects[i]->x + 16 > object->x - 16 && coObjects[i]->x < object->x)
					{
						DebugOut(L"next is block, left \n");
						return false;
					}	
			}
	return true;
}