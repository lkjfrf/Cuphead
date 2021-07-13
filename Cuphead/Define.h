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
	// move �� tick
	DWORD mStartTick;
	DWORD mEndTick;

	//ani �� tick
	DWORD aStartTick;
	DWORD aEndTick;

	//Bullet�� tick
	DWORD bStartTick;
	DWORD bEndTick;

	RECT rt;		//�ǰ�����ũ��

	POINT pt;
	bool bTrigger;		// PressAnyŰ + Space�� ��

	bool m_PauseTrigger;		// true�϶� ��� ����� �����ϱ�����


	//�ִϸ��̼���� ����
	int MaxFrame;	//0���� ����
	int frame;		//-1���� ����
	int size;		//�ִ� �������� ���λ�����

	//���� ����
	bool bJump;		//�������ΰ�?
	int originy;	//�����ٱ��� y��ǥ
	int jumpFrame;	//�������� ȭ���� ����� (1���� �����ؾ���)

	int test;
};



struct HANDLES
{
	HBITMAP hbmp, holdbmp;
	HDC dc;
	BITMAP bit;				// HBITMAP�̶� �ٸ�����
	RECT rt;			//�ǰ�����

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