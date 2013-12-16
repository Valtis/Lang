#include <cstdio>
#include "VM.h"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Not enough command line parameters: File name expected");
		return 1;
	}
	
	VM vm;
	vm.Run(argv[1]);

	return 0;
}