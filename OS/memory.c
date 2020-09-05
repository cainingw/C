/**
* @file memory.c
* @brief this c file is for Memory Allocation
*
* @author Caining Wang
*
* @date 6/27/2020
*/
#include <stdio.h>
#include "math.h"
#include "oslabs.h"

void setupmem(struct MEMORY_BLOCK *inmem, int start_address,int end_address,int segment_size,int process_id)
{
	(*inmem).start_address = start_address;
	(*inmem).end_address = end_address;
	(*inmem).segment_size = segment_size;
	(*inmem).process_id = process_id;
}

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
	int i;
	int index = -1;
	int bestfit = 9999;
	for(i = 0; i < *map_cnt; i++){		
		if((memory_map[i].segment_size - request_size) >= 0 && (memory_map[i].segment_size - request_size) < bestfit && memory_map[i].process_id == 0){
			bestfit = memory_map[i].segment_size - request_size;
			index = i;
		}
	}
	if(index > -1){
		if(memory_map[index].segment_size == request_size){
			memory_map[index].process_id = process_id;
				
			return memory_map[index];
		} else if(memory_map[index].segment_size > request_size){
			for(i = *map_cnt; i >= index + 2; i--){
            	memory_map[i] = memory_map[i - 1];
       		}
			struct MEMORY_BLOCK new_mem;
			setupmem(&new_mem, (memory_map[index].start_address + request_size), memory_map[index].end_address, (memory_map[index].segment_size - request_size), 0);
			memory_map[index + 1] = new_mem;
			*map_cnt += 1;
				
			memory_map[index].end_address = memory_map[index].start_address + request_size - 1;
			memory_map[index].segment_size = request_size;
			memory_map[index].process_id = process_id;
				
			return memory_map[index];
		} 
	} else{
		struct MEMORY_BLOCK NULLBLOCK;
		setupmem(&NULLBLOCK, 0, 0, 0, 0);
	
		return NULLBLOCK;
	}	
}



struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
	int i;
	int index = -1;
	int lowest = 99999999;
	for(i = 0; i < *map_cnt; i++){
		if((memory_map[i].segment_size - request_size) >= 0 && memory_map[i].start_address < lowest && memory_map[i].process_id == 0){
			lowest = memory_map[i].start_address;
			index = i;
		}
	}
	if(index > -1){
		if(memory_map[index].segment_size == request_size){
			memory_map[index].process_id = process_id;
				
			return memory_map[index];
		} else if(memory_map[index].segment_size > request_size){
			for(i = *map_cnt; i >= index + 2; i--){
            	memory_map[i] = memory_map[i - 1];
       		}
			struct MEMORY_BLOCK new_mem;
			setupmem(&new_mem, (memory_map[index].start_address + request_size), memory_map[index].end_address, (memory_map[index].segment_size - request_size), 0);
			memory_map[index + 1] = new_mem;
			*map_cnt += 1;
				
			memory_map[index].end_address = memory_map[index].start_address + request_size - 1;
			memory_map[index].segment_size = request_size;
			memory_map[index].process_id = process_id;
				
			return memory_map[index];
		} 
	} else{
		struct MEMORY_BLOCK NULLBLOCK;
		setupmem(&NULLBLOCK, 0, 0, 0, 0);
	
		return NULLBLOCK;
	}	
}
	
struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
	int i;
	int index = -1;
	int worstfit = -1;
		for(i = 0; i < *map_cnt; i++){		
		if((memory_map[i].segment_size - request_size) >= 0 && (memory_map[i].segment_size - request_size) > worstfit && memory_map[i].process_id == 0){
			worstfit = memory_map[i].segment_size - request_size;
			index = i;
		}
	}
	if(index > -1){
		if(memory_map[index].segment_size == request_size){
			memory_map[index].process_id = process_id;
				
			return memory_map[index];
		} else if(memory_map[index].segment_size > request_size){
			for(i = *map_cnt; i >= index + 2; i--){
            	memory_map[i] = memory_map[i - 1];
       		}
			struct MEMORY_BLOCK new_mem;
			setupmem(&new_mem, (memory_map[index].start_address + request_size), memory_map[index].end_address, (memory_map[index].segment_size - request_size), 0);
			memory_map[index + 1] = new_mem;
			*map_cnt += 1;
				
			memory_map[index].end_address = memory_map[index].start_address + request_size - 1;
			memory_map[index].segment_size = request_size;
			memory_map[index].process_id = process_id;
				
			return memory_map[index];
		} 
	} else{
			struct MEMORY_BLOCK NULLBLOCK;
			setupmem(&NULLBLOCK, 0, 0, 0, 0);
	
			return NULLBLOCK;
	}

}
	
struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id, int last_address){
	int i;
	int index = -1;
	int lowest = 99999999;
	for(i = 0; i < *map_cnt; i++){
		if((memory_map[i].segment_size - request_size) >= 0 && memory_map[i].start_address < lowest && memory_map[i].start_address >= last_address && memory_map[i].process_id == 0){
			lowest = memory_map[i].start_address;
			index = i;
		}
	}
	if(index > -1){
		if(memory_map[index].segment_size == request_size){
			memory_map[index].process_id = process_id;
				
			return memory_map[index];
		} else if(memory_map[index].segment_size > request_size){
			for(i = *map_cnt; i >= index + 2; i--){
            	memory_map[i] = memory_map[i - 1];
       		}
			struct MEMORY_BLOCK new_mem;
			setupmem(&new_mem, (memory_map[index].start_address + request_size), memory_map[index].end_address, (memory_map[index].segment_size - request_size), 0);
			memory_map[index + 1] = new_mem;
			*map_cnt += 1;
				
			memory_map[index].end_address = memory_map[index].start_address + request_size - 1;
			memory_map[index].segment_size = request_size;
			memory_map[index].process_id = process_id;
				
			return memory_map[index];
		} 
	} else{
		struct MEMORY_BLOCK NULLBLOCK;
		setupmem(&NULLBLOCK, 0, 0, 0, 0);
	
		return NULLBLOCK;
	}
}

void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt){
	int i;
	int index = -1;
	for(i = 0; i < *map_cnt; i++){
		if(memory_map[i].start_address == freed_block.start_address){
			index = i;
			break;
		}
	}
	memory_map[index].process_id = 0;
	
	if((index - 1) > -1 && memory_map[index - 1].process_id == 0){
		memory_map[index - 1].end_address = memory_map[index].end_address;
		memory_map[index - 1].segment_size = memory_map[index - 1].segment_size + memory_map[index].segment_size;
		for(i = index; i < *map_cnt-1; i++){
            memory_map[i] = memory_map[i + 1];
        }
		*map_cnt -= 1;
		index -= 1;
	}
	
	if((index + 1) < *map_cnt && memory_map[index + 1].process_id == 0){
		memory_map[index].end_address = memory_map[index+1].end_address;
		memory_map[index].segment_size = memory_map[index + 1].segment_size + memory_map[index].segment_size;
		for(i = index + 1; i < *map_cnt-1; i++){
            memory_map[i] = memory_map[i + 1];
        }
		*map_cnt -= 1;
	}

}