#include<iostream>
using namespace std;
#include <cstring>

class Fecha{
private:
    int dia,mes, anio;
public:
    void Cargar(){
        cin>>dia;
        cin>>mes;
        cin>>anio;
    }
    void Mostrar(){
        cout<<dia<<"/";
        cout<<mes<<"/";
        cout<<anio<<endl;
    }
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}

    void setDia(int d){dia=d;}
    void setMes(int m){mes=m;}
    void setAnio(int a){anio=a;}

};
void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}


class Partidos{
    private:
        int CD_partido;
        int CD_sede;
        int CD_local;
        int CD_visitante;
        Fecha Fecha_partido;
        char Nombre_arbitro[30];
        bool Estado;
    public:
         Partidos(int p = 0, int s=0, int l=0 , int v=0, Fecha c= Fecha(), bool e = false, const char* a="ss"){
            CD_partido = p;
            CD_sede=s;
            CD_local = l;
            CD_visitante = v;
            Estado = e;
            Fecha_partido=c;
             strcpy(Nombre_arbitro, a);

        }
        void setCD_partido(int p){CD_partido=p;}
        void setCD_sede(int s){CD_sede=s;}
        void setCD_local(int l){CD_local=l;}
        void setCD_visitante(int v){CD_visitante=v;}
        void setFecha_partido(Fecha t){Fecha_partido=t;};
        void setNombrearbitro(const char *n){strcpy(Nombre_arbitro,n);}
        void setEstado(bool e){Estado=e;}

       int getCD_partido(){return CD_partido;}
       int getCD_sede(){return CD_sede;}
       int getCD_local(){return CD_local;}
       int getCD_visitante(){return CD_visitante;}
        const char *get_Nombrearbitro(){return Nombre_arbitro;}
       bool getEstado(){return Estado;}

      void Mostrar(){
        cout<<CD_partido<<endl;
        cout<<CD_sede<<endl;
        cout<<CD_local<<endl;
        cout<<CD_visitante<<endl;
         cout<<Nombre_arbitro<<endl;
        Fecha_partido.Mostrar();
        }
      void Cargar(){
        cout<<"CD_partido"<<endl;
        cin>>CD_partido;
        cout<<"CD_sede"<<endl;
        cin>>CD_sede;
        cout<<"CD_local"<<endl;
        cin>>CD_local;
        cout<<"CD_visitante"<<endl;
        cin>>CD_visitante;
          cout<<"arbitro"<<endl;
        cargarCadena(Nombre_arbitro,29);
        Fecha_partido.Cargar();
        Estado=true;



        }

     bool operator == (const Partidos &a) const {
          if(CD_partido==a.CD_partido){return true;}
          else{return false;}
     }

};
    class ArchivoPartido{

        private:
        char nombre[30];
        public:
        ArchivoPartido(const char *n){
        strcpy(nombre, n);}

        ArchivoPartido() {
        strcpy(nombre, "partidos.dat");}

        Partidos leerRegistro(int pos){
            Partidos reg;
            reg.setEstado(false);
            FILE *p;
            p=fopen(nombre, "rb");
            if(p==NULL) return reg;
            fseek(p, sizeof reg*pos,0);
            fread(&reg, sizeof reg,1, p);
            fclose(p);
            return reg;
        }

        int contarRegistros(){
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0, SEEK_END);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(Partidos);
        }
        bool grabarRegistro(Partidos reg){
            FILE *p;
            p=fopen(nombre, "ab+");
            if(p==NULL) return false;
            bool escribio=fwrite(&reg, sizeof reg,1, p);
            fclose(p);
            return escribio;
        }
    };




int main (){
    int opc;
     while(true){
        system("cls");
        cout<<"MENU PARTIDOS "<<endl;
        cout<<"------------------------ "<<endl;
        cout<<"1. ALTA REGISTRO "<<endl;
        cout<<"2. BAJA LOGICA "<<endl;
        cout<<"3. LISTAR REGISTROS "<<endl;
        cout<<"0. SALIR DEL PROGRAMA "<<endl;
        cout<<"------------------------- "<<endl;
        cout<<"OPCION "<<endl;
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: {  Partidos a;
                        a.Cargar();
                        ArchivoPartido b("partidos.dat");
                        if(b.grabarRegistro(a)){cout<<"SE GUARDO REGISTRO"<<endl;}
                        else{cout<<"NO SE GUARDO REGISTRO"<<endl;}

                    }
                    break;

            case 2: {
                         int posicion;
                         cout<<"ingrese posicion "<<endl;
                         cin>>posicion;
                         ArchivoPartido b("partidos.dat");
                         Partidos a;
                         a=b.leerRegistro(posicion);
                         a.setEstado(false);
                         if(b.grabarRegistro(a)){cout<<"SE REALIZO BAJA LOGICA"<<endl;}
                         else{cout<<"NO SE REALIZO LA BAJA LOGICA"<<endl;}



                    }
                break;
            case 3: {
                        ArchivoPartido b("partidos.dat");
                        int tam=b.contarRegistros();
                        Partidos a;
                        for (int x=0 ; x<tam; x++){

                            a=b.leerRegistro(x);
                            a.Mostrar();}
                    }

                break;


            case 0:{ return 0;}
                break;

        }
        system("pause");
    }


    return 0;
}

