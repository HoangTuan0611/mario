#pragma once
#include "GameObject.h"

#define QUESTION_BRICK_NORMAL	0
#define QUESTION_BRICK_HIT	1
#define QUESTION_BRICK_HITTED	2

#define QUESTION_BRICK_ANI_NORMAL	0
#define QUESTION_BRICK_ANI_HIT	1

#define QUESTIONBRICK_SPEED		0.05f
#define QUESTIONBRICK_PUSH_MAX_HEIGHT 8

#define ITEM_COIN_QUESTION_BRICK_COIN	0
#define COIN_ANI_SET_ID 6

#define ITEM_MUSHROOM	1
#define ITEM_MUSHROOM_ANI_SET_ID 37

class QuestionBrick :public CGameObject
{
	int tag;

	bool isBeingPushedUp = false;
	bool isFallingDown = false;

	int totalItems = 1;

public:
	CGameObject* obj = NULL;
	QuestionBrick(int tag);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetState(int state);

	// setup item
	CGameObject* SetUpItem(int itemType);
	void ShowItem(int itemType = ITEM_COIN_QUESTION_BRICK_COIN);

	// animation push and fall
	void startPushedUp();
	void stopPushedUp();


	~QuestionBrick();

};