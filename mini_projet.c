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

static void copy_email(char *dest, const char *src)
{
    strncpy(dest, src, EMAIL_MAX - 1);
    dest[EMAIL_MAX - 1] = '\0';
} 


static User *grow_array(User *tab, int *capacity)
{
    int new_cap = (*capacity == 0) ? 16 : *capacity * 2;
    User *tmp = realloc(tab, (size_t)new_cap * sizeof(User));
    if (tmp == NULL) {
        fprintf(stderr, "Erreur : memoire insuffisante (realloc)\n");
        free(tab);
        exit(EXIT_FAILURE);
    }
    *capacity = new_cap;
    return tmp;
}



static User *seq_tab = NULL;
static int   seq_size = 0;
static int   seq_capacity = 0;
 
void seq_insert(const char *email, int id)
{
    if (seq_size == seq_capacity)
        seq_tab = grow_array(seq_tab, &seq_capacity);
    copy_email(seq_tab[seq_size].email, email);
    seq_tab[seq_size].id = id;
    seq_size++;
}
 
bool seq_search(const char *email)
{
    for (int i = 0; i < seq_size; i++)          /* annuaire vide : 0 tour */
        if (strcmp(seq_tab[i].email, email) == 0)
            return true;
    return false;
}
 
void seq_free(void)
{
    free(seq_tab);
    seq_tab = NULL;
    seq_size = seq_capacity = 0;
}