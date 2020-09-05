/**
* @file disk.c
* @brief this c file is for Disk Scheduling
*
* @author Caining Wang
*
* @date 6/29/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "oslabs.h"
void setuprcb(struct RCB *inrcb, int request_id, int arrival_timestamp, int cylinder, int address, int process_id)
{
	(*inrcb).request_id = request_id;
	(*inrcb).arrival_timestamp = arrival_timestamp;
	(*inrcb).cylinder = cylinder;
	(*inrcb).address = address;
	(*inrcb).process_id = process_id;
}

struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp){
	if(current_request.request_id == 0){
		return new_request;
	} else{
		request_queue[*queue_cnt] = new_request;
		*queue_cnt += 1;
		
		return current_request;
	}	
}

struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX],int *queue_cnt){
	if(*queue_cnt <= 0){
		struct RCB NULLRCB;
		setuprcb(&NULLRCB, 0, 0, 0, 0, 0);
		
		return NULLRCB;
	} else{
		int i, index;
		int min = 99999;
		
		for(i = 0; i < *queue_cnt; i++){
			if(request_queue[i].arrival_timestamp < min){
				min = request_queue[i].arrival_timestamp;
				index = i;
			}
		}
		
		struct RCB RETURNRCB;
		RETURNRCB = request_queue[index];
		
		*queue_cnt -= 1;
		for(i = index; i < *queue_cnt; i++){
			request_queue[i] = request_queue[i+1];
		}
		
		return RETURNRCB;
	}
}

struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp){
	if(current_request.request_id == 0){
		return new_request;
	} else{
		request_queue[*queue_cnt] = new_request;
		*queue_cnt += 1;
		
		return current_request;
	}	
}

struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt,int current_cylinder){
	if(*queue_cnt <= 0){
		struct RCB NULLRCB;
		setuprcb(&NULLRCB, 0, 0, 0, 0, 0);
		
		return NULLRCB;
	} else{
		int i, index, cyl_diff;
		int min_diff = 99999;
		int min_at = 999999;
		
		for(i = 0; i < *queue_cnt; i++){
			cyl_diff = abs(current_cylinder - request_queue[i].cylinder);
			if(cyl_diff < min_diff){
				min_diff = cyl_diff;
				min_at = request_queue[i].arrival_timestamp;
				index = i;
			} else if(cyl_diff == min_diff && request_queue[i].arrival_timestamp < min_at){
				min_at = request_queue[i].arrival_timestamp;
				index = i;
			}
		}
		
		struct RCB RETURNRCB;
		RETURNRCB = request_queue[index];
		
		*queue_cnt -= 1;
		for(i = index; i < *queue_cnt; i++){
			request_queue[i] = request_queue[i+1];
		}
		
		return RETURNRCB;
	}
}

struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp){
	if(current_request.request_id == 0){
		return new_request;
	} else{
		request_queue[*queue_cnt] = new_request;
		*queue_cnt += 1;
		
		return current_request;
	}	
}

struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX],int *queue_cnt, int current_cylinder, int scan_direction){
	if(*queue_cnt <= 0){
		struct RCB NULLRCB;
		setuprcb(&NULLRCB, 0, 0, 0, 0, 0);
		
		return NULLRCB;
	} else{
		int i, cyl_diff;
		int min_diff = 99999;
		int min_at = 999999;
		int index = -1;
		for(i = 0; i < *queue_cnt; i++){
			if(current_cylinder == request_queue[i].cylinder && request_queue[i].arrival_timestamp < min_at){
				min_at = request_queue[i].arrival_timestamp;
				index = i;
			}
		}
		if(index > -1){
			struct RCB RETURNRCB;
			RETURNRCB = request_queue[index];
		
			*queue_cnt -= 1;
			for(i = index; i < *queue_cnt; i++){
				request_queue[i] = request_queue[i+1];
			}
		
			return RETURNRCB;
		} else{	
			for(i = 0; i < *queue_cnt; i++){
				if(scan_direction == 1){
					cyl_diff = request_queue[i].cylinder - current_cylinder;
				}else if(scan_direction == 0){
					cyl_diff = current_cylinder - request_queue[i].cylinder;
				}
				
				if(cyl_diff > 0 && cyl_diff < min_diff){
					min_diff = cyl_diff;
					index = i;
				}
			}
			if(index > -1){
				struct RCB RETURNRCB;
				RETURNRCB = request_queue[index];
		
				*queue_cnt -= 1;
				for(i = index; i < *queue_cnt; i++){
					request_queue[i] = request_queue[i+1];
				}
		
				return RETURNRCB;
			}
			else{
				for(i = 0; i < *queue_cnt; i++){
					cyl_diff = abs(current_cylinder - request_queue[i].cylinder);
					if(cyl_diff < min_diff){
					min_diff = cyl_diff;
					min_at = request_queue[i].arrival_timestamp;
					index = i;
					} else if(cyl_diff == min_diff && request_queue[i].arrival_timestamp < min_at){
						min_at = request_queue[i].arrival_timestamp;
						index = i;
					}
				}
		
				struct RCB RETURNRCB;
				RETURNRCB = request_queue[index];
		
				*queue_cnt -= 1;
				for(i = index; i < *queue_cnt; i++){
					request_queue[i] = request_queue[i+1];
				}
		
				return RETURNRCB;
			}
		}
	}
}