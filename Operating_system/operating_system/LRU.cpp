#if 0
#include <iostream>
#include  <map>
#define MEM_SIZE 32
#define RAM_SIZE  16
#define SWAP_SIZE 32

struct page_item { //页表项
	int ram_addr;
	int swap_addr;
	unsigned access;
	bool present;
	bool modified;
};

static char ram[RAM_SIZE];
static char swap[SWAP_SIZE];
static struct page_item page_table[MEM_SIZE];
struct test_item{
	struct test_item *next = NULL;
	int data;
};
static struct test_item *first_list = NULL;
static struct test_item *end_list = NULL;
test_item head_item;
test_item item[RAM_SIZE];

void init_test_list(){
	first_list = &head_item;
	end_list = &head_item;
	for (int i = 0; i<16; i++){
		end_list->next = &item[i];
		item[i].data = i;
		end_list = &item[i];
	}
}
static int algo_swap(void){// 换页算法 
	return first_list->next->data;

}
static int mem_access(int laddr){// 逻辑地址laddr转换为物理地址paddr 
	if (page_table[laddr].present) {
		struct test_item *prev = first_list;
		struct test_item *cur = first_list->next;
		while (cur != NULL){
			if (cur->data == laddr){
				prev->next = cur->next;
				cur->next = NULL;
				end_list->next = cur;
				end_list = cur;
				break;
			}
			prev = cur;
			cur = cur->next;
		}
		return page_table[laddr].ram_addr;

	}
	//缺页处理 根据特定算法选择被换出的页
	int page = algo_swap();
	struct test_item *prev = first_list;
	struct test_item *cur = first_list->next;
	while (cur != NULL){
		if (cur->data == page){
			prev->next = cur->next;
			cur->data = laddr;
			cur->next = NULL;
			end_list->next = cur;
			end_list = cur;
			break;
		}
		prev = cur;
		cur = cur->next;
	}
	// 换出 
	if (page_table[page].modified) {			// 写回 
		int data = ram[page_table[page].ram_addr];
		swap[page_table[page].swap_addr] = data;
	}
	page_table[page].present = false;
	// 替换 
	int paddr = page_table[page].ram_addr;
	page_table[laddr].ram_addr = paddr;
	ram[paddr] = swap[page_table[laddr].swap_addr];
	page_table[laddr].modified = false;
	page_table[laddr].present = true;
	page_table[laddr].access = 1;
	return paddr;
}
int mem_read(int addr, char *buf){
	if (addr < 0 || addr > MEM_SIZE)
		return -1;

	int paddr = mem_access(addr);
	*buf = ram[paddr];

	return 0;
}
int mem_write(int addr, char buf){
	if (addr < 0 || addr > MEM_SIZE)
		return -1;

	int paddr = mem_access(addr);
	ram[paddr] = buf;
	page_table[addr].modified = true;

	return 0;
}
void mem_init(void){
	for (int i = 0; i < MEM_SIZE; i++) {		// 全部加载到交换空间 
		page_table[i].swap_addr = i;
		page_table[i].present = false;
		page_table[i].modified = false;
	}
	for (int i = 0; i < RAM_SIZE; i++) {		// 部分加载到内存 
		page_table[i].ram_addr = i;
		page_table[i].present = true;
		page_table[i].access = 0;
	}
}

void mem_state(void){
	printf("ram state:\t");
	for (int i = 0; i < RAM_SIZE; i++) {
		printf("%02x ", ram[i]);
	}
	printf("\nswap state:\t");
	for (int i = 0; i < SWAP_SIZE; i++) {
		printf("%02x ", swap[i]);
	}
	printf("\n\n");
}

void history_show(){
	struct test_item *prev = first_list;
	struct test_item *cur = first_list->next;
	printf("recond:\n");
	int i = 0;
	int a[100];
	while (cur != NULL){
		a[i] = cur->data;
		i++;
		//printf("%d ",cur->data);
		prev = cur;
		cur = cur->next;
	}
	while (i>0){
		i--;
		printf("%d ", a[i]);

	}
}
void mem_test(void){
	printf("0-31为地址，在其中依次写入0-31，前16个则会被替换：\n");

	for (int i = 0; i<32; i++)
		mem_write(i, i);
	mem_state();
	history_show();
	printf("\n访问22号单元，22-->链尾末段\n");
	mem_write(22, 22);
	history_show();
	printf("\n访问11号单元，11-->链尾末段\n");
	mem_write(11, 11);
	history_show();
}

int main(int argc, const char *argv[]){
	mem_init();
	init_test_list();
	mem_test();
	getchar();
	system("pause");
	return 0;
}
#endif