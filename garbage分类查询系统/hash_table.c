#include "garbage.h"

hash_ptable create_hash_table()
{
    hash_ptable H_T = (hash_ptable)malloc(sizeof(hash_table));
    if (NULL == H_T)
    {
        printf("hash_table create fail\n");
        return NULL;
    }
    for (int i = 0;i < SIZE;i++)
        H_T -> table[i] = NULL;
    
    H_T -> count = 0;
    return H_T;
}

hash_pnode create_hash_node(data_c *name,G_p G_pnode)
{
    hash_pnode H_N = (hash_pnode)malloc(sizeof(hash_node));
    if (NULL == H_N)
    {
        printf("hash_node create fail\n");
        return NULL;
    }
    strcpy(H_N -> name,name);
    H_N -> G_pnode = G_pnode;
    H_N -> next = NULL;
    return H_N;
}

int empty_hash_table(hash_ptable H_T)
{
    if (NULL == H_T)
    {
        printf("H_T is NULL\n");
        return -1;
    }
    if (0 == H_T -> count)
        return 0;
    else
        return 1;
}

int hash_function_DJB2(data_c *name)
{
    unsigned int hash_val = 5381;
    while (*name)
    {
        hash_val = (hash_val << 5) + hash_val + *name;
        name++;
    }
    return hash_val % SIZE;
}

int insert_hash_table(hash_ptable H_T,data_c *name,G_p pnode)
{
    if (NULL == H_T)
    {
        printf("H_T is NULL\n");
        return -1;
    }
    
    int index = hash_function_DJB2(name);
    printf("index = %d\n",index);
    
    if (H_T -> table[index] != NULL)
    {
        hash_pnode H_N = H_T -> table[index];
        hash_pnode temp = H_N;
        while (temp)
        {
            if (strcmp(temp -> name,name) == 0)
            {
                printf("已经有这个垃圾信息了\n");
                return -1;
            }
            temp = temp -> next;
        }
    }

    hash_pnode H_N = create_hash_node(name,pnode);
    H_N -> next = H_T -> table[index];
    H_T -> table[index] = H_N;
    H_T -> count++;
    printf("插入哈希表成功\n");
    return 0;
}

int hash_search(hash_ptable H_T)
{
    if (NULL == H_T)
    {
        printf("H_T is NULL\n");
    }
    if (0 == empty_hash_table(H_T))
    {
        printf("hash_table is empty\n");
        return -1;
    }
    
    data_c name[SIZE];
    printf("输入你要查找的垃圾名字\n");
    fgets(name,SIZE,stdin);
    name[strcspn(name,"\n")] = '\0';
    
    int index = hash_function_DJB2(name);
    hash_pnode H_N = H_T -> table[index];

    int flag = 0;
    while(H_N)
    {
        if (strcmp(H_N -> name,name) == 0)
        {
            printf("名称: %s, 类别: %s, 描述: %s\n",
               H_N -> G_pnode -> name, H_N -> G_pnode -> type, H_N -> G_pnode -> description);
            flag = 1;
        }
        H_N = H_N -> next;
    }
    if (flag == 0)
        printf("没有找到垃圾信息\n");
    return 0;
}

int dele_hash_node(hash_ptable H_T,data_c *name)
{
    if (NULL == H_T)
    {
        printf("H_T is NULL\n");
        return -1;
    }
    if (0 == empty_hash_table(H_T))
    {
        printf("hash_table is empty\n");
        return -1;
    }

    int index = hash_function_DJB2(name);
    hash_pnode H_N = H_T -> table[index];
    
    int flag = 0;
    while (H_N)
    {
        if (strcmp(H_N -> name,name) == 0)
        {
            hash_pnode temp = H_N;
            H_N = H_N -> next;
            free(temp);
            H_T -> table[index] = H_N;
            H_T -> count--;
            flag = 1;
        }
        else
            H_N = H_N -> next;
    }
    if (1 == flag)
    {
        printf("哈希节点删除成功\n");
        printf("哈希表中剩余节点数量: %d\n", H_T->count);
        return 0;
    }
    else 
    {
        printf("没有找到信息哈希节点\n");
        return -1;
    }
}

int traver_hash_table(hash_ptable H_T)
{
    if (NULL == H_T)
    {
        printf("H_T is NULL\n");
        return -1;
    }
    if (H_T -> count == 0)
    {
        printf("hash_table is empty\n");
        return -1;
    }
    
    printf("哈西表中记录的垃圾名称: \n");
    for (int i = 0;i < SIZE;i++)
    {
        hash_pnode H_N = H_T -> table[i];
        while (H_N)
        {
            printf("%s ",H_N -> name);
            H_N = H_N -> next;
        }
    }
    return 0;
}

