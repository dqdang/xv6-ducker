#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"
#include "fcntl.h"

/* 
Tests:
ctool create ctest1 -p 4 sh ps echoloop forkbomb
ctool start ctest1 vc0 sh

ctool create ctest2 -m 40000000 sh df free membomb
ctool start ctest2 vc1 sh

ctool create ctest3 -d 100000 sh ps free diskbomb
ctool start ctest3 vc2 sh

ctool create ctest4 sh ps echoloop
ctool start ctest4 vc3 echoloop a b
*/ 

void usage() {
    // printf(1, "usage: ctool create <name> [-p <max_processes>] [-m <max_memory>] [-d <max_disk>] prog [prog2.. ]\n");
    printf(1, "usage: ctool create container_id\n");
    exit();
}

void create(int argc, char *argv[]) {
    if(argc < 3) {
        usage();
    }

    int i = create_container(atoi(argv[3]));
    printf(1, "%d\n", i);
}

int main(int argc, char *argv[]) {
    create(argc, argv);
    exit();
}
