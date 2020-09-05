/**
* @file virtual.c
* @brief this c file is for Virtual Memory Allocation
*
* @author Caining Wang
*
* @date 6/29/2020
*/
#include <stdio.h>
#include "math.h"
#include "oslabs.h"

	

int process_page_access_fifo(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp){
	if(page_table[page_number].is_valid == 1){
		page_table[page_number].last_access_timestamp = current_timestamp;
		page_table[page_number].reference_count++;  
		
		return page_table[page_number].frame_number;
	} else{
		if(*frame_cnt > 0){
			page_table[page_number].frame_number = frame_pool[*frame_cnt - 1];
			*frame_cnt -= 1;
			page_table[page_number].is_valid = 1;
			page_table[page_number].last_access_timestamp = current_timestamp;
			page_table[page_number].reference_count++;
			
			return page_table[page_number].frame_number;
		} else{			
			int i, index;
			int min = 99999;
			
			for(i = 0; i < *table_cnt; i++){				
				if(page_table[i].is_valid == 1 && page_table[i].arrival_timestamp < min){
					min = page_table[i].arrival_timestamp;
					index = i;
				}
			}
			
			page_table[page_number].frame_number = page_table[index].frame_number;
			
			page_table[index].is_valid = 0;
			page_table[index].frame_number = -1;
			page_table[index].arrival_timestamp = 0;
			page_table[index].last_access_timestamp = 0;
			page_table[index].reference_count = 0;
			
			page_table[page_number].is_valid = 1;
			page_table[page_number].arrival_timestamp = current_timestamp;
			page_table[page_number].last_access_timestamp = current_timestamp;
			page_table[page_number].reference_count = 1;
			
			return page_table[page_number].frame_number;
		}
	}
}

int count_page_faults_fifo(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
	int timestamp = 1;
	int pagefaults = 0;
	int i;
	
	for(i = 0; i < reference_cnt; i++){
		if(page_table[refrence_string[i]].is_valid == 1){
			page_table[refrence_string[i]].last_access_timestamp = timestamp;
			page_table[refrence_string[i]].reference_count++;     
		} else{
			if(frame_cnt > 0){
				page_table[refrence_string[i]].frame_number = frame_pool[frame_cnt - 1];
				frame_cnt -= 1;
				page_table[refrence_string[i]].is_valid = 1;
				page_table[refrence_string[i]].last_access_timestamp = timestamp;
				page_table[refrence_string[i]].reference_count++;
				pagefaults++;
			} else{
				int j, index;
				int min = 99999;
				
				for(j = 0; j < table_cnt; j++){				
					if(page_table[j].is_valid == 1 && page_table[j].arrival_timestamp < min){
						min = page_table[j].arrival_timestamp;
						index = j;
					}
				}
			
				page_table[refrence_string[i]].frame_number = page_table[index].frame_number;
				
				page_table[index].is_valid = 0;
				page_table[index].frame_number = -1;
				page_table[index].arrival_timestamp = 0;
				page_table[index].last_access_timestamp = 0;
				page_table[index].reference_count = 0;
				
				page_table[refrence_string[i]].is_valid = 1;
				page_table[refrence_string[i]].arrival_timestamp = timestamp;
				page_table[refrence_string[i]].last_access_timestamp = timestamp;
				page_table[refrence_string[i]].reference_count = 1;
				pagefaults++;
			}
		}
		timestamp++;
	}
	return pagefaults;	
}

int process_page_access_lru(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
	if(page_table[page_number].is_valid == 1){
		page_table[page_number].last_access_timestamp = current_timestamp;
		page_table[page_number].reference_count++;  
		
		return page_table[page_number].frame_number;
	} else{
		if(*frame_cnt > 0){
			page_table[page_number].frame_number = frame_pool[*frame_cnt - 1];
			*frame_cnt -= 1;
			page_table[page_number].is_valid = 1;
			page_table[page_number].last_access_timestamp = current_timestamp;
			page_table[page_number].reference_count++;
			
			return page_table[page_number].frame_number;
		} else{			
			int i, index;
			int min = 99999;
			
			for(i = 0; i < *table_cnt; i++){				
				if(page_table[i].is_valid == 1 && page_table[i].last_access_timestamp < min){
					min = page_table[i].last_access_timestamp;
					index = i;
				}
			}
			
			page_table[page_number].frame_number = page_table[index].frame_number;
			
			page_table[index].is_valid = 0;
			page_table[index].frame_number = -1;
			page_table[index].arrival_timestamp = 0;
			page_table[index].last_access_timestamp = 0;
			page_table[index].reference_count = 0;
			
			page_table[page_number].is_valid = 1;
			page_table[page_number].arrival_timestamp = current_timestamp;
			page_table[page_number].last_access_timestamp = current_timestamp;
			page_table[page_number].reference_count = 1;
			
			return page_table[page_number].frame_number;
		}
	}
}

int count_page_faults_lru(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
	int timestamp = 1;
	int pagefaults = 0;
	int i;
	
	for(i = 0; i < reference_cnt; i++){
		if(page_table[refrence_string[i]].is_valid == 1){
			page_table[refrence_string[i]].last_access_timestamp = timestamp;
			page_table[refrence_string[i]].reference_count++;     
		} else{
			if(frame_cnt > 0){
				page_table[refrence_string[i]].frame_number = frame_pool[frame_cnt - 1];
				frame_cnt -= 1;
				page_table[refrence_string[i]].is_valid = 1;
				page_table[refrence_string[i]].last_access_timestamp = timestamp;
				page_table[refrence_string[i]].reference_count++;
				pagefaults++;
			} else{
				int j, index;
				int min = 99999;
				
				for(j = 0; j < table_cnt; j++){				
					if(page_table[j].is_valid == 1 && page_table[j].last_access_timestamp < min){
						min = page_table[j].last_access_timestamp;
						index = j;
					}
				}
			
				page_table[refrence_string[i]].frame_number = page_table[index].frame_number;
				
				page_table[index].is_valid = 0;
				page_table[index].frame_number = -1;
				page_table[index].arrival_timestamp = 0;
				page_table[index].last_access_timestamp = 0;
				page_table[index].reference_count = 0;
				
				page_table[refrence_string[i]].is_valid = 1;
				page_table[refrence_string[i]].arrival_timestamp = timestamp;
				page_table[refrence_string[i]].last_access_timestamp = timestamp;
				page_table[refrence_string[i]].reference_count = 1;
				pagefaults++;
			}
		}
		timestamp++;
	}
	return pagefaults;	
}

int process_page_access_lfu(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
	if(page_table[page_number].is_valid == 1){
		page_table[page_number].last_access_timestamp = current_timestamp;
		page_table[page_number].reference_count++;  
		
		return page_table[page_number].frame_number;
	} else{
		if(*frame_cnt > 0){
			page_table[page_number].frame_number = frame_pool[*frame_cnt - 1];
			*frame_cnt -= 1;
			page_table[page_number].is_valid = 1;
			page_table[page_number].last_access_timestamp = current_timestamp;
			page_table[page_number].reference_count++;
			
			return page_table[page_number].frame_number;
		} else{			
			int i, index;
			int minRC = 99999;
			int minATS = 99999;
			
			for(i = 0; i < *table_cnt; i++){
				if(page_table[i].is_valid == 1 && page_table[i].reference_count < minRC){					
					minRC = page_table[i].reference_count;
					minATS = page_table[i].arrival_timestamp;
					index = i;
				} else if(page_table[i].is_valid == 1 && page_table[i].reference_count == minRC && page_table[i].arrival_timestamp < minATS){					
					minATS = page_table[i].arrival_timestamp;
					index = i;
				} 
			}
			
			page_table[page_number].frame_number = page_table[index].frame_number;
			
			page_table[index].is_valid = 0;
			page_table[index].frame_number = -1;
			page_table[index].arrival_timestamp = 0;
			page_table[index].last_access_timestamp = 0;
			page_table[index].reference_count = 0;
			
			page_table[page_number].is_valid = 1;
			page_table[page_number].arrival_timestamp = current_timestamp;
			page_table[page_number].last_access_timestamp = current_timestamp;
			page_table[page_number].reference_count = 1;
			
			return page_table[page_number].frame_number;
		}
	}
}

int count_page_faults_lfu(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
	int timestamp = 1;
	int pagefaults = 0;
	int i;
	
	for(i = 0; i < reference_cnt; i++){
		if(page_table[refrence_string[i]].is_valid == 1){
			page_table[refrence_string[i]].last_access_timestamp = timestamp;
			page_table[refrence_string[i]].reference_count++;     
		} else{
			if(frame_cnt > 0){
				page_table[refrence_string[i]].frame_number = frame_pool[frame_cnt - 1];
				frame_cnt -= 1;
				page_table[refrence_string[i]].is_valid = 1;
				page_table[refrence_string[i]].last_access_timestamp = timestamp;
				page_table[refrence_string[i]].reference_count++;
				pagefaults++;
			} else{
				int j, index;
				int minRC = 99999;
				int minATS = 99999;
			
				for(j = 0; j < table_cnt; j++){
					if(page_table[j].is_valid == 1 && page_table[j].reference_count < minRC){					
						minRC = page_table[j].reference_count;
						minATS = page_table[j].arrival_timestamp;
						index = j;
					} else if(page_table[j].is_valid == 1 && page_table[j].reference_count == minRC && page_table[j].arrival_timestamp < minATS){					
						minATS = page_table[j].arrival_timestamp;
						index = j;
					} 
				}
			
				page_table[refrence_string[i]].frame_number = page_table[index].frame_number;
				
				page_table[index].is_valid = 0;
				page_table[index].frame_number = -1;
				page_table[index].arrival_timestamp = 0;
				page_table[index].last_access_timestamp = 0;
				page_table[index].reference_count = 0;
				
				page_table[refrence_string[i]].is_valid = 1;
				page_table[refrence_string[i]].arrival_timestamp = timestamp;
				page_table[refrence_string[i]].last_access_timestamp = timestamp;
				page_table[refrence_string[i]].reference_count = 1;
				pagefaults++;
			}
		}
		timestamp++;
	}
	return pagefaults;	
}