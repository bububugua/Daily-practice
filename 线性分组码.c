#include<stdio.h>
#include<math.h>

void shengcheng(char g[][15],int n,int k)
{
	int i,j,c;
	printf("���������ɾ���\n");
	for(i=0;i<k;i++)
		for(c=0;;c=0)//������ƣ���֤Ϊ2����
		{
			for(j=0;j<n;j++)
			{
				scanf("%c",&g[i][j]);
				if(j==(n-1))//�����س�����Ӱ��
					fflush(stdin);
				if((g[i][j]!='0')&&(g[i][j]!='1'))
					c=1;
			}
			if(c==0)
				break;
			else
				printf("���벻Ϊ0��1�������������%d��\n",i+1);
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

	printf("������������n��k\n n=");
	scanf("%d",&n);
	printf(" k=");
	scanf("%d",&k);
		fflush(stdin);

	for(i=0;i<n;i++)//��ʼ��
		for(j=0;j<n;j++)
			er[i][j]='0',h[i][j]='0',m[i][j]='0';

	shengcheng(g,n,k);
	erjin(er,k);
	mazi(er,g,m,n,k);
	a=minjuli(g,n,k);

	for(i=0;i<k;i++)//У�����
		for(j=k;j<n;j++)
			h[j-k][i]=g[i][j];
	for(i=0,j=k;i<n-k;i++,j++)
		h[i][j]='1';

	printf("����������ɾ�����:");
	dayin(k,n,g);
	printf("\n��Ӧ�Ķ�������������:");
	dayin(pow(2,k),k,er);
	printf("\nУ�������:");
	dayin(n-k,n,h);
		rn=n;rk=k;
	printf("\n����Ϊr=%.3f",rk/rn);
	printf("\n��С����d=%d",a);
	printf("\n���ɵ�����Ϊ��");
	dayin(pow(2,k),n,m);
	printf("\n\n");
}
