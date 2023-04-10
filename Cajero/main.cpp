#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
string stringchar(string);
int dbin (int);
string bin (int);
string sschar(string);
bool eusuario(string);
bool claveadmin(string);
void añadirusuario(string,string,string);
void iniciarsesion(string,bool* ,int*,string*);
void cambiodinero(string,int,string);
void transaccionescod(int,string, string);

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
            string admin;
            cout<<"Ingrese la clave de administrador: ";
            cin>>admin;
            binario=stringchar(admin);
            binario=sschar(binario);
            bool correc=claveadmin(binario);
            if (correc){
                cout<<"Acceso habilitado"<<endl;
                while(correc){
                    cout<<"Ingrese 1 para registrar usuarios o 2 para regresar: ";
                    cin>>U;
                    while(U<1 || U>2){
                        cout<<"Ingrese un movimiento valido: ";
                        cin>>U;
                    }
                    if(U==1){
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
        else if(U==2){
            string cedula, contra;
            cout<<"Ingrese su cedula: ";
            cin>>cedula;
            bool iniciado=false;
            int dinero=0;
            iniciarsesion(cedula,&iniciado,&dinero,&contra);
            while(iniciado){
                cout<<"Ingrese 1 para ver saldo, 2 para retirar dinero o 3 para regresar: ";
                cin>>U;
                while(U<1 || U>3){
                    cout<<"Ingrese un movimiento valido: ";
                    cin>>U;
                }
                if(U==1){
                    if (dinero>=1000){
                        dinero-=1000;
                    }
                    transaccionescod(1000,cedula,"paga");
                    cout<<"Su saldo es de "<<dinero<<endl;
                }
                else if(U==2){
                    if (dinero>=1000){
                        dinero-=1000;
                    }
                    int retiro=0;
                    cout<<"Ingrese el dinero que desea retirar mayor o igual a 1000: ";
                    cin>>retiro;
                    while (retiro<1000 || retiro>dinero){
                        if(retiro<1000){
                            cout<<"El retiro tiene que ser mayor a 1000"<<endl;
                        }
                        else{
                            cout<<"El retiro deseado supera el saldo de la cuenta"<<endl;
                        }
                        cout<<"Ingrese un retiro valido: ";
                        cin>>retiro;
                    }
                    dinero-=retiro;
                    cout<<"El dinero ha sido depositado en bandeja"<<endl;
                    transaccionescod(retiro,cedula,"retira");
                }
                else{
                    iniciado=false;
                    cambiodinero(cedula,dinero,contra);
                }
            }
        }
        else{
            encendido=false;
        }

    }


}

string stringchar(string linea)
{
    string binario, binf;
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
string sschar(string binario)
{
    int b=4;
    int inte=0,intes=b-1,cont=2;
    char aux='\0',aux2='\0';
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
    return binario;
}

bool claveadmin(string binario)
{
    ifstream arcs;
    arcs.open("Sudo.txt");
    string clave;
    getline(arcs,clave);
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
        cont=0;
        usuarios="";
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
    cedula+=".";
    archi<<cedula;
    archi<<"\n";
    archi.close();

}

void iniciarsesion(string usuario, bool* manejo, int* saldo, string* clave)
{
    ifstream arch;
    arch.open("Basedatos.txt");
    string linea, usuarios, clavev,dinero;
    int cont=0;
    bool encontrado=false;
    while(arch.good()){
        getline(arch,linea);
        while(linea[cont]!='\0' && linea[cont]!=':'){
            usuarios.push_back(linea[cont]);
            cont+=1;
        }
        if (usuarios==usuario){
            cout<<"Ingrese su clave: ";
            cin>>*clave;
            cont+=1;
            encontrado=true;
            while(linea[cont]!='\0' && linea[cont]!=','){
                clavev.push_back(linea[cont]);
                cont+=1;
            }
            if(*clave==clavev){
                cout<<"Acceso validado"<<endl;
                *manejo=true;
                cont+=1;

                while(linea[cont]!='\0' && linea[cont]!='.'){
                    dinero.push_back(linea[cont]);
                    cont+=1;
                }
                *saldo=stoi(dinero);
            }
            else{
                cout<<"Clave incorrecta"<<endl;
                *manejo=false;
            }
        }
        cont=0;
        usuarios="";
    }
    if(!encontrado){
        cout<<"El usuario no fue encontrado"<<endl;
        *manejo=false;
    }

}

void cambiodinero(string cedula,int saldo,string clave)
{
    string lineanueva, dinero;
    lineanueva+=cedula;
    lineanueva+=":";
    lineanueva+=clave;
    dinero=to_string(saldo);
    lineanueva+=",";
    lineanueva+=dinero;
    lineanueva+=".";
    ifstream archivo;
    ofstream archc;
    archc.open("auxbase.txt");
    archivo.open("Basedatos.txt");
    string linea;
    while (archivo.good()) {
        getline(archivo,linea);
        if (linea.find(cedula) != string::npos) {
            linea = lineanueva;
        }
        archc<<linea;
        archc<<"\n";
    }
    archivo.close();
    archc.close();
    ifstream archc1;
    ofstream archivo1;
    archc1.open("auxbase.txt");
    archivo1.open("Basedatos.txt");
    while (archc1.good()) {
        getline(archc1,linea);
        archivo1<<linea;
        archivo1<<"\n";
    }
    archivo1.close();
    archc1.close();
    ofstream archivo2("auxbase.txt", ios::out | ios::trunc);
    archivo2.close();
}

void transaccionescod(int valor,string cedula, string accion)
{
    string dinero;
    dinero=to_string(valor);
    cedula+=accion;
    cedula+=dinero;
    cedula=stringchar(cedula);
    cedula=sschar(cedula);
    ofstream arch;
    arch.open("historialtransacciones.txt", ios::app);
    arch<<cedula;
    arch<<"\n";
    arch.close();

}
