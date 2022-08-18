#include<stdio.h>
#include<math.h>

void shengcheng(char g[][15],int n,int k)
{
	int i,j,c;
	printf("请输入生成矩阵\n");
	for(i=0;i<k;i++)
		for(c=0;;c=0)//纠错机制，保证为2进制
		{
			for(j=0;j<n;j++)
			{
				scanf("%c",&g[i][j]);
				if(j==(n-1))//消除回车键的影响
					fflush(stdin);
				if((g[i][j]!='0')&&(g[i][j]!='1'))
					c=1;
			}
			if(c==0)
				break;
			else
				printf("输入不为0或1，请重新输入第%d行\n",i+1);
		}
}
void erjin(char er[][15],int k)
{
	int i,j,a,l,b[33][15];
	for(i=1;i<pow(2,k);i++)
	{
		for(a=i,j=0;;j++)
		{
			b[i][j]=a-(a/2)*2;
			a=a/2;
			if(a==0)
				break;
		}
		for(l=k-j-1;j>=0;l++,j--)
			er[i][l]=b[i][j]+'0';
	}
}
void dayin(int k,int n,char yin[][15])
{
	int i,j;
	for(i=0;i<k;i++)
	{
		printf("\n\t");
		for(j=0;j<n;j++)
			printf("%c  ",yin[i][j]);
	}
}
int moer(char a,char b)
{
	if(a==b)
		return 0;
	else
		return 1;
}
void mazi(char er[][15],char g[][15],char m[][15],int n,int k)
{
	int i,j,l,a;
	for(i=0;i<pow(2,k);i++)
		for(j=0,a=0;j<k;j++)
			if(er[i][j]=='1')
			{	
				for(l=0;l<n;l++)
					if(a==0)
						m[i][l]=g[j][l];
					else
					//	for(l=0;l<n;l++)
						m[i][l]=moer(g[j][l],m[i][l])+'0';
				a++;
			}
}
int minjuli(char g[][15],int n,int k)
{
	int i,j,a,b=n;
	for(i=0;i<k;i++)
	{
		for(j=0,a=0;j<n;j++)
			if(g[i][j]=='1')
				a++;
		if(b>a)
			b=a;
	}
	return b;
}
void main()
{
	int n,k,i,j,a;
	float rn,rk;
	char g[8][15],h[15][15],m[128][15],er[33][15];

	printf("请输入分组码的n，k\n n=");
	scanf("%d",&n);
	printf(" k=");
	scanf("%d",&k);
		fflush(stdin);

	for(i=0;i<n;i++)//初始化
		for(j=0;j<n;j++)
			er[i][j]='0',h[i][j]='0',m[i][j]='0';

	shengcheng(g,n,k);
	erjin(er,k);
	mazi(er,g,m,n,k);
	a=minjuli(g,n,k);

	for(i=0;i<k;i++)//校验矩阵
		for(j=k;j<n;j++)
			h[j-k][i]=g[i][j];
	for(i=0,j=k;i<n-k;i++,j++)
		h[i][j]='1';

	printf("您输入的生成矩阵是:");
	dayin(k,n,g);
	printf("\n对应的二进制输入码是:");
	dayin(pow(2,k),k,er);
	printf("\n校验矩阵是:");
	dayin(n-k,n,h);
		rn=n;rk=k;
	printf("\n码率为r=%.3f",rk/rn);
	printf("\n最小距离d=%d",a);
	printf("\n生成的码字为：");
	dayin(pow(2,k),n,m);
	printf("\n\n");
}
