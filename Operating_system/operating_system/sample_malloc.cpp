#if 0
#include<iostream>
using namespace std;
#define MEM_SIZE 128
static char mem[MEM_SIZE];

#define MINBLK 16
struct block {
	struct block * next;
	size_t length;
	char data[0];
};

static struct block * free_list = NULL;

void malloc_init(void){
	free_list = (struct block *)mem;
	free_list->next = NULL;
	free_list->length = MEM_SIZE - sizeof(struct block);
}

void * malloc(size_t size){
	size = (size + 7) & ~7;

	struct block * prev = (struct block	*) &free_list;
	struct block * cur = free_list;

	while (cur != NULL) {
		if (cur->length >= size) break;
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL)
		return NULL;

	if ((cur->length - size) >= MINBLK) {
		struct block * temp = (struct block *)(cur->data + size);
		temp->next = cur->next;
		temp->length = cur->length - size - sizeof(struct block);
		prev->next = temp;
		cur->length = size;
	} else {
		prev->next = cur->next;
	}

	return cur->data;
}
void free(void * ptr){
	if (ptr == NULL)
		return;

	struct block * temp = (struct block *)((char *)ptr - sizeof(struct block));
	char * tempn = (char *)ptr + temp->length; // 和temp物理上相邻的下一个block的地址

	struct block * prev = (struct block *) &free_list;
	struct block * cur = free_list;
	char * curn; // 和cur物理上相邻的下一个block的地址

	// 考虑多种情况，完成free函数
	// ... ...
}

void malloc_state(void){
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
void *malloc_test() {
	int *p = new int(1);
	int *a = &p;
	cout << p << endl << a << endl;
	void *temp=nullptr;
	if (temp == nullptr)
		return nullptr;
	else {

	}
	malloc_state();
	return temp;
}

int main(int argc, const char *argv[])
{
	malloc_init();

	malloc_test();
	system("pause");
	return 0;
}
#endif