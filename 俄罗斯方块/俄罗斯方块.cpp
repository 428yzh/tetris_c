#include "pch.h"
#include <graphics.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
MOUSEMSG m;
IMAGE b, L, d_L, z, d_z, T, p;
int currentTurns = 0;
int bs[4][4][4] = {
{
	{2,2,0,0},{2,2,0,0},{0,0,0,0},{0,0,0,0}
},
{
	{2,2,0,0}, {2,2,0,0}, {0,0,0,0}, {0,0,0,0}
},
{
	{2,2,0,0}, {2,2,0,0}, {0,0,0,0}, {0,0,0,0}
},
{
	{2,2,0,0},{2,2,0,0},{0,0,0,0},{0,0,0,0}
}
},
Ls[4][4][4] = {
{
	{2,2,2,0},{2,0,0,0},{0,0,0,0},{0,0,0,0}
},
{
	{2,2,0,0},{0,2,0,0},{0,2,0,0},{0,0,0,0}
},
{
	{0,0,2,0},{2,2,2,0},{0,0,0,0},{0,0,0,0}
},
{
	{2,0,0,0},{2,0,0,0},{2,2,0,0},{0,0,0,0}
}
},
d_Ls[4][4][4] =
{
{
	{2,2,2,0},{0,0,2,0},{0,0,0,0},{0,0,0,0}
},
{
	{0,2,0,0},{0,2,0,0},{2,2,0,0},{0,0,0,0}
},
{
	{2,0,0,0},{2,2,2,0},{0,0,0,0},{0,0,0,0}
},
{
	{2,2,0,0},{2,0,0,0},{2,0,0,0},{0,0,0,0}
}
},
zs[4][4][4] =
{
{
	{2,2,0,0}, {0,2,2,0}, {0,0,0,0}, {0,0,0,0}
},
{
	{0,2,0,0},{2,2,0,0},{2,0,0,0},{0,0,0,0}
},
{
	{2,2,0,0},{0,2,2,0},{0,0,0,0},{0,0,0,0}
},
{
	{0,2,0,0},{2,2,0,0},{2,0,0,0},{0,0,0,0}
}
},
d_zs[4][4][4] =
{
{
	{0,2,2,0}, {2,2,0,0}, {0,0,0,0}, {0,0,0,0}
},
{
	{2,0,0,0},{2,2,0,0},{0,2,0,0},{0,0,0,0}
},
{
	{0,2,2,0},{2,2,0,0},{0,0,0,0},{0,0,0,0}
},
{
	{2,0,0,0},{2,2,0,0},{0,2,0,0},{0,0,0,0}
}
},
Ts[4][4][4] =
{
{
	{0,2,0,0}, {2,2,2,0}, {0,0,0,0}, {0,0,0,0}
},
{
	{2,0,0,0},{2,2,0,0},{2,0,0,0},{0,0,0,0}
},
{
	{2,2,2,0},{0,2,0,0},{0,0,0,0},{0,0,0,0}
},
{
	{0,2,0,0},{2,2,0,0},{0,2,0,0},{0,0,0,0}
}
},
ps[4][4][4] =
{
{
	{2,2,2,2}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}
},
{
	{2,0,0,0},{2,0,0,0},{2,0,0,0},{2,0,0,0}
},
{
	{2,2,2,2},{0,0,0,0},{0,0,0,0},{0,0,0,0}
},
{
	{2,0,0,0},{2,0,0,0},{2,0,0,0},{2,0,0,0}
}
};
int currentBlockS[4][4] = { 0 };     // 在每次都复制现在的方块
int turns = 0;
IMAGE currentBlock, nextBlock;
int currentBlock_select, nextBlock_select;
int a[35][21];
int positionY = 2;                       // 方块落下的初始位置是2
int positionX = 0;
bool hasBlock = 0;   // 首先是没有block的
bool start_flag = 0;   // 游戏开始判断
bool sole_flag = 1;   // 触低判断
char score[5] = "0";
char rows[5] = "0";
int scoreValue = 0;
int rowsValue = 0;
void drawFrame();    // 画好框架
void drawMap();
void writeText();
void printData(char *scoreS, char* rows);    // 输出你的得分数
void get_start();
void load_block();
void blocks();
void block_drop(int speed);
void display();
void listenKeyBoard();
void blockRemove();
int main()
{
	initgraph(800, 640, SHOWCONSOLE);
	setfillcolor(RGB(176, 196, 222));
	srand((unsigned)time(NULL));
	currentBlock_select = rand() % 7 + 1;
	blocks();    // 加载方块
	drawFrame();
	do {
		get_start();
		sole_flag = 0;        // 落地了跳出循环后再赋值为0，加载一个方块
		positionY = 2;
		do {          // 如果没有落地就一直降落
			load_block();        // 使用现在的坐标复制current方块的形状
			display();         // 一定要在load_block之后，block_drop之前
			block_drop(230);     // 把地图上的2清除 ， 坐标获得加一，或者变为1
			// 后面的地图上是没有2的，而且positionY是+1的
			listenKeyBoard();
			blockRemove();
			listenKeyBoard();   // 来两个listen，提高灵敏度
		} while (!sole_flag);
		currentBlock_select = nextBlock_select;       // 等于下次的
	} while (start_flag);
	getchar();
	closegraph();
}
void drawFrame() {
	drawMap();
	writeText();
}            // 画出基本框架
void printData(char * scoreS, char* rows) {
	clearrectangle(280, 120, 380, 155);
	clearrectangle(280, 240, 380, 275);
	int i = 0;
	while (scoreS[i]) {
		outtextxy(280 + 20 * i, 120, scoreS[i]);
		i++;
	}
	int j = 0;
	while (rows[j]) {
		outtextxy(280 + 20 * j, 240, rows[j]);
		j++;
	}
}         // 分数系统
void blocks() {               // 加载下一个方块
	loadimage(&b, L"方块.png", 40, 40);
	loadimage(&L, L"L.png", 60, 40);
	loadimage(&d_L, L"反L.png", 60, 40);
	loadimage(&z, L"z.png", 60, 40);
	loadimage(&d_z, L"反z.png", 60, 40);
	loadimage(&T, L"T.png", 60, 40);
	loadimage(&p, L"1.png", 80, 20);
}
void writeText() {
	TCHAR scoreNotice[] = _T("你的分数 ： ");
	TCHAR rowsNotice[] = _T("已消除行数 ： ");
	// 设置字体样式
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 9;
	_tcscpy_s(f.lfFaceName, _T(""));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	outtextxy(265, 80, scoreNotice);
	outtextxy(265, 200, rowsNotice);

	f.lfHeight = 50;
	f.lfWidth = 30;
	settextstyle(&f);
   
	outtextxy(480, 100, _T("俄罗斯方块"));

	f.lfHeight = 35;
	f.lfWidth = 20;
	settextstyle(&f);
	
	outtextxy(480, 300, _T("翻转 W "));
	outtextxy(480, 400, _T("左 A  右 D"));
	outtextxy(480, 500, _T("快速下落 S"));
	f.lfUnderline = 1;
	settextstyle(&f);
	outtextxy(480, 200, _T("开始游戏"));
}
void get_start() {
	while (1) {    // 监听鼠标
		if (start_flag)          // 首先判断
			break;
		m = GetMouseMsg();
		if (m.x >= 480 && m.x <= 640 && m.y >= 200 && m.y <= 235) {     // 在开始游戏范围
			if (!start_flag && m.mkLButton) {
				printf("游戏开始");               // 设置替换文字为 暂停
				start_flag = 1;
				clearrectangle(480, 200, 640, 235);
				break;
			}
		}
	}
}
void drawMap() {
	int i, j;
	IMAGE bg;    // 一个猫的背景
	loadimage(&bg, L"miao.jpeg", 800, 640);
	putimage(0, 0, &bg);
	setbkcolor(WHITE);
	for (i = 1; i < 35; i++) {
		for (j = 1; j < 21; j++) {
			if ((i == 1 || i == 29 || j == 1 || j == 20 || j == 12) && i < 30) {
				if (j == 1) {

					printf("\n#");
					a[i][j] = 1;
				}
				else{
					printf("#");
					a[i][j] = 1;
				}
				int x = 20 * j;
				int y = 20 * i;  // 定义x ， y坐标
				fillrectangle(x, y, x + 20, y + 20);
			}
			else {
				printf(" ");
				a[i][j] = 0;
			}
		}
	}
}
void load_block() {               // 加载方块
	if (!hasBlock) {          // 如果不存在block了，就加载出来一个
		nextBlock_select = rand() % 7 + 1;   // 获取方块  
		clearrectangle(280, 400, 380, 480);
		switch (nextBlock_select) {
		case 1: {
			setfillcolor(RGB(186, 85, 211));
			nextBlock = b;
			putimage(285, 400, &nextBlock);
		}break;
		case 2: {
			setfillcolor(RGB(0, 139, 139));
			nextBlock = L;
			putimage(285, 400, &nextBlock);
		}break;
		case 3: {
			setfillcolor(RGB(240, 128, 128));
			nextBlock = d_L;
			putimage(285, 400, &nextBlock);
		}break;
		case 4: {
			setfillcolor(RGB(192, 14, 235));
			nextBlock = z;
			putimage(285, 400, &nextBlock);
		}break;
		case 5: {
			setfillcolor(RGB(143, 188, 143));
			nextBlock = d_z;
			putimage(285, 400, &nextBlock);
		}break;
		case 6: {
			setfillcolor(RGB(189, 183, 107));
			nextBlock = T;
			putimage(285, 400, &nextBlock);
		}break;
		case 7: {
			setfillcolor(RGB(169, 169, 169));
			nextBlock = p;
			putimage(285, 400, &nextBlock);
		}break;
		}                 // 只在下次方块的时候使用
	}
	switch (currentBlock_select) {
	case 1: {    // 这是方块
		currentBlock = b;
		if (!hasBlock) {     // 如果没有方块，这个X就应该变 , 还有一种方式就是，在左右键更改这个X
			hasBlock = 1;
			positionX = rand() % 9 + 2;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				currentBlockS[i][j] = bs[currentTurns][i][j];
			}                        // 赋值给现在的方块
		}
	}break;
	case 2: {     // 这是L型
		currentBlock = L;
		if (!hasBlock) {
			hasBlock = 1;
			positionX = rand() % 8 + 2;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				currentBlockS[i][j] = Ls[currentTurns][i][j];
			}                        // 赋值给现在的方块
		}
	}break;
	case 3: {    // 这是倒L
		currentBlock = d_L;
		if (!hasBlock) {
			hasBlock = 1;
			positionX = rand() % 8 + 2;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				currentBlockS[i][j] = d_Ls[currentTurns][i][j];
			}                        // 赋值给现在的方块
		}
	}break;
	case 4: {    // 这是z型
		currentBlock = z;
		if (!hasBlock) {
			hasBlock = 1;
			positionX = rand() % 8 + 2;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				currentBlockS[i][j] = zs[currentTurns][i][j];
			}                        // 赋值给现在的方块
		}
	}break;
	case 5: {     // 这是倒z
		currentBlock = d_z;
		if (!hasBlock) {
			hasBlock = 1;
			positionX = rand() % 8 + 2;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				currentBlockS[i][j] = d_zs[currentTurns][i][j];
			}                        // 赋值给现在的方块
		}
	}break;
	case 6: {   // 这是T型
		currentBlock = T;
		if (!hasBlock) {
			hasBlock = 1;
			positionX = rand() % 8 + 2;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				currentBlockS[i][j] = Ts[currentTurns][i][j];
			}                        // 赋值给现在的方块
		}
	}break;
	case 7: {    // 这是一型
		currentBlock = p;
		if (!hasBlock) {
			hasBlock = 1;
			positionX = rand() % 7 + 2;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				currentBlockS[i][j] = ps[currentTurns][i][j];
			}                        // 赋值给现在的方块
		}
	}break;
	}
	int m = 0, n = 0;
	for (int i = positionY; i < (positionY + 4); i++, m++) {      // 在指定区域复制方块地图
		n = 0;
		for (int j = positionX; j < (positionX + 4); j++, n++) {
			if (a[i][j] == 0)
				a[i][j] = currentBlockS[m][n];
			else if (a[i][j] == 1 && currentBlockS[m][n] == 2 && i < 5) {            // 如果新来的方块撞到了,
				start_flag = 0; // 游戏结束
			}
		}
	}
}
void block_drop(int speed) {     // 实现下降功能  ， 移动在监控里做  , speed在sleep中控
	for (int i = 29; i > 1; i--) {    // 从下往上检查
		for (int j = 2; j < 12; j++) {
			if (a[i][j] == 1 && a[i - 1][j] == 2) {                // 自由落下触低情况
				sole_flag = 1;
				hasBlock = 0;
			}
		}
	}
	if (sole_flag) {       // 如果触底则全部变为1.
		for (int i = 28; i > 1; i--) {
			for (int j = 2; j < 12; j++) {
				if (a[i][j] == 2) {
					a[i][j] = 1;
				}
			}
		}
	}
	else {
		for (int i = 29; i > 1; i--) {
			for (int j = 2; j < 12; j++) {
				if (a[i][j] == 0 && a[i - 1][j] == 2) {
					a[i - 1][j] = 0;
				}       // 把所有的2都清除，再把postionY加一
			}
		}
		positionY += 1;
	}
	Sleep(speed);      // 控制速度
}
void display() {           // 显示方块
	printData(score, rows);
	clearrectangle(40, 40, 240, 580);       // 每次执行先刷屏
	for (int i = 28; i > 1; i--) {
		for (int j = 2; j < 12; j++) {
			int x = j * 20;
			int y = i * 20;
			if (a[i][j] == 1 || a[i][j] == 2) {
				fillrectangle(x, y, x + 20, y + 20);
			}
		}
	}
}
void listenKeyBoard() {
	if (_kbhit()) {
		int c = _getch();
		switch (c) {
		case 'w': {           // 直接在全局变量的方块改了如何
			if (currentTurns < 3)
				currentTurns += 1;
			else
				currentTurns = 0;      // 3之后是0
			bool crushed = 0;
			int currentBlockSCopy[4][4];
			for (int i = 0; i < 4; i++) {         // 先做一个复制
				for (int j = 0; j < 4; j++) {
					currentBlockSCopy[i][j] = currentBlockS[i][j];
				}
			}
			switch (currentBlock_select) {
			case 1: {
				for (int i = 0; i < 4; i++) {        // 先全部赋值
					for (int j = 0; j < 4; j++) {
						currentBlockSCopy[i][j] = bs[currentTurns][i][j];
					}
				}
			}break;
			case 2: {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						currentBlockSCopy[i][j] = Ls[currentTurns][i][j];
					}
				}
			}break;
			case 3: {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						currentBlockSCopy[i][j] = d_Ls[currentTurns][i][j];
					}
				}
			}break;
			case 4: {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						currentBlockSCopy[i][j] = zs[currentTurns][i][j];
					}
				}
			}break;
			case 5: {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						currentBlockSCopy[i][j] = d_zs[currentTurns][i][j];
					}
				}
			}break;
			case 6: {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						currentBlockSCopy[i][j] = Ts[currentTurns][i][j];
					}
				}
			}break;
			case 7: {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						currentBlockSCopy[i][j] = ps[currentTurns][i][j];
					}
				}
			}break;
			default: {}break;
			}
			// 判断是否超出界限
			int m = 0, n = 0;
			for (int i = positionY; i < (positionY + 4); i++, m++) {
				n = 0;
				for (int j = positionX; j < (positionX + 4); j++, n++) {
					if (currentBlockSCopy[m][n] == 2 && a[i][j] == 1) {
						crushed = 1;               // 方块的移动好像没有跳跃的现象，所以不考虑超出边界而不撞边界
					}
				}
			}
			if (!crushed) {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						currentBlockS[i][j] = currentBlockSCopy[i][j];
					}
				}
			}
			else {
				currentTurns -= 1;
			}
		}break;
		case 'a': {
			bool crushed = 0;
			int m = 0, n = 0;
			for (int i = positionY; i < (positionY + 4); i++, m++) {
				n = 0;
				for (int j = positionX - 1; j < (positionX + 3); j++, n++) {       // positionX预先往左偏移
					if (currentBlockS[m][n] == 2 && a[i][j] == 1) {
						crushed = 1;               // 方块的移动好像没有跳跃的现象，所以不考虑超出边界而不撞边界
					}
				}
			}
			if (!crushed) {
				positionX -= 1;
			}
		}break;
		case 's': {
			int i = 0, j = 0;
			for (i = 2; i < 28; i++) {
				for (j = 2; j < 12; j++) {
					if (a[i][j] == 1)
						goto loop;
				}
			}
		loop: if (positionY < (i - 5)) {
			positionY += 4;
		}
		}break;
		case 'd': {         // 在移动赋值的时候，会有判断是否在边界上的 ， 1 ： 找到最右端
			bool crushed = 0;
			int m = 0, n = 0;
			for (int i = positionY; i < (positionY + 4); i++, m++) {
				n = 0;
				for (int j = positionX + 1; j < (positionX + 5); j++, n++) {       // positionX预先往左偏移
					if (currentBlockS[m][n] == 2 && a[i][j] == 1) {
						crushed = 1;               // 方块的移动好像没有跳跃的现象，所以不考虑超出边界而不撞边界
					}
				}
			}
			if (!crushed) {
				positionX += 1;
			}
		}break;
		default: {

		}break;
		}
	}
}
void blockRemove() {
	bool full_flag = 1;   // 一行是否满了
	int currentLine = 0;
	int times = 0;    // 连续消除次数
	int i = 0, j = 0;
	for (i = 2; i < 29; i++) {

		for (j = 2; j < 12; j++) {         // 这是一行
			if (a[i][j] == 0) {   // 如果有空位，直接否定
				full_flag = 0;
			}
		}

		if (full_flag) {    // 此时的i是当前行
			times += 1;
			currentLine = i;      // 当前行为i,这里有用到i，考虑作用域把i和j先声明
			for (int n = 2; n < 12; n++) {
				a[currentLine][n] = 0;        //  遍历当前行，全部清零
			}
			rowsValue += 1;
			scoreValue += (int)80 * (1.2 * times - 1);  // 逐渐增高的分数加成
			// 全部向下移一下
			for (int m = 28; m > 2; m--) {      
				for (int n = 2; n < 12; n++) {
					a[m][n] = a[m - 1][n];
					a[m - 1][n] = 0;
				}
			}
		}
		else {
			full_flag = 1;
		}
	}
	_itoa_s(scoreValue, score, 10);         // 转化到score里面去;
	_itoa_s(rowsValue, rows, 10);
}