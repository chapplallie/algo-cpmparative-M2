#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define EMAIL_MAX 100

typedef struct {
    char email[EMAIL_MAX];
    int  id;
} User;

