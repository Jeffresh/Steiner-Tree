#include <set>
#include <iostream>
#include <utility>
#include <limits>
#include <algorithm>
#include<cmath>
#include<vector>

typedef int Vertex;
typedef std::pair<int,int> Edge;
static const int INF = std::numeric_limits<int>::max();

Vertex** P;
std::set<Vertex> C;
std::set<Edge> S;

void genera_matrix(int** matrix,int n);
void genera_submatrix(int** matrix, int** submatrix,std::vector<int> nodos);
void genera_matrix_ejemplo(int** matrix,int n);

void permutations(int nodes,int k);
void imprimir(int** matrix, int n);
void imprimir_graf(std::set<Edge> S, std::vector<int> nodos);


int coste(std::set<Edge> S,int** subm);



Vertex select(const std::set<Vertex>&, const int*);
std::set<Edge> prim(Vertex**, size_t);



//funcion que genera las permutaciones y que encapsula la lógica del programa
// aparte de generar las permutaciones, con ellas genera la submatriz, con esas permutaciones, que son los nodos opcionales
// con ella alimenta la función de Prim y devuelve el coste local a ese grupo de permutaciones, aparte, devuelve por referencia
// el conjunto de vertices dado por el resultado de Prim y los nodos que los forman.


int permutations(int nodes,int k, int** matrix,std::set<Edge>& S_minimo, std::vector<int>& nodos_minimo)
{

    int w = INF;
    int myints[nodes];
    bool mask[nodes];

   

    std::fill(mask,mask+nodes,false);

    for(int i = nodes-1; i> nodes-1-k; i--)
      mask[i] = true;



    for(int i = 0; i < nodes; i++)
        myints[i]=i+1;

  std::sort (myints,myints+k);


  
  do 
  {
      std::vector<int> nodos ={1,2,3,4,5};

      for(int i = 0; i < nodes; i++)
      {
        if(mask[i])
        {
            nodos.push_back(myints[i]+5);
        }
      }
    std::sort(nodos.begin(),nodos.end());

   // for(auto v:nodos)
     //   std::cout<<v<<" ";

    int** submatrix;
    
    submatrix = new int* [nodos.size()]; 
    for(int i = 0; i < nodos.size(); ++i) 
       submatrix[i] = new int[nodos.size()];

    genera_submatrix(matrix,submatrix,nodos);

    std::set<Edge> S = prim(submatrix,nodos.size());

    int costelocal = coste(S,submatrix);

    if(w > costelocal )
    {
        w = costelocal;
        S_minimo =S;
        nodos_minimo =nodos;
    }



    //std::cout << '\n';
  } while ( std::next_permutation(mask,mask+nodes) );






  return w;




}

// algoritmo de prim que devuelve las aristas que forman el arbol de expansión mínimo, dado una matriz de costes.

std::set<Edge> prim(Vertex** p, size_t num_vertices)
{
    Vertex c[num_vertices] ;
    int d[num_vertices] ; 

    std::set<Vertex> C = std::set<Vertex>();

    for(Vertex j = 1; j < num_vertices; j++)
    {
        C.insert(j);
        c[j] = 0;
        d[j] = p[0][j];
        

    } 

    std::set<Edge> S = std::set<Edge>();


    while(!C.empty())
    {
        Vertex k =0;
        k = select(C,d);
        

        C.erase(k);
        S.insert(std::make_pair(c[k],k));
        for(auto j :C)
        {
            if(p[k][j]<d[j])
                c[j] = k;
                d[j] = p[k][j];
        }
    }


    return S;
}



//funcion que genera la sub matrix.
void genera_submatrix(int** matrix, int** submatrix,std::vector<int> nodos)
{


    int x =0 , y =0;

    for(auto i :nodos)
    {
        for(auto j:nodos)
        {
            submatrix[x][y] = matrix[i-1][j-1]; 
            y++;
        }
        y=0;
        x++;

    }
}

//end sub_matrix


// funcion que genera la matrix inicial

void genera_matrix(int** matrix,int n)
{

    for(int i = 0; i < n; ++i) 
    {
           for(int j = 0; j < n; ++j)
           {
                if(j==0 && i!=0)
                matrix[i][j]=i+1;
            
               else if(i ==j)
                    matrix[i][j] = INF;
                else
                    matrix[i][j]=j+1;
              
           }
    }



}

//end matrix,


//funcion auxiliar que genera una matrix de ejemplo, con la cual es facil comprobar la correción de nuestros algoritmos.

void genera_matrix_ejemplo(int** matrix,int n)
{

    for(int i = 0; i < n; ++i) 
    {
           for(int j = 0; j < n; ++j)
           {
                    matrix[i][j] = INF;

                
             
              
           }
    }


    matrix[0][1] = 1;
    
    matrix[1][0] = 1;
    matrix[1][2] = 8;
    matrix[1][3] = 8;
    matrix[1][4] = 8;

    matrix[2][1] = 8;
    matrix[2][3] = 7;



    matrix[3][1] = 8;
    matrix[3][2] = 7;
    matrix[3][4] = 6;
    matrix[3][5] = 9;


    matrix[4][1] = 8;
    matrix[4][3] = 6;
    matrix[4][5] = 9;

    matrix[5][3] = 9;
    matrix[5][4] = 9;
    matrix[5][6] = 4;

    matrix[6][5] = 4;


    



    



}







// end permutations

// funcion auxiliar que imprime una matrix por pantalla, dada una matrix.

void imprimir(int** matrix, int n)
{
    for(int i = 0; i < n; ++i) 
    {
        for(int j = 0; j < n; ++j)
        {
          std::cout<<"| "<<matrix[i][j]<<" | ";
        }

        std::cout<<std::endl;
    }

    std::cout<<std::endl;


}

//funcion auxiliar para imprimir un grafo, dado un conjunto de aristas, y los nodos que forman esas aristas.

void imprimir_graf(std::set<Edge> S, std::vector<int> nodos)
{


for(auto v: S)
   {
       std::cout<<"<"<<nodos[(v.first+1)-1]<<","<<nodos[(v.second+1)-1]<<">";
        std::cout<<std::endl;

   }

   


}

// función auxiliar obtiene el coste dado una matriz u un conjunto de aristas.

int coste(std::set<Edge> S,int** subm)
{
    int coste = 0;

     for(auto v: S)
   {
       coste+=subm[(v.first+1)-1][(v.second+1)-1];
   }

   return coste;

}



// función de selección de PRIM

Vertex select(const std::set<Vertex>& C, const int* d)
{
    int v = INF; // v equals to infinite
    Vertex k = 0;
     for(auto j: C)
        {
            

            if(d[j] < v)
            {
                v = d[j];
                k = j;
            }
        }


    return k;
}






