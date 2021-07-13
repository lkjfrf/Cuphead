#pragma once

#define XFILE 1296
#define YFILE 780
#define XRES 1280
#define YRES 720
#define HEROXSIZE 100
#define HEROYSIZE 155
#define HEROBULLETNUM 60
#define EXPFRAME 6
#define Enemy1XSIZE 500
#define Enemy1YSIZE 775
#define Enemy2XSIZE 800
#define Enemy2YSIZE 775
#define ENEMYBULLETNUM 7
#define HEROHEALTH 4
#define Enemy1_HEALTH 10000
#define Enemy2_HEALTH 20000



typedef struct FRECT
{
	FLOAT    left;
	FLOAT    top;
	FLOAT    right;
	FLOAT    bottom;
} FRECT;

struct UPDATE
{
	// move 용 tick
	DWORD mStartTick;
	DWORD mEndTick;

	//ani 용 tick
	DWORD aStartTick;
	DWORD aEndTick;

	//Bullet용 tick
	DWORD bStartTick;
	DWORD bEndTick;

	RECT rt;		//피격판정크기

	POINT pt;
	bool bTrigger;		// PressAny키 + Space바 용

	bool m_PauseTrigger;		// true일때 찍고 안찍고를 선택하기위해


	//애니메이션출력 관련
	int MaxFrame;	//0부터 시작
	int frame;		//-1부터 시작
	int size;		//애니 한프레임 가로사이즈

	//점프 관련
	bool bJump;		//점프중인가?
	int originy;	//점프뛰기전 y좌표
	int jumpFrame;	//점프중인 화면이 몇개인지 (1개만 점프해야함)

	int test;
};



struct HANDLES
{
	HBITMAP hbmp, holdbmp;
	HDC dc;
	BITMAP bit;				// HBITMAP이랑 다른거임
	RECT rt;			//피격판정

	BLENDFUNCTION bf;
};

enum m_StageNum
{
	INTRO,
	READY,
	STAGE1,
	STAGE2,
	CLEAR,
	GAME_OVER,
};

enum m_HeroState
{
	IdleRight, IdleLeft, 
	RunRight, RunLeft, 
	JumpRight, JumpLeft, 
	HitRight, HitLeft, 
	ShootRight, ShootLeft
};

enum m_Enemy1State
{
	Enemy1_Intro, Enemy1_Attack, Enemy1_Death,
	Enemy2_Intro, Enemy2_Attack, Enemy2_Death

};

struct DEBUG
{
	DWORD sTick;
	DWORD eTick;
	int StartFrmaeCout;
	int FrameCount;
	int FrameRate;
};

enum m_Scene
{
	Introing,
	Playing

};