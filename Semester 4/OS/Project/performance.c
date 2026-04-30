/*Performance analysis and metrics collection*/

#include "banker.h"

PerformanceMetrics perf;

/*Initialize all performance metrics to zero. */
void init_performance_metrics(void) {
    perf.requests_granted = 0;
    perf.requests_denied = 0;
    perf.total_safety_checks = 0;
    perf.total_safety_time_ms = 0.0;
    perf.max_safety_time_ms = 0.0;
    perf.min_safety_time_ms = 999999.0;
}

/*Record a successfully granted request.*/
void record_request_granted(void) {
    perf.requests_granted++;
}

/*Record a denied request. */
void record_request_denied(void) {
    perf.requests_denied++;
}

/* Record timing statistics for a safety check execution.*/
void record_safety_check(double time_ms) {
    perf.total_safety_checks++;
    perf.total_safety_time_ms += time_ms;

    if (time_ms > perf.max_safety_time_ms) {
        perf.max_safety_time_ms = time_ms;
    }
    if (time_ms < perf.min_safety_time_ms) {
        perf.min_safety_time_ms = time_ms;
    }
}

void print_performance_report(void) {
    print_separator();
    print_header("PERFORMANCE ANALYSIS REPORT");
    print_separator();

    int total_requests = perf.requests_granted + perf.requests_denied;
    double grant_rate = (total_requests > 0) ? 
                        (100.0 * perf.requests_granted / total_requests) : 0.0;
    double avg_time = (perf.total_safety_checks > 0) ? 
                      (perf.total_safety_time_ms / perf.total_safety_checks) : 0.0;

    printf("Total Requests Processed:     %d\n", total_requests);
    printf("Requests Granted:             %d\n", perf.requests_granted);
    printf("Requests Denied:              %d\n", perf.requests_denied);
    printf("Grant Rate:                   %.2f%%\n", grant_rate);
    printf("Denial Rate:                  %.2f%%\n", 100.0 - grant_rate);
    printf("\n");
    printf("Total Safety Checks:          %d\n", perf.total_safety_checks);
    printf("Average Safety Check Time:    %.3f ms\n", avg_time);
    printf("Minimum Safety Check Time:    %.3f ms\n", (perf.min_safety_time_ms == 999999.0) ? 0.0 : perf.min_safety_time_ms);
    printf("Maximum Safety Check Time:    %.3f ms\n", perf.max_safety_time_ms);
    printf("Total Safety Check Time:      %.3f ms\n", perf.total_safety_time_ms);
    print_separator();
}

/*Save performance report to a file. */
void save_performance_report(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("[Error] Could not open %s for writing.\n", filename);
        return;
    }

    int total_requests = perf.requests_granted + perf.requests_denied;
    double grant_rate = (total_requests > 0) ? (100.0 * perf.requests_granted / total_requests) : 0.0;
    double avg_time = (perf.total_safety_checks > 0) ? (perf.total_safety_time_ms / perf.total_safety_checks) : 0.0;

    fprintf(fp, "========================================\n");
    fprintf(fp, "  PERFORMANCE ANALYSIS REPORT\n");
    fprintf(fp, "========================================\n");
    fprintf(fp, "Total Requests Processed:     %d\n", total_requests);
    fprintf(fp, "Requests Granted:             %d\n", perf.requests_granted);
    fprintf(fp, "Requests Denied:              %d\n", perf.requests_denied);
    fprintf(fp, "Grant Rate:                   %.2f%%\n", grant_rate);
    fprintf(fp, "Denial Rate:                  %.2f%%\n", 100.0 - grant_rate);
    fprintf(fp, "\n");
    fprintf(fp, "Total Safety Checks:          %d\n", perf.total_safety_checks);
    fprintf(fp, "Average Safety Check Time:    %.3f ms\n", avg_time);
    fprintf(fp, "Minimum Safety Check Time:    %.3f ms\n", 
            (perf.min_safety_time_ms == 999999.0) ? 0.0 : perf.min_safety_time_ms);
    fprintf(fp, "Maximum Safety Check Time:    %.3f ms\n", perf.max_safety_time_ms);
    fprintf(fp, "Total Safety Check Time:      %.3f ms\n", perf.total_safety_time_ms);
    fprintf(fp, "========================================\n");

    fclose(fp);
    printf("[Performance] Report saved to %s\n", filename);
}

