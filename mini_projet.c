#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define EMAIL_MAX 100
#define TABLE_SIZE 100003 

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
  
typedef struct Node {
    char email[EMAIL_MAX];
    int  id;
    struct Node *next;
} Node;
 
static Node *hash_table[TABLE_SIZE];   
 
/* Fonction de hachage djb2 (Dan Bernstein) */
static unsigned long hash_function(const char *str)
{
    unsigned long h = 5381;
    int c;
    while ((c = (unsigned char)*str++) != 0)
        h = h * 33 + (unsigned long)c;
    return h % TABLE_SIZE;
}
 
void hash_insert(const char *email, int id)
{
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr, "Erreur : memoire insuffisante (malloc)\n");
        exit(EXIT_FAILURE);
    }
    copy_email(n->email, email);
    n->id = id;
    unsigned long idx = hash_function(email);
    n->next = hash_table[idx];
    hash_table[idx] = n;
}
 
bool hash_search(const char *email)
{
    Node *cur = hash_table[hash_function(email)];
    while (cur != NULL) {                        /* case vide : NULL */
        if (strcmp(cur->email, email) == 0)
            return true;
        cur = cur->next;
    }
    return false;
}
 
void hash_free(void)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *cur = hash_table[i];
        while (cur != NULL) {
            Node *next = cur->next;
            free(cur);
            cur = next;
        }
        hash_table[i] = NULL;
    }
}
