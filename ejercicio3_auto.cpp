/**
 * Curso: Tecnología de Objetos
 * Laboratorio 07 - Ejercicio Propuesto 3
 * Descripción: Configurador de automóviles aplicando el Patrón Builder
 *              (Cliente, Director, IBuilder, BuilderEspecifico, Producto)
 *              con personalización de color por pieza y filtrado por criterios.
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>
#include <algorithm>

using namespace std;

// ============================================================
// ESTRUCTURA PARA MANEJAR CADA COMPONENTE DEL AUTOMOVIL
// ============================================================
struct Componente {
    string nombre;
    string detalle;
    string color;
    double precio;

    Componente(string nom, string det, string col, double pre)
        : nombre(move(nom)), detalle(move(det)), color(move(col)), precio(pre) {}

    friend ostream& operator<<(ostream& os, const Componente& c) {
        os << "    - " << left << setw(12) << c.nombre
           << " | Color: " << setw(15) << c.color
           << " | " << setw(28) << c.detalle
           << " | USD " << right << setw(8) << fixed << setprecision(2) << c.precio;
        return os;
    }
};

// ============================================================
// PRODUCTO1: CLASE AUTOMOVIL
// ============================================================
class Automovil {
    string modelo;
    string motorizacion;
    string colorPrincipal;
    string paisOrigen;
    vector<Componente> componentes;

public:
    void setDatosGenerales(const string& mod, const string& mot, const string& col, const string& pais) {
        modelo = mod;
        motorizacion = mot;
        colorPrincipal = col;
        paisOrigen = pais;
    }

    void agregarComponente(const Componente& comp) {
        componentes.push_back(comp);
    }

    string getModelo() const { return modelo; }
    string getMotorizacion() const { return motorizacion; }
    string getColorPrincipal() const { return colorPrincipal; }
    string getPaisOrigen() const { return paisOrigen; }

    double getPrecioTotal() const {
        double total = 0.0;
        for (const auto& c : componentes) {
            total += c.precio;
        }
        return total;
    }

    void mostrarFicha() const {
        cout << "====================================================================================\n";
        cout << " MODELO: " << modelo << " | Motorizacion: " << motorizacion << "\n";
        cout << " Color Principal: " << colorPrincipal << " | Pais de Origen: " << paisOrigen << "\n";
        cout << "------------------------------------------------------------------------------------\n";
        cout << " Lista de Componentes:\n";
        for (const auto& c : componentes) {
            cout << c << "\n";
        }
        cout << "------------------------------------------------------------------------------------\n";
        cout << " >>> PRECIO TOTAL: USD " << fixed << setprecision(2) << getPrecioTotal() << "\n";
        cout << "====================================================================================\n";
    }
};

// ============================================================
// INTERFAZ IBUILDER (Figura 1)
// ============================================================
class IBuilder {
public:
    virtual ~IBuilder() = default;
    virtual void reset() = 0;
    virtual void setDatos(const string& modelo, const string& motorizacion,
                          const string& colorBase, const string& pais) = 0;
    virtual void buildPuertas(const string& color) = 0;
    virtual void buildLlantas(const string& color) = 0;
    virtual void buildTimon(const string& color) = 0;
    virtual void buildAsientos(const string& color) = 0;
    virtual void buildMotor(const string& color) = 0;
    virtual void buildEspejos(const string& color) = 0;
    virtual void buildVidrios(const string& color) = 0;
    virtual unique_ptr<Automovil> getProducto() = 0;
};

// ============================================================
// BUILDER ESPECIFICO 1: AUTOMOVIL SEDAN
// ============================================================
class AutoSedanBuilder : public IBuilder {
    unique_ptr<Automovil> autoActual;
public:
    AutoSedanBuilder() { reset(); }

    void reset() override { autoActual = make_unique<Automovil>(); }

    void setDatos(const string& modelo, const string& motorizacion,
                  const string& colorBase, const string& pais) override {
        autoActual->setDatosGenerales(modelo, motorizacion, colorBase, pais);
    }

    void buildPuertas(const string& color) override {
        autoActual->agregarComponente(Componente("Puertas", "4 puertas acero estampado", color, 2200.00));
    }
    void buildLlantas(const string& color) override {
        autoActual->agregarComponente(Componente("Llantas", "Aro 16 aleacion urbana", color, 950.00));
    }
    void buildTimon(const string& color) override {
        autoActual->agregarComponente(Componente("Timon", "Direccion asistida electrica", color, 420.00));
    }
    void buildAsientos(const string& color) override {
        autoActual->agregarComponente(Componente("Asientos", "5 asientos tela ergonomica", color, 1100.00));
    }
    void buildMotor(const string& color) override {
        autoActual->agregarComponente(Componente("Motor", "1.8L 4 cilindros 140 HP", color, 5800.00));
    }
    void buildEspejos(const string& color) override {
        autoActual->agregarComponente(Componente("Espejos", "Laterales electricos", color, 310.00));
    }
    void buildVidrios(const string& color) override {
        autoActual->agregarComponente(Componente("Vidrios", "Templados con filtro UV", color, 640.00));
    }

    unique_ptr<Automovil> getProducto() override {
        auto resultado = move(autoActual);
        reset();
        return resultado;
    }
};

// ============================================================
// BUILDER ESPECIFICO 2: AUTOMOVIL SUV / DEPORTIVO
// ============================================================
class AutoSUVBuilder : public IBuilder {
    unique_ptr<Automovil> autoActual;
public:
    AutoSUVBuilder() { reset(); }

    void reset() override { autoActual = make_unique<Automovil>(); }

    void setDatos(const string& modelo, const string& motorizacion,
                  const string& colorBase, const string& pais) override {
        autoActual->setDatosGenerales(modelo, motorizacion, colorBase, pais);
    }

    void buildPuertas(const string& color) override {
        autoActual->agregarComponente(Componente("Puertas", "5 puertas reforzadas AWD", color, 3400.00));
    }
    void buildLlantas(const string& color) override {
        autoActual->agregarComponente(Componente("Llantas", "Aro 19 todoterreno", color, 1850.00));
    }
    void buildTimon(const string& color) override {
        autoActual->agregarComponente(Componente("Timon", "Deportivo multifuncion cuero", color, 780.00));
    }
    void buildAsientos(const string& color) override {
        autoActual->agregarComponente(Componente("Asientos", "7 asientos cuero calefact.", color, 2600.00));
    }
    void buildMotor(const string& color) override {
        autoActual->agregarComponente(Componente("Motor", "2.5L Turbo Hibrido 260 HP", color, 9400.00));
    }
    void buildEspejos(const string& color) override {
        autoActual->agregarComponente(Componente("Espejos", "Abatibles con sensor punto", color, 590.00));
    }
    void buildVidrios(const string& color) override {
        autoActual->agregarComponente(Componente("Vidrios", "Laminados polarizados", color, 1120.00));
    }

    unique_ptr<Automovil> getProducto() override {
        auto resultado = move(autoActual);
        reset();
        return resultado;
    }
};

// ============================================================
// DIRECTOR (Figura 1)
// ============================================================
class Director {
    IBuilder* builder = nullptr;
public:
    void setBuilder(IBuilder* b) { builder = b; }

    // Construccion estandar (un solo color base para carroceria)
    unique_ptr<Automovil> construirEstandar(const string& modelo, const string& motorizacion,
                                            const string& colorBase, const string& pais) {
        builder->reset();
        builder->setDatos(modelo, motorizacion, colorBase, pais);
        builder->buildPuertas(colorBase);
        builder->buildLlantas("Plata Aluminio");
        builder->buildTimon("Negro");
        builder->buildAsientos("Gris Oscuro");
        builder->buildMotor("Acero Natural");
        builder->buildEspejos(colorBase);
        builder->buildVidrios("Transparente");
        return builder->getProducto();
    }

    // Construccion personalizada (el cliente indica color por cada pieza)
    unique_ptr<Automovil> construirPersonalizado(
        const string& modelo, const string& motorizacion, const string& colorBase, const string& pais,
        const string& colPuertas, const string& colLlantas, const string& colTimon,
        const string& colAsientos, const string& colMotor, const string& colEspejos,
        const string& colVidrios) {
        builder->reset();
        builder->setDatos(modelo, motorizacion, colorBase, pais);
        builder->buildPuertas(colPuertas);
        builder->buildLlantas(colLlantas);
        builder->buildTimon(colTimon);
        builder->buildAsientos(colAsientos);
        builder->buildMotor(colMotor);
        builder->buildEspejos(colEspejos);
        builder->buildVidrios(colVidrios);
        return builder->getProducto();
    }
};

// ============================================================
// TEMPLATE DE FILTRADO DE CATALOGO PARA EL CLIENTE
// ============================================================
template <typename Predicado>
void buscarAutomoviles(const vector<unique_ptr<Automovil>>& catalogo,
                       const string& tituloFiltro, Predicado criterio) {
    cout << "\n>>> CONSULTA DEL CLIENTE: " << tituloFiltro << "\n";
    bool encontrado = false;
    for (const auto& vehiculo : catalogo) {
        if (criterio(*vehiculo)) {
            cout << "  * " << vehiculo->getModelo()
                 << " | Pais: " << vehiculo->getPaisOrigen()
                 << " | Motor: " << vehiculo->getMotorizacion()
                 << " | Color: " << vehiculo->getColorPrincipal()
                 << " | Precio: USD " << fixed << setprecision(2) << vehiculo->getPrecioTotal() << "\n";
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "  (No hay vehiculos que coincidan con el criterio)\n";
    }
}

// ============================================================
// CLIENTE (main)
// ============================================================
int main() {
    Director director;
    AutoSedanBuilder sedanBuilder;
    AutoSUVBuilder suvBuilder;

    vector<unique_ptr<Automovil>> catalogo;

    // 1. Auto Sedan Estandar (Japon)
    director.setBuilder(&sedanBuilder);
    catalogo.push_back(director.construirEstandar("Toyota Corolla", "Gasolina", "Blanco Perla", "Japon"));

    // 2. Auto SUV Personalizado pieza por pieza (Alemania)
    director.setBuilder(&suvBuilder);
    catalogo.push_back(director.construirPersonalizado(
        "BMW X5 M-Sport", "Hibrido", "Negro Zafiro", "Alemania",
        "Negro Zafiro",   // Puertas
        "Negro Mate",     // Llantas
        "Negro/Rojo",     // Timon
        "Cuero Cognac",   // Asientos
        "Rojo Racing",    // Tapa Motor
        "Fibra Carbono",  // Espejos
        "Ahumado Oscuro"  // Vidrios
    ));

    // 3. Auto Sedan Personalizado (Corea del Sur)
    director.setBuilder(&sedanBuilder);
    catalogo.push_back(director.construirPersonalizado(
        "Hyundai Elantra", "GLP/Gasolina", "Azul Electrico", "Corea del Sur",
        "Azul Electrico", // Puertas
        "Grafito",        // Llantas
        "Negro",          // Timon
        "Beige",          // Asientos
        "Plata",          // Motor
        "Negro Brillante",// Espejos
        "Polarizado 35%"  // Vidrios
    ));

    // Mostrar fichas tecnicas completas
    for (const auto& vehiculo : catalogo) {
        vehiculo->mostrarFicha();
    }

    // Consultas del cliente por diferentes opciones (pais, precio, motorizacion)
    buscarAutomoviles(catalogo, "Vehiculos con precio menor a USD 15,000", [](const Automovil& a) {
        return a.getPrecioTotal() < 15000.0;
    });

    buscarAutomoviles(catalogo, "Vehiculos de origen Alemania", [](const Automovil& a) {
        return a.getPaisOrigen() == "Alemania";
    });

    buscarAutomoviles(catalogo, "Vehiculos con motorizacion Hibrido", [](const Automovil& a) {
        return a.getMotorizacion() == "Hibrido";
    });

    return 0;
}