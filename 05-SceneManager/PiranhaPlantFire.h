#pragma once
#include "ParanhaPlant.h"

#define PIRANHAPLANT_BBOX_WIDTH					20
#define PIRANHAPLANT_BOX_HEIGHT					24

#define PIRANHAPLANT_DARTING_SPEED				0.03f
#define PIRANHAPLANT_STATE_DARTING				0

#define BB_Height	0


class PiranhaPlantFire :
	public PiranhaPlant
{
	float limitY = 0;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
public:

	PiranhaPlantFire(int tag);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	void SetLimitY(float ly)
	{
		limitY = ly - BB_Height;
	}

};