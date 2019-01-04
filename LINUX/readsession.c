#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct node{
/*	char username[21];
	unsigned long time;
	char id[65];
	struct node *next;*/
	int data;
	char username[21];
	struct node *next;
}node_t;

node_t *creatlink()
{
	node_t *head = (node_t *)malloc(sizeof(node_t));
	int t;
	char str[21];
	node_t *p;
	node_t *q;
	p = q = head;
	FILE * r = fopen("text.txt", "r");
	if(r == NULL)
	{
		perror("open");
		return NULL;
	}
	while(fscanf(r, "%d%21s", &t, str)!=EOF)
	{
		q = (node_t *)malloc(sizeof(node_t));
		q->data = t;
		strcpy(q->username, str);
		p->next = q;
		p = q;
	}
	p->next = NULL;
	return head;
}
node_t *testlink()
{
	node_t *head = (node_t *)malloc(sizeof(node_t));
	int t;
	char str[21];
	node_t *p = NULL;
	p = head;
	FILE *r = fopen("text.txt", "r");
	while(fscanf(r, "%d%21s", &t, str)!=EOF){
		p = (node_t *)malloc(sizeof(node_t));
		p->data = t;
		strcpy(p->username, str);
		p = p->next;
	}
	p->next = NULL;
	fclose(r);
	return head;
}
void outlink(node_t *head)
{
	node_t *p=head->next;
	FILE *w = fopen("text.txt", "w");
	while(p){
		printf("%d ", p->data);
		printf("%21s,", p->username);
		fprintf(w,"%d ", p->data);
		fprintf(w,"%-21s", p->username);
		p = p->next;
	}
	printf("\n");
	fprintf(w,"\n");
	fclose(w);
}
int main(void)
{
	node_t *head;
	int n, m;
	head = testlink();
	outlink(head);
	system("pause");
	return 0;
}
