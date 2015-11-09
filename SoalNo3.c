#include<stdio.h> 
#include<pthread.h>
#include<stdlib.h>
void *run1 (void *args)
{
	FILE *in, *copy;
	char ch;
	in=fopen("open.txt", "r");
	copy=fopen("copy.txt", "w");
	while ((ch=fgetc(in))!=EOF)
	{
		fputc(ch, copy);
	}
	fclose(in);
	fclose(copy);
}

void *run2 (void *args)
{
	FILE *in, *out;
	char ch;
	in=fopen("copy.txt", "r");
	out=fopen("output.txt", "w");
	while ((ch=fgetc(in))!=EOF)
	{
		fputc(ch, out);
	}
	fclose(in);
	fclose(out);
}

int main()
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, run1, NULL);
	pthread_create(&t2, NULL, run2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}
