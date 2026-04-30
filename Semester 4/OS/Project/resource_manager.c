/*Resource type representation and management*/

#include "banker.h"

/**
 * Initialize resource types with their total instance counts.
 * Automatically sets available = total for each resource type.
 */
void initialize_resources(int counts[], int num_r) {
    if (num_r > MAX_RESOURCES) {
        printf("[Error] Number of resources exceeds maximum %d\n", MAX_RESOURCES);
        return;
    }

    sys.num_resources = num_r;

    for (int j = 0; j < num_r; j++) {
        sys.total_resources[j] = counts[j];
        sys.available[j] = counts[j];
    }

    printf("[Resources] Initialized %d resource types:\n", num_r);
    for (int j = 0; j < num_r; j++) {
        printf("  Resource %d (R%d): %d total instances\n", j, j, counts[j]);
    }

    log_state_transition("Resources initialized");
}

/*Display current resource status: total, allocated, and available.*/
void display_resource_status(void) {
    int allocated[MAX_RESOURCES] = {0};

    for (int i = 0; i < sys.num_processes; i++) {
        if (!sys.process_active[i]) continue;
        for (int j = 0; j < sys.num_resources; j++) {
            allocated[j] += sys.allocation[i][j];
        }
    }

    print_separator();
    printf("%-15s", "Resource");
    for (int j = 0; j < sys.num_resources; j++) {
        printf("R%-9d", j);
    }
    printf("\n");
    print_separator();

    printf("%-15s", "Total");
    for (int j = 0; j < sys.num_resources; j++) {
        printf("%-10d", sys.total_resources[j]);
    }
    printf("\n");

    printf("%-15s", "Allocated");
    for (int j = 0; j < sys.num_resources; j++) {
        printf("%-10d", allocated[j]);
    }
    printf("\n");

    printf("%-15s", "Available");
    for (int j = 0; j < sys.num_resources; j++) {
        printf("%-10d", sys.available[j]);
    }
    printf("\n");
    print_separator();
}

/**
 * Check if requested resources are available.
 * Returns true if all requested amounts <= available amounts.
 */
bool check_resource_availability(int request[]) {
    for (int j = 0; j < sys.num_resources; j++) {
        if (request[j] > sys.available[j]) {
            return false;
        }
    }
    return true;
}

/**
 * Update available resources by adding or subtracting delta amounts.
 * add = true: add to available (release); add = false: subtract (allocate)
 */
void update_available_resources(int delta[], bool add) {
    for (int j = 0; j < sys.num_resources; j++) {
        if (add) {
            sys.available[j] += delta[j];
        } else {
            sys.available[j] -= delta[j];
        }
    }
}

/* Get the total instance count for a specific resource type.*/
int get_resource_instance_count(int rtype) {
    if (rtype < 0 || rtype >= sys.num_resources) {
        return -1;
    }
    return sys.total_resources[rtype];
}

