#include<graphics.h>
#include<time.h>
#include<iostream>
#include<ctime>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


#define INTERVAL 100//������ļ��
using namespace std;
bool gameing = true;
bool first = true;
int grade = 0;

//��α�ʾ�ڿ飿
int map[4] = { 0 };
void initMap() {
	for (int i = 0; i < 4; i++) {		
		map[i] = rand() % 4;
		
	}	
}
void drawMap(){
	
	//����Ŀ�����е��ַ�������Ϊ���ֽ��ַ�����
	settextcolor(RGB(200, 60, 170));//������ɫĬ��Ϊ��ɫ������������ɫ
	settextstyle(25, 0, "����");//���������С������
	outtextxy(150, 30, "��Ȱ׿��");//д�����
	setlinecolor(RED);//����ֱ����ɫ ��Ĭ��Ϊ��ɫ
	setlinestyle(PS_SOLID,2);//����ֱ�ߵ���ʽ ʵ�� ����Ϊ2
	line(0, 0, 400, 0);
	for (int i = 0; i < 5; i++) {
		line(0,INTERVAL + i * 150, 400, i * 150 + INTERVAL);
	}
	for (int i = 0; i < 5; i++) {
		line(100 * i, INTERVAL,100 * i, 700);
	}	//���ƺڿ�
	for (int i = 0; i < 4; i++) {
		int x = map[i] * 100;
		int y = i * 150 + INTERVAL;
		setfillcolor(BLACK);
		solidrectangle(x + 1, y + 1, x + 100 - 1, y + 150 - 1);
	}	
}

//�����/��������Ϸ
void mouseEvent(MOUSEMSG& msg) {
	if (msg.uMsg == WM_LBUTTONDOWN)
	{
		
		//����±�Ϊ3�ķ�������Ͻ�����
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
			//����
			cleardevice();
			
			grade++;
		}
		else {
			settextstyle(80,0,"����");
			outtextxy(50, 300, "GAMEOVER~");
			gameing = false;
		}
	}
}

int main() {	
	//1������һ������
	initgraph(400, 700,EW_SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();//��ջ�ͼ�豸	

	//���������Ҫ�������������
	srand((	unsigned)time(NULL));
	//���������Ĳ���
	
	//��ʼ������
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
	cout << "���ķ����ǣ�" << grade << endl;
	cout << "�÷�����ʱ��Ϊ��" << duration << endl;
	MessageBox(GetHWnd(), "GAMEOVER-", "you die", MB_OK);

	return 0;
}