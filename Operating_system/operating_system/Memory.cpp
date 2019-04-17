#if 0
#include <iostream>
#include <stdio.h>
#define MEM_SIZE 128
static char mem[MEM_SIZE];

#define MINBLK 16
struct block {
	struct block * next;
	size_t length;
	char data[0];
};

static struct block * free_list = NULL;

void malloc_init(void)
{
	free_list = (struct block *)mem;
	free_list->next = NULL;
	free_list->length = MEM_SIZE - sizeof(struct block);
}

void * malloc(size_t size)
{
	size = (size + 7) & ~7;

	struct block * prev = (struct block *) &free_list;
	struct block * cur = free_list;

	while (cur != NULL) {
		if (cur->length >= size) break;
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL)
		return NULL;

	if ((cur->length - size) >= MINBLK)
	{
		struct block * temp = (struct block *)(cur->data + size);
		temp->next = cur->next;
		temp->length = cur->length - size - sizeof(struct block);
		prev->next = temp;
		cur->length = size;
	}
	else
	{
		prev->next = cur->next;
	}

	return cur->data;
}

void free(void * ptr)
{
	if (ptr == NULL)
		return;

	struct block * temp = (struct block *)((char *)ptr - sizeof(struct block));
	char * tempn = (char *)ptr + temp->length; // ��temp���������ڵ���һ��block�ĵ�ַ

	struct block * prev = (struct block *) &free_list;
	struct block * cur = free_list;
	char * curn; // ��cur���������ڵ���һ��block�ĵ�ַ

				 // ���Ƕ�����������free����
				 // ... ...
}

void malloc_state(void)
{
	printf("free blocks:\n");
	struct block * ptr;
	for (ptr = free_list; ptr != NULL; ptr = ptr->next) {
		int i;
		printf("%p:", ptr);
		for (i = 0; i < ptr->length; i++) {
			printf("=");
		}
		printf(" ");
	}
	printf("\n");
}

void malloc_test(void)
{
	char* a = (char*)malloc(sizeof(char));
	malloc_state();
	char* b = (char*)malloc(sizeof(char));
	malloc_state();
	char* c = (char*)malloc(sizeof(char));
	malloc_state();
	char* d = (char*)malloc(sizeof(char));
	malloc_state();
	free(a);
	malloc_state();
	free(b);
	malloc_state();
	free(c);
	malloc_state();
	free(d);
	malloc_state();
}

int main(int argc, const char *argv[]){
	malloc_init();

	malloc_test();

	return 0;
}
#endif