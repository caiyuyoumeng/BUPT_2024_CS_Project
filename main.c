#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//��ת�ǶȾ�Ϊ˳ʱ����ת
void InitSquare(int(*Square)[4]);//��ʼ������
void ModeSpinSquare(int(*Square)[4], char mode, int spin);//���ڻ�ȡ��ת��ķ�����״
void AddSquare(int (*Square)[4], int (*Area)[20], int index);//����ѵ�
void Move(int (*Area)[20]);//��������
int Remove(int (*Area)[20]);//����÷�
int GameoverJudge(int (*Area)[20]);//�����ж�
int AssessScore(int (*Area)[20], int spin, char mode, int index);//��������
void ShowArea(int index, int spin, int score, int (*Area)[20]);//��ʾ��ǰ��Ϸ����״̬
int main()
{
	char mode;//���ڼ�¼������״
	char mode1;//���ڼ�¼�ʼ�ĵ�һ������
	int spin;//���ڼ�¼��ת��ʽ
	int index;//���ڼ�¼�������λ��
	int score = 0;//���ڼ�¼�÷�
	int Area[10][20];//��Ϸ����
	for (int i = 0;i < 10;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			Area[i][j] = 0;
		}
	}//��������ʼ�����÷�������
	int Square[4][4];//���ڴ�ŷ���
	scanf("%c", &mode1);
	scanf("%c", &mode);
	while (GameoverJudge(Area))
	{
		int Score = -100000000;
		int arr[4] = { 0,270,180,90 };//���ڴ���ǶȲ���

		for (int j = 0;j < 4;j++)
		{
			int max = 0;
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
	for (int i = 0;i < 10;i++)//���ø߶Ȳ�߶�������
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
	for (int i = 0;i < 10;i++)//���ÿն�����
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
				score = score - 50;//100Ϊ���Ĳ���
			}
		}
	}
	for (int i = 0;i < 10;i++)
	{
		score = score - 2 * count[i];//2Ϊ�߶ȵĲ���
	}
	for (int i = 0;i < 9;i++)
	{
		if (count[i] >= count[i + 1])
		{
			score = score - 10 * (count[i] - count[i + 1]);//10Ϊ�߶Ȳ�Ĳ���
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


int GameoverJudge(int (*Area)[20])//����0��ʾ����������1��ʾ����
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
}//�ж��Ƿ񳬳��߶�����
void Move(int (*Area)[20])//�������������ƶ�����
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
}//����ʵ�������������

int Remove(int (*Area)[20])//����ֵΪ�÷�
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
}//���ڼ���һ�������еĵ÷�



void AddSquare(int (*Square)[4], int (*Area)[20], int index)
{
	for (int i = 15;i >= 1;i--)//i��ʾ����������һ�����ڵ���
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
}//����ʵ�ַ���ѵ�,����ֵ���ڽ�����������ʵ������

void InitSquare(int(*Square)[4])
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			Square[i][j] = 0;
		}
	}
}//��ʼ����������
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
}//��ȡ��ת��ķ�����״
void ShowArea(int index, int spin, int score, int (*Area)[20])
{
	printf("%d %d\n", spin / 90, index);
	//ˢ�»�����
	fflush(stdout);
	printf("%d\n", score);
	//ˢ�»�����
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
