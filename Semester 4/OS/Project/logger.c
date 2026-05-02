// Persistent logging of all state transitions

#include "banker.h"

FILE *log_fp = NULL;

/*
 * Initialize the logger by opening the log file.
 * Creates and truncates the file and writes a header.
 */
void init_logger(void) {
    log_fp = fopen(LOG_FILE, "w");
    if (!log_fp) {
        printf("[Warning] Could not open log file %s. Logging disabled.\n", LOG_FILE);
        return;
    }

    time_t now = time(NULL);
    fprintf(log_fp, "========================================\n");
    fprintf(log_fp, "  BANKER'S ALGORITHM SIMULATOR LOG\n");
    fprintf(log_fp, "  Started: %s", ctime(&now));
    fprintf(log_fp, "========================================\n\n");
    fflush(log_fp);

    printf("[Logger] Logging initialized to %s\n", LOG_FILE);
}

void close_logger(void) {
    if (log_fp) {
        time_t now = time(NULL);
        fprintf(log_fp, "\n========================================\n");
        fprintf(log_fp, "  Session ended: %s", ctime(&now));
        fprintf(log_fp, "========================================\n");
        fclose(log_fp);
        log_fp = NULL;
        printf("[Logger] Log file closed.\n");
    }
}

static void get_timestamp(char *buffer, size_t len) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, len, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Log a safe state with the safe sequence.

void log_safe_state(int safe_seq[], int len) {
    if (!log_fp) return;

    char ts[64];
    get_timestamp(ts, sizeof(ts));

    fprintf(log_fp, "[%s] SAFE STATE DETECTED\n", ts);
    fprintf(log_fp, "  Safe Sequence: <");
    for (int i = 0; i < len; i++) {
        fprintf(log_fp, "%s%s", sys.process_names[safe_seq[i]], 
                i < len - 1 ? ", " : "");
    }
    fprintf(log_fp, ">\n\n");
    fflush(log_fp);
}

//Log an unsafe state detection 
void log_unsafe_state(int pid, int request[] __attribute__((unused))) {
    if (!log_fp) return;

    char ts[64];
    get_timestamp(ts, sizeof(ts));

    fprintf(log_fp, "[%s] UNSAFE STATE DETECTED", ts);
    if (pid >= 0) {
        fprintf(log_fp, " (Process %s request denied)", sys.process_names[pid]);
    }
    fprintf(log_fp, "\n\n");
    fflush(log_fp);
}

// Log a granted resource request
void log_request_granted(int pid, int request[]) {
    if (!log_fp) return;

    char ts[64];
    get_timestamp(ts, sizeof(ts));

    fprintf(log_fp, "[%s] REQUEST GRANTED - Process %s\n", ts, sys.process_names[pid]);
    fprintf(log_fp, "  Resources: [");
    for (int j = 0; j < sys.num_resources; j++) {
        fprintf(log_fp, "%d%s", request[j], j < sys.num_resources - 1 ? ", " : "");
    }
    fprintf(log_fp, "]\n\n");
    fflush(log_fp);
}

// Log a denied resource request with reason
void log_request_denied(int pid, int request[], const char *reason) {
    if (!log_fp) return;

    char ts[64];
    get_timestamp(ts, sizeof(ts));

    fprintf(log_fp, "[%s] REQUEST DENIED - Process %s\n", ts, sys.process_names[pid]);
    fprintf(log_fp, "  Resources: [");
    for (int j = 0; j < sys.num_resources; j++) {
        fprintf(log_fp, "%d%s", request[j], j < sys.num_resources - 1 ? ", " : "");
    }
    fprintf(log_fp, "]\n");
    fprintf(log_fp, "  Reason: %s\n\n", reason);
    fflush(log_fp);
}

// Log a generic state transition
void log_state_transition(const char *description) {
    if (!log_fp) return;

    char ts[64];
    get_timestamp(ts, sizeof(ts));

    fprintf(log_fp, "[%s] STATE TRANSITION: %s\n", ts, description);
    fflush(log_fp);
}

// Log when a new process is added
void log_process_added(int pid, const char *name, int max_demand[]) {
    if (!log_fp) return;

    char ts[64];
    get_timestamp(ts, sizeof(ts));

    fprintf(log_fp, "[%s] PROCESS ADDED - %s (PID %d)\n", ts, name, pid);
    fprintf(log_fp, "  Max Demand: [");
    for (int j = 0; j < sys.num_resources; j++) {
        fprintf(log_fp, "%d%s", max_demand[j], j < sys.num_resources - 1 ? ", " : "");
    }
    fprintf(log_fp, "]\n\n");
    fflush(log_fp);
}

// Log when a process is removed 
void log_process_removed(int pid) {
    if (!log_fp) return;

    char ts[64];
    get_timestamp(ts, sizeof(ts));

    fprintf(log_fp, "[%s] PROCESS REMOVED - %s (PID %d)\n", ts, sys.process_names[pid], pid);
    fprintf(log_fp, "  All resources released back to available pool.\n\n");
    fflush(log_fp);
}

// Log resource release event
void log_resource_release(int pid, int release[]) {
    if (!log_fp) return;

    char ts[64];
    get_timestamp(ts, sizeof(ts));

    fprintf(log_fp, "[%s] RESOURCES RELEASED - Process %s\n", ts, sys.process_names[pid]);
    fprintf(log_fp, "  Released: [");
    for (int j = 0; j < sys.num_resources; j++) {
        fprintf(log_fp, "%d%s", release[j], j < sys.num_resources - 1 ? ", " : "");
    }
    fprintf(log_fp, "]\n\n");
    fflush(log_fp);
}

// Flush log buffer to disk
void flush_log(void) {
    if (log_fp) {
        fflush(log_fp);
    }
}

