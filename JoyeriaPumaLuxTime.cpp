/* UNIVERSIDAD NACIONAL AUTÓNOMA DE HONDURAS
FACULTAD DE CIENCIAS ECONÓMICAS, ADMINISTRATIVAS Y CONTABLES
DEPARTAMENTO DE INFORMÁTICA
DIA 044 Programación Básica
Proyecto: JOYERIA PUMA LUX TIME
Integrantes: Aldo Misael Flores Amador
No. Cuenta: 20141902108 
Grupo N°5
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h> // PARA CONFIGURAR EL IDIOMA ESPAÑOL

using namespace std;

// Constante para la tasa de cambio
const double TASA_CAMBIO = 26.75;

// Estructura para manejar los productos
struct Producto {
    int id;
    string categoria;
    string nombre;
    double precio;
    int inventario;
    int puntosBase;
    int unidadesVendidas; // Para estadísticas
};

int main() {
    // 1. Inicialización de Productos (Índices del 0 al 11 para los 12 productos)
    Producto productos[12] = {
        {1, "Relojes", "Reloj Clasico Puma Classic", 1450.00, 12, 80, 0},
        {2, "Relojes", "Reloj Deportivo Puma Sport", 1900.00, 10, 95, 0},
        {3, "Relojes", "Smartwatch Puma Smart X", 3600.00, 8, 140, 0},
        {4, "Cadenas", "Cadena acero (delgada)", 780.00, 18, 55, 0},
        {5, "Cadenas", "Cadena acero (gruesa)", 1150.00, 12, 75, 0},
        {6, "Cadenas", "Cadena bano oro", 1650.00, 10, 90, 0},
        {7, "Pulseras", "Pulsera cuero", 420.00, 22, 25, 0},
        {8, "Pulseras", "Pulsera acero", 650.00, 20, 35, 0},
        {9, "Pulseras", "Pulsera bano oro", 980.00, 14, 60, 0},
        {10, "Sets", "Set cadena + pulsera (acero)", 1350.00, 10, 110, 0},
        {11, "Sets", "Set cadena + pulsera (bano oro)", 2200.00, 8, 160, 0},
        {12, "Accesorios", "Aretes (par)", 350.00, 30, 20, 0}
    };

    double gananciaRelojes = 0, gananciaCadenas = 0, gananciaPulseras = 0;
    double gananciaSets = 0, gananciaAccesorios = 0;

    double totalDescuentos = 0;
    double totalISV = 0;
    double totalGeneral = 0;

    int conteoEfectivo = 0, conteoTransferencia = 0;

    char continuar = 'S';

    cout << fixed << setprecision(2);

    while (continuar == 'S' || continuar == 's') {

        int tipoCliente, edad;
        char genero;

        cout << "\n============================================\n";
        cout << "   JOYERIA Y ACCESORIOS \"PUMA LUX TIME\"     \n";
        cout << "============================================\n";

        // Datos del cliente
        cout << "Tipo de cliente (1-Regular, 2-VIP, 3-Mayorista): ";
        cin >> tipoCliente;
        cout << "Genero (H/M): ";
        cin >> genero;
        cout << "Edad: ";
        cin >> edad;

        int carrito[12] = {0};
        char seguir = 'S';

        while (seguir == 'S' || seguir == 's') {

            cout << "\n--- PRODUCTOS ---\n";
            for (int i = 0; i < 12; i++) {
                cout << productos[i].id << ". " << productos[i].nombre
                     << " | Lps." << productos[i].precio
                     << " | Stock: " << productos[i].inventario << "\n";
            }

            int op, cant;

            cout << "Seleccione producto: ";
            cin >> op;

            if (op < 1 || op > 12) {
                cout << "Codigo invalido\n";
                continue;
            }

            int idx = op - 1;

            if (productos[idx].inventario <= 0) {
                cout << "Agotado\n";
                continue;
            }

            cout << "Cantidad (disp " << productos[idx].inventario << "): ";
            cin >> cant;

            while (cant <= 0 || cant > productos[idx].inventario) {
                cout << "Cantidad invalida o stock insuficiente: ";
                cin >> cant;
            }

            carrito[idx] += cant;
            productos[idx].inventario -= cant;
            productos[idx].unidadesVendidas += cant;

            cout << "Agregado\n";

            cout << "Agregar otro? (S/N): ";
            cin >> seguir;
        }

        double subtotal = 0, descuento = 0;
        int puntosTotalesCliente = 0; // CORRECCIÓN 1: Variable para acumular puntos del cliente actual

        cout << "\n========= FACTURA =========\n";

        bool combo = (carrito[0] > 0 && carrito[3] > 0);

        for (int i = 0; i < 12; i++) {

            if (carrito[i] > 0) {

                int c = carrito[i];
                double precio = productos[i].precio * c;
                double desc = 0;

                // Descuento Tipo de cliente
                if (tipoCliente == 1 && productos[i].categoria == "Pulseras") desc += 0.05;
                if (tipoCliente == 2 && productos[i].categoria == "Relojes") desc += 0.10;
                if (tipoCliente == 3 && (productos[i].categoria == "Cadenas" || productos[i].categoria == "Sets")) desc += 0.12;

                // Descuento por género
                if ((genero == 'M' || genero == 'm') && productos[i].categoria == "Pulseras") desc += 0.08;
                if ((genero == 'H' || genero == 'h') && productos[i].categoria == "Relojes") desc += 0.05;

                // Descuento tercera edad
                if (edad >= 60) desc += 0.10;

                // Promoción Combo Elegante
                if (combo && (productos[i].id == 1 || productos[i].id == 4)) desc += 0.06;

                // CORRECCIÓN 2: Promoción Set Premium (5% adicional solo al set)
                if (productos[i].categoria == "Sets") desc += 0.05;

                // Promoción por volumen
                if (c > 2) desc += 0.04;

                double descVal = precio * desc;
                double neto = precio - descVal;

                subtotal += precio;
                descuento += descVal;
                puntosTotalesCliente += (productos[i].puntosBase * c); // CORRECCIÓN 1: Suma de puntos acumulados

                if (productos[i].categoria == "Relojes") gananciaRelojes += neto;
                if (productos[i].categoria == "Cadenas") gananciaCadenas += neto;
                if (productos[i].categoria == "Pulseras") gananciaPulseras += neto;
                if (productos[i].categoria == "Sets") gananciaSets += neto;
                if (productos[i].categoria == "Accesorios") gananciaAccesorios += neto;

                cout << productos[i].nombre << " x" << c
                     << " | Lps." << precio
                     << " | Desc: Lps." << descVal << "\n";
            }
        }

        double total = subtotal - descuento;
        double isv = total * 0.15;
        double finalLps = total + isv;
        double finalUSD = finalLps / TASA_CAMBIO; // CORRECCIÓN 3: Conversión a dólares en factura

        totalDescuentos += descuento;
        totalISV += isv;
        totalGeneral += finalLps;

        cout << "\n------------------------------------";
        cout << "\nSubtotal bruto:   Lps." << subtotal;
        cout << " \nTotal Descuentos: Lps." << descuento;
        cout << " \nISV (15%):        Lps." << isv;
        cout << "\nTOTAL A PAGAR:    Lps." << finalLps;
        cout << "\nTOTAL A PAGAR:    USD " << finalUSD; // Impresión requerida en dólares
        cout << "\nPUNTOS TOTALES:   " << puntosTotalesCliente << " pts"; // Impresión requerida de puntos
        cout << "\n------------------------------------\n";

        // ================= METODOS DE PAGO =================
        cout << "\n====================================\n";
        cout << "         METODOS DE PAGO            \n";
        cout << "====================================\n";
        cout << "Opcion | Descripcion\n";
        cout << "------------------------------------\n";
        cout << "1      | Efectivo (Calcula cambio)\n";
        cout << "2      | Transferencia (Comprobante + bancos)\n";
        cout << "====================================\n";

        int pago;
        cout << "Seleccione metodo: ";
        cin >> pago;

        if (pago == 1) {
            conteoEfectivo++;
            double rec;
            cout << "Monto recibido: Lps.";
            cin >> rec;

            while (rec < finalLps) {
                cout << "Monto insuficiente. Ingrese una cantidad mayor o igual a " << finalLps << ": Lps.";
                cin >> rec;
            }

            cout << "Cambio a entregar: Lps." << rec - finalLps << "\n";
        }
        else {
            conteoTransferencia++;
            string ref, b1, b2;

            cout << "Comprobante: ";
            cin >> ref;

            cout << "Banco origen: ";
            cin >> b1;

            cout << "Banco destino: ";
            cin >> b2;

            cout << "Pago registrado con exito por Lps." << finalLps << "\n";
        }

        cout << "\n¿Desea ingresar otro cliente? (S/N): ";
        cin >> continuar;
    }

    // ================= ESTADISTICAS FINAL =================

    int max = -1, min = 999999;
    string mas = "Ninguno", menos = "Ninguno";

    for (int i = 0; i < 12; i++) {
        if (productos[i].unidadesVendidas > max) {
            max = productos[i].unidadesVendidas;
            mas = productos[i].nombre;
        }
        if (productos[i].unidadesVendidas < min) {
            min = productos[i].unidadesVendidas;
            menos = productos[i].nombre;
        }
    }

    cout << "\n========== REPORTE FINAL DE VENTAS ==========\n";
    cout << "1. Producto mas vendido: " << mas << " (" << max << " unidades)\n";
    cout << "2. Producto menos vendido: " << menos << " (" << min << " unidades)\n";
    cout << "3. Ganancia neta por categoria:\n";
    cout << "   - Relojes:    Lps. " << gananciaRelojes << "\n";
    cout << "   - Cadenas:    Lps. " << gananciaCadenas << "\n";
    cout << "   - Pulseras:   Lps. " << gananciaPulseras << "\n";
    cout << "   - Sets:       Lps. " << gananciaSets << "\n";
    cout << "   - Accesorios: Lps. " << gananciaAccesorios << "\n";
    cout << "4. Total descuentos aplicados: Lps. " << totalDescuentos << "\n";
    cout << "5. Total ISV recaudado:        Lps. " << totalISV << "\n";
    cout << "6. Total general vendido:\n";
    cout << "   - En Lempiras: Lps. " << totalGeneral << "\n";
    cout << "   - En Dolares:  USD  " << (totalGeneral / TASA_CAMBIO) << "\n"; // CORRECCIÓN 3: Requerido en dólares en reporte global
    cout << "7. Metodo de pago mas utilizado: ";
    if (conteoEfectivo == 0 && conteoTransferencia == 0) {
        cout << "No hubo ventas hoy.\n";
    } else if (conteoEfectivo == conteoTransferencia) {
        cout << "Empate (Ambos metodos se utilizaron por igual)\n";
    } else {
        cout << (conteoEfectivo > conteoTransferencia ? "Efectivo" : "Transferencia") << "\n";
    }
    cout << "=============================================\n";

    return 0;
}