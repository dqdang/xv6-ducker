#include "types.h"
#include "defs.h"
#include "param.h"
#include "container.h"

int create_container(int selected_console) {
    struct container current_container = {0};

    current_container.container_id = selected_console;
    cprintf("Container ID: %d\n", current_container.container_id);

    return 23;
}
