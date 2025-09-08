#ifndef GARBAGE_H
#define GARBAGE_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

#define SIZE 1024
#define G_SIZE_MAX 1000
typedef char data_c;
typedef struct Garbage
{
    data_c name[SIZE];
    data_c type[SIZE];
    data_c description[SIZE];
    struct Garbage *next;
}G_node,*G_p;

typedef struct hash_node
{
    char name[SIZE];
    G_p G_pnode;
    struct hash_node *next;
}hash_node,*hash_pnode;

typedef struct hash_table
{
    hash_pnode table[SIZE];
    int count;//实际哈希节点的个数
}hash_table,*hash_ptable;


G_p create_Garbage();
int insert_Garbage(G_p G,hash_ptable H_T);
int traver_Garbage(G_p G);
int dele_Garbage(G_p G,hash_ptable H_T);
int search_Garbage(G_p G);
int modify_Garbage(G_p G);
int clean_Garbage(G_p G,hash_ptable H_T);
int break_Garbage(G_p G,hash_ptable H_T);

hash_ptable create_hash_table();
hash_pnode create_hash_node(char *name,G_p G_pnode);
int insert_hash_table(hash_ptable H_T,char *name,G_p pnode);
int hash_search(hash_ptable H_T);
int dele_hash_node(hash_ptable H_T,char *name);
int traver_hash_table(hash_ptable H_T);
#endif
