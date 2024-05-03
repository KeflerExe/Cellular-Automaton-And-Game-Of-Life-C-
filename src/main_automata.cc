/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: El juego de la vida
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 23/02/2024
/// Archivo: main_laberintos.cc
/// Contiene el main y las funciones llamadas desde el mismo.

#include "lattice.h"
#include "cell.h"

#include <iostream>
#include <limits>

// Función que comprueba que el número de parámetros de entrada es correcto y proporciona ayuda al usuario
void Usage(int argc, char *argv[]) {
  if (argc != 6 && argc != 7 && argc != 5) {
    std::cout << "--Autómata" << std::endl;
    std::cout << "Modo de uso: ./automata_main -size <M> <N> -border <b [v]> -init <file>" << std::endl << "Pruebe ./automata_main --help para más información" << std::endl;
    exit(EXIT_FAILURE);
  }  
  if (argv[1] == "--help") {
    std::string parametro_introducido = argv[1];
    if (parametro_introducido == "--help") {
      std::cout << "--Autómata" << std::endl;
      std::cout << "Modo de uso: ./automata_main -size <M> <N> -border <b [v]> -init <file>" << std::endl;
      std::cout << "-size <M> <N>: M son las filas de la matriz y N las columnas" << std::endl;
      std::cout << "-border <b [v]>: b indica el tipo de frontera según el valor sea open, periodic, reflective o noborder, mientras que v debe tomar valor 0 o 1 en caso de que la frontera sea abierta." << std::endl;
      std::cout << "-init <file>: file es el nombre del archivo que contiene la configuración inicial del autómata (este argumento es opcional y excluyente con -size)" << std::endl;
      exit(EXIT_SUCCESS);
    } 
  }
}

// Función principal
int main(int argc, char *argv[]) {
  Usage(argc, argv);
  std::string parametro_introducido = argv[1];
  if (parametro_introducido == "-size") {
    int filas = std::stoi(argv[2]);
    int columnas = std::stoi(argv[3]);
    std::string frontera = argv[5];
    int valor_frontera{0};
    if (frontera == "open") {
      valor_frontera = std::stoi(argv[6]);
    } else {
      valor_frontera = 0;
    }
    Lattice lattice1(filas, columnas, frontera, valor_frontera);
    std::cout << "La simulación comenzará con la configuración inicial: \n" << lattice1 << "\n";
    std::cout << "Para controlar la simulación debe introducir los siguientes comandos\n";
    std::cout << "'x' para salir de la simulación\n";
    std::cout << "'n' para avanzar y mostrar la siguiente generación\n";
    std::cout << "'L' para avanzar y mostrar las siguientes 5 generaciones\n";
    std::cout << "'c' para hacer que los comandos n y L dejen de mostrar el tablero y muestren solo la población\n";
    std::cout << "'s' para guardar la configuración actual en un archivo\n" << std::endl;
    std::string nombre_archivo_salida;
    std::string tecla_pulsada;
    bool comando_c = false;
    while (true) {
      std::cout << "Presione la tecla que desee..." << std::endl;
      std::cin >> tecla_pulsada;
      switch (tecla_pulsada[0]) {
        case 'x':
          std::cout << "Saliendo de la simulación..." << std::endl;
          exit(EXIT_SUCCESS);
          break;
        case 'n':
          lattice1.nextGeneration();
          if (comando_c) {
            std::cout << "Población: " << lattice1.Population() << std::endl;
          } else {
            std::cout << lattice1 << std::endl;
          }
          break;
        case 'L':
          if (comando_c) {
            for (int iterador = 0; iterador < 5; iterador++) {
              lattice1.nextGeneration();
              std::cout << "Población: " << lattice1.Population() << std::endl;
            }
          } else {
            for (int iterador = 0; iterador < 5; iterador++) {
              lattice1.nextGeneration();
              std::cout << lattice1 << std::endl;
            }
          }
          break;
        case 'c':
          if (comando_c) {
            comando_c = false;
            std::cout << "Comando c desactivado" << std::endl;
          } else {
            comando_c = true;
            std::cout << "Comando c activo" << std::endl;
          }
          break;
        case 's':
          std::cout << "Introduce el nombre del archivo donde guardar la configuración actual: ";
          std::cin >> nombre_archivo_salida;
          lattice1.GuardaConfiguracionEnArchivo(nombre_archivo_salida);
          std::cout << "Archivo guardado con éxito." << std::endl;
          break;
        default:
          std::cout << "Comando no reconocido." << std::endl;
          break;
      }
    }
  } else {
    std::string nombre_archivo = argv[2];
    std::string frontera = argv[4];
    int valor_frontera{0};
    if (frontera == "open") {
      valor_frontera = std::stoi(argv[5]);
    } else {
      valor_frontera = 0;
    }
    Lattice lattice1(nombre_archivo, frontera, valor_frontera);
    std::cout << "La simulación comenzará con la configuración inicial: \n" << lattice1 << "\n";
    std::cout << "Para controlar la simulación debe introducir los siguientes comandos\n";
    std::cout << "'x' para salir de la simulación\n";
    std::cout << "'n' para avanzar y mostrar la siguiente generación\n";
    std::cout << "'L' para avanzar y mostrar las siguientes 5 generaciones\n";
    std::cout << "'c' para hacer que los comandos n y L dejen de mostrar el tablero y muestren solo la población\n";
    std::cout << "'s' para guardar la configuración actual en un archivo\n" << std::endl;
    std::string nombre_archivo_salida;
    std::string tecla_pulsada;
    bool comando_c = false;
    while (true) {
      std::cout << "Presione la tecla que desee..." << std::endl;
      std::cin >> tecla_pulsada;
      switch (tecla_pulsada[0]) {
        case 'x':
          std::cout << "Saliendo de la simulación..." << std::endl;
          exit(EXIT_SUCCESS);
          break;
        case 'n':
          lattice1.nextGeneration();
          if (comando_c) {
            std::cout << "Población: " << lattice1.Population() << std::endl;
          } else {
            std::cout << lattice1 << std::endl;
          }
          break;
        case 'L':
          if (comando_c) {
            for (int iterador = 0; iterador < 5; iterador++) {
              lattice1.nextGeneration();
              std::cout << "Población: " << lattice1.Population() << std::endl;
            }
          } else {
            for (int iterador = 0; iterador < 5; iterador++) {
              lattice1.nextGeneration();
              std::cout << lattice1 << std::endl;
            }
          }
          break;
        case 'c':
          if (comando_c) {
            comando_c = false;
            std::cout << "Comando c desactivado" << std::endl;
          } else {
            comando_c = true;
            std::cout << "Comando c activo" << std::endl;
          }
          break;
        case 's':
          std::cout << "Introduce el nombre del archivo donde guardar la configuración actual: ";
          std::cin >> nombre_archivo_salida;
          lattice1.GuardaConfiguracionEnArchivo(nombre_archivo_salida);
          std::cout << "Archivo guardado con éxito." << std::endl;
          break;
        default:
          std::cout << "Comando no reconocido." << std::endl;
          break;
      }
    }
  }
}