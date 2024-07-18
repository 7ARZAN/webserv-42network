#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <vector>
#include "../includes/libconfpp.h"

int main(int argc, char **argv){
	// controlling buffering
	setvbuf(stdout, NULL, 0, 1);
	if (argc < 2)
		return (0);
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	char *file = (char *) mmap(0, 10000, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
	(void) file;
	config x = parse_string(std::string(file));
	int i = 0 ;
	while (i < x.size()){
		int j = 0;
		std::cout << "table name [" << x[i]->tables.size() << "] : " << x[i]->table_name  << std::endl;
		while (j < x[i]->tables.size()){
			std::cout << "\t" << x[i]->tables[j]->key << " = " << x[i]->tables[j]->val << std::endl;
			j++;
		}
		i++;
	}
}
