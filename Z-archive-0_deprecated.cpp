#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MAX_ARRY_SIZE 100

bool bianliziju(int(**data)[MAX_ARRY_SIZE], int wzshu, int zjshu)
{
	int i = 0, j = 0, k = wzshu, tmp = 0, wzshutmp = 0;
	int mark = wzshu + 1, judge = 1, count = 0, kjd = 0;
	int(*stmp)[MAX_ARRY_SIZE] = (int(*)[MAX_ARRY_SIZE])malloc(sizeof(int[MAX_ARRY_SIZE]) * zjshu);
	int *status = (int *)malloc(sizeof(int) * wzshu);
	int gostatus = 1;
	for (count = 0; k > 0 || k==0 && status[k]==0; count++)
	{
		if (judge == 0)
		{
			do
			{
				k++;
				if (k == wzshu)
				{
					printf("count = %d\n", count);
					printf("The cnf file is unsat\n");
					return false;
				}
			} while (status[k] == 0);
			status[k] = 0;
			kjd++;
			if (kjd == wzshu * MAX_ARRY_SIZE)
			{
				printf("Space is not enough! count = %d\n", count);
				return false;
			}
			for (i = 0; i < zjshu; i++)
			{
				j = -1;
				tmp = 0;
				do
				{
					++j;
					if (data[kjd][i][j] <= k && data[kjd][i][j] >= -k)
					{
						stmp[i][tmp] = data[kjd][i][j];
						tmp++;
					}
					else if (data[kjd][i][j] > 0 && status[data[kjd][i][j] - 1] || data[kjd][i][j] < 0 && !status[-data[kjd][i][j] - 1])
					{
						stmp[i][0] = mark;
						break;
					}
				} while (data[kjd][i][j] != 0);
			}
		}
		if (status[k] == 0 && gostatus)
		{
			wzshutmp = (k + 1) * -1;
			for (i = 0; i < zjshu; i++)
			{
				j = -1;
				do
				{
					++j;
					data[kjd][i][j] = stmp[i][j];
				} while (stmp[i][j] != 0);
			}
		}
		else
		{
			k--;
			wzshutmp = k + 1;
			status[k] = 1;
			for (i = 0; i < zjshu; i++)
			{
				j = -1;
				do
				{
					++j;
					stmp[i][j] = data[kjd][i][j];
				} while (data[kjd][i][j] != 0);
			}
		}
		judge = 1;
		gostatus = 1;
		i = 0;
		while (i < zjshu)
		{
			j = 0;
			do
			{
				if (data[kjd][i][0] == mark)
					break;
				else if (data[kjd][i][0] == 0)
				{
					if (status[k] == 0)
					{
						judge = 0;
					}
					else
						status[k] = 0;
					break;
					//return false;
				}
				else if (data[kjd][i][j] == wzshutmp)
				{
					data[kjd][i][0] = mark;
					break;
				}
				else if (data[kjd][i][j] == -1 * wzshutmp)
				{
					tmp = j;
					do
					{
						data[kjd][i][j] = data[kjd][i][j + 1];
						j++;
					} while (data[kjd][i][j] != 0);
					if (data[kjd][i][0] == 0)
					{
						if (status[k] == 0)
						{
							judge = 0;
						}
						else
							status[k] = 0;
						break;
						//return false;
					}
					j = tmp - 1;
				}
				j++;
			} while (data[kjd][i][j] != 0);
			//printf("j = %d\tdata[kjd][i][j] = %d\t\n",  j, data[kjd][i][j], kjd, status[k]);
			//printf("i = %d\tk = %d\tkjd = %d\tstatus[k] = %d\n", i, k, kjd, status[k]);
			if (status[k] == 0 && data[kjd][i][0] == 0)
			{
				break;
			}
			++i;
		}
		if (i == zjshu)
			gostatus = 0;
		printf("i = %d\tk = %d\tkjd = %d\tstatus[k] = %d\n", i, k, kjd, status[k]);
	}
	printf("circle count = %d\n", count);
	printf("One of the anwsers is below. The No.1 to No.%d word's value is:\n", wzshu);
	for (i = 0; i < wzshu; i++)
	{
		if (i % MAX_ARRY_SIZE == 0)
			printf("\n");
		printf(" %d\t", status[i]);
	}
	return true;
}

bool wenjianduqu(char *filepath)
{
	int zijun, wenzin;
	FILE *fp = fopen(filepath, "r");
	if (fp == NULL)
	{
		printf("file or path error\n");
		printf("Press enter to exit........\n");
		getchar();
		exit(0);
	}
	char perline[1024];
	char c = fgetc(fp);
	while (c == 'c')
	{
		fgets(perline, 1024, fp);
		c = fgetc(fp);
	}
	if (c == 'p')
	{
		fscanf(fp, "%*s %d %d", &wenzin, &zijun);
		printf("wenzishu: %d, juzishu: %d.\n", wenzin, zijun);
	}
	int(**zijushu)[MAX_ARRY_SIZE] = (int(**)[MAX_ARRY_SIZE])malloc(sizeof(int(*)[MAX_ARRY_SIZE]) * wenzin * MAX_ARRY_SIZE);
	//int(*zijushu)[MAX_ARRY_SIZE] = (int(*)[MAX_ARRY_SIZE])malloc(sizeof(int[MAX_ARRY_SIZE]) * zijun);
	int i = 0, j = 0, k = 0, tmp = 0;
	for (k = 0; k < wenzin * MAX_ARRY_SIZE; k++)
	{
		zijushu[k] = (int(*)[MAX_ARRY_SIZE])malloc(sizeof(int[MAX_ARRY_SIZE]) * zijun);
	}
	for (i = 0; i < zijun; i++)
	{
		tmp = 1;
		j = 0;
		while (tmp)
		{
			k = 0;
			fscanf(fp, "%d", &zijushu[k][i][j]);
			tmp = zijushu[k][i][j];
			for (k = 0; k < wenzin * MAX_ARRY_SIZE; k++)
			{
				zijushu[k][i][j] = tmp;
			}
			j++;
			//printf("%d\t", tmp);
		}
		//printf("\n");
	}
	fclose(fp);
	//system("pause");

	bianliziju(zijushu, wenzin, zijun);
	//printf("\nPress enter to exit...............\n");
	//getchar();
	return 0;
}

int main()
{
	int tstart = clock();
	char cnfname[1024];
	printf("Please input the full path of you cnf file: \n");
	//scanf("%s", cnfname);
	//sscanf("D:\\pengp\\source\\repos\\shudu\\shudu\\satexample\\jizhunsuanli\\gongnengceshi\\s.cnf", "%s", cnfname);
	sscanf("D:\\pengp\\source\\repos\\shudu\\shudu\\satexample\\jizhunsuanli\\gongnengceshi\\u.cnf", "%s", cnfname);
	//sscanf("D:\\pengp\\source\\repos\\shudu\\shudu\\satexample\\manzusuanli\\S\\1.cnf", "%s", cnfname);
	//sscanf("D:\\pengp\\Documents\\keshe\\test.cnf", "%s", cnfname);
	//sscanf("D:\\pengp\\source\\repos\\shudu\\shudu\\satexample\\jizhunsuanli\\xingnengceshi\\aisMAX_ARRY_SIZE.cnf", "%s", cnfname);
	wenjianduqu(cnfname);
	int tend = clock();
	printf("\nThe time that the program takes is %d ms\n", tend - tstart);
	printf("\nPress enter to exit...............\n");
	getchar();
	return 0;
}