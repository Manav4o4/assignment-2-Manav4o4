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

	if ((read_buf == NULL) && read_len > 0){
		return -4;
	}


	uint32_t current_addr = start_addr;

	uint32_t bytes_read = 0;

	while (bytes_read < read_len){

		current_addr = bytes_read + start_addr;
		uint8_t current_disk = current_addr / (JBOD_NUM_BLOCKS_PER_DISK * JBOD_BLOCK_SIZE); // Current disk that we are working with
		uint32_t block_offset = current_addr % (JBOD_NUM_BLOCKS_PER_DISK * JBOD_BLOCK_SIZE); // How many bytes into the disk are we
		uint8_t current_block = block_offset / JBOD_BLOCK_SIZE; // Current block that we are working in
		uint32_t offset_in_block = block_offset % JBOD_BLOCK_SIZE; // How many bytes into the block are we

		uint32_t op = (current_disk << 0) | (2 << 12); // Seek to current disk
		if (jbod_operation(op, NULL) == -1){
			return -4;
		}


		op = (current_block << 4) | (3 << 12);
		if (jbod_operation(op, NULL) == -1){
			return -4;
		}

		op = (4 << 12);
		uint8_t block[JBOD_BLOCK_SIZE]; // Why a buffer?
		if (jbod_operation(op, block) == -1){
			return -4;
		}

		uint32_t copied_bytes = JBOD_BLOCK_SIZE - offset_in_block;
		if(copied_bytes > read_len - bytes_read){
			copied_bytes = read_len - bytes_read;
		}

		memcpy(read_buf + bytes_read, block + offset_in_block, copied_bytes); // Why memecpy?

		bytes_read += copied_bytes;

	}

	return bytes_read;









}

