// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = { "usfsh", 0 };

// create devices to switch to later as virtual consoles
void
create_vcs(void)
{
  int i, fd;
  char *dname = "vc0";

  for (i = 0; i < NUM_VCS; i++) {
    dname[2] = '0' + i;
    if ((fd = open(dname, O_RDWR)) < 0) {
      mknod(dname, 1, i + 2);
    }
    else {
      close(fd);
    }
  }
}

int
main(void)
{
  int i, fd, pid, wpid, vid;

  if(open("console", O_RDWR) < 0) {
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  create_vcs();

  for(;;) {
    printf(1, "init: starting usfsh\n");
    pid = fork();
    if(pid < 0) {
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0) {
      exec("usfsh", argv);
      printf(1, "init: exec usfsh failed\n");
      exit();
    }
    int initialized = 0;
    if(pid > 0 && initialized == 0) {
      char *dname = "vc0";
      for (i = 0; i < NUM_VCS; i++) {
        dname[2] = '0' + i;
        fd = open(dname, O_RDWR);

        /* fork a child and exec usfsh */
        vid = fork();

        if (vid == 0) {
          close(0);
          close(1);
          dup(fd);
          dup(fd);

          exec("usfsh", argv);
          exit();
        }
        initialized = 1;
        close(fd);
      }
    }
    for(;;) {
      // this call to wait() returns if the shell exits,
      // or if a parentless process exits.
      wpid = wait();
      if(wpid == pid) {
        // the shell exited; restart it.
        break;
      }
      else if(wpid < 0) {
        printf(1, "init: wait returned an error\n");
        exit();
      }
      else {
        // it was a parentless process; do nothing.
      }
    }
  }
}
