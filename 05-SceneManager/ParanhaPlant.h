#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "debug.h"

#define PIRANHAPLANT_BBOX_WIDTH					20
#define PIRANHAPLANT_BBOX_HEIGHT				24

#define PIRANHAPLANT_STATE_IDLE					0

#define PIRANHAPLANT_DARTING_SPEED				0.03f

#define PIRANHAPLANT_ANI_IDLE			0

#define PIRANHAPLANT_ON_BRICK	28

class PiranhaPlant :
	public CGameObject
{
	float limitY = 0;
	ULONGLONG biting_start = 0;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);

	void StartBitting() { biting_start = GetTickCount64(); }

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	PiranhaPlant();
};