#include "garbage.h"
int main() {
    int choice = 0;
    G_p G = create_Garbage();
    hash_ptable H_T = create_hash_table();
    do {
        printf("\n=== 垃圾分类查询系统 ===\n");
        printf("1. 插入垃圾信息\n");
        printf("2. 删除垃圾信息\n");
        printf("3. (普通速度)查找垃圾信息\n");
        printf("4. 输入名字(快速)查找垃圾信息\n");
        printf("5. 查看哈西表中所有垃圾名字信息\n");
        printf("6. 修改垃圾信息\n");
        printf("7. 查看所有垃圾信息\n");
        printf("8. 清空所有垃圾信息\n");
        printf("9. 退出系统\n");
        printf("请输入选择 (1-9): ");
        if (scanf("%d", &choice) == 0) 
        {
    		while (getchar() != '\n');
            choice = 0;
        }
        else
            getchar();
        switch (choice) {
            case 1:
                insert_Garbage(G,H_T);
                break;
            case 2:
                dele_Garbage(G,H_T);
                break;
            case 3:
                search_Garbage(G);
                break;
            case 4:
                hash_search(H_T);
                break;
            case 5:
                traver_hash_table(H_T);
                break;
            case 6:
                modify_Garbage(G);
                break;
            case 7:
                traver_Garbage(G);
                break;
            case 8:
                clean_Garbage(G,H_T);
                break;
            case 9:
                printf("感谢使用垃圾分类查询系统！\n");
                break;
            default:
                printf("无效选择，请重新输入！\n");
        }
 //       sleep(2);
   //     system("clear");
    } while (choice != 9);

    break_Garbage(G,H_T);
    return 0;
}
