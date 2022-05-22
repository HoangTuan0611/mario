#pragma once
#include "GameObject.h"

#define QUESTION_BRICK_NORMAL	0
#define QUESTION_BRICK_HIT	1

#define QUESTION_BRICK_ANI_NORMAL	0
#define QUESTION_BRICK_ANI_HIT	1

#define QUESTIONBRICK_SPEED		0.05f
#define QUESTIONBRICK_PUSH_MAX_HEIGHT 8

class QuestionBrick :public CGameObject
{
	int tag;

	bool isBeingPushedUp = false;
	bool isFallingDown = false;

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

	// animation push and fall
	void startPushedUp();
	void stopPushedUp();

	~QuestionBrick();

};