#include<stdio.h>
#include<math.h>
#include<malloc.h>
#define MAXVALUE 1000                              //���Ȩֵ
#define MAXBIT 20                                  //������������󳤶�

typedef struct                                   
{
	char nm[2];
    float ch;
    int weight;                                    
    int parent;                                    
    int Lchild, Rchild;
}Htreetype;

typedef struct
{
    int bit[10];                                   //λ��
    int start;                                    //������λ���е���ʼλ��
    float ch;       
}Hcodetype;

void select(Htreetype t[], int k, int *p1, int *p2)  //ѡ��Ȩֵ��С�Ľ��
{
    int small1, small2;
    int i;
    *p1 = *p2 = 0;
    small1 = small2 = MAXVALUE;
    for (i = 0; i < k; i++)
        if (t[i].parent == -1)
            if (t[i].weight < small1)
            {
                small2 = small1;
                small1 = t[i].weight;
                *p2 = *p1;
                *p1 = i;
            }
            else if (t[i].weight < small2)
            {
                small2 = t[i].weight;
                *p2 = i;
            }
}
void HuffmanTree(Htreetype t[])                  //�����������
{
    int i, p1, p2;
	int a = t[0].nm[0],b = t[0].nm[1];
	float f, e;
    p1 = p2 = 0;
	for(;;)
	{
		for (i = 0,e =0; i < a; i++,e+=f)			//�����ַ��Ͷ�Ӧ��Ȩֵ
		{
			printf("�������%d������", i + 1);
			scanf("%f", &f);
			t[i].ch = f;
			t[i].weight = f*100;
		}
		if(fabs(1-e)<0.00001)
			break;
		if(e>1)
			printf("���ʺʹ���1���������,����������\n");
	}
    for (i = a; i < b; i++)			//�����������
    {
        select(t, i, &p1, &p2);
        t[p1].parent = i;
        t[p2].parent = i;
        t[i].Lchild = p1;
        t[i].Rchild = p2;
        t[i].weight = t[p1].weight + t[p2].weight;
    }
}
void HuffmanCode(Hcodetype code[],Htreetype t[])        //����������
{
    int i, c, p;
    Hcodetype cd;      //�����������ʱ�洢
    HuffmanTree(t);
    for (i = 0; i < t[0].nm[0]; i++)
    {
        cd.start =t[0].nm [0];
        cd.ch = t[i].ch;
        c = i;               //��Ҷ�ӽ������
        p = t[i].parent;     //t[p]��t[i]��˫��
        while (p != -1)
        {
            cd.start--;
            if (t[p].Lchild == c)
                cd.bit[cd.start] = '1';		//��������Ϊ1
            else
                cd.bit[cd.start] = '0';		//��������Ϊ0
            c = p;		//�ƶ�
            p = t[c].parent;
        }
        code[i] = cd;		//��i+1���ַ��ı������code
    }
}
void show(Htreetype t[], Hcodetype code[])
{
    int i, j, a;
	Hcodetype *dayin=code,zhongzh;
	int b[15];
	float c=0,d=0;
	a=t[0].nm [0];
	printf("\n�����ʵĻ�������Ϊ��\n");
	for(i=0;i<a;i++)
	{
		for(j=i;j<a;j++)
			if(dayin[i].ch <dayin[j].ch )		//����
				zhongzh=dayin[i],dayin[i]=dayin[j],dayin[j]=zhongzh;
        printf("\t%.2f: ", dayin[i].ch);
        for (j = code[i].start; j<a; j++)
			printf("%c ", code[i].bit[j]);
		b[i]=j-code[i].start;
		c=c+b[i]*dayin[i].ch;
        printf("\n");
	}
	printf("\n�����ʵ����ֳ�Ϊ\n");
	for(i=0;i<a;i++)
	{
		d=d-dayin[i].ch*log10(dayin[i].ch)/log10(2);
		printf("\t%.2f: %d\n", dayin[i].ch,b[i]);
	}
	printf("\nƽ���볤Ϊ��%.4f\n\n��Դ��Ϊ��%.4f\n\n����Ч��Ϊ��%.4f\n\n",c,d,d/c);
}
void main()
{
	int a, i;
	Htreetype t[100];
	Hcodetype code[15];
	printf("������Ҫ�����������ĸ��ʸ���\n");
	scanf("%d",&a);
	for (i = 0; i <(2*a-1); i++)			//��ʼ��
	{
		t[i].nm[0] = a;
		t[i].nm[1] = 2*a-1;
		t[i].weight = 0;
		t[i].Lchild = -1;
		t[i].parent = -1;
		t[i].Rchild = -1;
	}
	HuffmanCode(code, t);
	show(t,code);
}

