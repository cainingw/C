/**
* @file cpu.c
* @brief this c file is for CPU Scheduling
*
* @author Caining Wang
*
* @date 6/27/2020
*/
#include <stdio.h>
#include "math.h"
#include "oslabs.h"

void setuppcb(struct PCB *inpcb, int process_id,int arrival_timestamp,int total_bursttime,int execution_starttime,int execution_endtime, int remaining_bursttime, int process_priority)
{
	(*inpcb).process_id = process_id;
	(*inpcb).arrival_timestamp = arrival_timestamp;
	(*inpcb).total_bursttime = total_bursttime;
	(*inpcb).execution_starttime = execution_starttime;
	(*inpcb).execution_endtime = execution_endtime;
	(*inpcb).remaining_bursttime = remaining_bursttime;
	(*inpcb).process_priority = process_priority;
}

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp){
	if(current_process.process_id == 0){
		new_process.execution_starttime = timestamp;
		new_process.execution_endtime = timestamp + new_process.total_bursttime;
		new_process.remaining_bursttime = new_process.total_bursttime;
		
		return new_process;
	} else{
		if(new_process.process_priority >= current_process.process_priority){
			new_process.execution_starttime = 0;
			new_process.execution_endtime = 0;
			new_process.remaining_bursttime = new_process.total_bursttime;
			ready_queue[*queue_cnt] = new_process;
			*queue_cnt += 1;
			
			return current_process;
		} else{
			new_process.execution_starttime = timestamp;
			new_process.execution_endtime = timestamp + new_process.total_bursttime;
			new_process.remaining_bursttime = new_process.total_bursttime;
			
			current_process.remaining_bursttime -= timestamp - current_process.execution_starttime;
			current_process.execution_endtime = 0;
			ready_queue[*queue_cnt] = current_process;
			*queue_cnt += 1;
			
			return new_process;
		}
	}
}
		
struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp){
	if(*queue_cnt == 0){
		struct PCB NULLPCB;
		setuppcb(&NULLPCB,0,0,0,0,0,0,0);
		
		return NULLPCB;
	} else{
		int priority = 99999;
		int index, i;
		struct PCB ReturnPCB;
		for (i = 0; i < *queue_cnt; i++){
			if(ready_queue[i].process_priority < priority){
				priority = ready_queue[i].process_priority;
				index = i;
			}
		}
		ReturnPCB = ready_queue[index];
		for(i = index; i < *queue_cnt-1; i++){
            ready_queue[i] = ready_queue[i + 1];
        }
		*queue_cnt -= 1;
		ReturnPCB.execution_starttime = timestamp;
		ReturnPCB.execution_endtime = timestamp + ReturnPCB.remaining_bursttime;
		
		return ReturnPCB;
	}
}
			
struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp){
	if(current_process.process_id == 0){
		new_process.execution_starttime = time_stamp;
		new_process.execution_endtime = time_stamp + new_process.total_bursttime;
		new_process.remaining_bursttime = new_process.total_bursttime;
			
		return new_process;
	} else{
		if(new_process.total_bursttime >= current_process.remaining_bursttime){
			new_process.execution_starttime = 0;
			new_process.execution_endtime = 0;
			new_process.remaining_bursttime = new_process.total_bursttime;
			ready_queue[*queue_cnt] = new_process;
			*queue_cnt = *queue_cnt + 1;
			
			return current_process;
		} else{
			new_process.execution_starttime = time_stamp;
			new_process.execution_endtime = time_stamp + new_process.total_bursttime;
			new_process.remaining_bursttime = new_process.total_bursttime;
						
			current_process.remaining_bursttime -= (time_stamp - current_process.execution_starttime);
			current_process.execution_starttime = 0;
			current_process.execution_endtime = 0;
			ready_queue[*queue_cnt] = current_process;
			*queue_cnt += 1;
			
			return new_process;
		}
	}
}
	
	
	
struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp){
	if(*queue_cnt == 0){
		struct PCB NULLPCB;
		setuppcb(&NULLPCB,0,0,0,0,0,0,0);
		
		return NULLPCB;
	} else{
		int rbt = 99999;
		int index, i;
		struct PCB ReturnPCB;
		for (i = 0; i < *queue_cnt; i++){
			if(ready_queue[i].remaining_bursttime < rbt){
				rbt = ready_queue[i].remaining_bursttime;
				index = i;
			}
		}
		ReturnPCB = ready_queue[index];
		for(i = index; i < *queue_cnt-1; i++){
            ready_queue[i] = ready_queue[i + 1];
        }
		*queue_cnt -= 1;
		ReturnPCB.execution_starttime = timestamp;
		ReturnPCB.execution_endtime = timestamp + ReturnPCB.remaining_bursttime;
		
		return ReturnPCB;
	}
}

struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum){
	if(current_process.process_id == 0){
		new_process.execution_starttime = timestamp;
		new_process.execution_endtime = timestamp + MIN(time_quantum, new_process.total_bursttime);
		new_process.remaining_bursttime = new_process.total_bursttime;
			
		return new_process;
	} else{
		new_process.execution_starttime = 0;
		new_process.execution_endtime = 0;
		new_process.remaining_bursttime = new_process.total_bursttime;
		ready_queue[*queue_cnt] = new_process;
		*queue_cnt = *queue_cnt + 1;
			
		return current_process;
	}
}

struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp, int time_quantum){
	if(*queue_cnt == 0){
		struct PCB NULLPCB;
		setuppcb(&NULLPCB,0,0,0,0,0,0,0);
		
		return NULLPCB;
	} else{
		int at = 99999;
		int index, i;
		struct PCB ReturnPCB;
		for (i = 0; i < *queue_cnt; i++){
			if(ready_queue[i].arrival_timestamp < at){
				at = ready_queue[i].arrival_timestamp;
				index = i;
			}
		}
		
		ReturnPCB = ready_queue[index];
		for(i = index; i < *queue_cnt-1; i++){
            ready_queue[i] = ready_queue[i + 1];
        }
		*queue_cnt -= 1;
		ReturnPCB.execution_starttime = timestamp;
		ReturnPCB.execution_endtime = timestamp + MIN(time_quantum, ReturnPCB.total_bursttime);
		
		return ReturnPCB;
	}
}

