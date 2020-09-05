/**
* @file main.c
* @brief this c file contians main function for tests
*
* @author Caining Wang
*
* @date 6/27/2020
*/
#include <stdio.h>
#include "math.h"
#include "oslabs.h"

void setup_pcb(struct PCB *inpcb, int process_id,int arrival_timestamp,int total_bursttime,int execution_starttime,int execution_endtime, int remaining_bursttime, int process_priority)
{
	(*inpcb).process_id = process_id;
	(*inpcb).arrival_timestamp = arrival_timestamp;
	(*inpcb).total_bursttime = total_bursttime;
	(*inpcb).execution_starttime = execution_starttime;
	(*inpcb).execution_endtime = execution_endtime;
	(*inpcb).remaining_bursttime = remaining_bursttime;
	(*inpcb).process_priority = process_priority;
}

void setup_mem(struct MEMORY_BLOCK *inmem, int start_address,int end_address,int segment_size,int process_id)
{
	(*inmem).start_address = start_address;
	(*inmem).end_address = end_address;
	(*inmem).segment_size = segment_size;
	(*inmem).process_id = process_id;
}

void setup_vmem(struct PTE *invmem, int is_valid,int frame_number,int arrival_timestamp,int last_access_timestamp, int reference_count)
{
	(*invmem).is_valid = is_valid;
	(*invmem).frame_number = frame_number;
	(*invmem).arrival_timestamp = arrival_timestamp;
	(*invmem).last_access_timestamp = last_access_timestamp;
	(*invmem).reference_count = reference_count;
}

void setup_rcb(struct RCB *inrcb, int request_id, int arrival_timestamp, int cylinder, int address, int process_id)
{
	(*inrcb).request_id = request_id;
	(*inrcb).arrival_timestamp = arrival_timestamp;
	(*inrcb).cylinder = cylinder;
	(*inrcb).address = address;
	(*inrcb).process_id = process_id;
}

int main(int argc, char** argv) {
	
	//DISK TEST
	//arrival
	/**
	struct RCB request_queue[TABLEMAX];
	int queue_cnt = 0;
	struct RCB current_request;
	setup_rcb(&current_request, 51 , 1, 53, 53, 51);
	struct RCB new_request;
	setup_rcb(&new_request, 52, 2, 54, 54, 52);
	int timestamp = 2;
	
	struct RCB output = handle_request_arrival_fcfs(request_queue, &queue_cnt, current_request, new_request, timestamp);
	
	printf("request_queue: [RID:%d, AT:%d, CYL:%d, ADDR:%d, PID:%d]\n", request_queue[0].request_id, request_queue[0].arrival_timestamp, 
		   				request_queue[0].cylinder, request_queue[0].address, request_queue[0].process_id);
	printf("queue_cnt: %d\n", queue_cnt);
	printf("output: [RID:%d, AT:%d, CYL:%d, ADDR:%d, PID:%d]\n", output.request_id, output.arrival_timestamp, 
		   				output.cylinder, output.address, output.process_id);
	**/
	
	//completion
	struct RCB disk;
	struct RCB request_queue[TABLEMAX];
	int queue_cnt = 3;
	int current_cylinder = 58;
	int scan_direction = 1;
	setup_rcb(&disk, 1 , 52, 58, 58, 1);
	request_queue[0] = disk;
	setup_rcb(&disk, 2 , 51, 58, 58, 2);
	request_queue[1] = disk;
	setup_rcb(&disk, 3 , 53, 58, 58, 3);
	request_queue[2] = disk;
	
	struct RCB output = handle_request_completion_look(request_queue, &queue_cnt, current_cylinder, scan_direction);
	
	printf("request_queue: [RID:%d, AT:%d, CYL:%d, ADDR:%d, PID:%d]\n", request_queue[0].request_id, request_queue[0].arrival_timestamp, 
		   				request_queue[0].cylinder, request_queue[0].address, request_queue[0].process_id);
	printf("request_queue: [RID:%d, AT:%d, CYL:%d, ADDR:%d, PID:%d]\n", request_queue[1].request_id, request_queue[1].arrival_timestamp, 
		   				request_queue[1].cylinder, request_queue[1].address, request_queue[1].process_id);
	printf("queue_cnt: %d\n", queue_cnt);
	printf("output: [RID:%d, AT:%d, CYL:%d, ADDR:%d, PID:%d]\n", output.request_id, output.arrival_timestamp, 
		   				output.cylinder, output.address, output.process_id);
	
	//VMEM  TEST
	//fault test
	/**
	struct PTE vmem;
	struct PTE page_table[TABLEMAX];
	int table_cnt = 8;
	int frame_cnt = 3;
	int frame_pool[POOLMAX] = {0, 1, 2};
	int reference_cnt = 11;
	int refrence_string[REFERENCEMAX] = {0, 3, 2, 6, 3, 4, 5, 2, 6, 4, 5};
	setup_vmem(&vmem, 0, -1, -1, -1, -1);
	page_table[0] = vmem;
	page_table[1] = vmem;
	page_table[2] = vmem;
	page_table[3] = vmem;
	page_table[4] = vmem;
	page_table[5] = vmem;
	page_table[6] = vmem;
	page_table[7] = vmem;
	
	int output = count_page_faults_lfu(page_table, table_cnt,  refrence_string, reference_cnt, frame_pool, frame_cnt);
	
	printf("output: %d\n", output);
	**/
	
	//access test
	/**
	struct PTE vmem;
	struct PTE page_table[TABLEMAX];
	int table_cnt = 8;
	int page_number = 0;
	int frame_pool[POOLMAX];
	int frame_cnt = 0;
	int current_timestamp = 12;
	setup_vmem(&vmem, 0, -1, -1, -1, -1);
	page_table[0] = vmem;
	setup_vmem(&vmem, 0, -1, -1, -1, -1);
	page_table[1] = vmem;
	setup_vmem(&vmem, 1, 10, 3, 3, 1);
	page_table[2] = vmem;
	setup_vmem(&vmem, 0, -1, -1, -1, -1);
	page_table[3] = vmem;
	setup_vmem(&vmem, 0, -1, -1, -1, -1);
	page_table[4] = vmem;
	setup_vmem(&vmem, 1, 20, 2, 4, 2);
	page_table[5] = vmem;
	setup_vmem(&vmem, 0, -1, -1, -1, -1);
	page_table[6] = vmem;
	setup_vmem(&vmem, 1, 30, 1, 1, 1);
	page_table[7] = vmem;
	
	int output = process_page_access_fifo(page_table, &table_cnt, page_number, frame_pool, &frame_cnt, current_timestamp);
		
	printf("table_cnt: %d\n", table_cnt);
	printf("frame_cnt: %d\n", frame_cnt);
	printf("output: %d\n", output);
	
	printf("memory_map: [IV:%d, FN:%d, ATS:%d, LATS:%d, RC:%d]\n", page_table[0].is_valid, page_table[0].frame_number, 
		   				page_table[0].arrival_timestamp, page_table[0].last_access_timestamp,page_table[0].reference_count);
	
	printf("memory_map: [IV:%d, FN:%d, ATS:%d, LATS:%d, RC:%d]\n", page_table[1].is_valid, page_table[1].frame_number, 
		   				page_table[1].arrival_timestamp, page_table[1].last_access_timestamp,page_table[1].reference_count);
	
	printf("memory_map: [IV:%d, FN:%d, ATS:%d, LATS:%d, RC:%d]\n", page_table[2].is_valid, page_table[2].frame_number, 
		   				page_table[2].arrival_timestamp, page_table[2].last_access_timestamp,page_table[2].reference_count);
	
	printf("memory_map: [IV:%d, FN:%d, ATS:%d, LATS:%d, RC:%d]\n", page_table[3].is_valid, page_table[3].frame_number, 
		   				page_table[3].arrival_timestamp, page_table[3].last_access_timestamp,page_table[3].reference_count);
	
	printf("memory_map: [IV:%d, FN:%d, ATS:%d, LATS:%d, RC:%d]\n", page_table[4].is_valid, page_table[4].frame_number, 
		   				page_table[4].arrival_timestamp, page_table[4].last_access_timestamp,page_table[4].reference_count);
	
	printf("memory_map: [IV:%d, FN:%d, ATS:%d, LATS:%d, RC:%d]\n", page_table[5].is_valid, page_table[5].frame_number, 
		   				page_table[5].arrival_timestamp, page_table[5].last_access_timestamp,page_table[5].reference_count);
	
	printf("memory_map: [IV:%d, FN:%d, ATS:%d, LATS:%d, RC:%d]\n", page_table[6].is_valid, page_table[6].frame_number, 
		   				page_table[6].arrival_timestamp, page_table[6].last_access_timestamp,page_table[6].reference_count);
	
	printf("memory_map: [IV:%d, FN:%d, ATS:%d, LATS:%d, RC:%d]\n", page_table[7].is_valid, page_table[7].frame_number, 
		   				page_table[7].arrival_timestamp, page_table[7].last_access_timestamp,page_table[7].reference_count);
	**/
	
	/**
	//MEM TEST
	struct MEMORY_BLOCK memory_map[MAPMAX];
	struct MEMORY_BLOCK mem, returned_mem;
	
	setup_mem(&mem, 0, 7, 8, 12);
	memory_map[0] = mem;
	setup_mem(&mem, 8, 15, 8, 0);
	memory_map[1] = mem;
	setup_mem(&mem, 16, 23, 8, 0);
	memory_map[2] = mem;
	setup_mem(&mem, 24, 27, 4, 10);
	memory_map[3] = mem;
	setup_mem(&mem, 28, 31, 4, 0);
	memory_map[4] = mem;
	
	int map_cnt = 5;
	int request_size = 10;
	int process_id = 32;
	setup_mem(&mem, 0, 7, 8, 12);
	
	next_fit_allocate(4,memory_map,&map_cnt,99,9);
	
	printf("map_cntmap_cnt: %d\n", map_cnt);
	
	printf("memory_map: [start_address:%d, end_address:%d, segment_size:%d, process_id:%d]\n", memory_map[0].start_address, 
		   				memory_map[0].end_address, memory_map[0].segment_size,memory_map[0].process_id);
	printf("memory_map: [start_address:%d, end_address:%d, segment_size:%d, process_id:%d]\n", memory_map[1].start_address, 
		   				memory_map[1].end_address, memory_map[1].segment_size,memory_map[1].process_id);
	printf("memory_map: [start_address:%d, end_address:%d, segment_size:%d, process_id:%d]\n", memory_map[2].start_address, 
		   				memory_map[2].end_address, memory_map[2].segment_size,memory_map[2].process_id);
	printf("memory_map: [start_address:%d, end_address:%d, segment_size:%d, process_id:%d]\n", memory_map[3].start_address, 
		   				memory_map[3].end_address, memory_map[3].segment_size,memory_map[3].process_id);
	printf("memory_map: [start_address:%d, end_address:%d, segment_size:%d, process_id:%d]\n", memory_map[4].start_address, 
		   				memory_map[4].end_address, memory_map[4].segment_size,memory_map[4].process_id);
	**/
	
	
	
	
	
	//CPU TEST
	//arrival test
	/**
	struct PCB ready_queue[QUEUEMAX];
	struct PCB current_process, new_process, returned_pcb;
	
	
	int timestamp = 24;
    int queue_cnt = 3;
	int time_quantum = 10;
	
	setup_pcb(&current_process,1,1,8,1,9,8,0);
	setup_pcb(&new_process,2,2,8,0,0,8,0);
	returned_pcb = handle_process_arrival_rr(ready_queue, &queue_cnt, current_process, new_process, timestamp, time_quantum	);
	
	printf("ready_queue: [PID:%d, AT:%d, TBT:%d, EST:%d, EET:%d, RBT:%d, Priority:%d]\n", ready_queue[0].process_id, ready_queue[0].arrival_timestamp, ready_queue[0].total_bursttime,
		   				ready_queue[0].execution_starttime, ready_queue[0].execution_endtime, ready_queue[0].remaining_bursttime, ready_queue[0].process_priority);
	printf("queue_cnt: %d\n", queue_cnt);
	printf("PCB: [PID:%d, AT:%d, TBT:%d, EST:%d, EET:%d, RBT:%d, Priority:%d]\n", returned_pcb.process_id, returned_pcb.arrival_timestamp, returned_pcb.total_bursttime,
		   				returned_pcb.execution_starttime, returned_pcb.execution_endtime, returned_pcb.remaining_bursttime, returned_pcb.process_priority);
	
	//complete test
	
		
	setup_pcb(&current_process,1,22,8,0, 0, 8, 0);
	ready_queue[0] = current_process;
	setup_pcb(&current_process,2,21,8,0, 0, 8, 0);
	ready_queue[1] = current_process;
	setup_pcb(&current_process,3,23,8,0, 0, 8, 0);
	ready_queue[2] = current_process;

	returned_pcb = handle_process_completion_rr(ready_queue, &queue_cnt, timestamp, time_quantum);	
	
	printf("ready_queue: [PID:%d, AT:%d, TBT:%d, EST:%d, EET:%d, RBT:%d, Priority:%d]\n", ready_queue[0].process_id, ready_queue[0].arrival_timestamp, ready_queue[0].total_bursttime,
		   				ready_queue[0].execution_starttime, ready_queue[0].execution_endtime, ready_queue[0].remaining_bursttime, ready_queue[0].process_priority);
	printf("ready_queue: [PID:%d, AT:%d, TBT:%d, EST:%d, EET:%d, RBT:%d, Priority:%d]\n", ready_queue[1].process_id, ready_queue[1].arrival_timestamp, ready_queue[1].total_bursttime,
		   				ready_queue[1].execution_starttime, ready_queue[1].execution_endtime, ready_queue[1].remaining_bursttime, ready_queue[1].process_priority);
	printf("ready_queue: [PID:%d, AT:%d, TBT:%d, EST:%d, EET:%d, RBT:%d, Priority:%d]\n", ready_queue[2].process_id, ready_queue[2].arrival_timestamp, ready_queue[2].total_bursttime,
		   				ready_queue[2].execution_starttime, ready_queue[2].execution_endtime, ready_queue[2].remaining_bursttime, ready_queue[2].process_priority);
	printf("queue_cnt: %d\n", queue_cnt);
	printf("PCB: [PID:%d, AT:%d, TBT:%d, EST:%d, EET:%d, RBT:%d, Priority:%d]\n", returned_pcb.process_id, returned_pcb.arrival_timestamp, returned_pcb.total_bursttime,
		   				returned_pcb.execution_starttime, returned_pcb.execution_endtime, returned_pcb.remaining_bursttime, returned_pcb.process_priority);
	**/
	
	return 0;
}


