/*Core data structure initialization and management */

#include "banker.h"

SystemState sys;

/**
 * Initialize the system with given number of processes and resources.
 * All matrices are zeroed out, no processes are active initially.
 */
void init_system(int num_p, int num_r) {
    if (num_p > MAX_PROCESSES || num_r > MAX_RESOURCES) {
        printf("Error: Exceeds maximum limits (Processes: %d, Resources: %d)\n", 
               MAX_PROCESSES, MAX_RESOURCES);
        return;
    }

    sys.num_processes = num_p;
    sys.num_resources = num_r;

    memset(sys.total_resources, 0, sizeof(sys.total_resources));
    memset(sys.available, 0, sizeof(sys.available));
    memset(sys.allocation, 0, sizeof(sys.allocation));
    memset(sys.maximum, 0, sizeof(sys.maximum));
    memset(sys.need, 0, sizeof(sys.need));
    memset(sys.process_active, 0, sizeof(sys.process_active));

    for (int i = 0; i < num_p; i++) {
        snprintf(sys.process_names[i], 32, "P%d", i);
    }

    printf("[System] Initialized with %d processes and %d resource types.\n", num_p, num_r);
}
void add_process(int pid, int max_demand[], const char *name) {
    if (pid < 0 || pid >= sys.num_processes) {
        printf("[Error] Invalid process ID: %d\n", pid);
        return;
    }

    sys.process_active[pid] = true;

    if (name && strlen(name) > 0) {
        strncpy(sys.process_names[pid], name, 31);
        sys.process_names[pid][31] = '\0';
    }

    for (int j = 0; j < sys.num_resources; j++) {
        sys.maximum[pid][j] = max_demand[j];
        sys.need[pid][j] = max_demand[j];  /* Initially need = maximum since allocation is 0 */
        sys.allocation[pid][j] = 0;
    }

    log_process_added(pid, sys.process_names[pid], max_demand);
    printf("[System] Process %s (PID %d) added with max demand set.\n", 
           sys.process_names[pid], pid);
}

void remove_process(int pid) {
    if (pid < 0 || pid >= sys.num_processes || !sys.process_active[pid]) {
        printf("[Error] Invalid or inactive process ID: %d\n", pid);
        return;
    }
    
    for (int j = 0; j < sys.num_resources; j++) {
        sys.available[j] += sys.allocation[pid][j];
        sys.allocation[pid][j] = 0;
        sys.maximum[pid][j] = 0;
        sys.need[pid][j] = 0;
    }

    sys.process_active[pid] = false;
    log_process_removed(pid);
    printf("[System] Process %s (PID %d) removed. Resources released.\n", 
           sys.process_names[pid], pid);
}

void calculate_need_matrix(void) {
    for (int i = 0; i < sys.num_processes; i++) {
        if (!sys.process_active[i]) continue;
        for (int j = 0; j < sys.num_resources; j++) {
            sys.need[i][j] = sys.maximum[i][j] - sys.allocation[i][j];
        }
    }
}

void set_total_resources(int totals[]) {
    for (int j = 0; j < sys.num_resources; j++) {
        sys.total_resources[j] = totals[j];
        sys.available[j] = totals[j];
    }

    printf("[System] Total resources configured: ");
    for (int j = 0; j < sys.num_resources; j++) {
        printf("R%d=%d ", j, sys.total_resources[j]);
    }
    printf("\n");

    log_state_transition("Total resources configured");
}

void reset_system(void) {
    memset(&sys, 0, sizeof(SystemState));
    printf("[System] Full reset completed.\n");
    log_state_transition("System fully reset");
}

