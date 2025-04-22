/*
8 11
1 2 3
1 3 1
2 4 1
2 7 5
3 4 2
3 6 5
4 5 4
4 6 2
5 7 2
5 8 1
6 8 3
*/
#include <string.h>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
#define MAX 10005 
#define Node pair< int , int > 
#define INF 1<<30                    
struct cmp 
{
    bool operator() ( const Node &a , const Node &b ) 
	{
        return a.second > b.second;
    }
};    
vector< Node > ady[ MAX ]; 
int distancia[ MAX ], previo[ MAX ], V;     
bool visitado[ MAX ];      
priority_queue< Node , vector<Node> , cmp > Q;     
void init();
void relajacion( int actual , int adyacente , int peso );
void print( int destino );
void dijkstra( int inicial );

int main()
{
	int E , origen, destino , peso , inicial,op;
	printf("Copiar el grafo conexo del primer comentario del programa \n");
    scanf("%d %d" , &V , &E );
    while( E-- )
	{
        scanf("%d %d %d" , &origen , &destino , &peso );
        ady[ origen ].push_back( Node( destino , peso ) );  
    }
	do
	{
		printf("MENU\n");
		printf("1. Calcular la distancia mas corta entre vertices \n");
		printf("2. Salir \n");
		printf("Opcion: ");
		scanf("%d",&op);
		switch(op)
		{
			case 1: 
				system("CLS");
				printf("Vertice inicial: ");
	            scanf("%d" , &inicial );
	            dijkstra( inicial );
				printf("\n");
				system("PAUSE");
				break;
			default:
				printf("Opcion no valida\n");
				system("pause");
				break;			
		}
		system("CLS");
	}while(op != 2);
    system("PAUSE");
    return 0;
}

void init()
{
    for( int i = 0 ; i <= V ; ++i )
	{	
        distancia[ i ] = INF;  
        visitado[ i ] = false; 
        previo[ i ] = -1;      
    }
}
void relajacion( int actual , int adyacente , int peso )
{  
    if( distancia[ actual ] + peso < distancia[ adyacente ] )
	{
        distancia[ adyacente ] = distancia[ actual ] + peso;  
        previo[ adyacente ] = actual;                         
        Q.push( Node( adyacente , distancia[ adyacente ] ) ); 
    }
}
void print( int destino )
{
    if( previo[ destino ] != -1 )    
        print( previo[ destino ] );  
    printf("%d-" , destino );        
}
void dijkstra( int inicial )
{
	int destino;
    init();
    Q.push( Node( inicial , 0 ) ); 
    distancia[ inicial ] = 0;      
    int actual , adyacente , peso;
    while( !Q.empty() )
	{                   
        actual = Q.top().first;            
        Q.pop();                          
        if( visitado[ actual ] ) continue; 
        visitado[ actual ] = true;         
        for( int i = 0 ; i < ady[ actual ].size() ; ++i )
		{ 
            adyacente = ady[ actual ][ i ].first;   
            peso = ady[ actual ][ i ].second;       
            if( !visitado[ adyacente ] )
                relajacion( actual , adyacente , peso ); 
        }
    }
    printf( "Distancias mas cortas iniciando en vertice %d\n" , inicial );
    for( int i = 1 ; i <= V ; ++i )
        printf("Vertice %d , distancia mas corta = %d\n" , i , distancia[ i ] );
    puts("\nCamino mas corto");
    printf("Vertice destino: ");
    scanf("%d" , &destino );
    print( destino );
    printf("\n");
}
