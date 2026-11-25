# Laboratorio 07: Patrón de Diseño Builder en C++

**Universidad:** Universidad Nacional de San Agustín de Arequipa (UNSA)  
**Escuela Profesional:** Ingeniería de Sistemas  
**Asignatura:** Tecnología de Objetos (2026-B)  
**Docente:** MBA Mg. Ing. Rene Alonso Nieto Valencia  

## Integrantes
- Ccahua Chise Elizabeth Karina
- Navarro Quispe Henry Alex
- Davila Flores Mathias Dario

## Estructura del Repositorio

| Archivo | Descripción |
| :--- | :--- |
| `ejercicio1_builder.cpp` | Sistema de cotización de laptops con Patrón Builder extendido (marcas, colores, CPU, RAM, monitor plasma, impresoras y accesorios). |
| `ejercicio2_banco.cpp` | Sistema de cuentas bancarias usando Fluent Builder, herencia, polimorfismo, templates, sobrecarga y lambdas (cuentas individuales/mancomunadas, préstamos, transferencias y estado de cuenta con fecha de corte). |
| `ejercicio3_auto.cpp` | Configurador de automóviles con Patrón Builder clásico (`Director`, `IBuilder`, `AutoSedanBuilder`, `AutoSUVBuilder`), color por pieza y búsqueda filtrada por criterios. |

## Compilación y Ejecución

Requiere `g++` con soporte para **C++17**:

```bash
# Ejercicio 1
g++ -std=c++17 -Wall ejercicio1_builder.cpp -o ejercicio1 && ./ejercicio1

# Ejercicio 2
g++ -std=c++17 -Wall ejercicio2_banco.cpp -o ejercicio2 && ./ejercicio2

# Ejercicio 3
g++ -std=c++17 -Wall ejercicio3_auto.cpp -o ejercicio3 && ./ejercicio3
```
