
#include<stdio.h>
#include<pthread.h>
int total=0;
void *prima (void *args)
{
	int *i, n, j, factor;
	factor=0;
	i = (int*)args;
	for (j=1; j<=*i; j++)
	{
		if (*i%j==0) factor++;
	}
	if (factor==2)
	{
		total++;
	}
}

void main()
{
	pthread_t t1;
	int i, n;
	scanf("%d", &n);
	for (i=2; i<n; i++)
	{
		pthread_create(&t1, NULL, prima, (void*)&i);
		pthread_join(t1, NULL);
	}
	printf("Banyak bilangan prima: %d\n", total);
}
