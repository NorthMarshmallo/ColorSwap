// ColorsSwap.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <string>
using namespace std;

int main()
{
    begin:
    try {
        string vc[3];
        cout << "Enter R, G, B, each from 0 to 255 or stop if you want program to stop:" << endl;
        cout << "R: ";
        cin >> vc[0];
        cout << "G: ";
        cin >> vc[1];
        cout << "B: ";
        cin >> vc[2];
        float c[3], cmy[3], cmyk[4], hsv[3], hsl[3], xyz[3];
        int k = 0;
        for (int i = 0; i <= 2; i++) {

        }
        while (vc[0] != "stop") {
            c[0] = stof(vc[0].c_str());
            c[1] = stof(vc[1].c_str());
            c[2] = stof(vc[2].c_str());
            if ((c[0] < -0.0) or (c[0] > 255) or (c[1] < -0.0) or (c[1] > 255) or (c[2] < -0.0) or (c[2] > 255)) {
                throw - 1;
            }
            xyz[0] = 1 / 0.17697 * (0.49 * c[0] + 0.31 * c[1] + 0.20 * c[2]);
            xyz[1] = 1 / 0.17697 * (0.17697 * c[0] + 0.81240 * c[1] + 0.01063 * c[2]);
            xyz[2] = 1 / 0.17697 * (0.00 * c[0] + 0.01 * c[1] + 0.99 * c[2]);

            cmy[0] = 1 - c[0]/255;
            cmy[1] = 1 - c[1]/255;
            cmy[2] = 1 - c[2]/255;

            if ((c[0] == 0) and (c[1] == 0) and (c[2] == 0)) {
                cmyk[3] = 0;
            }
            else {
                cmyk[3] = fmin(fmin(fmin(cmy[0], cmy[1]), cmy[2]), 1);
            }
            cmyk[0] = (cmy[0] - cmyk[3]) / (1 - cmyk[3]);
            cmyk[1] = (cmy[1] - cmyk[3]) / (1 - cmyk[3]);
            cmyk[2] = (cmy[2] - cmyk[3]) / (1 - cmyk[3]);

            float r = c[0] / 255;
            float g = c[1] / 255;
            float b = c[2] / 255;
            float del = fmax(fmax(r, g), b) - fmin(fmin(r, g), b);
            hsl[2] = (fmax(fmax(r, g), b) + fmin(fmin(r, g), b)) / 2;
            float m = fmax(fmax(r, g), b);
            if (del == 0) {
                hsl[0] = 0;
                hsl[1] = 0;
                hsv[1] = 0;
            }
            else if (m == r) {
                hsl[0] = 60 * (fmod(((g - b) / del), 6));
            }
            else if (m == g) {
                hsl[0] = 60 * ((b - r) / del + 2);
            }
            else if (m == b) {
                hsl[0] = 60 * ((r - g) / del + 4);
            }
            if (del != 0) {
                hsl[1] = del / (1 - abs(2 * hsl[2] - 1));
                hsv[1] = del / m;
            }

            hsv[0] = hsl[0];
            hsv[2] = m;

            cout << "CMY: " << cmy[0]*100 << "% " << cmy[1]*100 << "% " << cmy[2]*100 << "%"<< endl;
            cout << "CMYK: " << cmyk[0]*100 << "% " << cmyk[1]*100 << "% " << cmyk[2]*100 << "% " << cmyk[3]*100 << "%" <<endl;
            cout << "XYZ: " << xyz[0] << " " << xyz[1] << " " << xyz[2] << endl;
            cout << "HSL: " << fmod(360+hsl[0],360) << "\xB0 " << hsl[1]*100 << "% " << hsl[2]*100 << "%" << endl;
            cout << "HSV: " << fmod(360 + hsv[0], 360) << "\xB0 " << hsv[1]*100 << "% " << hsv[2]*100 << "%" << endl;
                cout << "Enter R, G, B, each from 0 to 255 or stop if you want program to stop:" << endl;
                float c[3], cmy[3], cmyk[4], hsv[3], hsl[3], xyz[3];;
                cout << "R: ";
                cin >> vc[0];
                if (vc[0] == "stop") {
                    break;
                }
                cout << "G: ";
                cin >> vc[1];
                cout << "B: ";
                cin >> vc[2];
        }
    }
    catch (int) {
            cout << "Wrong data." << endl;
            goto begin;
        }
    catch (invalid_argument) {
        cout << "Wrong data." << endl;
        goto begin;
    }
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
