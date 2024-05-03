/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: El juego de la vida
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 23/02/2024
/// Archivo: lattice.h
/// Contiene la definición de los métodos de la clase Lattice.

#ifndef LATTICE_H
#define LATTICE_H

#include <iostream>
#include <vector>

class Cell;

typedef std::pair<int, int> Position;

// Clase Lattice 
class Lattice {
 public:
  // Constructores
  Lattice();
  Lattice(const int filas, const int columnas, const std::string& frontera, int valor_frontera);
  Lattice(const std::string& nombre_archivo, const std::string& frontera, int valor_frontera);

  // Destructor
  ~Lattice();

  // Métodos
  void Initialize(const Position& posicion, const bool estado);
  void nextGeneration();
  std::pair<int, int> PidePosicionesUsuario();
  std::size_t Population() const;
  void CambiaTamañoVector(const std::vector<bool>& frontera_viva);
  void ActualizaPosicionesVector();
  void GuardaConfiguracionEnArchivo(const std::string& nombre_archivo);

  // Getters
  const Cell& getCell(const Position& posicion) const;
  const Cell& getCellVector(const Position& posicion) const;
  const int getTamanio() const { return tamanio_; }
  const int getFilas() const { return filas_; }
  const int getColumnas() const { return columnas_; }
  std::string getFrontera() const { return frontera_; }

  // Operador de salida
  friend std::ostream& operator<<(std::ostream&, const Lattice&);
  Cell& operator[](const Position&) const;
 private:
  Cell** lattice_; // Para el caso de que la frontera sea open o reflective
  std::vector<std::vector<Cell>> lattice_vector_; // Para el caso de que la frontera sea noborder
  int tamanio_;
  std::string frontera_; // Implementadas la frontera open, noborder y reflective
  int valor_frontera_{0};
  int filas_;
  int columnas_;
};

#endif