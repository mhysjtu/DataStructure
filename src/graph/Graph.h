// Adj Matrix and List
// Create & Build Graph
#include <stdio.h>
#include <stdlib.h>

typedef int Vertex;
typedef int WeightType;
#define MaxVertexNum 100
#define INFINITY 65535

typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

//---Adjacency Matrix
typedef struct MGNode *PtrToMGNode;
struct MGNode{
    int Nv, Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToMGNode MGraph;

MGraph CreateMGraph(int VertexNum){
    Vertex V, W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct MGNode));
    Graph->Ne = 0;
    Graph->Nv = VertexNum;

    for (V = 0; V < Graph->Nv; ++V)
        for(W = 0; W < Graph->Nv; ++W)
            Graph->G[V][W] = INFINITY;
    
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E){
    Graph->G[E->V1][E->V2] = E->Weight;
    //Graph->G[E->V2][E->V1] = E->Weight;//for unweighted graph
}

MGraph BuildMGraph(){
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv;

    printf("input the number of vertex:\t");
    scanf("%d", &Nv);
    Graph = CreateMGraph(Nv);
    printf("input the number of edge:\t");
    scanf("%d", &(Graph->Ne));
    if (Graph->Ne!=0){
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph->Ne; ++i){
            printf("input edge %d: v1 v2 weight:\t", i+1);
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
//---

//---Adjacency List
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;
    WeightType Weight;
    PtrToAdjVNode Next;
};

typedef struct VNode{
    PtrToAdjVNode FirstEdge;
}AdjList[MaxVertexNum];

typedef struct LGNode *PtrToLGNode;
struct LGNode{
    int Nv, Ne;
    AdjList G;
};
typedef PtrToLGNode LGraph;

LGraph CreateLGraph(int VertexNum){
    Vertex V;
    LGraph Graph;
    Graph = (LGraph)malloc(sizeof(struct LGNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (V = 0; V < Graph->Nv; ++V)
        LGraph->G[V].FirstEdge = NULL;
    
    return Graph; 
}

void InsertEdge(LGraph Graph, Edge E){
    PtrToAdjVNode NewNode;
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;

    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
}

LGraph BuildLGraph(){
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv;

    printf("input the number of vertex:\t");
    scanf("%d", &Nv);
    Graph = CreateLGraph(Nv);
    printf("input the number of edge:\t");
    scanf("%d", &(Graph->Ne));
    if (Graph->Ne!=0){
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph->Ne; ++i){
            printf("input edge %d: v1 v2 weight:\t", i+1);
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
//---