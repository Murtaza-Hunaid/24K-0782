#ifndef BANKER_H
#define BANKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_PROCESSES 20
#define MAX_RESOURCES 10
#define LOG_FILE "banker_log.txt"
#define MAX_LINE_LENGTH 256

typedef struct {
    int num_processes;
    int num_resources;

    int total_resources[MAX_RESOURCES];
    int available[MAX_RESOURCES];

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int maximum[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];

    bool process_active[MAX_PROCESSES];
    char process_names[MAX_PROCESSES][32];
} SystemState;

typedef struct {
    int safe_sequence[MAX_PROCESSES];
    bool is_safe;
    int sequence_length;
} SafetyResult;

typedef struct {
    int requests_granted;
    int requests_denied;
    int total_safety_checks;
    double total_safety_time_ms;
    double max_safety_time_ms;
    double min_safety_time_ms;
} PerformanceMetrics;

/* Global State */
extern SystemState sys;
extern PerformanceMetrics perf;
extern FILE *log_fp;

void init_system(int num_p, int num_r);
void add_process(int pid, int max_demand[], const char *name);
void remove_process(int pid);
void calculate_need_matrix(void);
void set_total_resources(int totals[]);
void reset_system(void);

/* safety_algorithm.c */
SafetyResult run_safety_algorithm(void);
bool check_safety_with_temp(int temp_available[], int temp_allocation[][MAX_RESOURCES], int temp_need[][MAX_RESOURCES], bool temp_active[], int num_p, int num_r);

/* request_handler.c */
bool request_resources(int pid, int request[]);
bool release_resources(int pid, int release[]);
bool validate_request(int pid, int request[]);

/* rollback.c */
void save_state_snapshot(int temp_avail[], int temp_alloc[][MAX_RESOURCES], int temp_need[][MAX_RESOURCES]);
void restore_state_from_snapshot(int temp_avail[], int temp_alloc[][MAX_RESOURCES], int temp_need[][MAX_RESOURCES]);
void perform_hypothetical_allocation(int pid, int request[], int temp_avail[], int temp_alloc[][MAX_RESOURCES], int temp_need[][MAX_RESOURCES]);

/* performance.c */
void init_performance_metrics(void);
void record_request_granted(void);
void record_request_denied(void);
void record_safety_check(double time_ms);
void print_performance_report(void);
void save_performance_report(const char *filename);

/* resource_manager.c */
void initialize_resources(int counts[], int num_r);
void display_resource_status(void);
bool check_resource_availability(int request[]);
void update_available_resources(int delta[], bool add);
int get_resource_instance_count(int rtype);

/* visualization.c */
void display_all_matrices(void);
void display_matrix(const char *title, int matrix[][MAX_RESOURCES], int rows, int cols);
void display_vector(const char *title, int vec[], int len);
void display_safe_sequence(SafetyResult *result);
void display_process_status(void);
void print_separator(void);
void print_header(const char *title);

/* interactive_input.c */
void run_interactive_menu(void);
void interactive_add_process(void);
void interactive_request_resources(void);
void interactive_release_resources(void);
void interactive_set_resources(void);
void interactive_check_safety(void);
void interactive_display_state(void);
void print_menu(void);

/* logger.c */
void init_logger(void);
void close_logger(void);
void log_safe_state(int safe_seq[], int len);
void log_unsafe_state(int pid, int request[]);
void log_request_granted(int pid, int request[]);
void log_request_denied(int pid, int request[], const char *reason);
void log_state_transition(const char *description);
void log_process_added(int pid, const char *name, int max_demand[]);
void log_process_removed(int pid);
void log_resource_release(int pid, int release[]);
void flush_log(void);

/* main.c */
void cleanup_system(void);

#endif /* BANKER_H */
