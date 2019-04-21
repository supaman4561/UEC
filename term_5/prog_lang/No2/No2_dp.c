#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
//https://www.ied.inf.uec.ac.jp/support/projects/ied-support/wiki/%E6%95%99%E6%9D%90
 
#define SUCCESS 1    /* 成功*/ 
#define FAILURE 0    /* 失敗*/
#define SIZE 100
 
/*---------------------------------------------------------------------------------------*/
 
//構造体宣言
typedef char* string_type;
typedef int int_type;
typedef struct node_tag {
    string_type name;       //名前
    int_type point;         //点数
    struct node_tag *next;   /* 後続ノードへのポインタ*/
} node_type;                     /* ノードの型*/
 
void print_nodes(node_type *p);


//線形リストの初期化
void initialize(node_type **pp)
{
    *pp = NULL;     //先頭ノードなし
}
 
//新しいノードの生成と値の設定
node_type *new_node(string_type na, int_type po, node_type *p)
{
    node_type *temp;
 
    temp = (node_type *)malloc(sizeof(node_type));  //メモリ割り当て
    temp->name = (string_type)malloc(sizeof(char) * SIZE);

    if(temp == NULL){ return NULL; }            //メモリ割り当て失敗
    else{                       //ノードの各メンバの値の設定
        strcpy(temp->name, na);
        temp->point = po;
        temp->next = p;
        return temp;
    }
}
 
//線形リストに名前順で挿入
int insert(string_type na, int_type po, node_type **pp) //node_type **ppはヘッダのポインタ
{
    node_type *temp;
    temp = new_node(na, po, NULL);    /* 関数new_nodeの呼出し*/

    //挿入すべき場所を探す
    if(temp == NULL){ return FAILURE; }

    if (*pp == NULL)  {
        *pp = temp;
    } else {
        while((*pp) != NULL && (strcmp(temp->name, (*pp)->name)) > 0 ) {
            pp = &((*pp)->next);
        }
        temp->next = (*pp);
        *pp = temp;
    }

    return SUCCESS;
}


/*
//線形リストの末尾へのノード挿入
int insert_rear(string_type na, int_type po, node_type **pp) //node_type **ppはヘッダのポインタ
{
    node_type *temp;
    temp = new_node(na, po, NULL);    // 関数new_nodeの呼出し
    if(temp == NULL){ return FAILURE; }
    while(*pp != NULL) {    // 末尾のノードまで進める
       pp = &((*pp)->next);
    }
    *pp = temp;
    return SUCCESS;
}
*/
 
void print_nodes(node_type *p)
{
    while(p != NULL)
    {
        printf("Name:%s,Point:%d\n", p->name, p->point); //データの表示
        p = p->next;
    }
}
 
 
/*---------------------------------------------------------------------------------------*/
 
int main(int argc, char **argv)
{
    FILE *fp;
    char na[256];
    int po;
     
    node_type *head;
    initialize(&head);
 
    if((fp = fopen(argv[1], "r")) == NULL){
    perror(argv[1]);
        exit(1);
    }
 
    while(fscanf(fp, "%[^,],%d\n", na, &po) != EOF)  //End Of File
    {
        insert(na, po, &head);
    }
    printf("\n");
 
    print_nodes(head);
 
    fclose(fp);
     
    return 0;
}