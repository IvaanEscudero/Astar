#include "Maze.h"
#include <map>

#include <string>  
#include <iostream> 
#include <sstream>  

#define DEB true

#include "heuristic.h"
using namespace std;


bool AStar(lp &, Maze, int &);
list<position> ListaVecinos(position, Maze);
float Distancia(position, position);
bool PerteneceALista(lp, position);
bool WritePath(lp, string);


int main(int argc,char *argv[])
{
  int cont = 0;
 if (argc!=2)
 {
  cerr << "       " << argv[0] << " <input_file>\n";
  exit(1);
 }

 string inputname=string(argv[1]);
 Maze lab(inputname);

 if (DEB)
  lab.Print(cout);

 lp foundpath;
 foundpath.clear();

 bool result = AStar(foundpath, lab,cont);
 //cout << "cont: " << cont << endl;
 if (result==false)
 {
  cerr << "No path has been found for that maze. Writing the empty list.\n";
  foundpath.clear();
 }

 // Second argument is a string with the file name to write the solution
 if (DEB)
  WritePath(foundpath,"output.txt");

    
 if (DEB)
  lab.Print(cout,foundpath);

 return ( result ? 0 : 1 );
}
/*
* AStar
* Implementacion del algoritmo AStar
* foundpath es el camino final que se devuelve por referencia
* lab el laberinto que queremos resolver
* cont es un contador de los caminos que se han abierto y se devuelve por referencia
* Devuelve true si ha encontrado un camino y false si no
*/
bool AStar(lp & foundpath, Maze lab, int & cont)
{
    //Declaraciones
	lp open, closed, vecinos;
	map <position, float> gScore;
	float tentative_gScore = 0;
	map <position, float> fScore;
	map <position,position> camino;
	position aux, current, atras;
	float min = FLT_MAX;
	
	//Initial values
	for(unsigned i = 0; i < lab.GetNumRows(); i++){
		for(unsigned j = 0; j < lab.GetNumCols(); j++){
			aux.first= i;
			aux.second = j;
			gScore[aux] = 9999;
			fScore[aux] = 9999;
		}
	}
	
	//Inicializacion de los starts de scores
	gScore.at(lab.GetStart()) = 0;
	fScore.at(lab.GetStart())= h(lab.GetStart(),lab.GetGoals());
	
	//Inicializacion open, closed
	open.push_front(lab.GetStart()); //open <- {start}
	closed.clear(); // closed <- {}
	
	
	while(!open.empty()){
	    
	    //nodo en open con el menor fScore
		for(lp::iterator it = open.begin(); it != open.end(); it++){
			if(fScore.at((*it)) < min){
				current = (*it);
				if(fScore.at((*it)) != 0)
				    min = fScore.at((*it));
			}
			
		}
		min = FLT_MAX;
		
		//Si nuestro current es una meta acaba
		if (lab.IsGoal(current)){
		
		    atras = camino[current];
		    foundpath.push_front(current);
		    //Mientras el nodo atras no sea la casilla inicial, 
		    //ir desmontando el camino recorrido
		    while(atras != lab.GetStart()){
		    
		        foundpath.push_front(atras);
		        atras = camino[atras];
		    }
		    foundpath.push_front(lab.GetStart());
		   
			return true;	
		}
        
		open.remove(current);
		closed.push_back(current);
		vecinos = ListaVecinos(current, lab);
		
		//por cada vecino de current
		for(auto vec : vecinos){
		    // Si vec no pertenece a closed
		    if(!PerteneceALista(closed, vec)){
		    
		        tentative_gScore = gScore.at(current) + Distancia(current, vec);
		      
		        if(tentative_gScore < gScore.at(vec)){
		        
		            gScore.at(vec) = tentative_gScore;
		            fScore.at(vec) = gScore.at(vec) + h(vec, lab.GetGoals());
		            
		            if(!PerteneceALista(open, vec)){
		                open.push_back(vec);
		                camino[vec] = current;
		                cont++;
		            }
		        }
		    }
		}
	}
	//Ha recorrido todo el laberinto sin encontrar meta,por tanto,no tiene solucion
	return false;
}
/*
* ListaVecinos
* Para una posicion current calcula todos sus vecinos validos dentro del Maze lab
* Devuelve la lista de vecinos
*/
list<position> ListaVecinos(position current, Maze lab){
	list<position> vecinos;
	position aux;
    
    /*  Casillas contiguas
    *   x-1 y+1 | x y+1 | x+1 y+1
    *   x-1 y   | x  y  | x+1 y
    *   x-1 y-1 | x y-1 | x+1 y-1
    */  
    for(int i = (int)current.first - 1; i <= (int)current.first + 1; i++){
        for(int j = (int)current.second - 1; j <= (int)current.second + 1; j++){
            // Si i,j son numeros validos, estan dentro del tablero y NO son obstaculos
            // entonces posicion i,j es un vecino de current
            if((i >= 0 && j >= 0) && (i < (int)lab.GetNumRows() && j < (int)lab.GetNumCols())){
                aux.first = i;
                aux.second = j;
                
                if(!lab.IsObstacle(aux)){
                    vecinos.push_back(aux);
                }
            }    
        }
    }
   
    return vecinos;
}
/*
* Distancia
* Dada una posicion current calcula si nei es un vecino en su diagonal
* Devuelve raiz de 2 si es diagonal o 1 si no lo es  
*/
float Distancia(position current, position nei){
    // si |x1-x2|==1 y |y1-y2|==1 entonces son diagonales
    if ((abs((int)current.first - (int)nei.first) == 1) && (abs((int)current.second - (int)nei.second) == 1)){
        return sqrt(2);
    }
    else{
        return 1;
        }
}

/*
* PerteneceALista
* Busca si pos se encuentra dentro de la lista list
* Devuelve verdadero si ha sido encontrado o falso si no
*/
bool PerteneceALista(lp list, position pos){
    
    for(auto l : list){
        if((l.first == pos.first) &&(l.second == pos.second)){
            return true;        
        }
    }
   
    return false;
    
}
/*
* WritePath
* Escribe el camino foundpath pasado como parametro con el formato:  
* "[[R1,C1],...,[Rn,Cn]]" al fichero con el nombre pasado al outname
* Devuelve verdadero si ha podido abrir el archivo o falso si no
*/
bool WritePath(lp foundpath, string outname){
    
    ofstream outfile;
    string buffer;
    
    outfile.open(outname);
    
    if(outfile){
        buffer = "[";
        for(auto pos : foundpath){
            buffer += "[" + to_string(pos.first) + "," + to_string(pos.second) + "],";
        }
        buffer.pop_back();
        buffer += "]";
        
        outfile << buffer;
        
        return true;
    }
    else
        return false;
}
