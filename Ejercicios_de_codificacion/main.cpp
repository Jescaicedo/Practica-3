#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
void cadchar(ifstream&);
void bin(int,ofstream&);
int dbin(int);
void cpchar(ifstream&,int);
void cschar(ifstream&,int);
void stringchar(ifstream&);
void spchar(ifstream&, int);
void sschar(ifstream&,int);

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
    cout<<"Ingrese la semilla de codificacion mayor o igual a 3: ";
    cin>>N;
    while(N<3){
        cout<<"Ingrese una semilla valida: ";
        cin>>N;
    }
    ifstream archch;
    archch.open("Archivo.txt");
    ifstream archb;
    archb.open("Bin.txt");

    if (C==1){
        cadchar(archch);
        if(M==1){
            cpchar(archb,N);
        }
        else if(M==2){
            cschar(archb,N);
        }

    }
    else if(C==2){
        stringchar(archch);
        if(M==1){
            spchar(archb,N);
        }
        else if(M==2){
            sschar(archb,N);
        }
    }
    archch.close();
    archb.close();

}

void cadchar(ifstream& arch)
{
    ofstream arcb;
    arcb.open("bin.txt");
    char array[1000];
    int num=0;
    char carac=1;
    while(arch.good()){
        arch.getline(array,1000);
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

void cpchar(ifstream& archb, int b)
{
    ofstream arcs;
    arcs.open("Solucion.txt");
    int inte=0,inted=0,contc=0, contu=0, cont=2,contca=0,contua=0, contf=1;
    char *array=new char[100000];
    while(archb.good()){
        archb.getline(array,10000);
        for (int i=0;i<=b-1;i++){
            if (array[i]=='0'){
                contc+=1;
                array[i]='1';
            }
            else if(array[i]=='1'){
                contu+=1;
                array[i]='0';
            }
        }
        inte=b;
        inted=(b*cont)-1;
        while(array[inte]!='\0'){
            while(inte<=inted){
                if(contc==contu){
                    if (array[inte]=='0'){
                        contca+=1;
                        array[inte]='1';
                    }
                    else if(array[inte]=='1'){
                        contua+=1;
                        array[inte]='0';
                    }
                }
                else if(contc>contu){
                    if (array[inte]=='0'){
                        contca+=1;
                        if (contf==2){
                            array[inte]='1';
                            contf=0;
                        }
                        contf+=1;
                    }
                    else if(array[inte]=='1'){
                        contua+=1;
                        if (contf==2){
                           array[inte]='0';
                           contf=0;
                        }
                        contf+=1;
                    }
                }
                else if(contc<contu){
                    if (array[inte]=='0'){
                        contca+=1;
                        if (contf==3){
                            array[inte]='1';
                            contf=0;
                        }
                        contf+=1;
                    }
                    else if(array[inte]=='1'){
                        contua+=1;
                        if (contf==3){
                           array[inte]='0';
                           contf=0;
                        }
                        contf+=1;
                    }
                }
                inte+=1;
            }
            contc=contca;
            contu=contua;
            contf=1;
            contca=0;
            contua=0;
            inte=inted+1;
            cont+=1;
            inted=(b*cont)-1;
        }
    arcs<<array;
    arcs<<'\n';
    }
    delete [] array;
    arcs.close();
}

void cschar(ifstream& archb,int b)
{
    ofstream arcs;
    arcs.open("Solucion.txt");
    char *array=new char[100000];
    int inte=0,intes=b-1,cont=2;
    char aux='\0',aux2='\0';
    while(archb.good()){
        archb.getline(array,10000);
        while(array[inte]!='\0'){
            aux=array[inte];
            while(inte<=intes){
                if(inte<intes){
                    if(array[inte+1]=='0' || array[inte+1]=='1'){
                        aux2=array[inte+1];
                        array[inte+1]=aux;
                    }
                }
                else if(inte==intes){
                    if(array[inte-intes]=='0' || array[inte-intes]=='1'){
                        array[inte-(b-1)]=aux;
                    }
                }
                inte+=1;
                aux=aux2;
            }
            intes=(b*cont)-1;
            cont+=1;
        }
        arcs<<array;
        arcs<<'\n';
        inte=0;
        intes=b-1;
        cont=2;
    }
    delete [] array;
    arcs.close();
}

void stringchar(ifstream& arch)
{
    ofstream arcb;
    arcb.open("bin.txt");
    string linea;
    int num=0;
    char carac=1;
    while(arch.good()){
        getline(arch,linea);
        carac=linea[0];
        for(int i=1;carac!='\0';i++){
            num=carac;
            bin(num,arcb);
            carac=linea[i];
        }
        arcb<<'\n';

    }
    arcb.close();
}

void spchar(ifstream& archb, int b)
{
    ofstream arcs;
    arcs.open("Solucion.txt");
    int inte=0,inted=0,contc=0, contu=0, cont=2,contca=0,contua=0, contf=1;
    string array;
    while(archb.good()){
        getline(archb,array);
        for (int i=0;i<=b-1;i++){
            if (array[i]=='0'){
                contc+=1;
                array[i]='1';
            }
            else if(array[i]=='1'){
                contu+=1;
                array[i]='0';
            }
        }
        inte=b;
        inted=(b*cont)-1;
        while(array[inte]!='\0'){
            while(inte<=inted){
                if(contc==contu){
                    if (array[inte]=='0'){
                        contca+=1;
                        array[inte]='1';
                    }
                    else if(array[inte]=='1'){
                        contua+=1;
                        array[inte]='0';
                    }
                }
                else if(contc>contu){
                    if (array[inte]=='0'){
                        contca+=1;
                        if (contf==2){
                            array[inte]='1';
                            contf=0;
                        }
                        contf+=1;
                    }
                    else if(array[inte]=='1'){
                        contua+=1;
                        if (contf==2){
                           array[inte]='0';
                           contf=0;
                        }
                        contf+=1;
                    }
                }
                else if(contc<contu){
                    if (array[inte]=='0'){
                        contca+=1;
                        if (contf==3){
                            array[inte]='1';
                            contf=0;
                        }
                        contf+=1;
                    }
                    else if(array[inte]=='1'){
                        contua+=1;
                        if (contf==3){
                           array[inte]='0';
                           contf=0;
                        }
                        contf+=1;
                    }
                }
                inte+=1;
            }
            contc=contca;
            contu=contua;
            contf=1;
            contca=0;
            contua=0;
            inte=inted+1;
            cont+=1;
            inted=(b*cont)-1;
        }
    arcs<<array;
    arcs<<'\n';
    }
    arcs.close();
}

void sschar(ifstream& archb,int b)
{
    ofstream arcs;
    arcs.open("Solucion.txt");
    string array;
    int inte=0,intes=b-1,cont=2;
    char aux='\0',aux2='\0';
    while(archb.good()){
        getline(archb,array);
        while(array[inte]!='\0'){
            aux=array[inte];
            while(inte<=intes){
                if(inte<intes){
                    if(array[inte+1]=='0' || array[inte+1]=='1'){
                        aux2=array[inte+1];
                        array[inte+1]=aux;
                    }
                }
                else if(inte==intes){
                    if(array[inte-intes]=='0' || array[inte-intes]=='1'){
                        array[inte-(b-1)]=aux;
                    }
                }
                inte+=1;
                aux=aux2;
            }
            intes=(b*cont)-1;
            cont+=1;
        }
        arcs<<array;
        arcs<<'\n';
        inte=0;
        intes=b-1;
        cont=2;
    }
    arcs.close();
}
