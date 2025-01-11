#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;



    void Busqueda(vector<vector<char>> &tabla, int *i, int* j){
   for(int I = 0; I < tabla.size(); I++){
       for(int J = 0; J < tabla[I].size(); J++){
           if(tabla[I][J] == '^'){
                *i = I;
                *j = J;
               return;
           }
       }
   }
}

int Movimiento(vector<vector<char>> &tabla, int i, int j, int movi = 0, int Dir = 0){  
    switch(Dir){
        
        case 0:
    if(tabla[i-1][j] == '#'){
        Dir ++;
        return Movimiento(tabla, i, j, movi, Dir);
       
    }else if(tabla[i-1][j] != '\0' ){
       if(tabla[i-1][j] != 'X'){
        movi++;
        tabla[i-1][j] = '^';
        }
        tabla[i][j] = 'X';
        
        
       return Movimiento(tabla, i-1, j, movi, Dir);
    }
    break;
    
    case 1:
    if(tabla[i][j+1] == '#'){
        Dir ++;
        return Movimiento(tabla, i, j, movi, Dir);
       
    }else if(tabla[i][j+1] != '\0' ){

        if(tabla[i][j+1] != 'X'){
        movi++;
        tabla[i][j+1] = '^';
        }
        tabla[i][j] = 'X';
       return Movimiento(tabla, i, j+1, movi, Dir);
    }
    break;
    
    case 2:
    if(tabla[i+1][j] == '#'){
        Dir ++;
       return Movimiento(tabla, i, j, movi, Dir);
       
    }else if(tabla[i+1][j] != '\0' ){

       
        if(tabla[i+1][j] != 'X'){
            movi++;
            tabla[i+1][j] = '^';
        } 
        tabla[i][j] = 'X';
        
       return Movimiento(tabla, i+1, j, movi, Dir);
    }
    break;
    

    case 3:

    if(tabla[i][j-1] == '#'){
        Dir = 0;
        return Movimiento(tabla, i, j, movi, Dir);
       
    }else if(tabla[i][j-1] != '\0' ){
      
        
        if(tabla[i][j-1] != 'X'){
            movi++;
            tabla[i][j-1] = '^';
        } 
        tabla[i][j] = 'X';
       
       return Movimiento(tabla, i, j-1, movi, Dir);
    }
    break;
    }
    
    return movi;
 }

int main() {
    ifstream file("input6.txt");
    string linea;
    vector<vector<char>> tabla;
    int Result = 0;
    int i = 0;
    int j = 0;

    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    while (getline(file, linea)) {
        istringstream iss(linea);
        vector<char> c;
        char a;
        while(iss >> a){
            c.push_back(a);
        }
        tabla.push_back(c);
    }
    file.close();
    /*for(int i = 0; i < tabla.size(); i++){
        for(const auto &c : tabla[i]){
            cout << c;
        }
            cout << endl;
        }*/

    Busqueda(tabla, &i, &j);
    cout << "Posicion: " << i << " " << j << endl;
    cout << "posicion: " << tabla[i][j] << endl;

    int movi = Movimiento(tabla, i, j);
    tabla[i][j] = '0';
    
    for(int i = 0; i < tabla.size(); i++){
        for(const auto &c : tabla[i]){
            cout << c;
        }
            cout << endl;
        }
        movi++;
    cout << "Movimientos: " << movi << endl;
    return 0;
}