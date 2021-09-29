#include "files.h"
#include <conio.h>

int main()
{
    system("chcp 65001");


    cout<<"\n\n\n\n\t\t\t\tTRANSFORMAR el formato de ARCHIVOS de Datos de EIS\n"
          "\t\t\t\t\t   \" de WaveForm a ZView 3.2b\"\n\n\n";

    Files files;

    files.modifyEISfile();

    getch();
    return 0;
}
