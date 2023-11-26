#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <omp.h>

using namespace cv;
using namespace std;
using namespace std::chrono;

//convierte un color BGR a escala de grises
uchar convertirAGris(const Vec3b& color) {
    //utiliza la ponderación estándar para la conversión a escala de grises
    return static_cast<uchar>(color[2] * 0.3 + color[1] * 0.59 + color[0] * 0.11);
}

int main(int argc, char** argv) {
    //verifica los argumentos de entrada
    if (argc != 4) {
        cout << "Uso: " << argv[0] << " <ImagenEntrada> <ImagenSalida> <NumeroDeHilos>" << endl;
        return -1;
    }

    //lee el número de hilos desde los argumentos
    int numeroDeHilos = stoi(argv[3]);
    omp_set_num_threads(numeroDeHilos); //establece el número de hilos para OpenMP

    //carga la imagen
    cout << "Cargando imagen..." << endl;
    Mat imagenColor = imread(argv[1], IMREAD_COLOR);
    if (imagenColor.empty()) {
        cout << "No se pudo abrir o encontrar la imagen" << endl;
        return -1;
    }

    //crea una imagen en escala de grises vacía
    Mat imagenGris(imagenColor.size(), CV_8UC1);

    //inicia el cronómetro
    auto inicio = high_resolution_clock::now();

    //paralelización con OpenMP
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < imagenColor.rows; i++) {
        for (int j = 0; j < imagenColor.cols; j++) {
            //convierte y asigna el valor en escala de grises al pixel correspondiente
            imagenGris.at<uchar>(i, j) = convertirAGris(imagenColor.at<Vec3b>(i, j));
        }
    }

    //detiene el cronómetro y calcula la duración
    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<microseconds>(fin - inicio);
    cout << "Finalizando conversión..." << endl;
    cout << "Tiempo total en segundos: " << duracion.count() / 1000000.0 << endl;

    //guarda la imagen resultante
    imwrite(argv[2], imagenGris);

    return 0;
}
