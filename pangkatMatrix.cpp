#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

int N;
typedef vector<vector<ll>> matrix;

// Matriks identitas untuk ukuran N x N
void identityMatrix(matrix& A, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                A[i][j] = 1;
            } else {
                A[i][j] = 0;
            }
        }
    }
}

// Fungsi untuk perkalian dua matriks A dan B menjadi matriks C
void multiplyMatrix(const matrix& A, const matrix& B, matrix& C) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] = (C[i][j] + (1LL * A[i][k] * B[k][j]) % MOD) % MOD;
            }
        }
    }
}

// Fungsi untuk menghitung pangkat matriks A^exp secara iteratif
void matrixPowerIterative(const matrix& A, matrix& result, int exp) {
    identityMatrix(result, N);

    matrix temp(N, vector<ll>(N));
    matrix base = A;

    while (exp > 0) {
        if (exp % 2 == 1) {
            multiplyMatrix(result, base, temp);
            result = temp;
        }
        multiplyMatrix(base, base, temp);
        base = temp;
        exp /= 2;
    }
}

// Fungsi untuk menghitung pangkat matriks A^exp secara rekursif
void matrixPowerRecursive(const matrix& A, matrix& result, int exp) {
    if (exp == 0) {
        identityMatrix(result, N);
        return;
    }
    if (exp == 1) {
        result = A;
        return;
    }
    matrix temp(N, vector<ll>(N, 0));
    matrixPowerRecursive(A, temp, exp / 2);
    multiplyMatrix(temp, temp, result);

    if (exp % 2 == 1) {
        matrix temp2(N, vector<ll>(N, 0));
        multiplyMatrix(result, A, temp2);
        result = temp2;
    }
}

// Fungsi untuk mencetak matriks
void printMatrix(const matrix& m) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    cout << "Masukkan ukuran matrix N*N : ";
    cin >> N;
    matrix A(N, vector<ll>(N)), hasil(N, vector<ll>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Matriks A: " << endl;
    printMatrix(A);

    int pangkat;
    cout << "Masukkan pangkat matrix: ";
    cin >> pangkat;

    int metode;
    cout << "Pilih metode (1 = iteratif, 2 = rekursif): ";
    cin >> metode;

    if (metode == 1) {
        matrixPowerIterative(A, hasil, pangkat);
    } else if (metode == 2) {
        matrixPowerRecursive(A, hasil, pangkat);
    } else {
        cout << "Pilihan metode tidak valid!" << endl;
        return 1;
    }

    cout << endl;
    cout << "Matriks A^" << pangkat << ": " << endl;
    printMatrix(hasil);
    cout << endl;

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Waktu eksekusi: " << duration.count() << " detik" << std::endl;

    return 0;
}
