#include "stdafx.h"
#include "Window.h"
#include <Windows.h>
#include <stdint.h>
#include <time.h>


Window::Window(void):
	win(nullptr), renderer(nullptr)
{
	// 初始化SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		exit(1);
	}
	// 初始化图像库
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	// 初始化字体库
	TTF_Init();
	Font = TTF_OpenFont("res/SourceSansPro-Regular.ttf", 20);

	// 创建窗口

	win = SDL_CreateWindow(WINDOW_CAPTION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
	// 创建渲染器(使用硬件加速渲染和与当前显示器同步)
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// 初始化随机数种子
	srand(unsigned int (time(0)));

	for (int i=0; i<5; ++i)
		fontTexs[i] = nullptr;
	mouse_on_button1 = false;
	mouse_on_button2 = false;

	// 加载资源文件
	LoadResouceFile();
	// 初始化游戏对象
	Init();
}

void Window::Init()
{
	game = new Game(vec, PTtexs, P2Ttexs, bulletTex, blastTexs, tankBlastTexs, barnTexs, barrierTexs);
}

void Window::ResetGame()
{
	// do something
}

// 进入消息循环
void Window::Start()
{
	SDL_Event event;
	bool gameRunning = true;
	while (gameRunning)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_KEYDOWN:	// 键盘按键事件
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_w:
						game->HandleInput(UP);
						break;
					case SDLK_a:
						game->HandleInput(LEFT);
						break;
					case SDLK_d:
						game->HandleInput(RIGHT);
						break;
					case SDLK_s:
						game->HandleInput(DOWN);
						break;
					case SDLK_j:
						game->Launch();
						break;
					case SDLK_SPACE:
						{
							// do something
						}
						break;
					case SDLK_ESCAPE:
						gameRunning = false;
						break;
					default:
						break;
					}
				}
				break;
			case SDL_MOUSEMOTION:
				if (!game->IsGameStarted)
				{
					// 检测button1
					if (event.button.x > START_X_POS && event.button.x < (START_X_POS + START_WIDTH) &&
						event.button.y > START_Y1_POS && event.button.y < (START_Y1_POS + START_HEIGHT))
					{
						mouse_on_button1 = true;
					}
					else
						mouse_on_button1 = false;
					// 检测button2
					if (event.button.x > START_X_POS && event.button.x < (START_X_POS + START_WIDTH) &&
						event.button.y > START_Y2_POS && event.button.y < (START_Y2_POS + START_HEIGHT))
					{
						mouse_on_button2 = true;
					}
					else
						mouse_on_button2 = false;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						// 检测是否是单人游戏
						if (event.button.x > START_X_POS && event.button.x < (START_X_POS + START_WIDTH) &&
							event.button.y > START_Y1_POS && event.button.y < (START_Y1_POS + START_HEIGHT))
						{
							game->NewGame();
							game->IsGameStarted = true;
						}
						// 检测是否是双人游戏
						if (event.button.x > START_X_POS && event.button.x < (START_X_POS + START_WIDTH) &&
							event.button.y > START_Y2_POS && event.button.y < (START_Y2_POS + START_HEIGHT))
						{
							game->NewGame2();
							game->IsGameStarted = true;
						}
					}
				}
				break;
			default:
				break;
			}
		}

		Update();
		Refresh();
	}
}

// refresh到屏幕上
void Window::Refresh()
{
	SDL_RenderPresent(renderer);
}

// 更新图像位置信息
void Window::Update()
{
	SDL_RenderClear(renderer);

	if (game->IsGameStarted)
	{
		// 绘制背景
		int width = 0, height = 0;
		SDL_QueryTexture(bg, NULL, NULL, &width, &height);
		SDL_Rect rect = {
			GAME_RIGHT_AREA, 0, width, height
		};
		SDL_RenderCopy(renderer, bg, NULL, &rect);

		// 获取电脑玩家坦克数量，绘制还存在的电脑玩家坦克的逻辑提示
		SDL_QueryTexture(miniTank, NULL, NULL, &width, &height);
		for (int i=1; i<=20; ++i)
		{
			// 如果i % 2的余数不等于0，则i所在第一列否则为第二列
			if ((i % 2) != 0)
			{
				// 计算i所在的行
				int row = i / 2 + 1;
				SDL_Rect rect = {
					COL1_POSITION, ROWY_POSITION + height * row, width, height
				};
				SDL_RenderCopy(renderer, miniTank, NULL, &rect);
			}
			else
			{
				// 计算i所在的行
				int row = i / 2;
				SDL_Rect rect = {
					COL2_POSITION, ROWY_POSITION + height * row, width, height
				};
				SDL_RenderCopy(renderer, miniTank, NULL, &rect);
			}
		}

		// 绘制Player1、Player2的得分、生命以及游戏等级
		// Player1、Player2得分
		char p1_score[50];
		sprintf_s(p1_score, "P1 SCORE: %d", game->getP1Score());
		Draw_text(p1_score, X_POSITION, SCORE_Y_P1POSITION, 0);
		char p2_score[50];
		sprintf_s(p2_score, "P2 SCORE: %d", game->getP2Score());
		Draw_text(p2_score, X_POSITION, SCORE_Y_P2POSITION, 1);

		// Player1、Player2生命
		char p1_life[50];
		sprintf_s(p1_life, "P1 LIFE: %d", game->getP1Life());
		Draw_text(p1_life, X_POSITION, LIFE_P1POSITION, 2);
		char p2_life[50];
		sprintf_s(p2_life, "P2 LIFE: %d", game->getP2Life());
		Draw_text(p2_life, X_POSITION, LIFE_P2POSITION, 3);

		// 游戏等级
		char game_level[50];
		sprintf_s(game_level, "GAME LEVEL: %d", game->getGameLevel());
		Draw_text(game_level, X_POSITION, GAME_LIVEL_POSITION, 4);

		game->Draw(renderer);
	}
	else
	{
		int width = 0, height = 0;
		SDL_QueryTexture(gameTexs[4], NULL, NULL, &width, &height);
		SDL_Rect rect = {
			TITLE_X_POS, TITLE_Y_POS, width, height
		};
		SDL_RenderCopy(renderer, gameTexs[4], NULL, &rect);
		if (!mouse_on_button1)
		{
			SDL_QueryTexture(gameTexs[0], NULL, NULL, &width, &height);
			SDL_Rect rect = {
				START_X_POS, START_Y1_POS, width, height
			};
			SDL_RenderCopy(renderer, gameTexs[0], NULL, &rect);
		}
		else
		{
			SDL_QueryTexture(gameTexs[1], NULL, NULL, &width, &height);
			SDL_Rect rect = {
				START_X_POS, START_Y1_POS, width, height
			};
			SDL_RenderCopy(renderer, gameTexs[1], NULL, &rect);
		}
		
		if (!mouse_on_button2)
		{
			SDL_QueryTexture(gameTexs[2], NULL, NULL, &width, &height);
			SDL_Rect rect = {
				START_X_POS, START_Y2_POS, width, height
			};
			SDL_RenderCopy(renderer, gameTexs[2], NULL, &rect);
		}
		else
		{
			SDL_QueryTexture(gameTexs[3], NULL, NULL, &width, &height);
			SDL_Rect rect = {
				START_X_POS, START_Y2_POS, width, height
			};
			SDL_RenderCopy(renderer, gameTexs[3], NULL, &rect);
		}
	}
}

void Window::LoadResouceFile()
{
	std::vector<SDL_Texture*> localVec;
	char buffer[255] = { 0 };
	// normal tank
	for (int i=1; i<=4; ++i)
	{
		sprintf_s(buffer, "res/normal/enemy%d.gif", i);
		localVec.push_back(Load_gifImage(buffer));
	}
	vec.push_back(localVec);

	// double tank
	localVec.clear();
	for (int i=1; i<=4; ++i)
	{
		sprintf_s(buffer, "res/double/enemy%d.gif", i);
		localVec.push_back(Load_gifImage(buffer));
	}
	vec.push_back(localVec);

	// two double tank
	localVec.clear();
	for (int i=1; i<=16; ++i)
	{
		sprintf_s(buffer, "res/TDouble/enemy%d.gif", i);
		localVec.push_back(Load_gifImage(buffer));
	}
	vec.push_back(localVec);

	// load player tank textures
	for (int i=1; i<=4; ++i)
	{
		sprintf_s(buffer, "res/player1/p%d.gif", i);
		PTtexs.push_back(Load_gifImage(buffer));
	}
	for (int i=1; i<=4; ++i)
	{
		sprintf_s(buffer, "res/player2/p%d.gif", i);
		P2Ttexs.push_back(Load_gifImage(buffer));
	}

	// 子弹纹理资源文件加载
	bulletTex = Load_gifImage("res/bullet.gif");

	// 爆炸效果纹理资源文件加载
	for (int i=1; i<=3; ++i)
	{
		sprintf_s(buffer, "res/blast/blast%d.gif", i);
		blastTexs.push_back(Load_gifImage(buffer));
	}
	blastTexs.push_back(Load_gifImage("res/blast/blast3.gif"));

	for (int i=4; i<=5; ++i)
	{
		sprintf_s(buffer, "res/blast/blast%d.gif", i);
		tankBlastTexs.push_back(Load_gifImage(buffer));
	}
	tankBlastTexs.push_back(Load_gifImage("res/blast/blast5.gif"));

	// 坦克barn纹理资源文件加载
	for (int i=1; i<=4; ++i)
	{
		sprintf_s(buffer, "res/barn/born%d.gif", i);
		barnTexs.push_back(Load_gifImage(buffer));
	}

	// 障碍物纹理资源文件加载
	barrierTexs.push_back(Load_gifImage("res/barrier/normal.gif"));
	barrierTexs.push_back(Load_gifImage("res/barrier/steel.gif"));
	barrierTexs.push_back(Load_gifImage("res/barrier/grass.gif"));
	barrierTexs.push_back(Load_gifImage("res/barrier/water.gif"));

	// 背景资源文件加载
	bg = Load_image("res/bg/1.png");
	miniTank = Load_gifImage("res/minitank.gif");

	gameTexs[0] = Load_image("res/button1.png");
	gameTexs[1] = Load_image("res/button1_1.png");
	gameTexs[2] = Load_image("res/button2.png");
	gameTexs[3] = Load_image("res/button2_2.png");
	gameTexs[4] = Load_image("res/title.png");
}

// 加载图像纹理
SDL_Texture* Window::Load_image(std::string FilePath)
{
	SDL_Surface* picture = nullptr;

	picture = IMG_Load(FilePath.c_str());

	// 设置背景透明
	Uint32 colorkey = SDL_MapRGB(picture->format, 255, 255, 255);
	SDL_SetColorKey(picture, SDL_TRUE, colorkey);

	SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);

	return result;
}

SDL_Texture* Window::Load_gifImage(std::string FilePath)
{
	SDL_Surface* pic = nullptr;
	SDL_Texture* tex = nullptr;

	SDL_RWops* rWops = SDL_RWFromFile(FilePath.c_str(), "rb");
	pic = IMG_LoadGIF_RW(rWops);
	tex = SDL_CreateTextureFromSurface(renderer, pic);

	SDL_FreeSurface(pic);

	return tex;
}

SDL_Texture* Window::Draw_text(std::string message)
{
	SDL_Color color = { 0, 0, 0 };
	SDL_Surface* surface = TTF_RenderText_Blended(Font, message.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	return texture;
}

void Window::Draw_text(std::string message, int x, int y, int flag)
{
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Blended(Font, message.c_str(), color);
	// 释放资源，防止内存泄漏
	if (fontTexs)
	{
		SDL_DestroyTexture(fontTexs[flag]);
		fontTexs[flag] = nullptr;
	}
	fontTexs[flag] = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	int width = 0, height = 0;
	SDL_QueryTexture(fontTexs[flag], NULL, NULL, &width, &height);
	SDL_Rect rect = {
		x, y, width, height
	};
	SDL_RenderCopy(renderer, fontTexs[flag], NULL, &rect);
}

Window::~Window(void)
{
	TTF_CloseFont(Font);
	TTF_Quit();

	// 清除纹理数据
	for (int i=0; i<int(vec.size()); ++i)
	{
		std::vector<SDL_Texture*>::const_iterator it = vec[i].cbegin();
		for (; it != vec[i].end(); ++it)
		{
			if (*it)
				SDL_DestroyTexture(*it);
		}
	}
	vec.clear();
	// 坦克纹理数据
	for (std::vector<SDL_Texture*>::const_iterator it = PTtexs.cbegin(); it != PTtexs.cend(); ++it)
	{
		if (*it)
			SDL_DestroyTexture(*it);
	}
	PTtexs.clear();
	// 子弹纹理数据
	SDL_DestroyTexture(bulletTex);
	// 爆炸效果纹理数据
	for (std::vector<SDL_Texture*>::const_iterator it = blastTexs.cbegin(); it != blastTexs.cend(); ++it)
	{
		if (*it)
			SDL_DestroyTexture(*it);
	}
	blastTexs.clear();

	// barn纹理数据
	for (std::vector<SDL_Texture*>::const_iterator it = barnTexs.cbegin(); it != barnTexs.cend(); ++it)
	{
		if (*it)
			SDL_DestroyTexture(*it);
	}

	// 障碍物纹理数据
	for (std::vector<SDL_Texture*>::const_iterator it = barrierTexs.cbegin(); it != barrierTexs.cend(); ++it)
	{
		if (*it)
			SDL_DestroyTexture(*it);
	}

	// 背景和minitank
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(miniTank);

	for (int i=0; i<5; ++i)
		SDL_DestroyTexture(fontTexs[i]);
	for (int i=0; i<5; ++i)
		SDL_DestroyTexture(gameTexs[i]);

	// 释放游戏对象资源
	if (game)
		delete game;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
