/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: El juego de la vida
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 23/02/2024
/// Archivo: cell.cc
/// Contiene la implementación de los métodos de la clase Lattice.

#include "cell.h"
#include "lattice.h"

// Constructor por defecto
Cell::Cell() : posicion_(std::make_pair(0, 0)), estado_(0) {}

// Constructor con parámetros
Cell::Cell(const Position posicion, const State estado) : posicion_(posicion), estado_(estado) {}

// Método que calcula y devuelve el estado siguiente de la célula
int Cell::nextState(const Lattice& lattice) {
  State leftState;
  State rightState;
  State upState;
  State downState;
  State upleftState;
  State uprightState;
  State downleftState;
  State downrightState;
  State centerState;
  if (lattice.getFrontera() == "open") {
    centerState = lattice.getCell(posicion_).getState();
    leftState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
    rightState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
    upState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
    downState = lattice.getCell(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
    upleftState = lattice.getCell(std::make_pair((posicion_.first - 1), (posicion_.second - 1))).getState();
    uprightState = lattice.getCell(std::make_pair((posicion_.first - 1), (posicion_.second + 1))).getState();
    downleftState = lattice.getCell(std::make_pair((posicion_.first + 1), (posicion_.second - 1))).getState();
    downrightState = lattice.getCell(std::make_pair((posicion_.first + 1), (posicion_.second + 1))).getState();
  } else {
    if (lattice.getFrontera() == "noborder") {
      centerState = lattice.getCellVector(posicion_).getState();
      if (posicion_.first == 0 && posicion_.second == 0) { // Esquina superior izquierda
        leftState = 0;
        rightState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
        upState = 0;
        downState = lattice.getCellVector(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
        upleftState = 0;
        uprightState = 0;
        downleftState = 0;
        downrightState = lattice.getCellVector(std::make_pair((posicion_.first + 1), (posicion_.second + 1))).getState();
      } else {
        if (posicion_.first == 0 && posicion_.second == lattice.getColumnas() - 1) { // Esquina superior derecha
          leftState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
          rightState = 0;
          upState = 0;
          downState = lattice.getCellVector(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
          upleftState = 0;
          uprightState = 0;
          downleftState = lattice.getCellVector(std::make_pair((posicion_.first + 1), (posicion_.second - 1))).getState();
          downrightState = 0;
        } else {
          if (posicion_.first == lattice.getFilas() - 1 && posicion_.second == 0) { // Esquina inferior izquierda
            leftState = 0;
            rightState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
            upState = lattice.getCellVector(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
            downState = 0;
            upleftState = 0;
            uprightState = lattice.getCellVector(std::make_pair((posicion_.first - 1), (posicion_.second + 1))).getState();
            downleftState = 0;
            downrightState = 0;
          } else {
            if (posicion_.first == lattice.getFilas() - 1 && posicion_.second == lattice.getColumnas() - 1) { // Esquina inferior derecha
              leftState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
              rightState = 0;
              upState = lattice.getCellVector(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
              downState = 0;
              upleftState = lattice.getCellVector(std::make_pair((posicion_.first - 1), (posicion_.second - 1))).getState();
              uprightState = 0;
              downleftState = 0;
              downrightState = 0;
            } else {
              if (posicion_.first == 0) { // Frontera superior
                leftState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
                rightState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
                upState = 0;
                downState = lattice.getCellVector(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
                upleftState = 0;
                uprightState = 0;
                downleftState = lattice.getCellVector(std::make_pair((posicion_.first + 1), (posicion_.second - 1))).getState();
                downrightState = lattice.getCellVector(std::make_pair((posicion_.first + 1), (posicion_.second + 1))).getState();
              } else {
                if (posicion_.second == 0) { // Frontera izquierda
                  leftState = 0;
                  rightState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
                  upState = lattice.getCellVector(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
                  downState = lattice.getCellVector(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
                  upleftState = 0;
                  uprightState = lattice.getCellVector(std::make_pair((posicion_.first - 1), (posicion_.second + 1))).getState();
                  downleftState = 0;
                  downrightState = lattice.getCellVector(std::make_pair((posicion_.first + 1), (posicion_.second + 1))).getState();
                } else {
                  if (posicion_.first == lattice.getFilas() - 1) { // Frontera inferior
                    leftState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
                    rightState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
                    upState = lattice.getCellVector(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
                    downState = 0;
                    upleftState = lattice.getCellVector(std::make_pair((posicion_.first - 1), (posicion_.second - 1))).getState();
                    uprightState = lattice.getCellVector(std::make_pair((posicion_.first - 1), (posicion_.second + 1))).getState();
                    downleftState = 0;
                    downrightState = 0;
                  } else {
                    if (posicion_.second == lattice.getColumnas() - 1) { // Frontera derecha
                      leftState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
                      rightState = 0;
                      upState = lattice.getCellVector(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
                      downState = lattice.getCellVector(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
                      upleftState = lattice.getCellVector(std::make_pair((posicion_.first - 1), (posicion_.second - 1))).getState();  
                      uprightState = 0;
                      downleftState = lattice.getCellVector(std::make_pair((posicion_.first + 1), (posicion_.second - 1))).getState();
                      downrightState = 0;
                    } else { // Interior
                      leftState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
                      rightState = lattice.getCellVector(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
                      upState = lattice.getCellVector(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
                      downState = lattice.getCellVector(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
                      upleftState = lattice.getCellVector(std::make_pair((posicion_.first - 1), (posicion_.second - 1))).getState();
                      uprightState = lattice.getCellVector(std::make_pair((posicion_.first - 1), (posicion_.second + 1))).getState();
                      downleftState = lattice.getCellVector(std::make_pair((posicion_.first + 1), (posicion_.second - 1))).getState();
                      downrightState = lattice.getCellVector(std::make_pair((posicion_.first + 1), (posicion_.second + 1))).getState();
                    }
                  }
                }
              }
            }
          }
        }
      }       
    } else {
      centerState = lattice.getCell(posicion_).getState();
      if (posicion_.first == 0 && posicion_.second == 0) { // Esquina superior izquierda
        leftState = estado_;
        rightState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
        upState = estado_;
        downState = lattice.getCell(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
        upleftState = estado_;
        uprightState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
        downleftState = lattice.getCell(std::make_pair((posicion_.first + 1), (posicion_.second))).getState();
        downrightState = lattice.getCell(std::make_pair((posicion_.first + 1), (posicion_.second + 1))).getState();
      } else {
        if (posicion_.first == 0 && posicion_.second == lattice.getColumnas() - 1) { // Esquina superior derecha
          leftState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
          rightState = estado_;
          upState = estado_;
          downState = lattice.getCell(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
          upleftState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
          uprightState = estado_;
          downleftState = lattice.getCell(std::make_pair((posicion_.first + 1), (posicion_.second - 1))).getState();
          downrightState = lattice.getCell(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
        } else {
          if (posicion_.first == lattice.getFilas() - 1 && posicion_.second == 0) { // Esquina inferior izquierda
            leftState = estado_;
            rightState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
            upState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
            downState = estado_;
            upleftState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
            uprightState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second + 1)).getState();
            downleftState = estado_;
            downrightState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
          } else {
            if (posicion_.first == lattice.getFilas() - 1 && posicion_.second == lattice.getColumnas() - 1) { // Esquina inferior derecha
              leftState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
              rightState = estado_;
              upState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
              downState = estado_;
              upleftState = lattice.getCell(std::make_pair((posicion_.first - 1), (posicion_.second - 1))).getState();
              uprightState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
              downleftState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
              downrightState = estado_;
            } else {
              if (posicion_.first == 0) { // Frontera superior
                leftState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
                rightState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
                upState = estado_;
                downState = lattice.getCell(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
                upleftState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
                uprightState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
                downleftState = lattice.getCell(std::make_pair((posicion_.first + 1), (posicion_.second - 1))).getState();
                downrightState = lattice.getCell(std::make_pair((posicion_.first + 1), (posicion_.second + 1))).getState();
              } else {
                if (posicion_.second == 0) { // Frontera izquierda
                  leftState = estado_;
                  rightState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
                  upState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
                  downState = lattice.getCell(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
                  upleftState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
                  uprightState = lattice.getCell(std::make_pair((posicion_.first - 1), (posicion_.second + 1))).getState();
                  downleftState = lattice.getCell(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
                  downrightState = lattice.getCell(std::make_pair((posicion_.first + 1), (posicion_.second + 1))).getState();
                } else {
                  if (posicion_.first == lattice.getFilas() - 1) { // Frontera inferior
                    leftState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
                    rightState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
                    upState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
                    downState = estado_;
                    upleftState = lattice.getCell(std::make_pair((posicion_.first - 1), (posicion_.second - 1))).getState();
                    uprightState = lattice.getCell(std::make_pair((posicion_.first - 1), (posicion_.second + 1))).getState();
                    downleftState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
                    downrightState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
                  } else {
                    if (posicion_.second == lattice.getColumnas() - 1) { // Frontera derecha
                      leftState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
                      rightState = estado_;
                      upState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
                      downState = lattice.getCell(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
                      upleftState = lattice.getCell(std::make_pair((posicion_.first - 1), (posicion_.second - 1))).getState();
                      uprightState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
                      downleftState = lattice.getCell(std::make_pair((posicion_.first + 1), (posicion_.second - 1))).getState();
                      downrightState = lattice.getCell(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
                    } else { // Interior
                      leftState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second - 1))).getState();
                      rightState = lattice.getCell(std::make_pair(posicion_.first, (posicion_.second + 1))).getState();
                      upState = lattice.getCell(std::make_pair((posicion_.first - 1), posicion_.second)).getState();
                      downState = lattice.getCell(std::make_pair((posicion_.first + 1), posicion_.second)).getState();
                      upleftState = lattice.getCell(std::make_pair((posicion_.first - 1), (posicion_.second - 1))).getState();
                      uprightState = lattice.getCell(std::make_pair((posicion_.first - 1), (posicion_.second + 1))).getState();
                      downleftState = lattice.getCell(std::make_pair((posicion_.first + 1), (posicion_.second - 1))).getState();
                      downrightState = lattice.getCell(std::make_pair((posicion_.first + 1), (posicion_.second + 1))).getState();
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
  if (centerState == 0) {
    if (leftState + rightState + upState + downState + upleftState + uprightState + downleftState + downrightState == 3) {
      estado_siguiente_ = 1;
    } else {
      estado_siguiente_ = 0;
    }
  } else {
    if (leftState + rightState + upState + downState + upleftState + uprightState + downleftState + downrightState == 2 || leftState + rightState + upState + downState + upleftState + uprightState + downleftState + downrightState == 3) {
      estado_siguiente_ = 1;
    } else {
      estado_siguiente_ = 0;
    }
  }
  return estado_siguiente_;
}

// Método que actualiza el estado de la célula
void Cell::updateState() {
  if (estado_siguiente_ != -1) {
    estado_ = estado_siguiente_;
    estado_siguiente_ = -1;
  }
}

// Método que devuelve el estado de la célula
State Cell::getState() const {
  return estado_;
}

// Método que establece el estado de la célula
State Cell::setState(State estado) {
  estado_ = estado;
  return estado_;
}

// Método que devuelve la posición de la célula
Position Cell::getPosition() const {
  return posicion_;
}

// Método que establece la posición de la célula
Position Cell::setPosition(Position posicion) {
  posicion_ = posicion;
  return posicion_;
}

// Operador de salida
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  if (cell.estado_ == 0) {
    os << "_";
  } else {
    os << "1";
  }
  return os;
}