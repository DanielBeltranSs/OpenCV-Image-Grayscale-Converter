#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

//función para convertir un pixel a escala de grises
uchar convertirAGris(const Vec3b& color) { //vec3b recibe un vector de 3 bytes para el pixel en formato bgr
    return static_cast<uchar>(color[2] * 0.3 + color[1] * 0.59 + color[0] * 0.11);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <ImagenEntrada> <ImagenSalida>" << endl;
        return -1;
    }

    //cargar la imagen a la matriz
    cout << "Cargando imagen . . ." << endl;
    Mat imagenColor = imread(argv[1], IMREAD_COLOR);
    if (imagenColor.empty()) {
        cout << "No se pudo abrir o encontrar la imagen" << endl;
        return -1;
    }
    
    //imprimir datos de la matriz
    cout << "Filas (altura): " << imagenColor.rows << " Columnas (anchura): " << imagenColor.cols << endl;
    cout << "Iniciando conversión . . ." << endl;

    //se inicia el cronometro
    auto inicio = high_resolution_clock::now();

    //se inicia una matriz para la imagen de destino a escala de grises 
    Mat imagenGris(imagenColor.size(), CV_8UC1);

    //se recorre la matriz de la imagen original
    for (int i = 0; i < imagenColor.rows; i++) {
        for (int j = 0; j < imagenColor.cols; j++) {
            imagenGris.at<uchar>(i, j) = convertirAGris(imagenColor.at<Vec3b>(i, j)); //se llama a la funcion de conversion por cada pixel de la matriz
        }
    }

    //se detiene el cronometro
    auto fin = high_resolution_clock::now();

    cout << "Finalizando conversión . . ." << endl;

    //se calcula y se imprime el valor total de conversion
    auto duracion = duration_cast<microseconds>(fin - inicio);
    cout << "Tiempo total en segundos: " << duracion.count() / 1000000.0 << endl;

    //se guarda la imagen convertida
    imwrite(argv[2], imagenGris);

    return 0;
}
