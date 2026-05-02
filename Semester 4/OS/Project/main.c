/*
 * Entry point for Banker's Algorithm Simulator
 * Supports both interactive mode and automated demo mode.
 */

#include "banker.h"

// External function for demo mode 
static void run_demo_scenario(void);
static void run_custom_demo(void);

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
    printf("\n");
    print_separator();
    print_header("BANKER'S ALGORITHM SIMULATOR");
    print_header("Operating Systems");
    print_separator();
    printf("\n");
    printf("Team Members:\n");
    printf("  - Murtaza Hunaid Terai (24K-0782)\n");
    printf("  - Adnan Hatim (24K-0656)\n");
    printf("\n");

    // Initialize logging and performance metrics 
    init_logger();
    init_performance_metrics();

    int mode;
    printf("Select Mode:\n");
    printf("  1. Interactive Mode (manual input)\n");
    printf("  2. Demo Mode (pre-configured example)\n");
    printf("  3. Custom Demo (unsafe state demonstration)\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    if (mode == 2) {
        run_demo_scenario();
    } else if (mode == 3) {
        run_custom_demo();
    } else {
        // Interactive mode - need to initialize system first 
        int num_p, num_r;

        printf("\n=== System Initialization ===\n");
        printf("Enter number of processes (max %d): ", MAX_PROCESSES);
        scanf("%d", &num_p);

        printf("Enter number of resource types (max %d): ", MAX_RESOURCES);
        scanf("%d", &num_r);

        if (num_p <= 0 || num_p > MAX_PROCESSES || num_r <= 0 || num_r > MAX_RESOURCES) {
            printf("[Error] Invalid configuration.\n");
            close_logger();
            return 1;
        }

        init_system(num_p, num_r);

        interactive_set_resources();

        printf("\n=== Add Processes ===\n");
        for (int i = 0; i < num_p; i++) {
            printf("\nConfigure Process %d:\n", i);
            interactive_add_process();
        }

        run_interactive_menu();
    }

    cleanup_system();
    return 0;
}

// Pre-configured demo scenario demonstrating safe state and proper request handling.
static void run_demo_scenario(void) {
    printf("\n[Demo] Loading pre-configured scenario...\n\n");

    // 5 processes, 3 resource types 
    init_system(5, 3);

    int totals[] = {10, 5, 7};
    set_total_resources(totals);

    int p0_max[] = {7, 5, 3};
    add_process(0, p0_max, "P0");

    int p1_max[] = {3, 2, 2};
    add_process(1, p1_max, "P1");

    int p2_max[] = {9, 0, 2};
    add_process(2, p2_max, "P2");

    int p3_max[] = {2, 2, 2};
    add_process(3, p3_max, "P3");

    int p4_max[] = {4, 3, 3};
    add_process(4, p4_max, "P4");

    // Set initial allocations 
    int p0_alloc[] = {0, 1, 0};
    request_resources(0, p0_alloc);

    int p1_alloc[] = {2, 0, 0};
    request_resources(1, p1_alloc);

    int p2_alloc[] = {3, 0, 2};
    request_resources(2, p2_alloc);

    int p3_alloc[] = {2, 1, 1};
    request_resources(3, p3_alloc);

    int p4_alloc[] = {0, 0, 2};
    request_resources(4, p4_alloc);

    printf("\n=== Initial System State ===\n");
    display_all_matrices();

    printf("\n=== Running Safety Algorithm ===\n");
    SafetyResult result = run_safety_algorithm();
    display_safe_sequence(&result);

    if (result.is_safe) {
        log_safe_state(result.safe_sequence, result.sequence_length);
    }

    printf("\n=== Testing Resource Request ===\n");
    printf("P1 requests (1, 0, 2)...\n");
    int req1[] = {1, 0, 2};
    request_resources(1, req1);

    printf("\n=== Updated System State ===\n");
    display_all_matrices();

    printf("\n=== Re-check Safety ===\n");
    result = run_safety_algorithm();
    display_safe_sequence(&result);

    printf("\n=== Testing Unsafe Request ===\n");
    printf("P4 requests (3, 3, 0) - should be denied (insufficient available)...\n");
    int bad_req[] = {3, 3, 0};
    request_resources(4, bad_req);

    printf("\n=== Performance Report ===\n");
    print_performance_report();

    printf("\n=== Saving Log and Report ===\n");
    save_performance_report("demo_performance.txt");
    printf("Log saved to %s\n", LOG_FILE);
}

// Custom demo showing an unsafe state scenario and rollback 
static void run_custom_demo(void) {
    printf("\n[Custom Demo] Unsafe State Demonstration...\n\n");

    // 3 processes, 3 resources 
    init_system(3, 3);

    int totals[] = {10, 5, 7};
    set_total_resources(totals);

    int p0_max[] = {7, 5, 3};
    add_process(0, p0_max, "P0");

    int p1_max[] = {3, 2, 2};
    add_process(1, p1_max, "P1");

    int p2_max[] = {9, 0, 2};
    add_process(2, p2_max, "P2");

    // Initial allocations 
    int a0[] = {0, 1, 0};
    request_resources(0, a0);

    int a1[] = {2, 0, 0};
    request_resources(1, a1);

    int a2[] = {3, 0, 2};
    request_resources(2, a2);

    printf("\n=== Current State ===\n");
    display_all_matrices();

    printf("\n=== Safety Check ===\n");
    SafetyResult res = run_safety_algorithm();
    display_safe_sequence(&res);

    // This request should lead to unsafe state and be denied 
    printf("\n=== P0 requests (7, 4, 3) - Should be denied (unsafe) ===\n");
    int bad[] = {7, 4, 3};
    request_resources(0, bad);

    printf("\n=== Final State (unchanged after rollback) ===\n");
    display_all_matrices();

    print_performance_report();
    save_performance_report("custom_demo_performance.txt");
}

// Cleanup all resources before exit 
void cleanup_system(void) {
    close_logger();
    printf("\n[System] Cleanup complete.\n");
}

