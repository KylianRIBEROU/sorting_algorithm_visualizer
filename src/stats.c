#include "stats.h"
#include <string.h>
#include <time.h>

void stats_init(Statistics* stats) {
    memset(stats, 0, sizeof(Statistics));
}

void stats_reset(Statistics* stats) {
    stats->memory_reads = 0;
    stats->memory_writes = 0;
    stats->comparisons = 0;
    stats->start_time = 0;
    stats->execution_time_ms = 0.0;
}

void stats_increment_read(Statistics* stats) {
    stats->memory_reads++;
}

void stats_increment_write(Statistics* stats) {
    stats->memory_writes++;
}

void stats_increment_comparison(Statistics* stats) {
    stats->comparisons++;
}


void stats_start_timer(Statistics* stats) {
    stats->start_time = clock();
    stats->execution_time_ms = 0.0;
}

void stats_update_timer(Statistics* stats) {
    clock_t now = clock();
    stats->execution_time_ms =
        ((double)(now - stats->start_time) / CLOCKS_PER_SEC) * 1000.0;
}

void stats_stop_timer(Statistics* stats) {
    stats_update_timer(stats);
}