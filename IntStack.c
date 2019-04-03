#include<stdio.h>
#include<stdlib.h>//malloc用
#define DUMMY -1//ダミーデータ
#define NODATA 0//データ無し
#define EXISTDATA 1//データあり

/*
int型データを保持するセル
スタックで用いる
自己参照構造体
 */
struct intCell{
  int data;             //データ部
  struct intCell * next;//ポインタ部
};

typedef struct intCell IntCell ;
typedef IntCell* IntStack; //スタック型
typedef IntCell* Cell_P; //セル型

IntStack makeStack();//スタックの作成
void push(IntStack stack,int data);//データ挿入
int pop(IntStack stack);//データ取り出し
int isEmpty(IntStack stack);//空のテスト
void printStack(IntStack stack);//リスト表示
void fscanToStack(FILE*fp,IntStack stack);//ファイルからのデータ入力
void reverse_fprint(FILE*fp,IntStack stack);//ファイルへ逆順に出力
Cell_P makeCell(int n);//セル作成

int main(){
  //スタックの動作
  IntStack stack;
  FILE *fp_in,*fp_out;

  stack=makeStack();//スタック生成
  fp_in=fopen("IntData","r");
  fscanToStack(fp_in,stack);
  fclose(fp_in);

  printf("スタックを表示します。\n");
  printStack(stack);

  printf("ファイルへ逆順に出力します。\n");
  fp_out=fopen("IntReverse","w");
  reverse_fprint(fp_out,stack);//ファイルへ逆順に出力
  fclose(fp_in);

  printf("スタックを表示します。\n");
  printStack(stack);

  return 0;
}

IntStack makeStack(){
  IntStack stack=(IntStack)makeCell(DUMMY);//ダミーのセル
}

int isEmpty(IntStack stack){
  if(stack->next==NULL){
    return NODATA;
  }else{
    return EXISTDATA;
  }
}


Cell_P makeCell(int n){
  Cell_P new =(Cell_P)malloc(sizeof(IntCell));
  new->data=n;
  return new;
}

void push(IntStack stack,int data){
  Cell_P new_cell=makeCell(data);
  new_cell->next=stack->next;
  stack->next=new_cell;
  return;
}

int pop(IntStack stack){
  Cell_P top=stack->next;
  int data;
  if(top!=NULL){
    data=top->data;
    stack->next=top->next;
    free(top);
    return data;
  }else{
    printf("No data\n");
    return -1;
  }
}

void printStack(IntStack stack){
  Cell_P p=stack->next;
  printf("(");
  while(p!=NULL){
    printf("\%3d,",p->data);
    p=p->next;
  }
  printf("]\n");
  return ;
}

void fscanToStack(FILE *fp,IntStack stack){
  int idata;
  while(fscanf(fp,"%d",&idata)!=EOF){
    push(stack,idata);
  }
  return;
}

void reverse_fprint(FILE*fp,IntStack stack){
  int idata;
  while(isEmpty(stack)==EXISTDATA){
    idata=pop(stack);
    fprintf(fp,"%3d",idata);
  }
  return ;
}


  
  

