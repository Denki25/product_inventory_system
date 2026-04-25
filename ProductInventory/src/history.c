#include "../include/history.h"

#include "../include/utils.h"

#include <stdio.h>
#include <time.h>

void log_history(const char *actor, const char *action) {
    FILE *file = fopen(HISTORY_FILE, "a");
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    char timestamp[64];

    if (file == NULL || local_time == NULL) {
        return;
    }

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local_time);
    fprintf(file, "[%s] %s - %s\n", timestamp, actor, action);
    fclose(file);
}

void view_history(void) {
    FILE *file = fopen(HISTORY_FILE, "r");
    char line[256];
    int line_count = 0;

    print_banner("Inventory History");

    if (file == NULL) {
        print_message("ERROR", "Unable to open history file.", COLOR_RED);
        wait_for_enter();
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        fputs(line, stdout);
        line_count++;
    }

    if (line_count == 0) {
        print_message("INFO", "History is empty.", COLOR_YELLOW);
    }

    fclose(file);
    wait_for_enter();
}

void clear_history(void) {
    FILE *file = NULL;

    print_banner("Clear History");
    if (!prompt_yes_no("Are you sure you want to clear all history? (Y/N): ")) {
        print_message("INFO", "History was not cleared.", COLOR_YELLOW);
        wait_for_enter();
        return;
    }

    file = fopen(HISTORY_FILE, "w");
    if (file == NULL) {
        print_message("ERROR", "Unable to clear history file.", COLOR_RED);
        wait_for_enter();
        return;
    }

    fclose(file);
    print_message("SUCCESS", "History cleared successfully.", COLOR_GREEN);
    wait_for_enter();
}
