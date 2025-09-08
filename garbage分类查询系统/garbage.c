#include "garbage.h"

G_p create_Garbage()
{
    G_p G = (G_p)malloc(sizeof(G_node));
    if (NULL == G)
    {
        printf("Garbage create fail\n");
        return NULL;
    }
    G -> next = NULL;
    return G;
}

int empty_Garbage(G_p G)
{
    if (NULL == G)
    {
        printf("Garbage create fail\n");
        return -1;
    }
    if (G -> next == NULL)
        return 0;
}

int len_Garbage(G_p G)
{
    if (NULL == G)
    {
        printf("G is NULL\n");
        return -1;
    }
    int len = 0;
    while (G -> next)
    {
        G = G -> next;
        len++;
    }
    return len;
}

int insert_Garbage(G_p G,hash_ptable H_T)
{
    if (NULL == G)
    {
        printf("Garbage create fail\n");
        return -1;
    }
    data_c name[SIZE],type[SIZE],description[SIZE];
    
    printf("请输入垃圾名字:\n");
    fgets(name,SIZE,stdin);
    name[strcspn(name,"\n")] = '\0';
    
    G_p temp = G;
    while (temp -> next)
    {
        temp = temp -> next;
        if (strcmp(temp -> name,name) == 0)
        {
            printf("已经有这个垃圾的信息了");
            return -1;
        }
    }
    printf("请输入垃圾类别:\n");
    fgets(type,SIZE,stdin);
    type[strcspn(type,"\n")] = '\0';
    
    printf("请输入垃圾描述:\n");
    fgets(description,SIZE,stdin);
    description[strcspn(description,"\n")] = '\0';
    
    G_p new_Garbage = create_Garbage();
    strcpy(new_Garbage -> name,name);
    strcpy(new_Garbage -> type,type);
    strcpy(new_Garbage -> description,description);

    new_Garbage -> next = G -> next;
    G -> next = new_Garbage;
    printf("垃圾信息插入成功！\n");

    insert_hash_table(H_T,name,new_Garbage);
    return 0;
}

int traver_Garbage(G_p G)
{
    if (NULL == G)
    {
        printf("Garbage create fail\n");
        return -1;
    }
    if (0 == empty_Garbage(G))
    {
        printf("Garbage is empty\n");
        return -1;
    }

    G_p p = G -> next;
    G_p display[G_SIZE_MAX];
    int len = len_Garbage(G);
    if (len > G_SIZE_MAX)
    {
        printf("G nums greater than G_SIZE_MAX");
        return -1;
    }
    for (int i = 0; i < len;i++)
    {
        display[i] = p;
        p = p -> next;
    }
    
    G_p temp;
    for (int i = 0; i < len - 1;i++)
    {
        for (int j = 0;j < len - 1 - i;j++)
        {
            if (strcmp(display[i + 1] -> name, display[i] -> name) < 0)
            {
                temp = display[i];
                display[i] = display[i + 1];
                display[i + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < len;i++)
        printf("名称: %s, 类别: %s, 描述: %s\n",
               display[i]->name, display[i]->type, display[i]->description);  

    return 0;
}

int dele_Garbage(G_p G,hash_ptable H_T)
{
    if (0 == empty_Garbage(G))
    {
        printf("G is empty\n");
        return -1;
    }
    
    printf("输入你要删除的垃圾名字\n");
    data_c name[SIZE];
    fgets(name,SIZE,stdin);
    name[strcspn(name,"\n")] = '\0';
    
    dele_hash_node(H_T,name);
    
    int flag = 0;
    while (G -> next)
    {
        if (strcmp(G -> next -> name,name) == 0)
        {
            G_p temp = G -> next;
            G -> next = temp -> next;
            free(temp);
            temp = NULL;
            flag = 1;
        }
        G = G -> next;
        if (G == NULL)
            break;
    }
    if (0 == flag)
        printf("没有找到该垃圾信息\n");
    else
        printf("垃圾信息删除成功！\n");
    return 0;
}

int search_Garbage(G_p G)
{
    if (0 == empty_Garbage(G))
    {
        printf("G is empty\n");
        return -1;
    }
    
    printf("输入你要查找的垃圾名字、描述或种类\n");
    data_c key[SIZE];
    fgets(key,SIZE,stdin);
    key[strcspn(key,"\n")] = '\0';
    
    int flag = 0;
    while (G -> next)
    {
        if( strcmp(G -> next ->name,key) == 0 || 
            strcmp(G -> next ->description,key) == 0 || 
            strcmp(G -> next ->type,key) == 0)
        {
            printf("名称: %s, 类别: %s, 描述: %s\n", 
                   G -> next -> name, G -> next -> type,
                   G -> next -> description);
            flag = 1;
        }
        G = G -> next;
    }
    if (flag == 0)
        printf("没有找到\n");
    return 0;
}

int modify_Garbage(G_p G)
{
    if (NULL == G)
    {
        printf("G is NULL\n");
        return -1;
    }
    if (0 == empty_Garbage(G))
    {
        printf("Garbage is empty\n");
        return -1;
    }
    
    data_c name[SIZE];
    printf("请输入要修改的垃圾名称:\n");
    fgets(name,SIZE,stdin);
    name[strcspn(name,"\n")] = '\0';
    
    int flag = 0;
    while (G -> next)
    {
        G = G -> next;
        if (strcmp(G -> name,name) == 0)
        {
           printf("请输入新的垃圾类别:\n");
           data_c type[SIZE];
           fgets(type,SIZE,stdin);
           type[strcspn(type,"\n")] = '\0';
           
           if (strlen(type) > 0)
                strcpy(G -> type,type);
            
           printf("请输入新的垃圾描述:\n");
           data_c description[SIZE];
           fgets(description,SIZE,stdin);
           description[strcspn(description,"\n")] = '\0';
           
           if (strlen(description) > 0)
                strcpy(G -> description,description);
           flag = 1;
        }
    }
    if (0 == flag)
        printf("没有找到垃圾信息\n");
    return 0;
}

int clean_Garbage(G_p G,hash_ptable H_T)
{
    if (NULL == G)
    {
        printf("G is NULL\n");
        return -1;
    }
    if (0 == empty_Garbage(G))
    {
        printf("garbage is empty\n");
        return -1;
    }
    while (G -> next)
    {
        dele_hash_node(H_T,G -> next -> name);
        
        G_p temp = G -> next;
        G -> next = temp -> next;
        free(temp);
    }
    if (0 == H_T -> count)
        printf("哈希表清空成功\n");
    printf("垃圾链表清空成功\n");
    return 0;
}

int break_Garbage(G_p G,hash_ptable H_T)
{
    if (NULL == G)
    {
        printf("G is NULL\n");
        return -1;
    }
    if (0 == empty_Garbage(G) && 0 == H_T -> count)
    {
        free(G);
        printf("垃圾链表销毁成功\n");
        free(H_T);
        printf("哈希表销毁成功\n");
        return 0;
    }
    else
    {
        if (0 == clean_Garbage(G,H_T) && 0 == H_T -> count)
        {
            free(G);
            printf("垃圾链表销毁成功\n");
            free(H_T);
            printf("哈希表销毁成功\n");
            return 0;
        }
    }
}
