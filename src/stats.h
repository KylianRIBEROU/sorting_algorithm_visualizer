#ifndef STATS_H
#define STATS_H

typedef struct {
    unsigned long memory_reads;
    unsigned long memory_writes;
    unsigned long comparisons;
    double execution_time_ms;
} Statistics;

// Initialize statistics to zero
void stats_init(Statistics* stats);

// Reset all counters to zero
void stats_reset(Statistics* stats);

// Increment counters
void stats_increment_read(Statistics* stats);
void stats_increment_write(Statistics* stats);
void stats_increment_comparison(Statistics* stats);

// Time measurement
void stats_start_timer(Statistics* stats);
void stats_stop_timer(Statistics* stats);

#endif