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

void agregarDatos();
void eliminarDatos();
void buscarRegistro();
void modificarRegistro();

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

    cout << "¿Qué desea hacer?" << endl
         << "1. Ver la persona de mayor edad de cada género." << endl
         << "2. Sacar la proporción de cada género." << endl
         << "3. Ver el promedio de edad." << endl
         << "4. Agregar datos." << endl
         << "5. Eliminar datos." << endl
         << "6. Buscar un registro." << endl
         << "7. Modificar datos de un registro." << endl;
    cin >> eleccion;

    switch (eleccion) {
        case 1: // Persona de mayor edad de cada género
            cout << "Persona de mayor edad masculino: " << persona_mayor_masculino.nombre << " " << persona_mayor_masculino.apellido << ", Edad: " << persona_mayor_masculino.edad << endl;
            cout << "Persona de mayor edad femenino: " << persona_mayor_femenino.nombre << " " << persona_mayor_femenino.apellido << ", Edad: " << persona_mayor_femenino.edad << endl;
            cout << "Persona de mayor edad esteban: " << persona_mayor_esteban.nombre << " " << persona_mayor_esteban.apellido << ", Edad: " << persona_mayor_esteban.edad << endl;
            break;

        case 2: // Proporción de cada género
            cout << "Proporción de género masculino: " << (float)total_masculino / (total_masculino + total_femenino + total_esteban) << endl;
            cout << "Proporción de género femenino: " << (float)total_femenino / (total_masculino + total_femenino + total_esteban) << endl;
            cout << "Proporción de género esteban: " << (float)total_esteban / (total_masculino + total_femenino + total_esteban) << endl;
            break;

        case 3: // Promedio de edad
            cout << "Promedio de edad masculino: " << promedio_masculino << endl;
            cout << "Promedio de edad femenino: " << promedio_femenino << endl;
            cout << "Promedio de edad esteban: " << promedio_esteban << endl;
            break;

        case 4: // Agregar datos
            {
                persona nueva_persona;
                cout << "Ingrese el número de lista: ";
                cin >> nueva_persona.numero_lista;
                cout << "Ingrese el nombre: ";
                cin >> nueva_persona.nombre;
                cout << "Ingrese el apellido: ";
                cin >> nueva_persona.apellido;
                cout << "Ingrese el email: ";
                cin >> nueva_persona.email;
                cout << "Ingrese el género (Male/Female/Otro): ";
                cin >> nueva_persona.genero;
                cout << "Ingrese la edad: ";
                cin >> nueva_persona.edad;

                ofstream archivo_append("personas.csv", ios::app);
                if (archivo_append.is_open()) {
                    archivo_append << nueva_persona.numero_lista << "," << nueva_persona.nombre << "," << nueva_persona.apellido << "," << nueva_persona.email << "," << nueva_persona.genero << "," << nueva_persona.edad << "\n";
                    archivo_append.close();
                    cout << "Datos agregados correctamente." << endl;
                } else {
                    cout << "Error al abrir el archivo." << endl;
                }
            }
            break;

        case 5: // Eliminar datos
            eliminarDatos();
            break;

        case 6: // Buscar un registro
            buscarRegistro();
            break;

        case 7: // Modificar datos de un registro
            modificarRegistro();
            break;

        default:
            cout << "Opción no válida." << endl;
            break;
    }

    return 0;
}

void eliminarDatos() {
    int numero_lista;
    cout << "Ingrese el número de lista de la persona que desea eliminar: ";
    cin >> numero_lista;

    ifstream archivo_lectura("personas.csv", ios::in);
    ofstream archivo_temporal("temp.csv", ios::out);
    string linea;

    while (getline(archivo_lectura, linea)) {
        int lista_actual = atoi(linea.substr(0, linea.find(',')).c_str());
        if (lista_actual != numero_lista) {
            archivo_temporal << linea << endl;
        }
    }

    archivo_lectura.close();
    archivo_temporal.close();

    remove("personas.csv");
    rename("temp.csv", "personas.csv");

    cout << "Datos eliminados correctamente." << endl;
}

void buscarRegistro() {
    string criterio_busqueda;
    cout << "Ingrese el criterio de búsqueda (nombre, apellido, email): ";
    cin >> criterio_busqueda;

    ifstream archivo_lectura("personas.csv", ios::in);
    string linea;

    cout << "Resultados de la búsqueda:" << endl;
    while (getline(archivo_lectura, linea)) {
        size_t found = linea.find(criterio_busqueda);
        if (found != string::npos) {
            cout << linea << endl;
        }
    }

    archivo_lectura.close();
}

void modificarRegistro() {
    int numero_lista;
    cout << "Ingrese el número de lista de la persona cuyos datos desea modificar: ";
    cin >> numero_lista;

    ifstream archivo_lectura("personas.csv", ios::in);
    ofstream archivo_temporal("temp.csv", ios::out);
    string linea;

    while (getline(archivo_lectura, linea)) {
        int lista_actual = atoi(linea.substr(0, linea.find(',')).c_str());
        if (lista_actual == numero_lista) {
            // Modificar datos
            cout << "Ingrese los nuevos datos:" << endl;
            persona p;
            cout << "Número de lista: ";
            cin >> p.numero_lista;
            cout << "Nombre: ";
            cin >> p.nombre;
            cout << "Apellido: ";
            cin >> p.apellido;
            cout << "Email: ";
            cin >> p.email;
            cout << "Género (Male/Female/Otro): ";
            cin >> p.genero;
            cout << "Edad: ";
            cin >> p.edad;

            // Escribir los datos modificados en el archivo temporal
            archivo_temporal << p.numero_lista << "," << p.nombre << "," << p.apellido << "," << p.email << "," << p.genero << "," << p.edad << endl;
        } else {
            archivo_temporal << linea << endl;
        }
    }

    archivo_lectura.close();
    archivo_temporal.close();

    remove("personas.csv");
    rename("temp.csv", "personas.csv");

    cout << "Datos modificados correctamente." << endl;
}

