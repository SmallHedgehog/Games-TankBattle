#pragma once

/*
定义Window类主要负责窗口的创建、显示与更新，加载资源
*/

#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Game.h"

using namespace std;

class Window
{
public:
	Window(void);
	~Window(void);

public:
	void Start();				// 进入消息循环
	void Refresh();				// refresh到屏幕上
	void Update();				// 更新图像信息
	void LoadResouceFile();		// 加载资源文件
	SDL_Texture* Load_image(std::string FilePath);		// 加载图像
	SDL_Texture* Load_gifImage(std::string FilePath);
	void Init();				// 初始化游戏对象
	void ResetGame();			// 重置游戏
	SDL_Texture* Draw_text(std::string message);		// 绘制文字
	void Draw_text(std::string message, int x, int y, int flag);

private:
	SDL_Window* win;			// 窗口
	SDL_Renderer* renderer;		// 渲染器
	TTF_Font* Font;				// 字体

	// 坦克纹理资源
	std::vector<std::vector<SDL_Texture*>> vec;
	std::vector<SDL_Texture*> PTtexs;
	std::vector<SDL_Texture*> P2Ttexs;
	// 子弹纹理资源
	SDL_Texture* bulletTex;
	// 爆炸效果纹理资源
	std::vector<SDL_Texture*> blastTexs;
	std::vector<SDL_Texture*> tankBlastTexs;
	// 坦克barn纹理资源
	std::vector<SDL_Texture*> barnTexs;
	// 障碍物纹理资源
	std::vector<SDL_Texture*> barrierTexs;

	// 游戏对象
	Game* game;

	SDL_Texture* bg;
	SDL_Texture* miniTank;
	// 字体纹理资源，防止内存泄漏
	SDL_Texture* fontTexs[5];

	SDL_Texture* gameTexs[5];
	bool mouse_on_button1;
	bool mouse_on_button2;
};

