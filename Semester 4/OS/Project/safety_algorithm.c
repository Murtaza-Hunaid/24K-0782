// Safety Algorithm and deadlock avoidance verification 

#include "banker.h"
#include <sys/time.h>

/**
 * Run the Banker's Safety Algorithm on the current system state.
 * Returns a SafetyResult containing the safe sequence (if one exists).
 * 
 * Algorithm:
 * 1. Work = Available, Finish[i] = false for all i
 * 2. Find i where Finish[i] == false AND Need[i] <= Work
 * 3. If found: Work = Work + Allocation[i], Finish[i] = true, goto step 2
 * 4. If all Finish[i] == true, system is in safe state
 */
SafetyResult run_safety_algorithm(void) {
    SafetyResult result;
    result.is_safe = false;
    result.sequence_length = 0;

    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES];

    // Initialize Work = Available 
    for (int j = 0; j < sys.num_resources; j++) {
        work[j] = sys.available[j];
    }

    // Initialize Finish = false for active processes 
    for (int i = 0; i < sys.num_processes; i++) {
        finish[i] = !sys.process_active[i];  // Inactive processes count as finished 
    }

    int count = 0;
    bool found;

    // Step 2-3: Find processes that can complete 
    while (count < sys.num_processes) {
        found = false;

        for (int i = 0; i < sys.num_processes; i++) {
            if (finish[i]) continue; 

            // Check if Need[i] <= Work 
            bool can_execute = true;
            for (int j = 0; j < sys.num_resources; j++) {
                if (sys.need[i][j] > work[j]) {
                    can_execute = false;
                    break;
                }
            }

            if (can_execute) {
                for (int j = 0; j < sys.num_resources; j++) {
                    work[j] += sys.allocation[i][j];
                }
                finish[i] = true;
                result.safe_sequence[count] = i;
                count++;
                found = true;

                printf("  [Safety] Process %s can execute. Work becomes: [", sys.process_names[i]);
                for (int j = 0; j < sys.num_resources; j++) {
                    printf("%d%s", work[j], j < sys.num_resources - 1 ? ", " : "");
                }
                printf("]\n");
            }
        }

        if (!found) {
            break;
        }
    }

    // Check if all active processes finished 
    result.is_safe = true;
    for (int i = 0; i < sys.num_processes; i++) {
        if (sys.process_active[i] && !finish[i]) {
            result.is_safe = false;
            break;
        }
    }

    if (result.is_safe) {
        result.sequence_length = count;
        printf("  [Safety] SAFE STATE FOUND! Sequence: <");
        for (int i = 0; i < result.sequence_length; i++) {
            printf("%s%s", sys.process_names[result.safe_sequence[i]], 
                   i < result.sequence_length - 1 ? ", " : "");
        }
        printf(">\n");
    } else {
        printf("  [Safety] UNSAFE STATE! No safe sequence exists.\n");
    }

    return result;
}

/*
 * Check safety using temporary state for hypothetical allocation testing
 */
bool check_safety_with_temp(int temp_available[], int temp_allocation[][MAX_RESOURCES], 
                            int temp_need[][MAX_RESOURCES], bool temp_active[], int num_p, int num_r) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES];

    for (int j = 0; j < num_r; j++) {
        work[j] = temp_available[j];
    }

    for (int i = 0; i < num_p; i++) {
        finish[i] = !temp_active[i];
    }

    int count = 0;
    bool found;

    while (count < num_p) {
        found = false;

        for (int i = 0; i < num_p; i++) {
            if (finish[i]) continue;

            bool can_execute = true;
            for (int j = 0; j < num_r; j++) {
                if (temp_need[i][j] > work[j]) {
                    can_execute = false;
                    break;
                }
            }

            if (can_execute) {
                for (int j = 0; j < num_r; j++) {
                    work[j] += temp_allocation[i][j];
                }
                finish[i] = true;
                count++;
                found = true;
            }
        }

        if (!found) break;
    }

    for (int i = 0; i < num_p; i++) {
        if (temp_active[i] && !finish[i]) {
            return false;
        }
    }
    return true;
}

