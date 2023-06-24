#ifndef KERNEL_LOGS_H
#define KERNEL_LOGS_H

#define INFO 1
#define DEBUG 2
#define ERROR 3
#define CRITICAL 4

#define FBUFF 1
#define SERIAL 2
#define BOTH 3

void kpanic();
void log(char *msg, int level, int dev);
void log_info(char *msg, int dev);
void log_debug(char *msg, int dev);
void log_error(char *msg, int dev);
void log_critical(char *msg, int dev);

#endif