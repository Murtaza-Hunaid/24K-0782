/*Terminal-based graphical visualization of system state*/

#include "banker.h"

void print_separator(void) {
    printf("+");
    for (int i = 0; i < 70; i++) printf("-");
    printf("+\n");
}

void print_header(const char *title) {
    int len = strlen(title);
    int padding = (70 - len) / 2;
    printf("|");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", title);
    for (int i = 0; i < (70 - padding - len); i++) printf(" ");
    printf("|\n");
}

void display_matrix(const char *title, int matrix[][MAX_RESOURCES], int rows, int cols) {
    printf("\n%s\n", title);

    printf("%-12s", "Process");
    for (int j = 0; j < cols; j++) {
        printf("R%-7d", j);
    }
    printf("\n");

    printf("------------");
    for (int j = 0; j < cols; j++) printf("--------");
    printf("\n");

    for (int i = 0; i < rows; i++) {
        if (!sys.process_active[i]) continue;
        printf("%-12s", sys.process_names[i]);
        for (int j = 0; j < cols; j++) {
            printf("%-8d", matrix[i][j]);
        }
        printf("\n");
    }
}

void display_vector(const char *title, int vec[], int len) {
    printf("\n%s\n", title);
    for (int j = 0; j < len; j++) {
        printf("R%-3d: %-6d  ", j, vec[j]);
        if ((j + 1) % 4 == 0) printf("\n");
    }
    if (len % 4 != 0) printf("\n");
}

void display_all_matrices(void) {
    print_separator();
    print_header("SYSTEM STATE MATRICES");
    print_separator();

    display_matrix("ALLOCATION MATRIX", sys.allocation, sys.num_processes, sys.num_resources);
    display_matrix("MAXIMUM MATRIX", sys.maximum, sys.num_processes, sys.num_resources);
    display_matrix("NEED MATRIX", sys.need, sys.num_processes, sys.num_resources);

    display_vector("AVAILABLE VECTOR", sys.available, sys.num_resources);
    display_vector("TOTAL RESOURCES", sys.total_resources, sys.num_resources);

    print_separator();
}

void display_safe_sequence(SafetyResult *result) {
    if (!result->is_safe) {
        printf("\n[Status] System is in UNSAFE STATE - No safe sequence exists.\n");
        return;
    }

    print_separator();
    print_header("SAFE EXECUTION SEQUENCE");
    print_separator();

    printf("\n   ");
    for (int i = 0; i < result->sequence_length; i++) {
        printf("+----------+  ");
    }
    printf("\n   ");

    for (int i = 0; i < result->sequence_length; i++) {
        int pid = result->safe_sequence[i];
        printf("| %-8s |  ", sys.process_names[pid]);
    }
    printf("\n   ");

    for (int i = 0; i < result->sequence_length; i++) {
        printf("+----------+  ");
    }
    printf("\n");

    printf("\nOrder: ");
    for (int i = 0; i < result->sequence_length; i++) {
        printf("%s", sys.process_names[result->safe_sequence[i]]);
        if (i < result->sequence_length - 1) printf(" -> ");
    }
    printf("\n");
    print_separator();
}

void display_process_status(void) {
    print_separator();
    print_header("PROCESS STATUS");
    print_separator();

    printf("%-10s %-10s %-12s ", "PID", "Name", "Status");
    for (int j = 0; j < sys.num_resources; j++) {
        printf("R%-5d", j);
    }
    printf("\n");

    print_separator();

    for (int i = 0; i < sys.num_processes; i++) {
        printf("%-10d %-10s %-12s ", i, sys.process_names[i],
               sys.process_active[i] ? "ACTIVE" : "INACTIVE");
        for (int j = 0; j < sys.num_resources; j++) {
            printf("%-6d", sys.allocation[i][j]);
        }
        printf("\n");
    }
    print_separator();
}

