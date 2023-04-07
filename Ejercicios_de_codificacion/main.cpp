#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
ifstream cadchar(ifstream &);
void bin(int,ofstream&);
int dbin(int);

int main()
{
    int N=0, M=0,C=0;
    cout<<"Ingrese 1 para codificar utilizando arreglos de caracteres o 2 para utilizar string: ";
    cin>>C;
    while(C<1 || C>2){
        cout<<"Ingrese un numero valido valido: ";
        cin>>C;
    }
    cout<<"Ingrese el 1 o 2 para eligir el metodo de codificacion: ";
    cin>>M;
    while(M<1 || M>2){
        cout<<"Ingrese un metodo valido: ";
        cin>>M;
    }
    ifstream archch;
    archch.open("Archivo.txt");

    if (C==1){
        cadchar(archch);
    }
    archch.close();

}

ifstream cadchar(ifstream &arch)
{
    ofstream arcb;
    arcb.open("bin.txt");
    char array[256];
    int num=0;
    char carac=1;
    while(arch.good()){
        arch.getline(array,256);
        carac=array[0];
        for(int i=1;carac!='\0';i++){
            num=carac;
            bin(num,arcb);
            carac=array[i];
        }
        arcb<<'\n';

    }
    arcb.close();
}

void bin (int a, ofstream& arcb)
{
    int bin=0, res=0, contc=0, ceroa=0;
    bool ban=true;
    while (a!=0){
        res=a%2;
        bin=(bin*10)+res;
        a/=2;
        if (res==0 && ban==true){
            contc+=1;
        }
        else{
            ban=false;
        }
    }
    int cont=0, ceros=1;
    while (cont<contc){
        ceros*=10;
        cont+=1;
    }
    cont=0;
    int vbin=0;
    while (bin!=0){
        res=bin%10;
        vbin=(vbin*10)+res;
        bin/=10;
    }
    vbin*=ceros;
    ceroa=dbin(vbin);
    while(cont<ceroa){
        arcb<<'0';
        cont+=1;
    }
    arcb<<vbin;

}

int dbin (int b)
{
    if(b<=1){
        return 7;
    }
    else if(b<=11){
        return 6;
    }
    else if(b<=111){
        return 5;
    }
    else if(b<=1111){
        return 4;
    }
    else if(b<=11111){
        return 3;
    }
    else if(b<=111111){
        return 2;
    }
    else if(b<=1111111){
        return 1;
    }
    else{
        return 0;
    }

}
