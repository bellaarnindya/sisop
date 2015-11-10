
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
struct prime
{
	int bil;
	int* total;
};

void *prima (void *args)
{
	int j, factor;
	struct prime* thread=(struct prime*)args;
	factor=0;
	for (j=1; j<=(thread->bil); j++)
	{
		if ((thread->bil)%j==0) factor++;
	}
	if (factor==2)
	{
		*(thread->total)=*(thread->total)+1;
	}
}

void main()
{
	int i, n, total=0;
	scanf("%d", &n);
	pthread_t *t1=(pthread_t*)malloc(sizeof(pthread_t)*(n+1));
	struct prime *p=(struct prime*)malloc(sizeof(struct prime)*(n+1));
	for (i=2; i<n; i++)
	{
		p[i].bil=i;
		p[i].total=&total;
		pthread_create(&t1[i], NULL, prima, &p[i]);
	}

	for(i=2; i<n; i++)
	{
		pthread_join(t1[i], NULL);
	}
	printf("%d\n",  total);
}
