#pragma once

/*
����Window����Ҫ���𴰿ڵĴ�������ʾ����£�������Դ
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
	void Start();				// ������Ϣѭ��
	void Refresh();				// refresh����Ļ��
	void Update();				// ����ͼ����Ϣ
	void LoadResouceFile();		// ������Դ�ļ�
	SDL_Texture* Load_image(std::string FilePath);		// ����ͼ��
	SDL_Texture* Load_gifImage(std::string FilePath);
	void Init();				// ��ʼ����Ϸ����
	void ResetGame();			// ������Ϸ
	SDL_Texture* Draw_text(std::string message);		// ��������
	void Draw_text(std::string message, int x, int y, int flag);

private:
	SDL_Window* win;			// ����
	SDL_Renderer* renderer;		// ��Ⱦ��
	TTF_Font* Font;				// ����

	// ̹��������Դ
	std::vector<std::vector<SDL_Texture*>> vec;
	std::vector<SDL_Texture*> PTtexs;
	std::vector<SDL_Texture*> P2Ttexs;
	// �ӵ�������Դ
	SDL_Texture* bulletTex;
	// ��ըЧ��������Դ
	std::vector<SDL_Texture*> blastTexs;
	std::vector<SDL_Texture*> tankBlastTexs;
	// ̹��barn������Դ
	std::vector<SDL_Texture*> barnTexs;
	// �ϰ���������Դ
	std::vector<SDL_Texture*> barrierTexs;

	// ��Ϸ����
	Game* game;

	SDL_Texture* bg;
	SDL_Texture* miniTank;
	// ����������Դ����ֹ�ڴ�й©
	SDL_Texture* fontTexs[5];

	SDL_Texture* gameTexs[5];
	bool mouse_on_button1;
	bool mouse_on_button2;
};

