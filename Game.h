#pragma once

// 管理游戏对象、碰撞检测等逻辑

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
	void NewGame();					// 重新设置游戏中的对象等
	void NewGame2();				// 双人游戏
	void InitBarriers();			// 初始化游戏对象资源
	void LoadStage(int level);		// 读取关卡函数(设置障碍物对象以及电脑玩家坦克对象)
	int getCTanksCount();			// 获取电脑玩家坦克数量
	int getGameLevel() const;		// 获取游戏等级
	int getP1Score() const;			// 获取游戏玩家分数
	int getP2Score() const;
	int getP1Life();				// 获取游戏玩家坦克生命
	int getP2Life();

public:
	void Draw(SDL_Renderer* renderer);
	// 处理游戏玩家tank的移动以及是否发射子弹
	void HandleInput(TankMoveDir dir);
	// 发射子弹
	void Launch();

private:
	void Draw(std::list<Bullet*>& bullets, SDL_Renderer* renderer, CollisionWithBulletType type);
	void DrawBarriers(SDL_Renderer* renderer);
	void DrawBarriers(SDL_Renderer* renderer, std::list<BarrierClass*>& barriers);

private:
	bool IsCollisionScreen(Tank* tank, TankMoveDir dir);			// 碰撞检测(屏幕)
	bool IsCollisionTank(Tank* tank1, Tank* tank2);					// 碰撞检测(tank之间)
	bool IsCollisionTanks(Tank* tank);
	bool IsCollisionBullet(Bullet* bullet, Tank* tank);				// 检测子弹是否与坦克发生碰撞
	bool CollisionBarrier(BarrierClass* barriers, Tank* tank);		// 检测坦克是否与障碍物发生碰撞
	bool CollisionBarriers_Tanks(Tank* tank);
	bool CollisionBarrier(BarrierClass* barriers, Bullet* bullet);	// 检测子弹与障碍物的碰撞
	bool IsCollisionCPB(Bullet* C_bullet, Bullet* P_bullet);		// 检测游戏玩家子弹与电脑玩家子弹的碰撞

	void GetCoordinateAfterMove(int* x, int* y, Tank* tank);		// 获取tank移动动后的坐标

	void Handle_PBC(std::list<Bullet*>& bullets, SDL_Renderer* renderer, Tank* Ptank);		// 处理游戏玩家子弹与电脑坦克碰撞的逻辑
	void Handle_CBP(SDL_Renderer* renderer, Tank* Ptank);									// 处理电脑玩家子弹与游戏玩家坦克碰撞的逻辑
	void Handle_CB(std::list<Bullet*>& bullets, TankType type, SDL_Renderer* renderer);		// 处理子弹与障碍物barriers碰撞的逻辑
	void Handle_CPB(std::list<Bullet*>& PBullets, std::list<Bullet*>& CBullets, SDL_Renderer* renderer);

	// 处理子弹、坦克的爆炸效果
	void Blast(std::vector<SDL_Texture*>& texs, Bullet* bullet, SDL_Renderer* renderer);
	void Blast(std::vector<SDL_Texture*>& texs, Tank* tank, SDL_Renderer* renderer);

private:
	std::list<Tank*> CTanks;		// 电脑玩家tank
	PlayerTank* P1Tank;				// 游戏玩家1tank
	PlayerTank* P2Tank;				// 游戏玩家2tank
	// 障碍物
	std::list<BarrierClass*> steelBarriers;
	std::list<BarrierClass*> normalBarriers;
	std::list<BarrierClass*> waterBarriers;
	std::list<BarrierClass*> grassBarriers;

	// 纹理数据
	std::vector<std::vector<SDL_Texture*>> vec;		// 电脑玩家tank纹理
	std::vector<SDL_Texture*> P1Ttexs;				// 游戏玩家1tank纹理
	std::vector<SDL_Texture*> P2Ttexs;
	SDL_Texture* bulletTex;							// 子弹纹理数据
	std::vector<SDL_Texture*> blastTexs;			// 爆炸效果纹理数据
	std::vector<SDL_Texture*> tankBlastTexs;
	std::vector<SDL_Texture*> barnTexs;				// barn纹理数据
	std::vector<SDL_Texture*> barriersTexs;			// 障碍物纹理数据

	// 存储子弹(Bullet)对象
	std::list<Bullet*> PBullets;					// 游戏玩家发射的子弹
	std::list<Bullet*> P2Bullets;	
	std::list<Bullet*> CBullets;					// 电脑玩家发射的子弹

	int game_level;		// 游戏等级
	int Player1Score;	// 游戏玩家1分数
	int Player2Score;	// 游戏玩家2分数

public:
	bool IsGameStarted;	// 游戏是否开始
};

