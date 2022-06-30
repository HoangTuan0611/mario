#include "WMObject.h"
#include "debug.h"

CWorldMapObject::CWorldMapObject(int sceneId)
{
	vy, vx = 0;
	SetMove(false, false, false, false);
	this->sceneId = sceneId;
}
void CWorldMapObject::Render()
{
	if (tag == OBJECT_TYPE_HAMMER && vx < 0)
		animation_set->at(1)->Render(x, y);
	else
		animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}
void CWorldMapObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	//y += vy * dt;
	if (tag == OBJECT_TYPE_HAMMER && x >= HAMMER_LIMIT_X) {
		StartWalk();
		vx = -vx;
		DebugOut(L"vx:: %f \n", vx);
	}
	if (tag == OBJECT_TYPE_HAMMER && x <= HAMMER_LIMIT_X - OBJECT_BBOX_WIDTH * 4) {
		vx = -vx;
		//start_walk = 0;
		DebugOut(L"vx:: %f \n", vx);
	}

	CGameObject::Update(dt);
}
void CWorldMapObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (tag != OBJECT_TYPE_BUSH)
	{
		left = x + 2;
		top = y + 2;
		right = left + OBJECT_BBOX_WIDTH;
		bottom = top + OBJECT_BBOX_WIDTH;
	}
}

