#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  struct pstat pst;

  static char *states[] = {
    "UNUSED",
    "USED",
    "SLEEPING",
    "RUNNABLE",
    "RUNNING",
    "ZOMBIE"
  };

  if(getpinfo(&pst) < 0){
    printf("error: ps command failed\n");
    return -1;
  }

  printf("PID   PPID   PRIORITY  STATE      SIZE      CTICKS  WTICKS  NAME\n");

  for(int i=0; i<NPROC; i++){
    if(pst.valid[i] == 1){
      char *current_state = "UNKNOWN";
      if (pst.state[i] >= 0 && pst.state[i] < 6) {
          current_state = states[pst.state[i]];
      }
      printf("%d     %d      %d         %s   %lu      %d       %d       %s\n",
             pst.pid[i],
             pst.ppid[i],
             pst.priority[i],
             current_state,
             pst.size[i],
             pst.cticks[i],
             pst.wticks[i],
             pst.name[i]);
    }
  }
  return 0;
}
