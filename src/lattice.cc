/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: El juego de la vida
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 23/02/2024
/// Archivo: lattice.cc
/// Contiene la implementación de los métodos de la clase Lattice.

#include "lattice.h"
#include "cell.h"

#include <fstream>
#include <algorithm>

// Constructor por defecto
Lattice::Lattice() {
  tamanio_ = 0;
  filas_ = 0;
  columnas_ = 0;
  frontera_ = "open";
  valor_frontera_ = 0;
  lattice_ = new Cell*[filas_];
  for (int iterador = 0; iterador < filas_; iterador++) {
    lattice_[iterador] = new Cell[columnas_];
  }
}

// Constructor sin archivo
Lattice::Lattice(const int filas, const int columnas, const std::string& frontera, int valor_frontera) {
  tamanio_ = filas * columnas;
  filas_ = filas;
  columnas_ = columnas;
  frontera_ = frontera;
  valor_frontera_ = valor_frontera;
  if (frontera_ == "noborder") {
    lattice_vector_.resize(filas_, std::vector<Cell>(columnas_, Cell()));
    for (int iterador = 0; iterador < filas_; iterador++) {
      for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
        lattice_vector_[iterador][iterador2] = Cell(std::make_pair(iterador, iterador2), false);
      }
    }
    std::cout << "Introduzca la posición de la celula que desea inicializar viva separando fila y columna con un espacio (fila columna)" << std::endl;
    std::cout << "Si quiere iniciar varias introdúzcalas separadas por un ENTER. Cuando haya terminado presione ENTER sin escribir nada para que el programa continúe" << std::endl;
    while (true) {
      std::pair<int, int> coordenadas = PidePosicionesUsuario();
      if (coordenadas.first == -1) {
        break;
      }
      lattice_vector_[coordenadas.first][coordenadas.second] = Cell(coordenadas, true);
    }
  } else {
    if (frontera_ == "open") {
      columnas_ = columnas_ + 2;
      filas_ = filas_ + 2;
      lattice_ = new Cell*[filas_ ];
      for (int iterador = 0; iterador < filas_; iterador++) {
        lattice_[iterador] = new Cell[columnas_];
      }
      for (int iterador = 1; iterador < filas_ - 1; iterador++) {
        for (int iterador2 = 1; iterador2 < columnas_ - 1; iterador2++) {
          lattice_[iterador][iterador2] = Cell(std::make_pair(iterador, iterador2), false);
        }
      }
      for (int iterador = 0; iterador < columnas_; iterador++) {
        lattice_[0][iterador] = Cell(std::make_pair(0, iterador), valor_frontera);
        Initialize(std::make_pair(0, iterador), valor_frontera);
      }
      for (int iterador = 0; iterador < filas_; iterador++) {
        lattice_[iterador][0] = Cell(std::make_pair(iterador, 0), valor_frontera);
        Initialize(std::make_pair(iterador, 0), valor_frontera);
      }
      for (int iterador = 0; iterador < columnas_; iterador++) {
        lattice_[filas_ - 1][iterador] = Cell(std::make_pair(filas_ - 1, iterador), valor_frontera);
        Initialize(std::make_pair(filas_ - 1, iterador), valor_frontera);
      }
      for (int iterador = 0; iterador < filas_; iterador++) {
        lattice_[iterador][columnas_ - 1] = Cell(std::make_pair(iterador, columnas_ - 1), valor_frontera);
        Initialize(std::make_pair(iterador, columnas_ - 1), valor_frontera);
      }

      std::cout << "Introduzca la posición de la celula que desea inicializar viva separando fila y columna con un espacio (fila columna). Ejemplo: 0 3" << std::endl;
      std::cout << "Si quiere iniciar varias introdúzcalas separadas por un ENTER. Cuando haya terminado presione ENTER sin escribir nada para que el programa continúe." << std::endl;
      while (true) {
        std::pair<int, int> coordenadas = PidePosicionesUsuario();
        if (coordenadas.first == -1) {
          break;
        }
        Initialize(coordenadas, true);
      }       
    } else {
      lattice_ = new Cell*[filas_];
      for (int iterador = 0; iterador < filas_; iterador++) {
        lattice_[iterador] = new Cell[columnas_];
      }
      for (int iterador = 0; iterador < filas_; iterador++) {
        for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
          lattice_[iterador][iterador2] = Cell(std::make_pair(iterador, iterador2), false);
        }
      }
      std::cout << "Introduzca la posición de la celula que desea inicializar viva separando fila y columna con un espacio (fila columna). Ejemplo: 0 3" << std::endl;
      std::cout << "Si quiere iniciar varias introdúzcalas separadas por un ENTER. Cuando haya terminado presione ENTER sin escribir nada para que el programa continúe." << std::endl;
      while (true) {
        std::pair<int, int> coordenadas = PidePosicionesUsuario();
        if (coordenadas.first == -1) {
          break;
        }
        Initialize(coordenadas, true);
      }
    }
  }
}

// Constructor con archivo
Lattice::Lattice(const std::string& nombre_archivo, const std::string& frontera, int valor_frontera) {
  frontera_ = frontera;
  valor_frontera_ = valor_frontera;
  std::ifstream archivo;
  std::string linea_extraida;
  archivo.open(nombre_archivo);
  int numero_lineas{0};
  while (getline(archivo, linea_extraida)) {
    linea_extraida.erase(std::remove_if(linea_extraida.begin(), linea_extraida.end(), ::isspace), linea_extraida.end());
    numero_lineas++;
  }
  columnas_ = linea_extraida.size();
  filas_ = numero_lineas;
  tamanio_ = filas_ * columnas_;
  archivo.close();
  archivo.open(nombre_archivo);
  if (frontera_ == "noborder") {
    lattice_vector_.resize(filas_, std::vector<Cell>(columnas_, Cell()));
    for (int iterador = 0; iterador < filas_; iterador++) {
      getline(archivo, linea_extraida);
      linea_extraida.erase(std::remove_if(linea_extraida.begin(), linea_extraida.end(), ::isspace), linea_extraida.end());
      for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
        lattice_vector_[iterador][iterador2] = Cell(std::make_pair(iterador, iterador2), linea_extraida[iterador2] - '0');
      }
    }
  } else {
    if (frontera_ == "open") {
      columnas_ = columnas_ + 2;
      filas_ = filas_ + 2;
      lattice_ = new Cell*[filas_];
      for (int iterador = 0; iterador < filas_; iterador++) {
        lattice_[iterador] = new Cell[columnas_ ];
      }
      for (int iterador = 0; iterador < columnas_; iterador++) {
        Initialize(std::make_pair(0, iterador), valor_frontera);
      }
      for (int iterador = 0; iterador < filas_; iterador++) {
        Initialize(std::make_pair(iterador, 0), valor_frontera);
      }
      for (int iterador = 0; iterador < columnas_; iterador++) {
        Initialize(std::make_pair(filas_ - 1, iterador), valor_frontera);
      }
      for (int iterador = 0; iterador < filas_; iterador++) {
        Initialize(std::make_pair(iterador, columnas_ - 1), valor_frontera);
      }
      for (int iterador = 1; iterador < filas_ - 1; iterador++) {
        for (int iterador2 = 1; iterador2 < columnas_ - 1; iterador2++) {
          lattice_[iterador][iterador2] = Cell(std::make_pair(iterador, iterador2), false);
        }
      }
      for (int iterador = 1; iterador < filas_ - 1; iterador++) {
        getline(archivo, linea_extraida); 
        linea_extraida.erase(std::remove_if(linea_extraida.begin(), linea_extraida.end(), ::isspace), linea_extraida.end());
        for (int iterador2 = 1; iterador2 < columnas_ - 1; iterador2++) {
          Initialize(std::make_pair(iterador, iterador2), linea_extraida[iterador2 - 1] - '0');
        }
      }
    } else {
      lattice_ = new Cell*[filas_];
      for (int iterador = 0; iterador < filas_; iterador++) {
        lattice_[iterador] = new Cell[columnas_];
      }
      for (int iterador = 0; iterador < filas_; iterador++) {
        for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
          lattice_[iterador][iterador2] = Cell(std::make_pair(iterador, iterador2), false);
        }
      }
      for (int iterador = 0; iterador < filas_; iterador++) {
        getline(archivo, linea_extraida); 
        linea_extraida.erase(std::remove_if(linea_extraida.begin(), linea_extraida.end(), ::isspace), linea_extraida.end());
        for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
          Initialize(std::make_pair(iterador, iterador2), linea_extraida[iterador2] - '0');
        }
      }
    }
  }
}

// Destructor
Lattice::~Lattice() {
  delete[] lattice_;
}

// Método que inicializa el estado de las células
void Lattice::Initialize(const Position& posicion, const bool estado) {
  lattice_[posicion.first][posicion.second] = Cell(posicion, estado);
}

// Método que actualiza el estado de las células usando la regla 23/3
void Lattice::nextGeneration() {
  if (frontera_ == "open") {
    for (int iterador = 1; iterador < filas_ - 1; iterador++) {
      for (int iterador2 = 1; iterador2 < columnas_ - 1; iterador2++) {
        lattice_[iterador][iterador2].nextState(*this);
      }
    }
    for (int iterador = 1; iterador < filas_ - 1; iterador++) {
      for (int iterador2 = 1; iterador2 < columnas_ - 1; iterador2++) {
        lattice_[iterador][iterador2].updateState();
      }
    }
  } else {
    if (frontera_ == "noborder") {
      int estado_siguiente{0};
      std::vector<bool> frontera_viva(8, false); // Este vector representa las 8 posibles posiciones de una célula viva en el borde: esquina superior izquierda, esquina superior derecha, esquina inferior izquierda, esquina inferior derecha, borde superior, borde inferior, borde izquierdo, borde derecho. Se usa para saber si hay células vivas en ese borde y así poder añadir filas o columnas en el respectivo lugar
      for (int iterador = 0; iterador < filas_; iterador++) {
        for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
          estado_siguiente = lattice_vector_[iterador][iterador2].nextState(*this);
          if (estado_siguiente == 1) {
            if (iterador == 0 && iterador2 == 0) { // esquina superior izquierda
              frontera_viva[0] = true;
            } else {
              if (iterador == 0 && iterador2 == columnas_ - 1) { // esquina superior derecha
                frontera_viva[1] = true;
              } else {
                if (iterador == filas_ - 1 && iterador2 == 0) { // esquina inferior izquierda
                  frontera_viva[2] = true;
                } else {
                  if (iterador == filas_ - 1 && iterador2 == columnas_ - 1) { // esquina inferior derecha
                    frontera_viva[3] = true;
                  } else {
                    if (iterador == 0) { // borde superior
                      frontera_viva[4] = true;
                    } else {
                      if (iterador == filas_ - 1) { // borde inferior
                        frontera_viva[5] = true;
                      } else {
                        if (iterador2 == 0) { // borde izquierdo
                          frontera_viva[6] = true;
                        } else {
                          if (iterador2 == columnas_ - 1) { // borde derecho
                            frontera_viva[7] = true;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      CambiaTamañoVector(frontera_viva);
      ActualizaPosicionesVector();
      for (int iterador = 0; iterador < filas_; iterador++) {
        for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
          lattice_vector_[iterador][iterador2].updateState();
        }
      }
    } else {
      for (int iterador = 0; iterador < filas_; iterador++) {
        for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
          lattice_[iterador][iterador2].nextState(*this);
        }
      }
      for (int iterador = 0; iterador < filas_; iterador++) {
        for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
          lattice_[iterador][iterador2].updateState();
        }
      }
    }
  }
}

// Método que pide al usuario las posiciones de las células que desea inicializar
std::pair<int, int> Lattice::PidePosicionesUsuario() {
  int fila;
  int columna;
  std::string coordenadas;
  getline(std::cin, coordenadas);
  if (coordenadas.empty()) {
    return std::make_pair(-1, -1);
  } else {
    fila = coordenadas[0] - '0';
    columna = coordenadas[2] - '0';
    return std::make_pair(fila, columna);
  }
}

// Método que devuelve el número de células vivas
std::size_t Lattice::Population() const {
  std::size_t poblacion{0};
  if (frontera_ == "noborder") {
    for (int iterador = 0; iterador < filas_; iterador++) {
      for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
        if (lattice_vector_[iterador][iterador2].getState() == 1) {
          poblacion++;
        }
      }
    }
  } else {
    if (frontera_ == "open") {
      for (int iterador = 1; iterador < filas_ - 1; iterador++) {
        for (int iterador2 = 1; iterador2 < columnas_ - 1; iterador2++) {
          if (lattice_[iterador][iterador2].getState() == 1) {
            poblacion++;
          }
        }
      }
    } else {
      for (int iterador = 0; iterador < filas_; iterador++) {
        for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
          if (lattice_[iterador][iterador2].getState() == 1) {
            poblacion++;
          }
        }
      }
    }
  }
  return poblacion;
}

// Método que cambia el tamaño del vector de células
void Lattice::CambiaTamañoVector(const std::vector<bool>& frontera_viva) {
  if (frontera_viva[0] == 1) {
    lattice_vector_.insert(lattice_vector_.begin(), std::vector<Cell>(lattice_vector_[0].size(), Cell()));
    for (int iterador = 0; iterador < lattice_vector_.size(); iterador++) {
      lattice_vector_[iterador].insert(lattice_vector_[iterador].begin(), Cell());
    }
    filas_++;
    columnas_++;
  }
  if (frontera_viva[1] == 1) { // esquina superior derecha
    lattice_vector_.insert(lattice_vector_.begin(), std::vector<Cell>(lattice_vector_[0].size(), Cell()));
    for (int iterador = 0; iterador < lattice_vector_.size(); iterador++) {
      lattice_vector_[iterador].push_back(Cell());
    }
    filas_++;
    columnas_++;
  }
  if (frontera_viva[2] == 1) { // esquina inferior izquierda
    lattice_vector_.push_back(std::vector<Cell>(lattice_vector_[0].size(), Cell()));
    for (int iterador = 0; iterador < lattice_vector_.size(); iterador++) {
      lattice_vector_[iterador].insert(lattice_vector_[iterador].begin(), Cell());
    }
    filas_++;
    columnas_++;
  }
  if (frontera_viva[3] == 1) { // esquina inferior derecha
    lattice_vector_.push_back(std::vector<Cell>(lattice_vector_[0].size(), Cell()));
    for (int iterador = 0; iterador < lattice_vector_.size(); iterador++) {
      lattice_vector_[iterador].push_back(Cell());
    }
    filas_++;
    columnas_++;
  }
  if (frontera_viva[4] == 1) { // borde superior
    lattice_vector_.insert(lattice_vector_.begin(), std::vector<Cell>(lattice_vector_[0].size(), Cell()));
    filas_++;
  }
  if (frontera_viva[5] == 1) { // borde inferior
    lattice_vector_.push_back(std::vector<Cell>(lattice_vector_[0].size(), Cell()));
    filas_++;
  }
  if (frontera_viva[6] == 1) { // borde izquierdo
    for (int iterador = 0; iterador < lattice_vector_.size(); iterador++) {
      lattice_vector_[iterador].insert(lattice_vector_[iterador].begin(), Cell());
    }
    columnas_++;
  }
  if (frontera_viva[7] == 1) { // borde derecho
    for (int iterador = 0; iterador < lattice_vector_.size(); iterador++) {
      lattice_vector_[iterador].push_back(Cell());
    }
    columnas_++;
  }
}

// Método que actualiza las posiciones del vector de células
void Lattice::ActualizaPosicionesVector() {
  for (int iterador = 0; iterador < filas_; iterador++) {
    for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
      lattice_vector_[iterador][iterador2].setPosition(std::make_pair(iterador, iterador2));
    }
  }
}

// Método que guarda la configuración actual en un archivo
void Lattice::GuardaConfiguracionEnArchivo(const std::string& nombre_archivo) {
  std::ofstream archivo;
  archivo.open(nombre_archivo);
  if (frontera_ == "noborder") {
    for (int iterador = 0; iterador < filas_; iterador++) {
      for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
        archivo << lattice_vector_[iterador][iterador2].getState() << " ";
      }
      archivo << std::endl;
    }
  } else {
    if (frontera_ == "open") {
      for (int iterador = 1; iterador < filas_ - 1; iterador++) {
        for (int iterador2 = 1; iterador2 < columnas_ - 1; iterador2++) {
          archivo << lattice_[iterador][iterador2].getState() << " ";
        }
        archivo << std::endl;
      }
    } else {
      for (int iterador = 0; iterador < filas_; iterador++) {
        for (int iterador2 = 0; iterador2 < columnas_; iterador2++) {
          archivo << lattice_[iterador][iterador2].getState() << " ";
        }
        archivo << std::endl;
      }
    }
  }
  archivo.close();
}

// Método que devuelve la célula en la posición indicada
const Cell& Lattice::getCell(const Position& posicion) const {
  return lattice_[posicion.first][posicion.second];
}

// Método que devuelve la célula en la posición indicada del vector de células con frontera noborder
const Cell& Lattice::getCellVector(const Position& posicion) const {
  return lattice_vector_[posicion.first][posicion.second];
}

// Operador de salida
std::ostream& operator<<(std::ostream& salida, const Lattice& lattice) {
  if (lattice.lattice_vector_.size() != 0) {
    for (int iterador = 0; iterador < lattice.filas_; iterador++) {
      for (int iterador2 = 0; iterador2 < lattice.columnas_; iterador2++) {
        salida << lattice.lattice_vector_[iterador][iterador2] << " ";
      }
      salida << std::endl;
    }
  } else {
    if (lattice.frontera_ == "open") {
    for (int iterador = 1; iterador < lattice.filas_ - 1; iterador++) {
      for (int iterador2 = 1; iterador2 < lattice.columnas_ - 1; iterador2++) {
        salida << lattice.lattice_[iterador][iterador2] << " ";
      }
      salida << std::endl;
    }
    } else {
      for (int iterador = 0; iterador < lattice.filas_; iterador++) {
        for (int iterador2 = 0; iterador2 < lattice.columnas_; iterador2++) {
          salida << lattice.lattice_[iterador][iterador2] << " ";
        }
        salida << std::endl;
      }
    }
  }
  salida << std::endl;
  return salida;
}

// Operador de acceso
Cell& Lattice::operator[](const Position& posicion) const {
  return lattice_[posicion.first][posicion.second];
}