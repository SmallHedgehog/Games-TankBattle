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
	// ��ʼ�����������
	srand(unsigned int(time(NULL)));
	
	game_level = 1;
	Player1Score = 0;
	Player2Score = 0;
	IsGameStarted = false;

	// NewGame();
}

// ������Ϸ
void Game::NewGame()
{
	P1Tank = new PlayerTank(4 * SQUARE_LENGTH * 2, 12 * SQUARE_LENGTH * 2, PLAYER_TANK, P1Ttexs);
	
	LoadStage(1);
	/*
	NormalTank* normalTank = new NormalTank(0, 0, NORMAL_TANK, vec);
	NormalTank* normalTank1 = new NormalTank(6 * SQUARE_LENGTH * 2, 0, NORMAL_TANK, vec);
	DoubleTank* doubleTank = new DoubleTank(12 * SQUARE_LENGTH * 2, 0, DOUBLE_TANK, vec);
	// �����̹���ƶ�����
	//normalTank->setCurrentDir(TankMoveDir(rand() % 4));
	//doubleTank->setCurrentDir(TankMoveDir(rand() % 4));
	CTanks.push_back(normalTank);
	CTanks.push_back(normalTank1);
	CTanks.push_back(doubleTank);

	// �ϰ���
	steelBarriers.push_back(new BarrierClass(6 * SQUARE_LENGTH * 2, 6 * SQUARE_LENGTH * 2, STEEL_BARRIER, barriersTexs[1]));
	normalBarriers.push_back(new BarrierClass(7 * SQUARE_LENGTH * 2, 7 * SQUARE_LENGTH * 2, NORMAL_BARRIER, barriersTexs[0]));
	normalBarriers.push_back(new BarrierClass(7 * SQUARE_LENGTH * 2 + SQUARE_LENGTH, 7 * SQUARE_LENGTH * 2, NORMAL_BARRIER, barriersTexs[0]));
	*/
}

// ˫����Ϸ
void Game::NewGame2()
{
	P1Tank = new PlayerTank(4 * SQUARE_LENGTH * 2, 12 * SQUARE_LENGTH * 2, PLAYER_TANK, P1Ttexs);
	P2Tank = new PlayerTank(8 * SQUARE_LENGTH * 2, 12 * SQUARE_LENGTH * 2, PLAYER_TANK, P2Ttexs);

	LoadStage(1);
}

void Game::InitBarriers()
{
	// ��ʼ��barriers
}

// ��ȡ�������̹������
int Game::getCTanksCount()
{
	return CTanks.size();
}

// ��ȡ��Ϸ�ȼ�
int Game::getGameLevel() const
{
	return game_level;
}

// ��ȡ��Ϸ���̹������
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

// ��ȡ��Ϸ��ҷ���
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

// ��ȡ�ؿ�����(�����ϰ�������Լ��������̹�˶���)
void Game::LoadStage(int level)
{
	char buffer[255] = { 0 };

	// �ϰ�����Դ
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

	// ̹����Դ
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

// ������Ϸ���tank���ƶ�
void Game::HandleInput(TankMoveDir dir)
{
	if (IsGameStarted)
	{
		if (!P1Tank)
			return ;
		Tank* Player1 = dynamic_cast<Tank*>(P1Tank);
		Player1->setCurrentDir(dir);

		// ����Ϸ����֮����û�з�����ײ���Ҳ�������tank������ײ
		if (!IsCollisionScreen(Player1, dir) && 
			!IsCollisionTanks(Player1) && !CollisionBarriers_Tanks(Player1))
		{
			Player1->Move(dir);
		}	
	}
}

// �����ӵ�
void Game::Launch()
{
	if (IsGameStarted)
	{
		if (!P1Tank)
			return ;
		Tank* Player1 = dynamic_cast<Tank*>(P1Tank);
		// ���Player1���Է����ӵ�
		if (Player1->CanLauncher())
		{
			Bullet* bullet = new Bullet(Player1->getX() + SQUARE_LENGTH - BULLET_LENGTH / 2, Player1->getY() + SQUARE_LENGTH - BULLET_LENGTH / 2, 
				Player1->currentDir, bulletTex, Player1);
			PBullets.push_back(bullet);
			// ��ֹ�ٷ����ӵ�
			Player1->setIsCanLauncher(false);
		}
	}
}

// ����tank
void Game::Draw(SDL_Renderer* renderer)
{
	if (IsGameStarted)
	{
		// ����������̹���ƶ�ʱ���߼�
		static int RecordTank_isCanMove = 0;
		static int New_TankMoveDir = SQUARE_LENGTH * (rand() % 3 + 4);
	
		// �ϰ���
		DrawBarriers(renderer);

		// ���1
		if (P1Tank)
		{
			Tank* Player1 = dynamic_cast<Tank*>(P1Tank);
			Player1->Draw(renderer);
		}
		// ���2
		if (P2Tank)
		{
			Tank* Player2 = dynamic_cast<Tank*>(P2Tank);
			Player2->Draw(renderer);
		}

		// �������tank
		RecordTank_isCanMove++;
		New_TankMoveDir--;
		for (std::list<Tank*>::const_iterator it = CTanks.cbegin(); it != CTanks.cend(); ++it){
			(*it)->Draw(renderer);
			// ����������ӵ�
			if ((*it)->Launch())
			{
				if ((*it)->CanLauncher())
				{
					Bullet* bullet = new Bullet((*it)->getX() + SQUARE_LENGTH - BULLET_LENGTH / 2, (*it)->getY() + SQUARE_LENGTH - BULLET_LENGTH / 2, 
						(*it)->currentDir, bulletTex, (*it));
					CBullets.push_back(bullet);
					// ��ֹ�ٷ����ӵ�
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
					// ����Ϸ����֮����û�з�����ײ���������һ����ʱ�������³�ʼ��tank�ƶ�����
					if (!IsCollisionScreen(*it, (*it)->currentDir)
						&& !IsCollisionTanks(*it)
						&& !CollisionBarriers_Tanks(*it))
					{
						(*it)->Move((*it)->currentDir);
						// ��ʱ������������������tank�ƶ�����
						if (New_TankMoveDir <= 0){
							(*it)->setCurrentDir(TankMoveDir(rand() % 4));
						}
					}else{
						// �������Ļ������ײ�����������tank�ƶ�����
						(*it)->setCurrentDir(TankMoveDir(rand() % 4));
					}
				//}
			}
			RecordTank_isCanMove = 0;
			if (New_TankMoveDir <= 0){
				New_TankMoveDir = SQUARE_LENGTH * (rand() % 3 + 4);
			}
		}

		// ��Ϸ����ӵ�
		Draw(PBullets, renderer, WALL);
		Draw(PBullets, renderer, C_TANK);

		// ��������ӵ�
		Draw(CBullets, renderer, WALL);
		Draw(CBullets, renderer, P_TANK);

		// �ϰ���
		Draw(PBullets, renderer, BARRIER);

		// ��Ϸ����ӵ����������ӵ�
		Draw(PBullets, renderer, NOT_ALL);
	}
}

// �����ϰ���barriers
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

// ������Ϸ��ҡ�������ҵ��ӵ��Լ�����ص���ײ���
void Game::Draw(std::list<Bullet*>& bullets, SDL_Renderer* renderer, CollisionWithBulletType type)
{
	switch (type)
	{
	case C_TANK:	// �����Ϸ����ӵ��Ƿ���������̹�˷�����ײ
		{
			// ��Ϸ���1
			if (P1Tank)
				Handle_PBC(PBullets, renderer, P1Tank);
			// ��Ϸ���2
			// do something
		}
		break;
	case P_TANK:	// ����������ӵ��Ƿ�����Ϸ���̹�˷�����ײ
		{
			// ��������Ϸ���1���߼�
			if (P1Tank)
				Handle_CBP(renderer, P1Tank);
			// ������Ϸ���2���߼�
			// do something
		}
		break;
	case WALL:		// ����ӵ��Ƿ�����Ļ������ײ
		{
			for (std::list<Bullet*>::const_iterator it = bullets.cbegin(); it != bullets.cend(); )
			{
				bool result = (*it)->MoveSelf();	// MoveSelf()�����������ӵ�����Ļ����ײ���
				if (result){
					// ��ըЧ��
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
	case BARRIER:	// ����ӵ����ϰ���֮�䷢������ײ
		{
			if (P1Tank)
				Handle_CB(PBullets, PLAYER_TANK, renderer);
			if (P2Tank)
				Handle_CB(P2Bullets, PLAYER_TANK, renderer);
			Handle_CB(CBullets, COMPUTER_TANK, renderer);
		}
		break;
	case NOT_ALL:	// ������Ϸ����ӵ����������ӵ�����ײ
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

// ������Ϸ����ӵ������̹����ײ���߼�
void Game::Handle_PBC(std::list<Bullet*>& bullets, SDL_Renderer* renderer, Tank* Ptank)
{
	for (std::list<Bullet*>::const_iterator item = bullets.cbegin(); item != bullets.cend(); )
	{
		bool sign = false;
		for (std::list<Tank*>::const_iterator it = CTanks.cbegin(); it != CTanks.cend(); )
		{
			if (item == PBullets.cend())
				break;
			// �ӵ���ײ��̹��
			if (IsCollisionBullet(*item, *it))
			{
				sign = true;
				// �ӵ���ըЧ��
				Blast(blastTexs, *item, renderer);
				delete (*item);
				item = PBullets.erase(item);
				// �������1�������·����ӵ�
				Ptank->setIsCanLauncher(true);
				// ̹�˱�ըЧ��
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

// �����������ӵ�����Ϸ���̹����ײ���߼�
void Game::Handle_CBP(SDL_Renderer* renderer, Tank* Ptank)
{
	for (std::list<Bullet*>::const_iterator it = CBullets.cbegin(); it != CBullets.cend(); )
	{
		if (IsCollisionBullet(*it, Ptank))
		{
			std::cout << "Player tank is hitted" << std::endl;
			// �ӵ���ըЧ��
			Blast(blastTexs, *it, renderer);
			// �������õ������̹�˿��Է����ӵ�
			(*it)->getTank()->setIsCanLauncher(true);
			delete (*it);
			it = CBullets.erase(it);
		}else{
			(*it)->Draw(renderer);
			++it;
		}
	}
}

// ������Ϸ����ӵ������������ӵ���ײ���߼�
void Game::Handle_CPB(std::list<Bullet*>& PBullets, std::list<Bullet*>& CBullets, SDL_Renderer* renderer)
{
	for (std::list<Bullet*>::const_iterator it = CBullets.cbegin(); it != CBullets.cend(); )
	{
		bool sign = false;
		for (std::list<Bullet*>::const_iterator item = PBullets.cbegin(); item != PBullets.cend(); )
		{
			// ���������ײ���������ӵ��͵�������ӵ�
			if (IsCollisionCPB(*it, *item))
			{
				sign = true;
				// ���item
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
			// ���it
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

// �����ӵ����ϰ���barriers��ײ���߼�
void Game::Handle_CB(std::list<Bullet*>& bullets, TankType type, SDL_Renderer* renderer)
{
	for (std::list<Bullet*>::const_iterator it = bullets.cbegin(); it != bullets.cend(); )
	{
		bool sign = false;
		// normalBarriers
		for (std::list<BarrierClass*>::const_iterator item = normalBarriers.cbegin(); item != normalBarriers.cend(); )
		{
			// ����ӵ���barrier������ײ
			if (CollisionBarrier(*item, *it))
			{
				sign = true;
				// ���item
				delete (*item);
				item = normalBarriers.erase(item);
				// �ٱȽ�һ��
				for (std::list<BarrierClass*>::const_iterator item2 = normalBarriers.cbegin(); item2 != normalBarriers.cend(); )
				{
					// �ٴμ���Ƿ�����ײ
					if (CollisionBarrier(*item2, *it))
					{
						// ���item2
						delete (*item2);
						item2 = normalBarriers.erase(item2);
						break;
					}
					else{
						++item2;
					}
				}
				// ����ӵ�bullet
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
			// ����ӵ���barrier������ײ������TankType��������steelBarriers�������߼�
			if (CollisionBarrier(*item, *it))
			{
				sign = true;
				switch (type)
				{
				case PLAYER_TANK:		// �������Ϸ���̹�˻���steel barriers
					{
						Blast(blastTexs, *it, renderer);
						(*it)->getTank()->setIsCanLauncher(true);
						delete (*it);
						it = bullets.erase(it);
					}
					break;
				case COMPUTER_TANK:		// ����ǵ������̹�˻���steel barriers
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

// �����ӵ���ըЧ��
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

// ����̹�˱�ըЧ��
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

// ����������ӵ�����Ϸ����ӵ�����ײ
bool Game::IsCollisionCPB(Bullet* C_bullet, Bullet* P_bullet)
{
	/* ��C_bullet���в��� */
	// ��ȡ�ӵ�ÿ�ƶ�һ�εľ���
	int Distance = C_bullet->getSpeed();
	// ��ȡ�ӵ����Ͻ�����
	int x = C_bullet->getX();
	int y = C_bullet->getY();
	// ��ȡ�ӵ����ƶ�����
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

	// ��ȡP_bullet�����Ͻ�����
	int x2 = P_bullet->getX();
	int y2 = P_bullet->getY();

	if ((abs(x2 - x) < BULLET_LENGTH) &&
		(abs(y2 - y) < BULLET_LENGTH))
	{
		return true;
	}
	return false;
}

// ����ϰ������ӵ�֮�����ײ
bool Game::CollisionBarrier(BarrierClass* barriers, Bullet* bullet)
{
	// ��ȡ�ӵ�ÿ�ƶ�һ�εľ���
	int Distance = bullet->getSpeed();
	// ��ȡ�ӵ����Ͻ�����
	int x = bullet->getX();
	int y = bullet->getY();
	// ��ȡ�ӵ��ƶ�����
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

	// �����ӵ���������
	int bullet_centerX = x + BULLET_LENGTH / 2;
	int bullet_centerY = y + BULLET_LENGTH / 2;

	// �����ϰ�����������
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

// ����ϰ����̹��֮�����ײ
bool Game::CollisionBarrier(BarrierClass* barriers, Tank* tank)
{
	// ��ȡ̹��ÿ�ƶ�һ�εľ���
	int Distance = tank->getDistance();
	// ��ȡ̹�����Ͻǵ�����
	int x = tank->getX();
	int y = tank->getY();
	// ��ȡtank���ƶ�����
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

	// ����barriers����������
	int BarrierLength = barriers->GetBarrierLength();
	int barrier_centerX = barriers->getX() + BarrierLength / 2;
	int barrier_centerY = barriers->getY() + BarrierLength / 2;

	// ����tank����������
	int tank_centerX = x + SQUARE_LENGTH;
	int tank_centerY = y + SQUARE_LENGTH;

	if ((abs(tank_centerX - barrier_centerX) < (BarrierLength / 2 + SQUARE_LENGTH)) &&
		(abs(tank_centerY - barrier_centerY) < (BarrierLength / 2 + SQUARE_LENGTH)))
	{
		return true;
	}
	return false;
}

// ����ӵ���̹�˼����ײ
bool Game::IsCollisionBullet(Bullet* bullet, Tank* tank)
{
	// ��ȡ�ӵ�ÿ�ƶ�һ�εľ���
	int Distance = bullet->getSpeed();
	// ��ȡ�ӵ����Ͻǵ�����
	int x = bullet->getX();
	int y = bullet->getY();
	// ��ȡ�ӵ��ƶ��ķ���
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

	// �����ӵ�����������
	int bullet_centerX = x + BULLET_LENGTH / 2;
	int bullet_centerY = y + BULLET_LENGTH / 2;

	// ����tank����������
	int tank_centerX = tank->getX() + SQUARE_LENGTH;
	int tank_centerY = tank->getY() + SQUARE_LENGTH;

	if ((abs(tank_centerX - bullet_centerX) < (BULLET_LENGTH / 2 + SQUARE_LENGTH)) &&
		(abs(tank_centerY - bullet_centerY) < (BULLET_LENGTH / 2 + SQUARE_LENGTH)))
	{
		return true;
	}
	return false;
}

// ���������tank��barriers����ײ
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

// ��ײ���(��Ļ)
bool Game::IsCollisionScreen(Tank* tank, TankMoveDir dir)
{
	// ÿ�ƶ�һ�εľ���
	int Distance = SQUARE_LENGTH;
	// tank�����Ͻ�����
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
	// ��ȡtank�����Ͻ�����
	int tank_x = tank->getX();
	int tank_y = tank->getY();

	// ��ȡtankÿ�ƶ�һ�εľ���
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

// ��ײ���(tank֮��)
bool Game::IsCollisionTank(Tank* tank1, Tank* tank2)
{
	// ��ȡtank1��tank2�ƶ�������Ͻ�����
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

// ���ÿһ�ص���̹����Դ���ϰ�����Դ
void Game::Clear()
{
	// �ͷ��ϰ�����Դ
	Clear(steelBarriers);
	Clear(normalBarriers);
	Clear(grassBarriers);
	Clear(waterBarriers);

	// ����������̹����Դ
	for (std::list<Tank*>::const_iterator it = CTanks.cbegin(); it != CTanks.cend(); ++it)
	{
		if (*it)
			delete (*it);
	}
	CTanks.clear();
}

void Game::Clear(std::list<BarrierClass*>& barriers)
{
	// �ͷ��ϰ�����Դ
	for (std::list<BarrierClass*>::const_iterator item = barriers.cbegin(); item != barriers.cend(); ++item)
	{
		if (*item)
			delete (*item);
	}
	barriers.clear();
}

void Game::Clear(std::list<Bullet*>& bullets)
{
	// �ͷ��ӵ���Դ
	for (std::list<Bullet*>::const_iterator it = bullets.cbegin(); it != bullets.cend(); ++it)
	{
		if (*it)
			delete (*it);
	}
	bullets.clear();
}

Game::~Game(void)
{
	// �ͷŵ��������Դ
	for (std::list<Tank*>::const_iterator it = CTanks.cbegin(); it != CTanks.cend(); ++it)
	{
		if (*it)
			delete (*it);
	}
	CTanks.clear();
	// �ͷ���Ϸ�����Դ
	if (P1Tank)
		delete P1Tank;
	if (P2Tank)
		delete P2Tank;

	// �ͷ��ϰ�����Դ
	Clear(steelBarriers);
	Clear(normalBarriers);
	Clear(grassBarriers);
	Clear(waterBarriers);

	// ����ӵ�
	Clear(PBullets);
	Clear(P2Bullets);
	Clear(CBullets);
}
