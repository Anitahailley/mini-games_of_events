#include<stdio.h>
#include<math.h>

#define RL 35
#define RX 85
#define GS 5
#define GM 50
#define GL 500
#define Y 1
#define ZS 3
#define ZM 22
#define ZL 105

void r_x(double materials[], int buff[])
{
	materials[2] = materials[1];
	materials[1] = 0;
	buff[0] = 1;
}
void g_s(double materials[])
{
	materials[4] = materials[3];
	materials[7] = materials[7] + materials[3] * 1;								//额外产出 1 倍沙伊纳
	materials[7] = ceil(materials[7]);											//向上取整
	materials[4] = ceil(materials[4]);
	materials[3] = 0;
}
void g_m(double materials[])
{
	materials[5] = materials[4] * 4 / 5;
	materials[7] = materials[4] / 5 + materials[4] * 1.6 + materials[7];		//额外产出 1.6 倍沙伊纳
	materials[7] = ceil(materials[7]);
	materials[5] = ceil(materials[5]);
	materials[4] = 0;
}
void g_l(double materials[])
{
	materials[6] = materials[5] * 7 / 10;
	materials[7] = materials[5] * 3 / 10 + materials[5] * 1.4 + materials[7];	//额外产出 1.4 倍沙伊纳
	materials[7] = ceil(materials[7]);
	materials[6] = ceil(materials[6]);
	materials[5] = 0;
}
void y_s(double materials[])
{
	materials[7] = ceil(materials[7]);											//向上取整
	materials[7] = materials[7] * 5;
}
void y_m(double materials[])
{
	materials[7] = ceil(materials[7]);
	materials[7] = materials[7] * 8;
}
void y_l(double materials[], int buff[])
{
	materials[7] = ceil(materials[7]);
	materials[7] = materials[7] * 9;
	buff[4] = 1;
}
void z_s(double materials[], int buff[])
{
	materials[9] = (materials[8] + materials[7]) / 2;
	materials[9] = ceil(materials[9]);											//向上取整
	materials[7] = 0;
	materials[8] = 0;
	buff[1] = 1;

}
void z_m(double materials[], int buff[])
{
	materials[10] = (materials[9] + materials[4]) / 2;
	materials[10] = ceil(materials[10]);
	materials[4] = 0;
	materials[9] = 0;
	buff[2] = 1;
}
void z_l(double materials[], int buff[])
{
	materials[11] = (materials[10] + materials[1]) / 2;
	materials[11] = ceil(materials[11]);
	materials[1] = 0;
	materials[10] = 0;
	buff[3] = 1;
}
void jiagong(int x, int* p_unused_console, double materials[], int buff[], int j)
{
	switch (x)
	{
	case 0:
		(*p_unused_console)++;
		break;
	case 1:
		r_x(materials, buff);
		break;
	case 2:
		g_s(materials);
		break;
	case 3:
		g_m(materials);
		break;
	case 4:
		g_l(materials);
		break;
	case 8:
		y_s(materials);
		break;
	case 9:
		y_m(materials);
		break;
	case 10:
		y_l(materials, buff);
		break;
	case 5:
		z_s(materials, buff);
		break;
	case 6:
		z_m(materials, buff);
		break;
	case 7:
		z_l(materials, buff);
		break;
	case 11:
		printf("未解锁第%d个操作台\n", j + 1);
		break;
	default:
		printf("第%d个操作台输入了无效的加工工艺\n", j + 1);
		break;
	}
}
int score(double materials[], int buff[], int* p_unused_console)
{
	double total = 0;
	total = materials[1] * RL + materials[2] * RX + materials[3] + materials[4] * GS + materials[5] * GM + materials[6] * GL + materials[7] + materials[8] + materials[9] * ZS + materials[10] * ZM + materials[11] * ZL;
	for (int x = 0; x < 5; x++)
	{
		if (buff[x])
		{
			switch (x)
			{
			case 0:
				total = total + 5000 * *p_unused_console;
				break;
			case 1:
				total = total + (materials[9] + materials[10] + materials[11]) * 5;
				break;
			case 2:
				total = total + (materials[9] + materials[10] + materials[11]) * 15;
				break;
			case 3:
				if (materials[2] + materials[3] + materials[4] + materials[5] + materials[6] + materials[8] + materials[9] + materials[7] == 0)
				{
					total = total + materials[11] * 100;
				}
				break;
			case 4:
				total = total + materials[7];
				break;
			}
		}
	}
	return (int)total;
}
int main(void)
{
	double materials[12] = { 0 };
	int buff[5] = { 0 };
	int unused_console = 0, sc = 0, all_m = 0, times = 1;
	int* p_unused_console = &unused_console;

	int a[6] = { 0,0,0,0,0,0 };
	int* ap = a;
	do {
		printf("请输入现在的预估分数:");
		scanf_s("%d", &sc);
	} while (0);
	while (1)
	{
		for (int i = 0; i < 12; i++)
		{
			materials[i] = 0;
			if (i < 5)
				buff[i] = 0;
		}
		unused_console = 0, all_m = 0;
		printf("请输入待加工原料的数量(红、蓝、黄、紫)\n");
		scanf_s("%lf %lf %lf %lf", materials, materials + 3, materials + 7, materials + 8);
		all_m = (int)(materials[0] + materials[3] + materials[7] + materials[8]);
		materials[1] = materials[0] * 2 * 2 * 2.4;
		materials[1] = ceil(materials[1]);
		printf("红=%.1lf,蓝=%.1lf,黄=%.1lf,紫=%.1lf\n", materials[0], materials[3], materials[7], materials[8]);
		printf("\n请输入加工工艺：\n");
		for (int i = 0; i < 6; i++)
		{
			printf("第%d个操作台：", i + 1);
			scanf_s("%d", a + i);

		}
		for (int j = 0; j < 6; j++)
		{
			jiagong(a[j], p_unused_console, materials, buff, j);
		}
		printf("\n加工后，红  大=%8.1lf, 蓝  =%5.1lf, 黄=%8.1lf, 紫  =%8.1lf\n", materials[1], materials[3], materials[7], materials[8]);
		printf("        红特大=%8.1lf, 蓝小=%5.1lf,              紫小=%8.1lf\n", materials[2], materials[4], materials[9]);
		printf("                         蓝中=%5.1lf,              紫中=%8.1lf\n", materials[5], materials[10]);
		printf("                         蓝大=%5.1lf,              紫大=%8.1lf\n", materials[6], materials[11]);

		sc = sc + score(materials, buff, p_unused_console) - all_m;				//扣除初始总数原料的分数
		printf("第%d次累加的分数为:%d\n\n", times, sc);
		printf("是否需要累加本次分数？(输入1为是，0则为否): ");
		double answer = 0; int s = 0;
		if (!scanf_s("%lf", &answer))
		{
		Answer_unint:
			do {
				printf("错误,输入了字符,请重新输入:");
				getchar();
				s = scanf_s("%lf", &answer);
			} while (!s);
		}
	Wrong_answer:
		if (answer == 1)
		{
			printf("累加，");
			times++;
			continue;
		}
		else if (answer == 0)
		{
			printf("不累加，");
			sc = sc - score(materials, buff, p_unused_console) + all_m;
			continue;
		}
		else
		{
			do {
				printf("错误,输入了非0-2的整数,请重新输入:");
				while (getchar() != '\n');
				if (!scanf_s("%lf", &answer))
					goto Answer_unint;
			} while (answer != 0 && answer != 1);
			goto Wrong_answer;
		}
	}

	return 0;
}
