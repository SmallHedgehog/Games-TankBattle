#include "stdafx.h"
#include "Game.h"


Game::Game(std::vector<std::vector<SDL_Texture*>>& vec, 
	std::vector<SDL_Texture*>& P1Ttexs, std::vector<SDL_Texture*>& P2Ttexs,
	SDL_Texture* bulletTex, std::vector<SDL_Texture*>& blastTexs, 
	std::vector<SDL_Texture*>& tankBlastTexs, 
	std::vector<SDL_Texture*>& barnTexs, 
	std::vector<SDL_Texture*>& barriersTexs): 
P1Tank(nullptr), P2Tank(nullptr), vec(vec), P1Ttexs(P1Ttexs), P2Ttexs(P2Ttexs), bulletTex(bulletTex), 
	blastTexs(blastTexs), tankBlastTexs(tankBlastTexs), barnTexs(barnTexs), 
	barriersTexs(barriersTexs)
{
	// 初始化随机数种子
	srand(unsigned int(time(NULL)));
	
	game_level = 1;
	Player1Score = 0;
	Player2Score = 0;
	IsGameStarted = false;

	// NewGame();
}

// 单人游戏
void Game::NewGame()
{
	P1Tank = new PlayerTank(4 * SQUARE_LENGTH * 2, 12 * SQUARE_LENGTH * 2, PLAYER_TANK, P1Ttexs);
	
	LoadStage(1);
	/*
	NormalTank* normalTank = new NormalTank(0, 0, NORMAL_TANK, vec);
	NormalTank* normalTank1 = new NormalTank(6 * SQUARE_LENGTH * 2, 0, NORMAL_TANK, vec);
	DoubleTank* doubleTank = new DoubleTank(12 * SQUARE_LENGTH * 2, 0, DOUBLE_TANK, vec);
	// 随机化坦克移动方向
	//normalTank->setCurrentDir(TankMoveDir(rand() % 4));
	//doubleTank->setCurrentDir(TankMoveDir(rand() % 4));
	CTanks.push_back(normalTank);
	CTanks.push_back(normalTank1);
	CTanks.push_back(doubleTank);

	// 障碍物
	steelBarriers.push_back(new BarrierClass(6 * SQUARE_LENGTH * 2, 6 * SQUARE_LENGTH * 2, STEEL_BARRIER, barriersTexs[1]));
	normalBarriers.push_back(new BarrierClass(7 * SQUARE_LENGTH * 2, 7 * SQUARE_LENGTH * 2, NORMAL_BARRIER, barriersTexs[0]));
	normalBarriers.push_back(new BarrierClass(7 * SQUARE_LENGTH * 2 + SQUARE_LENGTH, 7 * SQUARE_LENGTH * 2, NORMAL_BARRIER, barriersTexs[0]));
	*/
}

// 双人游戏
void Game::NewGame2()
{
	P1Tank = new PlayerTank(4 * SQUARE_LENGTH * 2, 12 * SQUARE_LENGTH * 2, PLAYER_TANK, P1Ttexs);
	P2Tank = new PlayerTank(8 * SQUARE_LENGTH * 2, 12 * SQUARE_LENGTH * 2, PLAYER_TANK, P2Ttexs);

	LoadStage(1);
}

void Game::InitBarriers()
{
	// 初始化barriers
}

// 获取电脑玩家坦克数量
int Game::getCTanksCount()
{
	return CTanks.size();
}

// 获取游戏等级
int Game::getGameLevel() const
{
	return game_level;
}

// 获取游戏玩家坦克生命
int Game::getP1Life()
{
	if (P1Tank)
		return P1Tank->getLife();
	else
		return 0;
}

int Game::getP2Life()
{
	if (P2Tank)
		return P2Tank->getLife();
	else
		return 0;
}

// 获取游戏玩家分数
int Game::getP1Score() const
{
	if (P1Tank)
		return Player1Score;
	else
		return 0;
}

int Game::getP2Score() const
{
	if (P2Tank)
		return Player2Score;
	else
		return 0;
}

// 读取关卡函数(设置障碍物对象以及电脑玩家坦克对象)
void Game::LoadStage(int level)
{
	char buffer[255] = { 0 };

	// 障碍物资源
	sprintf_s(buffer, "stage/level_barriers%d.txt", level);
	FILE* file = NULL; 
	fopen_s(&file, buffer, "r");
	if (!file){
		std::cout << "Load stage file error!" << std::endl;
	}
	else
	{
		int type = 0, x_pos = 0, y_pos = 0;
		while (!feof(file))
		{
			fscanf_s(file, "%d %d %d\n", &type, &x_pos, &y_pos);
			switch (type)
			{
			case 0:		// normal barrier
				normalBarriers.push_back(new BarrierClass(x_pos, y_pos, NORMAL_BARRIER, barriersTexs[0]));
				break;
			case 1:		// steel barrier
				steelBarriers.push_back(new BarrierClass(x_pos, y_pos, STEEL_BARRIER, barriersTexs[1]));
				break;
			case 2:		// grass barrier
				grassBarriers.push_back(new BarrierClass(x_pos, y_pos, GRASS_BARRIER, barriersTexs[2]));
				break;
			case 3:		// water barrier
				waterBarriers.push_back(new BarrierClass(x_pos, y_pos, WATER_BARRIER, barriersTexs[3]));
				break;
			}
		}
		fclose(file);
	}

	// 坦克资源
	sprintf_s(buffer, "stage/level_tanks%d.txt", level);
	FILE* tank_file = NULL;
	fopen_s(&tank_file, buffer, "r");
	if (!tank_file){
		std::cout << "Load stage tank_file error!" << std::endl;
	}
	else
	{
		int type = 0, x_pos = 0, y_pos = 0;
		while (!feof(tank_file))
		{
			fscanf_s(file, "%d %d %d\n", &type, &x_pos, &y_pos);
			switch (type)
			{
			case 0:		// normal tank
				CTanks.push_back(new NormalTank(x_pos, y_pos, NORMAL_TANK, vec));
				break;
			case 1:		// double tank
				CTanks.push_back(new DoubleTank(x_pos, y_pos, DOUBLE_TANK, vec));
				break;
			case 2:		// two double tank
				CTanks.push_back(new TDoublesTank(x_pos, y_pos, TWO_DOUBLE_TANK, vec));
				break;
			}
		}
		fclose(tank_file);
	}
}

// 处理游戏玩家tank的移动
void Game::HandleInput(TankMoveDir dir)
{
	if (IsGameStarted)
	{
		if (!P1Tank)
			return ;
		Tank* Player1 = dynamic_cast<Tank*>(P1Tank);
		Player1->setCurrentDir(dir);

		// 在游戏区域之内且没有发生碰撞，且不与其它tank发生碰撞
		if (!IsCollisionScreen(Player1, dir) && 
			!IsCollisionTanks(Player1) && !CollisionBarriers_Tanks(Player1))
		{
			Player1->Move(dir);
		}	
	}
}

// 发射子弹
void Game::Launch()
{
	if (IsGameStarted)
	{
		if (!P1Tank)
			return ;
		Tank* Player1 = dynamic_cast<Tank*>(P1Tank);
		// 如果Player1可以发射子弹
		if (Player1->CanLauncher())
		{
			Bullet* bullet = new Bullet(Player1->getX() + SQUARE_LENGTH - BULLET_LENGTH / 2, Player1->getY() + SQUARE_LENGTH - BULLET_LENGTH / 2, 
				Player1->currentDir, bulletTex, Player1);
			PBullets.push_back(bullet);
			// 禁止再发射子弹
			Player1->setIsCanLauncher(false);
		}
	}
}

// 绘制tank
void Game::Draw(SDL_Renderer* renderer)
{
	if (IsGameStarted)
	{
		// 处理电脑玩家坦克移动时的逻辑
		static int RecordTank_isCanMove = 0;
		static int New_TankMoveDir = SQUARE_LENGTH * (rand() % 3 + 4);
	
		// 障碍物
		DrawBarriers(renderer);

		// 玩家1
		if (P1Tank)
		{
			Tank* Player1 = dynamic_cast<Tank*>(P1Tank);
			Player1->Draw(renderer);
		}
		// 玩家2
		if (P2Tank)
		{
			Tank* Player2 = dynamic_cast<Tank*>(P2Tank);
			Player2->Draw(renderer);
		}

		// 电脑玩家tank
		RecordTank_isCanMove++;
		New_TankMoveDir--;
		for (std::list<Tank*>::const_iterator it = CTanks.cbegin(); it != CTanks.cend(); ++it){
			(*it)->Draw(renderer);
			// 随机化发射子弹
			if ((*it)->Launch())
			{
				if ((*it)->CanLauncher())
				{
					Bullet* bullet = new Bullet((*it)->getX() + SQUARE_LENGTH - BULLET_LENGTH / 2, (*it)->getY() + SQUARE_LENGTH - BULLET_LENGTH / 2, 
						(*it)->currentDir, bulletTex, (*it));
					CBullets.push_back(bullet);
					// 禁止再发射子弹
					(*it)->setIsCanLauncher(false);
				}
			}
		}
		if (RecordTank_isCanMove > SQUARE_LENGTH - 2)
		{
			for (std::list<Tank*>::const_iterator it = CTanks.cbegin(); it != CTanks.cend(); ++it)
			{
				//if (RecordTank_isCanMove > SQUARE_LENGTH)
				//{
					// 在游戏区域之内且没有发生碰撞，如果超出一定的时间则重新初始化tank移动方向
					if (!IsCollisionScreen(*it, (*it)->currentDir)
						&& !IsCollisionTanks(*it)
						&& !CollisionBarriers_Tanks(*it))
					{
						(*it)->Move((*it)->currentDir);
						// 超时，重新随机化电脑玩家tank移动方向
						if (New_TankMoveDir <= 0){
							(*it)->setCurrentDir(TankMoveDir(rand() % 4));
						}
					}else{
						// 如果与屏幕发生碰撞，重新随机化tank移动方向
						(*it)->setCurrentDir(TankMoveDir(rand() % 4));
					}
				//}
			}
			RecordTank_isCanMove = 0;
			if (New_TankMoveDir <= 0){
				New_TankMoveDir = SQUARE_LENGTH * (rand() % 3 + 4);
			}
		}

		// 游戏玩家子弹
		Draw(PBullets, renderer, WALL);
		Draw(PBullets, renderer, C_TANK);

		// 电脑玩家子弹
		Draw(CBullets, renderer, WALL);
		Draw(CBullets, renderer, P_TANK);

		// 障碍物
		Draw(PBullets, renderer, BARRIER);

		// 游戏玩家子弹与电脑玩家子弹
		Draw(PBullets, renderer, NOT_ALL);
	}
}

// 绘制障碍物barriers
void Game::DrawBarriers(SDL_Renderer* renderer)
{
	DrawBarriers(renderer, steelBarriers);
	DrawBarriers(renderer, normalBarriers);
	DrawBarriers(renderer, waterBarriers);
	DrawBarriers(renderer, grassBarriers);
}

void Game::DrawBarriers(SDL_Renderer* renderer, std::list<BarrierClass*>& barriers)
{
	for (std::list<BarrierClass*>::const_iterator it = barriers.cbegin(); it != barriers.cend(); ++it)
	{
		if (*it)
			(*it)->Draw(renderer);
	}
}

// 绘制游戏玩家、电脑玩家的子弹以及做相关的碰撞检测
void Game::Draw(std::list<Bullet*>& bullets, SDL_Renderer* renderer, CollisionWithBulletType type)
{
	switch (type)
	{
	case C_TANK:	// 检测游戏玩家子弹是否与电脑玩家坦克发生碰撞
		{
			// 游戏玩家1
			if (P1Tank)
				Handle_PBC(PBullets, renderer, P1Tank);
			// 游戏玩家2
			// do something
		}
		break;
	case P_TANK:	// 检测电脑玩家子弹是否与游戏玩家坦克发生碰撞
		{
			// 处理与游戏玩家1的逻辑
			if (P1Tank)
				Handle_CBP(renderer, P1Tank);
			// 处理游戏玩家2的逻辑
			// do something
		}
		break;
	case WALL:		// 检测子弹是否与屏幕发生碰撞
		{
			for (std::list<Bullet*>::const_iterator it = bullets.cbegin(); it != bullets.cend(); )
			{
				bool result = (*it)->MoveSelf();	// MoveSelf()方法中做了子弹与屏幕的碰撞检测
				if (result){
					// 爆炸效果
					Blast(blastTexs, *it, renderer);
					delete (*it);
					it = bullets.erase(it);
					continue;
				}
				else{
					(*it)->Draw(renderer);
					++it;
				}
			}
		}
		break;
	case BARRIER:	// 检测子弹与障碍物之间发生的碰撞
		{
			if (P1Tank)
				Handle_CB(PBullets, PLAYER_TANK, renderer);
			if (P2Tank)
				Handle_CB(P2Bullets, PLAYER_TANK, renderer);
			Handle_CB(CBullets, COMPUTER_TANK, renderer);
		}
		break;
	case NOT_ALL:	// 处理游戏玩家子弹与电脑玩家子弹的碰撞
		{
			if (P1Tank)
				Handle_CPB(PBullets, CBullets, renderer);
			if (P2Tank)
				Handle_CPB(P2Bullets, CBullets, renderer);
		}
		break;
	default:
		break;
	}
}

// 处理游戏玩家子弹与电脑坦克碰撞的逻辑
void Game::Handle_PBC(std::list<Bullet*>& bullets, SDL_Renderer* renderer, Tank* Ptank)
{
	for (std::list<Bullet*>::const_iterator item = bullets.cbegin(); item != bullets.cend(); )
	{
		bool sign = false;
		for (std::list<Tank*>::const_iterator it = CTanks.cbegin(); it != CTanks.cend(); )
		{
			if (item == PBullets.cend())
				break;
			// 子弹碰撞到坦克
			if (IsCollisionBullet(*item, *it))
			{
				sign = true;
				// 子弹爆炸效果
				Blast(blastTexs, *item, renderer);
				delete (*item);
				item = PBullets.erase(item);
				// 设置玩家1可以重新发射子弹
				Ptank->setIsCanLauncher(true);
				// 坦克爆炸效果
				Blast(tankBlastTexs, *it, renderer);
				delete (*it);
				it = CTanks.erase(it);
				break;
			}else{
				++it;
			}
		}
		if (!sign){
			(*item)->Draw(renderer);
			++item;
		}
	}
}

// 处理电脑玩家子弹与游戏玩家坦克碰撞的逻辑
void Game::Handle_CBP(SDL_Renderer* renderer, Tank* Ptank)
{
	for (std::list<Bullet*>::const_iterator it = CBullets.cbegin(); it != CBullets.cend(); )
	{
		if (IsCollisionBullet(*it, Ptank))
		{
			std::cout << "Player tank is hitted" << std::endl;
			// 子弹爆炸效果
			Blast(blastTexs, *it, renderer);
			// 重新设置电脑玩家坦克可以发射子弹
			(*it)->getTank()->setIsCanLauncher(true);
			delete (*it);
			it = CBullets.erase(it);
		}else{
			(*it)->Draw(renderer);
			++it;
		}
	}
}

// 处理游戏玩家子弹和与电脑玩家子弹碰撞的逻辑
void Game::Handle_CPB(std::list<Bullet*>& PBullets, std::list<Bullet*>& CBullets, SDL_Renderer* renderer)
{
	for (std::list<Bullet*>::const_iterator it = CBullets.cbegin(); it != CBullets.cend(); )
	{
		bool sign = false;
		for (std::list<Bullet*>::const_iterator item = PBullets.cbegin(); item != PBullets.cend(); )
		{
			// 如果发生碰撞，清除玩家子弹和电脑玩家子弹
			if (IsCollisionCPB(*it, *item))
			{
				sign = true;
				// 清除item
				(*item)->getTank()->setIsCanLauncher(true);
				delete (*item);
				item = PBullets.erase(item);
				break;
			}
			else{
				(*item)->Draw(renderer);
				++item;
			}
		}
		if (sign){
			// 清除it
			(*it)->getTank()->setIsCanLauncher(true);
			delete (*it);
			it = CBullets.erase(it);
			break;
		}
		else{
			(*it)->Draw(renderer);
			++it;
		}
	}
}

// 处理子弹与障碍物barriers碰撞的逻辑
void Game::Handle_CB(std::list<Bullet*>& bullets, TankType type, SDL_Renderer* renderer)
{
	for (std::list<Bullet*>::const_iterator it = bullets.cbegin(); it != bullets.cend(); )
	{
		bool sign = false;
		// normalBarriers
		for (std::list<BarrierClass*>::const_iterator item = normalBarriers.cbegin(); item != normalBarriers.cend(); )
		{
			// 如果子弹与barrier发生碰撞
			if (CollisionBarrier(*item, *it))
			{
				sign = true;
				// 清除item
				delete (*item);
				item = normalBarriers.erase(item);
				// 再比较一次
				for (std::list<BarrierClass*>::const_iterator item2 = normalBarriers.cbegin(); item2 != normalBarriers.cend(); )
				{
					// 再次检测是否发生碰撞
					if (CollisionBarrier(*item2, *it))
					{
						// 清除item2
						delete (*item2);
						item2 = normalBarriers.erase(item2);
						break;
					}
					else{
						++item2;
					}
				}
				// 清除子弹bullet
				Blast(blastTexs, *it, renderer);
				(*it)->getTank()->setIsCanLauncher(true);
				delete (*it);
				it = bullets.erase(it);
				break;
			}
			else{
				++item;
			}
		}
		if (!sign){
			(*it)->Draw(renderer);
			++it;
		}
	}

	// steel barriers
	for (std::list<Bullet*>::const_iterator it = bullets.cbegin(); it != bullets.cend(); )
	{
		bool sign = false;
		for (std::list<BarrierClass*>::const_iterator item = steelBarriers.cbegin(); item != steelBarriers.cend(); )
		{
			// 如果子弹与barrier发生碰撞，根据TankType来处理与steelBarriers发生的逻辑
			if (CollisionBarrier(*item, *it))
			{
				sign = true;
				switch (type)
				{
				case PLAYER_TANK:		// 如果是游戏玩家坦克击中steel barriers
					{
						Blast(blastTexs, *it, renderer);
						(*it)->getTank()->setIsCanLauncher(true);
						delete (*it);
						it = bullets.erase(it);
					}
					break;
				case COMPUTER_TANK:		// 如果是电脑玩家坦克击中steel barriers
					{
						Blast(blastTexs, *it, renderer);
						(*it)->getTank()->setIsCanLauncher(true);
						delete (*it);
						it = bullets.erase(it);
					}
					break;
				}
				break;
			}
			else{
				++item;
			}
		}
		if (!sign){
			(*it)->Draw(renderer);
			++it;
		}
	}
}

// 处理子弹爆炸效果
void Game::Blast(std::vector<SDL_Texture*>& texs, Bullet* bullet, SDL_Renderer* renderer)
{
	for (std::vector<SDL_Texture*>::const_iterator it = texs.cbegin(); it != texs.cend(); ++it)
	{
		int width = 0, height = 0;
		SDL_QueryTexture(*it, NULL, NULL, &width, &height);
		SDL_Rect rect = {
			bullet->getX() - width / 2, bullet->getY() - height / 2, width, height
		};

		SDL_RenderCopy(renderer, *it, NULL, &rect);
	}
}

// 处理坦克爆炸效果
void Game::Blast(std::vector<SDL_Texture*>& texs, Tank* tank, SDL_Renderer* renderer)
{
	for (std::vector<SDL_Texture*>::const_iterator it = texs.cbegin(); it != texs.cend(); ++it)
	{
		int width = 0, height = 0;
		SDL_QueryTexture(*it, NULL, NULL, &width, &height);
		SDL_Rect rect = {
			tank->getX() - width / 2 + SQUARE_LENGTH, tank->getY() - height / 2 + SQUARE_LENGTH, width, height
		};

		SDL_RenderCopy(renderer, *it, NULL, &rect);
	}
}

// 检测电脑玩家子弹与游戏玩家子弹的碰撞
bool Game::IsCollisionCPB(Bullet* C_bullet, Bullet* P_bullet)
{
	/* 对C_bullet进行操作 */
	// 获取子弹每移动一次的距离
	int Distance = C_bullet->getSpeed();
	// 获取子弹左上角坐标
	int x = C_bullet->getX();
	int y = C_bullet->getY();
	// 获取子弹的移动方向
	TankMoveDir dir = C_bullet->getDir();

	switch (dir)
	{
	case LEFT:
		x -= Distance;
		break;
	case UP:
		y -= Distance;
		break;
	case RIGHT:
		x += Distance;
		break;
	case DOWN:
		y += Distance;
		break;
	case NONE:
		break;
	default:
		break;
	}

	// 获取P_bullet的左上角坐标
	int x2 = P_bullet->getX();
	int y2 = P_bullet->getY();

	if ((abs(x2 - x) < BULLET_LENGTH) &&
		(abs(y2 - y) < BULLET_LENGTH))
	{
		return true;
	}
	return false;
}

// 检测障碍物与子弹之间的碰撞
bool Game::CollisionBarrier(BarrierClass* barriers, Bullet* bullet)
{
	// 获取子弹每移动一次的距离
	int Distance = bullet->getSpeed();
	// 获取子弹左上角坐标
	int x = bullet->getX();
	int y = bullet->getY();
	// 获取子弹移动方向
	TankMoveDir dir = bullet->getDir();

	switch (dir)
	{
	case LEFT:
		x -= Distance;
		break;
	case UP:
		y -= Distance;
		break;
	case RIGHT:
		x += Distance;
		break;
	case DOWN:
		y += Distance;
		break;
	case NONE:
		break;
	default:
		break;
	}

	// 计算子弹中心坐标
	int bullet_centerX = x + BULLET_LENGTH / 2;
	int bullet_centerY = y + BULLET_LENGTH / 2;

	// 计算障碍物中心坐标
	int BarrierLength = barriers->GetBarrierLength();
	int barrier_centerX = barriers->getX() + BarrierLength / 2;
	int barrier_centerY = barriers->getY() + BarrierLength / 2;

	if ((abs(barrier_centerX - bullet_centerX) < (BULLET_LENGTH / 2 + BarrierLength / 2)) && 
		(abs(barrier_centerY - bullet_centerY) < (BULLET_LENGTH / 2 + BarrierLength / 2)))
	{
		return true;
	}
	return false;
}

// 检测障碍物和坦克之间的碰撞
bool Game::CollisionBarrier(BarrierClass* barriers, Tank* tank)
{
	// 获取坦克每移动一次的距离
	int Distance = tank->getDistance();
	// 获取坦克左上角的坐标
	int x = tank->getX();
	int y = tank->getY();
	// 获取tank的移动方向
	TankMoveDir dir = tank->currentDir;

	switch (dir)
	{
	case LEFT:
		x -= Distance;
		break;
	case UP:
		y -= Distance;
		break;
	case RIGHT:
		x += Distance;
		break;
	case DOWN:
		y += Distance;
		break;
	case NONE:
		break;
	default:
		break;
	}

	// 计算barriers的中心坐标
	int BarrierLength = barriers->GetBarrierLength();
	int barrier_centerX = barriers->getX() + BarrierLength / 2;
	int barrier_centerY = barriers->getY() + BarrierLength / 2;

	// 计算tank的中心坐标
	int tank_centerX = x + SQUARE_LENGTH;
	int tank_centerY = y + SQUARE_LENGTH;

	if ((abs(tank_centerX - barrier_centerX) < (BarrierLength / 2 + SQUARE_LENGTH)) &&
		(abs(tank_centerY - barrier_centerY) < (BarrierLength / 2 + SQUARE_LENGTH)))
	{
		return true;
	}
	return false;
}

// 检测子弹和坦克间的碰撞
bool Game::IsCollisionBullet(Bullet* bullet, Tank* tank)
{
	// 获取子弹每移动一次的距离
	int Distance = bullet->getSpeed();
	// 获取子弹左上角的坐标
	int x = bullet->getX();
	int y = bullet->getY();
	// 获取子弹移动的方向
	TankMoveDir dir = bullet->getDir();

	switch (dir)
	{
	case LEFT:
		x -= Distance;
		break;
	case UP:
		y -= Distance;
		break;
	case RIGHT:
		x += Distance;
		break;
	case DOWN:
		y += Distance;
		break;
	case NONE:
		break;
	default:
		break;
	}

	// 计算子弹的中心坐标
	int bullet_centerX = x + BULLET_LENGTH / 2;
	int bullet_centerY = y + BULLET_LENGTH / 2;

	// 计算tank的中心坐标
	int tank_centerX = tank->getX() + SQUARE_LENGTH;
	int tank_centerY = tank->getY() + SQUARE_LENGTH;

	if ((abs(tank_centerX - bullet_centerX) < (BULLET_LENGTH / 2 + SQUARE_LENGTH)) &&
		(abs(tank_centerY - bullet_centerY) < (BULLET_LENGTH / 2 + SQUARE_LENGTH)))
	{
		return true;
	}
	return false;
}

// 检测电脑玩家tank与barriers的碰撞
bool Game::CollisionBarriers_Tanks(Tank* tank)
{
	// steel barrier
	for (std::list<BarrierClass*>::const_iterator it = steelBarriers.cbegin(); it != steelBarriers.cend(); ++it)
	{
		if (CollisionBarrier(*it, tank))
			return true;
	}

	// normal barrier
	for (std::list<BarrierClass*>::const_iterator it = normalBarriers.cbegin(); it != normalBarriers.cend(); ++it)
	{
		if (CollisionBarrier(*it, tank))
			return true;
	}

	// water barrier
	for (std::list<BarrierClass*>::const_iterator it = waterBarriers.cbegin(); it != waterBarriers.cend(); ++it)
	{
		if (CollisionBarrier(*it, tank))
			return true;
	}

	return false;
}

// 碰撞检测(屏幕)
bool Game::IsCollisionScreen(Tank* tank, TankMoveDir dir)
{
	// 每移动一次的距离
	int Distance = SQUARE_LENGTH;
	// tank的左上角坐标
	int x = tank->getX();
	int y = tank->getY();
	
	bool result = false;
	switch (dir)
	{
	case LEFT:
		{
			if ((x - Distance) < GAME_LEFT_AREA)
				result = true;
			else
				result = false;
		}
		break;
	case UP:
		{
			if ((y - Distance) < GAME_TOP_AREA)
				result = true;
			else
				result = false;
		}
		break;
	case RIGHT:
		{
			if ((x + SQUARE_LENGTH * 2 + Distance) > GAME_RIGHT_AREA)
				result = true;
			else
				result = false;
		}
		break;
	case DOWN:
		{
			if ((y + SQUARE_LENGTH * 2 + Distance) > GAME_BOTTOM_AREA)
				result = true;
			else
				result = false;
		}
		break;
	case NONE:
		break;
	default:
		break;
	}

	return result;
}

void Game::GetCoordinateAfterMove(int* x, int* y, Tank* tank)
{
	// 获取tank的左上角坐标
	int tank_x = tank->getX();
	int tank_y = tank->getY();

	// 获取tank每移动一次的距离
	int Distance = tank->getDistance();

	switch (tank->currentDir)
	{
	case LEFT:
		tank_x -= Distance;
		break;
	case UP:
		tank_y -= Distance;
		break;
	case RIGHT:
		tank_x += Distance;
		break;
	case DOWN:
		tank_y += Distance;
		break;
	case NONE:
		break;
	default:
		break;
	}

	(*x) = tank_x;
	(*y) = tank_y;
}

// 碰撞检测(tank之间)
bool Game::IsCollisionTank(Tank* tank1, Tank* tank2)
{
	// 获取tank1、tank2移动后的左上角坐标
	int tank1_x = 0, tank1_y = 0;
	int tank2_x = 0, tank2_y = 0;
	GetCoordinateAfterMove(&tank1_x, &tank1_y, tank1);
	//GetCoordinateAfterMove(&tank2_x, &tank2_y, tank2);
	tank2_x = tank2->getX();
	tank2_y = tank2->getY();

	if ((abs(tank2_x - tank1_x) < (SQUARE_LENGTH * 2)) &&
		(abs(tank2_y - tank1_y) < (SQUARE_LENGTH * 2)))
	{
		return true;
	}
	return false;
}

bool Game::IsCollisionTanks(Tank* tank)
{
	for (std::list<Tank*>::const_iterator it = CTanks.cbegin(); it != CTanks.cend(); ++it)
	{
		if (tank == (*it)){
			continue;
		}
		else{
			if (IsCollisionTank(tank, *it)){
				return true;
			}
			if (P1Tank && tank != P1Tank){
				if (IsCollisionTank(tank, P1Tank))
					return true;
			}
			if (P2Tank && tank != P2Tank){
				if (IsCollisionTank(tank, P2Tank))
					return true;
			}
		}
	}
	return false;
}

// 清除每一关电脑坦克资源和障碍物资源
void Game::Clear()
{
	// 释放障碍物资源
	Clear(steelBarriers);
	Clear(normalBarriers);
	Clear(grassBarriers);
	Clear(waterBarriers);

	// 清除电脑玩家坦克资源
	for (std::list<Tank*>::const_iterator it = CTanks.cbegin(); it != CTanks.cend(); ++it)
	{
		if (*it)
			delete (*it);
	}
	CTanks.clear();
}

void Game::Clear(std::list<BarrierClass*>& barriers)
{
	// 释放障碍物资源
	for (std::list<BarrierClass*>::const_iterator item = barriers.cbegin(); item != barriers.cend(); ++item)
	{
		if (*item)
			delete (*item);
	}
	barriers.clear();
}

void Game::Clear(std::list<Bullet*>& bullets)
{
	// 释放子弹资源
	for (std::list<Bullet*>::const_iterator it = bullets.cbegin(); it != bullets.cend(); ++it)
	{
		if (*it)
			delete (*it);
	}
	bullets.clear();
}

Game::~Game(void)
{
	// 释放电脑玩家资源
	for (std::list<Tank*>::const_iterator it = CTanks.cbegin(); it != CTanks.cend(); ++it)
	{
		if (*it)
			delete (*it);
	}
	CTanks.clear();
	// 释放游戏玩家资源
	if (P1Tank)
		delete P1Tank;
	if (P2Tank)
		delete P2Tank;

	// 释放障碍物资源
	Clear(steelBarriers);
	Clear(normalBarriers);
	Clear(grassBarriers);
	Clear(waterBarriers);

	// 清除子弹
	Clear(PBullets);
	Clear(P2Bullets);
	Clear(CBullets);
}
