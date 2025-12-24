#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
  int valid[NPROC];
  int pid[NPROC];
  int ppid[NPROC];
  int priority[NPROC];
  int state[NPROC];
  uint64 size[NPROC];
  char name[NPROC][16];
  int cticks[NPROC];
  int wticks[NPROC];
};

#endif
