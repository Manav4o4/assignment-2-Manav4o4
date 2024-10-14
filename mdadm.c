#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mdadm.h"
#include "jbod.h"

int mdadm_mount(void) {
  if(jbod_operation(JBOD_MOUNT, NULL) == 0){
	  return 1;
  }
  else{
	  return -1;
  }
}

int mdadm_unmount(void) {
  if(jbod_operation(JBOD_UNMOUNT, NULL) == 0){
	  return 1;
  }
  else{
	  return -1;
  }
}

int mdadm_read(uint32_t start_addr, uint32_t read_len, uint8_t *read_buf)  {
  //Complete your code here
  return 0;
}

