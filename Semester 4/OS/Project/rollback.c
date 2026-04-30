/*State snapshot and rollback simulation */

#include "banker.h"

/**
 * Save a complete snapshot of the current system state.
 * Used before hypothetical allocations to enable rollback.
 */
void save_state_snapshot(int temp_avail[], int temp_alloc[][MAX_RESOURCES], int temp_need[][MAX_RESOURCES]) {
    for (int j = 0; j < sys.num_resources; j++) {
        temp_avail[j] = sys.available[j];
    }

    for (int i = 0; i < sys.num_processes; i++) {
        for (int j = 0; j < sys.num_resources; j++) {
            temp_alloc[i][j] = sys.allocation[i][j];
            temp_need[i][j] = sys.need[i][j];
        }
    }
}

/**
 * Restore system state from a saved snapshot.
 * Used when a hypothetical allocation leads to an unsafe state.
 */
void restore_state_from_snapshot(int temp_avail[], int temp_alloc[][MAX_RESOURCES], 
                                 int temp_need[][MAX_RESOURCES]) {
    for (int j = 0; j < sys.num_resources; j++) {
        sys.available[j] = temp_avail[j];
    }

    for (int i = 0; i < sys.num_processes; i++) {
        for (int j = 0; j < sys.num_resources; j++) {
            sys.allocation[i][j] = temp_alloc[i][j];
            sys.need[i][j] = temp_need[i][j];
        }
    }

    printf("  [Rollback] System state restored to pre-request snapshot.\n");
    log_state_transition("State rolled back due to unsafe hypothetical allocation");
}

/**
 * Perform a hypothetical allocation on temporary state variables.
 * This modifies only the temporary copies, not the actual system state.
 * Used to test if granting a request keeps the system safe.
 */
void perform_hypothetical_allocation(int pid, int request[], int temp_avail[], int temp_alloc[][MAX_RESOURCES], 
                                     int temp_need[][MAX_RESOURCES]) {
    for (int j = 0; j < sys.num_resources; j++) {
        temp_avail[j] -= request[j];
        temp_alloc[pid][j] += request[j];
        temp_need[pid][j] -= request[j];
    }

    printf("  [Hypothetical] Temporarily allocated. Testing safety...\n");
}

