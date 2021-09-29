#include "files.h"



Files::Files(){

    namingTXTfile();
    fileTXT.open ("./EIS DATASET/"+fileNameTXT,ios::in);
    checkingTXTfile();
    fileEIS.open ("./EIS DATASET/"+fileName,ios::out);//ios::in|ios::out);
    checkingEISfile();

}
Files::~Files(){
    fileTXT.close();
    fileEIS.close();

}

void Files::namingTXTfile(){
    string nameTXT;
    cout<<"\nA continuación deberá ingresar el nombre del archivo de la siguiente forma:"
          "\n\t- NOMBRE DEL ARCHIVO:"
          "\n\t\t   Escrbia el nombre del archivo sin la extención"
          "\n\t\t   Por ejemplo, si el archivo se llama \"EIS1.txt\", ingrese \"EIS1\""
          "\n\t- UBICACIÓN DEL ARCHIVO"
          "\n\t\ta- Si el archivo está en la carpeta EIS DATASET."
          "\n\t\t   Por ejemplo, para abrir el archivo \"EIS1.txt\" escribo \"EIS1\""
          "\n\t\tb- Escriba la dirección completa del archivo."
          "\n\t\t   Por ejemplo, para abrir el archivo en la ubicación \"c:/EISlibrary/EIS1.txt\" escribo \"c:/EISlibrary/EIS1\""
          "\n\nNombre del archivo: ";
    cin>>fileNameTXT;
    fileName=fileNameTXT+".zview.txt";

    fileNameTXT += ".txt";
}
void Files::checkingTXTfile(){
    if(fileTXT.fail()){
        cout<<"\nEl archivo \""<<fileNameTXT<<"\" NO se ha podido abrir. "
              "\n---Verifique el nombre y vuelva a ejecutar el programa.---"<<endl;
        exit(1);
    }
    else{
        cout<<"\nEl archivo \""<<fileNameTXT<<"\" se ha abierto con exito."<<endl;
    }
}

void Files::checkingEISfile(){
    if(fileEIS.fail()){
        cout<<"\nEl archivo \""<<fileName<<"\" no se ha podido crear."<<endl;
        exit(1);
    }
    else{
        cout<<"\nEl archivo \""<<fileName<<"\" se ha creado con exito."<<endl<<endl;
        flagEIS = true;
    }
}
void Files::modifyEISfile(){
    bool itsutf16=false, itsutf8=false;

    fileTXT.seekg(0,ios::beg);//me posiciono al principio
    int countline=0, nHeadsLine=0;
    string line1, line2;

    int columnFreq=0, columnPhase=0, columnReal=0, postab=0;

    while (getline(fileTXT, line1)){
        string titlesline,numbersline;titlesline.clear();numbersline.clear(); numbersline="";



        /*
 * 0- leer la linea de los títulos (frec, z, -z) etc;
 *      -asignar un auxiliar numérico a cada uno (frec=1, z=2, etc)
 *      -al buscar el valor en una línea buscar al que corresponda all auxiliar numérico (si frec=4, busca el cuarto número de la fila)
 * 1- lee las líneas hasta que encuentra una que diga las primeras letras sean "frecuencia"; entonces salta a la siguiente línea.
 * 2- lee copia toda la línea a un string (string linea)
 * 3- lee los valores hasta que encuentra la primera \t (tabulación).
 * 4- copia esos valores a otro string (string frecuencia)
 * 5- sigo leyendo el string línea hasta el tercer (revisar si es el tercer o cuarto num) \t y elimina ese pedazo (elimino la tabulación incluída)
 * 6- leo hasta la primer tabulación y copio ese número en otro string (string imaginario)
 * 7- elimino hasta la primer \t (tabulación incluída)
 * 8- copio el primer número (hasta la primer tabulación) a un string (string real)
 * 9- copio en el archivo EIS string real, inserto \t, string imaginario, \t y string frecuencia.
 *
 *
*/





    //  ####################################### UTF-8 #################################################
        string line;
        line=line1;

        if ((line.find("freq")!=string::npos||line.find("Freq")!=string::npos||line.find("FREQ")!=string::npos)&&itsutf16==false){
            itsutf8=true;
            columnFreq=0;columnReal=0;columnPhase=0;postab=0;
            nHeadsLine=countline;
            if (line.find("freq")>0||line.find("Freq")>0||line.find("FREQ")>0){
                while((line.find("freq")!=string::npos||line.find("Freq")!=string::npos||line.find("FREQ")!=string::npos)&&postab!=string::npos){
                    postab = line.find("\t");
                    line = line.substr(postab+1, line.length());
                    columnFreq++;
                }
            }
            postab=0;
            line=line1;
            if (line.find("imag")>0||line.find("Imag")>0||line.find("IMAG")>0){//||line.find("amp")>0||line.find("Amp")>0||line.find("AMP")>0){
                while((line.find("\timag")!=string::npos||line.find("\tImag")!=string::npos||line.find("\tIMAG")!=string::npos)&&postab!=string::npos){//&&line.length()>linecompare){//||line.find("amp")!=string::npos||line.find("Amp")!=string::npos||line.find("AMP")!=string::npos)&&postab!=string::npos){
                    postab = line.find("\t");
                    line = line.substr(postab+1, line.length());
                    columnPhase++;
                }
            }
            postab=0;
            line=line1;
            if (line.find("z ")>0||line.find("Z ")>0||line.find("real")>0||line.find("Real")>0||line.find("REAL")>0){
                while((line.find("\tz ")!=string::npos||line.find("\tZ ")!=string::npos||line.find("\treal")!=string::npos||line.find("\tReal")!=string::npos||line.find("\tREAL")!=string::npos)&&postab!=string::npos){
                    postab = line.find("\t");
                    line = line.substr(postab+1, line.length());
                    columnReal++;
                }
            }
            columnFreq=columnFreq-1;
            columnPhase=columnPhase;
            columnReal=columnReal;
        }
            double imagInt=0.0;

        if(itsutf8&&countline>nHeadsLine&&line.length()>1&&itsutf16==false){

            line=line1;
            postab=0;
            for(int i=0;i<columnFreq;i++){
                postab = line.find("\t");
                line = line.substr(postab+1, line.length());
            }
            postab = line.find("\t");
            line = line.substr(0,postab+1);

            fileEIS<<line<<"\t";

            line=line1;
            postab=0;
            for(int i=0;i<columnReal;i++){
                postab = line.find("\t");
                line = line.substr(postab+1, line.length());
            }
            postab = line.find("\t");
            line = line.substr(0,postab+1);
            fileEIS<<line<<"\t";

            line=line1;
            postab=0;
            for(int i=0;i<columnPhase;i++){
                postab = line.find("\t");
                line = line.substr(postab+1, line.length());
            }
            postab = line.find("\t");
            line = line.substr(0,postab+1);
            fileEIS<<line<<endl;

        }
        countline++;
    }

    cout<<"\n\n\t|################### 100% ##################|"
          "\n\t\t     PROCESO FINALIZADO."
          "\n\n ---Presione una tecla para cerrar.---\n\n";
    int countdata=0;

    if(itsutf8) countdata=countline-(nHeadsLine+1);

    fileEIS.clear();
    fileEIS.seekp(0,ios::beg);

}
