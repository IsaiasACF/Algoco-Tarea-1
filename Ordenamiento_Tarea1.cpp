#include <bits/stdc++.h>
#include <ctime>
#include <algorithm>
using namespace std;

/*** selectionSort
* Parametro 1: vector<int>& arr - El vector de enteros a ordenar.
* Resumen: Implementa el algoritmo de ordenamiento por seleccion. Recorre el vector, seleccionando el 
*elemento minimo y colocandolo en la posicion correcta.
*/
void selectionSort(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }
}
/*** printArray
* Parametro 1: const vector<int>& arr - El vector de enteros a imprimir.
* Resumen: Imprime los elementos del vector separados por un espacio.
*/
void printArray(const vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

/*** merge
* Parametro 1: vector<int>& arr - El vector de enteros a ordenar.
* Parametro 2: int left - Indice izquierdo del subarreglo.
* Parametro 3: int mid - Indice medio del subarreglo.
* Parametro 4: int right - Indice derecho del subarreglo.
* Resumen: Realiza la fusion de dos subarreglos ordenados dentro del arreglo principal.
*/
void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
/*** mergeSort
* Parametro 1: vector<int>& arr - El vector de enteros a ordenar.
* Parametro 2: int left - Indice izquierdo del subarreglo.
* Parametro 3: int right - Indice derecho del subarreglo.
* Resumen: Implementa el algoritmo Merge Sort recursivo para ordenar un vector.
*/
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

/*** readNumbersFromFile
* Parametro 1: const string& filename - El nombre del archivo desde el cual se leeran los numeros.
* Parametro 2: vector<int>& arr - El vector en el cual se almacenaran los numeros leidos.
* Resumen: Lee una lista de numeros enteros desde un archivo y los almacena en un vector.
*/
void readNumbersFromFile(const string& filename, vector<int>& arr) {
    ifstream inFile(filename);
    int number;

    if (!inFile) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    while (inFile >> number) {
        arr.push_back(number);
    }

    inFile.close();
}
/*** partition
* Parametro 1: vector<int>& arr - El vector de enteros a ordenar.
* Parametro 2: int low - Indice inferior del subarreglo.
* Parametro 3: int high - Indice superior del subarreglo.
* Return: int - Indice de la particion.
* Resumen: Implementa la funcion de particion para el algoritmo QuickSort, eligiendo un pivote y organizando los elementos menores a su izquierda y los mayores a su derecha.
*/
int partition(vector<int>& arr, int low, int high) {
  
    int pivot = arr[high];
  

    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    

    swap(arr[i + 1], arr[high]);  
    return i + 1;
}
/*** quickSort
* Parametro 1: vector<int>& arr - El vector de enteros a ordenar.
* Parametro 2: int low - Indice inferior del subarreglo.
* Parametro 3: int high - Indice superior del subarreglo.
* Resumen: Implementa el algoritmo QuickSort recursivo para ordenar un vector de enteros.
*/
void quickSort(vector<int>& arr, int low, int high) {
  
    if (low < high) {
      
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    vector<int> arr;
    string filename;
    int x;
    cout << "Ingrese el nombre del archivo de entrada: ";
    cin >> filename;

    readNumbersFromFile(filename, arr);

    if (arr.empty()) {
        cerr << "No se encontraron datos en el archivo o hubo un error al leerlo." << endl;
        return 1;
    }

    int n = arr.size();

    cout << "Seleccione el algoritmo a utilizar:" << endl;
    cout << "1. MergeSort" << endl;
    cout << "2. SelectionSort" << endl;
    cout << "3. QuickSort" << endl;
    cout << "4. Sort (STL)" << endl;
    cout << "Ingrese el numero de la opcion: ";
    cin >> x;

    clock_t start = clock();

    switch (x) {
        case 1:
            mergeSort(arr, 0, n - 1);
            cout << "Tiempo de ejecucion de MergeSort: ";
            break;
        case 2:
            selectionSort(arr);
            cout << "Tiempo de ejecucion de SelectionSort: ";
            break;
        case 3:
            quickSort(arr, 0, n - 1);
            cout << "Tiempo de ejecucion de QuickSort: ";
            break;
        case 4:
            sort(arr.begin(), arr.end());
            cout << "Tiempo de ejecucion de Sort (STL): ";
            break;
        default:
            cerr << "Opcion no valida." << endl;
            return 1;
    }

    clock_t end = clock();

    double elapsed_time = double(end - start) / CLOCKS_PER_SEC;

    printArray(arr);

    cout << elapsed_time << " segundos" << endl;

    return 0;
}