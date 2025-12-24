#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  struct pstat pst;

  if(getpinfo(&pst) < 0){
    printf("error: ps command failed\n");
    return -1;
  }

  printf("PID  PPID  PRIORITY  STATE  SIZE  CTICKS  WTICKS  NAME\n");

  for(int i=0; i<NPROC; i++){
    if(pst.valid[i] == 1){
      printf("  %d    %d        %d     %d    %lu      %d      %d    %s\n",
             pst.pid[i],
             pst.ppid[i],
             pst.priority[i],
             pst.state[i],
             pst.size[i],
             pst.cticks[i],
             pst.wticks[i],
             pst.name[i]);
    }
  }
  return 0;
}
