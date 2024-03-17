#include<graphics.h>
#include<time.h>
#include<iostream>
#include<ctime>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


#define INTERVAL 100//最上面的间隔
using namespace std;
bool gameing = true;
bool first = true;
int grade = 0;

//如何表示黑块？
int map[4] = { 0 };
void initMap() {
	for (int i = 0; i < 4; i++) {		
		map[i] = rand() % 4;
		
	}	
}
void drawMap(){
	
	//将项目属性中的字符集设置为多字节字符集；
	settextcolor(RGB(200, 60, 170));//文字颜色默认为白色，设置字体颜色
	settextstyle(25, 0, "楷书");//设置字体大小和字体
	outtextxy(150, 30, "别踩白块儿");//写入标题
	setlinecolor(RED);//设置直线颜色 ，默认为白色
	setlinestyle(PS_SOLID,2);//设置直线的形式 实线 像素为2
	line(0, 0, 400, 0);
	for (int i = 0; i < 5; i++) {
		line(0,INTERVAL + i * 150, 400, i * 150 + INTERVAL);
	}
	for (int i = 0; i < 5; i++) {
		line(100 * i, INTERVAL,100 * i, 700);
	}	//绘制黑块
	for (int i = 0; i < 4; i++) {
		int x = map[i] * 100;
		int y = i * 150 + INTERVAL;
		setfillcolor(BLACK);
		solidrectangle(x + 1, y + 1, x + 100 - 1, y + 150 - 1);
	}	
}

//用鼠标/键盘玩游戏
void mouseEvent(MOUSEMSG& msg) {
	if (msg.uMsg == WM_LBUTTONDOWN)
	{
		
		//获得下表为3的方块的左上角坐标
		int x = map[3] * 100;
		int y = 3 * 150 + INTERVAL;
		if (msg.x >= 0 && msg.x <= 100) {
			mciSendString("play ./1.mp3 wait", NULL, NULL, NULL);
		}else if (msg.x > 100 && msg.x <= 200) {
			mciSendString("play ./2.mp3 wait", NULL, NULL, NULL);
		}else if (msg.x >200 && msg.x <= 300) {
			mciSendString("play ./3.mp3 wait", NULL, NULL, NULL);
		}else if (msg.x > 300 && msg.x <= 400) {
			mciSendString("play ./4.mp3 wait", NULL, NULL, NULL);
		}
		if (msg.x >= x && msg.x <= x + 100 && msg.y >= y && msg.y <= y + 150) {
			
			for (int i = 3; i > 0; i--) {
				map[i] = map[i - 1];
			}
			map[0] = rand() % 4;
			//清屏
			cleardevice();
			
			grade++;
		}
		else {
			settextstyle(80,0,"楷书");
			outtextxy(50, 300, "GAMEOVER~");
			gameing = false;
		}
	}
}

int main() {	
	//1、创建一个窗口
	initgraph(400, 700,EW_SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();//清空绘图设备	

	//随机数，需要设置随机数种子
	srand((	unsigned)time(NULL));
	//编译器真心不错
	
	//初始化数据
	initMap();

	
	

	clock_t start_time = clock();
	MOUSEMSG msg;
	while (true) {
	
		if (first) {
			
			first = false;
		}
		if (gameing == false)
			break;
		
		drawMap();
		msg = GetMouseMsg();
		mouseEvent(msg);

	}

	clock_t end_time = clock();
	double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "您的分数是：" << grade << endl;
	cout << "得分所用时长为：" << duration << endl;
	MessageBox(GetHWnd(), "GAMEOVER-", "you die", MB_OK);

	return 0;
}