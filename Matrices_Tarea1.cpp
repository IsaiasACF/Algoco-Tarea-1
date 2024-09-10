#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

/*** addMatrix
* Parametro 1: const vector<vector<int>>& A - Primera matriz para sumar.
* Parametro 2: const vector<vector<int>>& B - Segunda matriz para sumar.
* Parametro 3: vector<vector<int>>& C - Matriz resultado de la suma.
* Parametro 4: int size - Tamaño de las matrices cuadradas.
* Resumen: Realiza la suma de las matrices A y B, almacenando el resultado en la matriz C.
*/
void addMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}
/*** subtractMatrix
* Parametro 1: const vector<vector<int>>& A - Primera matriz para restar.
* Parametro 2: const vector<vector<int>>& B - Segunda matriz para restar.
* Parametro 3: vector<vector<int>>& C - Matriz resultado de la resta.
* Parametro 4: int size - Tamaño de las matrices cuadradas.
* Resumen: Realiza la resta de las matrices A y B, almacenando el resultado en la matriz C.
*/
void subtractMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
}
/*** strassen
* Parametro 1: const vector<vector<int>>& A - Primera matriz para multiplicar.
* Parametro 2: const vector<vector<int>>& B - Segunda matriz para multiplicar.
* Parametro 3: vector<vector<int>>& C - Matriz resultado de la multiplicacion.
* Parametro 4: int size - Tamaño de las matrices cuadradas.
* Resumen: Implementa el algoritmo de Strassen para multiplicar dos matrices cuadradas de manera recursiva.
*/
void strassen(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    vector<int> inner(newSize);
    vector<vector<int>> 
        a11(newSize, inner), a12(newSize, inner), a21(newSize, inner), a22(newSize, inner),
        b11(newSize, inner), b12(newSize, inner), b21(newSize, inner), b22(newSize, inner),
        c11(newSize, inner), c12(newSize, inner), c21(newSize, inner), c22(newSize, inner),
        p1(newSize, inner), p2(newSize, inner), p3(newSize, inner), p4(newSize, inner),
        p5(newSize, inner), p6(newSize, inner), p7(newSize, inner),
        temp1(newSize, inner), temp2(newSize, inner);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + newSize];
            a21[i][j] = A[i + newSize][j];
            a22[i][j] = A[i + newSize][j + newSize];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + newSize];
            b21[i][j] = B[i + newSize][j];
            b22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // p1 = (a11 + a22) * (b11 + b22)
    addMatrix(a11, a22, temp1, newSize);
    addMatrix(b11, b22, temp2, newSize);
    strassen(temp1, temp2, p1, newSize);

    // p2 = (a21 + a22) * b11
    addMatrix(a21, a22, temp1, newSize);
    strassen(temp1, b11, p2, newSize);

    // p3 = a11 * (b12 - b22)
    subtractMatrix(b12, b22, temp2, newSize);
    strassen(a11, temp2, p3, newSize);

    // p4 = a22 * (b21 - b11)
    subtractMatrix(b21, b11, temp2, newSize);
    strassen(a22, temp2, p4, newSize);

    // p5 = (a11 + a12) * b22
    addMatrix(a11, a12, temp1, newSize);
    strassen(temp1, b22, p5, newSize);

    // p6 = (a21 - a11) * (b11 + b12)
    subtractMatrix(a21, a11, temp1, newSize);
    addMatrix(b11, b12, temp2, newSize);
    strassen(temp1, temp2, p6, newSize);

    // p7 = (a12 - a22) * (b21 + b22)
    subtractMatrix(a12, a22, temp1, newSize);
    addMatrix(b21, b22, temp2, newSize);
    strassen(temp1, temp2, p7, newSize);

    // C11 = p1 + p4 - p5 + p7
    addMatrix(p1, p4, temp1, newSize);
    subtractMatrix(temp1, p5, temp2, newSize);
    addMatrix(temp2, p7, c11, newSize);

    // C12 = p3 + p5
    addMatrix(p3, p5, c12, newSize);

    // C21 = p2 + p4
    addMatrix(p2, p4, c21, newSize);

    // C22 = p1 - p2 + p3 + p6
    subtractMatrix(p1, p2, temp1, newSize);
    addMatrix(temp1, p3, temp2, newSize);
    addMatrix(temp2, p6, c22, newSize);

    // Combine the 4 halves into the result matrix
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = c11[i][j];
            C[i][j + newSize] = c12[i][j];
            C[i + newSize][j] = c21[i][j];
            C[i + newSize][j + newSize] = c22[i][j];
        }
    }
}

void transposeMatrix(vector<vector<int>>& mat, vector<vector<int>>& transposed) {
    int rows = mat.size();       
    int cols = mat[0].size();  
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = mat[i][j];
        }
    }
}
/*** mulMat
* Parametro 1: vector<vector<int>>& mat1 - Primera matriz para multiplicar.
* Parametro 2: vector<vector<int>>& mat2 - Segunda matriz para multiplicar.
* Parametro 3: vector<vector<int>>& result - Matriz resultado de la multiplicacion.
* Parametro 4: int M - Numero de filas de la primera matriz.
* Parametro 5: int N1 - Numero de columnas de la primera matriz y filas de la segunda.
* Parametro 6: int N2 - Numero de columnas de la segunda matriz.
* Resumen: Multiplica mat1 y mat2 utilizando multiplicacion matricial clasica.
*/
void mulMat(vector<vector<int>>& mat1, vector<vector<int>>& mat2, vector<vector<int>>& result, int M, int N1, int N2) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

/*** mulMatTransposed
* Parametro 1: vector<vector<int>>& mat1 - Primera matriz para multiplicar.
* Parametro 2: vector<vector<int>>& mat2 - Segunda matriz para multiplicar.
* Parametro 3: vector<vector<int>>& result - Matriz resultado de la multiplicacion.
* Parametro 4: int M - Numero de filas de la primera matriz.
* Parametro 5: int N2 - Numero de columnas de la segunda matriz.
* Resumen: Multiplica mat1 y la matriz transpuesta de mat2 para optimizar el acceso a la memoria.
*/
void mulMatTransposed(vector<vector<int>>& mat1, vector<vector<int>>& mat2, vector<vector<int>>& result, int M, int N) {
    int K = mat1[0].size();  // Asumiendo que mat1 tiene al menos una fila y todas las filas tienen el mismo tamaño
    
    // Crear una matriz transpuesta para mat2
    vector<vector<int>> mat2T(N, vector<int>(K)); 

    transposeMatrix(mat2, mat2T); // Transponer mat2 de N*K a K*N
    
    // Multiplicar mat1 (MxK) por mat2T (NxK) -> El resultado es MxN
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < K; k++) {
                result[i][j] += mat1[i][k] * mat2T[j][k];
            }
        }
    }
}



/*** printMatrix
* Parametro 1: const vector<vector<int>>& mat - Matriz a imprimir.
* Resumen: Imprime los elementos de la matriz en filas, formateando cada fila con corchetes y separando los elementos con comas para que parezca una matriz.
*/
void printMatrix(const vector<vector<int>>& mat) {
    int rows = mat.size();
    int cols = mat[0].size();
    for (int i = 0; i < rows; ++i) {
        cout << "[";
        for (int j = 0; j < cols; ++j) {
            cout << mat[i][j];
            if (j < cols - 1) {
                cout << ", "; // Coloca una coma entre los elementos, excepto al final
            }
        }
        cout << "]" << endl; // Cierra el corchete y salta a la siguiente linea
    }
}

int main() {
    clock_t start_time = clock();

    string filename;
    cout << "Ingrese el nombre del archivo de entrada: ";
    cin >> filename;
    
    ifstream file(filename);
    if (!file) {
        cerr << "No se encontraron datos en el archivo o hubo un error al leerlo." << endl;
        return 1;
    }

    int M1, N1, M2, N2;
    
    // Leer las dimensiones de la primera matriz
    file >> M1 >> N1;
    vector<vector<int>> mat1(M1, vector<int>(N1));
    for (int i = 0; i < M1; i++) {
        for (int j = 0; j < N1; j++) {
            file >> mat1[i][j];
        }
    }

    // Leer las dimensiones de la segunda matriz
    file >> M2 >> N2;
    vector<vector<int>> mat2(M2, vector<int>(N2));
    for (int i = 0; i < M2; i++) {
        for (int j = 0; j < N2; j++) {
            file >> mat2[i][j];
        }
    }

    if (N1 != M2) {
        cerr << "Las dimensiones de las matrices no permiten la multiplicacion." << endl;
        return 1;
    }

    vector<vector<int>> result(M1, vector<int>(N2));

    int x;
    cout << "Seleccione el algoritmo a utilizar:" << endl;
    cout << "1. Multiplicacion Clasica" << endl;
    cout << "2. Multiplicacion Transpuesta" << endl;
    cout << "3. Strassen" << endl;
    cout << "Ingrese el numero de la opcion: ";
    cin >> x;

    switch (x) {
        case 1:
            mulMat(mat1, mat2, result, M1, N1, N2);
            break;
        case 2:
            mulMatTransposed(mat1, mat2, result, M1, N2);
            break;
        case 3:
            if (M1 == N1 && N1 == N2) {
                strassen(mat1, mat2, result, M1);
            } else {
                cerr << "Strassen solo funciona con matrices cuadradas." << endl;
                return 1;
            }
            break;
        default:
            cerr << "Opcion no valida." << endl;
            return 1;
    }

    clock_t end_time = clock();
    double duration = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Matriz resultado:" << endl;
    printMatrix(result);

    cout << "Tiempo tomado para multiplicar matrices: " << duration << " segundos" << endl;

    return 0;
}

