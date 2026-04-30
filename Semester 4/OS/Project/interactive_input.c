/* Interactive runtime prompt and menu system*/

#include "banker.h"

void print_menu(void) {
    print_separator();
    print_header("BANKER'S ALGORITHM SIMULATOR");
    print_separator();
    printf("  1.  Display System State (Matrices)\n");
    printf("  2.  Display Process Status\n");
    printf("  3.  Display Resource Status\n");
    printf("  4.  Add/Configure Process\n");
    printf("  5.  Remove Process\n");
    printf("  6.  Request Resources\n");
    printf("  7.  Release Resources\n");
    printf("  8.  Run Safety Algorithm\n");
    printf("  9.  Display Safe Sequence\n");
    printf("  10. Display Performance Report\n");
    printf("  11. Save Performance Report to File\n");
    printf("  12. Reset System\n");
    printf("  0.  Exit\n");
    print_separator();
    printf("Enter choice: ");
}

/*Interactive prompt to add a new process with maximum demands.*/
void interactive_add_process(void) {
    int pid;
    int max_demand[MAX_RESOURCES];
    char name[32];

    printf("\nEnter Process ID (0 to %d): ", sys.num_processes - 1);
    scanf("%d", &pid);

    if (pid < 0 || pid >= sys.num_processes) {
        printf("[Error] Invalid process ID.\n");
        return;
    }

    if (sys.process_active[pid]) {
        printf("[Warning] Process %d already active. Overwrite? (1=Yes, 0=No): ", pid);
        int confirm;
        scanf("%d", &confirm);
        if (!confirm) return;
    }

    printf("Enter Process Name (or 'auto' for default): ");
    scanf("%s", name);

    printf("Enter Maximum Demand for each resource type (%d types):\n", sys.num_resources);
    for (int j = 0; j < sys.num_resources; j++) {
        printf("  Resource R%d max demand: ", j);
        scanf("%d", &max_demand[j]);

        if (max_demand[j] > sys.total_resources[j]) {
            printf("[Error] Max demand cannot exceed total resources (%d). Setting to %d.\n",
                   sys.total_resources[j], sys.total_resources[j]);
            max_demand[j] = sys.total_resources[j];
        }
    }

    if (strcmp(name, "auto") == 0) {
        add_process(pid, max_demand, NULL);
    } else {
        add_process(pid, max_demand, name);
    }
}

/*Interactive prompt for a process to request resources.*/
void interactive_request_resources(void) {
    int pid;
    int request[MAX_RESOURCES];

    printf("\nEnter Process ID requesting resources: ");
    scanf("%d", &pid);

    if (pid < 0 || pid >= sys.num_processes || !sys.process_active[pid]) {
        printf("[Error] Invalid or inactive process ID.\n");
        return;
    }

    printf("Process %s current need: [", sys.process_names[pid]);
    for (int j = 0; j < sys.num_resources; j++) {
        printf("%d%s", sys.need[pid][j], j < sys.num_resources - 1 ? ", " : "");
    }
    printf("]\n");

    printf("Enter request amounts for each resource type (%d types):\n", sys.num_resources);
    for (int j = 0; j < sys.num_resources; j++) {
        printf("  Resource R%d request: ", j);
        scanf("%d", &request[j]);
    }

    request_resources(pid, request);
}

/*Interactive prompt for a process to release resources.*/
void interactive_release_resources(void) {
    int pid;
    int release[MAX_RESOURCES];

    printf("\nEnter Process ID releasing resources: ");
    scanf("%d", &pid);

    if (pid < 0 || pid >= sys.num_processes || !sys.process_active[pid]) {
        printf("[Error] Invalid or inactive process ID.\n");
        return;
    }

    printf("Process %s current allocation: [", sys.process_names[pid]);
    for (int j = 0; j < sys.num_resources; j++) {
        printf("%d%s", sys.allocation[pid][j], j < sys.num_resources - 1 ? ", " : "");
    }
    printf("]\n");

    printf("Enter release amounts for each resource type (%d types):\n", sys.num_resources);
    for (int j = 0; j < sys.num_resources; j++) {
        printf("  Resource R%d release: ", j);
        scanf("%d", &release[j]);
    }

    release_resources(pid, release);
}

/*Interactive prompt to set total resources (only valid when system is empty).*/
void interactive_set_resources(void) {
    int counts[MAX_RESOURCES];

    printf("\nEnter total instances for each resource type (%d types):\n", sys.num_resources);
    for (int j = 0; j < sys.num_resources; j++) {
        printf("  Resource R%d total instances: ", j);
        scanf("%d", &counts[j]);
        if (counts[j] < 0) counts[j] = 0;
    }

    set_total_resources(counts);
}

/* Run safety algorithm and display results interactively. */
void interactive_check_safety(void) {
    printf("\n[Running Safety Algorithm...]\n");
    SafetyResult result = run_safety_algorithm();
    display_safe_sequence(&result);

    if (result.is_safe) {
        log_safe_state(result.safe_sequence, result.sequence_length);
    } else {
        int dummy[MAX_RESOURCES] = {0};
        log_unsafe_state(-1, dummy);
    }
}

/*Display current system state matrices.*/
void interactive_display_state(void) {
    display_all_matrices();
}

/*Main interactive menu loop.*/
void run_interactive_menu(void) {
    int choice;

    do {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                interactive_display_state();
                break;
            case 2:
                display_process_status();
                break;
            case 3:
                display_resource_status();
                break;
            case 4:
                interactive_add_process();
                break;
            case 5: {
                int pid;
                printf("Enter Process ID to remove: ");
                scanf("%d", &pid);
                remove_process(pid);
                break;
            }
            case 6:
                interactive_request_resources();
                break;
            case 7:
                interactive_release_resources();
                break;
            case 8:
                interactive_check_safety();
                break;
            case 9: {
                SafetyResult result = run_safety_algorithm();
                display_safe_sequence(&result);
                break;
            }
            case 10:
                print_performance_report();
                break;
            case 11: {
                char fname[64];
                printf("Enter filename (default: performance_report.txt): ");
                scanf("%s", fname);
                save_performance_report(fname);
                break;
            }
            case 12:
                reset_system();
                printf("System reset. Please reinitialize.\n");
                break;
            case 0:
                printf("\nExiting Banker's Algorithm Simulator. Goodbye!\n");
                break;
            default:
                printf("\n[Error] Invalid choice. Please try again.\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar();  /* Consume newline */
            getchar();  /* Wait for Enter */
        }

    } while (choice != 0);
}

