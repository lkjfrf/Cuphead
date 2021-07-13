#pragma once
class Game
{
private:
	RECT m_rtClient;		//윈도우창크기
	int m_HeroState;		//히어로 상태
	int m_EnemyState;		//적 상태
	int m_StageNum;			//스테이지넘버
	bool m_bDebug;			//디버깅모드
	int m_LastKey;			//마지막으로 눌렀던 키
	int m_nScore;
	int m_EnemyBulletX[3];
	int m_nHeroHit;			//적총알에 맞았을때
	int m_nHeroHealth;		//히어로 목숨
	POINT m_ptEnemy1Explod;
	int m_Scene;			//장면 나누기

	// UPDATE
	//맵
	UPDATE m_uScore;		//점수
	UPDATE m_uIntro;		//인트로
	UPDATE m_uStage1[4];		//스테이지1
	UPDATE m_uStage2;		//스테이지2
	UPDATE m_uClear;		//클리어
	UPDATE m_uGameOver;		//게임오버
	UPDATE m_uFade;
	UPDATE m_uFX;			//옛날화면 효과
	//캐릭터
	UPDATE m_uHero[12];
	UPDATE m_uHeroBullet[HEROBULLETNUM];
	UPDATE m_uEnemy1[3];
	UPDATE m_uEnemy1Bullet[ENEMYBULLETNUM];
	UPDATE m_uEnemy2[3];
	UPDATE m_uEnemy2Bullet[3];
	UPDATE m_uHeroBulletExplode;
	UPDATE m_uEnemy1BulletExplode[2];			//  바닥에 닿을때와 히어로에 닿을때
	UPDATE m_uEnemy2BulletExplode;			
	//Ex
	UPDATE m_uPress;

	//HANDLES
	//맵
	HANDLES m_Score;		//점수
	HANDLES m_Intro;		//인트로
	HANDLES m_Stage1[4];		//스테이지1
	HANDLES m_Stage2;		//스테이지2
	HANDLES m_Clear;		//클리어
	HANDLES m_Gameover;		//게임오버
	HANDLES m_Alpha[3];
	HANDLES m_Fade;			
	HANDLES m_FX;			
	//캐릭터
	HANDLES m_Hero[12];
	HANDLES m_HeroBullet;
	HANDLES m_Enemy1[3];
	HANDLES m_Enemy1Bullet;		
	HANDLES m_Enemy2[3];
	HANDLES m_Enemy2Bullet;
	HANDLES m_HeroBulletExplode[EXPFRAME];
	HANDLES m_Enemy1BulletExplode;
	HANDLES m_Enemy2BulletExplode;
	//Ex
	HANDLES m_Base;			//기본버퍼 이위에 버퍼를 추가해서 이중버퍼로 그릴거임
	


	DEBUG m_Debug;
public:
	//생성자 소멸자
	Game();
	~Game();
	
	//Init
	void InitAll();			//모두초기화
	void InitResource(HDC hdc);	//화면출력에 필요한 자료 초기화
	void InitBG(UPDATE& update);
	void ReleaseResource();		//소멸자
	void InitHero(UPDATE& update);	
	void InitHeroBullet();	
	void InitHeroBullet(int n);	
	void InitEnemy1(UPDATE& update);
	void InitEnemy2(UPDATE& update);
	void InitEnemy1Bullet();
	void InitEnemy1Bullet(int i);
	//void InitEnemy2Bullet();
	//void InitEnemy2Bullet(int i);
	void InitHeroBulletExplode();
	void InitEnemy1BulletExplode();

	//그리기
	void DrawAll(HDC hdc);			//그리기
	//맵
	void DrawIntro();
	void DrawBG();		//스테이지1
	void DrawBG2();		//스테이지1
	void DrawBG3();		//스테이지1
	void DrawClear();		//클리어
	void DrawGameover();		//게임오버
	void DrawFade();
	void DrawFX();		//레트로화면 이펙트
	void DrawAlpha();
	//캐릭터
	void DrawHero(HDC hdc);
	void DrawHeroBullet(HDC hdc);
	void DrawEnemy1(HDC hdc);
	void DrawEnemy1Bullet();
	void DrawEnemy2(HDC hdc);
	void DrawEnemy2Bullet();
	void DrawHeroBulletExplode();
	void DrawEnemy1BulletExplode();
	//Ex
	void DrawDebug(HDC hdc);
	void DrawScore(HDC hdc);

	//업데이트
	void UpdateAll();		//Loop되면서 업데이트될 기능
	//맵
	void UpdateIntro();
	void UpdateStage1();
	void UpdateFade();
	void UpdateFX();
	//캐릭터
	void UpdateHero();
	void UpdateHeroBullet();
	void MoveHeroBullet();
	void UpdateHeroBulletExplode();
	void UpdateEnemy1BulletExplode();
	void UpdateEnemy1Bullet();
	void MoveEnemy1Bullet();
	void UpdateEnemy1();
	void UpdateEnemy2();


	//Ex
	void AttariCheck();
	void UpdatePress();
	bool UpdateCheck(UPDATE& up, unsigned int tick);


	//Extra
	void GameLoop(HDC hdc);	//게임실행후 반복될 기능
	void SetClient();		//윈도우창 크기설정
	RECT GetClient();		//윈도우창 크기값 가져오기
	bool KeyCheck();
	void MakeResource(HANDLES& dest, HANDLES base, const WCHAR* w);
	void MakeResource(HANDLES& dest, HANDLES base, const WCHAR* w, UPDATE& update, int MaxFrame, int size);		//리소스 자동초기화
	void MakeResource(HANDLES& dest, HANDLES base, const WCHAR* w, UPDATE& update, int MaxFrame, int size, int Xsize, int Ysize);		//리소스 자동초기화
	void FramePlus(UPDATE& update, int tick);
	void xPlus(UPDATE& update, int tick, int n);
	void xPlusAni(UPDATE& update, int tick, int n);
	void PlusBullet(UPDATE& update, int tick, int n);
	void SetDebug();
	bool InitOverLap(int i);
	
	
	//키
	void MoveKey(UPDATE& update, int tick, int n);

	
};

