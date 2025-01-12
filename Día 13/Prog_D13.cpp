        //Leer linea y separar letras de numeros en bloques de 3 tandas
        //Estructura con los datos ordenados
        //Calcular si se puede llegar al lugar
//calcular recorrido optimo
        //sumar numero de movimientos usados y 1 a los premios gandos

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#define MAXPRES 100
using namespace std;

struct coord{
    int x;
    int y;
};
class Maquina(){
    private:
        coord BotA;
        coord BotB;
        coord Prize;
        unordered_map<string, int> memoria;

        string generarClave(int presA, int presB) {
            return to_string(presA) + "," + to_string(presB);
    }
        
    public:
        Maquina(string line1, string line2, string line3){//separa datos de cada tanda
            //se guarda la cadena a leer
            std::string temp;
            std::istringstream ss1(line1), ss2(line2), ss3(line3);
            //separa datos de la cadena
            ss1 >> temp >> temp >> temp >> temp >> BotA.x; //Lee solo la X
            ss1.ignore(1); // Ignora la coma
            ss1 >> temp >> BotA.y;//Lee y

            ss2 >> temp >> temp >> temp >> temp >> BotB.x; //Lee solo la X
            ss2.ignore(1); // Ignora la coma
            ss2 >> temp >> BotB.y;//Lee y

            ss3 >> temp >> temp >> temp >> Prize.x; //Lee solo la X
            ss3.ignore(1); // Ignora la coma
            ss3 >> temp >> Prize.y;//Lee y
        }
        int posible(){
            int min_tokens=MAXPRES+1;
            for (int presA=0;presA<=MAXPRES;presA++){
                for (int presB=0;presB<=(MAXPRES-presA);presB++){
                    string clave = generarClave(presA, presB);
                    if (memoria.find(clave) != memoria.end()) {
                        int tokens = memoria[clave];
                        if (tokens < min_tokens) {
                            min_tokens = tokens;
                        }
                        continue; // No recalcular, pasar al siguiente
                    }
                    int x=(presA*BotA.x)+(presB*BotB.x);
                    int y=(presA*BotA.y)+(presB*BotB.y);
                    if(x==(Prize.x)&&(y==Prize.y)){
                        int tokens=presA+presB;
                        if(tokens<min_tokens){
                            tokens=min_tokens;
                        }
                        memoria[clave] = tokens;
                    }
                }
            }
            if(min_tokens>MAXPRES){
                return -1;
            }else{
                return min_tokens;
            }
        }
}

int main(){
    int vacio=0;
    int premios=0;
    int tokens=0;
    string line;
    ifstream file("input13.txt");//abrir archivo
    if (!file) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }
    //ejecutar hasta terminar
    while (std::getline(file, line)) {
        if (line.empty()) {
            vacio++;
            // Si encontramos dos líneas vacías seguidas, detenemos el bucle
            if (vacio >= 2) {
                break;
            }
            continue;
        }
        //Lee 3 lineas
        string line1 = line;
        string line2, line3;
        getline(file, line2);
        getline(file, line3);
        Maquina m(line1, line2, line3);

        //mira si hay premio y recorrido optimo
        int apto=m.posible();
        if (apto>=0){
            premios++;
            tokens += apto;
        }
        vacio=0;
    }
    file.close();
    cout<<"Premios ganados= "<<premio<<"\nTokens usados= "<<tokens;
    return 0;
}

