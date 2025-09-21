#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//旋转角度均为顺时针旋转
void InitSquare(int(*Square)[4]);//初始化方块
void ModeSpinSquare(int(*Square)[4], char mode, int spin);//用于获取旋转后的方块形状
void AddSquare(int (*Square)[4], int (*Area)[20], int index);//方块堆叠
void Move(int (*Area)[20]);//消除下落
int Remove(int (*Area)[20]);//计算得分
int GameoverJudge(int (*Area)[20]);//结束判断
int AssessScore(int (*Area)[20], int spin, char mode, int index);//用于评估
void ShowArea(int index, int spin, int score, int (*Area)[20]);//显示当前游戏区域状态
int main()
{
	char mode;//用于记录方块形状
	char mode1;//用于记录最开始的第一个方块
	int spin;//用于记录旋转方式
	int index;//用于记录方块放置位置
	int score = 0;//用于记录得分
	int Area[10][20];//游戏区域
	for (int i = 0;i < 10;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			Area[i][j] = 0;
		}
	}//建立并初始化放置方块区域
	int Square[4][4];//用于存放方块
	scanf("%c", &mode1);
	scanf("%c", &mode);
	while (GameoverJudge(Area))
	{
		int Score = -100000000;
		int arr[4] = { 0,270,180,90 };//用于储存角度参数

		for (int j = 0;j < 4;j++)
		{
			int max = 0;//用于确定可放置边界
			switch (mode1)
			{
			case 'I':
				switch (arr[j])
				{
				case 0:
					max = 6;
					break;
				case 270:
					max = 9;
					break;
				case 180:
					max = 6;
					break;
				case 90:
					max = 9;
					break;
				}
				break;
			case 'T':
				switch (arr[j])
				{
				case 0:
					max = 7;
					break;
				case 270:
					max = 8;
					break;
				case 180:
					max = 7;
					break;
				case 90:
					max = 8;
					break;
				}
				break;
			case 'O':
				switch (arr[j])
				{
				case 0:
					max = 8;
					break;
				case 270:
					max = 8;
					break;
				case 180:
					max = 8;
					break;
				case 90:
					max = 8;
					break;
				}
				break;
			case 'J':
				switch (arr[j])
				{
				case 0:
					max = 7;
					break;
				case 270:
					max = 8;
					break;
				case 180:
					max = 7;
					break;
				case 90:
					max = 8;
					break;
				}
				break;
			case 'L':
				switch (arr[j])
				{
				case 0:
					max = 7;
					break;
				case 270:
					max = 8;
					break;
				case 180:
					max = 7;
					break;
				case 90:
					max = 8;
					break;
				}
				break;
			case 'S':
				switch (arr[j])
				{
				case 0:
					max = 7;
					break;
				case 270:
					max = 8;
					break;
				case 180:
					max = 7;
					break;
				case 90:
					max = 8;
					break;
				}
				break;
			case 'Z':
				switch (arr[j])
				{
				case 0:
					max = 7;
					break;
				case 270:
					max = 8;
					break;
				case 180:
					max = 7;
					break;
				case 90:
					max = 8;
					break;
				}
				break;
			}
			for (int i = 0;i <= max;i++)
			{
				if (Score < AssessScore(Area, arr[j], mode1, i))
				{
					Score = AssessScore(Area, arr[j], mode1, i);
					spin = arr[j];
					index = i;
				}
			}
		}
		InitSquare(Square);
		ModeSpinSquare(Square, mode1, spin);
		AddSquare(Square, Area, index);
		score = score + Remove(Area);
		Move(Area);
		ShowArea(index, spin, score, Area);
		
		if (mode == 'X')
		{
			return 0;
		}
		mode1 = mode;
		scanf(" %c", &mode);
		if (mode == 'E')
		{
			return 0;
		}

	}

	return 0;
}
int AssessScore(int (*Area)[20], int spin, char mode, int index)
{
	int score = 0;
	int Square[4][4];
	InitSquare(Square);
	ModeSpinSquare(Square, mode, spin);
	int area[10][20];
	for (int i = 0;i < 10;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			area[i][j] = Area[i][j];
		}
	}
	AddSquare(Square, area, index);
	int count[10] = { 0,0,0,0,0,0,0,0,0,0 };
	for (int i = 0;i < 10;i++)//利用高度差及高度来减分
	{
		for (int j = 19;j >= 0;j--)
		{
			if (area[i][j] == 1)
			{
				count[i] = j + 1;
				break;
			}
		}
	}
	for (int i = 0;i < 10;i++)//利用空洞减分
	{
		int state = 0;
		for (int j = 19;j >= 0;j--)
		{
			if (state == 0 && area[i][j] == 1)
			{
				state = 1;
			}
			if (state == 1 && area[i][j] == 0)
			{
				score = score - 50;//100为洞的参数
			}
		}
	}
	for (int i = 0;i < 10;i++)
	{
		score = score - 2 * count[i];//2为高度的参数
	}
	for (int i = 0;i < 9;i++)
	{
		if (count[i] >= count[i + 1])
		{
			score = score - 10 * (count[i] - count[i + 1]);//10为高度差的参数
		}
		else
		{
			score = score - 10 * (count[i + 1] - count[i]);
		}
	}
	int Count = 0;
	for (int j = 0;j < 20;j++)
	{
		for (int i = 0;i < 10;i++)
		{


			if (area[i][j] == 0)
			{
				break;
			}
			if (i == 9)
			{
				Count++;
			}

		}
	}
	switch (Count)
	{
	case 1:
		score = score + 100 * Count;
		break;
	case 2:
		score = score + 110 * Count;
		break;
	case 3:
		score = score + 130 * Count;
		break;
	case 4:
		score = score + 150 * Count;
		break;
	}

	return score;
}


int GameoverJudge(int (*Area)[20])//返回0表示结束，返回1表示继续
{
	for (int i = 0;i < 10;i++)
	{
		for (int j = 15;j < 20;j++)
		{
			if (Area[i][j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}//判断是否超出高度限制
void Move(int (*Area)[20])//用于在消除后移动方块
{
	for (int j = 0;j < 15;j++)
	{
		for (int i = 0;i < 10;i++)
		{
			if (Area[i][j] == 0)
			{
				break;
			}
			if (i == 9)
			{
				for (int t = j;t < 19;t++)
				{
					for (int y = 0;y < 10;y++)
					{
						Area[y][t] = Area[y][t + 1];
					}
				}
				j--;
			}
		}
	}
}//用于实现消除后的下落

int Remove(int (*Area)[20])//返回值为得分
{
	int count = 0;
	int score;
	for (int j = 0;j < 15;j++)
	{
		for (int i = 0;i < 10;i++)
		{
			if (Area[i][j] == 0)
			{
				break;
			}
			if (i == 9)
			{
				count++;
			}
		}
	}
	switch (count)
	{
	case 0:
		score = 0;
		break;
	case 1:
		score = 100;
		break;
	case 2:
		score = 300;
		break;
	case 3:
		score = 500;
		break;
	case 4:
		score = 800;
		break;
	}
	return score;
}//用于计算一次消除中的得分



void AddSquare(int (*Square)[4], int (*Area)[20], int index)
{
	for (int i = 15;i >= 1;i--)//i表示方块最下面一行所在的行
	{
		for (int t = i;t < i + 4;t++)
		{
			for (int j = index;j < 4 + index && j < 10;j++)
			{
				if (Square[j - index][t - i] == 1 && Area[j][t - 1] == 1)
				{
					for (int r = index;r < 4 + index && r < 10;r++)
					{
						for (int y = i;y < 4 + i;y++)
						{
							if (Area[r][y] == 0 && Square[r - index][y - i] == 1)
							{
								Area[r][y] = Square[r - index][y - i];
							}
						}
					}
					return;
				}
			}
		}
	}


	for (int i = index;i < 4 + index && i < 10;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			if (Area[i][j] == 0 && Square[i - index][j] == 1)
			{
				Area[i][j] = Square[i - index][j];
			}
		}
	}
	return;
}//用于实现方块堆叠,返回值用于结束函数，无实际意义

void InitSquare(int(*Square)[4])
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			Square[i][j] = 0;
		}
	}
}//初始化方块数组
void ModeSpinSquare(int(*Square)[4], char mode, int spin)
{
	if (spin == 0)
	{
		switch (mode)
		{
		case 'I':
			Square[0][0] = 1;
			Square[1][0] = 1;
			Square[2][0] = 1;
			Square[3][0] = 1;
			break;
		case 'T':
			Square[0][0] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			Square[2][0] = 1;
			break;
		case 'O':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			break;
		case 'J':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[1][0] = 1;
			Square[2][0] = 1;
			break;
		case 'L':
			Square[0][0] = 1;
			Square[1][0] = 1;
			Square[2][0] = 1;
			Square[2][1] = 1;
			break;
		case 'S':
			Square[0][0] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			Square[2][1] = 1;
			break;
		case 'Z':
			Square[0][1] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			Square[2][0] = 1;
			break;
		}
	}
	else if (spin == 270)
	{
		switch (mode)
		{
		case 'I':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[0][2] = 1;
			Square[0][3] = 1;
			break;
		case 'T':
			Square[0][1] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			Square[1][2] = 1;
			break;
		case 'O':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			break;
		case 'J':
			Square[0][0] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			Square[1][2] = 1;
			break;
		case 'L':
			Square[0][2] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			Square[1][2] = 1;
			break;
		case 'S':
			Square[0][1] = 1;
			Square[0][2] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			break;
		case 'Z':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[1][1] = 1;
			Square[1][2] = 1;
			break;
		}
	}
	else if (spin == 180)
	{
		switch (mode)
		{
		case 'I':
			Square[0][0] = 1;
			Square[1][0] = 1;
			Square[2][0] = 1;
			Square[3][0] = 1;
			break;
		case 'T':
			Square[0][1] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			Square[2][1] = 1;
			break;
		case 'O':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			break;
		case 'J':
			Square[0][1] = 1;
			Square[1][1] = 1;
			Square[2][0] = 1;
			Square[2][1] = 1;
			break;
		case 'L':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[1][1] = 1;
			Square[2][1] = 1;
			break;
		case 'S':
			Square[0][0] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			Square[2][1] = 1;
			break;
		case 'Z':
			Square[0][1] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			Square[2][0] = 1;
			break;
		}
	}
	else if (spin == 90)
	{
		switch (mode)
		{
		case 'I':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[0][2] = 1;
			Square[0][3] = 1;
			break;
		case 'T':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[0][2] = 1;
			Square[1][1] = 1;
			break;
		case 'O':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			break;
		case 'J':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[0][2] = 1;
			Square[1][2] = 1;
			break;
		case 'L':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[0][2] = 1;
			Square[1][0] = 1;
			break;
		case 'S':
			Square[0][1] = 1;
			Square[0][2] = 1;
			Square[1][0] = 1;
			Square[1][1] = 1;
			break;
		case 'Z':
			Square[0][0] = 1;
			Square[0][1] = 1;
			Square[1][1] = 1;
			Square[1][2] = 1;
			break;
		}
	}
}//获取旋转后的方块形状
void ShowArea(int index, int spin, int score, int (*Area)[20])
{
	printf("%d %d\n", spin / 90, index);
	//刷新缓冲区
	fflush(stdout);
	printf("%d\n", score);
	//刷新缓冲区
	fflush(stdout);
	for (int j = 19;j >= 0;j--)
	{
		for (int i = 0;i < 10;i++)
		{
			printf("%d ", Area[i][j]);
		}
		printf("\n");
	}
}
