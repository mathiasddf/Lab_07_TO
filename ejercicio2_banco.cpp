/**
 * Curso: Tecnología de Objetos
 * Laboratorio 07 - Ejercicio Propuesto 2
 * Descripción: Sistema de consulta y operaciones sobre cuentas bancarias.
 *              Aplica Patrón Builder, herencia, polimorfismo, templates,
 *              sobrecarga, constructores y expresiones lambda.
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <functional>

using namespace std;

// ============================================================
// ESTRUCTURA DE MOVIMIENTO (con sobrecarga de operador <<)
// ============================================================
struct Movimiento {
    string fecha;        // Formato YYYY-MM-DD para comparacion cronologica
    string descripcion;
    double monto;
    string moneda;

    Movimiento(string f, string desc, double m, string mon = "PEN")
        : fecha(move(f)), descripcion(move(desc)), monto(m), moneda(move(mon)) {}

    friend ostream& operator<<(ostream& os, const Movimiento& mov) {
        os << "    [" << mov.fecha << "] " << left << setw(38) << mov.descripcion
           << " | " << mov.moneda << " " << right << setw(9) << fixed << setprecision(2) << mov.monto;
        return os;
    }
};

// ============================================================
// TEMPLATE GENERICO PARA PROCESAR Y FILTRAR COLECCIONES
// ============================================================
template <typename T, typename Predicado>
vector<T> filtrarElementos(const vector<T>& lista, Predicado criterio) {
    vector<T> resultado;
    for (const auto& elem : lista) {
        if (criterio(elem)) {
            resultado.push_back(elem);
        }
    }
    return resultado;
}

// ============================================================
// CLASE BASE POLIMORFICA: CUENTA BANCARIA
// ============================================================
class CuentaBancaria {
protected:
    string numeroCuenta;
    string tipoCuenta;
    string moneda;
    double saldo;
    double deuda;
    double tasaInteres; // Porcentaje (0.45% a 26.50%)
    vector<string> titulares; // Soporta cuentas individuales y mancomunadas
    vector<Movimiento> movimientos;

public:
    CuentaBancaria(string num, string tipo, string mon, double saldoIni, double tasa)
        : numeroCuenta(move(num)), tipoCuenta(move(tipo)), moneda(move(mon)),
          saldo(saldoIni), deuda(0.0), tasaInteres(tasa) {}

    virtual ~CuentaBancaria() = default;

    void agregarTitular(const string& nombre) {
        titulares.push_back(nombre);
    }

    bool esMancomunada() const { return titulares.size() > 1; }
    string getNumero() const { return numeroCuenta; }
    string getTipo() const { return tipoCuenta; }
    string getMoneda() const { return moneda; }
    double getSaldo() const { return saldo; }
    double getDeuda() const { return deuda; }
    double getTasaInteres() const { return tasaInteres; }

    // Polimorfismo puro: cada cuenta calcula su interes segun su naturaleza
    virtual double calcularInteres() const = 0;

    // Transferencia nacional: 0.5%-4% (Soles) | 0.21%-0.35% (Dolares)
    void transferirNacional(double monto, double tasaComision, const string& fecha) {
        bool valida = (moneda == "PEN" && tasaComision >= 0.5 && tasaComision <= 4.0) ||
                      (moneda == "USD" && tasaComision >= 0.21 && tasaComision <= 0.35);
        if (!valida) {
            cout << "  [!] Comision fuera de rango para moneda " << moneda << endl;
            return;
        }
        double comision = monto * (tasaComision / 100.0);
        double total = monto + comision;
        if (saldo >= total) {
            saldo -= total;
            movimientos.emplace_back(fecha, "Transferencia nacional (com. " + to_string(tasaComision).substr(0, 4) + "%)", -total, moneda);
        } else {
            cout << "  [!] Saldo insuficiente en cuenta " << numeroCuenta << endl;
        }
    }

    // Prestamo personal: 8.55% a 11.25% sujeto a calificacion crediticia
    void solicitarPrestamoPersonal(double monto, const string& calificacion, const string& fecha) {
        double tasaPrestamo = 11.25;
        if (calificacion == "A") tasaPrestamo = 8.55;
        else if (calificacion == "B") tasaPrestamo = 9.90;
        else tasaPrestamo = 11.25;

        double deudaGenerada = monto * (1.0 + tasaPrestamo / 100.0);
        saldo += monto;
        deuda += deudaGenerada;
        movimientos.emplace_back(fecha, "Prestamo personal (Calif. " + calificacion + ", " + to_string(tasaPrestamo).substr(0, 4) + "%)", monto, moneda);
    }

    // Adelantar o liquidar deuda
    void pagarDeuda(double monto, const string& fecha, bool liquidarTotal = false) {
        double pago = liquidarTotal ? deuda : min(monto, deuda);
        if (pago <= 0.0) return;

        if (saldo >= pago) {
            saldo -= pago;
            deuda -= pago;
            string desc = liquidarTotal ? "Liquidacion total de deuda" : "Adelanto de pago de deuda";
            movimientos.emplace_back(fecha, desc, -pago, moneda);
        } else {
            cout << "  [!] Saldo insuficiente para pagar deuda en " << numeroCuenta << endl;
        }
    }

    // Compra con tarjeta (sobreescrita en TarjetaCredito)
    virtual void realizarCompra(double monto, double tasaCompra, const string& fecha) {
        (void)tasaCompra;
        if (saldo >= monto) {
            saldo -= monto;
            movimientos.emplace_back(fecha, "Compra con debito", -monto, moneda);
        }
    }

    // Mostrar estado de cuenta hasta una fecha de corte usando LAMBDA
    void mostrarEstadoCuenta(const string& fechaCorte) const {
        cout << "  ----------------------------------------------------------------------\n";
        cout << "  Cuenta: " << numeroCuenta << " | Tipo: " << tipoCuenta
             << (esMancomunada() ? " [MANCOMUNADA]" : " [INDIVIDUAL]") << "\n";
        cout << "  Titular(es): ";
        for (size_t i = 0; i < titulares.size(); ++i) {
            cout << titulares[i] << (i + 1 < titulares.size() ? ", " : "");
        }
        cout << "\n  Moneda: " << moneda
             << " | Tasa base: " << fixed << setprecision(2) << tasaInteres << "%"
             << " | Interes proyectado: " << moneda << " " << calcularInteres() << "\n";
        cout << "  Saldo actual: " << moneda << " " << saldo
             << " | Deuda vigente: " << moneda << " " << deuda << "\n";
        cout << "  Movimientos con corte al " << fechaCorte << ":\n";

        // Uso de Template + Lambda para filtrar movimientos por fecha de corte
        auto movsFiltrados = filtrarElementos(movimientos, [&fechaCorte](const Movimiento& m) {
            return m.fecha <= fechaCorte;
        });

        if (movsFiltrados.empty()) {
            cout << "    (Sin movimientos registrados hasta la fecha de corte)\n";
        } else {
            for (const auto& m : movsFiltrados) {
                cout << m << "\n";
            }
        }
    }
};

// ============================================================
// CLASES DERIVADAS: TIPOS DE CUENTAS Y TARJETAS
// ============================================================
class CuentaAhorro : public CuentaBancaria {
public:
    CuentaAhorro(string num, string mon, double saldoIni)
        : CuentaBancaria(move(num), "Ahorro", move(mon), saldoIni, 0.45) {}
    double calcularInteres() const override { return saldo * (tasaInteres / 100.0); }
};

class CuentaJoven : public CuentaBancaria {
public:
    CuentaJoven(string num, string mon, double saldoIni)
        : CuentaBancaria(move(num), "Joven", move(mon), saldoIni, 1.50) {}
    double calcularInteres() const override { return saldo * (tasaInteres / 100.0); }
};

class CuentaPluss : public CuentaBancaria {
public:
    CuentaPluss(string num, string mon, double saldoIni)
        : CuentaBancaria(move(num), "Pluss", move(mon), saldoIni, 3.75) {}
    double calcularInteres() const override { return saldo * (tasaInteres / 100.0); }
};

class CuentaEmpresarial : public CuentaBancaria {
public:
    CuentaEmpresarial(string num, string mon, double saldoIni)
        : CuentaBancaria(move(num), "Empresarial", move(mon), saldoIni, 5.20) {}
    double calcularInteres() const override { return saldo * (tasaInteres / 100.0); }
};

class TarjetaCredito : public CuentaBancaria {
    double lineaCredito;
public:
    TarjetaCredito(string num, string mon, double linea)
        : CuentaBancaria(move(num), "Tarjeta de Credito", move(mon), linea, 26.50),
          lineaCredito(linea) {}

    // Compras con tarjeta de credito: interes de 15% a 25%
    void realizarCompra(double monto, double tasaCompra, const string& fecha) override {
        if (tasaCompra < 15.0 || tasaCompra > 25.0) {
            cout << "  [!] Tasa de compra con TC fuera de rango (15% - 25%)\n";
            return;
        }
        if (saldo >= monto) {
            double costoTotal = monto * (1.0 + tasaCompra / 100.0);
            saldo -= monto;
            deuda += costoTotal;
            movimientos.emplace_back(fecha, "Compra TC (int. " + to_string(tasaCompra).substr(0, 4) + "%)", -monto, moneda);
        }
    }

    double calcularInteres() const override {
        return deuda * (tasaInteres / 100.0);
    }
};

// ============================================================
// PATRON BUILDER: CONSTRUCTOR EXTENSIBLE DE CUENTAS
// ============================================================
class CuentaBuilder {
    shared_ptr<CuentaBancaria> cuenta;
public:
    CuentaBuilder& crearAhorro(const string& num, const string& mon, double saldo) {
        cuenta = make_shared<CuentaAhorro>(num, mon, saldo);
        return *this;
    }
    CuentaBuilder& crearJoven(const string& num, const string& mon, double saldo) {
        cuenta = make_shared<CuentaJoven>(num, mon, saldo);
        return *this;
    }
    CuentaBuilder& crearPluss(const string& num, const string& mon, double saldo) {
        cuenta = make_shared<CuentaPluss>(num, mon, saldo);
        return *this;
    }
    CuentaBuilder& crearEmpresarial(const string& num, const string& mon, double saldo) {
        cuenta = make_shared<CuentaEmpresarial>(num, mon, saldo);
        return *this;
    }
    CuentaBuilder& crearTarjetaCredito(const string& num, const string& mon, double linea) {
        cuenta = make_shared<TarjetaCredito>(num, mon, linea);
        return *this;
    }
    CuentaBuilder& conTitular(const string& nombre) {
        if (cuenta) cuenta->agregarTitular(nombre);
        return *this;
    }
    shared_ptr<CuentaBancaria> build() { return cuenta; }
};

// ============================================================
// CLASE CLIENTE (con sobrecarga de estado de cuenta)
// ============================================================
class Cliente {
    string nombre;
    string dni;
    vector<shared_ptr<CuentaBancaria>> cuentas;

public:
    Cliente(string nom, string doc) : nombre(move(nom)), dni(move(doc)) {}

    string getNombre() const { return nombre; }

    void asociarCuenta(const shared_ptr<CuentaBancaria>& cta) {
        cuentas.push_back(cta);
    }

    // Sobrecarga 1: Estado de cuenta GLOBAL con fecha de corte
    void solicitarEstadoCuenta(const string& fechaCorte) const {
        cout << "\n========================================================================\n";
        cout << " ESTADO DE CUENTA GLOBAL | Cliente: " << nombre << " (DNI: " << dni << ")\n";
        cout << " Fecha de corte: " << fechaCorte << "\n";
        cout << "========================================================================\n";
        for (const auto& cta : cuentas) {
            cta->mostrarEstadoCuenta(fechaCorte);
        }
    }

    // Sobrecarga 2: Estado de cuenta POR TIPO DE CUENTA usando Template + Lambda
    void solicitarEstadoCuenta(const string& fechaCorte, const string& tipoFiltro) const {
        cout << "\n========================================================================\n";
        cout << " ESTADO DE CUENTA POR TIPO (" << tipoFiltro << ") | Cliente: " << nombre << "\n";
        cout << " Fecha de corte: " << fechaCorte << "\n";
        cout << "========================================================================\n";

        auto filtradas = filtrarElementos(cuentas, [&tipoFiltro](const shared_ptr<CuentaBancaria>& c) {
            return c->getTipo() == tipoFiltro;
        });

        if (filtradas.empty()) {
            cout << "  No se encontraron cuentas del tipo: " << tipoFiltro << "\n";
        } else {
            for (const auto& cta : filtradas) {
                cta->mostrarEstadoCuenta(fechaCorte);
            }
        }
    }
};

// ============================================================
// FUNCION PRINCIPAL
// ============================================================
int main() {
    Cliente cliente1("Carlos Mendoza", "72849102");
    Cliente cliente2("Lucia Paredes", "74120589");

    CuentaBuilder builder;

    // 1. Creacion de cuentas variadas mediante Builder
    auto ctaAhorro = builder.crearAhorro("AH-001", "PEN", 5000.00)
                            .conTitular(cliente1.getNombre())
                            .build();

    auto ctaEmpresarialMancomunada = builder.crearEmpresarial("EMP-900", "USD", 12000.00)
                                            .conTitular(cliente1.getNombre())
                                            .conTitular(cliente2.getNombre()) // Cuenta mancomunada
                                            .build();

    auto tarjetaCred = builder.crearTarjetaCredito("TC-4550", "PEN", 8000.00)
                              .conTitular(cliente1.getNombre())
                              .build();

    // Asociar multiples cuentas a los clientes
    cliente1.asociarCuenta(ctaAhorro);
    cliente1.asociarCuenta(ctaEmpresarialMancomunada);
    cliente1.asociarCuenta(tarjetaCred);
    cliente2.asociarCuenta(ctaEmpresarialMancomunada);

    // 2. Operaciones financieras
    ctaAhorro->transferirNacional(1000.00, 1.5, "2026-11-05");             // Soles: 0.5% - 4%
    ctaAhorro->solicitarPrestamoPersonal(2000.00, "A", "2026-11-10");      // Calif. A: 8.55%
    ctaAhorro->pagarDeuda(1000.00, "2026-11-18", false);                   // Adelanto de deuda

    ctaEmpresarialMancomunada->transferirNacional(2500.00, 0.25, "2026-11-12"); // Dolares: 0.21% - 0.35%

    tarjetaCred->realizarCompra(1500.00, 18.0, "2026-11-08");              // Compra TC: 15% - 25%
    tarjetaCred->pagarDeuda(0.0, "2026-11-22", true);                      // Liquidacion total

    // 3. Consultas de estado de cuenta (Global y por Tipo, con fecha de corte)
    cliente1.solicitarEstadoCuenta("2026-11-20");                          // Corte al 20 (excluye mov. del 22)
    cliente1.solicitarEstadoCuenta("2026-11-24", "Tarjeta de Credito");    // Filtrado por tipo al 24

    return 0;
}