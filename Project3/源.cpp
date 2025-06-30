#include <iostream>
#include <conio.h>
#include "def.h"
#include <process.h>
#include <time.h>
#include <thread>

using namespace std;
using namespace cv;

void detect(VideoCapture &cap,int &direction)
{
	static Mat vid;
	cap.read(vid);
	vector<Mat>channel;
	split(vid, channel);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	vector<Rect>choose;
	subtract(channel[2], channel[1], vid);
	threshold(vid, vid, 100, 255, cv::THRESH_BINARY);	
	findContours(vid, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++)
	{
		Rect rect = boundingRect(Mat(contours[i]));
		if (rect.area() > 2000 && abs(rect.height - rect.width) < 200)
		{
			choose.push_back(rect);
		}
	}
	//cout << "检测物体数量：" << choose.size() << endl;
	if (choose.size() == 2)
	{
		if (choose[0].x > choose[1].x && choose[0].y < choose[1].y)
		{
			//cout << "right" << endl; 
			direction = 1;
			
		}
		if (choose[0].x < choose[1].x && choose[0].y < choose[1].y)
		{
			//cout << "left" << endl; 
			direction = 2; 
		}
		if (choose[0].x > choose[1].x && choose[0].y > choose[1].y)
		{
			//cout << "right" << endl; 
			direction = 1;
		}
		if (choose[0].x < choose[1].x && choose[0].y > choose[1].y)
		{
			//cout << "left" << endl; 
			direction = 2;
		}
	}
	else
	{
		direction = 0;
	}
	imshow("video", vid);
	waitKey(1);
}

bool timer(int ms)//定时器
{
	static int t1 = 0, t2;
	if (t2 - t1 > ms)
	{
		t2 = 0;
		return true;
	}
	t2++;
	return false;
}

class hero
{
private:
	int dx = 5;
	int dy = 3;
	int direction = 2;
	IMAGE hero_img[2];
public:
	int alive = 1;
	int x = WINDOWWIDTH/2;
	int y = WINDOWHEIGHT- PLAYERH;
	int width = PLAYERW;
	int height = PLAYERH;
	int play_time = 0;
	void diplay()
	{
		if (alive)
		{
			loadimage(&hero_img[0], ".\\resourcesss\\hero.jpg", PLAYERW, PLAYERH);
			loadimage(&hero_img[1], ".\\resourcesss\\hero;.jpg", PLAYERW, PLAYERH);
			putimage(x, y, &hero_img[0],SRCAND);
			putimage(x, y, &hero_img[1], SRCPAINT);
		}
		
		
	}
	void control()
	{
		
		
		if (GetAsyncKeyState(VK_UP))
		{
			direction = 1;
			if (y > 0) {  y -= dy; }
			else { y = 0; }
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			direction = 2;
			if (x < 940 - PLAYERW) {  x += dx; }
			else { x = 940 - PLAYERW; }
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			direction = 3;
			if (y < WINDOWHEIGHT - PLAYERH) {  y += dy; }
			else { y = 720- PLAYERH; }
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			direction = 4;
			if (x > 340) {  x -= dx; }
			else { x = 340; }
		}
	}
};

class kun
{
private:
	int dx = 10;
	int dy = 5;
	IMAGE kun_img[5][2];
	IMAGE kunimg[2];
public:
	bool alive = true;
	int x = WINDOWWIDTH / 2;
	int y = WINDOWHEIGHT - KUNH;
	int width = KUNW;
	int height = KUNH;
	int play_time = 0;
	int score = 0;

	void diplay()
	{
		static int dingzhen = 1;
		static bool fangxiang = true;
		if (alive)
		{
			if (fangxiang){dingzhen+=1;}
			else { dingzhen-=1; }
			if (dingzhen == 1)
			{
				loadimage(&kunimg[0], ".\\resourcesss\\k1;.jpg", width, height);
				loadimage(&kunimg[1], ".\\resourcesss\\k1.jpg", width, height);
				putimage(x, y, &kunimg[0], SRCAND);
				putimage(x, y, &kunimg[1], SRCPAINT);
			}
			if (dingzhen == 2)
			{
				loadimage(&kunimg[0], ".\\resourcesss\\k2;.jpg", width, height);
				loadimage(&kunimg[1], ".\\resourcesss\\k2.jpg", width, height);
				putimage(x, y, &kunimg[0], SRCAND);
				putimage(x, y, &kunimg[1], SRCPAINT);
			}
			if (dingzhen == 3)
			{
				loadimage(&kunimg[0], ".\\resourcesss\\k3;.jpg", width, height);
				loadimage(&kunimg[1], ".\\resourcesss\\k3.jpg", width, height);
				putimage(x, y, &kunimg[0], SRCAND);
				putimage(x, y, &kunimg[1], SRCPAINT);
			}
			if (dingzhen == 4)
			{
				loadimage(&kunimg[0], ".\\resourcesss\\k4;.jpg", width, height);
				loadimage(&kunimg[1], ".\\resourcesss\\k4.jpg", width, height);
				putimage(x, y, &kunimg[0], SRCAND);
				putimage(x, y, &kunimg[1], SRCPAINT);
			}
			if (dingzhen == 5)
			{
				loadimage(&kunimg[0], ".\\resourcesss\\k5;.jpg", width, height);
				loadimage(&kunimg[1], ".\\resourcesss\\k5.jpg", width, height);
				putimage(x, y, &kunimg[0], SRCAND);
				putimage(x, y, &kunimg[1], SRCPAINT);
			}
			if (dingzhen == 5||dingzhen ==1)
			{
				fangxiang =!fangxiang;
			}
		}
	}

	void control()
	{
		if (GetAsyncKeyState(VK_UP))
		{
			if (y > 0) { y -= dy; }
			else { y = 0; }
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			if (x < WINDOWWIDTH - KUNW) { x += dx; }
			else { x = WINDOWWIDTH - KUNW; }
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (y < WINDOWHEIGHT - KUNH) { y += dy; }
			else { y = 720 - KUNH; }
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (x > 0) { x -= dx; }
			else { x = 0; }
		}
	}
};

class wall
{
private:
	int width = WALLWID;
	int height = WALLHEI;
	int road_num;
	int x;
	int y;
	int speed = 7;
	int exist = 0;
	IMAGE wall_img[2];
public:
	void display_car1()
	{
		if (exist == 1)
		{
			loadimage(&wall_img[0], ".\\resourcesss\\car1.jpg", width, height);
			loadimage(&wall_img[1], ".\\resourcesss\\car1;.jpg", width, height);
			putimage(x, y, &wall_img[0], SRCAND);
			putimage(x, y, &wall_img[1], SRCPAINT);
		}
	}
	void setup()
	{
		if (exist == 0)
		{
			exist = 1;
			//x = rand() % ((940-wid)-340+1)+340;
			road_num = rand() % (6 - 1 + 1) + 1;
			switch (road_num)
			{
			case 1: x = 340 + 20; break;
			case 2: x = 440 + 20; break;
			case 3: x = 540 + 20; break;
			case 4: x = 640 + 20; break;
			case 5: x = 740 + 20; break;
			case 6: x = 840 + 20; break;
			}
			y = -height;
		}
	}
	void move()
	{
		if (exist == 1 && y <WINDOWHEIGHT)
		{
			y += speed;
		}
		if (exist == 1 && y >= WINDOWHEIGHT)
		{
			exist = 0;
		}
	}
	void collision_detect(hero &player)
	{
		if ((player.x > x && player.x<x + width && player.y>y && player.y < y + height)
			|| (player.x + player.width > x && player.x + player.width<x + width && player.y>y && player.y < y + height)
			|| (player.x > x && player.x < x + width && player.y + player.height>y && player.y + player.height < y + height)
			|| (player.x + player.width > x && player.x + player.width < x + width && player.y + player.height>y && player.y + player.height < y + height))
		{
			player.alive = 0;
		}
	}
};

class ball
{
protected:
	int x;
	int y;
	int speed = 10;
	int wid = BALLWID;
	int hei = BALLHEI;
	int exist = 0;
	IMAGE img[2];
	LPCTSTR filename1 = ".\\resourcesss\\lq;.jpg";
	LPCTSTR filename2 = ".\\resourcesss\\lq.jpg";
public:
	void display()
	{
		if (exist == 1)
		{
			loadimage(&img[0], filename1, wid, hei);
			loadimage(&img[1], filename2, wid, hei);
			putimage(x, y, &img[0], SRCAND);
			putimage(x, y, &img[1], SRCPAINT);
		}
		
	}
	void setup()
	{
		if (exist == 0)
		{
			exist = 1;
			x = rand() % (WINDOWWIDTH-BALLWID + 1);
			y = -BALLHEI;
		}
	}
	void move()
	{
		if (exist == 1 && y < WINDOWHEIGHT)
		{
			y += speed;
		}
		if (exist == 1 && y >= WINDOWHEIGHT)
		{
			exist = 0;
		}
	}
	bool colasion(kun &player)//碰撞检测
	{
		if ((x > player.x && x<player.x + player.width && y>player.y && y < player.y + player.height)
			|| (x + wid > player.x && x + wid<player.x + player.width && y>player.y && y < player.y + player.height)
			|| (x > player.x && x < player.x + player.width && y + hei>player.y && y + hei < player.y + player.height)
			|| (x + wid > player.x && x + wid < player.x + player.width && y + hei>player.y && y + hei < player.y + player.height))
		{
			exist = 0;
			player.score += 1;
			return true;
		}
		return false;
	}
};

class chick:public ball
{
protected:
	int x;
	int y;
	int speed = 10;
	int wid = CHICKWID;
	int hei = CHICKHEI;
	int exist = 0;
	IMAGE img[2];
	LPCTSTR filename1 = ".\\resourcesss\\chick;.jpg";
	LPCTSTR filename2 = ".\\resourcesss\\chick.jpg";
public:
	void display()
	{
		if (exist == 1)
		{
			loadimage(&img[0], filename1, wid, hei);
			loadimage(&img[1], filename2, wid, hei);
			putimage(x, y, &img[0], SRCAND);
			putimage(x, y, &img[1], SRCPAINT);
		}

	}
	void setup()
	{
		if (exist == 0)
		{
			exist = 1;
			x = rand() % (WINDOWWIDTH - wid + 1);
			y = -hei;
		}
	}
	void move()
	{
		if (exist == 1 && y < WINDOWHEIGHT)
		{
			y += speed;
		}
		if (exist == 1 && y >= WINDOWHEIGHT)
		{
			exist = 0;
		}
	}
	bool colasion(kun& player)
	{
		if ((x > player.x && x<player.x + player.width && y>player.y && y < player.y + player.height)
			|| (x + wid > player.x && x + wid<player.x + player.width && y>player.y && y < player.y + player.height)
			|| (x > player.x && x < player.x + player.width && y + hei>player.y && y + hei < player.y + player.height)
			|| (x + wid > player.x && x + wid < player.x + player.width && y + hei>player.y && y + hei < player.y + player.height))
		{
			player.alive = false;
			PlaySound(TEXT(".\\resourcesss\\ngm.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return true;
		}
		return false;
	}
};

bool game_start()
{
	IMAGE Start;
	IMAGE Button[2][2];
	IMAGE Cursor;
	int mode = 1;
	loadimage(&Start, ".\\resourcesss\\开始界面.jpg", 1280, 720);
	loadimage(&Button[0][0], ".\\resourcesss\\start.jpg", 300, 75);
	loadimage(&Button[1][0], ".\\resourcesss\\ikun.jpg", 300, 75);
	loadimage(&Button[0][1], ".\\resourcesss\\start_1.jpg", 300, 75);
	loadimage(&Button[1][1], ".\\resourcesss\\ikun2.jpg", 300, 75);
	while (1)
	{
		putimage(0, 0, &Start);
		if (mode == 1)
		{
			putimage(WINDOWWIDTH / 2 - 150, WINDOWHEIGHT / 2, &Button[0][1]);
			putimage(WINDOWWIDTH / 2 - 150, WINDOWHEIGHT / 2 + 150, &Button[1][0]);
		}
		else
		{
			putimage(WINDOWWIDTH / 2 - 150, WINDOWHEIGHT / 2, &Button[0][0]);
			putimage(WINDOWWIDTH / 2 - 150, WINDOWHEIGHT / 2 + 150, &Button[1][1]);
		}
		char key = _getch();
		if (key == 's' && mode == 1)
		{
			mode -= 1;
		}
		if (key == 'w' && mode == 0)
		{
			mode += 1;
		}
		if (key == 13 && mode == 1) { return true;  }
		if (key == 13 && mode == 0) { return false; break;}
	}
}

class background_gaming//进行游戏背景
{
private:
	int speed = FLOWSPEED;
	int y1 = 0;
	int y2 = -720;
public:
	IMAGE car_background[2];
	IMAGE kun_background;
	void display_car()
	{
		loadimage(&car_background[0], ".\\resourcesss\\地图1.jpg", 1280, 720);
		loadimage(&car_background[1], ".\\resourcesss\\地图2.jpg", 1280, 720);
		putimage(0, y1, &car_background[0]);
		putimage(0, y2, &car_background[1]);
		
	}
	void display_kun()
	{
		loadimage(&kun_background, ".\\resourcesss\\kunback.jpg", 1280, 720);
		putimage(0, 0, &kun_background);
	}
	void flow_control()
	{
		if (y1 >= 720) { y1 = -720; }
		else { y1 += speed; }
		if (y2 >= 720){y2 = -720;}
		else { y2 += speed; }
	}
	
};

void showimg(bool mode,hero &player,kun &k,wall walls[],ball balls[],chick ji[], background_gaming &bg)//显示
{
	
	if (mode)
	{
		bg.display_car();
		for (int i = 0; i < WALLNUM; i++)
		{
			walls[i].display_car1();
		}
		player.diplay();
	}
	else
	{
		bg.display_kun();
		for (int i = 0; i < BALLNUM; i++)
		{
			balls[i].display();
		}
		for (int j = 0; j < CHICKNUM; j++)
		{
			ji[j].display();
		}
		k.diplay();
	}
	
}

void update_control(bool mode, hero &player,kun &k,wall walls[],ball balls[], chick ji[],background_gaming &bg,int direction)//控制流更新
{
	if (mode)
	{
		bg.flow_control();
		if (player.alive)
		{
			player.control();
			if (player.x < 940 - PLAYERW&&direction == 2)//右转
			{
				player.x += 3;
			}
			if (player.x>340 &&direction == 1)
			{
				player.x -= 3;
			}
		}
		for (int i = 0; i < WALLNUM; i++)
		{
			walls[i].move();
			walls[i].collision_detect(player);
		}
	}
	else
	{
		if (k.alive)
		{
			k.control();
		}
		for (int i = 0; i < BALLNUM; i++)
		{
			balls[i].move();
			balls[i].colasion(k);
		}
		for (int j = 0; j < CHICKNUM; j++)
		{
			ji[j].move();
			ji[j].colasion(k);
		}
	}
}

void car_gaming_frame(bool mode,hero &a,kun &k,wall b[],ball balls[],chick ji[], int &total_time, background_gaming &bg)
{
	static int direction = 0;
	VideoCapture cap(0);
	BeginBatchDraw();
	while (true)
	{
		detect(cap, direction);
		cout << direction << endl;
		int startime = clock();
		total_time++;
		if (timer(rand() % (TIMEMAX - TIMEMIN + 1) + TIMEMIN))
		{
			static int index = 0;
			b[index].setup();
			index++;
			if (index == WALLNUM)
			{
				index = 0;
			}
		}
		update_control(mode,a,k, b,balls,ji,bg,direction);
		showimg(mode,a, k,b,balls,ji,bg);
		if (a.alive == 0)
		{
			break;
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}

void kun_gaming_frame(bool mode, hero & a,kun& k, wall b[],ball balls[],chick ji[], int& total_time, background_gaming& bg)
{

	BeginBatchDraw();
	while (true)
	{
		int startime = clock();
		total_time++;
		if (timer(rand() % (TIMEMAX - TIMEMIN + 1) + TIMEMIN))
		{
			static int index = 0;
			static int jndex = 0;
			ji[jndex].setup();
			balls[index].setup();
			index++;
			jndex++;
			if (index == BALLNUM)
			{
				index = 0;
			}
			if (jndex == CHICKNUM)
			{
				jndex = 0;
			}
		}
		int n = 1;
		update_control(mode, a,k, b, balls, ji,bg,n);
		showimg(mode, a,k, b,balls, ji, bg);
		if (!k.alive)
		{
			break;
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}

void game_end(bool mode, int score, int kunscore)
{
	IMAGE End;
	IMAGE Die;
	loadimage(&End, ".\\resourcesss\\结束界面.jpg", WINDOWWIDTH, WINDOWHEIGHT);
	loadimage(&Die, ".\\resourcesss\\end.jpg", 300, 75);
	putimage(0, 0, &End);
	putimage(WINDOWWIDTH / 2 - 150, WINDOWHEIGHT / 2, &Die);
	char key = _getch();
	if (mode)
	{
		while (key != 'q' || key == NULL)
		{
			settextstyle(42, 30, "宋体");
			setbkmode(TRANSPARENT);
			settextcolor(RGB(255, 0, 0));
			outtextxy(WINDOWWIDTH / 2 - 175, WINDOWHEIGHT / 2 + 120, "您的得分是：");
			TCHAR text[5];
			sprintf_s(text, "%d", score);
			outtextxy(WINDOWWIDTH / 2 + 150, WINDOWHEIGHT / 2 + 120, text);
		}
	}
	else
	{
		while (key != 'q' || key == NULL)
		{
			settextstyle(42, 30, "宋体");
			setbkmode(TRANSPARENT);
			settextcolor(RGB(255, 0, 0));
			outtextxy(WINDOWWIDTH / 2 - 175, WINDOWHEIGHT / 2 + 120, "您的得分是：");
			TCHAR text[5];
			sprintf_s(text, "%d", kunscore);
			outtextxy(WINDOWWIDTH / 2 + 150, WINDOWHEIGHT / 2 + 120, text);
		}
	}
}


int main()
{
	initgraph(WINDOWWIDTH, WINDOWHEIGHT);
	//开始界面
	
	bool mode = game_start();
	static int total_time = 0;
	hero a;
	kun k;
	wall b[WALLNUM];
	ball ba[BALLNUM];
	chick ji[CHICKNUM];
	background_gaming c;
	if (mode)
	{
		if (a.alive)
		{
			PlaySound(TEXT(".\\resourcesss\\bgm.wav"), NULL, SND_FILENAME | SND_ASYNC);
			car_gaming_frame(mode, a, k, b, ba,ji, total_time, c);
			
		}
	}
	else
	{
		if (k.alive)
		{
			PlaySound(TEXT(".\\resourcesss\\jntm.wav"), NULL, SND_FILENAME | SND_ASYNC);
			kun_gaming_frame(mode, a, k, b, ba, ji, total_time, c);
		}
	}
	game_end(mode,total_time,k.score);
	_getch();
	closegraph();
	return 0;
}

