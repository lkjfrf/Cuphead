#pragma once
#include "framework.h"128
#include "Game.h"			// include 순서 잘해야됨
#include <cstdlib>			//랜덤함수
#include <ctime>			//시간으로랜덤함수 seed역할

Game::Game()
{
}

Game::~Game()
{
}

void Game::InitAll()
{
	m_Scene = Introing;
	m_StageNum = INTRO;
	m_uIntro.bTrigger = true;
	m_nScore = 0;
	m_nHeroHit = 0;
	m_nHeroHealth = HEROHEALTH;
	InitBG(m_uIntro);
	InitBG(m_uStage1[0]);
	InitBG(m_uStage1[1]);
	InitBG(m_uStage1[2]);
	InitBG(m_uStage1[3]);
	InitHero(m_uHero[IdleRight]);
	InitHero(m_uHero[IdleLeft]);
	InitHero(m_uHero[RunRight]);
	InitHero(m_uHero[RunLeft]);
	InitHero(m_uHero[JumpRight]);
	InitHero(m_uHero[JumpLeft]);
	InitHero(m_uHero[HitRight]);
	InitHero(m_uHero[HitLeft]);
	InitHero(m_uHero[ShootRight]);
	InitHero(m_uHero[ShootLeft]);

	//Enemy1
	InitEnemy1(m_uEnemy1[Enemy1_Intro]);
	InitEnemy1(m_uEnemy1[Enemy1_Attack]);
	InitEnemy1(m_uEnemy1[Enemy1_Death]);
	InitHeroBullet();
	InitHeroBulletExplode();
	InitEnemy1BulletExplode();
	InitEnemy1Bullet();

	//Enemy2
	InitEnemy2(m_uEnemy2[Enemy2_Intro]);
	InitEnemy2(m_uEnemy2[Enemy2_Attack]);
	InitEnemy2(m_uEnemy2[Enemy2_Death]);
	//InitEnemy2BulletExplode();
	//InitEnemy2Bullet();
	
	m_Alpha[0].bf.SourceConstantAlpha = 255;
	m_Alpha[1].bf.SourceConstantAlpha = 255;
	m_Fade.bf.SourceConstantAlpha = 255;
	m_FX.bf.SourceConstantAlpha = 120;
}

void Game::InitResource(HDC hdc)
{
	// 베이스 기본버퍼
	m_Base.hbmp = (HBITMAP)LoadImage(NULL, L"image//base.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	// base.bmp 저장할때 24비트 비트맵으로 저장해야됨
	GetObject(m_Base.hbmp, sizeof(BITMAP), &m_Base.bit);		// bit에 비트맵정보가 들어감
	m_Base.dc = CreateCompatibleDC(hdc);		// 윈도우화면과 호환되는 DC를 만들기
	m_Base.holdbmp = (HBITMAP)SelectObject(m_Base.dc, m_Base.hbmp);		// 현재상황이 여기에 저장됨

	//Intro
	MakeResource(m_Intro, m_Base, L"image//Intro.bmp", m_uIntro, 6, 1280);

	//BG1
	MakeResource(m_Stage1[0], m_Base, L"image//BG//stage1//0.bmp",m_uStage1[0],4,1280);
	MakeResource(m_Stage1[1], m_Base, L"image//BG//stage1//1.bmp",m_uStage1[1],1,1280);
	MakeResource(m_Stage1[2], m_Base, L"image//BG//stage1//2.bmp",m_uStage1[2],1,1280);
	MakeResource(m_Stage1[3], m_Base, L"image//BG//stage1//3.bmp",m_uStage1[3],1,1280);

	//Hero
	MakeResource(m_Hero[IdleRight], m_Base, L"image//Hero//Idle//IdleRight//1.bmp",m_uHero[IdleRight],5,100);
	MakeResource(m_Hero[IdleLeft], m_Base, L"image//Hero//Idle//IdleLeft//1.bmp", m_uHero[IdleLeft],5,100);
	MakeResource(m_Hero[RunRight], m_Base, L"image//Hero//Run//RunRIght//1.bmp",m_uHero[RunRight],16,100);
	MakeResource(m_Hero[RunLeft], m_Base, L"image//Hero//Run//RunLeft//1.bmp", m_uHero[RunLeft],16,100);
	MakeResource(m_Hero[JumpRight], m_Base, L"image//Hero//Jump//JumpRight//1.bmp");
	MakeResource(m_Hero[JumpLeft], m_Base, L"image//Hero//Jump//JumpLeft//1.bmp");
	MakeResource(m_Hero[HitRight], m_Base, L"image//Hero//Hit//HitRight//1.bmp");
	MakeResource(m_Hero[HitLeft], m_Base, L"image//Hero//Hit//HitLeft//1.bmp");
	MakeResource(m_Hero[ShootRight], m_Base, L"image//Hero//Shoot//ShootRight//1.bmp",m_uHero[ShootRight],6, 100);
	MakeResource(m_Hero[ShootLeft], m_Base, L"image//Hero//Shoot//ShootLeft//1.bmp", m_uHero[ShootLeft], 6, 100);

	//Enemy1
	MakeResource(m_Enemy1[Enemy1_Intro], m_Base, L"image//Enemy1//Attack.bmp", m_uEnemy1[Enemy1_Intro], 22, Enemy1XSIZE);
	MakeResource(m_Enemy1[Enemy1_Attack], m_Base, L"image//Enemy1//Attack.bmp", m_uEnemy1[Enemy1_Attack],22, Enemy1XSIZE);
	MakeResource(m_Enemy1[Enemy1_Death], m_Base, L"image//Enemy1//Attack.bmp", m_uEnemy1[Enemy1_Death], 22, Enemy1XSIZE);

	//Enemy2
	MakeResource(m_Enemy2[Enemy2_Intro], m_Base, L"image//Enemy2//1.bmp", m_uEnemy2[Enemy2_Intro], 17, Enemy2XSIZE);
	MakeResource(m_Enemy2[Enemy2_Attack], m_Base, L"image//Enemy2//1.bmp", m_uEnemy2[Enemy2_Attack], 17, Enemy2XSIZE);
	MakeResource(m_Enemy2[Enemy2_Death], m_Base, L"image//Enemy2//1.bmp", m_uEnemy2[Enemy2_Death], 17, Enemy2XSIZE);

	//HeroBullet
	MakeResource(m_HeroBullet, m_Base, L"image//HeroBullet//HeroBullet.bmp",m_uHeroBullet[0],5,45);

	//EnemyBullet
	for (int i = 0; i < ENEMYBULLETNUM; i++)
	{
		MakeResource(m_Enemy1Bullet, m_Base, L"image//EnemyBullet//Enemy1Bullet.bmp", m_uEnemy1Bullet[i], 3, 61);	//총알
	}

	//HeroBulletExplode
	MakeResource(m_HeroBulletExplode[0], m_Base, L"image//HeroBullet//1.bmp", m_uHeroBulletExplode,3,240);

	//Enemy1BulletExplode
	MakeResource(m_Enemy1BulletExplode, m_Base, L"image//EnemyBullet//Enemy1Explode.bmp", m_uEnemy1BulletExplode[0],6,153);
	MakeResource(m_Enemy1BulletExplode, m_Base, L"image//EnemyBullet//Enemy1Explode.bmp", m_uEnemy1BulletExplode[1],6,153);

	//Alpha
	m_Alpha[0].hbmp = (HBITMAP)LoadImage(NULL, L"image//base.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	
	GetObject(m_Alpha[0].hbmp, sizeof(BITMAP), &m_Base.bit);		

	m_Alpha[0].dc = CreateCompatibleDC(hdc);

	m_Alpha[0].holdbmp = (HBITMAP)SelectObject(m_Alpha[0].dc, m_Alpha[0].hbmp);
	m_Alpha[0].bf.AlphaFormat = 0;
	m_Alpha[0].bf.BlendFlags = 0;
	m_Alpha[0].bf.BlendOp = 0;
	m_Alpha[0].bf.SourceConstantAlpha = 127;	//0~255  127은 반투명임


	m_Alpha[1].hbmp = (HBITMAP)LoadImage(NULL, L"image//base.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	// base.bmp 저장할때 24비트 비트맵으로 저장해야됨
	GetObject(m_Alpha[1].hbmp, sizeof(BITMAP), &m_Base.bit);		// bit에 비트맵정보가 들어감
	m_Alpha[1].dc = CreateCompatibleDC(hdc);		// 윈도우화면과 호환되는 DC를 만들기
	m_Alpha[1].holdbmp = (HBITMAP)SelectObject(m_Alpha[1].dc, m_Alpha[1].hbmp);
	m_Alpha[1].bf.AlphaFormat = 0;
	m_Alpha[1].bf.BlendFlags = 0;
	m_Alpha[1].bf.BlendOp = 0;
	m_Alpha[1].bf.SourceConstantAlpha = 127;	//0~255  127은 반투명임

	//Fade
	m_Fade.hbmp = (HBITMAP)LoadImage(NULL,L"image//Ready//RW.bmp", IMAGE_BITMAP,0, 0, LR_LOADFROMFILE);
	GetObject(m_Fade.hbmp, sizeof(BITMAP), &m_Fade.bit);
	m_Fade.dc = CreateCompatibleDC(m_Base.dc);
	m_Fade.holdbmp = (HBITMAP)SelectObject(m_Fade.dc, m_Fade.hbmp);
	m_Fade.bf.AlphaFormat = 0;
	m_Fade.bf.BlendFlags = 0;
	m_Fade.bf.BlendOp = 0;
	m_Fade.bf.SourceConstantAlpha = 255;
	m_uFade.frame = 0;
	m_uFade.MaxFrame = 22 - 1;
	m_uFade.size = 1280;

	//FX
	m_FX.hbmp = (HBITMAP)LoadImage(NULL, L"image//FrontFX//1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(m_FX.hbmp, sizeof(BITMAP), &m_FX.bit);
	m_FX.dc = CreateCompatibleDC(m_Base.dc);
	m_FX.holdbmp = (HBITMAP)SelectObject(m_FX.dc, m_FX.hbmp);
	m_FX.bf.AlphaFormat = 0;
	m_FX.bf.BlendFlags = 0;
	m_FX.bf.BlendOp = 0;
	m_FX.bf.SourceConstantAlpha = 255;
	m_uFX.frame = 0;
	m_uFX.MaxFrame = 24 - 1;
	m_uFX.size = 1280;

	//SCORE
	MakeResource(m_Score, m_Base, L"image//HeroHealth//score.bmp", m_uScore, 4, 90);

	//CLEAR
	MakeResource(m_Clear, m_Base, L"image//Clear.bmp", m_uClear, 1, 1280);

	//GAMEOVER
	MakeResource(m_Gameover, m_Base, L"image//GameOver.bmp", m_uGameOver, 1, 1280);

}

void Game::InitBG(UPDATE& update)
{
	update.pt.x = 0;
	update.pt.y = 0;
	//update.aEndTick = update.aStartTick = GetTickCount();
}


void Game::InitHero(UPDATE & update)
{
	update.rt.left = 1280/2-HEROXSIZE/2;
	update.rt.top = YRES - HEROYSIZE - 20;
	update.rt.right = update.rt.left + HEROXSIZE;
	update.rt.bottom = update.rt.top + HEROYSIZE;

	m_HeroState = IdleRight;

}

void Game::InitHeroBullet()
{
	for (int i = 0; i < HEROBULLETNUM; i++)
	{
		m_uHeroBullet[i].rt.left = m_Hero[0].rt.left + 45 / 2;		//총알 45x45
		m_uHeroBullet[i].rt.top = m_Hero[0].rt.top;
		m_uHeroBullet[i].rt.right = m_uHeroBullet[i].rt.left + 45;
		m_uHeroBullet[i].rt.bottom = m_uHeroBullet[i].rt.top + 45;
	}
}

void Game::InitHeroBullet(int i)
{
	m_uHeroBullet[i].rt.left = m_uHero[0].rt.left + 45 / 2;		//총알 x : 80
	m_uHeroBullet[i].rt.top = m_uHero[0].rt.top;
	m_uHeroBullet[i].rt.right = m_uHeroBullet[i].rt.left + 45;
	m_uHeroBullet[i].rt.bottom = m_uHeroBullet[i].rt.top + 45;

}

void Game::InitEnemy1Bullet()
{
	srand((unsigned int)time(NULL));
	
	for (int i = 0; i < ENEMYBULLETNUM; i++)
	{
		m_uEnemy1Bullet[i].rt.left = rand() % XFILE;
		m_uEnemy1Bullet[i].rt.right = m_uEnemy1Bullet[i].rt.left + 61;
		m_uEnemy1Bullet[i].rt.top = 0-rand() % YFILE;
		m_uEnemy1Bullet[i].rt.bottom = m_uEnemy1Bullet[i].rt.top + 105;
	}
}

void Game::InitEnemy1Bullet(int i)
{
	//srand((unsigned int)time(NULL));			// 총알2개가 동시에(같은시간)에 초기화되면 무한루프

	m_uEnemy1Bullet[i].rt.left = ((XRES + 1) / 61)*(rand() % 61 + 1);		//61배수의 랜덤수 
	m_uEnemy1Bullet[i].rt.right = m_uEnemy1Bullet[i].rt.left + 61;
	m_uEnemy1Bullet[i].rt.top = 0 - (YRES / 105) * (rand() % 105 +1);		//105배수의 랜덤수
	m_uEnemy1Bullet[i].rt.bottom = m_uEnemy1Bullet[i].rt.top + 105;

	if (InitOverLap(i))		// x,y 좌표가 겹친다면 다시좌표초기화
	{
		return;
	}
	else
	{
		InitEnemy1Bullet(i);
	}
}


bool Game::InitOverLap(int i)		//x좌표가 서로같은게 있다면 false, 아니면 true
{
	for (int j = 0; j < i ; j++)
	{
		if (m_uEnemy1Bullet[i].rt.left == m_uEnemy1Bullet[j].rt.left)
			return false;
		else
			true;
	}
	for (int j = i + 1; j < ENEMYBULLETNUM; j++)
	{
		if (m_uEnemy1Bullet[i].rt.left == m_uEnemy1Bullet[j].rt.left)
			return false;
		else
			true;
	}
}


void Game::InitEnemy1(UPDATE & update)
{
	update.rt.left = 1280 / 2 - Enemy1XSIZE /2;
	update.rt.top =  -Enemy1YSIZE+500;
	update.rt.right = update.rt.left + Enemy1XSIZE;
	update.rt.bottom = update.rt.top + Enemy1YSIZE;

	m_EnemyState = Enemy1_Attack;
}

void Game::InitEnemy2(UPDATE & update)
{
	update.rt.left = 1280 / 2 - Enemy2XSIZE / 2;
	update.rt.top = -Enemy2YSIZE+500;
	update.rt.right = update.rt.left + Enemy2XSIZE;
	update.rt.bottom = update.rt.top + Enemy2YSIZE;

	//m_EnemyState = Enemy2_Attack;
}
void Game::ReleaseResource()
{
	SelectObject(m_Base.dc, m_Base.holdbmp);
	DeleteDC(m_Base.dc);		//m_Base.dc = CreateCompatibleDC(hdc); 이걸로 만들어진걸 delete
}

void Game::GameLoop(HDC hdc)
{
	UpdateAll();
	DrawAll(hdc);
}

void Game::SetClient()
{
	m_rtClient = { 0, 0, 1280, 720 };
}

RECT Game::GetClient()
{
	return m_rtClient;
}

bool Game::KeyCheck()
{
	if (m_StageNum == INTRO)		// 인트로라면
	{
		m_StageNum = STAGE1;		// 레디화면 보이게
		return true;
	}
	return false;
}

void Game::MakeResource(HANDLES & dest, HANDLES base, const WCHAR * w)
{
	// TODO: 여기에 구현 코드 추가.
	dest.hbmp = (HBITMAP)LoadImage(NULL,
		w, IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);
	GetObject(dest.hbmp, sizeof(BITMAP), &dest.bit);

	//!!!!여기서부턴베이스에호환되는 dc 를 만든다
	dest.dc = CreateCompatibleDC(base.dc);
	dest.holdbmp = (HBITMAP)SelectObject(dest.dc, dest.hbmp);
}

void Game::MakeResource(HANDLES & dest, HANDLES base, const WCHAR * w, UPDATE & update, int MaxFrame, int size)
{
	// TODO: 여기에 구현 코드 추가.
	dest.hbmp = (HBITMAP)LoadImage(NULL,
		w, IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);
	GetObject(dest.hbmp, sizeof(BITMAP), &dest.bit);

	//!!!!여기서부턴베이스에호환되는 dc 를 만든다
	dest.dc = CreateCompatibleDC(base.dc);
	dest.holdbmp = (HBITMAP)SelectObject(dest.dc, dest.hbmp);

	update.frame = 0;
	update.MaxFrame = MaxFrame-1;
	update.size = size;
}


void Game::InitHeroBulletExplode()
{
	m_uHeroBulletExplode.aEndTick = m_uHeroBulletExplode.aStartTick = GetTickCount();
	m_uHeroBulletExplode.bTrigger = FALSE;				//적에 부딫히면 true
}

void Game::InitEnemy1BulletExplode()
{
	m_uEnemy1BulletExplode[0].aEndTick = m_uEnemy1BulletExplode[0].aStartTick = GetTickCount();
	m_uEnemy1BulletExplode[1].aEndTick = m_uEnemy1BulletExplode[1].aStartTick = GetTickCount();
	m_uEnemy1BulletExplode[0].bTrigger = FALSE;				//적에 부딫히면 true
	m_uEnemy1BulletExplode[1].bTrigger = FALSE;				//적에 부딫히면 true
	m_uEnemy1BulletExplode[0].test = 0;
	m_uEnemy1BulletExplode[1].test = 0;

}

void Game::DrawAll(HDC hdc)
{

	switch (m_StageNum)
	{
	case INTRO:
		DrawIntro();
		DrawFX();
		break;
	case STAGE1:
		DrawBG();
		DrawEnemy1(hdc);
		DrawBG2();
		DrawHeroBullet(hdc);
		DrawHero(hdc);
		DrawHeroBulletExplode();
		DrawEnemy1Bullet();
		DrawEnemy1BulletExplode();
		DrawBG3();
		DrawScore(hdc);
		DrawFade();
		DrawFX();
		break;
	case STAGE2:
		DrawBG();
		DrawEnemy2(hdc);
		DrawBG2();
		DrawHeroBullet(hdc);
		DrawHero(hdc);
		DrawHeroBulletExplode();
		DrawEnemy1Bullet();
		DrawEnemy1BulletExplode();
		DrawBG3();
		DrawScore(hdc);
		DrawFade();
		DrawFX();
		break;
	case CLEAR:
		DrawClear();
		DrawFX();
		break;
	case GAME_OVER:
		DrawGameover();
		DrawFX();
		break;
	default:
		break;
	}
	DrawDebug(hdc);
	BitBlt(hdc, 0, 0, m_Base.bit.bmWidth, m_Base.bit.bmHeight, m_Base.dc, 0, 0, SRCCOPY);//윈도우 화면에 베이스 찍기

}

void Game::DrawAlpha()
{
	BitBlt(m_Alpha[0].dc, 0, 0, XRES, YRES, m_Base.dc, 0, 0, SRCCOPY);
}

void Game::DrawFade()
{
	BitBlt(m_Alpha[0].dc, 0, 0, XRES, YRES, m_Fade.dc, m_uFade.frame * 1280, 0, SRCCOPY);
	AlphaBlend(m_Base.dc, 0, 0, XRES, YRES, m_Alpha[0].dc, 0, 0, XRES, YRES, m_Fade.bf);
}

void Game::DrawFX()
{
	BitBlt(m_Alpha[1].dc, 0, 0, XRES, YRES, m_FX.dc, m_uFX.frame * 1280, 0, SRCCOPY);
	AlphaBlend(m_Base.dc, 0, 0, XRES, YRES, m_Alpha[1].dc, 0, 0, XRES, YRES, m_FX.bf);
}


void Game::DrawHero(HDC hdc)
{
	TransparentBlt(m_Base.dc,
		m_uHero[m_HeroState].rt.left,								//그리기 시작위치 x
		m_uHero[m_HeroState].rt.top,								//그리기 시작위치 y
		HEROXSIZE,											//그릴 길이
		HEROYSIZE,												//그릴 높이
		m_Hero[m_HeroState].dc,									//소스의 dc
		m_uHero[m_HeroState].frame* HEROXSIZE,	//소스의 x위치 
		0,
		HEROXSIZE,
		HEROYSIZE,
		RGB(255, 255, 255));

	for (int i = 0; i < 12; i++)
	{
		//MaxMinXBG(m_uEnemy1[i]);
		if(m_Scene == Playing)
			MoveKey(m_uHero[i], 1, 10);	//중요
	}
}

void Game::DrawHeroBullet(HDC hdc)
{
	for (int i = 0; i < HEROBULLETNUM; i++)
	{
		if (m_uHeroBullet[i].bTrigger == TRUE)
		{
			TransparentBlt(m_Base.dc,
				m_uHeroBullet[i].rt.left,
				m_uHeroBullet[i].rt.top,
				45,
				45,
				m_HeroBullet.dc,
				0,	//소스의 x위치 
				0,
				45,
				45,
				RGB(255, 255, 255));
		}
	}
}

void Game::DrawEnemy1(HDC hdc)
{
	TransparentBlt(m_Base.dc,
		m_uEnemy1[m_EnemyState].rt.left,								//그리기 시작위치 x
		m_uEnemy1[m_EnemyState].rt.top,									//그리기 시작위치 y
		Enemy1XSIZE,													//그릴 길이
		Enemy1YSIZE,													//그릴 높이
		m_Enemy1[m_EnemyState].dc,										//소스의 dc
		m_uEnemy1[m_EnemyState].frame* m_uEnemy1[m_EnemyState].size,	//소스의 x위치 
		0,
		Enemy1XSIZE,													//그릴 길이
		Enemy1YSIZE,
		RGB(0, 128, 128));

	//for (int i = 0; i < 10; i++)
	//{
	//	//MaxMinXBG(m_uEnemy1[i]);
	//	MoveKey(m_uEnemy1[i], 1, 10);
	//}
}

void Game::DrawEnemy1Bullet()
{
	for (int i = 0; i < ENEMYBULLETNUM; i++)
	{
		TransparentBlt(m_Base.dc,
			m_uEnemy1Bullet[i].rt.left,	
			m_uEnemy1Bullet[i].rt.top,										
			61,				
			105,		
			m_Enemy1Bullet.dc,		
			m_uEnemy1Bullet[i].frame * m_uEnemy1Bullet[i].size,		
			0,
			61,
			105,
			RGB(0, 128, 128));
		
	}
}

void Game::DrawEnemy2(HDC hdc)
{
	TransparentBlt(m_Base.dc,
		m_uEnemy2[m_EnemyState].rt.left,								//그리기 시작위치 x
		m_uEnemy2[m_EnemyState].rt.top,									//그리기 시작위치 y
		Enemy2XSIZE,													//그릴 길이
		Enemy2YSIZE,													//그릴 높이
		m_Enemy2[m_EnemyState].dc,										//소스의 dc
		m_uEnemy2[m_EnemyState].frame* m_uEnemy2[m_EnemyState].size,	//소스의 x위치 
		0,
		Enemy2XSIZE,													//그릴 길이
		Enemy2YSIZE,
		RGB(0, 128, 128));
}

void Game::DrawIntro()
{
	TransparentBlt(m_Base.dc,
		0, 0,
		XRES,
		YRES,
		m_Intro.dc,
		m_uIntro.frame* m_uIntro.size,
		m_uIntro.pt.y, 
		XRES, YRES,
		RGB(1, 2, 3));
}

void Game::DrawBG()
{
	TransparentBlt(m_Base.dc,
		0, 0,
		XRES,
		YRES,
		m_Stage1[0].dc,
		m_uStage1[0].pt.x,
		0,
		XRES, YRES,
		RGB(255, 0, 255));

	TransparentBlt(m_Base.dc,
		0, 0,
		XRES,
		YRES,
		m_Stage1[1].dc,
		0,
		0,
		XRES, YRES,
		RGB(255, 255, 255));
}

void Game::DrawBG2()
{
	TransparentBlt(m_Base.dc,
		0, 0,
		XRES,
		YRES,
		m_Stage1[2].dc,
		m_uStage1[2].pt.x,
		0,
		XRES, YRES,
		RGB(255, 255, 255));
}

void Game::DrawBG3()
{
	TransparentBlt(m_Base.dc,
		0, 0,
		XRES,
		YRES,
		m_Stage1[3].dc,
		m_uStage1[3].pt.x,
		0,
		XRES, YRES,
		RGB(255, 255, 255));
}

void Game::DrawClear()
{
	TransparentBlt(m_Base.dc,
		0, 0,
		XRES,
		YRES,
		m_Clear.dc,
		0,
		0,
		XRES, YRES,
		RGB(1, 1, 1));
}

void Game::DrawGameover()
{
	TransparentBlt(m_Base.dc,
		0, 0,
		XRES,
		YRES,
		m_Gameover.dc,
		0,
		0,
		XRES, YRES,
		RGB(1, 1, 1));
}

void Game::DrawHeroBulletExplode()
{
	if (m_uHeroBulletExplode.bTrigger == FALSE) return;

	POINT pt;
	if (m_StageNum == STAGE1)
	{
		pt.x = m_Enemy1[0].rt.left + 500;
		pt.y = m_Enemy1[0].rt.top + (m_uEnemy1[0].size - 240) / 2;
	}
	else if(m_StageNum == STAGE2)
	{
		pt.x = m_Enemy2[0].rt.left + 500;
		pt.y = m_Enemy2[0].rt.top + (m_uEnemy2[0].size - 240) / 2 + 300;
	}
	TransparentBlt(m_Base.dc,
		pt.x,
		pt.y,
		240,
		240,
		m_HeroBulletExplode[m_uHeroBulletExplode.frame].dc,
		240 * m_uHeroBulletExplode.frame,
		0,
		240,
		240,
		RGB(0, 128, 128));
}
void Game::DrawEnemy1BulletExplode()
{
	//if (m_uEnemy1BulletExplode.bTrigger == FALSE) return;
	if (m_uEnemy1BulletExplode[0].bTrigger == FALSE) return;
	
	
	POINT pt;
	pt.x = m_uEnemy1BulletExplode[0].rt.left;
	pt.y = m_uEnemy1BulletExplode[0].rt.top;

	TransparentBlt(m_Base.dc,
		pt.x,
		pt.y,
		153,
		116,
		//m_Enemy1BulletExplode[m_uEnemy1BulletExplode.frame].dc,
		m_Enemy1BulletExplode.dc,
		153 * m_uEnemy1BulletExplode[0].frame,
		//153,
		0,
		153,
		116,
		RGB(0, 128, 128));
	
}

void Game::DrawDebug(HDC hdc)
{
	if (m_bDebug == FALSE) return;

		Rectangle(hdc, m_uHeroBullet[0].rt.left, m_uHeroBullet[0].rt.top, m_uHeroBullet[0].rt.right, m_uHeroBullet[0].rt.bottom);
		Rectangle(hdc, m_uHero[0].rt.left, m_uHero[0].rt.top, m_uHero[0].rt.right, m_uHero[0].rt.bottom);
		Rectangle(hdc, m_uEnemy1[1].rt.left, m_uEnemy1[1].rt.top, m_uEnemy1[1].rt.right, m_uEnemy1[1].rt.bottom-200 );


		WCHAR ttt[100];
		// TODO: 여기에 구현 코드 추가.
		//wsprintf(ttt, L"FPS : %d", m_Debug.FrameRate);
		wsprintf(ttt, L"FPS : %d", m_uEnemy2[1].rt.top);

		size_t size;
		StringCchLength(ttt, 100, &size);
		SetBkMode(m_Base.dc, TRANSPARENT);

		SetTextColor(m_Base.dc, RGB(0, 0, 0));

		TextOut(m_Base.dc, 30, 50, ttt, (int)size);

		SetTextColor(m_Base.dc, RGB(255, 255, 255));
		TextOut(m_Base.dc, 25, 45, ttt, (int)size);

		for (int i = 0; i < ENEMYBULLETNUM; i++)
		{
			Rectangle(hdc, m_uEnemy1Bullet[i].rt.left, m_uEnemy1Bullet[i].rt.top, m_uEnemy1Bullet[i].rt.right, m_uEnemy1Bullet[i].rt.bottom);
		}
		for (int i = 0; i < ENEMYBULLETNUM; i++)
		{
			wsprintf(ttt, L"[%d]위치 : [%d,%d]",
				i,
				m_uEnemy1Bullet[i].rt.left,
				m_uEnemy1Bullet[i].rt.right
			);
			//wsprintf(ttt, L"%d,%d,%d,%d",
			//	m_uHero[i].rt.left, m_uHero[i].rt.top, m_uHero[i].rt.right, m_uHero[i].rt.bottom);
			StringCchLength(ttt, 100, &size);
			SetTextColor(m_Base.dc, RGB(0, 0, 0));
			TextOut(m_Base.dc, 80, 80 + i * 20, ttt, (int)size);
		}
	
}
	

void Game::DrawScore(HDC hdc)
{
	WCHAR ttt[100];
	size_t size;
	wsprintf(ttt, L"SCORE : %d", m_nScore);

	StringCchLength(ttt, 100, &size);
	SetBkMode(m_Base.dc, TRANSPARENT);

	SetTextColor(m_Base.dc, RGB(0, 0, 0));
	TextOut(m_Base.dc, 10, 10, ttt, (int)size);

	SetTextColor(m_Base.dc, RGB(255, 255, 255));
	TextOut(m_Base.dc, 9, 9, ttt, (int)size);


	if (m_nHeroHealth == 4)
	{
		TransparentBlt(m_Base.dc, 50, YRES - 100, 90, 35, m_Score.dc, 90 * 0, 0, 90, 35, RGB(255, 255, 255));
	}
	else if (m_nHeroHealth == 3)
	{
		TransparentBlt(m_Base.dc, 50, YRES - 100, 90, 35, m_Score.dc, 90 * 1, 0, 90, 35, RGB(255, 255, 255));
	}
	else if (m_nHeroHealth == 2)
	{
		TransparentBlt(m_Base.dc, 50, YRES - 100, 90, 35, m_Score.dc, 90 * 2, 0, 90, 35, RGB(255, 255, 255));
	}
	else if (m_nHeroHealth == 1)
	{
		TransparentBlt(m_Base.dc, 50, YRES - 100, 90, 35, m_Score.dc, 90 * 3, 0, 90, 35, RGB(255, 255, 255));
	}


}

void Game::UpdateAll()
{
	switch (m_StageNum)
	{
	case INTRO:
		//UpdatePress();
		UpdateIntro();
		break;
	case STAGE1:
		UpdateFade();
		if (m_Scene == Playing)
		{
			UpdateEnemy1();
			UpdateHeroBullet();
			UpdateStage1();
			MoveHeroBullet();
			UpdateHero();
			UpdateHeroBulletExplode();
			UpdateEnemy1Bullet();
			UpdateEnemy1BulletExplode();
			MoveEnemy1Bullet();
		}
		break;
	case STAGE2:
		UpdateFade();
		//if (m_Scene == Playing)
		{
			UpdateEnemy2();
			UpdateHeroBullet();
			UpdateStage1();
			MoveHeroBullet();
			UpdateHero();
			UpdateHeroBulletExplode();
			UpdateEnemy1Bullet();
			UpdateEnemy1BulletExplode();
			MoveEnemy1Bullet();
		}
		break;
	case CLEAR:
		break;
	case GAME_OVER:
		break;
	default:
		break;
	}
	//UpdateDebug();
	UpdateFX();
}

void Game::UpdateHero()
{
	FramePlus(m_uHero[m_HeroState], 100);
	//MoveKey(m_uHero[m_HeroState], 50, 10);
}

void Game::UpdateHeroBullet()
{
	for (int i = 0; i < HEROBULLETNUM; i++)	
	{
		FramePlus(m_uHeroBullet[i], 100);
	}
}

void Game::MoveHeroBullet()
{
	for (int i = 0; i < HEROBULLETNUM; i++)		
	{

		m_uHeroBullet[i].aEndTick = GetTickCount();			// 프로그램실행훈 1000분에 1초로 tick을 세고있음

		if (m_uHeroBullet[i].aEndTick - m_uHeroBullet[i].aStartTick > 10)		// (프로그램실행부터 현재까지의 tick - 새로운 tick) 이 100보다 크다면 
		{
			m_uHeroBullet[i].aStartTick = m_uHeroBullet[i].aEndTick;		// 새로운 tick
			if (m_uHeroBullet[i].bTrigger == true)
			{
				m_uHeroBullet[i].rt.top -= 10;
				m_uHeroBullet[i].rt.bottom -= 10;
				AttariCheck();
			}
			if (m_uHeroBullet[i].rt.bottom < 0)//화면을벗어나는순간
			{
				InitHeroBullet(i);		//초기화 
				m_uHeroBullet[i].bTrigger = FALSE;	//안쏜걸로 세팅
				//DrawEnemy1BulletExplode(m_uHeroBullet[i].rt.left, m_uHeroBullet[i].rt.top);
				DrawEnemy1BulletExplode();
				//m_uHeroBullet[i].test++;
			}
		}

	}

}

void Game::UpdateEnemy1()
{
	FramePlus(m_uEnemy1[m_EnemyState], 103);
}

void Game::UpdateEnemy2()
{
	FramePlus(m_uEnemy2[m_EnemyState], 103);
}

void Game::UpdateHeroBulletExplode()
{
	if (m_uHeroBulletExplode.bTrigger == FALSE) return;

	FramePlus(m_uHeroBulletExplode, 100);
	if (UpdateCheck(m_uHeroBulletExplode, 150) == TRUE)
	{
		m_uHeroBulletExplode.frame++;
		if (m_uHeroBulletExplode.frame > m_uHeroBulletExplode.MaxFrame)
		{
			m_uHeroBulletExplode.frame = 0;
			m_uHeroBulletExplode.bTrigger = FALSE;
		}
	}
}

void Game::UpdateEnemy1BulletExplode()
{
	//if (m_uEnemy1BulletExplode.bTrigger == FALSE) return;

	FramePlus(m_uEnemy1BulletExplode[0], 100);
	if (UpdateCheck(m_uEnemy1BulletExplode[0], 150) == TRUE)
	{
		m_uEnemy1BulletExplode[0].frame++;
		if (m_uEnemy1BulletExplode[0].frame > m_uEnemy1BulletExplode[0].MaxFrame)
		{
			m_uEnemy1BulletExplode[0].frame = 0;
			m_uEnemy1BulletExplode[0].bTrigger = FALSE;
			//m_uEnemy1BulletExplode[0].test++;
		}
	}
}

void Game::UpdateEnemy1Bullet()
{
	for (int i = 0; i < ENEMYBULLETNUM; i++)
	{
		m_uEnemy1Bullet[i].aEndTick = GetTickCount();
		if (m_uEnemy1Bullet[i].aEndTick - m_uEnemy1Bullet[i].aStartTick > 100)
		{
			m_uEnemy1Bullet[i].aStartTick = m_uEnemy1Bullet[i].aEndTick;
			m_uEnemy1Bullet[i].frame++;
			if (m_uEnemy1Bullet[i].frame >= m_uEnemy1Bullet[i].MaxFrame)
			{
				m_uEnemy1Bullet[i].frame = 0;
			}
		}
	}
}

void Game::MoveEnemy1Bullet()
{
	for (int i = 0; i < ENEMYBULLETNUM; i++)
	{
		m_uEnemy1Bullet[i].bEndTick = GetTickCount();			// 프로그램실행훈 1000분에 1초로 tick을 세고있음
		if (m_uEnemy1Bullet[i].bEndTick - m_uEnemy1Bullet[i].bStartTick > 30)		// (프로그램실행부터 현재까지의 tick - 새로운 tick) 이 100보다 크다면 
		{
			m_uEnemy1Bullet[i].bStartTick = m_uEnemy1Bullet[i].bEndTick;		// 새로운 tick
			m_uEnemy1Bullet[i].rt.top += 10;
			m_uEnemy1Bullet[i].rt.bottom += 10;
			AttariCheck();
			if (m_uEnemy1Bullet[i].rt.top > YRES)//화면을벗어나는순간
			{
				InitEnemy1Bullet(i);		//초기화 
				m_uEnemy1Bullet[i].bTrigger = FALSE;	//안쏜걸로 세팅
			}
		}

	}
}

void Game::UpdateIntro()
{
	FramePlus(m_uIntro,120);
}

void Game::UpdateStage1()
{
	xPlus(m_uStage1[0], 1,1);
	//sFramePlus(m_uStage1[0],10);
}

void Game::UpdateFade()
{
	FramePlus(m_uFade, 125);
	if (m_Fade.bf.SourceConstantAlpha > 0)
	{
		if (UpdateCheck(m_uFade, 10) == TRUE)
		{
			m_Fade.bf.SourceConstantAlpha -=1;
			if (m_Fade.bf.SourceConstantAlpha == 0)
				m_Scene = Playing;
				return;
				//m_Fade.bf.SourceConstantAlpha = 0;
		}

	}

}

void Game::UpdateFX()
{
	FramePlus(m_uFX, 125);
	//if (m_FX.bf.SourceConstantAlpha > 0)
	//{
	//	if (UpdateCheck(m_uFX, 10) == TRUE)
	//	{
	//		m_FX.bf.SourceConstantAlpha -= 1;
	//		if (m_FX.bf.SourceConstantAlpha == 0)
	//			m_Scene = Playing;
	//		return;
	//	}

	//}

}

void Game::AttariCheck()
{
	POINT pt;
	for (int i = 0; i < HEROBULLETNUM; i++)			//히어로총알 vs 적
	{
		pt.x = m_uHeroBullet[i].rt.left;
		pt.y = m_uHeroBullet[i].rt.top+200;
		//피격됨
		if (PtInRect(&m_uEnemy1[0].rt, pt) != FALSE)
		{
			InitHeroBullet(i);//총알초기화
			m_uHeroBullet[i].bTrigger = FALSE;
			m_nScore += 100;
			m_uHeroBulletExplode.bTrigger = TRUE;				//폭발 이펙트 활성화
			if (m_nScore >= Enemy1_HEALTH)
			{
				m_StageNum = STAGE2;
				m_EnemyState = Enemy2_Intro;
				m_uClear.aEndTick = GetTickCount();
				m_uClear.aStartTick = m_uClear.aEndTick;
				//스테이지끝나면 초기화 해야될것 은 updateclear에서
			}
			if (m_nScore >= Enemy2_HEALTH)
			{
				m_StageNum = CLEAR;
			}
			
		}
	}
	for (int i = 0; i < ENEMYBULLETNUM; i++)		//적총알 vs 히어로
	{

		RECT rcTemp;
		//피격됨
		//if (PtInRect(&m_uHero[0].rt, pt) != FALSE)
		if (IntersectRect(&rcTemp, &m_uHero[0].rt, &m_uEnemy1Bullet[i].rt) != FALSE)
		{
			m_uEnemy1BulletExplode[0].bTrigger = TRUE;				//폭발 이펙트 활성화
			m_uEnemy1BulletExplode[0].rt.left = m_uEnemy1Bullet[i].rt.left;
			m_uEnemy1BulletExplode[0].rt.top = m_uEnemy1Bullet[i].rt.top;
			m_nHeroHit += 1;
			m_nHeroHealth -= 1;
			m_uEnemy1BulletExplode[0].test++;
			//DrawEnemy1BulletExplode(m_uEnemy1Bullet[i].rt.left, m_uEnemy1Bullet[i].rt.top);
			//DrawEnemy1BulletExplode(m_uHero[0].rt.left, m_uHero[0].rt.top);
			DrawEnemy1BulletExplode();
			m_uHeroBullet[i].rt.top += 10;
			m_uHeroBullet[i].rt.bottom += 10;
			if (UpdateCheck(m_uHeroBullet[i], 1000) == true)
			{
				m_uHeroBullet[i].rt.top -= 10;
				m_uHeroBullet[i].rt.bottom -= 10;
			}
			if (m_nHeroHealth < 1)
			{
				m_StageNum = GAME_OVER;
				//스테이지끝나면 초기화 해야될것 은 updateclear에서
			}
			InitEnemy1Bullet(i);//총알초기화

		}

	}
}

void Game::UpdatePress()
{
	m_uPress.mEndTick = GetTickCount();
	if (m_uPress.mEndTick - m_uPress.mStartTick > 500)
	{
		m_uPress.mStartTick = m_uPress.mEndTick;
		m_uPress.bTrigger = !m_uPress.bTrigger;		// true, false 반복되도록 
	}
}

bool Game::UpdateCheck(UPDATE & up, unsigned int tick)
{
	up.aEndTick = GetTickCount();
	if (up.aEndTick - up.aStartTick > tick)
	{
		up.aStartTick = up.aEndTick;
		return true;

	}
	return false;
}


void Game::FramePlus(UPDATE& update,int tick)
{
	update.mEndTick = GetTickCount();
	if (update.mEndTick - update.mStartTick > tick)
	{
		update.mStartTick = update.mEndTick;
		update.frame++;
		if (update.frame > update.MaxFrame)
		{
			update.frame = 0;
		}
	}
}

void Game::xPlus(UPDATE & update, int tick, int n)
{
	update.mEndTick = GetTickCount();
	if (update.mEndTick - update.mStartTick > tick)
	{
		update.mStartTick = update.mEndTick;
		update.pt.x += n;
		if (update.pt.x > XFILE)
		{
			update.pt.x = 0;
		}
	}
}

void Game::MoveKey(UPDATE & update, int tick, int n)
{
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)&& m_uHero[0].rt.right <= XRES)
	{
		m_HeroState = RunRight;
		xPlusAni(update, tick, n);
		/*m_uHeroBullet[0].bEndTick = GetTickCount();
		if (m_uHeroBullet[0].bEndTick - m_uHeroBullet[0].bStartTick > 10)
		{
			m_uHeroBullet[0].bStartTick = m_uHeroBullet[0].bEndTick;
			m_uStage1[2].pt.x += 1;
		}*/
	}
	else if (m_HeroState == RunRight)
	{
		m_HeroState = IdleRight;
	}

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && m_uHero[0].rt.left > 0)
	{
		m_HeroState = RunLeft;
		xPlusAni(update, tick, -n);
		/*m_uHeroBullet[0].bEndTick = GetTickCount();
		if (m_uHeroBullet[0].bEndTick - m_uHeroBullet[0].bStartTick > 10)
		{
			m_uHeroBullet[0].bStartTick = m_uHeroBullet[0].bEndTick;
			m_uStage1[2].pt.x -= 1;
		}*/
	}
	else if (m_HeroState == RunLeft)
	{
		m_HeroState = IdleLeft;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8001 && ((m_HeroState == IdleRight) || (m_HeroState == RunRight) || (m_HeroState == ShootRight)))
	{
		m_HeroState = ShootRight;
		m_uHeroBullet[0].bEndTick = GetTickCount();
		if (m_uHeroBullet[0].bEndTick - m_uHeroBullet[0].bStartTick > tick)
		{
			m_uHeroBullet[0].bStartTick = m_uHeroBullet[0].bEndTick;

			for (int i = 0; i < HEROBULLETNUM; i++)
			{
				if (m_uHeroBullet[i].bTrigger == FALSE)
				{
					InitHeroBullet(i);
					m_uHeroBullet[i].bTrigger = TRUE;

					break;
				}
			}
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8001 && ((m_HeroState == IdleLeft) || (m_HeroState == RunLeft) || (m_HeroState == ShootLeft)))
	{
		m_HeroState = ShootLeft;
		m_uHeroBullet[0].aEndTick = GetTickCount();
		if (m_uHeroBullet[0].aEndTick - m_uHeroBullet[0].aStartTick > tick)
		{
			m_uHeroBullet[0].aStartTick = m_uHeroBullet[0].aEndTick;

			for (int i = 0; i < HEROBULLETNUM; i++)
			{
				if (m_uHeroBullet[i].bTrigger == FALSE)
				{
					InitHeroBullet(i);
					m_uHeroBullet[i].bTrigger = TRUE;
					break;
				}
			}

		}
	}
	//else if (m_HeroState == ShootRight)
	//{
	//	m_HeroState = IdleRight;
	//}


	/*if (GetAsyncKeyState(VK_SPACE) & 0x8000 && ((m_HeroState == IdleLeft) || (m_HeroState == RunLeft)))
	{
		m_uPress.mEndTick = GetTickCount();
		if (m_uPress.mEndTick - m_uPress.mStartTick > 500)
		{
			m_uPress.mStartTick = m_uPress.mEndTick;
			m_HeroState = ShootLeft;
			for (int i = 0; i < HEROBULLETNUM; i++)
			{
				if (m_uHeroBullet[i].bTrigger == false)
				{
					InitHeroBullet(i);
					m_uHeroBullet[i].bTrigger = true;
					break;
				}
			}
		}
	}*/

	//else if (m_HeroState == ShootLeft)
	//{
	//	m_HeroState = IdleLeft;
	//}
	

}



void Game::xPlusAni(UPDATE & update, int tick, int n)
{
	update.aEndTick = GetTickCount();
	if (update.aEndTick - update.aStartTick > tick)
	{
		update.aStartTick = update.aEndTick;
		update.rt.left += n;
		update.rt.right += n;
		if (update.frame > update.MaxFrame)
		{
			update.frame = 0;
		}
	}
}

void Game::PlusBullet(UPDATE & update, int tick, int n)
{
	update.aEndTick = GetTickCount();
	if (update.aEndTick - update.aStartTick > tick)
	{
		update.aStartTick = update.aEndTick;
		for (int i = 0; i < HEROBULLETNUM; i++)
		{
			if (update.bTrigger == false)
			{
				InitHeroBullet(i);
				update.bTrigger = true;
				break;
			}
		}
	}
}

void Game::SetDebug()
{
	// TODO: 여기에 구현 코드 추가.
	m_bDebug = !m_bDebug;
}

