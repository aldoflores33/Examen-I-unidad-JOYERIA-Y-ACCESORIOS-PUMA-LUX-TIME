#include <iostream>
#include <string>
using namespace std;

// Variables globales básicas
string nombreCliente, generoCliente;
int edadCliente, puntosAcumulados;
int opcion;

// Inventario inicial
int cantidadAlgodones = 20, cantidadGasas = 20, cantidadPovidine = 20;
int cantidadPanadol = 20, cantidadAcetaminofen = 20, cantidadVitaminasB = 20;

// Totales
float totalVentaLibre = 0;
float totalVentaControlada = 0;

// Prototipos
void registrarCliente();
void menuVentaLibre();
void menuVentaControlada();
void menuInventario();
void mostrarFactura();

int main() {
    registrarCliente();

    do {
        cout << "\n===== FARMACIA LA TOXICA =====\n";
        cout << "1. Venta libre\n";
        cout << "2. Venta controlada\n";
        cout << "3. Inventario\n";
        cout << "4. Factura\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuVentaLibre(); break;
            case 2: menuVentaControlada(); break;
            case 3: menuInventario(); break;
            case 4: mostrarFactura(); break;
            case 5: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion no valida.\n";
        }

    } while (opcion != 5);

    return 0;
}

// Módulos iniciales temporales
void registrarCliente() {
    cout << "Modulo cliente pendiente de desarrollo.\n";
}

void menuVentaLibre() {
    cout << "Modulo venta libre pendiente de desarrollo.\n";
}

void menuVentaControlada() {
    cout << "Modulo venta controlada pendiente de desarrollo.\n";
}

void menuInventario() {
    cout << "Modulo inventario pendiente de desarrollo.\n";
}

void mostrarFactura() {
    cout << "Modulo factura pendiente de desarrollo.\n";
}

/*
git add .
git commit -m "Crea estructura base del sistema farmacia"
git push origin develop

*/