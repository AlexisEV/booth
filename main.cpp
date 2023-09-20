#include <bitset>
#include <iostream>

using namespace std;

const int n =8; // cabmiar num bits

// Funcion convertir decimal a binario
bitset<n> decimalABinario(int num) { return bitset<n>(num); }

// Cambio de signo complemento2
bitset<n> complementoDos(bitset<n> b) {
  b.flip(); // Complemento-1
  // Suma 1 al resultado.
  int acarreo = 1;
  for (int i = 0; i < n; i++) {
    int suma = b[i] + acarreo;
    b[i] = suma % 2;
    acarreo = suma / 2;
  }
  return b;
}

//Suma
bitset<n> sumaBinaria(bitset<n> a, bitset<n> b) {
  bitset<n> resultado;
  int acarreo = 0;
  for (int i = 0; i < n; i++) {
    int suma = a[i] + b[i] + acarreo;
    resultado[i] = suma % 2;
    acarreo = suma / 2;
  }
  return resultado;
}

//Resta complemento
bitset<n> restaBinaria(bitset<n> a, bitset<n> b) {
  return sumaBinaria(a, complementoDos(b));
}

//Corrimiento 
bitset<n> corrimientoAritmetico(bitset<n> b) {
  bool signo = b[n - 1]; //signo.
  b >>= 1;
  b[n - 1] = signo; // recolocando bit signo.
  return b;
}

// Multiplicacion Booth
bitset<2 * n> multiplicacionBooth(int multiplicando, int multiplicador) {
  bitset<n> M = decimalABinario(multiplicando);
  bitset<n> Q = decimalABinario(multiplicador);

  bitset<n> A;
  bitset<1> Q_anterior = 0;

  cout << "Inicial: A = " << A << ", Q = " << Q
       << ", Q-1 = " << Q_anterior[0] << endl;

  for (int i = 0; i < n; i++) {
    cout << "\nCiclo " << i + 1 << ":" << endl;

    if (Q[0] == 1 && Q_anterior[0] == 0) {
      A = restaBinaria(A, M);
      cout << "Operación: A = A - M" << endl;
    } else if (Q[0] == 0 && Q_anterior[0] == 1) {
      A = sumaBinaria(A, M);
      cout << "Operación: A = A + M" << endl;
    } else {
      cout << "Operación: no hay cambio" << endl;
    }
    
    // Corrimiento a la derecha (A, Q, Q_anterior)
    Q_anterior[0] = Q[0];
    Q >>= 1;
    Q[n - 1] = A[0];
    A = corrimientoAritmetico(A);

    cout << "Después del corrimiento: A = " << A << ", Q = " << Q
         << ", Q anterior = " << Q_anterior[0] << endl;
  }

  bitset<2 * n> resultado;
  for (int i = 0; i < n; i++) {
    resultado[i] = Q[i];
    resultado[n + i] = A[i];
  }

  return resultado;
}

int main() {
  int multiplicando, multiplicador;
  cout << "Introduce el multiplicando: ";
  cin >> multiplicando;
  cout << "Introduce el multiplicador: ";
  cin >> multiplicador;

  bitset<2 *n> resultado = multiplicacionBooth(multiplicando, multiplicador);
  cout << "\nResultado: " << resultado.to_string() << endl;

  return 0;
}
