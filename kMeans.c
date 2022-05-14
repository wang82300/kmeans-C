//author : Zhuang Lee 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <math.h>
#define maxFileLength 256
#define data_path "D:\\Fast KMeans Tested Data Sets\\"
#define lable_path "D:\\initIDXForCenters\\"
#define out_path "D:\\kmeans\\out\\"
//#define N
//#define k
//#define d
//#define n ��maxRun
//�洢�������ݵ��ά��
//double **data = NULL; //N * d
//�洢���ĵ�
//double **centerPoint = NULL; //k * d
//double centerPoint[k][d];
//�洢���������ĵ�������Сֵ
//double *distance = NULL;
//double distance[N];
//�洢����ľ۴ط���
//int *clusters = NULL;
//int clusters[N]; //��洢ֵ�ķ�ΧΪ0-��k-1��
//N ��������
//d ����ά��
//k �۴ظ���
//n �㷨���д���
//double *objFunc = NULL;

int isCenterPointChange(double **matrix1, double **matrix2,int k,int d)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < d; j++)
		{
			if (matrix1[i][j] != matrix2[i][j])
				return -1;//false
		}
	}
	return 1;//true
}

//�����ֵ�������ĵ�,����centerPoint��
int Mean_value(int N, int d, int k, int *clusters, double **data, double **centerPoint,int flag)
{
	//int flag = -1;
	/*
	printf("\nԭʼ����start\n");
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < d; j++)
		{
			printf("%lf\t", centerPoint[i][j]);
		}
		printf("%\n");
	}
	printf("ԭʼ����end\n");
	*/
	double **centerPoint_temp = (double **)malloc(sizeof(double *) * k);
	for (int i = 0; i < k; i++)
	{
		centerPoint_temp[i] = (double *)malloc(sizeof(double) * d);
	}
	double *sum_values = (double *)calloc(d,sizeof(double));
	double **value_data = (double **)calloc(N,sizeof(double *));
	//double **values = (double **)malloc(sizeof(double *) * N);
	for (int i = 0; i < N; i++)
	{
		//values[i] = (double *)malloc(sizeof(double) * d);
		value_data[i] = (double *)calloc(d,sizeof(double));	 
	}

	for (int i = 0; i < k; i++)
	{
		//printf("i:%d\n", i);
		//��¼ÿ�����е����������
		int count = 0;
		//printf("��ʼ����\n");
		for (int j = 0; j < N; j++)
		{
			//printf("%d\n", clusters[j]);
			if (clusters[j] == i)
			{
				for (int q = 0; q < d; q++)
				{
					value_data[count][q] = data[j][q];
					//printf("value_data:%lf\t", value_data[count][q]);
				}
				//printf("%\n");
				count++;
			}
		}
		//����������������Ϊ�������������������Ϊ�㣬�����ֵ�����µĴ�����Ϊԭ���ġ�
		if (count != 0)
		{
			//printf("��ʼ���ֵ\n");
			for (int q = 0; q < d; q++)     //ͳ����
			{
				double sum = 0;
				for (int p = 0; p < count; p++) //ͳ����
				{
					sum += value_data[p][q];//�����еĺ�
				}
				sum /= count; //���ֵ
				sum_values[q] = sum;
				//printf("sum:%lf\t", sum);
			}
			//printf("%\n");
			//printf("��ʼ�������ĵ�\n");
			for (int j = 0; j < d; j++)
			{
				centerPoint_temp[i][j] = sum_values[j]; //�������ĵ�����
				//printf("centerPoint_temp:%lf\t", centerPoint_temp[i][j]);
			}
			//printf("\n");
		}
		else
		{
			for (int j = 0; j < d; j++)
			{
				centerPoint_temp[i][j] = centerPoint[i][j];
			}
			printf("��������");
		}
		
	}

	if (isCenterPointChange(centerPoint_temp,centerPoint,k,d) == -1) 
	{
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < d; j++)
			{
				centerPoint[i][j] = centerPoint_temp[i][j];
				//printf("centerPoint_temp:%lf\t", centerPoint_temp[i][j]);
			}
			//printf("\n");
		}
	}
	else
	{
		flag = 0;
	}
	/*
	printf("\n���º������start\n");
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < d; j++)
		{
			printf("%lf\t", centerPoint[i][j]);
		}
		printf("%\n");
	}
	printf("���º������end\n");
	*/
	free(sum_values);
	for (int i = 0; i < N; i++)
	{
		free(value_data[i]);
	}
	free(value_data);
	free(centerPoint_temp);
	return flag;
	//printf("end~~~");
}
//��Ҫ
void kMeans(int N, int d, int k, double **data ,double **centerPoint, double *distance, int *clusters)
{
	double *values = (double *)malloc(sizeof(double) * k);
	int flag = 1;
	//int counting = 0;
	while(flag)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < k; j++)
			{
				double distance_sum = 0;
				for (int x = 0; x < d; x++)
				{
					//printf("data:%lf\t", data[i][x]);
					//printf("centerPoint:%lf\t", centerPoint[j][x]);
					//distance_sum += pow((data[i][x] - centerPoint[j][x]), 2);
					//����ŷʽ����
					//printf("%f\t", centerPoint[j][x]);
					//distance_sum += (data[i][x] - centerPoint[j][x]) * (data[i][x] - centerPoint[j][x]);
					double temp = data[i][x] - centerPoint[j][x];
					distance_sum += temp * temp;
					//printf("distance_sum:%lf\n", distance_sum);
				}
				//values[j] = sqrt(distance_sum);
				values[j] = distance_sum;
			}
			double min = values[0];
			int temp = 0;
			for (int j = 1; j < k; ++j)
			{
				if (values[j] < min)
				{
					min = values[j];
					temp = j;
				}
			}
			//�洢�����������ĵ�������Сֵ
			distance[i] = min;
			//����
			clusters[i] = temp;
		}
		
		//�����ֵ���������ĵ�
		flag = Mean_value(N, d, k,clusters,data,centerPoint,flag);
		//printf("%d\t", flag);
		//counting++;
	}
	//printf("��������:%d\n", counting);
	free(values);
}
//���ƽ��
double squareError(int *clusters, double **centerPont, double **data, int k, int d, int N)
{
	double sum = 0;
	for (int i = 0; i < k; i++)
	{
		//��¼ÿ�����е���������� 
		//int count = 0;
		for (int j = 0; j < N; j++)//�˴����Ż�����Ϊ����ÿ�α������������㣬�ɽ�ÿ������ͬһ�ص���������뵽һ�������У����ÿռ任ȡʱ�䡣
		{
			//printf("%d\n", clusters[j]);
			if (clusters[j] == i)
			{
				for (int q = 0; q < d; q++)
				{
					sum += (centerPont[i][q] - data[j][q]) * (centerPont[i][q] - data[j][q]);
				}
				//count++;
			}
		}
	}
	return sum;
}
/*
double distance_all(double *distance, int N)
{
	double sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += distance[i];
	}
	return sum;
}
*/
void readFiletoArray(int N, int d, double **data,char *dataPath_all)
{
	FILE *fp = NULL;
	char *fileName = dataPath_all;
	if ((fp = fopen(fileName, "rt")) == NULL)
	{
		printf("fail to read");
		exit(1);
	}
	printf("\n��������~~\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < d; ++j)
		{
			fscanf(fp, "%lf", &data[i][j]);
			//printf("%f\t",data[i][j]);
		}
		//printf("\n");
	}
	printf("\ndata��һ��:\n");
	for (int i = 0; i < d; i++)
	{
		printf("%lf\t", data[0][i]);
	}

	printf("\ndata�ں�һ��\n");;
	for (int i = 0; i < d; i++)
	{
		printf("%lf\t", data[N-1][i]);
	}
	printf("\n");
	fclose(fp);
	printf("\n�����������!\n");
}

int **readLable(int k, int d,int n,char *lableNameAll)
{
	FILE *fp = NULL;
	int **value = (int **)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
	{
		value[i] = (int *)malloc(sizeof(int) * k);
	}
	char *fileName = lableNameAll;
	if ((fp = fopen(fileName, "rt")) == NULL)
	{
		printf("fail to read");
		exit(1);
	}
	printf("\n��ȡ��ǩ~~\n");
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				fscanf(fp, "%d", &value[i][j]);
				//printf("values:%d\t", value[i][j]);
			}
			//printf("\n");
		}
		printf("��ǩ��һ�У�\n");
		for (int i = 0; i < k; i++)
		{
			printf("%d\t", value[0][i]);
		}
		printf("\n��ǩ���һ��\n");
		for (int i = 0; i < k; i++)
		{
			printf("%d\t", value[n - 1][i]);
		}
		printf("\n");
		/*
		for (int i = 0; i < n; i++)
		{
			int temp = values[i] - 1;
			for (int j = 0; j < d; j++)
			{
				printf("%lf\t", data[temp][j]);
				centerPoint[i][j] = data[temp][j];
			}
			printf("\n");
		}*/
	fclose(fp);
	printf("\n�����ǩ���!\n");
	return value;
}
void toCenter(int x,int k,int **value,int d, double **data, double **centerPoint)
{
	//printf("\n�������ĵ�\n");
	for (int i = 0; i < k; i++)
	{
		//int temp = value[x][i] - 1;
		int temp = value[x][i];
		//printf("%d\n", temp);
		if (temp == -1)
			temp = 0;
		
		for (int j = 0; j < d; j++)
		{
			centerPoint[i][j] = data[temp][j];
			//printf("centerPoint:%lf\t", data[temp][j]);
		}
		//printf("\n");
	}
	//printf("\n�������\n");
}
void writeFile(int N, int d, int n, double *objFunc,char *outPath)
{
	FILE *fp;
	char *fileName = outPath;
	fp = fopen(fileName, "a+");
	if (fp != NULL)
	{
		printf("\n��ʼд��~~\n");
		for (int i = 0; i < n; i++) {
			printf(" %d\t %lf\n",(i+1), objFunc[i]);
			fprintf(fp, "%lf\n", objFunc[i]);
		}
	}
	fclose(fp);
	printf("д�����");
}
//�ϲ���������
char *mergeTwoCharArrays(char *array_one, char *array_two)
{
	char *temp = (char *)malloc(sizeof(char) * (strlen(array_one) + strlen(array_two) + 1));
	int n = 0;
	for (int i = 0; i < strlen(array_one); i++)
	{
		temp[i] = array_one[i];
		n = i;
	}
	for (int i = 0; i < strlen(array_two); i++)
	{
		temp[++n] = array_two[i];
	}
	temp[n + 1] = '\0';
	//printf("%s\n", temp);
	return temp;
}

int main()
{
	int N, k, d, n;
	char dataName[maxFileLength];
	printf("�������ݼ�����dataName;");
	scanf("%s", dataName);
	printf("������������N:");
	scanf("%d", &N);
	printf("�㷨���д���(��󲻳���50)n:");
	scanf("%d", &n);
	printf("����������k:");
	scanf("%d", &k);
	printf("��������ά��d:");
	scanf("%d", &d);

	if (N > 1 && d > 1 && k > 0 && n <= 50);
	else
	{
		printf("��ֵ����");
		return;
	}

	//---------------�������ݼ��ļ���start----------------
	char *dataPath_all = NULL;
	char *data_temp = NULL;
	char *dataName_pre = data_path;
	data_temp = mergeTwoCharArrays(dataName_pre, dataName);
	char data_format_txt[] = ".txt";
	dataPath_all = mergeTwoCharArrays(data_temp, data_format_txt);
	//--------------�������ݼ��ļ���end--------------------

	//---------------�����ǩ�ļ���start-------------------
	char *lableNameAll = NULL;
	char *lableName_pre = lable_path;
	char *lable_temp_N = NULL;
	char *lable_temp_C = NULL;
	char *lable_temp = NULL;
	char lable_N[] = "N=";
	char lable_C[] = "_c=";
	char lable_format_txt[] = "_Runs=50.txt";
	char *str_N[1];
	char *str_C[1];
	sprintf(str_N, "%d", N);
	sprintf(str_C, "%d", k);
	lable_temp_N = mergeTwoCharArrays(lable_N, str_N);
	lable_temp_C = mergeTwoCharArrays(lable_C, str_C);
	lable_temp = mergeTwoCharArrays(lable_temp_N, lable_temp_C);
	//��ǩȫ��
	lable_temp = mergeTwoCharArrays(lable_temp, lable_format_txt);
	lableNameAll = mergeTwoCharArrays(lableName_pre, lable_temp);
	//----------------�����ǩ�ļ���end-----------------


	//---------------���ݳ�ʼ��---------------------
		double **data = NULL;
		double **centerPoint = NULL;
		double *distance = NULL;
		double *objFunc = NULL;
		int *clusters = NULL;
		printf("\n���ݿռ��ʼ��~~\n");
		data = (double **)malloc(sizeof(double *) * N);
		for (int i = 0; i < N; i++)
		{
			data[i] = (double *)malloc(sizeof(double) * d);
		}
		readFiletoArray(N, d,data,dataPath_all);
		printf("data��ʼ�����\n");
		centerPoint = (double **)malloc(sizeof(double *) * k);
		for (int i = 0; i < k; i++)
		{
			centerPoint[i] = (double *)malloc(sizeof(double) * d);
		}
		printf("centerPoint�ռ��ʼ�����\n");
		/*for (int i = 0; i < k; ++i)
		{
			for (int j = 0; j < d; ++j)
			{
				centerPoint[i][j] = rand() % 100 + 1;
			}
		}
		printf("����������ĵ����\n");*/
		distance = (double *)malloc(sizeof(double) * N);
		for (int i = 0; i < N; i++)
		{
			distance[i] = 0;
		}
		printf("distance��ʼ�����Ĭ��Ϊ��\n");
		clusters = (int *)malloc(sizeof(int) * N);
		for (int i = 0; i < N; i++)
		{
			clusters[i] = -1;
		}
		printf("clusters��ʼ�����Ĭ�Ϸ���-1\n");

		printf("���ݿռ��ʼ����ɣ�\n");
		//����data�����ַ
		/*for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < d; ++j)
			{
				printf("%p\t",&data[i][j]);
			}
			printf("\n");
		}*/
		objFunc = (double *)calloc(n,sizeof(double));
		int temp = n;
		int **value = readLable(k, d, n,lableNameAll);
		//double objFunc = 0;
		//int flag;
		time_t start;
		double duration;
		start = clock();
		while (n)
		{
			toCenter((temp - n), k, value, d, data, centerPoint);
			kMeans(N, d, k,data, centerPoint, distance, clusters);
			objFunc[temp - n] = squareError(clusters,centerPoint,data,k,d,N);
			n--;
		}
		time_t end;
		end = clock();
		duration = (double)(end - start) / CLOCKS_PER_SEC;
		printf("CPUռ�õ�ʱ��;%fms", duration);

		//----------------���ɽ���ļ���start---------------
		time_t t;
		struct tm *st;
		//���ش�1970��1��1��0ʱ0��0�룬�����ڵĵ�����
		time(&t);
		st = localtime(&t);
		int year = st->tm_year + 1900;
		int month = st->tm_mon + 1;
		int day = st->tm_mday;
		int hour = st->tm_hour;
		int min = st->tm_min;
		int sec = st->tm_sec;
		char out_time[20];
		char middle[] = "-";
		sprintf(out_time, "%d%s%d%s%d%s%d%s%d%s%d", year, middle, month, middle, day, middle, hour, middle, min, middle, sec);

		char *outPath = NULL;
		char *str_dataName[maxFileLength];
		sprintf(str_dataName, "%s", dataName);
		//_c=k�������ʹ�������lable_temp_C
		outPath = mergeTwoCharArrays(str_dataName, lable_temp_C);
		char out_dim[] = "_dim=";
		char *out_temp_dim = NULL;
		char *str_dim[1];
		sprintf(str_dim, "%d", d);
		out_temp_dim = mergeTwoCharArrays(out_dim, str_dim);
		outPath = mergeTwoCharArrays(outPath, out_temp_dim);
		char out_dataNum[] = "_dataNum=";
		char *str_dataNum[1];
		char *out_temp_dataNum = NULL;
		sprintf(str_dataNum, "%d", N);
		out_temp_dataNum = mergeTwoCharArrays(out_dataNum, str_dataNum);
		outPath = mergeTwoCharArrays(outPath, out_temp_dataNum);
		char out_maxRunTimes[] = "_maxRunTimes=";
		char *str_maxRunTimes[1];
		sprintf(str_maxRunTimes, "%d", n);
		char *out_temp_maxRunTimes = NULL;
		out_temp_maxRunTimes = mergeTwoCharArrays(out_maxRunTimes, str_maxRunTimes);
		outPath = mergeTwoCharArrays(outPath, out_temp_maxRunTimes);
		char algorithm[] = "_KMeans_Ori_";
		outPath = mergeTwoCharArrays(outPath, algorithm);
		outPath = mergeTwoCharArrays(outPath, out_time);
		outPath = mergeTwoCharArrays(out_path, outPath);

		//-----------------���ɽ���ļ���end---------------

		writeFile(N, d, temp, objFunc,outPath);
		free(data);
		free(centerPoint);
		free(distance);
		free(clusters);
		free(objFunc);
		system("pause");
		return 0;
		
}
