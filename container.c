#include "types.h"
#include "defs.h"
#include "container.h"

int create_container(int selected_console) {
    struct container current_container = {0};

    current_container.container_id = selected_console;

    cprintf("selected_console: %d, cid: %d\n", selected_console, current_container.container_id);

    return 23;
}
