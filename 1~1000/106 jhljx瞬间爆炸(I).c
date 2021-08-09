#include<stdio.h>

struct stackWithName
{
    int tower[220];
    int top;
    char name;
}; 

struct stackWithName HanoiTower[3];

int T;
int n;
long long step;
long long current;

int main()
{
    while(~scanf("%d",&n))
	{
        HanoiTower[0].name='A';
        int i;
        for(i=0;i<n;++i)
		{
            HanoiTower[0].tower[HanoiTower[0].top]=n-i;
            HanoiTower[0].top++;
        }
        if(n%2==0)
		{
			HanoiTower[1].name='B';
			HanoiTower[2].name='C';
		}
        else
		{
			HanoiTower[1].name='C';
			HanoiTower[2].name='B';
		}
        step=((long long)1<<n)-1;
        current=0;
        i=0;
        int curPlace;
        while(current<step)
		{
            curPlace=HanoiTower[i%3].tower[HanoiTower[i%3].top-1];
            HanoiTower[i%3].top--;
            HanoiTower[(i+1)%3].tower[HanoiTower[(i+1)%3].top]=curPlace;
            HanoiTower[(i+1)%3].top++;
            ++current;
            printf("%c->%c\n",HanoiTower[i%3].name,HanoiTower[(i+1)%3].name);
            ++i;
            if(i>3)
			{
				i%=3;
			}
            if(current<step)
			{
                if(HanoiTower[(i+1)%3].top==0||HanoiTower[(i-1)%3].top!=0&&HanoiTower[(i+1)%3].tower[HanoiTower[(i+1)%3].top-1]>HanoiTower[(i-1)%3].tower[HanoiTower[(i-1)%3].top-1])
				{
                    curPlace=HanoiTower[(i-1)%3].tower[HanoiTower[(i-1)%3].top-1];
                    HanoiTower[(i-1)%3].top--;
                    HanoiTower[(i+1)%3].tower[HanoiTower[(i+1)%3].top]=curPlace;
                    HanoiTower[(i+1)%3].top++;
                    ++current;
                    printf("%c->%c\n",HanoiTower[(i-1)%3].name,HanoiTower[(i+1)%3].name);
                }
                else
				{
                    curPlace=HanoiTower[(i+1)%3].tower[HanoiTower[(i+1)%3].top-1];
                    HanoiTower[(i+1)%3].top--;
                    HanoiTower[(i-1)%3].tower[HanoiTower[(i-1)%3].top]=curPlace;
                    HanoiTower[(i-1)%3].top++;
                    ++current;
                    printf("%c->%c\n",HanoiTower[(i+1)%3].name,HanoiTower[(i-1)%3].name);
                }
            }
        }
        printf("\n");
        for(i=0;i<3;++i)
		{
			HanoiTower[i].top=0;
        }
    }
}
