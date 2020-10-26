#include "GraphAlgorithm.h"
#include <stack>

void printMGraph(MGraph G){
    for (int i = 0; i < G->Nv; ++i){
        for (int j = 0; j < G->Nv; ++j)
            printf("%d\t", G->G[i][j]);
        printf("\n");
    }
}

int main(int argc, char** argv){
    MGraph G;
    Vertex V;

    G = BuildMGraph();
    printMGraph(G);

    //DFS
    printf("-----DFS------");
    printf("\nDFS from vertex ? ");
    scanf("%d", &V);
    printf("DFS from %d:\n", V);
    DFS(G, V, Visit);
    //BFS
    printf("\n-----BFS------");
    printf("\nBFS from vertex ? ");
    scanf("%d", &V);
    printf("BFS from %d:\n", V);
    BFS(G, V, Visit);

    //Dijkstra
    printf("\n---Dijkstra---");
    printf("\nDijkstra from vertex ? ");
    scanf("%d", &V);
    int dist[G->Nv], path[G->Nv];
    if(Dijkstra(G, dist, path, V)){
        printf("result path: ");
        for (int i = 0; i < G->Nv; ++i)
            printf("%d ", path[i]);

        printf("\nDijkstra path from %d to vertex ? ",V);
        scanf("%d", &V);
        
        printf("Dijkstra path is:\n");
        std::stack<Vertex> S;
        do{
            S.push(V);
            V=path[V];
        }while (V!=-1);
        while (!S.empty()){
            printf(" %d", S.top());
            S.pop();
        }
        printf("\n");
    }

    Vertex V1,Vn;
    //Floyd
    printf("-----Floyd----\n");
    WeightType D[G->Nv][MaxVertexNum], P[G->Nv][MaxVertexNum];
    if (Floyd(G, D, P)){
        printf("result path for ");
        scanf("%d", &V1);
        for (int i = 0; i < G->Nv; ++i){
            for (int j = 0; j < G->Nv; ++j)
                printf("%d ", P[i][j]);
            printf("\n");
        }

        printf("\nFloyd path from %d to vertex ? ",V1);
        scanf("%d", &Vn);

        printf("Floyd path is:\n");
        std::stack<Vertex> S;
        do{
            S.push(Vn);
            Vn=P[V1][Vn];
        }while (Vn!=-1);
        while (!S.empty()){
            printf(" %d", S.top());
            S.pop();
        }
        printf("\n");
    }
    

    return 0;
}