#include <iostream>
#include <math.h>
#include <string>
using namespace std;

void output(float r0, float g0, float b0) {
    try {
        float c[3],cmy[3], cmyk[4], hsv[3], hsl[3], xyz[3];
        c[0] = r0; c[1] = g0; c[2] = b0;
        int k = 0;
        if ((c[0] < -0.0) or (c[0] > 255) or (c[1] < -0.0) or (c[1] > 255) or (c[2] < -0.0) or (c[2] > 255)) {
            throw - 1;
        }
        xyz[0] = 1 / 0.17697 * (0.49 * c[0] + 0.31 * c[1] + 0.20 * c[2]);
        xyz[1] = 1 / 0.17697 * (0.17697 * c[0] + 0.81240 * c[1] + 0.01063 * c[2]);
        xyz[2] = 1 / 0.17697 * (0.00 * c[0] + 0.01 * c[1] + 0.99 * c[2]);

        cmy[0] = 1 - c[0] / 255;
        cmy[1] = 1 - c[1] / 255;
        cmy[2] = 1 - c[2] / 255;

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

        cout << "RGB: " << r0 << " " << g0 << " " << b0 << endl;
        cout << "CMY: " << cmy[0] * 100 << "% " << cmy[1] * 100 << "% " << cmy[2] * 100 << "%" << endl;
        cout << "CMYK: " << cmyk[0] * 100 << "% " << cmyk[1] * 100 << "% " << cmyk[2] * 100 << "% " << cmyk[3] * 100 << "%" << endl;
        cout << "XYZ: " << xyz[0] << " " << xyz[1] << " " << xyz[2] << endl;
        cout << "HSL: " << fmod(360 + hsl[0], 360) << "\xB0 " << hsl[1] * 100 << "% " << hsl[2] * 100 << "%" << endl;
        cout << "HSV: " << fmod(360 + hsv[0], 360) << "\xB0 " << hsv[1] * 100 << "% " << hsv[2] * 100 << "%" << endl;
    }
    catch (int) {
        cout << "Wrong data1." << endl;
    }
}

int main()
{
    begin:
    try {
        int n;
        bool exit = false;
        while (!exit) {
            cout << "Choose color model:" << endl;
            cout << "1. RGB (0-255)" << endl;
            cout << "2. CMY (0-100(%))"<<endl;
            cout << "3. CMYK (0-100(%))"<<endl;
            cout << "4. HSV (H:0-360(°); S,V:0-100(%))"<<endl;
            cout << "5. HSL (H:0-360(°); S,L:0-100(%))"<<endl;
            cout << "6. Exit."<<endl;
            cin >> n;
            string vc[3]; float c[3], c1[3], k, x1, x2,m;
            switch (n) {
            case 1:
                cout << "R: ";
                cin >> vc[0];
                cout << "G: ";
                cin >> vc[1];
                cout << "B: ";
                cin >> vc[2];
                c[0] = stof(vc[0].c_str());
                c[1] = stof(vc[1].c_str());
                c[2] = stof(vc[2].c_str());
                output(c[0], c[1], c[2]);
                break;
            case 2:
                try {
                    cout << "C: ";
                    cin >> vc[0];
                    cout << "M: ";
                    cin >> vc[1];
                    cout << "Y: ";
                    cin >> vc[2];
                    c1[0] = stof(vc[0].c_str());
                    c1[1] = stof(vc[1].c_str());
                    c1[2] = stof(vc[2].c_str());
                    c[0] = (1 - c1[0]/100) * 255;
                    c[1] = (1 - c1[1]/100) * 255;
                    c[2] = (1 - c1[2]/100) * 255;
                    if ((c1[0] < -0.0) or (c1[0] > 100) or (c1[1] < -0.0) or (c1[1] > 100) or (c1[2] < -0.0) or (c1[2] > 100)) {
                        throw - 1;
                    }
                    output(c[0], c[1], c[2]);
                    break;
                }
                catch (int) {
                    cout << "Wrong data." << endl;
                }
            case 3:
                try {
                    cout << "C: ";
                    cin >> vc[0];
                    cout << "M: ";
                    cin >> vc[1];
                    cout << "Y: ";
                    cin >> vc[2];
                    cout << "K:";
                    cin >> k;
                    c1[0] = stof(vc[0].c_str());
                    c1[1] = stof(vc[1].c_str());
                    c1[2] = stof(vc[2].c_str());
                    c[0] = (1 - c1[0]/100) * 255;
                    c[1] = (1 - c1[1]/100) * 255;
                    c[2] = (1 - c1[2]/100) * 255;
                    if ((c1[0] < -0.0) or (c1[0] > 100) or (k != fmin(fmin(fmin(c1[0], c1[1]), c1[2]), 100)) or (c1[1] < -0.0) or (c1[1] > 100) or (c1[2] < -0.0) or (c1[2] > 100)) {
                        throw - 1;
                    }
                    output(c[0], c[1], c[2]);
                }
                catch (int) {
                    cout << "Wrong data." << endl;
                }
                break;
            case 4:
                try {
                    cout << "H: ";
                    cin >> vc[0];
                    cout << "S: ";
                    cin >> vc[1];
                    cout << "V: ";
                    cin >> vc[2];
                    c1[0] = stof(vc[0].c_str());
                    c1[1] = stof(vc[1].c_str())/100;
                    c1[2] = stof(vc[2].c_str())/100;
                    x1 = c1[1] * c1[2];
                    x2 = x1 * (1 - abs(fmod(c1[0] / 60, 2) - 1));
                    m = c1[2] - x1;
                    if ((c1[0] < -0.0) or (c1[0] > 360) or (c1[1] < -0.0) or (c1[1] > 100) or (c1[2] < -0.0) or (c1[2] > 100)) {
                        throw - 1;
                    }
                    if (c1[0] < 60) {
                        c[0] = 255 * (x1 + m);
                        c[1] = 255 * (x2 + m); 
                        c[2] = 255 * m;
                    }
                    else if (c1[0] < 120) {
                        c[0] = 255 * (x2 + m);
                        c[1] = 255 * (x1 + m);
                        c[2] = 255 * m;
                    }
                    else if (c1[0] < 180) {
                        c[1] = 255 * (x1 + m);
                        c[2] = 255 * (x2 + m);
                        c[0] = 255 * m;
                    }
                    else if (c1[0] < 240) {
                        c[2] = 255 * (x1 + m);
                        c[1] = 255 * (x2 + m);
                        c[0] = 255 * m;
                    }
                    else if (c1[0] < 300) {
                        c[2] = 255 * (x1 + m);
                        c[0] = 255 * (x2 + m);
                        c[1] = 255 * m;
                    }
                    else if (c1[0] < 360) {
                        c[0] = 255 * (x1 + m);
                        c[2] = 255 * (x2 + m);
                        c[1] = 255 * m;
                    }
                    output(c[0], c[1], c[2]);
                }
                catch (int) {
                    cout << "Wrong data." << endl;
                }
                break;
            case 5: 
                try {
                    cout << "H: ";
                    cin >> vc[0];
                    cout << "S: ";
                    cin >> vc[1];
                    cout << "L: ";
                    cin >> vc[2];
                    c1[0] = stof(vc[0].c_str());
                    c1[1] = stof(vc[1].c_str())/100;
                    c1[2] = stof(vc[2].c_str())/100;
                    x1 = (1 - abs(c1[2] * 2 - 1)) * c1[1];
                    x2 = x1 * (1 - abs(fmod(c1[0] / 60, 2) - 1));
                    m = c1[2] - x1/2;
                    if ((c1[0] < -0.0) or (c1[0] > 360) or (c1[1] < -0.0) or (c1[1] > 100) or (c1[2] < -0.0) or (c1[2] > 100)) {
                        throw - 1;
                    }
                    if (c1[0] < 60) {
                        c[0] = 255 * (x1 + m);
                        c[1] = 255 * (x2 + m);
                        c[2] = 255 * m;
                    }
                    else if (c1[0] < 120) {
                        c[0] = 255 * (x2 + m);
                        c[1] = 255 * (x1 + m);
                        c[2] = 255 * m;
                    }
                    else if (c1[0] < 180) {
                        c[1] = 255 * (x1 + m);
                        c[2] = 255 * (x2 + m);
                        c[0] = 255 * m;
                    }
                    else if (c1[0] < 240) {
                        c[2] = 255 * (x1 + m);
                        c[1] = 255 * (x2 + m);
                        c[0] = 255 * m;
                    }
                    else if (c1[0] < 300) {
                        c[2] = 255 * (x1 + m);
                        c[0] = 255 * (x2 + m);
                        c[1] = 255 * m;
                    }
                    else if (c1[0] < 360) {
                        c[0] = 255 * (x1 + m);
                        c[2] = 255 * (x2 + m);
                        c[1] = 255 * m;
                    }
                    output(c[0], c[1], c[2]);
                }
                catch (int) {
                    cout << "Wrong data." << endl;
                }
                break;
            case 6:
                exit = true;
                break;
            }
        }
    }
        catch (invalid_argument) {
            cout << "Wrong data." << endl;
            goto begin;
        }
    
}
