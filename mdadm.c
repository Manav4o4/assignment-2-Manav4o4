#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mdadm.h"
#include "jbod.h"

static int is_mounted = 0;

int mdadm_mount(void) {

	if (is_mounted == 1){
		return -1;
	}

	uint32_t op = (0 << 12);

	if(jbod_operation(op, NULL) == 0){
		is_mounted = 1;
		return 1;
	}
	else{
		return -1;
	}
}

int mdadm_unmount(void) {

	uint32_t op = (1 << 12);

	if(jbod_operation(op, NULL) == 0){
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

