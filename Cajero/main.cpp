#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
string stringchar();
int dbin (int);
string bin (int);
bool sschar(string);
bool eusuario(string);
void añadirusuario(string,string,string);

int main()
{
    int U;
    string binario;
    bool encendido=true;
    while(encendido){
        cout << "BIENVENIDO AL CAJERO AUTOMATICO" << endl;
        cout<<"Ingrese 1 para acceder al cajero como administrador, 2 para acceder como usuario o 3 para cerrar el programa: ";
        cin>>U;
        while(U<1 || U>3){
            cout<<"Ingrese un movimiento valido: ";
            cin>>U;
        }
        if (U==1){
            binario=stringchar();
            bool correc=sschar(binario);
            if (correc){
                cout<<"Acceso habilitado"<<endl;
                while(correc){
                    int N=0;
                    cout<<"Ingrese 1 para registrar usuarios o 2 para regresar: ";
                    cin>>N;
                    while(N<1 || N>2){
                        cout<<"Ingrese un movimiento valido: ";
                        cin>>N;
                    }
                    if(N==1){
                        string ced, clav, ssaldo;
                        int saldo=0;
                        cout<<"Ingrese su cedula: ";
                        cin>>ced;
                        bool existe=eusuario(ced);
                        if(existe){
                            cout<<"Ingrese la clave del usuario: ";
                            cin>>clav;
                            cout<<"Ingrese el saldo del usuario que tiene que ser mayor que 1000: ";
                            cin>>saldo;
                            while(saldo<1000){
                                cout<<"Ingrese un saldo valido: ";
                                cin>>saldo;
                            }
                            ssaldo=to_string(saldo);
                            añadirusuario(ced,clav,ssaldo);
                        }
                        else{
                            cout<<"El usuario ya existe"<<endl;
                        }
                    }
                    else{
                        correc=false;
                    }
                }
            }
            else{
                cout<<"Acceso denegado"<<endl;
            }

        }

    }


}

string stringchar()
{
    string linea, binario, binf;
    cout<<"Ingrese la clave de administrador: ";
    cin>>linea;
    int num=0;
    char carac=1;
    carac=linea[0];
    for(int i=1;carac!='\0';i++){
        num=carac;
        binario=bin(num);
        binf+=binario;
        carac=linea[i];
    }
    return binf;
}

string bin (int a)
{
    string bina;
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
        bina.push_back('0');
        cont+=1;
    }
    bina+=to_string(vbin);
    return bina;

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
bool sschar(string binario)
{
    ifstream arcs;
    arcs.open("Sudo.txt");
    string clave;
    int b=4;
    int inte=0,intes=b-1,cont=2;
    char aux='\0',aux2='\0';
    getline(arcs,clave);
    while(binario[inte]!='\0'){
        aux=binario[inte];
        while(inte<=intes){
            if(inte<intes){
                if(binario[inte+1]=='0' || binario[inte+1]=='1'){
                    aux2=binario[inte+1];
                    binario[inte+1]=aux;
                }
            }
            else if(inte==intes){
                if(binario[inte-intes]=='0' || binario[inte-intes]=='1'){
                    binario[inte-(b-1)]=aux;
                }
            }
            inte+=1;
            aux=aux2;
        }
        intes=(b*cont)-1;
        cont+=1;
    }
    arcs.close();
    if (clave==binario){
        return true;
    }
    else{
        return false;
    }
}

bool eusuario(string usuario)
{
    ifstream arch;
    arch.open("Basedatos.txt");
    string linea, usuarios;
    int cont=0;
    while(arch.good()){
        getline(arch,linea);
        while(linea[cont]!='\0' && linea[cont]!=':'){
            usuarios.push_back(linea[cont]);
            cont+=1;
        }
        if (usuarios==usuario){
            return false;
        }
    }
    return true;
}

void añadirusuario(string cedula, string clave, string saldo)
{
    ofstream archi;
    archi.open("Basedatos.txt", ios::app);
    cedula+=":";
    cedula+=clave;
    cedula+=",";
    cedula+=saldo;
    archi<<cedula;
    archi<<'\n';
    archi.close();

}
