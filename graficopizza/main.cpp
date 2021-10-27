#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;


/* o que a proxima função faz é
separar as strings que possuem mais de um sintoma
como por exemplo : dor de cabeça,tosse,febre.
*n é a quantidade de strings que o vetor sintomas tem.
*/
void Sintomas::separar (int *n){
string aux;
int num=0;
int a;
aux=sintomas[*n];
a=aux.find(',');
stringstream sep(sintomas[*n]);
while(a!=(-1)){
    num++;
    a=aux.find(',',a+1);
}
num=num+1;

if(num>1){
for(int i=0;i<num;i++){
   getline(sep,sintomas[*n],',');
   if(i!=num-1){
   (*n)++;
   }
}
}
}

void Sintomas::setsintomas (string s,int *n){
    sintomas[*n] = s;
}


/* essa função vai colocar no array sinunic
   como o nome diz, todos os sintomas unicos para
   na proxima função contar quantos de cada existem
*/
void Dados::pegaunicos (int *n){
int x=0;
// o int ateonde vai ser o indice limitador dos vetores
// sintunic e quant para a leitura futura.
ateonde=0;
for(int i=1;i<*n;i++){
// esse for roda por todos os strings de sintomas e vai colocando
// em sintunic todos os que são unicos comparando no proprio array se ele já está lá.
    for (int j=0;j<=ateonde;j++){
        if(sintomas[i]!=sintunic[j]){
            x++;
        }
    }
    if(x==ateonde+1){
    sintunic[ateonde]=sintomas[i];
    ateonde++;
    }
    x=0;
}
}


//essa função verá quantas vezes cada sintoma aparece,
//o indice do sintoma unico vai ser igual ao indice do array quant
void Dados::buscaquant (int *n){
for (int i=0;i<=ateonde;i++){
        quant[i]=0;
    for(int j=0;j<*n;j++){
        if(sintomas[j]==sintunic[i]){
            quant[i]++;
        }
    }
}


}


// essa função como o nome diz irá ordenar
// para quando começar a criação do gui, aparece do maior para o menor.
void Dados::ordena (){
int aux1;
string aux2;
for(int i=0;i<ateonde;i++){
    for (int j=i+1;j<ateonde;j++){
        if(quant[i]<quant[j]){
            aux1=quant[i];
            aux2=sintunic[i];
            quant[i]=quant[j];
            sintunic[i]=sintunic[j];
            quant[j]=aux1;
            sintunic[j]=aux2;
        }
    }
}
}

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    Dados sin;
    // vai procurar e abrir o .csv
    ifstream ip("dados-se.csv");
    //erro caso não ache o arquivo
    if(!ip.is_open()) cout << "ERROR: File Open" << endl;

    string s;
    int x=0;
    int *n;
    n=&x;
    string descarta;

    /* esse while vai ler ate o final do arquivo csv
    e alem disso os getline com a string descarta
    vao pular ate a parte dos sintomas do arquivo e tambem
    pular linhas para nao ter que ler todas as 240k linhas
    no fim vão ficar 10k+ strings.
    */
    while(ip.good()){
        for(int i=0;i<4;i++){
            getline(ip,descarta,';');
        }

        getline(ip,s,';');

        sin.setsintomas(s,n);

        sin.separar(n);

        for(int i=0;i<25;i++){
            getline(ip,descarta,'\n');
        }
        (*n)++;

    }

    // sequencia de chamada das funções

    sin.pegaunicos(n);

    sin.buscaquant(n);

    sin.ordena();

    ip.close();



    // toda a parte visual foi feita aqui mesmo no main.cpp

    QApplication apie(argc, argv);

    // fiz isso devido a 2 dados problematicos que aparecem
    // no sintunic com menos de 10 ocorrencias.
    sin.ateonde=sin.ateonde-2;

    // tive que criar esse array de QString
    //porque o series->append não aceita string normal.
    QString qstr[sin.ateonde];

    //so passa de um pra outro
    for(int i=0;i<sin.ateonde;i++){
        qstr[i] = QString::fromStdString(sin.sintunic[i]);
    }

    QPieSeries *series = new QPieSeries();

    //vai criar as fatias da pizza com seus respectivos
    //nomes e valores(porcentagem)
    for(int i=0;i<sin.ateonde;i++){
        series->append(qstr[i],sin.quant[i]);
    }

    // daqui pra baixo so vai ser a parte visual do grafico
    // titulo, legenda, destaque, tamanhos, etc.
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Sintomas covid-19 e de outras doenças respiratorias em Sergipe (03-12/20) / Fonte: dados.gov.br");
    chart->legend()->setVisible(false);


    for(int i=0;i<sin.ateonde;i++){
        // esses ifs sao para ajeitar o design e a posição dos textos das fatias
        // não achei uma forma de separar o texto da legenda do das fatias, então coloquei
        // o sintoma junto com sua devida porcentagem e sem legenda.

        if(i==9){
            QPieSlice *slice1 = series->slices().at(i);
            slice1->setLabelVisible();
            slice1->setLabelArmLengthFactor(0.3);
            //concatenação do sintoma com sua porcentagem.
            qstr[i]=qstr[i]+"/ "+QString("%1%").arg(100*slice1->percentage(), 0, 'f', 1);
            slice1->setLabel(qstr[i]);
        }
        else if(i==8){
            QPieSlice *slice1 = series->slices().at(i);
            slice1->setLabelVisible();
            slice1->setLabelArmLengthFactor(0.22);
            qstr[i]=qstr[i]+"/ "+QString("%1%").arg(100*slice1->percentage(), 0, 'f', 1);
            slice1->setLabel(qstr[i]);
        }
        else if(i==1){
            QPieSlice *slice1 = series->slices().at(i);
            slice1->setExploded();
            slice1->setLabelVisible();
            qstr[i]=qstr[i]+"/ "+QString("%1%").arg(100*slice1->percentage(), 0, 'f', 1);
            slice1->setLabel(qstr[i]);
        } else{
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
        qstr[i]=qstr[i]+"/ "+QString("%1%").arg(100*slice->percentage(), 0, 'f', 1);
        slice->setLabel(qstr[i]);
        }
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //definições da janela do gráfico:

    QMainWindow window;

    window.setCentralWidget(chartView);
    window.resize(900,600);
    window.show();

    return apie.exec();
    // fim. fin. the end.
}
