/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: El juego de la vida
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 23/02/2024
/// Archivo: cell.h
/// Contiene la definición de los métodos de la clase Cell.

#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <utility>

class Lattice;

typedef int State;
typedef std::pair<int, int> Position;

// Clase Cell 
class Cell {
 public:
  // Constructores
  Cell(); 
  Cell(const std::pair<int, int>  posicion, const int estado);

  // Métodos
  int nextState(const Lattice& lattice);
  void updateState();
    
  // Getters y setters
  State getState() const;
  State setState(const int estado);
  Position getPosition() const;
  Position setPosition(const std::pair<int, int> posicion);
  
  // Operador de salida
  friend std::ostream& operator<<(std::ostream&, const Cell&);
 private:
  Position posicion_;
  State estado_;
  int estado_siguiente_{-1};
};

#endif