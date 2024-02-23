#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct persona {
    int numero_lista;
    string nombre;
    string apellido;
    string email;
    string genero;
    int edad;
};

int main() {
    ifstream archivo("personas.csv", ios::in);
    string linea;
    persona persona_mayor_masculino, persona_mayor_femenino, persona_mayor_esteban;
    int proporcion_masculino = 0, proporcion_femenino = 0, proporcion_esteban = 0;
    int total_masculino = 0, total_femenino = 0, total_esteban = 0;
    float promedio_masculino = 0, promedio_femenino = 0, promedio_esteban = 0;

    persona_mayor_masculino.edad = -1;
    persona_mayor_femenino.edad = -1;
    persona_mayor_esteban.edad = -1;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            persona p; 
            string campo;
            size_t pos = 0;

            // Lista
            pos = linea.find(',');
            p.numero_lista = atoi(linea.substr(0, pos).c_str());
            linea.erase(0, pos + 1);

            // Nombre
            pos = linea.find(',');
            p.nombre = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            // Apellido
            pos = linea.find(',');
            p.apellido = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            // Email
            pos = linea.find(',');
            p.email = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            // Género
            pos = linea.find(',');
            p.genero = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            // Edad
            p.edad = atoi(linea.c_str());

            if (p.genero == "Male" && p.edad > persona_mayor_masculino.edad) {
                persona_mayor_masculino = p;
            }
            else if (p.genero == "Female" && p.edad > persona_mayor_femenino.edad) {
                persona_mayor_femenino = p;
            }
            else if (p.genero != "Male" && p.genero != "Female" && p.edad > persona_mayor_esteban.edad) {
                persona_mayor_esteban = p;
            }

            // Contar el número total de cada género
            if (p.genero == "Male") {
                total_masculino++;
            } else if (p.genero == "Female") {
                total_femenino++;
            } else {
                total_esteban++;
            }

            // Sumar edades para el cálculo del promedio
            if (p.genero == "Male") {
                promedio_masculino += p.edad;
            } else if (p.genero == "Female") {
                promedio_femenino += p.edad;
            } else {
                promedio_esteban += p.edad;
            }
        }
        archivo.close();

        // Calcular promedio de edades
        promedio_masculino /= total_masculino;
        promedio_femenino /= total_femenino;
        promedio_esteban /= total_esteban;
    } else {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    int eleccion;

    cout << "¿Que desea hacer?" << endl
         << "1. Ver la persona de mayor edad de cada genero." << endl
         << "2. Sacar la proporcion de cada genero." << endl
         << "3. Ver el promedio de edad." << endl
         << "4. Agregar datos." << endl
         << "5. Eliminar datos." << endl
         << "6. Buscar un registro." << endl
         << "7. Modificar datos de un registro." << endl;
    cin >> eleccion;

    switch (eleccion) {
        case 1: // Persona de mayor edad de cada género
            cout << "Genero: masculino, Nombre: " << persona_mayor_masculino.nombre << ", Apellido: " << persona_mayor_masculino.apellido << ", Edad: " << persona_mayor_masculino.edad << "\n";
            cout << "Genero: femenino, Nombre: " << persona_mayor_femenino.nombre << ", Apellido: " << persona_mayor_femenino.apellido << ", Edad: " << persona_mayor_femenino.edad << "\n";
            cout << "Genero: otros, Nombre: " << persona_mayor_esteban.nombre << ", Apellido: " << persona_mayor_esteban.apellido << ", Edad: " << persona_mayor_esteban.edad << "\n";
            break;

        case 2:
            cout << "La proporcion de genero masculino es: " << (float)total_masculino / (total_masculino + total_femenino + total_esteban) << endl;
            cout << "La proporcion de genero femenino es: " << (float)total_femenino / (total_masculino + total_femenino + total_esteban) << endl;
            cout << "La proporcion de genero variado es : " << (float)total_esteban / (total_masculino + total_femenino + total_esteban) << endl;
            break;

        case 3:
            cout << "El promedio de edad para el genero masculino es: " << promedio_masculino << endl;
            cout << "El promedio de edad para el genero femenino es: " << promedio_femenino << endl;
            cout << "El promedio de edad para el genero variado es : " << promedio_esteban << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
            break;
    }

    return 0;
}


