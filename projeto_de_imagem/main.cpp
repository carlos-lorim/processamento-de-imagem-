/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Autores: João Pedro Pereira de Freitas 2024.1.08.029
 * Carlos Augusto Regis Lorim 2024.1.08.004
 *
 * Created on 21 de junho de 2024, 11:05
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // para usar rand() e srand()

using namespace std;

const int MAX_LINHAS = 1000;
const int MAX_COLUNAS = 1000;



void abrirImagem(const string& nomeArquivo, int matriz[MAX_LINHAS][MAX_COLUNAS], string& tipo, int& linhas, int& colunas) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cout << "Erro: arquivo não existe" << endl;
        return;
    }

    // Leitura do cabeçalho da imagem PGM
    arquivo >> tipo;
    arquivo >> colunas >> linhas;

    // Verifica se o tipo da imagem é P2 ou P5
    if (tipo != "P2" && tipo != "P5") {
        cout << "Formato de arquivo inválido. Apenas P2 ou P5 são suportados." << endl;
        arquivo.close();
        return;
    }

    // Leitura do valor máximo do pixel
    int valorMax;
    arquivo >> valorMax;

    // Ignorar o caractere de nova linha após o valor máximo
    arquivo.ignore();

    if (tipo == "P2") {
        // Leitura dos pixels da imagem P2 (texto)
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                arquivo >> matriz[i][j];
            }
        }
    } else if (tipo == "P5") {
        // Leitura dos pixels da imagem P5 (binário)
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                matriz[i][j] = static_cast<unsigned char>(arquivo.get());
            }
        }
    }

    arquivo.close();
}
// Função para salvar a imagem modificada em um novo arquivo PGM
void salvarImagem(const string& nomeArquivoSaida, int matriz[MAX_LINHAS][MAX_COLUNAS], const string& tipo, int linhas, int colunas) {
    ofstream arquivo(nomeArquivoSaida);

    if (!arquivo.is_open()) {
        cout << "Erro ao criar arquivo de saída." << endl;
        return;
    }

    arquivo << tipo << endl;
    arquivo << colunas << " " << linhas << endl;
    arquivo << 255 << endl;

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            arquivo << matriz[i][j] << " ";
        }
        arquivo << endl;
    }

    arquivo.close();
}

// Função para escurecer ou clarear a imagem
void escurecer_clarearImagem(int matriz[MAX_LINHAS][MAX_COLUNAS], int linhas, int colunas, float fator, const string& tipo) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matriz[i][j] = int(matriz[i][j] * fator);
            if (matriz[i][j] < 0) {
                matriz[i][j] = 0;
            } else if (matriz[i][j] > 255) {
                matriz[i][j] = 255;
            }
        }
    }
    salvarImagem("stanfordsaida.pgm", matriz, tipo, linhas, colunas);
}

// Função para converter a imagem em sua negativa
void negativaImagem(int matriz[MAX_LINHAS][MAX_COLUNAS], int linhas, int colunas, const string& tipo) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matriz[i][j] = 255 - matriz[i][j];
        }
    }
    salvarImagem("stanfordsaida.pgm", matriz, tipo, linhas, colunas);
}

// Função para binarizar a imagem
void binarizarImagem(int matriz[MAX_LINHAS][MAX_COLUNAS], int linhas, int colunas, int limiar, const string& tipo) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (matriz[i][j] >= limiar) {
                matriz[i][j] = 255;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
    salvarImagem("stanfordsaida.pgm", matriz, tipo, linhas, colunas);
}

// Função para iconizar a imagem (redução de resolução)
void iconizarImagem(int matriz[MAX_LINHAS][MAX_COLUNAS], int& linhas, int& colunas, const string& tipo) {
    for (int i = 0; i < linhas / 2; ++i) {
        for (int j = 0; j < colunas / 2; ++j) {
            matriz[i][j] = (matriz[2 * i][2 * j] + matriz[2 * i + 1][2 * j] +
                            matriz[2 * i][2 * j + 1] + matriz[2 * i + 1][2 * j + 1]) / 4;
        }
    }
    linhas /= 2;
    colunas /= 2;
    salvarImagem("stanfordsaida.pgm", matriz, tipo, linhas, colunas);
}

// Função para adicionar ruído sal e pimenta na imagem
void adicionarRuido(int matriz[MAX_LINHAS][MAX_COLUNAS], int linhas, int colunas, float intensidade, const string& tipo) {
    int numPixels = linhas * colunas;
    int numRuido = numPixels * intensidade;

    srand(12345); // Semente fixa para gerar números aleatórios previsíveis

    for (int i = 0; i < numRuido; ++i) {
        int x = rand() % linhas;
        int y = rand() % colunas;
        matriz[x][y] = (rand() % 2) ? 255 : 0;
    }
    salvarImagem("stanfordsaida.pgm", matriz, tipo, linhas, colunas);
}

// Função para suavizar a imagem
void suaveImagem(int matriz[MAX_LINHAS][MAX_COLUNAS], int linhas, int colunas, const string& tipo) {
    int kernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    int kernelSum = 16;

    int temp[MAX_LINHAS][MAX_COLUNAS];
    for (int i = 1; i < linhas - 1; ++i) {
        for (int j = 1; j < colunas - 1; ++j) {
            int sum = 0;
            for (int ki = -1; ki <= 1; ++ki) {
                for (int kj = -1; kj <= 1; ++kj) {
                    sum += matriz[i + ki][j + kj] * kernel[ki + 1][kj + 1];
                }
            }
            temp[i][j] = sum / kernelSum;
        }
    }
    for (int i = 1; i < linhas - 1; ++i) {
        for (int j = 1; j < colunas - 1; ++j) {
            matriz[i][j] = temp[i][j];
        }
    }
    salvarImagem("stanfordsaida.pgm", matriz, tipo, linhas, colunas);
}

int main() {
    int matriz[MAX_LINHAS][MAX_COLUNAS];
    string tipo;
    int linhas = 0, colunas = 0;
    int op;

    do {
        cout << "Digite 1 para abrir a imagem" << endl;
        cout << "Digite 2 para clarear ou escurecer a imagem" << endl;
        cout << "Digite 3 para converter a imagem em sua negativa" << endl;
        cout << "Digite 4 para binarizar a imagem" << endl;
        cout << "Digite 5 para iconizar a imagem" << endl;
        cout << "Digite 6 para adicionar ruído à imagem" << endl;
        cout << "Digite 7 para suavizar a imagem" << endl;
        cout << "Digite 8 para sair" << endl;
        cin >> op;

        switch (op) {
            case 1:
                abrirImagem("stanford.pgm", matriz, tipo, linhas, colunas);
                if (linhas > 0 && colunas > 0) {
                    cout << "Tipo da imagem: " << tipo << endl;
                    cout << "Dimensões: " << linhas << " x " << colunas << endl;
                    salvarImagem("stanfordsaida.pgm", matriz, tipo, linhas, colunas);
                } else {
                    cout << "Falha ao carregar a imagem." << endl;
                }
                break;

            case 2:
                if (linhas == 0 || colunas == 0) {
                    cout << "Imagem não carregada. Abra uma imagem primeiro." << endl;
                } else {
                    float fator;
                    cout << "Digite o fator para clarear (>1) ou escurecer"<< endl;

                    cin >> fator;
                    escurecer_clarearImagem(matriz, linhas, colunas, fator, tipo);
                    cout << "Imagem modificada com fator " << fator << endl;
                }
                break;

            case 3:
                if (linhas == 0 || colunas == 0) {
                    cout << "Imagem não carregada. Abra uma imagem primeiro." << endl;
                } else {
                    negativaImagem(matriz, linhas, colunas, tipo);
                    cout << "Imagem convertida para negativa." << endl;
                }
                break;

            case 4:
                if (linhas == 0 || colunas == 0) {
                    cout << "Imagem não carregada. Abra uma imagem primeiro." << endl;
                } else {
                    int limiar;
                    cout << "Digite o limiar para binarizar a imagem (0-255): ";
                    cin >> limiar;
                    binarizarImagem(matriz, linhas, colunas, limiar, tipo);
                    cout << "Imagem binarizada com limiar " << limiar << endl;
                }
                break;

            case 5:
                if (linhas == 0 || colunas == 0) {
                    cout << "Imagem não carregada. Abra uma imagem primeiro." << endl;
                } else {
                    iconizarImagem(matriz, linhas, colunas, tipo);
                    cout << "Imagem iconizada (resolução reduzida)." << endl;
                }
                break;

            case 6:
                if (linhas == 0 || colunas == 0) {
                    cout << "Imagem não carregada. Abra uma imagem primeiro." << endl;
                } else {
                    float intensidade;
                    cout << "Digite a intensidade do ruído (0-1): ";
                    cin >> intensidade;
                    adicionarRuido(matriz, linhas, colunas, intensidade, tipo);
                    cout << "Ruído adicionado com intensidade " << intensidade << endl;
                }
                break;

            case 7:
                if (linhas == 0 || colunas == 0) {
                    cout << "Imagem não carregada. Abra uma imagem primeiro." << endl;
                } else {
                    suaveImagem(matriz, linhas, colunas, tipo);
                    cout << "Imagem suavizada." << endl;
                }
                break;

            case 8:
                cout << "Saindo..." << endl;
                break;

            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }
    } while (op != 8);

    return 0;
}
