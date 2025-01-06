#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>




using namespace std;

struct Node { //estructura de nodo
    long long data;
    Node* left = nullptr;
    Node* right = nullptr;
};
// funcion para determinar metodo a aplicar
void Quard(Node* root, int Rep){
    if(Rep == 0){
        return;
    }
    string num = to_string(root->data); //transforma el numero en un string para facilitar la segunda condicion
    //cout << "Numero: " << num << endl;
    root->left = new Node();

    if(root->data == 0){ // si es cero lo transforma en uno
        root->left->data = 1;
        return Quard(root->left, Rep - 1);

    }else if(num.size() % 2 == 0){ //si el numero de digitos es par lo divide en dos
        int mid = num.size() / 2; // coge la mitad
        string a = num.substr(0, mid); // la primera mitad
        //cout << "Primera mitad: " << a << endl;
        root->left->data = stoi(a); // la primera mitad lo pone a la izquierda 
       
        string b = num.substr(mid, mid); // la segunda mitad
        //cout << "Segunda mitad: " << b << endl;
        root->right = new Node();
        root->right->data = stoi(b); // la segunda mitad lo pone a la derecha 
        return Quard(root->left, Rep - 1), Quard(root->right, Rep - 1);

        
    } else { //Y si no pasa nada multiplica el numero por 2024
        root->left->data = root->data * 2024;
        return Quard(root->left, Rep - 1);
    }
    
    return;
}

int Recorrido(Node* root, int *movi, vector<long long> *v){ //recorre el arbol hasta llegar al final, por cada final del arbol suma una roca
    if(root->left == nullptr && root->right == nullptr){
            (*movi)++;
            v->push_back(root->data);
            return *movi;
    }
    Recorrido(root->left, movi, v);
    if(root->right  != nullptr){
    Recorrido(root->right, movi, v);
    }
    return *movi;
}    

void Limpieza(Node* root){ //borra el arbol
    if(root == NULL){
        return;
    }
    Limpieza(root->left);
    Limpieza(root->right);
    delete root;
}



int main(){
    ifstream file ("input11.txt");
    string linea;
    vector<long long> v ;
    vector<long long> v2;
    int Rep = 25;
    int rock = 0;

    //v = {100, 20, 3, 0, 5423}; //vector de numeros
    if(!file.is_open()){
        cout << "Error al abrir el archivo" << endl;
    }
while (getline(file, linea)) {
    istringstream iss (linea);
    int a;
    while (iss >> a){
        v.push_back(a);
    }
    file.close();
}
 for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl; 


    for(int i = 0; i < v.size(); i++){ // por cada numero en el vector crea un nodo y lo manda a la funcion Quard
         Node* root = new Node();
         root->data = v[i];
            Quard(root, Rep);
            rock = Recorrido(root, &rock, &v2);
            Limpieza(root);
    }
    cout << "Numero de rocas: " << rock << endl;
    cout << "Rocas: ";
    /*for(int i = 0; i < v2.size(); i++){
        cout << v2[i] << " ";
    }
    cout << endl;*/

    return 0;
}
