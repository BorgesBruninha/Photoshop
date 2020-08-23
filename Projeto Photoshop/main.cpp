#include <iostream>
#include <cstdlib>
#include <fstream>
#include <locale.h>
#include <stdlib.h>
#include <cstring>

using namespace std;
const int MAX = 512;
const int STRMAX = 50;

///Caracteristicas da imagem
struct img{
    char p[STRMAX];
    int linha;
    int coluna;
    int pp;
    int pixel[3][MAX][MAX];
};
///Obrigat�ria
///Abre imagem
///FEITO COM SUCESSO
void abre_img(char nome[], img& img){
    fstream foto;
    foto.open(nome);

    if(!foto.is_open()){
        cout << "Desculpa! Arquivo n�o encontrado!\n";
        exit(0);
    }else{
        system("cls");
    }

    foto >> img.p;
    if(strcasecmp(img.p, "P3") != 0){
        cout << "Formato incorreto de arquivo\n";
        exit(0);
    }
    foto >> img.coluna;
    foto >> img.linha;
    foto >> img.pp;


    for(int i = 0; i < img.linha; i++){
        for(int j = 0; j < img.coluna; j++){
            for(int k = 0; k < 3; k++){
                foto >> img.pixel[k][i][j];
            }
        }
    }
}
///Obrigat�ria
///Salva Imagem
///FEITO COM SUCESSO
void salva_img(char nome[], img img){
    cin.ignore();
    cout << "Escolha um nome para a imagem:\n";
    cin.getline(nome, STRMAX);


    ofstream foto;
    foto.open(nome);

    if(!foto.is_open()){
        exit(0);
    }else{
        system("cls");
    }

    foto << "P3\n";
    foto << img.coluna << " " << img.linha << endl;
    foto << 255 << endl;

    for(int i = 0; i < img.linha; i++){
        for(int j = 0; j < img.coluna; j++){
            for(int k = 0; k < 3; k++){
                foto << img.pixel[k][i][j] << " ";
            }
        }
    cout << endl;
    }
}
///Obrigat�ria
///Corta Imagem
///Feito com sucesso
void corta_rgb(img img_in, img& img_out, int li, int ci, int lf, int cf){
    img_out.coluna = cf - ci;
    img_out.linha = lf - li;

    for(int i = 0; i < lf - li; i++){
        for(int j = 0; j < cf - ci; j++){
            for(int k = 0; k < 3; k++){
                img_out.pixel[k][i][j] = img_in.pixel[k][li + i][ci + j];
            }

        }
    }

}

///*Converte para cinza* (asterisco)
void converte_para_cinza(img img_in, img& img_out){
    float media;
    img_out.linha = img_in.linha;
    img_out.coluna = img_in.coluna;

    for(int i = 0; i < img_in.linha; i++){
        for(int j = 0; j < img_in.coluna; j++){
            media = 0;
            for(int k = 0; k < 3; k++){
                media += img_in.pixel[k][i][j];
            }
            media = media / 3.0;
            for(int k = 0; k < 3; k++){
                img_out.pixel[k][i][j] = media;
            }
        }
    }
}
///*Binariza Imagem* (asterisco)
///FEITO COM SUCESSO
void binariza(img img_in, img& img_out, int limiar){
    converte_para_cinza(img_in, img_out);

    img_out.linha = img_in.linha;
    img_out.coluna = img_in.coluna;

    for(int i = 0; i < img_in.linha; i++){
        for(int j = 0; j < img_in.coluna; j++){
            if(img_out.pixel[1][i][j] <= limiar){
                for(int k = 0; k < 3; k++){
                    img_out.pixel[k][i][j] = 0;
                }
            }else{
                for(int k = 0; k < 3; k++){
                    img_out.pixel[k][i][j] = 255;
                }
            }
        }
    }
}

///*Negativo da imagem* (asterisco)
///FEITO COM SUCESSO
void computa_negativo(img img_in, img& img_out){
    img_out.linha = img_in.linha;
    img_out.coluna = img_in.coluna;

        for(int i = 0; i < img_out.linha; i++){
            for(int j = 0; j < img_out.coluna; j++){
                  for(int k = 0; k < 3; k++){
                     img_out.pixel[k][i][j] = 255 - img_in.pixel[k][i][j];
                  }
            }
        }
}
///Diminui tamanho da imagem
///FEITO COM SUCESSO
void diminui_tamanho(img img_in, img& img_out){
    img_out.linha = img_in.linha/2;
    img_out.coluna = img_in.coluna/2;

    for(int i = 0; i < img_out.linha; i++){
        for(int j = 0; j < img_out.coluna; j++){
            for(int k = 0; k < 3; k++){
                img_out.pixel[k][i][j] = img_in.pixel[k][2*i][2*j];
            }
        }
    }
}
///*Filtragem por dilata��o* (asterisco)
///FALTA FAZER
void filtragem_por_dilatacao(img img_in, img& img_out){
    int n;

    cout << "Sua imagem est� binarizada?\n1 - Sim\n2 - N�o\n";
    cin >> n;

    if(n == 2){
        cout << "Binarize antes de prosseguir\n";
        exit(0);
    }

    img_out.linha = img_in.linha;
    img_out.coluna = img_in.coluna;

    for(int i = 0; i < img_out.linha; i++){
            for(int j = 0; j < img_out.coluna; j++){
                  for(int k = 0; k < 3; k++){
                        if(i < img_in.linha - 1 && i > 0 && j < img_in.coluna - 1 && j > 0){
                            if(img_in.pixel[k][i+1][j] == 255 || img_in.pixel[k][i][j+1] == 255 || img_in.pixel[k][i+1][j+1] == 255){
                                img_out.pixel[k][i][j] = 255;
                            }else{
                                img_out.pixel[k][i][j] = 0;
                            }
                        }else{
                                img_out.pixel[k][i][j] = 0;
                        }
                  }
            }
        }
}

int main()
{   setlocale(LC_ALL, "Portuguese");

    int menu;
    int qntlinha, qntcoluna;
    char nome_usuario[MAX];

    cout << "Ol�, usu�rio! Digite seu nome: \n";
    cin.getline(nome_usuario,MAX);
    system("cls");

    cout << nome_usuario << ", digite o nome.tipo do arquivo que voc� deseja manipular" << endl;

    img img_in, img_out;
    char nome[STRMAX];
    cin.getline(nome, STRMAX);
    abre_img(nome, img_in);

    ///Op��es menu
    cout << endl << "Ol�, " << nome_usuario << "! Escolha qual recurso voc� deseja aplicar � sua foto: ";
    cout << endl;
    cout << "1 - Recortar\n";
    cout << "2 - Binarizar\n";
    cout << "3 - Negativo\n";
    cout << "4 - Reduzir imagem\n";
    cout << "5 - Filtragem por dilata��o\n";
    cout << "6 - Conveter para tons de cinza\n";
    cin >> menu;
    while (menu<1 || menu>6){
        cout << "N�mero inv�lido! Digite novamente!\n";
        cin>>menu;
    }

    ///Menu
    switch(menu){

    case 1:
    system("cls");
    int li, lf, ci, cf;

    qntlinha = img_in.linha;
    qntcoluna = img_in.coluna;

    cout << nome_usuario << ", a sua imagem tem: "<<qntlinha<<" linhas e "<<qntcoluna<<" colunas\n";
    cout<<endl;
    ///Recortar imagem
    cout << "Digite o inicio da linha: \n";
    cin >> li;
    while (li<0 || li > qntlinha){
        cout << "N�mero inv�lido! Digite novamente!\n";
        cin >> li;
    }
    cout << "Digite o final da linha: \n";
    cin >> lf;
        while (lf>qntlinha || lf==li || lf < 0){
        cout << "N�mero inv�lido! Digite novamente!\n";
        cin >> lf;
    }
        cout << "Digite o inicio da coluna: \n";
        cin >> ci;
     while (ci < 0 || ci > qntcoluna){
        cout << "N�mero inv�lido! Digite novamente!\n";
        cin >> ci;
    }
        cout << "Digite o final da coluna: \n";
        cin >> cf;
     while (cf > qntcoluna || cf==ci || cf< 0){
        cout << "N�mero inv�lido! Digite novamente!\n";
        cin >> cf;
    }


    corta_rgb(img_in, img_out, li, ci, lf, cf);
    salva_img(nome, img_out);
    cout << endl << "Imagem cortada e salva com sucesso!\n";

    break;


    case 2:
        system("cls");
        int limiar;
        cout << "Digite o limiar\n";
        cin >> limiar;

        while (limiar <0 || limiar>255){
            cout << nome_usuario<< ", n�mero inv�lido!\nDigite um n�mero entre 0 e 255\n";
            cin  >> limiar;
        }

        binariza(img_in, img_out, limiar);
        salva_img(nome, img_out);

        cout << endl << "Imagem binarizada e salva com sucesso!\n";

        break;

    case 3:
        system("cls");
        computa_negativo(img_in, img_out);
        salva_img(nome, img_out);

        cout << endl << "Imagem negativada e salva com sucesso!\n";
        break;


    case 4:
        system("cls");

        diminui_tamanho(img_in, img_out);
        salva_img(nome, img_out);

        cout << endl << "Imagem reduzida e salva com sucesso!\n";
        break;

    case 5:
        system("cls");

        filtragem_por_dilatacao(img_in, img_out);
        salva_img(nome, img_out);

        cout << endl << "Imagem filtrada por dilata��o e salva com sucesso!\n";
        break;

    case 6:
        system("cls");
        converte_para_cinza(img_in, img_out);
        salva_img(nome, img_out);

        cout << endl << "Imagem convertida em tons de cinza e salva com sucesso!\n";
        break;

 }
    return 0;
}
