// Resource request handling, validation, and deadlock avoidance 

#include "banker.h"
#include <sys/time.h>

extern PerformanceMetrics perf;

/*
 * Validate a resource request against basic constraints:
 * 1. Request <= Need[pid] (process cannot ask more than declared max)
 * 2. Request <= Available (enough resources must exist)
 */
bool validate_request(int pid, int request[]) {
    if (pid < 0 || pid >= sys.num_processes || !sys.process_active[pid]) {
        printf("[Error] Invalid process ID: %d\n", pid);
        return false;
    }

    // Check 1: Request <= Need[pid] 
    for (int j = 0; j < sys.num_resources; j++) {
        if (request[j] > sys.need[pid][j]) {
            printf("[Error] Request exceeds declared need for resource %d (%d > %d)\n",
                   j, request[j], sys.need[pid][j]);
            return false;
        }
    }

    // Check 2: Request <= Available 
    for (int j = 0; j < sys.num_resources; j++) {
        if (request[j] > sys.available[j]) {
            printf("[Error] Not enough available resources of type %d (%d requested, %d available)\n",
                   j, request[j], sys.available[j]);
            return false;
        }
    }

    return true;
}

/**
 * Handle a resource request from a process.
 * Implements full Banker's Algorithm request handling:
 * 1. Validate request
 * 2. Pretend to allocate
 * 3. Run safety algorithm on hypothetical state
 * 4. If safe: commit allocation; else: rollback and deny
 * 
 * Returns true if request is granted, false otherwise.
 */
bool request_resources(int pid, int request[]) {
    struct timeval start, end;

    printf("\n[Request] Process %s requesting resources: [", sys.process_names[pid]);
    for (int j = 0; j < sys.num_resources; j++) {
        printf("%d%s", request[j], j < sys.num_resources - 1 ? ", " : "");
    }
    printf("]\n");

    // Step 1: Basic validation 
    if (!validate_request(pid, request)) {
        log_request_denied(pid, request, "Request exceeds need or available resources");
        record_request_denied();
        return false;
    }

    // Step 2: Save current state for potential rollback 
    int temp_available[MAX_RESOURCES];
    int temp_allocation[MAX_PROCESSES][MAX_RESOURCES];
    int temp_need[MAX_PROCESSES][MAX_RESOURCES];

    save_state_snapshot(temp_available, temp_allocation, temp_need);

    // Step 3: Hypothetical allocation 
    perform_hypothetical_allocation(pid, request, temp_available, temp_allocation, temp_need);

    // Step 4: Check safety of hypothetical state 
    printf("  [Request] Checking safety of hypothetical state...\n");

    gettimeofday(&start, NULL);
    bool safe = check_safety_with_temp(temp_available, temp_allocation, temp_need, 
                                       sys.process_active, sys.num_processes, sys.num_resources);
    gettimeofday(&end, NULL);

    double time_ms = (end.tv_sec - start.tv_sec) * 1000.0 + 
                     (end.tv_usec - start.tv_usec) / 1000.0;
    record_safety_check(time_ms);

    if (safe) {
        // Step 5a: Safe - commit the allocation 
        for (int j = 0; j < sys.num_resources; j++) {
            sys.available[j] = temp_available[j];
            sys.allocation[pid][j] = temp_allocation[pid][j];
            sys.need[pid][j] = temp_need[pid][j];
        }

        record_request_granted();
        log_request_granted(pid, request);

        printf("  [Request] GRANTED! System remains in safe state.\n");
        return true;
    } else {
        // Step 5b: Unsafe - rollback and deny 
        restore_state_from_snapshot(temp_available, temp_allocation, temp_need);

        record_request_denied();
        log_request_denied(pid, request, "Would lead to unsafe state");

        printf("  [Request] DENIED! Granting would lead to UNSAFE state.\n");
        printf("  [Request] Rollback performed. No resources allocated.\n");
        return false;
    }
}

/*
 * Release resources held by a process back to the available pool.
 * Returns true if successful.
 */
bool release_resources(int pid, int release[]) {
    if (pid < 0 || pid >= sys.num_processes || !sys.process_active[pid]) {
        printf("[Error] Invalid process ID: %d\n", pid);
        return false;
    }

    // Verify process actually holds these resources 
    for (int j = 0; j < sys.num_resources; j++) {
        if (release[j] > sys.allocation[pid][j]) {
            printf("[Error] Cannot release more than allocated for resource %d\n", j);
            return false;
        }
    }

    for (int j = 0; j < sys.num_resources; j++) {
        sys.allocation[pid][j] -= release[j];
        sys.available[j] += release[j];
        sys.need[pid][j] = sys.maximum[pid][j] - sys.allocation[pid][j];
    }

    log_resource_release(pid, release);
    printf("[Release] Process %s released resources: [", sys.process_names[pid]);
    for (int j = 0; j < sys.num_resources; j++) {
        printf("%d%s", release[j], j < sys.num_resources - 1 ? ", " : "");
    }
    printf("]\n");

    return true;
}

