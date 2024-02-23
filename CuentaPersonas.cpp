#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct persona{
    
    int numero_lista;
    string nombre;
    string apellido;
    string email;
    string genero;
    int edad;
};

int main(){
    int eleccion; 
    ifstream archivo("personas.csv", ios::in);
    string linea;
    persona persona_mayor;
    persona_mayor.edad = -1;
    

    if(archivo.is_open()){
        while(getline(archivo, linea)){
            persona p; 
            string campo;
            size_t pos = 0;

            //lista
            pos= linea.find(',');
            p.numero_lista = atoi(linea.substr(0, pos).c_str());
            linea.erase(0, pos +1);

            //nombre
            pos= linea.find(',');
            p.nombre = linea.substr(0, pos);
            linea.erase(0, pos +1);

            //apellido
            pos= linea.find(',');
            p.apellido = linea.substr(0, pos);
            linea.erase(0, pos +1);

            //email
            pos= linea.find(',');
            p.email = linea.substr(0, pos);
            linea.erase(0, pos +1);

            //genero
            pos= linea.find(',');
            p.genero = linea.substr(0, pos);
            linea.erase(0, pos +1);

            //edad
            pos= linea.find(',');
            p.edad = atoi(linea.substr(0, pos).c_str());
            linea.erase(0, pos +1);

            if(p.edad > persona_mayor.edad){
                persona_mayor= p;
            }
        }

    }
    else{
        cout<<"Error al abrir el archivo. "<<endl;
    }

    cout<<"Que desea hacer? "<<"\n"
    <<"1. ver la persona de mayor edad de cada genero. "<<"\n"
    <<"2. sacar la proporcion de cada genero. "<<"\n"
    <<"3. Ver el promedio de edad. "<<"\n"
    <<"4. Agregar datos. "<<"\n"
    <<"5. Eliminar datos. "<<"\n"
    <<"6. Buscar un registro."<<"\n"
    <<"7. Modificar datos de un registro. "<<endl;
    cin>>eleccion;

    switch(eleccion){

        case 1: //Persona de mayor edad de cada genero.

           if (persona_mayor.edad != -1) {
        cout << "Nombres: " << persona_mayor.nombre << " " << persona_mayor.apellido << "\n";
        cout << "Edad: " << persona_mayor.edad << "\n";
    } else {
        cout << "No se encontraron personas en el archivo.\n";


        break; 




    default:
        cout<<"opcion no valida."<<endl;
    break;    
    } 


    return 0;

    }
}
