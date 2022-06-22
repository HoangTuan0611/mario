#pragma once
#include "GameObject.h"

#include "Animations.h"

#include "debug.h"

#include "Tail.h"
#include "Portal.h"

// basic
#define MARIO_SPEED_MAX				0.25f
//#define MARIO_ACCELERATION			0.0007f
#define MARIO_ACCELERATION			0.07f
//#define MARIO_ACCELERATION_JUMP		0.0005f
#define MARIO_ACCELERATION_JUMP		0.005f
#define MARIO_JUMP_SPEED_MAX		0.43f
#define MARIO_JUMP_SPEED_MIN		0.18f
#define MARIO_SLOW_FALLING_SPEED	0.05f
#define MARIO_JUMP_DEFLECT_SPEED	0.3f
#define MARIO_JUMP_DEFLECT_SPEED_GB	0.1f
#define MARIO_UNTOUCHABLE_TIME		1000
#define MARIO_TURNING_TAIL_TIME		350
#define MARIO_TURNING_STATE_TIME	70
#define MARIO_KICKING_TIME			200	
//#define MARIO_FLYING_TIME			1750
#define MARIO_FLYING_TIME			1550
#define MARIO_WALKING_SPEED		0.05f
#define MARIO_RUNNING_SPEED		0.1f
#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f
#define MARIO_JUMP_SPEED_Y		0.35f
#define MARIO_JUMP_RUN_SPEED_Y	0.4f
#define MARIO_GRAVITY_FAST		0.002f
#define MARIO_GRAVITY			0.0005f

//state
#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500
#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define MARIO_STATE_KICK			411

// SMALL
#define MARIO_ANI_SMALL_IDLE_RIGHT			0
#define MARIO_ANI_SMALL_WALKING_RIGHT		1
#define MARIO_ANI_SMALL_RUNNING_RIGHT		3
#define MARIO_ANI_SMALL_JUMPINGUP_RIGHT		4
#define MARIO_ANI_SMALL_BRAKING_RIGHT		6

#define MARIO_ANI_SMALL_IDLE_LEFT			7
#define MARIO_ANI_SMALL_WALKING_LEFT		8
#define MARIO_ANI_SMALL_RUNNING_LEFT		10
#define MARIO_ANI_SMALL_JUMPINGUP_LEFT		11
#define MARIO_ANI_SMALL_BRAKING_LEFT		13

//BIG
#define MARIO_ANI_BIG_IDLE_RIGHT			14
#define MARIO_ANI_BIG_WALKING_RIGHT			15
#define MARIO_ANI_BIG_WALKING_FAST_RIGHT	16
#define MARIO_ANI_BIG_RUNNING_RIGHT			17
#define MARIO_ANI_BIG_JUMPINGUP_RIGHT		18
#define MARIO_ANI_BIG_BRAKING_RIGHT			20
#define MARIO_ANI_BIG_SITTING_RIGHT			21
#define MARIO_ANI_BIG_IDLE_LEFT				22
#define MARIO_ANI_BIG_WALKING_LEFT			23
#define MARIO_ANI_BIG_WALKING_FAST_LEFT		24
#define MARIO_ANI_BIG_RUNNING_LEFT			25
#define MARIO_ANI_BIG_JUMPINGUP_LEFT		26
#define MARIO_ANI_BIG_BRAKING_LEFT			28
#define MARIO_ANI_BIG_SITTING_LEFT			29
#define MARIO_ANI_DIE	62

//SMALL
#define MARIO_ANI_SMALL_HOLD_IDLE_RIGHT			63
#define MARIO_ANI_SMALL_HOLD_WALKING_RIGHT		64
#define MARIO_ANI_SMALL_HOLD_WALKING_FAST_RIGHT	64
#define MARIO_ANI_SMALL_HOLD_RUNNING_RIGHT		64
#define MARIO_ANI_SMALL_HOLD_JUMPINGUP_RIGHT	65
#define MARIO_ANI_SMALL_HOLD_JUMPINGDOWN_RIGHT	65
#define MARIO_ANI_SMALL_HOLD_BRAKING_RIGHT		64
#define MARIO_ANI_SMALL_KICKING_RIGHT			66

#define MARIO_ANI_SMALL_HOLD_IDLE_LEFT			67
#define MARIO_ANI_SMALL_HOLD_WALKING_LEFT		68
#define MARIO_ANI_SMALL_HOLD_WALKING_FAST_LEFT	68
#define MARIO_ANI_SMALL_HOLD_RUNNING_LEFT		68
#define MARIO_ANI_SMALL_HOLD_JUMPINGUP_LEFT		69
#define MARIO_ANI_SMALL_HOLD_JUMPINGDOWN_LEFT	69
#define MARIO_ANI_SMALL_HOLD_BRAKING_LEFT		68
#define MARIO_ANI_SMALL_KICKING_LEFT			70

//BIG
#define MARIO_ANI_BIG_HOLD_IDLE_RIGHT			71
#define MARIO_ANI_BIG_HOLD_WALKING_RIGHT		72
#define MARIO_ANI_BIG_HOLD_WALKING_FAST_RIGHT	72
#define MARIO_ANI_BIG_HOLD_RUNNING_RIGHT		72
#define MARIO_ANI_BIG_HOLD_JUMPINGUP_RIGHT		73
#define MARIO_ANI_BIG_HOLD_JUMPINGDOWN_RIGHT	73
#define MARIO_ANI_BIG_HOLD_BRAKING_RIGHT		72
#define MARIO_ANI_BIG_KICKING_RIGHT				74

#define MARIO_ANI_BIG_HOLD_IDLE_LEFT			75
#define MARIO_ANI_BIG_HOLD_WALKING_LEFT			76
#define MARIO_ANI_BIG_HOLD_WALKING_FAST_LEFT	76
#define MARIO_ANI_BIG_HOLD_RUNNING_LEFT			76
#define MARIO_ANI_BIG_HOLD_JUMPINGUP_LEFT		77
#define MARIO_ANI_BIG_HOLD_JUMPINGDOWN_LEFT		77
#define MARIO_ANI_BIG_HOLD_BRAKING_LEFT			76
#define MARIO_ANI_BIG_KICKING_LEFT				78

//TAIL
#define MARIO_ANI_TAIL_IDLE_RIGHT			30
#define MARIO_ANI_TAIL_WALKING_RIGHT		31
#define MARIO_ANI_TAIL_WALKING_FAST_RIGHT	32
#define MARIO_ANI_TAIL_RUNNING_RIGHT		33
#define MARIO_ANI_TAIL_JUMPINGUP_RIGHT		34
#define MARIO_ANI_TAIL_JUMPINGDOWN_RIGHT	35
#define MARIO_ANI_TAIL_BRAKING_RIGHT		36
#define MARIO_ANI_TAIL_SITTING_RIGHT		37

#define MARIO_ANI_TAIL_IDLE_LEFT			38
#define MARIO_ANI_TAIL_WALKING_LEFT			39
#define MARIO_ANI_TAIL_WALKING_FAST_LEFT	40
#define MARIO_ANI_TAIL_RUNNING_LEFT			41
#define MARIO_ANI_TAIL_JUMPINGUP_LEFT		42
#define MARIO_ANI_TAIL_JUMPINGDOWN_LEFT		43
#define MARIO_ANI_TAIL_BRAKING_LEFT			44
#define MARIO_ANI_TAIL_SITTING_LEFT			45

#define MARIO_ANI_TAIL_HOLD_RUNNING_RIGHT		80
#define MARIO_ANI_TAIL_KICKING_RIGHT			82
#define MARIO_ANI_TAIL_HOLD_RUNNING_LEFT		84
#define MARIO_ANI_TAIL_KICKING_LEFT				86

#define MARIO_STATE_TAIL_ATTACK		14
#define MARIO_DIFF					3

#define MARIO_SPRITE_WHACK_LEFT_1_ID	12813
#define MARIO_SPRITE_WHACK_LEFT_2_ID	12814
#define MARIO_SPRITE_WHACK_LEFT_3_ID	12815
#define MARIO_SPRITE_WHACK_LEFT_4_ID	12816

#define MARIO_SPRITE_WHACK_RIGHT_1_ID	12803
#define MARIO_SPRITE_WHACK_RIGHT_2_ID	12804
#define MARIO_SPRITE_WHACK_RIGHT_3_ID	12805
#define MARIO_SPRITE_WHACK_RIGHT_4_ID	12806

// Fly
//#define MARIO_SPEED_STACK			0.05f // chi can chay rat ngan la fly duoc
#define MARIO_SPEED_STACK			0.1f
#define MARIO_NORMAL_FLY_MAX		0.3f

#define MARIO_ANI_FLAPPING_RIGHT			97
#define MARIO_ANI_FLAPPING_LEFT				98
#define MARIO_ANI_FLY_UP_RIGHT				107
#define MARIO_ANI_FLY_FLAPPING_RIGHT		109
#define MARIO_ANI_FLY_UP_LEFT				110
#define MARIO_ANI_FLY_FLAPPING_LEFT			112

//JUMP
#define MARIO_JUMP_MAX	0.16f
//#define MARIO_JUMP_MAX	0.28f
#define MARIO_SUPER_JUMP_MAX 0.30f

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_TAIL	3

#ifndef MARIO_BBOX

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 21

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 16

#define MARIO_BBOX_SIT_HEIGHT	18
#define MARIO_SIT_HEIGHT_ADJUST	0.4f

#endif // !MARIO_BBOX

#define MARIO	0

class CMario : public CGameObject
{
	
	float maxVx;

	// handle mario fly
	bool isRunning = false;
	bool isReadyToRun = false;
	ULONGLONG fly_start = 0;

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG start_kicking = 0;
	ULONGLONG start_turning_state = 0;
	ULONGLONG start_turning = 0;
	BOOLEAN isJumping = false;

	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant();
	void OnCollisionWithPiranhaPlantFire();
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithPCardItem(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithSwitch(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdTail();

public:

	// for mario hold and kick koopas
	BOOLEAN isReadyToHold = false;
	BOOLEAN isHolding = false;
	BOOLEAN isOnPlatform;
	BOOLEAN isFlapping = false;
	BOOLEAN isKick = false;

	// handle mario fly
	BOOLEAN isFlying = false;
	BOOLEAN isFlappingFlying = false;
	BOOLEAN normalFallDown = false;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y

	// tail attack
	BOOLEAN isTuring = false;
	int turningStack = 0;

	CTail* tail = NULL;
	
	// end game
	bool isFinish = false;

	// switch map
	CPortal* portal = NULL;
	BOOLEAN isPipeUp = false;
	BOOLEAN isPipeDown = false;
	BOOLEAN isSwitchMap = false;
	BOOLEAN isSitting;

	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		tail = new CTail(180, y);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	// get level mario
	int GetLevel() {
		return this->level;
	}

	// get level mario
	int GetY() {
		return this->y;
	}

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	// Start behavior
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartKicking() { start_kicking = GetTickCount64(); isKick = true; }
	void StartTurning() { start_turning_state = GetTickCount64(); isTuring = true; }
	void StartFlying() { fly_start = GetTickCount64(); } // handle fly

	void StartPipeUp() {
		isPipeUp = true;

	}
	void StartPipeDown() {
		isPipeDown = true;
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	//Handle mario behavior
	void HandleMarioJump();
	void HandleMarioDie();
	void HandleMarioKick();
	void HandleTurning();
	void HandleFlying();
	void HandleFlapping();
	void HandleFinishMap();
	void HandleSwitchMap();

	//Stop behavior
	void StopKick() { start_kicking = 0; isKick = false; }

	// Not jumping
	void pullDown() {
		if (!isFlapping) ay = MARIO_GRAVITY; isJumping = false;
	}

	// hack
	//travel to extra map
	void ExtraMap() { x = 2270; y = 0; };
	
	// start map
	void StartMap() { x = 80; y = 0; };

	// end map
	void EndMap() { x = 2688; y = 0; };

};