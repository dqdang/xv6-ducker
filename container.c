#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "container.h"

int create_container(int selected_console) {
    struct container current_container = {0};

    current_container.container_id = selected_console;
    struct proc *proc = myproc();

    cprintf("selected_console: %d, cid: %d, pid: %d\n", selected_console, current_container.container_id, &proc->pid);

    return 23;
}
