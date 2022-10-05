#include <stdio.h>

__attribute__((constructor)) static void init() { printf("Loaded\n"); }