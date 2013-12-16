#include <cstdio>
#include "VM.h"

int main(int argc, char **argv)
{
	char *file = argv[1];
	if (argc < 2)
	{
		printf("Not enough command line parameters: File name expected");
		VM vm;
		vm.Run("test.txt");
		return 0;
	}

	
	VM vm;
	vm.Run(argv[1]);

	return 0;
}