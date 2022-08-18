#include<stdio.h>
#include<math.h>
#include<malloc.h>
#define MAXVALUE 1000                              //最大权值
#define MAXBIT 20                                  //哈夫曼编码最大长度

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
    int bit[10];                                   //位串
    int start;                                    //编码在位串中的起始位置
    float ch;       
}Hcodetype;

void select(Htreetype t[], int k, int *p1, int *p2)  //选择权值最小的结点
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
void HuffmanTree(Htreetype t[])                  //构造哈夫曼树
{
    int i, p1, p2;
	int a = t[0].nm[0],b = t[0].nm[1];
	float f, e;
    p1 = p2 = 0;
	for(;;)
	{
		for (i = 0,e =0; i < a; i++,e+=f)			//输入字符和对应的权值
		{
			printf("请输入第%d个概率", i + 1);
			scanf("%f", &f);
			t[i].ch = f;
			t[i].weight = f*100;
		}
		if(fabs(1-e)<0.00001)
			break;
		if(e>1)
			printf("概率和大于1，输入错误,请重新输入\n");
	}
    for (i = a; i < b; i++)			//构造哈夫曼树
    {
        select(t, i, &p1, &p2);
        t[p1].parent = i;
        t[p2].parent = i;
        t[i].Lchild = p1;
        t[i].Rchild = p2;
        t[i].weight = t[p1].weight + t[p2].weight;
    }
}
void HuffmanCode(Hcodetype code[],Htreetype t[])        //哈夫曼编码
{
    int i, c, p;
    Hcodetype cd;      //缓冲变量，暂时存储
    HuffmanTree(t);
    for (i = 0; i < t[0].nm[0]; i++)
    {
        cd.start =t[0].nm [0];
        cd.ch = t[i].ch;
        c = i;               //从叶子结点向上
        p = t[i].parent;     //t[p]是t[i]的双亲
        while (p != -1)
        {
            cd.start--;
            if (t[p].Lchild == c)
                cd.bit[cd.start] = '1';		//左子树编为1
            else
                cd.bit[cd.start] = '0';		//右子树编为0
            c = p;		//移动
            p = t[c].parent;
        }
        code[i] = cd;		//第i+1个字符的编码存入code
    }
}
void show(Htreetype t[], Hcodetype code[])
{
    int i, j, a;
	Hcodetype *dayin=code,zhongzh;
	int b[15];
	float c=0,d=0;
	a=t[0].nm [0];
	printf("\n各概率的霍夫曼码为：\n");
	for(i=0;i<a;i++)
	{
		for(j=i;j<a;j++)
			if(dayin[i].ch <dayin[j].ch )		//排序
				zhongzh=dayin[i],dayin[i]=dayin[j],dayin[j]=zhongzh;
        printf("\t%.2f: ", dayin[i].ch);
        for (j = code[i].start; j<a; j++)
			printf("%c ", code[i].bit[j]);
		b[i]=j-code[i].start;
		c=c+b[i]*dayin[i].ch;
        printf("\n");
	}
	printf("\n各概率的码字长为\n");
	for(i=0;i<a;i++)
	{
		d=d-dayin[i].ch*log10(dayin[i].ch)/log10(2);
		printf("\t%.2f: %d\n", dayin[i].ch,b[i]);
	}
	printf("\n平均码长为：%.4f\n\n信源熵为：%.4f\n\n编码效率为：%.4f\n\n",c,d,d/c);
}
void main()
{
	int a, i;
	Htreetype t[100];
	Hcodetype code[15];
	printf("请输入要求哈夫曼编码的概率个数\n");
	scanf("%d",&a);
	for (i = 0; i <(2*a-1); i++)			//初始化
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

