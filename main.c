#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if(argc!=3) {
		printf("Shared Object dlmopen void main function tester\n");
		printf("Usage: ./main ./libX.so <0:LM_ID_BASE 1:LM_ID_NEWLM>\n");
		printf("Example: ./main ./libhello.so 1\n");
		return 0;
	}

	void* handle;
	if(strcmp(argv[2],"0")==0) {
		handle = dlmopen(LM_ID_BASE, argv[1], RTLD_LAZY|RTLD_LOCAL);
	} else if(strcmp(argv[2],"1")==0) {
		handle = dlmopen(LM_ID_NEWLM, argv[1], RTLD_LAZY|RTLD_LOCAL);
	}
	dlerror();
	void (*fn)() = dlsym(handle, "main");
	(*fn)();
	dlclose(handle);
	return 0;
}