#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>

#include "Animations.h"
#include "Sprites.h"
#include "Collision.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define BBOX_ALPHA 0.25f		// Bounding box transparency

#define STATIC	0
#define MOVING	1

class CGameObject
{
protected:

	int isBlocking = 1;

	
	//float z;

	//float vx;

	float start_x;
	float start_y;

	//int nx;	 
	int ny;

	bool isDeleted; 

	LPANIMATION_SET animation_set;

public: 
	float x;
	float y;

	int nx;
	float vx;
	float vy;

	int state; // for qBrick state

	int tag = 0; // define for goomba tag

	// set up for question brick animation - push and fall
	bool isBeingPushedUp = false;
	bool isFallingDown = false;

	int z = 0; // For render mushroom in brick

	void SetPosition(float x, float y) { this->x = x, this->y = y; this->start_x = x, this->start_y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	void SetTag(int tag) { this->tag = tag; } // set tag for goomba

	int GetState() { return this->state; }
	virtual void Delete() { isDeleted = true;  }
	bool IsDeleted() { return isDeleted; }


	void RenderBoundingBox();

	CGameObject();
	CGameObject(float x, float y) :CGameObject() { this->x = x; this->y = y; }

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	
	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return 1; }
	virtual void SetIsBlocking(int blocking) {
		this->isBlocking = blocking;
	}

	void SetZIndex(int z) {
		this->z = z;
	}

	// oncollision
	bool isColliding(float friend_left, float friend_top, float friend_right, float friend_bottom) {
		float this_left, this_top, this_right, this_bottom;

		GetBoundingBox(
			this_left,
			this_top,
			this_right,
			this_bottom);

		bool on1 = friend_left <= this_right;
		bool on2 = friend_top <= this_bottom;
		bool down1 = friend_right >= this_left;
		bool down2 = friend_bottom >= this_top;

		return on1 && on2 && down1 && down2;
	};

	// Get width
	float GetWidth()
	{
		float left, top, right, bottom;
		GetBoundingBox(left, top, right, bottom);
		return right - left;
	}

	//GET
	float getX() { return x; }
	float getY() { return y; }

	~CGameObject();

	static bool IsDeleted(const LPGAMEOBJECT &o) { return o->isDeleted; }
};
