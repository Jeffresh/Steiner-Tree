#include "prim.hpp"
#include <chrono>


int main()
{


    int** matrix;
    int n = 25; // nodos totales, mandatory and optionals
    int w_global = INF, w_local =INF;
    std::set<Edge> S_minimo;
    std::vector<int> nodos_minimo;

    std::set<Edge> S_minimo_G;
    std::vector<int> nodos_minimo_G;


    matrix = new int* [n]; 
    for(int i = 0; i < n; ++i) 
        matrix[i] = new int[n];
    
    genera_matrix(matrix,n);


 
        for(int j = 1; j <= 20; j++)
        {

            std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();


            w_local=permutations(20,j,matrix,S_minimo,nodos_minimo);

            if(w_global > w_local)
            {
                w_global = w_local;
                S_minimo_G = S_minimo;
                nodos_minimo_G = nodos_minimo;

            }



            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();



            std::cout<<"K = "<<j<<" Tarda: "<<duration<<" microsegundos"<<std::endl;
                

            
        }

        std::cout<<"Coste mínimo Global:"<<w_global<<"\n"<<std::endl;
        imprimir_graf(S_minimo_G,nodos_minimo_G);

    

    


}