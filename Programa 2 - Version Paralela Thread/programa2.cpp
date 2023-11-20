#include <iostream>
#include <vector>
#include <thread>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

//función para convertir un pixel a escala de grises
uchar convertirAGris(const Vec3b& color) {
    //utiliza la ponderacion estándar para la conversion a escala de grises
    return static_cast<uchar>(color[2] * 0.3 + color[1] * 0.59 + color[0] * 0.11);
}

//procesa una parte específica de la imagen (se divide la matriz dependiendo de la cantidad de hilos)
void procesarParteImagen(Mat& imagenColor, Mat& imagenGris, int filaInicio, int filaFin) {
    //recorre las filas asignadas y todas las columnas de la imagen
    for (int i = filaInicio; i < filaFin; i++) {
        for (int j = 0; j < imagenColor.cols; j++) {
            //se llama a la funcion de conversion por cada pixel de la matriz
            imagenGris.at<uchar>(i, j) = convertirAGris(imagenColor.at<Vec3b>(i, j));
        }
    }
}

int main(int argc, char** argv) {
    //verifica los argumentos de entrada
    if (argc != 4) {
        cout << "Uso: " << argv[0] << " <ImagenEntrada> <ImagenSalida> <NumeroDeHilos>" << endl;
        return -1;
    }

    //lee el numero de hilos desde los argumentos
    int numeroDeHilos = stoi(argv[3]);
    vector<thread> hilos(numeroDeHilos);

    //cargar la imagen a la matriz
    cout << "Cargando imagen . . ." << endl;
    Mat imagenColor = imread(argv[1], IMREAD_COLOR);
    if (imagenColor.empty()) {
        cout << "No se pudo abrir o encontrar la imagen" << endl;
        return -1;
    }

    //imprimir dimensiones de la imagen
    cout << "Filas (altura): " << imagenColor.rows << " Columnas (anchura): " << imagenColor.cols << endl;
    cout << "Iniciando conversión . . ." << endl;

    //se inicia una matriz para la imagen de destino a escala de grises 
    Mat imagenGris(imagenColor.size(), CV_8UC1);

    //se inicia el cronometro
    auto inicio = high_resolution_clock::now();

    //divide el trabajo entre los hilos
    int filasPorHilo = imagenColor.rows / numeroDeHilos;
    int inicioFila, finFila;
    for (int i = 0; i < numeroDeHilos; i++) {
        inicioFila = i * filasPorHilo;
        finFila = (i == numeroDeHilos - 1) ? imagenColor.rows : (i + 1) * filasPorHilo;
        hilos[i] = thread(procesarParteImagen, ref(imagenColor), ref(imagenGris), inicioFila, finFila);
    }

    //espera a que todos los hilos terminen
    for (auto& hilo : hilos) {
        hilo.join();
    }

    //detiene el cronometro y calcula la duracion
    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<microseconds>(fin - inicio);
    cout << "Finalizando conversión . . ." << endl;
    cout << "Tiempo total en segundos: " << duracion.count() / 1000000.0 << endl;

    //se guarda la imagen convertida
    imwrite(argv[2], imagenGris);

    return 0;
}

