#pragma once
class Game
{
private:
	RECT m_rtClient;		//������âũ��
	int m_HeroState;		//����� ����
	int m_EnemyState;		//�� ����
	int m_StageNum;			//���������ѹ�
	bool m_bDebug;			//�������
	int m_LastKey;			//���������� ������ Ű
	int m_nScore;
	int m_EnemyBulletX[3];
	int m_nHeroHit;			//���Ѿ˿� �¾�����
	int m_nHeroHealth;		//����� ���
	POINT m_ptEnemy1Explod;
	int m_Scene;			//��� ������

	// UPDATE
	//��
	UPDATE m_uScore;		//����
	UPDATE m_uIntro;		//��Ʈ��
	UPDATE m_uStage1[4];		//��������1
	UPDATE m_uStage2;		//��������2
	UPDATE m_uClear;		//Ŭ����
	UPDATE m_uGameOver;		//���ӿ���
	UPDATE m_uFade;
	UPDATE m_uFX;			//����ȭ�� ȿ��
	//ĳ����
	UPDATE m_uHero[12];
	UPDATE m_uHeroBullet[HEROBULLETNUM];
	UPDATE m_uEnemy1[3];
	UPDATE m_uEnemy1Bullet[ENEMYBULLETNUM];
	UPDATE m_uEnemy2[3];
	UPDATE m_uEnemy2Bullet[3];
	UPDATE m_uHeroBulletExplode;
	UPDATE m_uEnemy1BulletExplode[2];			//  �ٴڿ� �������� ����ο� ������
	UPDATE m_uEnemy2BulletExplode;			
	//Ex
	UPDATE m_uPress;

	//HANDLES
	//��
	HANDLES m_Score;		//����
	HANDLES m_Intro;		//��Ʈ��
	HANDLES m_Stage1[4];		//��������1
	HANDLES m_Stage2;		//��������2
	HANDLES m_Clear;		//Ŭ����
	HANDLES m_Gameover;		//���ӿ���
	HANDLES m_Alpha[3];
	HANDLES m_Fade;			
	HANDLES m_FX;			
	//ĳ����
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
	HANDLES m_Base;			//�⺻���� ������ ���۸� �߰��ؼ� ���߹��۷� �׸�����
	


	DEBUG m_Debug;
public:
	//������ �Ҹ���
	Game();
	~Game();
	
	//Init
	void InitAll();			//����ʱ�ȭ
	void InitResource(HDC hdc);	//ȭ����¿� �ʿ��� �ڷ� �ʱ�ȭ
	void InitBG(UPDATE& update);
	void ReleaseResource();		//�Ҹ���
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

	//�׸���
	void DrawAll(HDC hdc);			//�׸���
	//��
	void DrawIntro();
	void DrawBG();		//��������1
	void DrawBG2();		//��������1
	void DrawBG3();		//��������1
	void DrawClear();		//Ŭ����
	void DrawGameover();		//���ӿ���
	void DrawFade();
	void DrawFX();		//��Ʈ��ȭ�� ����Ʈ
	void DrawAlpha();
	//ĳ����
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

	//������Ʈ
	void UpdateAll();		//Loop�Ǹ鼭 ������Ʈ�� ���
	//��
	void UpdateIntro();
	void UpdateStage1();
	void UpdateFade();
	void UpdateFX();
	//ĳ����
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
	void GameLoop(HDC hdc);	//���ӽ����� �ݺ��� ���
	void SetClient();		//������â ũ�⼳��
	RECT GetClient();		//������â ũ�Ⱚ ��������
	bool KeyCheck();
	void MakeResource(HANDLES& dest, HANDLES base, const WCHAR* w);
	void MakeResource(HANDLES& dest, HANDLES base, const WCHAR* w, UPDATE& update, int MaxFrame, int size);		//���ҽ� �ڵ��ʱ�ȭ
	void MakeResource(HANDLES& dest, HANDLES base, const WCHAR* w, UPDATE& update, int MaxFrame, int size, int Xsize, int Ysize);		//���ҽ� �ڵ��ʱ�ȭ
	void FramePlus(UPDATE& update, int tick);
	void xPlus(UPDATE& update, int tick, int n);
	void xPlusAni(UPDATE& update, int tick, int n);
	void PlusBullet(UPDATE& update, int tick, int n);
	void SetDebug();
	bool InitOverLap(int i);
	
	
	//Ű
	void MoveKey(UPDATE& update, int tick, int n);

	
};

