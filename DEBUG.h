#ifndef debug_h
#define debug_h

#if defined DEBUG
#define debug(FORMAT, ...) \
            do { \
                fprintf(stderr, "\n!!! DEBUG %s - %d - %s !!! " FORMAT, __FILE_NAME__, __LINE__, __func__, ##__VA_ARGS__); \
                fprintf(stderr, "\n"); \
            } while (0)
#else
#define debug(FORMAT, ...) do {} while (0)
#endif

#endif