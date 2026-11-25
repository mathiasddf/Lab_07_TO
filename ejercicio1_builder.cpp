#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// INTERFAZ BASE DE COMPONENTES
class item {
public:
    virtual ~item() {}
    virtual string GetName() { return ""; }
    virtual float GetPrice() { return 0.0f; }
    virtual void GetConfiguration() {}
};

// 1. CPU / PROCESADORES (Base + Nuevos modelos)
class Processor : public item {
public:
    virtual string GetName() override { return ""; }
    virtual float GetPrice() override { return 0.0f; }
    virtual void GetConfiguration() override {}
};

class IntelI5 : public Processor {
public:
    string GetName() override { return "CPU Intel i5"; }
    float GetPrice() override { return 3000.00f; }
    void GetConfiguration() override {
        cout << "1.50 GHz, hasta 2.0 GHz con turbo, 2 cores, 4 threads, 8 MB cache" << endl;
    }
};

class IntelI7 : public Processor {
public:
    string GetName() override { return "CPU Intel i7"; }
    float GetPrice() override { return 4700.00f; }
    void GetConfiguration() override {
        cout << "1.60 GHz, hasta 1.99 GHz, 9na Gen, 4 cores, 8 threads, 16 MB cache" << endl;
    }
};

class IntelI9 : public Processor {
public:
    string GetName() override { return "CPU Intel i9"; }
    float GetPrice() override { return 6200.00f; }
    void GetConfiguration() override {
        cout << "2.40 GHz, hasta 5.0 GHz, 13va Gen, 16 cores, 24 threads, 30 MB cache" << endl;
    }
};

class AMDRyzen7 : public Processor {
public:
    string GetName() override { return "CPU AMD Ryzen 7"; }
    float GetPrice() override { return 4300.00f; }
    void GetConfiguration() override {
        cout << "3.20 GHz, hasta 4.75 GHz, Serie 7000, 8 cores, 16 threads, 16 MB cache" << endl;
    }
};

// 2. ALMACENAMIENTO (Base)
class Drive : public item {
public:
    virtual string GetName() override { return ""; }
    virtual float GetPrice() override { return 0.0f; }
    virtual void GetConfiguration() override {}
};

class HDD : public Drive {
public:
    string GetName() override { return "Hard Disk Drive (HDD)"; }
    float GetPrice() override { return 150.00f; }
    void GetConfiguration() override {
        cout << "Capacidad: 1 TB, transferencia de datos 1050 Mbits/s" << endl;
    }
};

class SSD : public Drive {
public:
    string GetName() override { return "Solid State Drive (SSD)"; }
    float GetPrice() override { return 270.00f; }
    void GetConfiguration() override {
        cout << "Capacidad: 512 GB NVMe, transferencia de datos 1800 Mbits/s" << endl;
    }
};

// 3. PANTALLA / MONITOR (Base + Monitor Plasma)
class DisplayType : public item {
public:
    virtual string GetName() override { return ""; }
    virtual float GetPrice() override { return 0.0f; }
    virtual void GetConfiguration() override {}
};

class Normal : public DisplayType {
public:
    string GetName() override { return "Pantalla Normal (No tactil)"; }
    float GetPrice() override { return 195.00f; }
    void GetConfiguration() override {
        cout << "15.6 pulgadas FHD (1920 x 1080), panel plano IPS, 60 Hz" << endl;
    }
};

class MonitorPlasma : public DisplayType {
public:
    string GetName() override { return "Monitor Plasma"; }
    float GetPrice() override { return 850.00f; }
    void GetConfiguration() override {
        cout << "27 pulgadas Plasma Full HD (1920 x 1080), alto contraste, salida HDMI" << endl;
    }
};

// 4. MARCAS (Nuevo)
class Marca : public item {
public:
    virtual string GetName() override { return ""; }
    virtual float GetPrice() override { return 0.0f; }
    virtual void GetConfiguration() override {}
};

class MarcaLenovo : public Marca {
public:
    string GetName() override { return "Marca"; }
    float GetPrice() override { return 200.00f; }
    void GetConfiguration() override {
        cout << "Lenovo ThinkPad Series - Chasis reforzado, garantia 2 anos" << endl;
    }
};

class MarcaHP : public Marca {
public:
    string GetName() override { return "Marca"; }
    float GetPrice() override { return 180.00f; }
    void GetConfiguration() override {
        cout << "HP Pavilion Series - Diseno ultradelgado, garantia 1 ano" << endl;
    }
};

class MarcaDell : public Marca {
public:
    string GetName() override { return "Marca"; }
    float GetPrice() override { return 250.00f; }
    void GetConfiguration() override {
        cout << "Dell XPS Series - Acabado en aluminio CNC, garantia 2 anos" << endl;
    }
};

// 5. COLORES (Nuevo)
class Color : public item {
public:
    virtual string GetName() override { return ""; }
    virtual float GetPrice() override { return 0.0f; }
    virtual void GetConfiguration() override {}
};

class ColorNegro : public Color {
public:
    string GetName() override { return "Color"; }
    float GetPrice() override { return 0.00f; }
    void GetConfiguration() override {
        cout << "Negro Mate (acabado antihuellas estandar)" << endl;
    }
};

class ColorPlata : public Color {
public:
    string GetName() override { return "Color"; }
    float GetPrice() override { return 50.00f; }
    void GetConfiguration() override {
        cout << "Plata Metalico (aluminio anodizado)" << endl;
    }
};

class ColorAzul : public Color {
public:
    string GetName() override { return "Color"; }
    float GetPrice() override { return 75.00f; }
    void GetConfiguration() override {
        cout << "Azul Medianoche (edicion especial)" << endl;
    }
};

// 6. MEMORIA RAM (Nuevo - Figura 2)
class MemoriaRAM : public item {
public:
    virtual string GetName() override { return ""; }
    virtual float GetPrice() override { return 0.0f; }
    virtual void GetConfiguration() override {}
};

class RAM8GB : public MemoriaRAM {
public:
    string GetName() override { return "Memoria RAM"; }
    float GetPrice() override { return 140.00f; }
    void GetConfiguration() override {
        cout << "8 GB DDR4 3200 MHz (Single Channel)" << endl;
    }
};

class RAM16GB : public MemoriaRAM {
public:
    string GetName() override { return "Memoria RAM"; }
    float GetPrice() override { return 280.00f; }
    void GetConfiguration() override {
        cout << "16 GB DDR5 4800 MHz (Dual Channel)" << endl;
    }
};

class RAM32GB : public MemoriaRAM {
public:
    string GetName() override { return "Memoria RAM"; }
    float GetPrice() override { return 540.00f; }
    void GetConfiguration() override {
        cout << "32 GB DDR5 5200 MHz (Dual Channel)" << endl;
    }
};

// 7. IMPRESORAS (Nuevo)
class Impresora : public item {
public:
    virtual string GetName() override { return ""; }
    virtual float GetPrice() override { return 0.0f; }
    virtual void GetConfiguration() override {}
};

class ImpresoraEpson : public Impresora {
public:
    string GetName() override { return "Impresora Multifuncional"; }
    float GetPrice() override { return 680.00f; }
    void GetConfiguration() override {
        cout << "Epson EcoTank L3250 - Sistema continuo Wi-Fi, impresion a color" << endl;
    }
};

class ImpresoraHPLaser : public Impresora {
public:
    string GetName() override { return "Impresora Laser"; }
    float GetPrice() override { return 920.00f; }
    void GetConfiguration() override {
        cout << "HP LaserJet Pro - Impresion monocromatica rapida, Ethernet/Wi-Fi" << endl;
    }
};

// 8. OTROS ACCESORIOS / PERIFERICOS (Nuevo)
class OtrosAccesorios : public item {
public:
    virtual string GetName() override { return ""; }
    virtual float GetPrice() override { return 0.0f; }
    virtual void GetConfiguration() override {}
};

class MouseInalambrico : public OtrosAccesorios {
public:
    string GetName() override { return "Accesorio - Mouse"; }
    float GetPrice() override { return 85.00f; }
    void GetConfiguration() override {
        cout << "Logitech M720 Inalambrico Bluetooth/USB, ergonomico" << endl;
    }
};

class TecladoMecanico : public OtrosAccesorios {
public:
    string GetName() override { return "Accesorio - Teclado"; }
    float GetPrice() override { return 210.00f; }
    void GetConfiguration() override {
        cout << "Teclado mecanico RGB compacto 75%, switches tactiles" << endl;
    }
};

class CoolerLaptop : public OtrosAccesorios {
public:
    string GetName() override { return "Accesorio - Base Refrigerante"; }
    float GetPrice() override { return 95.00f; }
    void GetConfiguration() override {
        cout << "Base refrigerante con 4 ventiladores silenciosos y 2 puertos USB" << endl;
    }
};

// PRODUCTO: CLASE LAPTOP
class laptop {
public:
    ~laptop() {
        for (auto part : mLaptopParts) {
            delete part;
        }
        mLaptopParts.clear();
    }

    void AddParts(item* part) {
        mLaptopParts.push_back(part);
    }

    float GetCost() {
        float cost = 0.0f;
        for (auto part : mLaptopParts) {
            cost += part->GetPrice();
        }
        return cost;
    }

    void GetConfiguration() {
        for (size_t i = 0; i < mLaptopParts.size(); i++) {
            cout << "  - " << mLaptopParts[i]->GetName()
                 << " [S/. " << fixed << setprecision(2) << mLaptopParts[i]->GetPrice() << "] : ";
            mLaptopParts[i]->GetConfiguration();
        }
    }

private:
    vector<item*> mLaptopParts;
};

// BUILDER: CLASE LAPTOPBUILDER
class laptopBuilder {
public:
    // Opcion 1: Equipo Oficina / Estudiante
    laptop* opcion1() {
        laptop* lap = new laptop();
        lap->AddParts(new MarcaLenovo());
        lap->AddParts(new ColorNegro());
        lap->AddParts(new IntelI5());
        lap->AddParts(new RAM8GB());
        lap->AddParts(new Normal());
        lap->AddParts(new HDD());
        lap->AddParts(new MouseInalambrico());
        return lap;
    }

    // Opcion 2: Equipo Profesional con Monitor Plasma e Impresora
    laptop* opcion2() {
        laptop* lap = new laptop();
        lap->AddParts(new MarcaHP());
        lap->AddParts(new ColorPlata());
        lap->AddParts(new IntelI7());
        lap->AddParts(new RAM16GB());
        lap->AddParts(new MonitorPlasma());
        lap->AddParts(new SSD());
        lap->AddParts(new ImpresoraEpson());
        lap->AddParts(new MouseInalambrico());
        return lap;
    }

    // Opcion 3: Estacion de Trabajo Avanzada
    laptop* opcion3() {
        laptop* lap = new laptop();
        lap->AddParts(new MarcaDell());
        lap->AddParts(new ColorAzul());
        lap->AddParts(new IntelI9());
        lap->AddParts(new RAM32GB());
        lap->AddParts(new MonitorPlasma());
        lap->AddParts(new SSD());
        lap->AddParts(new ImpresoraHPLaser());
        lap->AddParts(new TecladoMecanico());
        lap->AddParts(new CoolerLaptop());
        return lap;
    }
};

// FUNCION PRINCIPAL
int main() {
    laptopBuilder cotizar;

    cout << "   SISTEMA DE COTIZACION DE EQUIPOS (PATRON BUILDER)" << endl;

    cout << "\n[OPCION 1] Laptop Lenovo Oficina\n";
    laptop* lenovo = cotizar.opcion1();
    lenovo->GetConfiguration();
    cout << ">>> PRECIO TOTAL: S/. " << fixed << setprecision(2) << lenovo->GetCost() << endl;

    cout << "\n[OPCION 2] Pack Profesional HP (con Monitor Plasma e Impresora)\n";
    laptop* hp = cotizar.opcion2();
    hp->GetConfiguration();
    cout << ">>> PRECIO TOTAL: S/. " << fixed << setprecision(2) << hp->GetCost() << endl;

    cout << "\n[OPCION 3] Estacion de Trabajo Dell (Gama Alta Completa)\n";
    laptop* dell = cotizar.opcion3();
    dell->GetConfiguration();
    cout << ">>> PRECIO TOTAL: S/. " << fixed << setprecision(2) << dell->GetCost() << endl;

    // Liberacion de memoria dinamica
    delete lenovo;
    delete hp;
    delete dell;

    return 0;
}