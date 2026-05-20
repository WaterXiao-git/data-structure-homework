#define _CRT_SECURE_NO_WARNINGS
//实验一 图书管理系统
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10000

typedef struct { char no[20]; char name[50]; float price; } Book;
typedef struct LNode { Book data; struct LNode* next; } LNode, * LinkList;

LinkList createBookList() {
    LinkList head = NULL, current = NULL;
    char no[20], name[50], input[100]; float price;
    while (1) {
        fgets(input, sizeof(input), stdin);
        if (input[0]=='0'&&input[1]==' '&&input[2]=='0'&&input[3]==' '&&input[4]=='0') break;
        sscanf(input,"%s %s %f",no,name,&price);
        LNode* newBook = (LNode*)malloc(sizeof(LNode));
        strcpy(newBook->data.no,no); strcpy(newBook->data.name,name);
        newBook->data.price=price; newBook->next=NULL;
        if (!head) { head=newBook; current=head; }
        else { current->next=newBook; current=newBook; }
    }
    return head;
}
int listlength(LinkList head) {
    int c=0; while(head) { c++; head=head->next; } return c;
}
void Listlength(LinkList head) { printf("%d\n",listlength(head)); }
void printBookList(LinkList head) {
    while(head) { printf("%s %s %.2f\n",head->data.no,head->data.name,head->data.price); head=head->next; }
}
void ClearList(LinkList head) { LNode* t; while(head) { t=head; head=head->next; free(t); } }

void insertBook(LinkList* head, int pos, char* no, char* name, float price) {
    LNode* n=(LNode*)malloc(sizeof(LNode));
    strcpy(n->data.no,no); strcpy(n->data.name,name); n->data.price=price;
    if(!*head||pos==0) { n->next=*head; *head=n; return; }
    LNode* c=*head; int i=0;
    while(c&&i<pos-1) { c=c->next; i++; }
    if(!c) { printf("Error: invalid position\n"); free(n); return; }
    n->next=c->next; c->next=n;
}

void deleteBook(LinkList* head, int pos) {
    if(!*head) { printf("Error: empty list\n"); return; }
    LNode* c=*head, *p=NULL; int i=0;
    while(c&&i<pos) { p=c; c=c->next; i++; }
    if(!c) { printf("Error: invalid position\n"); return; }
    if(!p) *head=c->next; else p->next=c->next;
    free(c);
}

#define HASH_TABLE_SIZE 101
typedef struct HashNode { char* key; struct HashNode* next; } HashNode;
typedef struct { HashNode* buckets[HASH_TABLE_SIZE]; } HashTable;

HashTable* createHT() {
    HashTable* ht=(HashTable*)malloc(sizeof(HashTable));
    for(int i=0;i<HASH_TABLE_SIZE;i++) ht->buckets[i]=NULL; return ht;
}
unsigned int hash(char* k) { unsigned int h=0; while(*k) h=(h*31+*k++)%HASH_TABLE_SIZE; return h; }
int containsKey(HashTable* ht, char* k) {
    HashNode* c=ht->buckets[hash(k)]; while(c) { if(!strcmp(c->key,k)) return 1; c=c->next; } return 0;
}
void insertKey(HashTable* ht, char* k) {
    HashNode* n=(HashNode*)malloc(sizeof(HashNode));
    unsigned int i=hash(k); n->key=_strdup(k); n->next=ht->buckets[i]; ht->buckets[i]=n;
}
void freeHT(HashTable* ht) {
    for(int i=0;i<HASH_TABLE_SIZE;i++) { HashNode* c=ht->buckets[i]; while(c) { HashNode* t=c; c=c->next; free(t->key); free(t); } } free(ht);
}

LinkList cheakBookList(LinkList head) {
    if(!head||!head->next) return head;
    HashTable* ht=createHT(); LinkList c=head, p=NULL;
    while(c) {
        if(containsKey(ht,c->data.no)) { LinkList t=c; if(!p) head=c->next; else p->next=c->next; c=c->next; free(t); }
        else { insertKey(ht,c->data.no); p=c; c=c->next; }
    }
    freeHT(ht); return head;
}

void modifyBookPrice(LinkList head) {
    double total=0; int cnt=0; LNode* c=head;
    while(c) { total+=c->data.price; cnt++; c=c->next; }
    double avg=total/cnt; printf("%.2f\n",avg); c=head;
    while(c) { if(c->data.price<avg) c->data.price*=1.2; else c->data.price*=1.1; c=c->next; }
}

void findMostExpensiveBooks(LinkList head) {
    double max=0; LNode* c=head; int cnt=0;
    while(c) { if(c->data.price>max) max=c->data.price; c=c->next; }
    c=head; while(c) { if(c->data.price==max) cnt++; c=c->next; }
    printf("%d\n",cnt); c=head;
    while(c) { if(c->data.price==max) printf("%s %s %.2f\n",c->data.no,c->data.name,c->data.price); c=c->next; }
}

int main() {
    printf("Create book list:\n"); LinkList bookList=createBookList(); if(!bookList) return 1;
    int a,pos; char no[20],name[50]; float price;
    printf("Choose function:\n 1.Print\n 2.Modify price\n 3.Most expensive\n 4.Insert\n 5.Delete\n 6.Deduplicate\n");
    scanf("%d",&a);
    switch(a) {
        case 1: Listlength(bookList); printBookList(bookList); break;
        case 2: modifyBookPrice(bookList); Listlength(bookList); printBookList(bookList); break;
        case 3: Listlength(bookList); findMostExpensiveBooks(bookList); break;
        case 4: scanf("%d%s%s%f",&pos,no,name,&price); insertBook(&bookList,pos-1,no,name,price); Listlength(bookList); printBookList(bookList); break;
        case 5: scanf("%d",&pos); deleteBook(&bookList,pos-1); Listlength(bookList); printBookList(bookList); break;
        case 6: bookList=cheakBookList(bookList); Listlength(bookList); printBookList(bookList); break;
    }
    ClearList(bookList); return 0;
}*/

//实验二 表达式求值（链栈 + 顺序栈）
//2.1 链栈实现（只支持个位数，以=结尾）
/*#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define Max 100
typedef struct nNode { int data; struct nNode* next; } nNode, * nStack;
typedef struct strNode { char sign; struct strNode* next; } strNode, * strStack;
nStack createnStack() { return NULL; }
strStack createstrStack() { return NULL; }
void nPush(nStack* top, int d) { nNode* q=(nNode*)malloc(sizeof(nNode)); q->data=d; q->next=*top; *top=q; }
void strPush(strStack* top, char s) { strNode* q=(strNode*)malloc(sizeof(strNode)); q->sign=s; q->next=*top; *top=q; }
int nPop(nStack* top) { if(!*top) return -1; int e=(*top)->data; nNode* p=*top; *top=(*top)->next; free(p); return e; }
char strPop(strStack* top) { if(!*top) return -1; char e=(*top)->sign; strNode* p=*top; *top=(*top)->next; free(p); return e; }
int ngetTop(nStack top) { return top?top->data:-1; }
char strgetTop(strStack top) { return top?top->sign:-1; }

int getIndex(char theta) {
    switch(theta) {
        case'+':return 0; case'-':return 1; case'*':return 2; case'/':return 3;
        case'(':return 4; case')':return 5; case'=':return 6; default:return 0;
    }
}
char getPriority(char t1, char t2) {
    const char p[7][7]={{'>','>','<','<','<','>','>'},{'>','>','<','<','<','>','>'},
    {'>','>','>','>','<','>','>'},{'>','>','>','>','<','>','>'},
    {'<','<','<','<','<','=','0'},{'>','>','>','>','0','>','>'},
    {'<','<','<','<','<','0','='}};
    return p[getIndex(t1)][getIndex(t2)];
}
int Canculate(int a, char t, int b) {
    switch(t) { case'+':return a+b; case'-':return a-b; case'*':return a*b;
    case'/':return b? a/b:0; default:return 0; }
}
int In(char ch) { return (ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='='); }

int main() {
    char ch,theta; nStack data=createnStack(); strStack sign=createstrStack();
    printf("Input expression (ends with =, single digit):\n");
    strPush(&sign,'='); ch=getchar();
    while(ch!='='||strgetTop(sign)!='=') {
        if(!In(ch)) { nPush(&data,ch-'0'); ch=getchar(); }
        else {
            switch(getPriority(strgetTop(sign),ch)) {
                case'<': strPush(&sign,ch); ch=getchar(); break;
                case'>': theta=strPop(&sign); int b=nPop(&data), a=nPop(&data); nPush(&data,Canculate(a,theta,b)); break;
                case'=': theta=strPop(&sign); ch=getchar(); break;
            }
        }
    }
    printf("%d\n",ngetTop(data)); return 0;
}*/

//2.2 顺序栈实现（支持多位数和小数，以=结尾）
/*#include<stdio.h>
#include<stdlib.h>
#define Max 30
typedef struct { float elem[Max]; int top; } nStack;
typedef struct { char elem[Max]; int top; } strStack;

void nInitStack(nStack* S) { S->top=-1; }
int nIsEmpty(nStack* S) { return S->top==-1; }
int nPush(nStack* S, float x) { if(S->top==Max-1) return 0; S->elem[++S->top]=x; return 1; }
int nPop(nStack* S, float* x) { if(S->top==-1) return 0; *x=S->elem[S->top--]; return 1; }
int nGetTop(nStack* S, float* x) { if(S->top==-1) return 0; *x=S->elem[S->top]; return 1; }

void strInitStack(strStack* S) { S->top=-1; }
int strPush(strStack* S, char x) { if(S->top==Max-1) return 0; S->elem[++S->top]=x; return 1; }
int strPop(strStack* S, char* x) { if(S->top==-1) return 0; *x=S->elem[S->top--]; return 1; }
int strGetTop(strStack* S, char* x) { if(S->top==-1) return 0; *x=S->elem[S->top]; return 1; }

int In(char ch) { return (ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='='); }
int getIndex(char theta) {
    switch(theta) {
        case'+':return 0; case'-':return 1; case'*':return 2; case'/':return 3;
        case'(':return 4; case')':return 5; case'=':return 6; default:return 0;
    }
}
char getPriority(char t1, char t2) {
    const char p[7][7]={{'>','>','<','<','<','>','>'},{'>','>','<','<','<','>','>'},
    {'>','>','>','>','<','>','>'},{'>','>','>','>','<','>','>'},
    {'<','<','<','<','<','=','0'},{'>','>','>','>','0','>','>'},
    {'<','<','<','<','<','0','='}};
    return p[getIndex(t1)][getIndex(t2)];
}
float Canculate(float a, char t, float b) {
    switch(t) { case'+':return a+b; case'-':return a-b; case'*':return a*b;
    case'/':return b? a/b:0; default:return 0; }
}

float EvaluateExpression() {
    char x,y,ch,op; float a,b,v;
    nStack data; strStack sign;
    nInitStack(&data); strInitStack(&sign);
    strPush(&sign,'=');
    printf("Input expression (ends with =):\n");
    ch=getchar(); strGetTop(&sign,&y);
    while(ch!='='||y!='=') {
        if(!In(ch)) {
            int i,temp1,temp; float temp2; float p[7]={0,0.1,0.01,0.001,0.0001,0.00001,0.000001};
            temp=ch-'0'; ch=getchar();
            while(!In(ch)&&ch!='.') { temp1=ch-'0'; temp=temp*10+temp1; ch=getchar(); }
            temp2=temp;
            if(ch=='.') { ch=getchar(); for(i=1;!In(ch);i++) { temp1=ch-'0'; temp2+=temp1*p[i]; ch=getchar(); } }
            nPush(&data,temp2);
        } else {
            switch(getPriority(y,ch)) {
                case'<': strPush(&sign,ch); ch=getchar(); break;
                case'=': strPop(&sign,&x); ch=getchar(); break;
                case'>': strPop(&sign,&op); nPop(&data,&b); nPop(&data,&a);
                         v=Canculate(a,op,b); nPush(&data,v); break;
            }
            strGetTop(&sign,&y);
        }
    }
    nGetTop(&data,&v); return v;
}
int main() { printf("%.2f",EvaluateExpression()); return 0; }*/

//实验三 病毒DNA检测（BF / KMP）
/*#include <stdio.h>
#include <string.h>
#define MAX 100

int Index_BF(char* s, char* p) {
    int i=0,j=0,sL=strlen(s),pL=strlen(p);
    while(i<sL&&j<pL) { if(s[i]==p[j]) { i++; j++; } else { i=i-j+1; j=0; } }
    return j==pL?1:0;
}

void getNext(char* p, int next[]) {
    int j=0,k=-1; next[0]=-1;
    while(j<strlen(p)) {
        if(k==-1||p[j]==p[k]) { ++j; ++k; next[j]=p[j]==p[k]?next[k]:k; }
        else k=next[k];
    }
}

int Index_KMP(char* s, char* p) {
    int i=0,j=0,sL=strlen(s),pL=strlen(p),next[MAX];
    getNext(p,next);
    while(i<sL&&j<pL) { if(j==-1||s[i]==p[j]) { i++; j++; } else j=next[j]; }
    return j==pL? i-j : 0;
}

int main() {
    char Virus[100],Person[100],result[100][4];
    int count=0,a;
    printf("Choose algorithm: 1.BF 2.KMP\n"); scanf("%d",&a);
    printf("Input virus DNA and human DNA (0 0 to end):\n");
    while(1) {
        scanf("%s %s",Virus,Person);
        if(strcmp(Virus,"0")==0&&strcmp(Person,"0")==0) break;
        int flag=0,m=strlen(Virus);
        for(int i=0;i<m;i++) {
            char temp[100];
            for(int j=0;j<m;j++) temp[j]=Virus[(i+j)%m];
            temp[m]='\0';
            flag=(a==1)?Index_BF(Person,temp):Index_KMP(Person,temp);
            if(flag) break;
        }
        strcpy(result[count],flag?"YES":"NO"); count++;
    }
    printf("Result:\n");
    for(int i=0;i<count;i++) printf("%s\n",result[i]);
    return 0;
}*/

//实验四 哈夫曼编码
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int alpha[26],k=0; char list[26];
typedef struct { int weight,parent,lchild,rchild; } HTNode,*HuffmanTree;
typedef char** HuffmanCode;

void Select(HuffmanTree HT, int sum, int* s1, int* s2) {
    int i,min1=100,min2=100;
    for(i=1;i<=sum;i++) if(HT[i].parent==0&&HT[i].weight<min1) { min1=HT[i].weight; *s1=i; }
    int t=HT[*s1].weight; HT[*s1].weight=100;
    for(i=1;i<=sum;i++) if(HT[i].parent==0&&HT[i].weight<min2) { min2=HT[i].weight; *s2=i; }
    HT[*s1].weight=t;
}

void CreateHuffmanTree(HuffmanTree* HT, int n) {
    if(n<=1) return; int m=2*n-1;
    *HT=(HTNode*)malloc((m+1)*sizeof(HTNode));
    for(int i=1;i<=m;i++) { (*HT)[i].parent=(*HT)[i].lchild=(*HT)[i].rchild=0; }
    for(int i=1;i<=n;i++) (*HT)[i].weight=alpha[i-1];
    int s1,s2;
    for(int i=n+1;i<=m;i++) {
        Select(*HT,i-1,&s1,&s2);
        (*HT)[s1].parent=i; (*HT)[s2].parent=i;
        (*HT)[i].lchild=s1; (*HT)[i].rchild=s2;
        (*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
    }
}

void CreatHuffmanCode(HuffmanTree HT, HuffmanCode* HC, int n) {
    *HC=(char**)malloc((n+1)*sizeof(char*));
    char* cd=(char*)malloc(n*sizeof(char)); cd[n-1]='\0';
    for(int i=1;i<=n;i++) {
        int start=n-1,c=i,f=HT[i].parent;
        while(f) {
            cd[--start]=HT[f].lchild==c?'0':'1';
            c=f; f=HT[f].parent;
        }
        (*HC)[i]=(char*)malloc((n-start)*sizeof(char));
        strcpy((*HC)[i],&cd[start]);
    }
    free(cd);
}

void Output(HuffmanTree HT, HuffmanCode HC) {
    for(int i=1;i<=2*k-1;i++) printf("%d %d %d %d %d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
    for(int i=1;i<=k;i++) { printf("%c:%s",list[i-1],HC[i]); if(i!=k) printf(" "); }
    printf("\n");
}

void Translate(HuffmanCode HC, char* s) {
    int i=0;
    while(s[i]) { int j=0; while(j<26) { if(s[i]==list[j]) printf("%s",HC[j+1]); j++; } i++; }
    printf("\n"); i=0; while(s[i]) { printf("%c",s[i]); i++; } printf("\n");
}

int main() {
    char s[100];
    printf("Input string:\n");
    while(scanf("%s",s)&&strcmp(s,"0")!=0) {
        int fre[26]={0}; k=0;
        for(int i=0;s[i];i++) if(s[i]>=97) fre[s[i]-97]++;
        for(int i=0;i<26;i++) if(fre[i]) { printf("%c:%d",i+97,fre[i]); if(k!=26) printf(" "); alpha[k]=fre[i]; list[k]=i+97; k++; }
        printf("\n");
        HuffmanTree HT=NULL; HuffmanCode HC=NULL;
        CreateHuffmanTree(&HT,k); CreatHuffmanCode(HT,&HC,k);
        Output(HT,HC); Translate(HC,s);
        printf("Input next string (0 to exit):\n");
    }
    return 0;
}*/

//实验五 二叉树表达式解析与求值
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
#define ELEM 10

typedef struct BiNode { char data; struct BiNode *lchild,*rchild; } BiNode,*BiTree;

typedef struct { char *base,*top; int stacksize; } SqStack;
int InitStack(SqStack* S) { S->base=(char*)malloc(SIZE*sizeof(char)); if(!S->base) exit(0); S->top=S->base; S->stacksize=SIZE; return 1; }
int Push(SqStack* S, char e) {
    if(S->top-S->base>=SIZE) { S->base=(char*)realloc(S->base,(S->stacksize+ELEM)*sizeof(char)); if(!S->base) exit(1); S->top=S->base+S->stacksize; S->stacksize+=ELEM; }
    *(S->top)++=e; return 1;
}
int Pop(SqStack* S, char* e) { if(S->top==S->base) return 0; *e=*--(S->top); return 1; }
int GetTop(SqStack* S, char* e) { if(S->top==S->base) return 0; *e=*(S->top-1); return 1; }

typedef struct { BiTree* base,*top; int stacksize; } SqStack_BiTree;
void SB_Init(SqStack_BiTree* S) { S->base=(BiTree*)malloc(SIZE*sizeof(BiTree)); if(!S->base) exit(0); S->top=S->base; S->stacksize=SIZE; }
void SB_Push(SqStack_BiTree* S, BiTree e) {
    if(S->top-S->base>=S->stacksize) { S->base=(BiTree*)realloc(S->base,(S->stacksize+ELEM)*sizeof(BiTree)); if(!S->base) exit(1); S->top=S->base+S->stacksize; S->stacksize+=ELEM; }
    *(S->top)++=e;
}
int SB_Pop(SqStack_BiTree* S, BiTree* e) { if(S->top==S->base) return 0; *e=*--(S->top); return 1; }

char Precede(char t1, char t2) {
    char pre[7][7]={{'>','>','<','<','<','>','>'},{'>','>','<','<','<','>','>'},
    {'>','>','>','>','<','>','>'},{'>','>','>','>','<','>','>'},
    {'<','<','<','<','<','=','0'},{'>','>','>','>','0','>','>'},
    {'<','<','<','<','<','0','='}};
    int i,j;
    switch(t1) { case'+':i=0;break;case'-':i=1;break;case'*':i=2;break;case'/':i=3;break;case'(':i=4;break;case')':i=5;break;case'=':i=6;break; }
    switch(t2) { case'+':j=0;break;case'-':j=1;break;case'*':j=2;break;case'/':j=3;break;case'(':j=4;break;case')':j=5;break;case'=':j=6;break; }
    return pre[i][j];
}
int In(char ch) { return ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='='; }
int Operate(int a, char t, int b) { switch(t) { case'+':return a+b;case'-':return a-b;case'*':return a*b;case'/':return b?a/b:0; } return 0; }

void EvaluateExpression(BiTree* root, char* str) {
    SqStack OPTR; InitStack(&OPTR);
    SqStack_BiTree EXPT; SB_Init(&EXPT);
    char ch,x,theta; BiTree a,b; int i=0;
    Push(&OPTR,'='); ch=str[i++]; GetTop(&OPTR,&x);
    while(ch!='='||x!='=') {
        if(In(ch)) {
            switch(Precede(x,ch)) {
                case'<': Push(&OPTR,ch); ch=str[i++]; break;
                case'=': Pop(&OPTR,&x); ch=str[i++]; break;
                case'>': Pop(&OPTR,&theta);
                    BiTree T=(BiNode*)malloc(sizeof(BiNode)); T->data=theta;
                    SB_Pop(&EXPT,&b); SB_Pop(&EXPT,&a);
                    T->lchild=a; T->rchild=b; SB_Push(&EXPT,T); *root=T; break;
            }
        }
        if(ch>='0'&&ch<='9') {
            BiTree T=(BiNode*)malloc(sizeof(BiNode)); T->data=ch; T->lchild=T->rchild=NULL;
            SB_Push(&EXPT,T); ch=str[i++];
        }
        GetTop(&OPTR,&x);
    }
}

int calculate_BiTree(BiTree T) {
    if(!T) return 0;
    if(!T->lchild&&!T->rchild) return T->data-'0';
    int lv=calculate_BiTree(T->lchild), rv=calculate_BiTree(T->rchild);
    return Operate(lv,T->data,rv);
}

int main() {
    BiTree T; char str[1000]; int result[100]={0},num=0;
    do { printf("Input expression:\n"); gets(str); EvaluateExpression(&T,str); result[num++]=calculate_BiTree(T); } while(strcmp(str,"=")!=0);
    for(int j=0;j<num-1;j++) printf("\nResult: %d",result[j]);
    return 0;
}*/

//实验六 Dijkstra 最短路径
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MVNum 100
#define MaxInt 32767

typedef struct { char vex[MVNum]; int arcs[MVNum][MVNum]; int Vexnum,arcnum; } AMGraph;

void CreateAMGraph(AMGraph* G) {
    int i,j,w; char a,b;
    printf("Input vertex count and edge count: "); scanf("%d%d",&G->Vexnum,&G->arcnum);
    if(!G->Vexnum&&!G->arcnum) exit(0);
    printf("Input vertices: "); for(i=0;i<G->Vexnum;i++) scanf(" %c",&G->vex[i]);
    for(i=0;i<G->Vexnum;i++) for(j=0;j<G->Vexnum;j++) G->arcs[i][j]=MaxInt;
    for(i=0;i<G->arcnum;i++) {
        printf("Input edge (start end weight): "); scanf(" %c %c %d",&a,&b,&w);
        for(j=0;j<G->Vexnum;j++) if(G->vex[j]==a) for(int k=0;k<G->Vexnum;k++) if(G->vex[k]==b) { G->arcs[j][k]=w; break; }
    }
}

void Dijkstra(AMGraph G, int v0, int* dist, int* path) {
    int S[MVNum],i,j,u,min;
    for(i=0;i<G.Vexnum;i++) { S[i]=0; dist[i]=G.arcs[v0][i]; path[i]=dist[i]<MaxInt?v0:-1; }
    S[v0]=1; dist[v0]=0; path[v0]=-1;
    for(i=0;i<G.Vexnum-1;i++) {
        min=MaxInt; u=v0;
        for(j=0;j<G.Vexnum;j++) if(!S[j]&&dist[j]<min) { u=j; min=dist[j]; }
        S[u]=1;
        for(j=0;j<G.Vexnum;j++) if(!S[j]&&G.arcs[u][j]<MaxInt&&dist[u]+G.arcs[u][j]<dist[j]) { dist[j]=dist[u]+G.arcs[u][j]; path[j]=u; }
    }
}

int main() {
    AMGraph G; int dist[MVNum],path[MVNum]; char start,end; int i,j;
    while(1) {
        CreateAMGraph(&G);
        printf("Input start and end:\n"); scanf(" %c %c",&start,&end);
        for(i=0;i<G.Vexnum;i++) if(G.vex[i]==start) break;
        for(j=0;j<G.Vexnum;j++) if(G.vex[j]==end) break;
        Dijkstra(G,i,dist,path);
        printf("Shortest distance: %d\n",dist[j]);
        printf("Path: "); int stack[MVNum],top=-1;
        while(j!=-1) { stack[++top]=G.vex[j]; j=path[j]; }
        while(top!=-1) printf("%c ",stack[top--]); printf("\n");
    }
    return 0;
}*/

//实验七 六度空间（BFS）
/*#include <stdio.h>
#include <stdlib.h>
#define MAXN 1000
int G[MAXN][MAXN]={0},N,M,visited[MAXN]={0};
void init() { for(int i=0;i<N;i++) visited[i]=0; }

int BFS(int v) {
    int Q[10001],f=-1,r=-1;
    visited[v]=1; int cnt=1,lv=0,last=v,tail;
    Q[++r]=v;
    while(f<r) {
        v=Q[++f];
        for(int i=0;i<N;i++) if(!visited[i]&&G[v][i]) { visited[i]=1; Q[++r]=i; cnt++; tail=i; }
        if(v==last) { lv++; last=tail; }
        if(lv==6) break;
    }
    return cnt;
}

int main() {
    while(1) {
        printf("Input vertices and edges (0 0 to exit):\n"); scanf("%d%d",&N,&M);
        if(!N&&!M) break;
        for(int i=0;i<M;i++) { int v1,v2; scanf("%d%d",&v1,&v2); G[v1-1][v2-1]=1; G[v2-1][v1-1]=1; }
        printf("Six-degree space percentage:\n");
        for(int i=0;i<N;i++) { init(); int cnt=BFS(i); printf("%d: %.2f%%\n",i+1,cnt*100.0/N); }
        for(int i=0;i<MAXN;i++) for(int j=0;j<MAXN;j++) G[i][j]=0;
    }
    return 0;
}*/

//实验八 8种排序算法
/*#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 100

typedef struct { char name[8]; float score; } Student;

void insertionSort(Student s[], int n) {
    for(int i=1;i<n;i++) { Student t=s[i]; int j=i-1; while(j>=0&&s[j].score<t.score) { s[j+1]=s[j]; j--; } s[j+1]=t; }
}

void quickSort(Student s[], int l, int r) {
    if(l>=r) return; int i=l,j=r; Student p=s[l];
    while(i<j) { while(i<j&&s[j].score<=p.score) j--; if(i<j) s[i++]=s[j]; while(i<j&&s[i].score>p.score) i++; if(i<j) s[j--]=s[i]; }
    s[i]=p; quickSort(s,l,i-1); quickSort(s,i+1,r);
}

void bubbleSort(Student s[], int n) {
    for(int i=0;i<n-1;i++) for(int j=0;j<n-i-1;j++) if(s[j].score<s[j+1].score) { Student t=s[j]; s[j]=s[j+1]; s[j+1]=t; }
}

void selectionSort(Student s[], int n) {
    for(int i=0;i<n-1;i++) { int m=i; for(int j=i+1;j<n;j++) if(s[j].score>s[m].score) m=j; Student t=s[i]; s[i]=s[m]; s[m]=t; }
}

void binaryInsertionSort(Student s[], int n) {
    for(int i=1;i<n;i++) { Student t=s[i]; int l=0,r=i-1,m; while(l<=r) { m=(l+r)/2; if(s[m].score<t.score) r=m-1; else l=m+1; } for(int j=i-1;j>=l;j--) s[j+1]=s[j]; s[l]=t; }
}

void shellSort(Student s[], int n) {
    for(int g=n/2;g>0;g/=2) for(int i=g;i<n;i++) { Student t=s[i]; int j; for(j=i;j>=g&&s[j-g].score<t.score;j-=g) s[j]=s[j-g]; s[j]=t; }
}

void merge(Student s[], Student L[], int lsz, Student R[], int rsz) {
    int i=0,j=0,k=0; while(i<lsz&&j<rsz) s[k++]=L[i].score>=R[j].score?L[i++]:R[j++];
    while(i<lsz) s[k++]=L[i++]; while(j<rsz) s[k++]=R[j++];
}
void mergeSort(Student s[], int n) {
    if(n<=1) return; int m=n/2; Student L[100],R[100];
    for(int i=0;i<m;i++) L[i]=s[i]; for(int i=m;i<n;i++) R[i-m]=s[i];
    mergeSort(L,m); mergeSort(R,n-m); merge(s,L,m,R,n-m);
}

void heapify(Student s[], int n, int i) {
    int l=i; int lc=2*i+1,rc=2*i+2;
    if(lc<n&&s[lc].score<s[l].score) l=lc; if(rc<n&&s[rc].score<s[l].score) l=rc;
    if(l!=i) { Student t=s[i]; s[i]=s[l]; s[l]=t; heapify(s,n,l); }
}
void heapSort(Student s[], int n) {
    for(int i=n/2-1;i>=0;i--) heapify(s,n,i);
    for(int i=n-1;i>0;i--) { Student t=s[0]; s[0]=s[i]; s[i]=t; heapify(s,i,0); }
}

int main() {
    Student s[MAX_STUDENTS]; int n=0;
    printf("Input student info (name score, 0 0 to end):\n");
    while(1) { scanf("%s",s[n].name); scanf("%f",&s[n].score); if(!strcmp(s[n].name,"0")&&s[n].score==0) break; n++; }
    int ch; printf("Choose sort:\n 1.Insertion 2.Quick 3.Bubble 4.Selection 5.BinaryInsert 6.Shell 7.Merge 8.Heap\n"); scanf("%d",&ch);
    switch(ch) {
        case 1: insertionSort(s,n); break; case 2: quickSort(s,0,n-1); break;
        case 3: bubbleSort(s,n); break; case 4: selectionSort(s,n); break;
        case 5: binaryInsertionSort(s,n); break; case 6: shellSort(s,n); break;
        case 7: mergeSort(s,n); break; case 8: heapSort(s,n); break;
        default: return 1;
    }
    int r=1; printf("%d %s %.2f\n",r,s[0].name,s[0].score);
    for(int i=1;i<n;i++) { if(s[i].score!=s[i-1].score) r=i+1; printf("%d %s %.2f\n",r,s[i].name,s[i].score); }
    return 0;
}
*/