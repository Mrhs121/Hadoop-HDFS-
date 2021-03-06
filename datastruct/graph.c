#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 100
typedef int VertexType;
typedef int I_ten[10];
#define V_Type %d
#define VISITED 1
#define NOT_VISITED 0
#define MAXX 999

/*
 *  
 *  数据结构 图的存储结构以及相关的操作
 *
 *
 */
//---------邻接矩阵

typedef struct{
    int Vex[MAXNUM];
    int Edge[MAXNUM][MAXNUM];
    int vexnum,edgenum;
}MGraph;

// ---------------------------

FILE * fin;
// ----邻接表------ 
typedef struct ArcNode{
    int adjvex; //vertices index
    int info; //  权值
    struct ArcNode * next;
}ArcNode;

typedef struct VNode{
    VertexType data;
    ArcNode * first;
}VNode,AdjList[MAXNUM];

typedef struct{
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;
// ----------------------------------------

typedef struct Queue{
    int data[MAXNUM];
    int front;
    int rear;
}Q;
    void init(Q **queue){
        (*queue)->front = 0;
        (*queue)->rear = 0;
    }

    void EnQueue(Q **queue,int _data){
        (*queue)->data[((*queue)->rear)++] = _data;
    }
    int DeQueue(Q **queue){
        //int f = queue->front;
        //printf("%d,%d\n",queue->front,queue->data[f]);
        //printf("->%d\n",queue->data[queue->front]);
        
        return (*queue)->data[(*queue)->front++];
    }
    int isEmpty(Q *queue){
        return queue->front-queue->rear;
    }

// 打印邻接表的结构
void printAlg(ALGraph * algraph){
    int i=0;
    printf("---------------邻接表的结构-----------------\n");
    printf("顶点 ---(权)--->adjvex-----(权)----->adjvex\n");
    for(i=0;i<algraph->vexnum;i++){
        printf("%d: %d ",i,algraph->vertices[i].data);
        ArcNode * p = algraph->vertices[i].first;
        while(p!=NULL){
            printf("---(%d)--->%d(%d)",p->info,p->adjvex,algraph->vertices[p->adjvex].data
                   );
            p = p->next;
        }
        printf("\n");
    }
    printf("----------------------------------------------\n");
}

ALGraph * create_graph(){
    //int vexnum;
    ALGraph * algraph = (ALGraph*)malloc(sizeof(ALGraph));
    int i=0;
    printf("input vexnum and arcnum:");
    fscanf(fin,"%d%d",&algraph->vexnum,&algraph->arcnum);
    printf("---->%d %d\n",algraph->vexnum,algraph->arcnum);
    // printf("---->input all vex's data\n");
    //初始化定点表
    for(i=0;i<algraph->vexnum;i++){
        //printf("input vex%d\'s data:",i);
        fscanf(fin,"%d",&algraph->vertices[i].data);
        algraph->vertices[i].first = (ArcNode*)malloc(sizeof(ArcNode));
        algraph->vertices[i].first = NULL;
    }
    // 初始化边表
    printf("----> input arc\n");
    for(i=0;i<algraph->vexnum;i++){
        int arcnum = 0;
        int j=0;
        ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
        p = algraph->vertices[i].first; 
        fscanf(fin,"%d",&arcnum);         
        for(j=0;j<arcnum;j++){
           ArcNode * newnode = (ArcNode*)malloc(sizeof(ArcNode));
           newnode->next = NULL;
            //printf("int arcnode data:\n");
            // 此处输入的顶点的编号，数组下表为0 ，编号为1，注意区别
            int num=0;    
            fscanf(fin,"%d",&num);
            //printf("v%d connect-->v%d\t",i+1,num);
            newnode->adjvex = num;
            if(p==NULL){
                algraph->vertices[i].first = newnode;
                p = algraph->vertices[i].first;
            } else {
                p->next = newnode;
                p = newnode;
            } 
        }
        printf("\n");
    }
    return  algraph;
}

// 创建有向图
ALGraph * createDAG(){
    ALGraph * algraph = (ALGraph*)malloc(sizeof(ALGraph));
    int i=0;
    printf("input vexnum and arcnum:");
    fscanf(fin,"%d%d",&algraph->vexnum,&algraph->arcnum);
    printf("---->%d %d\n",algraph->vexnum,algraph->arcnum);
    // printf("---->input all vex's data\n");
    //初始化定点表
    for(i=0;i<algraph->vexnum;i++){
        //printf("input vex%d\'s data:",i);
        fscanf(fin,"%d",&algraph->vertices[i].data);
        algraph->vertices[i].first = (ArcNode*)malloc(sizeof(ArcNode));
        algraph->vertices[i].first = NULL;
    }
    int v1,v2,info;
    for(i=0;i<algraph->arcnum;i++){
        fscanf(fin,"%d %d\n",&v1,&v2);
        ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
        ArcNode * t = (ArcNode*)malloc(sizeof(ArcNode));
        p->next = NULL;
        t->next = NULL;
        if(algraph->vertices[v1].first == NULL){
            //ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex = v2;
            //p->info = info;
            algraph->vertices[v1].first = p; 
        } else {
            p = algraph->vertices[v1].first;
            while(p->next!=NULL)
                p = p->next;
            t->adjvex = v2;
            //t->info = info;
            p->next = t;
        }    
        p = (ArcNode*)malloc(sizeof(ArcNode));
        t = (ArcNode*)malloc(sizeof(ArcNode));
        p->next = NULL;
        t->next = NULL;
          
    }
    return algraph;
}



// 按照边创建邻接表
ALGraph * createAlgByArc(){
    ALGraph * algraph = (ALGraph*)malloc(sizeof(ALGraph));
    int i=0;
    printf("input vexnum and arcnum:");
    fscanf(fin,"%d%d",&algraph->vexnum,&algraph->arcnum);
    printf("---->%d %d\n",algraph->vexnum,algraph->arcnum);
    // printf("---->input all vex's data\n");
    //初始化定点表
    for(i=0;i<algraph->vexnum;i++){
        //printf("input vex%d\'s data:",i);
        fscanf(fin,"%d",&algraph->vertices[i].data);
        algraph->vertices[i].first = (ArcNode*)malloc(sizeof(ArcNode));
        algraph->vertices[i].first = NULL;
    }
    int v1,v2,info;
    for(i=0;i<algraph->arcnum;i++){
        fscanf(fin,"%d %d %d\n",&v1,&v2,&info);
        ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
        ArcNode * t = (ArcNode*)malloc(sizeof(ArcNode));
        p->next = NULL;
        t->next = NULL;
        if(algraph->vertices[v1].first == NULL){
            //ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex = v2;
           p->info = info;
            algraph->vertices[v1].first = p; 
        } else {
            p = algraph->vertices[v1].first;
            while(p->next!=NULL)
                p = p->next;
            t->adjvex = v2;
           // t->info = info;
            p->next = t;
        }    
        p = (ArcNode*)malloc(sizeof(ArcNode));
        t = (ArcNode*)malloc(sizeof(ArcNode));
        p->next = NULL;
        t->next = NULL;
        if(algraph->vertices[v2].first == NULL) {
            //ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex = v1;
            p->info = info;
            algraph->vertices[v2].first = p; 
        } else {
            p = algraph->vertices[v2].first;
            while(p->next!=NULL)
                p = p->next;
            t->adjvex = v1;
            t->info = info;
            p->next = t;
        }    
          
    }
    return algraph;
}


// 创建邻接举矩阵 
MGraph * create(){
    FILE * fin = fopen("mgraph.txt","r");
    MGraph * mgraph = (MGraph*)malloc(sizeof(mgraph));
    fscanf(fin,"%d %d\n",&mgraph->vexnum,&mgraph->edgenum);
    int i=0;
    int j=0;
    int l,r,info;
    printf("%d %d\n",mgraph->vexnum,mgraph->edgenum);
    for(i=0;i<mgraph->vexnum;i++){
       // printf("--->\n");
        fscanf(fin,"%d ",&mgraph->Vex[i]);
    }
    for(i=0;i<mgraph->vexnum;i++){
        for(j=0;j<mgraph->vexnum;j++){
           // printf("%d %d\n",i,j);
            mgraph->Edge[i][j] = MAXX;
            if(i==j)
                mgraph->Edge[i][j] = 0;
        }
    }
    for(i=0;i<mgraph->edgenum;i++){
        fscanf(fin,"%d %d %d\n",&l,&r,&info);
        
        //printf("%d,%d\n",l,r);
        // 编号从0开始
        mgraph->Edge[l][r] = info;
        mgraph->Edge[r][l] = info;
    }
    return mgraph;
}





void print(ALGraph * g){
    int i =0;
    for(i=0;i<g->vexnum;i++){
        printf("%4d",g->vertices[i].data);
    }
}

void printM(MGraph * mgraph){
    int i,j;

    printf(" V |");
    for(i=0;i<mgraph->vexnum;i++){
        printf(" v%d  |",i);
    }
    printf("\n");
    for(i=0;i<mgraph->vexnum;i++){
        printf("v%d |",i);
        for(j=0;j<mgraph->vexnum;j++){
            printf("%5d|",mgraph->Edge[i][j]);
        }
        printf("\n----");
        for(j=0;j<mgraph->vexnum;j++){
            printf("------");
        }
        printf("\n");
    }
}

void testAlgraph(){
    fin = fopen("g_input.txt","r");
    ALGraph * algraph = (ALGraph*)malloc(sizeof(ALGraph)); 
    algraph = create_graph();
    printAlg(algraph);
    void BFSTraverse(ALGraph * a,int v);
    void bfstraverse(ALGraph * a);
    
    BFSTraverse(algraph,2);
    printf("\n----------bfs-------------\n");
    bfstraverse(algraph);
    printf("\n");
    void dfs_traverse(ALGraph * g);
    printf("\n---> dfs\n");
    dfs_traverse(algraph);
    void BFS_MIN_Distance(ALGraph * a,int v);
//    BFS_MIN_Distance(algraph,2);
//    printf("test\n");
//    printf("0 first is :%d\n",algraph->vertices[algraph->vertices[0].first->adjvex].data);
//    printf("%d",algraph->vertices[algraph->vertices[0].first->next->adjvex].data); 
//    printf("\n------\n"); 
   
}
void testMgraph(){
    MGraph * m = create();
    printM(m);
    void prim(MGraph * m,int p);
    prim(m,0);
}

typedef struct{
    VNode  v;
    int adjvex;
}Queue1;


// 广度优先
void BFSTraverse(ALGraph * algraph,int v)
{
    if(algraph == NULL || v>algraph->vexnum-1){
        return;
    }
    printf("form %d search\n",v);
    int i=0;
    int visited[MAXNUM];
    for(i=0;i<algraph->vexnum;i++){
        visited[i] = NOT_VISITED;
        printf("%5d",algraph->vertices[i].data);
    }
    printf("\n");
    //int adj = 0;
    Queue1 queue[MAXNUM];
    int front=-1,rear=-1;
    ++rear;
    queue[rear].v= algraph->vertices[v];
    queue[rear].adjvex = v;
    ArcNode * temp = NULL;
   
    while(front!=rear){
        ++front;
        VNode p = queue[front].v;
        temp = p.first;
        if(visited[queue[front].adjvex]==NOT_VISITED){
            printf("visit ---> %d\n",p.data);
            visited[queue[front].adjvex] = VISITED;
            while(temp != NULL){
                ++rear;
                queue[rear].v = algraph->vertices[temp->adjvex];
                queue[rear].adjvex = temp->adjvex;
                
                temp = temp->next;
            }
        }
    }   
}


void visit(ALGraph * algraph,int v){
    printf("visit ------> %d\n",algraph->vertices[v].data);
}
int visited[MAXNUM];
Q * q;

void initVisited(int n){
    int i=0;
    for(i=0;i<n;i++){
        visited[i] = 0;
    }
}

//  蔡写法 v 为编号
void bfs(ALGraph * algraph,int v){
    visit(algraph,v);
    visited[v] = VISITED;
    Q *_q = (Q*)malloc(sizeof(Q));
    init(&_q);
    EnQueue(&_q,v);
    while(isEmpty(_q)!=0){
        v = DeQueue(&_q);
        ArcNode * p = algraph->vertices[v].first;
//        printf("<------- v=%d,%d\n",v,p->adjvex);
        while(p!=NULL){
            if(!visited[p->adjvex]){
   //             printf("adj--->%d\n",p->adjvex);

                visit(algraph,p->adjvex);
               // if( vj == p->adjvex) 可用于判断是否存在路径
                visited[p->adjvex] = VISITED;
                EnQueue(&_q,p->adjvex);
            }
            p = p->next;
        }
    }
}

void bfstraverse(ALGraph * algraph){
    int i=0;
    q = (Q*)malloc(sizeof(Q));
    init(&q);
    for(i=0;i<algraph->vexnum;i++){
        visited[i] = NOT_VISITED;
    }
      //   有向图可能从某一 个顶点不能遍历完整个图
      //   所以for
//    for(i=0;i<algraph->vexnum;i++){

//        if(!visited[i]){
            bfs(algraph,2);
   //    }
    //}
    
}


void dfs(ALGraph * algraph,int v){
    visit(algraph,v);
    visited[v] = VISITED;
    ArcNode * f = algraph->vertices[v].first;
    while(f!=NULL){
        if(visited[f->adjvex]!=VISITED){
            dfs(algraph,f->adjvex);
          //  f = f->next;
        }
        f = f->next;
    }
}

typedef struct Stack_Node{
    int adjnum;
    ArcNode * next_arc;
}DFS_non_node;

typedef struct Stack{
    int data[MAXNUM];
    int top;
}DFS_Stack;

// 深度优先非递归写法
// 由于使用了栈 所以导致 由右边开始遍历，但是 任然是深度
void dfs_non(ALGraph * algraph,int v){
    if(algraph==NULL){
        return;
    }
    initVisited(algraph->vexnum);
    DFS_Stack * stack = (DFS_Stack*)malloc(sizeof(DFS_Stack));
    stack->top = -1;
    stack->data[++(stack->top)] = v;
    visited[v] = VISITED;
    //visit(algraph,v);
    //ArcNode * p = algraph->vertices[v].first;
    while(stack->top!=-1){
        int k = stack->data[stack->top--];
        visit(algraph,k);
        ArcNode * p = algraph->vertices[k].first;
        while(p!=NULL){
            if(visited[p->adjvex]==NOT_VISITED){
                stack->data[++(stack->top)] = p->adjvex;
                visited[p->adjvex] = VISITED; // 以免 再次 入栈
            }
            p = p->next;
        }
    }
}

void  getDegree(ALGraph * algraph,int degree[]){
    int i;
    ArcNode * p;
    for(i=0;i<algraph->vexnum;i++){
         p = algraph->vertices[i].first;
         while(p!=NULL){
            degree[p->adjvex] = degree[p->adjvex] + 1;
            p = p->next;
         }
    }
}

void dfs_traverse(ALGraph * algraph){
    int i=0;
    for(i=0;i<algraph->vexnum;i++){
        visited[i] = NOT_VISITED;
    }
    printf("-------- 递归深度优先-----\n");
    dfs(algraph,0);
    printf("\n------非递归 深度------\n");
    dfs_non(algraph,0);
}




void testQ(){
    Q *queue = (Q*)malloc(sizeof(Q));
    init(&queue);
    EnQueue(&queue,100);
 EnQueue(&queue,12);
    EnQueue(&queue,13);
//    EnQueue(&queue,14);
    int a =  DeQueue(&queue);   
    printf("dequeue : %d,%d\n",a,queue->data[0]);
    printf("%d% d\n",queue->front,queue->rear);
}

// bfs单源最短路径
void BFS_MIN_Distance(ALGraph * algraph,int u){
    int di[MAXNUM];
    int i=0;
    Q *queue = (Q*)malloc(sizeof(Q));
    init(&queue);
    for(i=0;i<algraph->vexnum;i++){
        di[i] = -1;
        visited[i] = NOT_VISITED;
    }
    visited[u] = VISITED;
    di[u] = 0;
    EnQueue(&queue,u);
    while(isEmpty(queue)!=0){
        u = DeQueue(&queue);
        ArcNode * p = algraph->vertices[u].first;
        while(p!=NULL){
            if(!visited[p->adjvex]){
                visited[p->adjvex] = VISITED;
                di[p->adjvex] = di[u] + 1;
                EnQueue(&queue,p->adjvex);
            
            }
            p = p->next;
        }
    }
    for(i=0;i<algraph->vexnum;i++){
        printf("%3d",di[i]);
    }
    printf("\n");
}


void printPath(int path[],int size){
    int i=0;
    for(i=0;i<=size;i++){
        printf("--->%d",path[i]);
    }
    printf("\n");
}
void FindPath(ALGraph * algraph,int u,int v,int path[],int d){
    int w;
    ArcNode * p;
    d++;
    path[d] = u;
    visited[u] = VISITED;
    if(u==v){
        printf("finded :%d,%d ",u,v);
        printPath(path,d);
        visited[v] = NOT_VISITED;
        return;
    }
    p = algraph->vertices[u].first;
    while(p!=NULL){
        w = p->adjvex;
        if(visited[w] == NOT_VISITED){
            FindPath(algraph,w,v,path,d);
        }
        p = p->next;
    }
    visited[u] = 0;
}

void testFindPath(){

    fin = fopen("g_input.txt","r");
    int path[MAXNUM] = {-1};
    ALGraph * algraph = (ALGraph *)malloc(sizeof(ALGraph));
    algraph = create_graph();
    printAlg(algraph);
    initVisited(algraph->vexnum); 
    BFSTraverse(algraph,0);
    printf("---------------find simple path -----------\n");
    initVisited(algraph->vexnum);
    FindPath(algraph,0,3,path,-1);
}
// 创建   代 权 的 图
ALGraph * testCreateByArc(){

    fin = fopen("arc_input.txt","r");
 //   int path[MAXNUM] = {-1};
    ALGraph * algraph = (ALGraph *)malloc(sizeof(ALGraph));
    //algraph = createAlgByArc();
    algraph = createDAG();
    printAlg(algraph);
    dfs_traverse(algraph);
    int degree[10] = {0,0,0,0,0,0,0,0,0,0};
    
    getDegree(algraph,degree);
    int i;
    for(i=0;i<algraph->vexnum;i++){
        printf("%5d",degree[i]);
    }
    printf("\n");
    return algraph;
}

// param : MGraph
void prim(MGraph * mgraph,int start){
    printf("最小生成树算法\n");
    int cost[MAXNUM][MAXNUM];
    int i,j,k,n,u;
    int min;
    int low[MAXNUM];
    int close_set[MAXNUM];
    int vexnum  = mgraph->vexnum;
    for(i=0;i<vexnum;i++){
        for(j=0;j<vexnum;j++){
            cost[i][j] = mgraph->Edge[i][j];
        }
    }
    // 初始化顶点的邻近的 边的代价 以及将其是顶点 并入 集合
    for(i=0;i<vexnum;i++){
        low[i] = cost[start][i];
        close_set[i] = start;
    }
    // 需要循环 vexnum-1 
    for(i=0;i<vexnum-1;i++){
        min = MAXX;
        for(j=0;j<vexnum;j++){
            if(low[j]!=0 && low[j] < min){
                min = low[j];
                k = j; //save the current close
            }
        }
//bin        printf("select min :%d,k=%d\n",min,k);
        printf("{%d<-->%d\tinfo:%d}\n",close_set[k],k,cost[close_set[k]][k]);
        low[k] = 0;
//        printf("low :");
//        for(j=0;j<vexnum;j++){
//            printf("%d  ",low[j]);
//        }
//        printf("\nclose_set:");
//        for(j=0;j<vexnum;j++){
//            printf("%d  ",close_set[j]);
//        }
        printf("\n");
        for(j=0;j<vexnum;j++){
            if(cost[k][i]!=0 && cost[k][j]<low[j]){
                low[j] = cost[k][j];
                close_set[j] = k; //
            }
        }
        //low[k] = 0;
/*        printf("调整新的权值\nlow :");
        for(j=0;j<vexnum;j++){
            printf("%d  ",low[j]);
        }
        printf("\nclose_set:");
        for(j=0;j<vexnum;j++){
            printf("%d  ",close_set[j]);
        }
        printf("\n");
*/
    }
}

void Dijkstra(){

}

void Kruskal(){
}

void floyd(MGraph * mg,int n){
 // nt cost[MAXNUM][MAXNUM] = mg->Edge;
    printf("最短路径算法");
}
void push(DFS_Stack * s,int data){
    s->data[++(s->top)] = data;
}
int pop(DFS_Stack * s){
    return s->data[(s->top)--];
}
// algraph : 邻接表
// 图的拓扑排序
int ToplogicalSort(ALGraph * algraph){
    DFS_Stack * s = (DFS_Stack*)malloc(sizeof(DFS_Stack));
    s->top = -1;
    int degree[MAXNUM] = {0};
    getDegree(algraph,degree);
    int i=0;
    for(i=0;i<algraph->vexnum;i++){
        if(degree[i]==0)
            push(s,i);
    }
    int element;
    int count = 0;
    ArcNode * p;
    while(s->top != -1){
        element = pop(s);
        count++;
        printf("index:%d data:%d\n ",element,algraph->vertices[element].data);
        p = algraph->vertices[element].first;
        while(p!=NULL){
            int v = p->adjvex;
            if(!(--degree[v]))
                push(s,v);
            p = p->next;
        }
    }
    if(count < algraph->vexnum)
        return 0;
    else 
        return 1;
}// 如果一个顶点有多个直接后继，那么排序的结果不唯一

void a(int b[]){
    b[0] = 1;
    b[1] = 2;
}

int main()
{
    
   // ALGraph * algraph = testCreateByArc();
  //  printf("--->toplfo sort :%d\n",ToplogicalSort(algraph));
// testFindPath();
//bin    testQ();
    testMgraph();
//   testAlgraph();
    return 0;
}

