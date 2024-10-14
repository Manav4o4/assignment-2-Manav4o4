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

	if(is_mounted == 0){
		return -1;
	}

	if(jbod_operation(op, NULL) == 0)
	{	
		is_mounted = 0;
		return 1;
	}
	else{
		return -1;
	}
	
}

int mdadm_read(uint32_t start_addr, uint32_t read_len, uint8_t *read_buf)  {

	if (start_addr + read_len > 1048576){
		return -1;
	}

	if ((read_len > 1024) | (read_len < 0)){
		return -2;
	}

	if (is_mounted == 0){
		return -3;
	}
	
	if (read_buf == NULL){
		return -4;
	}

	DISK_NUMBER = 0;
	
	while (start_addr >= JBOD_DISK_SIZE){
		DISK_NUMBER += 1;
		start_addr -= JBOD_DISK_SIZE;

	return 0;

}

