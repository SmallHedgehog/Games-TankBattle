#pragma once

// ������Ϸ������ײ�����߼�

#include "BarrierClass.h"
#include "NormalTank.h"
#include "DoubleTank.h"
#include "TDoublesTank.h"
#include "PlayerTank.h"
#include "Bullet.h"
#include <list>
#include <iostream>
#include <time.h>

class Game
{
public:
	Game(std::vector<std::vector<SDL_Texture*>>& vec, 
		std::vector<SDL_Texture*>& P1Ttexs, std::vector<SDL_Texture*>&P2Ttexs,
		SDL_Texture* bulletTex, std::vector<SDL_Texture*>& blastTexs, 
		std::vector<SDL_Texture*>& tankBlastTexs, 
		std::vector<SDL_Texture*>& barnTexs, 
		std::vector<SDL_Texture*>& barriersTexs);
	void Clear();
	~Game(void);

// clear
private:
	void Clear(std::list<BarrierClass*>& barriers);
	void Clear(std::list<Bullet*>& bullets);

public:
	//void Reset();
	void NewGame();					// ����������Ϸ�еĶ����
	void NewGame2();				// ˫����Ϸ
	void InitBarriers();			// ��ʼ����Ϸ������Դ
	void LoadStage(int level);		// ��ȡ�ؿ�����(�����ϰ�������Լ��������̹�˶���)
	int getCTanksCount();			// ��ȡ�������̹������
	int getGameLevel() const;		// ��ȡ��Ϸ�ȼ�
	int getP1Score() const;			// ��ȡ��Ϸ��ҷ���
	int getP2Score() const;
	int getP1Life();				// ��ȡ��Ϸ���̹������
	int getP2Life();

public:
	void Draw(SDL_Renderer* renderer);
	// ������Ϸ���tank���ƶ��Լ��Ƿ����ӵ�
	void HandleInput(TankMoveDir dir);
	// �����ӵ�
	void Launch();

private:
	void Draw(std::list<Bullet*>& bullets, SDL_Renderer* renderer, CollisionWithBulletType type);
	void DrawBarriers(SDL_Renderer* renderer);
	void DrawBarriers(SDL_Renderer* renderer, std::list<BarrierClass*>& barriers);

private:
	bool IsCollisionScreen(Tank* tank, TankMoveDir dir);			// ��ײ���(��Ļ)
	bool IsCollisionTank(Tank* tank1, Tank* tank2);					// ��ײ���(tank֮��)
	bool IsCollisionTanks(Tank* tank);
	bool IsCollisionBullet(Bullet* bullet, Tank* tank);				// ����ӵ��Ƿ���̹�˷�����ײ
	bool CollisionBarrier(BarrierClass* barriers, Tank* tank);		// ���̹���Ƿ����ϰ��﷢����ײ
	bool CollisionBarriers_Tanks(Tank* tank);
	bool CollisionBarrier(BarrierClass* barriers, Bullet* bullet);	// ����ӵ����ϰ������ײ
	bool IsCollisionCPB(Bullet* C_bullet, Bullet* P_bullet);		// �����Ϸ����ӵ����������ӵ�����ײ

	void GetCoordinateAfterMove(int* x, int* y, Tank* tank);		// ��ȡtank�ƶ����������

	void Handle_PBC(std::list<Bullet*>& bullets, SDL_Renderer* renderer, Tank* Ptank);		// ������Ϸ����ӵ������̹����ײ���߼�
	void Handle_CBP(SDL_Renderer* renderer, Tank* Ptank);									// �����������ӵ�����Ϸ���̹����ײ���߼�
	void Handle_CB(std::list<Bullet*>& bullets, TankType type, SDL_Renderer* renderer);		// �����ӵ����ϰ���barriers��ײ���߼�
	void Handle_CPB(std::list<Bullet*>& PBullets, std::list<Bullet*>& CBullets, SDL_Renderer* renderer);

	// �����ӵ���̹�˵ı�ըЧ��
	void Blast(std::vector<SDL_Texture*>& texs, Bullet* bullet, SDL_Renderer* renderer);
	void Blast(std::vector<SDL_Texture*>& texs, Tank* tank, SDL_Renderer* renderer);

private:
	std::list<Tank*> CTanks;		// �������tank
	PlayerTank* P1Tank;				// ��Ϸ���1tank
	PlayerTank* P2Tank;				// ��Ϸ���2tank
	// �ϰ���
	std::list<BarrierClass*> steelBarriers;
	std::list<BarrierClass*> normalBarriers;
	std::list<BarrierClass*> waterBarriers;
	std::list<BarrierClass*> grassBarriers;

	// ��������
	std::vector<std::vector<SDL_Texture*>> vec;		// �������tank����
	std::vector<SDL_Texture*> P1Ttexs;				// ��Ϸ���1tank����
	std::vector<SDL_Texture*> P2Ttexs;
	SDL_Texture* bulletTex;							// �ӵ���������
	std::vector<SDL_Texture*> blastTexs;			// ��ըЧ����������
	std::vector<SDL_Texture*> tankBlastTexs;
	std::vector<SDL_Texture*> barnTexs;				// barn��������
	std::vector<SDL_Texture*> barriersTexs;			// �ϰ�����������

	// �洢�ӵ�(Bullet)����
	std::list<Bullet*> PBullets;					// ��Ϸ��ҷ�����ӵ�
	std::list<Bullet*> P2Bullets;	
	std::list<Bullet*> CBullets;					// ������ҷ�����ӵ�

	int game_level;		// ��Ϸ�ȼ�
	int Player1Score;	// ��Ϸ���1����
	int Player2Score;	// ��Ϸ���2����

public:
	bool IsGameStarted;	// ��Ϸ�Ƿ�ʼ
};

