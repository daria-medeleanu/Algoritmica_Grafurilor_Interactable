#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
int nrMaxDenumireNoduri,r=20,nrLinii=0,nrDeNoduriCurent=0,meniu=1,ecran_neorientat=0,ecran_orientat=0;
char numeNod[5],mesaje[20][100];
struct graf
{
    float x,y;///coodonatele nodului
    int nrLegaturi;
    int exista_nod;
} G[16];
struct matrice_adiacenta_neorientata
{
    float x_capat,y_capat;
    int exista_muchie;
    char cost[10];
} M[16][16];
struct matrice_adiacenta_orientata
{
    float x1_capat,y1_capat,x2_capat,y2_capat,x1_sageata,y1_sageata,x2_sageata,y2_sageata,x_arc,y_arc;
    int exista_arc;
    char cost[10];
} N[16][16];
struct vector_costuri
{
    int capat1,capat2,cost;
} C[400];
void OpenGraph()
{
    initwindow(1200,625,"Algoritmica Grafurilor");
}
void InitWindowMenu()
{
    readimagefile("meniu.jpg",0,0,1200,625);
    setcolor(BLACK);
    setbkcolor(WHITE);
    settextstyle(0,0,4);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(600,175,"ALGORITMICA GRAFURILOR");
    rectangle(425,225,775,275);
    settextstyle(0,0,2);
    outtextxy(600,250,"Grafuri neorientate");
    rectangle(425,325,775,375);
    outtextxy(600,350,"Grafuri orientate");
    rectangle(550,425,650,475);
    outtextxy(600,450,"Exit");
    setbkcolor(LIGHTGRAY);
    setfillstyle(1,LIGHTGRAY);
}
void InitWindow1()
{
    setbkcolor(LIGHTGRAY);
    setfillstyle(1,LIGHTGRAY);
    bar(0,0,1200,625);
    outtextxy(600,30,"GRAFURI NEORIENTATE");
    rectangle(10,10,110,60);
    outtextxy(60,35,"Exit");
    rectangle(1000,10,1190,60);
    outtextxy(1095,35,"Spre Graf Orientat ->");
    rectangle(325,475,475,525);
    outtextxy(400,500,"Adaugare nod");
    rectangle(525,475,675,525);
    outtextxy(600,500,"Adaugare muchie");
    rectangle(725,475,875,525);
    outtextxy(800,500,"Adaugare cost");
    rectangle(325,550,475,600);
    outtextxy(400,575,"Stergere nod");
    rectangle(525,550,675,600);
    outtextxy(600,575,"Stergere muchie");
    rectangle(725,550,875,600);
    outtextxy(800,575,"Stergere graf");
    rectangle(920,175,1040,225);
    outtextxy(980,200,"BFS");
    rectangle(1060,175,1180,225);
    outtextxy(1120,200,"DFS");
    rectangle(920,250,1040,300);
    outtextxy(980,275,"Prim");
    rectangle(1060,250,1180,300);
    outtextxy(1120,275,"Kruskal");
    rectangle(920,325,1040,375);
    outtextxy(980,350,"Conexitate");
    rectangle(1060,325,1180,375);
    outtextxy(1120,350,"Componenta");
    line(300,450,900,450);
    line(0,75,1200,75);
    line(300,75,300,625);
    line(900,75,900,625);
    line(300,150,0,150);
    line(900,150,1200,150);
    outtextxy(150,110,"OUTPUT LOG");
    outtextxy(1050,110,"ALGORITMI");
}
void InitWindow2()
{
    setbkcolor(LIGHTGRAY);
    setfillstyle(1,LIGHTGRAY);
    bar(0,0,1200,625);
    outtextxy(600,30,"GRAFURI ORIENTATE");
    rectangle(10,10,200,60);
    outtextxy(105,35,"<- Spre graf neorientat");
    rectangle(1090,10,1190,60);
    outtextxy(1140,35,"Exit");
    rectangle(325,475,475,525);
    outtextxy(400,500,"Adaugare nod");
    rectangle(525,475,675,525);
    outtextxy(600,500,"Adaugare arc");
    rectangle(725,475,875,525);
    outtextxy(800,500,"Adaugare cost");
    rectangle(325,550,475,600);
    outtextxy(400,575,"Stergere nod");
    rectangle(525,550,675,600);
    outtextxy(600,575,"Stergere arc");
    rectangle(725,550,875,600);
    outtextxy(800,575,"Stergere graf");
    rectangle(920,175,1040,225);
    outtextxy(980,200,"BFS");
    rectangle(1060,175,1180,225);
    outtextxy(1120,200,"DFS");
    rectangle(920,250,1040,300);
    outtextxy(980,275,"Dijkstra");
    rectangle(1060,250,1180,300);
    outtextxy(1120,275,"Bellman-Ford");
    rectangle(920,325,1040,375);
    outtextxy(980,350,"Floyd-Warshall");
    rectangle(1060,325,1180,375);
    outtextxy(1120,350,"Ford-Fulkerson");
    rectangle(920,400,1040,450);
    outtextxy(980,425,"Tare conex");
    rectangle(1060,400,1180,450);
    outtextxy(1120,425,"Componenta");
    line(300,450,900,450);
    line(0,75,1200,75);
    line(300,75,300,625);
    line(900,75,900,625);
    line(300,150,0,150);
    line(900,150,1200,150);
    outtextxy(150,110,"OUTPUT LOG");
    outtextxy(1050,110,"ALGORITMI");
}
void InitGraf(graf G[16])
{
    for(int i=1; i<=15; i++)
    {
        G[i].x=G[i].y=0;
        G[i].nrLegaturi=0;
        G[i].exista_nod=0;
    }
    nrMaxDenumireNoduri=0;
    nrDeNoduriCurent=0;
}
void InitMatriceNeorientata(matrice_adiacenta_neorientata M[16][16])
{
    for(int i=1; i<=15; i++)
        for(int j=1; j<=15; j++)
        {
            M[i][j].x_capat=M[i][j].y_capat=0;
            M[i][j].exista_muchie=0;
            M[i][j].cost[0]='*';
        }
}
void InitMatriceOrientata(matrice_adiacenta_orientata N[16][16])
{
    for(int i=1; i<=15; i++)
        for(int j=1; j<=15; j++)
        {
            N[i][j].x1_capat=N[i][j].y1_capat=N[i][j].x2_capat=N[i][j].y2_capat=N[i][j].x1_sageata=N[i][j].y1_sageata=N[i][j].x2_sageata=N[i][j].y2_sageata=0;
            N[i][j].x_arc=N[i][j].y_arc=0;
            N[i][j].exista_arc=0;
            N[i][j].cost[0]='*';
        }
}
void InitVectorCosturi(vector_costuri C[400])
{
    for(int i=1; i<=400; i++)
    {
        C[i].capat1=C[i].capat2=C[i].cost=0;
    }
}
void spre_graf_neorientat()
{
    cleardevice();
    settextstyle(0,0,3);
    outtextxy(600,300,"LOADING...");
    delay(1500);
    settextstyle(0,0,1);
    setactivepage(1);
    cleardevice();
    InitWindow1();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    InitWindow1();
    delay(1);
    setvisualpage(0);
    InitGraf(G);
    InitMatriceOrientata(N);
    InitMatriceNeorientata(M);
    InitVectorCosturi(C);
    nrLinii=0;///pentru output log
    ecran_neorientat=1;
    ecran_orientat=0;
    meniu=0;
}
void spre_graf_orientat()
{
    cleardevice();
    settextstyle(0,0,3);
    outtextxy(600,300,"LOADING...");
    delay(1500);
    settextstyle(0,0,1);
    setactivepage(1);
    cleardevice();
    InitWindow2();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    InitWindow2();
    delay(1);
    setvisualpage(0);
    InitGraf(G);
    InitMatriceOrientata(N);
    InitMatriceNeorientata(M);
    InitVectorCosturi(C);
    nrLinii=0;///pentru output log
    ecran_orientat=1;
    ecran_neorientat=0;
    meniu=0;
}
void redesenare_ecran_nod_mutat(int nod_exclus)
{
    InitWindow1();
    for(int i=1; i<=nrMaxDenumireNoduri; i++)///redesenarea muchiilor
        if(i!=nod_exclus && G[i].exista_nod==1)
        {
            itoa(i,numeNod,10);
            circle(G[i].x,G[i].y,r);
            outtextxy(G[i].x,G[i].y,numeNod);
        }
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        for(int j=1; j<=nrMaxDenumireNoduri; j++)
            if(i!=nod_exclus && j!=nod_exclus && M[i][j].exista_muchie==1)
            {
                line(M[i][j].x_capat,M[i][j].y_capat,M[j][i].x_capat,M[j][i].y_capat);
                if(M[i][j].cost[0]!='*')
                {
                    outtextxy((M[i][j].x_capat+M[j][i].x_capat)/2,(M[j][i].y_capat+M[i][j].y_capat)/2,M[i][j].cost);
                }
            }
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    for(int i=1; i<=nrLinii; i++)
        {
            outtextxy(10,150+25*i,mesaje[i]);
        }
    settextjustify(CENTER_TEXT,CENTER_TEXT);
}
void redesenare_ecran_nod_mutat_orientat(int nod_exclus)
{
    InitWindow2();
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        if(i!=nod_exclus && G[i].exista_nod==1)
        {
            itoa(i,numeNod,10);
            circle(G[i].x,G[i].y,r);
            outtextxy(G[i].x,G[i].y,numeNod);
        }
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        for(int j=1; j<=nrMaxDenumireNoduri; j++)
            if(i!=nod_exclus && j!=nod_exclus && N[i][j].exista_arc==1)
            {
                if(N[j][i].exista_arc==0)
                {
                    line(N[i][j].x1_capat,N[i][j].y1_capat,N[i][j].x2_capat,N[i][j].y2_capat);
                    line(N[i][j].x1_sageata,N[i][j].y1_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                    line(N[i][j].x2_sageata,N[i][j].y2_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                }
                else if(N[j][i].exista_arc==1)
                {
                    line(N[i][j].x_arc,N[i][j].y_arc,N[i][j].x1_capat,N[i][j].y1_capat);
                    line(N[i][j].x_arc,N[i][j].y_arc,N[i][j].x2_capat,N[i][j].y2_capat);
                    line(N[i][j].x1_sageata,N[i][j].y1_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                    line(N[i][j].x2_sageata,N[i][j].y2_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                }
                if(N[i][j].cost[0]!='*')
                {
                    outtextxy(N[i][j].x_arc, N[i][j].y_arc,N[i][j].cost);
                }
            }
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    for(int i=1; i<=nrLinii; i++)
        {
            outtextxy(10,150+25*i,mesaje[i]);
        }
    settextjustify(CENTER_TEXT,CENTER_TEXT);
}
void redesenare_graf_curent()
{
    InitWindow1();
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        if(G[i].exista_nod==1)
        {
            itoa(i,numeNod,10);
            circle(G[i].x,G[i].y,r);
            outtextxy(G[i].x,G[i].y,numeNod);
        }
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        for(int j=1; j<=nrMaxDenumireNoduri; j++)
            if(M[i][j].exista_muchie==1)
            {
                line(M[i][j].x_capat,M[i][j].y_capat,M[j][i].x_capat,M[j][i].y_capat);
                if(M[i][j].cost[0]!='*')
                {
                    outtextxy((M[i][j].x_capat+M[j][i].x_capat)/2,(M[i][j].y_capat+M[j][i].y_capat)/2,M[i][j].cost);
                }
            }
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    for(int i=1; i<=nrLinii; i++)
        {
            outtextxy(10,150+25*i,mesaje[i]);
        }
    settextjustify(CENTER_TEXT,CENTER_TEXT);
}
void redesenare_graf_curent_orientat()
{
    InitWindow2();
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        if(G[i].exista_nod==1)
        {
            itoa(i,numeNod,10);
            circle(G[i].x,G[i].y,r);
            outtextxy(G[i].x,G[i].y,numeNod);
        }
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        for(int j=1; j<=nrMaxDenumireNoduri; j++)
            if(N[i][j].exista_arc==1)
            {
                if(N[j][i].exista_arc==0)
                {
                    line(N[i][j].x1_capat,N[i][j].y1_capat,N[i][j].x2_capat,N[i][j].y2_capat);
                    line(N[i][j].x1_sageata,N[i][j].y1_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                    line(N[i][j].x2_sageata,N[i][j].y2_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                }
                else if(N[j][i].exista_arc==1)
                {
                    line(N[i][j].x_arc,N[i][j].y_arc,N[i][j].x1_capat,N[i][j].y1_capat);
                    line(N[i][j].x_arc,N[i][j].y_arc,N[i][j].x2_capat,N[i][j].y2_capat);
                    line(N[i][j].x1_sageata,N[i][j].y1_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                    line(N[i][j].x2_sageata,N[i][j].y2_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                }
                if(N[i][j].cost[0]!='*')
                {
                    outtextxy(N[i][j].x_arc, N[i][j].y_arc,N[i][j].cost);
                }
            }
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    for(int i=1; i<=nrLinii; i++)
        {
            outtextxy(10,150+25*i,mesaje[i]);
        }
    settextjustify(CENTER_TEXT,CENTER_TEXT);
}
int gasire_nod_apasat(int x, int y)
{
    int nod_apasat=0;
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
    {
        if(sqrt(pow(x-G[i].x,2)+pow(y-G[i].y,2))<=r && G[i].exista_nod==1)///apasam pe nod
        {
            nod_apasat=i;
            break;
        }
    }
    return nod_apasat;
}
int nod_nesuprapus(int x, int y)
{
    int ok=1,distantaDintreMijlocuri;
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        if(G[i].exista_nod==1)
        {
            distantaDintreMijlocuri=sqrt(pow(x-G[i].x,2)+pow(y-G[i].y,2));
            if(distantaDintreMijlocuri<=2*r)
                ok=0;
        }
    return ok;
}
int nod_neciocnit(int x, int y, int nod_folosit)
{
    int ok=1,distantaDintreMijlocuri;
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        if(nod_folosit!=i && G[i].exista_nod==1)
        {
            distantaDintreMijlocuri=sqrt(pow(x-G[i].x,2)+pow(y-G[i].y,2));
            if(distantaDintreMijlocuri<=2*r)
                ok=0;
        }
    return ok;
}
int input_valid(char input[10])
{
    int input_corect=1;
    if(input[0]=='0'&&input[1]!=NULL)
        input_corect=0;
    else if(input[0]=='-'&&(input[1]=='0'||input[1]==NULL))
        input_corect=0;
    else if(input[0]==NULL)
        input_corect=0;
    else if((input[0]<'0'||input[0]>'9')&&input[0]!='-')
        input_corect=0;
    for(int i=1; i<strlen(input); i++)
    {
        if(input[i]=='-')
            input_corect=0;
        if(input[i]<'0'||input[i]>'9')
            input_corect=0;
    }
    return input_corect;
}
int graf_cu_costuri_valid()
{
    int graf_valid=1;
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        for(int j=1; j<=nrMaxDenumireNoduri; j++)
            if(i!=j&&M[i][j].exista_muchie==1&&M[i][j].cost[0]=='*')
                graf_valid=0;
    return graf_valid;
}
int graf_cu_costuri_valid_orientat()
{
    int graf_valid=1;
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        for(int j=1; j<=nrMaxDenumireNoduri; j++)
            if(i!=j&&N[i][j].exista_arc==1&&N[i][j].cost[0]=='*')
                graf_valid=0;
    return graf_valid;
}
void actualizare_output_log(char prop[100])
{
    if(nrLinii==18)
    {
        bar(0,151,300,1200);
        nrLinii=0;
    }
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    nrLinii++;
    strcpy(mesaje[nrLinii],prop);
    outtextxy(10,150+25*nrLinii,mesaje[nrLinii]);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
}
void adaugare_muchie()
{
    float x_apasat, y_apasat;
    int in_generare=1,nod_1=0,nod_2=0;
    actualizare_output_log("Selectati 2 noduri.");
    while(in_generare)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x_apasat=mousex();
            y_apasat=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            nod_1=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_1==0)
            {
                in_generare=0;
                actualizare_output_log("Graf nemodificat. Muchie neadaugata.");
            }
            else if(G[nod_1].nrLegaturi==nrDeNoduriCurent-1)
            {
                actualizare_output_log("Numar maxim de legaturi.");
                return;
            }
            else
            {
                while(nod_2==0)
                {
                    x_apasat=mousex();
                    y_apasat=mousey();
                    if(x_apasat>=300 && x_apasat<=900 && y_apasat>=75 && y_apasat<=450)
                    {
                        setactivepage(1);
                        cleardevice();
                        redesenare_graf_curent();
                        line(G[nod_1].x,G[nod_1].y,x_apasat,y_apasat);
                        setvisualpage(1);
                        setactivepage(0);
                        cleardevice();
                        redesenare_graf_curent();
                        line(G[nod_1].x,G[nod_1].y,x_apasat,y_apasat);
                        delay(1);
                        setvisualpage(0);
                    }
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        nod_2=gasire_nod_apasat(x_apasat,y_apasat);
                        if(nod_2==0 || nod_1==nod_2 || M[nod_1][nod_2].exista_muchie==1)
                        {
                            in_generare=0;
                            setactivepage(1);
                            cleardevice();
                            redesenare_graf_curent();
                            setvisualpage(1);
                            setactivepage(0);
                            cleardevice();
                            redesenare_graf_curent();
                            delay(1);
                            setvisualpage(0);
                            actualizare_output_log("Graf nemodificat. Muchie neadaugata.");
                            break;
                        }
                        else
                        {
                            in_generare=0;
                            setactivepage(1);
                            cleardevice();
                            redesenare_graf_curent();
                            setvisualpage(1);
                            setactivepage(0);
                            cleardevice();
                            redesenare_graf_curent();
                            delay(1);
                            setvisualpage(0);
                            G[nod_1].nrLegaturi++;
                            G[nod_2].nrLegaturi++;
                            M[nod_1][nod_2].exista_muchie=M[nod_2][nod_1].exista_muchie=1; ///punem in matricea de adiacenta
                            M[nod_1][nod_2].x_capat=G[nod_1].x+r*(G[nod_2].x-G[nod_1].x)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                            M[nod_1][nod_2].y_capat=G[nod_1].y+r*(G[nod_2].y-G[nod_1].y)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                            M[nod_2][nod_1].x_capat=G[nod_2].x+r*(G[nod_1].x-G[nod_2].x)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                            M[nod_2][nod_1].y_capat=G[nod_2].y+r*(G[nod_1].y-G[nod_2].y)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                            line(M[nod_1][nod_2].x_capat,M[nod_1][nod_2].y_capat,M[nod_2][nod_1].x_capat,M[nod_2][nod_1].y_capat);
                            actualizare_output_log("Muchie adaugata.");
                        }
                    }
                }
            }
        }
    }
}
void adaugare_arc()
{
    float x_apasat, y_apasat, x_mijloc_sageata, y_mijloc_sageata, aux_x, aux_y, aux_dist, x1_mij_arc, y1_mij_arc, x2_mij_arc, y2_mij_arc, x_mij, y_mij;
    int in_generare=1,nod_1=0,nod_2=0, aux;
    actualizare_output_log("Selectati 2 noduri.");
    while(in_generare)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x_apasat=mousex();
            y_apasat=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            nod_1=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_1==0)
            {
                in_generare=0;
                actualizare_output_log("Graf nemodificat. Arc neadaugat.");
            }
            else if(G[nod_1].nrLegaturi==nrDeNoduriCurent-1)
            {
                actualizare_output_log("Numar maxim de legaturi.");
                return;
            }
            else
            {
                while(nod_2==0)
                {
                    x_apasat=mousex();
                    y_apasat=mousey();
                    if(x_apasat>=300 && x_apasat<=900 && y_apasat>=75 && y_apasat<=450)
                    {
                        setactivepage(1);
                        cleardevice();
                        redesenare_graf_curent_orientat();
                        line(G[nod_1].x,G[nod_1].y,x_apasat,y_apasat);
                        setvisualpage(1);
                        setactivepage(0);
                        cleardevice();
                        redesenare_graf_curent_orientat();
                        line(G[nod_1].x,G[nod_1].y,x_apasat,y_apasat);
                        delay(1);
                        setvisualpage(0);
                    }
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        nod_2=gasire_nod_apasat(x_apasat,y_apasat);
                        if(nod_2==0 || nod_1==nod_2 || N[nod_1][nod_2].exista_arc==1)
                        {
                            in_generare=0;
                            setactivepage(1);
                            cleardevice();
                            redesenare_graf_curent_orientat();
                            setvisualpage(1);
                            setactivepage(0);
                            cleardevice();
                            redesenare_graf_curent_orientat();
                            delay(1);
                            setvisualpage(0);
                            actualizare_output_log("Graf nemodificat. Arc neadaugat.");
                            break;
                        }
                        else
                        {
                            in_generare=0;
                            setactivepage(1);
                            cleardevice();
                            redesenare_graf_curent_orientat();
                            setvisualpage(1);
                            setactivepage(0);
                            cleardevice();
                            redesenare_graf_curent_orientat();
                            delay(1);
                            setvisualpage(0);
                            G[nod_1].nrLegaturi++;
                            N[nod_1][nod_2].exista_arc=1;///punem in matricea de adiacenta
                            if(N[nod_2][nod_1].exista_arc==0)
                            {
                                N[nod_1][nod_2].x1_capat=G[nod_1].x+r*(G[nod_2].x-G[nod_1].x)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                N[nod_1][nod_2].y1_capat=G[nod_1].y+r*(G[nod_2].y-G[nod_1].y)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                N[nod_1][nod_2].x2_capat=G[nod_2].x+r*(G[nod_1].x-G[nod_2].x)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                N[nod_1][nod_2].y2_capat=G[nod_2].y+r*(G[nod_1].y-G[nod_2].y)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                line(N[nod_1][nod_2].x1_capat,N[nod_1][nod_2].y1_capat,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                N[nod_1][nod_2].x_arc=(N[nod_1][nod_2].x1_capat+N[nod_1][nod_2].x2_capat)/2;
                                N[nod_1][nod_2].y_arc=(N[nod_1][nod_2].y1_capat+N[nod_1][nod_2].y2_capat)/2;
                                x_mijloc_sageata=G[nod_2].x+2*r*(G[nod_1].x-G[nod_2].x)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                y_mijloc_sageata=G[nod_2].y+2*r*(G[nod_1].y-G[nod_2].y)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                aux_x=x_mijloc_sageata-G[nod_2].x;
                                aux_y=y_mijloc_sageata-G[nod_2].y;
                                aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                aux_x=aux_x/aux_dist;
                                aux_y=aux_y/aux_dist;
                                N[nod_1][nod_2].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                N[nod_1][nod_2].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                N[nod_1][nod_2].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                N[nod_1][nod_2].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                line(N[nod_1][nod_2].x1_sageata,N[nod_1][nod_2].y1_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                line(N[nod_1][nod_2].x2_sageata,N[nod_1][nod_2].y2_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                            }
                            else if(N[nod_2][nod_1].exista_arc==1)
                            {
                                N[nod_1][nod_2].x1_capat=G[nod_1].x+r*(G[nod_2].x-G[nod_1].x)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                N[nod_1][nod_2].y1_capat=G[nod_1].y+r*(G[nod_2].y-G[nod_1].y)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                N[nod_1][nod_2].x2_capat=G[nod_2].x+r*(G[nod_1].x-G[nod_2].x)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                N[nod_1][nod_2].y2_capat=G[nod_2].y+r*(G[nod_1].y-G[nod_2].y)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                x_mij=(N[nod_1][nod_2].x1_capat+N[nod_1][nod_2].x2_capat)/2;
                                y_mij=(N[nod_1][nod_2].y1_capat+N[nod_1][nod_2].y2_capat)/2;
                                aux_x=x_mij-N[nod_1][nod_2].x1_capat;
                                aux_y=y_mij-N[nod_1][nod_2].y1_capat;
                                aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                aux_x=aux_x/aux_dist;
                                aux_y=aux_y/aux_dist;
                                x1_mij_arc=x_mij+(2*r/3)*aux_y;
                                y1_mij_arc=y_mij-(2*r/3)*aux_x;
                                x2_mij_arc=x_mij-(2*r/3)*aux_y;
                                y2_mij_arc=y_mij+(2*r/3)*aux_x;
                                if(nod_1>nod_2)
                                {
                                    aux=nod_1;
                                    nod_1=nod_2;
                                    nod_2=aux;
                                }
                                if(y1_mij_arc<y2_mij_arc)
                                {
                                    N[nod_1][nod_2].x_arc=x1_mij_arc;
                                    N[nod_1][nod_2].y_arc=y1_mij_arc;
                                    N[nod_2][nod_1].x_arc=x2_mij_arc;
                                    N[nod_2][nod_1].y_arc=y2_mij_arc;
                                    ///incep cu arcul de sus
                                    x_mijloc_sageata=N[nod_1][nod_2].x2_capat+r*(x1_mij_arc-N[nod_1][nod_2].x2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x1_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y1_mij_arc,2));
                                    y_mijloc_sageata=N[nod_1][nod_2].y2_capat+r*(y1_mij_arc-N[nod_1][nod_2].y2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x1_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y1_mij_arc,2));
                                    aux_x=x_mijloc_sageata-N[nod_1][nod_2].x2_capat;
                                    aux_y=y_mijloc_sageata-N[nod_1][nod_2].y2_capat;
                                    aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                    aux_x=aux_x/aux_dist;
                                    aux_y=aux_y/aux_dist;
                                    N[nod_1][nod_2].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                    N[nod_1][nod_2].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                    N[nod_1][nod_2].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                    N[nod_1][nod_2].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                    line(N[nod_1][nod_2].x1_sageata,N[nod_1][nod_2].y1_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                    line(N[nod_1][nod_2].x2_sageata,N[nod_1][nod_2].y2_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                    ///arcul de jos acum
                                    x_mijloc_sageata=N[nod_2][nod_1].x2_capat+r*(x2_mij_arc-N[nod_2][nod_1].x2_capat)/sqrt(pow(x2_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y2_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                    y_mijloc_sageata=N[nod_2][nod_1].y2_capat+r*(y2_mij_arc-N[nod_2][nod_1].y2_capat)/sqrt(pow(x2_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y2_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                    aux_x=x_mijloc_sageata-N[nod_2][nod_1].x2_capat;
                                    aux_y=y_mijloc_sageata-N[nod_2][nod_1].y2_capat;
                                    aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                    aux_x=aux_x/aux_dist;
                                    aux_y=aux_y/aux_dist;
                                    N[nod_2][nod_1].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                    N[nod_2][nod_1].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                    N[nod_2][nod_1].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                    N[nod_2][nod_1].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                    line(N[nod_2][nod_1].x1_sageata,N[nod_2][nod_1].y1_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                    line(N[nod_2][nod_1].x2_sageata,N[nod_2][nod_1].y2_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                }
                                else if(y1_mij_arc>=y2_mij_arc)
                                {
                                    N[nod_1][nod_2].x_arc=x2_mij_arc;
                                    N[nod_1][nod_2].y_arc=y2_mij_arc;
                                    N[nod_2][nod_1].x_arc=x1_mij_arc;
                                    N[nod_2][nod_1].y_arc=y1_mij_arc;
                                    ///incep cu arcul de sus
                                    x_mijloc_sageata=N[nod_1][nod_2].x2_capat+r*(x2_mij_arc-N[nod_1][nod_2].x2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x2_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y2_mij_arc,2));
                                    y_mijloc_sageata=N[nod_1][nod_2].y2_capat+r*(y2_mij_arc-N[nod_1][nod_2].y2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x2_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y2_mij_arc,2));
                                    aux_x=x_mijloc_sageata-N[nod_1][nod_2].x2_capat;
                                    aux_y=y_mijloc_sageata-N[nod_1][nod_2].y2_capat;
                                    aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                    aux_x=aux_x/aux_dist;
                                    aux_y=aux_y/aux_dist;
                                    N[nod_1][nod_2].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                    N[nod_1][nod_2].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                    N[nod_1][nod_2].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                    N[nod_1][nod_2].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                    line(N[nod_1][nod_2].x1_sageata,N[nod_1][nod_2].y1_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                    line(N[nod_1][nod_2].x2_sageata,N[nod_1][nod_2].y2_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                    ///arcul de jos acum
                                    x_mijloc_sageata=N[nod_2][nod_1].x2_capat+r*(x1_mij_arc-N[nod_2][nod_1].x2_capat)/sqrt(pow(x1_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y1_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                    y_mijloc_sageata=N[nod_2][nod_1].y2_capat+r*(y1_mij_arc-N[nod_2][nod_1].y2_capat)/sqrt(pow(x1_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y1_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                    aux_x=x_mijloc_sageata-N[nod_2][nod_1].x2_capat;
                                    aux_y=y_mijloc_sageata-N[nod_2][nod_1].y2_capat;
                                    aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                    aux_x=aux_x/aux_dist;
                                    aux_y=aux_y/aux_dist;
                                    N[nod_2][nod_1].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                    N[nod_2][nod_1].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                    N[nod_2][nod_1].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                    N[nod_2][nod_1].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                    line(N[nod_2][nod_1].x1_sageata,N[nod_2][nod_1].y1_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                    line(N[nod_2][nod_1].x2_sageata,N[nod_2][nod_1].y2_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                }
                                line(N[nod_1][nod_2].x_arc,N[nod_1][nod_2].y_arc,N[nod_1][nod_2].x1_capat,N[nod_1][nod_2].y1_capat);
                                line(N[nod_1][nod_2].x_arc,N[nod_1][nod_2].y_arc,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                line(N[nod_2][nod_1].x_arc,N[nod_2][nod_1].y_arc,N[nod_2][nod_1].x1_capat,N[nod_2][nod_1].y1_capat);
                                line(N[nod_2][nod_1].x_arc,N[nod_2][nod_1].y_arc,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                            }
                            setactivepage(1);
                            cleardevice();
                            redesenare_graf_curent_orientat();
                            setvisualpage(1);
                            setactivepage(0);
                            cleardevice();
                            redesenare_graf_curent_orientat();
                            delay(1);
                            setvisualpage(0);
                            actualizare_output_log("Arc adaugat.");
                        }
                    }
                }
            }
        }
    }
}
void stergere_muchie()
{
    float x_apasat, y_apasat;
    int in_generare=1,nod_1=0,nod_2=0;
    if(nrDeNoduriCurent<2)
    {
        actualizare_output_log("Numar de noduri insuficient.");
        return;
    }
    actualizare_output_log("Selectati nodurile incidente.");
    while(in_generare)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x_apasat=mousex();
            y_apasat=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            nod_1=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_1==0)
            {
                in_generare=0;
                actualizare_output_log("Stergere muchie esuata.");
            }
            else if(G[nod_1].nrLegaturi==0)
            {
                actualizare_output_log("Nu exista muchie pentru stergere.");
                return;
            }
            else
            {
                while(nod_2==0)
                {
                    x_apasat=mousex();
                    y_apasat=mousey();
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        nod_2=gasire_nod_apasat(x_apasat,y_apasat);
                        if(nod_2==0 || nod_1==nod_2 || M[nod_1][nod_2].exista_muchie==0)
                        {
                            in_generare=0;
                            actualizare_output_log("Stergere muchie esuata.");
                            break;
                        }
                        else
                        {
                            in_generare=0;
                            G[nod_1].nrLegaturi--;
                            G[nod_2].nrLegaturi--;
                            M[nod_1][nod_2].exista_muchie=M[nod_2][nod_1].exista_muchie=0; ///punem in matricea de adiacenta
                            M[nod_1][nod_2].x_capat=0;
                            M[nod_1][nod_2].y_capat=0;
                            M[nod_2][nod_1].x_capat=0;
                            M[nod_2][nod_1].y_capat=0;
                            actualizare_output_log("Muchie stearsa cu succes.");
                            M[nod_1][nod_2].cost[0]=M[nod_2][nod_1].cost[0]=NULL;
                            M[nod_1][nod_2].cost[0]=M[nod_2][nod_1].cost[0]='*';
                            setactivepage(1);
                            cleardevice();
                            redesenare_graf_curent();
                            setvisualpage(1);
                            setactivepage(0);
                            cleardevice();
                            redesenare_graf_curent();
                            delay(1);
                            setvisualpage(0);
                        }
                    }
                }
            }
        }
    }
}
void stergere_arc()
{
    float x_apasat, y_apasat, x_mijloc_sageata,y_mijloc_sageata,aux_x,aux_y,aux_dist;
    int in_generare=1,nod_1=0,nod_2=0;
    if(nrDeNoduriCurent<2)
    {
        actualizare_output_log("Numar de noduri insuficient.");
        return;
    }
    actualizare_output_log("Selectati nodurile incidente.");
    while(in_generare)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x_apasat=mousex();
            y_apasat=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            nod_1=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_1==0)
            {
                in_generare=0;
                actualizare_output_log("Stergere arc esuata.");
            }
            else if(G[nod_1].nrLegaturi==0)
            {
                actualizare_output_log("Nu exista arc pentru stergere.");
                return;
            }
            else
            {
                while(nod_2==0)
                {
                    x_apasat=mousex();
                    y_apasat=mousey();
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        nod_2=gasire_nod_apasat(x_apasat,y_apasat);
                        if(nod_2==0 || nod_1==nod_2 || N[nod_1][nod_2].exista_arc==0)
                        {
                            in_generare=0;
                            actualizare_output_log("Stergere muchie esuata.");
                            break;
                        }
                        else
                        {
                            in_generare=0;
                            G[nod_1].nrLegaturi--;
                            N[nod_1][nod_2].exista_arc=0; ///punem in matricea de adiacenta
                            N[nod_1][nod_2].x1_capat=0;
                            N[nod_1][nod_2].y1_capat=0;
                            N[nod_1][nod_2].x2_capat=0;
                            N[nod_1][nod_2].y2_capat=0;
                            N[nod_1][nod_2].x1_sageata=0;
                            N[nod_1][nod_2].y1_sageata=0;
                            N[nod_1][nod_2].x2_sageata=0;
                            N[nod_1][nod_2].y2_sageata=0;
                            N[nod_1][nod_2].x_arc=0;
                            N[nod_1][nod_2].y_arc=0;
                            N[nod_1][nod_2].cost[0]=NULL;
                            N[nod_1][nod_2].cost[0]='*';
                            if(N[nod_2][nod_1].exista_arc==1)
                            {
                                N[nod_2][nod_1].x_arc=(N[nod_2][nod_1].x1_capat+N[nod_2][nod_1].x2_capat)/2;
                                N[nod_2][nod_1].y_arc=(N[nod_2][nod_1].y1_capat+N[nod_2][nod_1].y2_capat)/2;
                                x_mijloc_sageata=G[nod_1].x+2*r*(G[nod_2].x-G[nod_1].x)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                y_mijloc_sageata=G[nod_1].y+2*r*(G[nod_2].y-G[nod_1].y)/sqrt(pow(G[nod_1].x-G[nod_2].x,2)+pow(G[nod_1].y-G[nod_2].y,2));
                                aux_x=x_mijloc_sageata-G[nod_1].x;
                                aux_y=y_mijloc_sageata-G[nod_1].y;
                                aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                aux_x=aux_x/aux_dist;
                                aux_y=aux_y/aux_dist;
                                N[nod_2][nod_1].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                N[nod_2][nod_1].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                N[nod_2][nod_1].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                N[nod_2][nod_1].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                line(N[nod_2][nod_1].x1_sageata,N[nod_2][nod_1].y1_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                line(N[nod_2][nod_1].x2_sageata,N[nod_2][nod_1].y2_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                if(N[nod_2][nod_1].cost[0]!='*')
                                {
                                    outtextxy(N[nod_2][nod_1].x_arc, N[nod_2][nod_1].y_arc,N[nod_2][nod_1].cost);
                                }
                            }
                            actualizare_output_log("Arc sters cu succes.");
                            setactivepage(1);
                            cleardevice();
                            redesenare_graf_curent_orientat();
                            setvisualpage(1);
                            setactivepage(0);
                            cleardevice();
                            redesenare_graf_curent_orientat();
                            delay(1);
                            setvisualpage(0);
                        }
                    }
                }
            }
        }
    }
}
void adaugare_nod()
{
    int nod_plasat=0, nod_eligibil=0;
    float x_apasat, y_apasat;
    if(nrMaxDenumireNoduri==15)
    {
        actualizare_output_log("Numar maxim de noduri atins.");
        return;
    }
    actualizare_output_log("Plasati nodul in zona de editare.");
    while(nod_plasat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            if(x_apasat>=300+r && x_apasat<=900-r && y_apasat>=75+r && y_apasat<=450-r && nod_nesuprapus(x_apasat, y_apasat))
            {
                nod_plasat=1;
                nrMaxDenumireNoduri++;
                nrDeNoduriCurent++;
                for(int i=1; i<=nrMaxDenumireNoduri; i++)
                {
                    if(G[i].exista_nod==0)
                    {
                        nod_eligibil=i;
                        break;
                    }
                }
                G[nod_eligibil].exista_nod=1;
                G[nod_eligibil].nrLegaturi=0;
                itoa(nod_eligibil,numeNod,10);
                G[nod_eligibil].x=x_apasat;
                G[nod_eligibil].y=y_apasat;
                circle(x_apasat,y_apasat,r);
                outtextxy(x_apasat,y_apasat,numeNod);
                actualizare_output_log("Nod adaugat.");
            }
            else if(!(x_apasat>=300+r && x_apasat<=900-r && y_apasat>=75+r && y_apasat<=450-r))
            {
                nod_plasat=1;
                actualizare_output_log("Inafara zonei de editare.");
            }
        }
    }
}
void stergere_nod()
{
    int nod_nesters=0, nod_apasat=0;
    float x_apasat, y_apasat;
    actualizare_output_log("Selectati nodul pentru stergere.");
    if(nrDeNoduriCurent == 0)
    {
        actualizare_output_log("Nu exista noduri pentru stergere.");
        return;
    }
    while(nod_nesters==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_apasat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_apasat)
            {
                nod_nesters=1;
                for(int i=1; i<=nrMaxDenumireNoduri; i++)
                {
                    if(M[nod_apasat][i].exista_muchie==1)
                    {
                        M[nod_apasat][i].exista_muchie=M[i][nod_apasat].exista_muchie=0;
                        M[nod_apasat][i].x_capat=M[nod_apasat][i].y_capat=M[i][nod_apasat].x_capat=M[i][nod_apasat].y_capat=0;
                        M[nod_apasat][i].cost[0]=M[i][nod_apasat].cost[0]=NULL;
                        M[nod_apasat][i].cost[0]=M[i][nod_apasat].cost[0]='*';
                        G[i].nrLegaturi--;
                    }
                }
                G[nod_apasat].exista_nod=0;
                G[nod_apasat].nrLegaturi=0;
                G[nod_apasat].x=0;
                G[nod_apasat].y=0;
                while(G[nrMaxDenumireNoduri].exista_nod==0&&nrMaxDenumireNoduri>0)
                    nrMaxDenumireNoduri--;
                nrDeNoduriCurent--;
                actualizare_output_log("Nod sters.");
                setactivepage(1);
                cleardevice();
                redesenare_graf_curent();
                setvisualpage(1);
                setactivepage(0);
                cleardevice();
                redesenare_graf_curent();
                delay(1);
                setvisualpage(0);
            }
            else
            {
                nod_nesters=1;
                actualizare_output_log("Stergere nod neefectuata.");
            }
        }
    }
}
void stergere_nod_orientat()
{
    int nod_nesters=0,nod_apasat=0;
    float x_apasat, y_apasat;
    actualizare_output_log("Selectati nodul pentru stergere.");
    if(nrDeNoduriCurent == 0)
    {
        actualizare_output_log("Nu exista noduri pentru stergere.");
        return;
    }
    while(nod_nesters==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_apasat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_apasat)
            {
                nod_nesters=1;
                for(int i=1; i<=nrMaxDenumireNoduri; i++)
                {
                    if(N[nod_apasat][i].exista_arc==1 && N[i][nod_apasat].exista_arc==0)
                    {
                        N[nod_apasat][i].exista_arc=0;
                        N[nod_apasat][i].x1_capat=N[nod_apasat][i].y1_capat=N[nod_apasat][i].x2_capat=N[nod_apasat][i].y2_capat=0;
                        N[nod_apasat][i].x1_sageata=N[nod_apasat][i].y1_sageata=N[nod_apasat][i].x2_sageata=N[nod_apasat][i].y2_sageata=0;
                        N[nod_apasat][i].x_arc=N[nod_apasat][i].y_arc=0;
                        N[nod_apasat][i].cost[0]=NULL;
                        N[nod_apasat][i].cost[0]='*';
                    }
                    else if(N[nod_apasat][i].exista_arc==0 && N[i][nod_apasat].exista_arc==1)
                    {
                        N[i][nod_apasat].exista_arc=0;
                        N[i][nod_apasat].x1_capat=N[i][nod_apasat].y1_capat=N[i][nod_apasat].x2_capat=N[i][nod_apasat].y2_capat=0;
                        N[i][nod_apasat].x1_sageata=N[i][nod_apasat].y1_sageata=N[i][nod_apasat].x2_sageata=N[i][nod_apasat].y2_sageata=0;
                        N[i][nod_apasat].x_arc=N[i][nod_apasat].y_arc=0;
                        N[i][nod_apasat].cost[0]=NULL;
                        N[i][nod_apasat].cost[0]='*';
                        G[i].nrLegaturi--;
                    }
                    else if(N[nod_apasat][i].exista_arc==1 && N[i][nod_apasat].exista_arc==1)
                    {
                        N[nod_apasat][i].exista_arc=0;
                        N[nod_apasat][i].x1_capat=N[nod_apasat][i].y1_capat=N[nod_apasat][i].x2_capat=N[nod_apasat][i].y2_capat=0;
                        N[nod_apasat][i].x1_sageata=N[nod_apasat][i].y1_sageata=N[nod_apasat][i].x2_sageata=N[nod_apasat][i].y2_sageata=0;
                        N[nod_apasat][i].x_arc=N[nod_apasat][i].y_arc=0;
                        N[i][nod_apasat].exista_arc=0;
                        N[i][nod_apasat].x1_capat=N[i][nod_apasat].y1_capat=N[i][nod_apasat].x2_capat=N[i][nod_apasat].y2_capat=0;
                        N[i][nod_apasat].x1_sageata=N[i][nod_apasat].y1_sageata=N[i][nod_apasat].x2_sageata=N[i][nod_apasat].y2_sageata=0;
                        N[i][nod_apasat].x_arc=N[i][nod_apasat].y_arc=0;
                        N[nod_apasat][i].cost[0]=NULL;
                        N[nod_apasat][i].cost[0]='*';
                        N[i][nod_apasat].cost[0]=NULL;
                        N[i][nod_apasat].cost[0]='*';
                        G[i].nrLegaturi--;
                    }
                }
                G[nod_apasat].exista_nod=0;
                G[nod_apasat].nrLegaturi=0;
                G[nod_apasat].x=0;
                G[nod_apasat].y=0;
                while(G[nrMaxDenumireNoduri].exista_nod==0&&nrMaxDenumireNoduri>0)
                    nrMaxDenumireNoduri--;
                nrDeNoduriCurent--;
                actualizare_output_log("Nod sters.");
                setactivepage(1);
                cleardevice();
                redesenare_graf_curent_orientat();
                setvisualpage(1);
                setactivepage(0);
                cleardevice();
                redesenare_graf_curent_orientat();
                delay(1);
                setvisualpage(0);
            }
            else
            {
                nod_nesters=1;
                actualizare_output_log("Stergere nod neefectuata.");
            }
        }
    }
}
void stergere_graf()
{
    if(nrMaxDenumireNoduri==0)
    {
        actualizare_output_log("Graf neexistent.");
        return;
    }
    actualizare_output_log("Graf sters.");
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
    {
        G[i].x=0;
        G[i].y=0;
        G[i].nrLegaturi=0;
        G[i].exista_nod=0;
    }
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        for(int j=1; j<=nrMaxDenumireNoduri; j++)
            if(M[i][j].exista_muchie==1)
            {
                M[i][j].exista_muchie=M[j][i].exista_muchie=0;
                M[i][j].x_capat=M[i][j].y_capat=M[j][i].x_capat=M[j][i].y_capat=0;
                M[i][j].cost[0]=M[j][i].cost[0]=NULL;
                M[i][j].cost[0]=M[j][i].cost[0]='*';
            }
    nrMaxDenumireNoduri=0;
    nrDeNoduriCurent=0;
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent();
    delay(1);
    setvisualpage(0);
}
void stergere_graf_orientat()
{
    if(nrMaxDenumireNoduri==0)
    {
        actualizare_output_log("Graf neexistent.");
        return;
    }
    actualizare_output_log("Graf sters.");
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
    {
        G[i].x=0;
        G[i].y=0;
        G[i].nrLegaturi=0;
        G[i].exista_nod=0;
    }
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        for(int j=1; j<=nrMaxDenumireNoduri; j++)
            if(N[i][j].exista_arc==1)
            {
                N[i][j].exista_arc=0;
                N[i][j].x1_capat=0;
                N[i][j].y1_capat=0;
                N[i][j].x2_capat=0;
                N[i][j].y2_capat=0;
                N[i][j].x1_sageata=0;
                N[i][j].y1_sageata=0;
                N[i][j].x2_sageata=0;
                N[i][j].y2_sageata=0;
                N[i][j].x_arc=0;
                N[i][j].y_arc=0;
                N[i][j].cost[0]=NULL;
                N[i][j].cost[0]='*';
            }
    nrMaxDenumireNoduri=0;
    nrDeNoduriCurent=0;
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent_orientat();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent_orientat();
    delay(1);
    setvisualpage(0);
}
void adaugare_cost()
{
    float x_apasat, y_apasat, mijx, mijy;
    int in_generare=1,nod_1=0,nod_2=0,i=-1;
    char vector_costuri[10]= {NULL},a;
    actualizare_output_log("Selectati 2 noduri.");
    while(in_generare)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x_apasat=mousex();
            y_apasat=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            nod_1=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_1==0)
            {
                in_generare=0;
                actualizare_output_log("Cost neadaugat.");
            }
            else
            {
                while(nod_2==0)
                {
                    x_apasat=mousex();
                    y_apasat=mousey();
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        nod_2=gasire_nod_apasat(x_apasat,y_apasat);
                        if(nod_2==0 || nod_1==nod_2 || M[nod_1][nod_2].exista_muchie==0)
                        {
                            in_generare=0;
                            actualizare_output_log("Cost neadaugat.");
                            break;
                        }
                        else
                        {
                            actualizare_output_log("Introduceti valoarea costului.");
                            in_generare=0;
                            mijx=(M[nod_1][nod_2].x_capat+M[nod_2][nod_1].x_capat)/2;
                            mijy=(M[nod_1][nod_2].y_capat+M[nod_2][nod_1].y_capat)/2;
                            settextjustify(LEFT_TEXT,CENTER_TEXT);
                            a=getch();
                            nrLinii++;
                            if(nrLinii==18)
                            {
                                bar(0,151,300,1200);
                                nrLinii=1;
                            }
                            while(a!=13&&i<9)
                            {
                                i++;
                                if(a==8&&i>0)
                                {
                                    i--;
                                    setcolor(LIGHTGRAY);
                                    outtextxy(10,150+25*nrLinii,vector_costuri);
                                    setcolor(BLACK);
                                    vector_costuri[i]=NULL;
                                    i--;
                                }
                                else if(a!=8)
                                {
                                    vector_costuri[i]=a;
                                }
                                else i--;
                                outtextxy(10,150+25*nrLinii,vector_costuri);
                                a=getch();
                            }
                            nrLinii--;
                            settextjustify(CENTER_TEXT,CENTER_TEXT);
                            actualizare_output_log(vector_costuri);
                            if(input_valid(vector_costuri)&&i<9)
                            {
                                actualizare_output_log("Cost adaugat.");
                                M[nod_1][nod_2].cost[0]=M[nod_2][nod_1].cost[0]=NULL;
                                M[nod_1][nod_2].cost[0]=M[nod_2][nod_1].cost[0]='*';
                                setactivepage(1);
                                cleardevice();
                                redesenare_graf_curent();
                                outtextxy(mijx,mijy,vector_costuri);
                                setvisualpage(1);
                                setactivepage(0);
                                cleardevice();
                                redesenare_graf_curent();
                                outtextxy(mijx,mijy,vector_costuri);
                                delay(1);
                                setvisualpage(0);
                                strcpy(M[nod_1][nod_2].cost,vector_costuri);
                                strcpy(M[nod_2][nod_1].cost,vector_costuri);
                                vector_costuri[0]=NULL;
                            }
                            else
                            {
                                actualizare_output_log("Cost invalid.");
                                vector_costuri[0]=NULL;
                            }
                        }
                    }
                }
            }
        }
    }
}
void adaugare_cost_orientat()
{
    float x_apasat, y_apasat;
    int in_generare=1,nod_1=0,nod_2=0,i=-1;
    char vector_costuri[10]= {NULL},a;
    actualizare_output_log("Selectati 2 noduri.");
    while(in_generare)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x_apasat=mousex();
            y_apasat=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            nod_1=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_1==0)
            {
                in_generare=0;
                actualizare_output_log("Cost neadaugat.");
            }
            else
            {
                while(nod_2==0)
                {
                    x_apasat=mousex();
                    y_apasat=mousey();
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        nod_2=gasire_nod_apasat(x_apasat,y_apasat);
                        if(nod_2==0 || nod_1==nod_2 || N[nod_1][nod_2].exista_arc==0)
                        {
                            in_generare=0;
                            actualizare_output_log("Cost neadaugat.");
                            break;
                        }
                        else
                        {
                            actualizare_output_log("Introduceti valoarea costului.");
                            in_generare=0;
                            settextjustify(LEFT_TEXT,CENTER_TEXT);
                            a=getch();
                            nrLinii++;
                            if(nrLinii==18)
                            {
                                bar(0,151,300,1200);
                                nrLinii=1;
                            }
                            while(a!=13&&i<9)
                            {
                                i++;
                                if(a==8&&i>0)
                                {
                                    i--;
                                    setcolor(LIGHTGRAY);
                                    outtextxy(10,150+25*nrLinii,vector_costuri);
                                    setcolor(BLACK);
                                    vector_costuri[i]=NULL;
                                    i--;
                                }
                                else if(a!=8)
                                {
                                    vector_costuri[i]=a;
                                }
                                else i--;
                                outtextxy(10,150+25*nrLinii,vector_costuri);
                                a=getch();
                            }
                            nrLinii--;
                            settextjustify(CENTER_TEXT,CENTER_TEXT);
                            actualizare_output_log(vector_costuri);
                            if(input_valid(vector_costuri)&&i<9)
                            {
                                actualizare_output_log("Cost adaugat.");
                                N[nod_1][nod_2].cost[0]=NULL;
                                N[nod_1][nod_2].cost[0]='*';
                                setactivepage(1);
                                cleardevice();
                                redesenare_graf_curent_orientat();
                                outtextxy(N[nod_1][nod_2].x_arc,N[nod_1][nod_2].y_arc,vector_costuri);
                                setvisualpage(1);
                                setactivepage(0);
                                cleardevice();
                                redesenare_graf_curent_orientat();
                                outtextxy(N[nod_1][nod_2].x_arc,N[nod_1][nod_2].y_arc,vector_costuri);
                                delay(1);
                                setvisualpage(0);
                                strcpy(N[nod_1][nod_2].cost,vector_costuri);
                                vector_costuri[0]=NULL;
                            }
                            else
                            {
                                actualizare_output_log("Cost invalid.");
                                vector_costuri[0]=NULL;
                            }
                        }
                    }
                }
            }
        }
    }
}
void BFSN()
{
    int poz=0,k=0,st,dr,vizitat[16]= {NULL},coada[16]= {NULL}, nod_selectat=0,x_apasat,y_apasat,nod_neselectat=0;
    char rezultat[200]= {NULL};
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    actualizare_output_log("Selecteaza nodul de start.");
    while(nod_neselectat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_selectat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_selectat!=0)
                nod_neselectat=1;
            else
            {
                actualizare_output_log("Nod neselectat.");
                return;
            }
        }
    }
    //initializez coada
    st=dr=1;
    coada[1]=nod_selectat;
    vizitat[nod_selectat]=1;//vizitez varful initial
    if(nod_selectat<10)
        rezultat[poz++]=nod_selectat+'0';
    else
    {
        rezultat[poz++]=(nod_selectat/10)+'0';
        rezultat[poz++]=(nod_selectat%10)+'0';
    }
    rezultat[poz++]=' ';
    setcolor(RED);
    circle(G[nod_selectat].x,G[nod_selectat].y,r);
    delay(1000);
    while(st<=dr)//cat timp coada nu este vida
    {
        k=coada[st];//preiau un element din coada
        for(int i=1; i<=nrMaxDenumireNoduri; i++) //parcurg varfurile
            if(vizitat[i]==0 && M[k][i].exista_muchie==1)//daca i este vecin cu k si nu este vizitat
            {
                line(M[k][i].x_capat,M[k][i].y_capat,M[i][k].x_capat,M[i][k].y_capat);
                circle(G[i].x,G[i].y,r);
                delay(1000);
                vizitat[i]=1;//il vizitez
                if(i<10)
                    rezultat[poz++]=i+'0';
                else
                {
                    rezultat[poz++]=(i/10)+'0';
                    rezultat[poz++]=(i%10)+'0';
                }
                rezultat[poz++]=' ';
                coada[++dr]=i;//il adaug in coada
            }
        st++;//sterg din coada
    }
    delay(1000);
    setcolor(BLACK);
    actualizare_output_log(rezultat);
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent();
    delay(1);
    setvisualpage(0);
}
void BFSO()
{
    int poz=0,k=0,st,dr,vizitat[16]= {NULL},coada[16]= {NULL}, nod_selectat=0,x_apasat,y_apasat,nod_neselectat=0;
    char rezultat[200]={NULL};
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    actualizare_output_log("Selecteaza nodul de start.");
    while(nod_neselectat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_selectat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_selectat!=0)
                nod_neselectat=1;
            else
            {
                actualizare_output_log("Nod neselectat.");
                return;
            }
        }
    }
    //initializez coada
    st=dr=1;
    coada[1]=nod_selectat;
    vizitat[nod_selectat]=1;//vizitez varful initial
    if(nod_selectat<10)
        rezultat[poz++]=nod_selectat+'0';
    else
    {
        rezultat[poz++]=(nod_selectat/10)+'0';
        rezultat[poz++]=(nod_selectat%10)+'0';
    }
    rezultat[poz++]=' ';
    setcolor(RED);
    circle(G[nod_selectat].x,G[nod_selectat].y,r);
    delay(1000);
    while(st<=dr)//cat timp coada nu este vida
    {
        k=coada[st];//preiau un element din coada
        for(int i=1; i<=nrMaxDenumireNoduri; i++) //parcurg varfurile
            if(vizitat[i]==0 && N[k][i].exista_arc==1)//daca i este vecin cu k si nu este vizitat
            {
                vizitat[i]=1;//il vizitez
                line(N[k][i].x1_capat,N[k][i].y1_capat,N[k][i].x_arc,N[k][i].y_arc);
                line(N[k][i].x2_capat,N[k][i].y2_capat,N[k][i].x_arc,N[k][i].y_arc);
                line(N[k][i].x1_sageata,N[k][i].y1_sageata,N[k][i].x2_capat,N[k][i].y2_capat);
                line(N[k][i].x2_sageata,N[k][i].y2_sageata,N[k][i].x2_capat,N[k][i].y2_capat);
                circle(G[i].x,G[i].y,r);
                delay(1000);
                if(i<10)
                    rezultat[poz++]=i+'0';
                else
                {
                    rezultat[poz++]=(i/10)+'0';
                    rezultat[poz++]=(i%10)+'0';
                }
                rezultat[poz++]=' ';
                coada[++dr]=i;//il adaug in coada
            }
        st++;//sterg din coada
    }
    delay(1000);
    setcolor(BLACK);
    actualizare_output_log(rezultat);
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent_orientat();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent_orientat();
    delay(1);
    setvisualpage(0);
}
void DFSN_REC(int nod_selectat,int &poz,char rezultat[200],int vizitat[16])
{
    setcolor(RED);
    circle(G[nod_selectat].x,G[nod_selectat].y,r);
    delay(1000);
    vizitat[nod_selectat]=1; //vizitam varful curent x
    if(nod_selectat<10)
        rezultat[poz++]=nod_selectat+'0';
    else
    {
        rezultat[poz++]=(nod_selectat/10)+'0';
        rezultat[poz++]=(nod_selectat%10)+'0';
    }
    rezultat[poz++]=' ';
    for(int i=1; i<=nrMaxDenumireNoduri; i++) // determinam vecinii nevizitati ai lui x
        if(M[nod_selectat][i].exista_muchie==1 && vizitat[i]==0)
        {
            circle(G[i].x,G[i].y,r);
            line(M[nod_selectat][i].x_capat,M[nod_selectat][i].y_capat,M[i][nod_selectat].x_capat,M[i][nod_selectat].y_capat);
            DFSN_REC(i,poz,rezultat,vizitat); // continuam parcurgerea cu vecinul curent i
        }
}
void DFSN_REC_noncolor(int nod_selectat,int &poz,char rezultat[200],int vizitat[16])
{
    vizitat[nod_selectat]=1; //vizitam varful curent x
    if(nod_selectat<10)
        rezultat[poz++]=nod_selectat+'0';
    else
    {
        rezultat[poz++]=(nod_selectat/10)+'0';
        rezultat[poz++]=(nod_selectat%10)+'0';
    }
    rezultat[poz++]=' ';
    for(int i=1; i<=nrMaxDenumireNoduri; i++) // determinam vecinii nevizitati ai lui x
        if(M[nod_selectat][i].exista_muchie==1 && vizitat[i]==0)
        {
            DFSN_REC_noncolor(i,poz,rezultat,vizitat); // continuam parcurgerea cu vecinul curent i
        }
}
void DFSN()
{
    int nod_selectat=0,x_apasat,y_apasat,nod_neselectat=0,vizitat[16]= {0},poz=0;
    char rezultat[200]= {NULL};
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    actualizare_output_log("Selecteaza nodul de start.");
    while(nod_neselectat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_selectat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_selectat!=0)
                nod_neselectat=1;
            else
            {
                actualizare_output_log("Nod neselectat.");
                return;
            }
        }
    }
    DFSN_REC(nod_selectat,poz,rezultat,vizitat);
    delay(1000);
    setcolor(BLACK);
    actualizare_output_log(rezultat);
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent();
    delay(1);
    setvisualpage(0);
}
void DFSO_REC(int nod_selectat,int &poz,char rezultat[200],int vizitat[16])
{
    setcolor(RED);
    circle(G[nod_selectat].x,G[nod_selectat].y,r);
    delay(1000);
    vizitat[nod_selectat]=1; //vizitam varful curent x
    if(nod_selectat<10)
        rezultat[poz++]=nod_selectat+'0';
    else
    {
        rezultat[poz++]=(nod_selectat/10)+'0';
        rezultat[poz++]=(nod_selectat%10)+'0';
    }
    rezultat[poz++]=' ';
    for(int i=1; i<=nrMaxDenumireNoduri; i++) // determinam vecinii nevizitati ai lui x
        if(N[nod_selectat][i].exista_arc==1 && vizitat[i]==0)
        {
            circle(G[i].x,G[i].y,r);
            line(N[nod_selectat][i].x1_capat,N[nod_selectat][i].y1_capat,N[nod_selectat][i].x_arc,N[nod_selectat][i].y_arc);
            line(N[nod_selectat][i].x2_capat,N[nod_selectat][i].y2_capat,N[nod_selectat][i].x_arc,N[nod_selectat][i].y_arc);
            line(N[nod_selectat][i].x1_sageata,N[nod_selectat][i].y1_sageata,N[nod_selectat][i].x2_capat,N[nod_selectat][i].y2_capat);
            line(N[nod_selectat][i].x2_sageata,N[nod_selectat][i].y2_sageata,N[nod_selectat][i].x2_capat,N[nod_selectat][i].y2_capat);
            DFSO_REC(i,poz,rezultat,vizitat); // continuam parcurgerea cu vecinul curent i
        }
}
void DFSO()
{
    int nod_selectat=0,x_apasat,y_apasat,nod_neselectat=0,vizitat[16]= {0},poz=0;
    char rezultat[200]= {NULL};
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    actualizare_output_log("Selecteaza nodul de start.");
    while(nod_neselectat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_selectat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_selectat!=0)
                nod_neselectat=1;
            else
            {
                actualizare_output_log("Nod neselectat.");
                return;
            }
        }
    }
    DFSO_REC(nod_selectat,poz,rezultat,vizitat);
    delay(1000);
    setcolor(BLACK);
    actualizare_output_log(rezultat);
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent_orientat();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent_orientat();
    delay(1);
    setvisualpage(0);
}
int conex()
{
    int vizitat[16]= {0},poz=0,verif_conex=1;
    char rezultat[200]= {NULL};
    DFSN_REC_noncolor(1,poz,rezultat,vizitat);
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        if (vizitat[i]==0 && G[i].exista_nod==1)
        {
            verif_conex=0;
            break;
        }
    return verif_conex;
}
void conexitate()
{
    int verif_conex=1;
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    verif_conex=conex();
    if(verif_conex==0)
        actualizare_output_log("Graful nu este conex.");
    else
        actualizare_output_log("Graful este conex.");
}
void prima_parcurgere(int nod, int primul_vector[16])
{
    primul_vector[nod]=1;
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        if(primul_vector[i]==0 && N[nod][i].exista_arc==1)
            prima_parcurgere(i,primul_vector);
}
void a2a_parcurgere(int nod, int al2lea_vector[16])
{
    al2lea_vector[nod]=1;
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        if(al2lea_vector[i]==0 && N[i][nod].exista_arc==1)
            a2a_parcurgere(i,al2lea_vector);
}
void tare_conexitate()
{
    int poz=0,nod_neselectat=0,x_apasat,y_apasat,nod_selectat=0,comp_necesara=0,comp_tare_conex[16]={NULL}, primul_vector[16]={NULL}, al2lea_vector[16]={NULL}, nr_comp_conexe=0;
    char rezultat[200]={NULL};
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    actualizare_output_log("Selecteaza nodul.");
    while(nod_neselectat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_selectat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_selectat!=0)
                nod_neselectat=1;
            else
            {
                actualizare_output_log("Nod neselectat.");
                return;
            }
        }
    }
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        if(comp_tare_conex[i]==0)
        {
            for(int j=1; j<=nrMaxDenumireNoduri; j++)
                primul_vector[j]=al2lea_vector[j]=0;
            nr_comp_conexe++;
            prima_parcurgere(i,primul_vector);
            a2a_parcurgere(i,al2lea_vector);
            for(int j=1; j<=nrMaxDenumireNoduri; j++)
                if(primul_vector[j]==1&&al2lea_vector[j]==1)
                    comp_tare_conex[j]=nr_comp_conexe;
        }
    comp_necesara=comp_tare_conex[nod_selectat];
    setcolor(RED);
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
    {
        if(comp_tare_conex[i]==comp_necesara)
        {
            circle(G[i].x,G[i].y,r);
            for(int j=1;j<=nrMaxDenumireNoduri;j++)
            {
                if(N[i][j].exista_arc==1 && comp_tare_conex[j]==comp_necesara)
                {
                    line(N[i][j].x1_capat,N[i][j].y1_capat,N[i][j].x_arc,N[i][j].y_arc);
                    line(N[i][j].x2_capat,N[i][j].y2_capat,N[i][j].x_arc,N[i][j].y_arc);
                    line(N[i][j].x1_sageata,N[i][j].y1_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                    line(N[i][j].x2_sageata,N[i][j].y2_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                    delay(1000);
                }
            }
            if(i<10)
                rezultat[poz++]=i+'0';
            else
            {
                rezultat[poz++]=(i/10)+'0';
                rezultat[poz++]=(i%10)+'0';
            }
            rezultat[poz++]=' ';
        }
    }
    delay(1000);
    setcolor(BLACK);
    actualizare_output_log(rezultat);
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent_orientat();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent_orientat();
    delay(1);
    setvisualpage(0);
}
void Prim()
{
    int vizitat[16],negativ,cost_dupa_conversie,nr_muchii=1,maxim=99999999;
    char cost_final_rezultat[200]={NULL},numar_cost[200]={NULL},mesaj_cost_final[200]={NULL};
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    if(conex()==0)
    {
        actualizare_output_log("Graful nu este conex.");
        return;
    }
    if(graf_cu_costuri_valid()==0)
    {
        actualizare_output_log("Costuri lipsa.");
        return;
    }
    InitVectorCosturi(C);
    for(int i=1; i<nrMaxDenumireNoduri; i++)
    {
        for(int j=i+1; j<=nrMaxDenumireNoduri; j++)
        {
            negativ=0;
            if(M[i][j].exista_muchie==1 && M[i][j].cost[0]!='*')
            {
                strcpy(numar_cost,M[i][j].cost);
                if(numar_cost[0]=='-')
                {
                    negativ=1;
                    strcpy(numar_cost,numar_cost+1);
                }
                C[nr_muchii].capat1=i;
                C[nr_muchii].capat2=j;
                cost_dupa_conversie=atoi(numar_cost);
                if(negativ==1)
                    C[nr_muchii].cost=-cost_dupa_conversie;
                else C[nr_muchii].cost=cost_dupa_conversie;
                nr_muchii++;
            }
        }
    }
    nr_muchii--;
    for(int i=1; i<nr_muchii; i++)
    {
        for(int j=i+1; j<=nr_muchii; j++)
        {
            if(C[i].cost>C[j].cost)
            {
                swap(C[i].cost,C[j].cost);
                swap(C[i].capat1,C[j].capat1);
                swap(C[i].capat2,C[j].capat2);
            }
        }
    }
    for(int i=1;i<=nrMaxDenumireNoduri;i++)
        vizitat[i]=0;
    vizitat[C[1].capat1]=1;
    vizitat[C[1].capat2]=1;
    setcolor(RED);
    circle(G[C[1].capat1].x,G[C[1].capat1].y,r);
    circle(G[C[1].capat2].x,G[C[1].capat2].y,r);
    line(M[C[1].capat1][C[1].capat2].x_capat,M[C[1].capat1][C[1].capat2].y_capat,M[C[1].capat2][C[1].capat1].x_capat,M[C[1].capat2][C[1].capat1].y_capat);
    delay(1000);
    int verif_nr_muchii_selectate=1,primul_nod=C[1].capat1,al_doilea_nod=C[1].capat2,gasit_primul=0,gasit_al_doilea=0,cost_final=0;
    cost_final=cost_final+C[1].cost;
    while(verif_nr_muchii_selectate<nrMaxDenumireNoduri-1)
    {
        for(int i=2;i<=nr_muchii;i++)
        {
            if(vizitat[C[i].capat1]==1 && vizitat[C[i].capat2]==0)
            {
                primul_nod=C[i].capat1;
                al_doilea_nod=C[i].capat2;
                vizitat[al_doilea_nod]=1;
                circle(G[C[i].capat2].x,G[C[i].capat2].y,r);
                line(M[C[i].capat1][C[i].capat2].x_capat,M[C[i].capat1][C[i].capat2].y_capat,M[C[i].capat2][C[i].capat1].x_capat,M[C[i].capat2][C[i].capat1].y_capat);
                delay(1000);
                cost_final=cost_final+C[i].cost;
                verif_nr_muchii_selectate++;
                break;
            }
            else if(vizitat[C[i].capat2]==1 && vizitat[C[i].capat1]==0)
            {
                al_doilea_nod=C[i].capat2;
                primul_nod=C[i].capat1;
                vizitat[primul_nod]=1;
                circle(G[C[i].capat1].x,G[C[i].capat1].y,r);
                line(M[C[i].capat2][C[i].capat1].x_capat,M[C[i].capat2][C[i].capat1].y_capat,M[C[i].capat1][C[i].capat2].x_capat,M[C[i].capat1][C[i].capat2].y_capat);
                delay(1000);
                cost_final=cost_final+C[i].cost;
                verif_nr_muchii_selectate++;
                break;
            }
        }
    }
    itoa(cost_final,cost_final_rezultat,10);
    setcolor(BLACK);
    delay(1000);
    strcat(mesaj_cost_final,"Rezultat algoritm Prim: ");
    strcat(mesaj_cost_final,cost_final_rezultat);
    actualizare_output_log(mesaj_cost_final);
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent();
    delay(1);
    setvisualpage(0);
}
void Kruskal()
{
    int negativ,nr_muchii=1,cost_dupa_conversie,rezultat_parcurgere=0,radacini[16]= {0},radacina1, radacina2;
    char numar_cost[10], mesaj_final[100];
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    if(conex()==0)
    {
        actualizare_output_log("Graful nu este conex.");
        return;
    }
    if(!graf_cu_costuri_valid())
    {
        actualizare_output_log("Costuri lipsa.");
        return;
    }
    InitVectorCosturi(C);
    for(int i=1; i<nrMaxDenumireNoduri; i++)
    {
        for(int j=i+1; j<=nrMaxDenumireNoduri; j++)
        {
            negativ=0;
            if(M[i][j].exista_muchie==1&&M[i][j].cost[0]!='*')
            {
                strcpy(numar_cost,M[i][j].cost);
                if(numar_cost[0]=='-')
                {
                    negativ=1;
                    strcpy(numar_cost,numar_cost+1);
                }
                C[nr_muchii].capat1=i;
                C[nr_muchii].capat2=j;
                cost_dupa_conversie=atoi(numar_cost);
                if(negativ==1)
                    C[nr_muchii].cost=-cost_dupa_conversie;
                else C[nr_muchii].cost=cost_dupa_conversie;
                nr_muchii++;
            }
        }
    }
    for(int i=1; i<nr_muchii; i++)
    {
        for(int j=i+1; j<=nr_muchii; j++)
        {
            if(C[i].cost>C[j].cost)
            {
                swap(C[i].cost,C[j].cost);
                swap(C[i].capat1,C[j].capat1);
                swap(C[i].capat2,C[j].capat2);
            }
        }
    }
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
        radacini[i]=i;
    setcolor(RED);
    for(int i=1; i<=nr_muchii; i++)
    {
        if(radacini[C[i].capat1]!=radacini[C[i].capat2])
        {
            circle(G[C[i].capat1].x,G[C[i].capat1].y,r);
            circle(G[C[i].capat2].x,G[C[i].capat2].y,r);
            line(M[C[i].capat1][C[i].capat2].x_capat,M[C[i].capat1][C[i].capat2].y_capat,M[C[i].capat2][C[i].capat1].x_capat,M[C[i].capat2][C[i].capat1].y_capat);
            delay(1000);
            rezultat_parcurgere=rezultat_parcurgere+C[i].cost;
            radacina1=radacini[C[i].capat1];
            radacina2=radacini[C[i].capat2];
            for(int j=1; j<=nrMaxDenumireNoduri; j++)
            {
                if(radacini[j]==radacina2)
                    radacini[j]=radacina1;
            }
        }
    }
    strcpy(mesaj_final,"Rezultat algoritm Kruskal: ");
    itoa(rezultat_parcurgere,numar_cost,10);
    strcat(mesaj_final,numar_cost);
    delay(1000);
    setcolor(BLACK);
    actualizare_output_log(mesaj_final);
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent();
    delay(1);
    setvisualpage(0);
}
void componenta()
{
    int poz=0,i=0,j=0,k=0,nod_selectat=0,x_apasat,y_apasat,nod_neselectat=0,eticheta_cheie,etichete[16],eticheta1,eticheta2;
    char rezultat[200]= {NULL};
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    actualizare_output_log("Selecteaza nodul de start.");
    while(nod_neselectat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_selectat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_selectat!=0)
                nod_neselectat=1;
            else
            {
                actualizare_output_log("Nod neselectat.");
                return;
            }
        }
    }
    for(i=1; i<=nrMaxDenumireNoduri; i++)
    {
        etichete[i]=i;
    }
    for(i=1; i<nrMaxDenumireNoduri; i++)
        for(j=i+1; j<=nrMaxDenumireNoduri; j++)
        {
            if(M[i][j].exista_muchie==1&&etichete[i]!=etichete[j])
            {
                eticheta1=etichete[i];
                eticheta2=etichete[j];
                for(k=1; k<=nrMaxDenumireNoduri; k++)
                {
                    if(etichete[k]==eticheta1||etichete[k]==eticheta2)
                        etichete[k]=eticheta1;
                }
            }
        }
    eticheta_cheie=etichete[nod_selectat];
    setcolor(RED);
    for(i=1; i<=nrMaxDenumireNoduri; i++)
    {
        if(etichete[i]==eticheta_cheie)
        {
            circle(G[i].x,G[i].y,r);
            for(j=i+1;j<=nrMaxDenumireNoduri;j++)
            {
                if(M[i][j].exista_muchie==1)
                    {
                        line(M[i][j].x_capat,M[i][j].y_capat,M[j][i].x_capat,M[j][i].y_capat);
                        circle(G[j].x,G[j].y,r);
                        delay(1000);
                    }
            }
            if(i<10)
                rezultat[poz++]=i+'0';
            else
            {
                rezultat[poz++]=(i/10)+'0';
                rezultat[poz++]=(i%10)+'0';
            }
            rezultat[poz++]=' ';
        }
    }
    delay(1000);
    setcolor(BLACK);
    actualizare_output_log(rezultat);
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent();
    delay(1);
    setvisualpage(0);
}
void componenta_orientat()
{
    int poz=0,i=0,j=0,k=0,nod_selectat=0,x_apasat,y_apasat,nod_neselectat=0,eticheta_cheie,etichete[16],eticheta1,eticheta2;
    char rezultat[200]= {NULL};
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    actualizare_output_log("Selecteaza nodul de start.");
    while(nod_neselectat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_selectat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_selectat!=0)
                nod_neselectat=1;
            else
            {
                actualizare_output_log("Nod neselectat.");
                return;
            }
        }
    }
    for(i=1; i<=nrMaxDenumireNoduri; i++)
    {
        etichete[i]=i;
    }
    for(i=1; i<nrMaxDenumireNoduri; i++)
        for(j=i+1; j<=nrMaxDenumireNoduri; j++)
        {
            if((N[j][i].exista_arc==1||N[i][j].exista_arc==1)&&etichete[i]!=etichete[j])
            {
                eticheta1=etichete[i];
                eticheta2=etichete[j];
                for(k=1; k<=nrMaxDenumireNoduri; k++)
                {
                    if(etichete[k]==eticheta1||etichete[k]==eticheta2)
                        etichete[k]=eticheta1;
                }
            }
        }
    eticheta_cheie=etichete[nod_selectat];
    setcolor(RED);
    for(i=1; i<=nrMaxDenumireNoduri; i++)
    {
        if(etichete[i]==eticheta_cheie)
        {
            circle(G[i].x,G[i].y,r);
            for(int j=1;j<=nrMaxDenumireNoduri;j++)
            {
                if(N[i][j].exista_arc==1)
                {
                    line(N[i][j].x1_capat,N[i][j].y1_capat,N[i][j].x_arc,N[i][j].y_arc);
                    line(N[i][j].x2_capat,N[i][j].y2_capat,N[i][j].x_arc,N[i][j].y_arc);
                    line(N[i][j].x1_sageata,N[i][j].y1_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                    line(N[i][j].x2_sageata,N[i][j].y2_sageata,N[i][j].x2_capat,N[i][j].y2_capat);
                    delay(1000);
                }
            }
            if(i<10)
                rezultat[poz++]=i+'0';
            else
            {
                rezultat[poz++]=(i/10)+'0';
                rezultat[poz++]=(i%10)+'0';
            }
            rezultat[poz++]=' ';
        }
    }
    delay(1000);
    setcolor(BLACK);
    actualizare_output_log(rezultat);
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent_orientat();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent_orientat();
    delay(1);
    setvisualpage(0);
}
void print_cale(int tata[],int j,char rezultat[])
{
    char valoare[5]={NULL};
    int maxim=999999999;
    setcolor(RED);
    if(tata[j]==-1 || tata[j]==maxim)
        return;
    print_cale(tata,tata[j],rezultat);
    line(N[tata[j]][j].x1_capat,N[tata[j]][j].y1_capat,N[tata[j]][j].x_arc,N[tata[j]][j].y_arc);
    line(N[tata[j]][j].x2_capat,N[tata[j]][j].y2_capat,N[tata[j]][j].x_arc,N[tata[j]][j].y_arc);
    line(N[tata[j]][j].x1_sageata,N[tata[j]][j].y1_sageata,N[tata[j]][j].x2_capat,N[tata[j]][j].y2_capat);
    line(N[tata[j]][j].x2_sageata,N[tata[j]][j].y2_sageata,N[tata[j]][j].x2_capat,N[tata[j]][j].y2_capat);
    circle(G[j].x,G[j].y,r);
    delay(1000);
    if(j<maxim)
    {
        itoa(j,valoare,10);
        strcat(rezultat,valoare);
    }
    else
        strcat(rezultat,"*");
    strcat(rezultat," ");
}
void afisare(char rezultat[],int nod_selectat, int dist[], int tata[])
{
    char valoare_nod_selectat[5]={NULL},valoare_nod_curent[5]={NULL},valoare_cost[5]={NULL};
    int maxim=999999999;
    ///int to char nod_selectat
    itoa(nod_selectat,valoare_nod_selectat,10);
    for(int i=1;i<=nrMaxDenumireNoduri;i++)
    {
        if(G[i].exista_nod==1)
        {
            for(int j=200;j>=0;j--)
                rezultat[j]=NULL;
            strcpy(rezultat,valoare_nod_selectat);
            strcat(rezultat,"-");
            itoa(i,valoare_nod_curent,10);
            strcat(rezultat,valoare_nod_curent);
            strcat(rezultat,":");
            if(dist[i]<maxim)
            {
                itoa(dist[i],valoare_cost,10);
                strcat(rezultat,valoare_cost);
            }
            else
                strcat(rezultat,"*");///nod care nu este conex sau este inexistent
            setcolor(BLACK);
            delay(1000);
            actualizare_output_log(rezultat);
            for(int j=200;j>=0;j--)
                rezultat[j]=NULL;
            strcpy(rezultat,valoare_nod_selectat); ///punem radacina
            strcat(rezultat," ");
            setcolor(RED);
            circle(G[nod_selectat].x,G[nod_selectat].y,r);
            print_cale(tata,i,rezultat);
            setcolor(BLACK);
            delay(1000);
            actualizare_output_log(rezultat);
            setactivepage(1);
            cleardevice();
            redesenare_graf_curent_orientat();
            setvisualpage(1);
            setactivepage(0);
            cleardevice();
            redesenare_graf_curent_orientat();
            delay(1);
            setvisualpage(0);
        }
    }
}
void Dijkstra()
{
    int nod_neselectat=0,x_apasat,y_apasat,nod_selectat=0,dist[16],vizitat[16],maxim=999999999,cost_u_v,tata[16],mini,mini_index,u;
    char rezultat[200]={NULL};
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    if(!graf_cu_costuri_valid_orientat())
    {
        actualizare_output_log("Costuri lipsa.");
        return;
    }
    ///eroare costuri negative
    for(int i=1;i<=nrMaxDenumireNoduri;i++)
        for(int j=1;j<=nrMaxDenumireNoduri;j++)
            if(N[i][j].cost[0]=='-')
            {
                actualizare_output_log("Eroare costuri negative Dijkstra.");
                return;
            }
    ///actualizarea output-log-ului
    bar(0,151,300,1200);
    nrLinii=0;
    ///alegerea nodului selectat
    actualizare_output_log("Selectati nodul de start:");
    while(nod_neselectat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_selectat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_selectat!=0)
                nod_neselectat=1;
            else
            {
                actualizare_output_log("Nod neselectat.");
                return;
            }
        }
    }
    for(int i=1;i<=nrMaxDenumireNoduri;i++)
    {
        dist[i]=maxim;
        tata[i]=maxim;
        vizitat[i]=0;
    }
    tata[nod_selectat]=-1;
    dist[nod_selectat]=0;
    for(int i=1;i<=nrMaxDenumireNoduri;i++)
    {
        mini=maxim;
        mini_index=0;
        for(int j=1;j<=nrMaxDenumireNoduri;j++)///intra intotdeauna pentru primul nod si gaseste nodul cu cost minim conectat
            if(vizitat[j]==0 && dist[j]<=mini)
            {
                mini=dist[j];
                mini_index=j;
            }
        u=mini_index;
        vizitat[u]=1;
        for(int v=1;v<=nrMaxDenumireNoduri;v++)
        {
            if(N[u][v].cost[0]!='*')
            {
                cost_u_v=atoi(N[u][v].cost);
                if(vizitat[v]==0 && dist[u]!=maxim && dist[u]+cost_u_v<dist[v])///"relaxeaza" toate nodurile adiacente
                {
                    dist[v]=dist[u]+cost_u_v;
                    tata[v]=u;
                }
            }
        }
    }
    afisare(rezultat,nod_selectat,dist,tata);
}
void BellmanFord()
{
    int nod_neselectat=0,x_apasat,y_apasat,nod_selectat,dist[16],maxim=9999999999,nr_arce=1,negativ,cost_dupa_conversie,tata[16]={0};
    char numar_cost[10],rezultat[200]={NULL};
    bar(0,151,300,1200);
    nrLinii=0;
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    if(!graf_cu_costuri_valid_orientat())
    {
        actualizare_output_log("Costuri lipsa.");
        return;
    }
    ///alegerea nodului
    actualizare_output_log("Selectati nodul de start:");
    while(nod_neselectat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_selectat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_selectat!=0)
                nod_neselectat=1;
            else
            {
                actualizare_output_log("Nod neselectat.");
                return;
            }
        }
    }
    InitVectorCosturi(C);
    for(int i=1; i<=nrMaxDenumireNoduri; i++)
    {
        for(int j=1; j<=nrMaxDenumireNoduri; j++)
        {
            negativ=0;
            if(N[i][j].exista_arc==1&&N[i][j].cost[0]!='*')
            {
                strcpy(numar_cost,N[i][j].cost);
                if(numar_cost[0]=='-')
                {
                    negativ=1;
                    strcpy(numar_cost,numar_cost+1);
                }
                C[nr_arce].capat1=i;
                C[nr_arce].capat2=j;
                cost_dupa_conversie=atoi(numar_cost);
                if(negativ==1)
                    C[nr_arce].cost=-cost_dupa_conversie;
                else C[nr_arce].cost=cost_dupa_conversie;
                nr_arce++;
            }
        }
    }
    nr_arce--;
    for(int i=1;i<=nrMaxDenumireNoduri;i++)
        dist[i]=maxim;
    dist[nod_selectat]=0;
    tata[nod_selectat]=-1;
    for(int i=1;i<=nrMaxDenumireNoduri-1;i++)
        for(int j=1;j<=nr_arce;j++)
        {
            int u=C[j].capat1;
            int v=C[j].capat2;
            int cost=C[j].cost;
            if(dist[u]!=maxim && dist[u]+cost<dist[v])
                {
                    dist[v]=dist[u]+cost;
                    tata[v]=u;
                }
        }
    ///verficare ciclu cost negativ
    for(int j=1;j<=nr_arce;j++)
    {
        int u=C[j].capat1;
        int v=C[j].capat2;
        int cost=C[j].cost;
        if(dist[u]!=maxim && dist[u]+cost<dist[v])
        {
            actualizare_output_log("Graful contine ciclu cu cost negativ.");
            return;
        }
    }
    afisare(rezultat,nod_selectat,dist,tata);
}
void FloydWarshall()
{
    int dist[16][16],maxim=999999999,negativ=0;
    char numar_cost[200]={NULL},rezultat[200]={NULL};
    bar(0,151,300,1200);
    nrLinii=0;
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    if(!graf_cu_costuri_valid_orientat())
    {
        actualizare_output_log("Costuri lipsa.");
        return;
    }
    for(int i=1;i<=nrMaxDenumireNoduri;i++)
        for(int j=1;j<=nrMaxDenumireNoduri;j++)
            if(i==j)
                dist[i][j]=0;
            else if(N[i][j].exista_arc==1)
            {
                strcpy(numar_cost,N[i][j].cost);
                if(numar_cost[0]=='-')
                {
                    negativ=1;
                    strcpy(numar_cost,numar_cost+1);
                }
                if(negativ==0)
                    dist[i][j]=atoi(numar_cost);
                else
                    dist[i][j]=-atoi(numar_cost);
            }
            else if(N[i][j].exista_arc==0)
                    dist[i][j]=maxim;
    for(int k=1;k<=nrMaxDenumireNoduri;k++)
        for(int i=1;i<=nrMaxDenumireNoduri;i++)
            for(int j=1;j<=nrMaxDenumireNoduri;j++)
                if((dist[k][j]!=maxim && dist[i][k]!=maxim)&&dist[i][j]>(dist[i][k]+dist[k][j]))
                    dist[i][j]=dist[i][k]+dist[k][j];
    for(int i=1;i<=nrMaxDenumireNoduri;i++)
    {
        for(int k=200;k>=0;k--)
        {
            rezultat[k]=NULL;
            numar_cost[k]=NULL;
        }
        for(int j=1;j<=nrMaxDenumireNoduri;j++)
        {
            if(dist[i][j]<maxim)
            {
                itoa(dist[i][j],numar_cost,10);
                strcat(rezultat,numar_cost);
            }
            else
                strcat(rezultat,"*");
            strcat(rezultat," ");
        }
        actualizare_output_log(rezultat);
    }
}
bool bfs_fordfulkerson(int graf_rezidual[16][16],int s, int t,int tata[16])
{
    int poz=0,k=0,st,dr,vizitat[16]={0},coada[16]={0};
    st=dr=1;
    coada[1]=s;
    vizitat[s]=1;
    tata[s]=-1;
    while(st<=dr)
    {
        k=coada[st];
        for(int i=1; i<=nrMaxDenumireNoduri; i++)
            if(vizitat[i]==0 && graf_rezidual[k][i]>0)
            {
                vizitat[i]=1;//il vizitez
                if(i==t)
                {
                    tata[i]=k;
                    return true;
                }
                tata[i]=k;
                coada[++dr]=i;//il adaug in coada
            }
        st++;//sterg din coada
    }
    return false;
}
void FordFulkerson()
{
    int nod_neselectat=0,nod_selectat,s,t,x_apasat,y_apasat,maxim=999999999,graf_rezidual[16][16],tata[16],max_flux=0,u;
    char rezultat[200]={NULL},flux_curent_rezultat[200]={NULL},nod_start[200]={NULL};
    if(nrDeNoduriCurent==0)
    {
        actualizare_output_log("Graf indisponibil.");
        return;
    }
    if(!graf_cu_costuri_valid_orientat())
    {
        actualizare_output_log("Costuri lipsa.");
        return;
    }
    bar(0,151,300,1200);
    nrLinii=0;
    ///verificare costuri negative
    for(int i=1;i<=nrMaxDenumireNoduri;i++)
        for(int j=1;j<=nrMaxDenumireNoduri;j++)
            if(N[i][j].cost[0]=='-')
            {
                actualizare_output_log("Eroare costuri negative.");
                return;
            }
    ///alegerea nodului
    actualizare_output_log("Selectati nodul de start:");
    while(nod_neselectat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_selectat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_selectat!=0)
                nod_neselectat=1;
            else
            {
                actualizare_output_log("Nod neselectat.");
                return;
            }
        }
    }
    s=nod_selectat;
    nod_neselectat=0;
    nod_selectat=0;
    actualizare_output_log("Selectati nodul final:");
    while(nod_neselectat==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x_apasat=mousex();
            y_apasat=mousey();
            nod_selectat=gasire_nod_apasat(x_apasat,y_apasat);
            if(nod_selectat!=0)
                nod_neselectat=1;
            else
            {
                actualizare_output_log("Nod neselectat.");
                return;
            }
        }
    }
    t=nod_selectat;
    ///initializare graf rezidual
    for(int i=1;i<=nrMaxDenumireNoduri;i++)
        for(int j=1;j<=nrMaxDenumireNoduri;j++)
        {
            if(N[i][j].cost[0]=='*')
                graf_rezidual[i][j]=0;
            else
                graf_rezidual[i][j]=atoi(N[i][j].cost);
        }
    for(int i=1;i<=nrMaxDenumireNoduri;i++)
        tata[i]=0;
    while(bfs_fordfulkerson(graf_rezidual,s,t,tata))
    {
        int flux_curent=maxim;
        for(int i=200;i>=0;i--)
        {
            rezultat[i]=NULL;
            flux_curent_rezultat[i]=NULL;
        }
        for(int v=t;v!=s;v=tata[v])
        {
            u=tata[v];
            if(graf_rezidual[u][v]<flux_curent)
                flux_curent=graf_rezidual[u][v];
        }
        for(int v=t;v!=s;v=tata[v])
        {
            u=tata[v];
            graf_rezidual[u][v]=graf_rezidual[u][v]-flux_curent;
            graf_rezidual[v][u]=graf_rezidual[u][v]+flux_curent;
        }
        for(int i=200;i>=0;i--)
            nod_start[i]=NULL;
        setcolor(RED);
        circle(G[s].x,G[s].y,r);
        itoa(s,nod_start,10);
        strcat(rezultat,nod_start);
        strcat(rezultat," ");
        print_cale(tata,t,rezultat);
        setcolor(BLACK);
        actualizare_output_log(rezultat);
        itoa(flux_curent,flux_curent_rezultat,10);
        setcolor(BLACK);
        delay(2000);
        actualizare_output_log("Rezultatul pentru calea curenta: ");
        actualizare_output_log(flux_curent_rezultat);
        delay(2000);
        setactivepage(1);
        cleardevice();
        redesenare_graf_curent_orientat();
        setvisualpage(1);
        setactivepage(0);
        cleardevice();
        redesenare_graf_curent_orientat();
        delay(1);
        setvisualpage(0);
        max_flux=max_flux+flux_curent;
    }
    itoa(max_flux,rezultat,10);
    delay(1000);
    actualizare_output_log("Rezultatul Ford-Fulkerson este: ");
    actualizare_output_log(rezultat);
    setactivepage(1);
    cleardevice();
    redesenare_graf_curent_orientat();
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    redesenare_graf_curent_orientat();
    delay(1);
    setvisualpage(0);
}
void colorare_buton(int x,int y,char nume_buton[20])
{
    setfillstyle(SOLID_FILL,DARKGRAY);
    floodfill(x,y,BLACK);
    setbkcolor(DARKGRAY);
    outtextxy(x,y,nume_buton);
    delay(100);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x,y,BLACK);
    setbkcolor(LIGHTGRAY);
    outtextxy(x,y,nume_buton);
}
int main()
{
    OpenGraph();
    InitWindowMenu();
    float x_mouse,y_mouse;
    while(1)
    {
        if(meniu==1)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                x_mouse=mousex();
                y_mouse=mousey();
                if(x_mouse>=425 && x_mouse<=775 && y_mouse>=225 && y_mouse<=275)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(600,250,"Grafuri neorientate");
                    settextstyle(0,0,1);
                    spre_graf_neorientat();
                }
                else if(x_mouse>=425 && x_mouse<=775 && y_mouse>=325 && y_mouse<=375)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(600,350,"Grafuri orientate");
                    settextstyle(0,0,1);
                    spre_graf_orientat();
                }
                else if(x_mouse>=550 && x_mouse<=650 && y_mouse>=425 && y_mouse<=475)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(600,450,"Exit");
                    closegraph();
                    break;
                }
                clearmouseclick(WM_LBUTTONDOWN);
            }
        }
        else if(ecran_neorientat==1)
        {
            int nod_apasat=0,nodul_este_miscat;
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                x_mouse=mousex();
                y_mouse=mousey();
                if(x_mouse>=10 && x_mouse<=110 && y_mouse>=10 && y_mouse<=60)///buton exit
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(60,35,"Exit");
                    closegraph();
                    break;
                }
                else if(x_mouse>=1000 && x_mouse<=1190 && y_mouse>=10 && y_mouse<=60)///buton spre grafuri orientate
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(1095,35,"Spre Graf Orientat ->");
                    spre_graf_orientat();
                }
                else if(x_mouse>=325 && x_mouse<=475 && y_mouse>=475 && y_mouse<=525)///buton adaugare nod
                {
                    clearmouseclick(WM_LBUTTONDOWN); ///elibereaza ca sa se faca un singur click
                    colorare_buton(400,500,"Adaugare nod");
                    adaugare_nod();
                }
                else if(x_mouse>=525 && x_mouse<=675 && y_mouse>=475 && y_mouse<=525)///buton adaugare muchie
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(600,500,"Adaugare muchie");
                    adaugare_muchie();
                }
                else if(x_mouse>=725 && x_mouse<=875 && y_mouse>=475 && y_mouse<=525)///buton adaugare cost
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(800,500,"Adaugare cost");
                    adaugare_cost();
                }
                else if(x_mouse>=325 && x_mouse<=475 && y_mouse>=550 && y_mouse<=600)///buton stergere nod
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(400,575,"Stergere nod");
                    stergere_nod();
                }
                else if(x_mouse>=525 && x_mouse<=675 && y_mouse>=550 && y_mouse<=600)///buton stergere muchie
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(600,575,"Stergere muchie");
                    stergere_muchie();
                }
                else if(x_mouse>=725 && x_mouse<=875 && y_mouse>=550 && y_mouse<=600)///buton stergere tot graful
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(800,575,"Stergere graf");
                    stergere_graf();
                }
                else if(x_mouse>=920 && x_mouse<=1040 && y_mouse>=175 && y_mouse<=225)///buton BFS
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(980,200,"BFS");
                    BFSN();
                }
                else if(x_mouse>=1060 && x_mouse<=1180 && y_mouse>=175 && y_mouse<=225)///buton DFS
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(1120,200,"DFS");
                    DFSN();
                }
                else if(x_mouse>=920 && x_mouse<=1040 && y_mouse>=250 && y_mouse<=300)///buton PRIM
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(980,275,"Prim");
                    Prim();
                }
                else if(x_mouse>=920 && x_mouse<=1040 && y_mouse>=325 && y_mouse<=375)///buton CONEX
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(980,350,"Conexitate");
                    conexitate();
                }
                else if(x_mouse>=1060 && x_mouse<=1180 && y_mouse>=250 && y_mouse<=300)///buton kruskal
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(1120,275,"Kruskal");
                    Kruskal();
                }
                else if(x_mouse>=1060 && x_mouse<=1180 && y_mouse>=325 && y_mouse<=375)///buton componenta
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(1120,350,"Componenta");
                    componenta();
                }
                else if(x_mouse>=300 && x_mouse<=900 && y_mouse>=75 && y_mouse<=450)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    nod_apasat=gasire_nod_apasat(x_mouse,y_mouse);
                    if(nod_apasat!=0&&nod_neciocnit(x_mouse,y_mouse,nod_apasat))
                    {
                        nodul_este_miscat=1;
                        while(nodul_este_miscat)
                        {
                            x_mouse=mousex();
                            y_mouse=mousey();
                            if(x_mouse>=300+r && x_mouse<=900-r && y_mouse>=75+r && y_mouse<=450-r && nod_neciocnit(x_mouse, y_mouse,nod_apasat))
                            {
                                G[nod_apasat].x=x_mouse;
                                G[nod_apasat].y=y_mouse;
                                setactivepage(1);
                                cleardevice();
                                redesenare_ecran_nod_mutat(nod_apasat);
                                circle(x_mouse,y_mouse,r);
                                itoa(nod_apasat,numeNod,10);
                                outtextxy(x_mouse,y_mouse,numeNod);
                                for(int i=1; i<=nrMaxDenumireNoduri; i++)
                                {
                                    if(M[nod_apasat][i].exista_muchie==1)
                                    {
                                        M[nod_apasat][i].x_capat=G[nod_apasat].x+r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        M[nod_apasat][i].y_capat=G[nod_apasat].y+r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        M[i][nod_apasat].x_capat=G[i].x+r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        M[i][nod_apasat].y_capat=G[i].y+r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        line(M[nod_apasat][i].x_capat,M[nod_apasat][i].y_capat,M[i][nod_apasat].x_capat,M[i][nod_apasat].y_capat);
                                        if(M[nod_apasat][i].cost[0]!='*')
                                        {
                                            outtextxy((M[nod_apasat][i].x_capat+M[i][nod_apasat].x_capat)/2,(M[nod_apasat][i].y_capat+M[i][nod_apasat].y_capat)/2,M[nod_apasat][i].cost);
                                        }
                                    }
                                }
                                setvisualpage(1);
                                setactivepage(0);
                                cleardevice();
                                redesenare_ecran_nod_mutat(nod_apasat);
                                circle(x_mouse,y_mouse,r);
                                itoa(nod_apasat,numeNod,10);
                                outtextxy(x_mouse,y_mouse,numeNod);
                                for(int i=1; i<=nrMaxDenumireNoduri; i++)
                                {
                                    if(M[nod_apasat][i].exista_muchie==1)
                                    {
                                        M[nod_apasat][i].x_capat=G[nod_apasat].x+r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        M[nod_apasat][i].y_capat=G[nod_apasat].y+r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        M[i][nod_apasat].x_capat=G[i].x+r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        M[i][nod_apasat].y_capat=G[i].y+r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        line(M[nod_apasat][i].x_capat,M[nod_apasat][i].y_capat,M[i][nod_apasat].x_capat,M[i][nod_apasat].y_capat);
                                        if(M[nod_apasat][i].cost[0]!='*')
                                        {
                                            outtextxy((M[nod_apasat][i].x_capat+M[i][nod_apasat].x_capat)/2,(M[nod_apasat][i].y_capat+M[i][nod_apasat].y_capat)/2,M[nod_apasat][i].cost);
                                        }
                                    }
                                }
                                delay(1);
                                setvisualpage(0);
                            }
                            if(ismouseclick(WM_LBUTTONDOWN))
                            {
                                nodul_este_miscat=0;
                                clearmouseclick(WM_LBUTTONDOWN);
                            }
                        }
                        setactivepage(1);
                        cleardevice();
                        redesenare_graf_curent();
                        setvisualpage(1);
                        setactivepage(0);
                        cleardevice();
                        redesenare_graf_curent();
                        delay(1);
                        setvisualpage(0);
                    }
                }
                clearmouseclick(WM_LBUTTONDOWN);
            }
        }
        else if(ecran_orientat==1)
        {
            int nod_apasat=0,nodul_este_miscat, aux, nod_1, nod_2;
            float x_mijloc_sageata, y_mijloc_sageata, aux_x, aux_y, aux_dist, x_mij, y_mij, x1_mij_arc, y1_mij_arc, x2_mij_arc, y2_mij_arc;
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                x_mouse=mousex();
                y_mouse=mousey();
                if(x_mouse>=10 && x_mouse<=200 && y_mouse>=10 && y_mouse<=60)///buton spre grafuri neorientate
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(105,35,"<- Spre graf neorientat");
                    spre_graf_neorientat();
                }
                else if(x_mouse>=1090 && x_mouse<=1190 && y_mouse>=10 && y_mouse<=60)///buton exit
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(1140,35,"Exit");
                    closegraph();
                    break;
                }
                else if(x_mouse>=325 && x_mouse<=475 && y_mouse>=475 && y_mouse<=525)///buton adaugare nod
                {
                    clearmouseclick(WM_LBUTTONDOWN); ///elibereaza ca sa se faca un singur click
                    colorare_buton(400,500,"Adaugare nod");
                    adaugare_nod();
                }
                else if(x_mouse>=525 && x_mouse<=675 && y_mouse>=475 && y_mouse<=525)///buton adaugare arc
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(600,500,"Adaugare arc");
                    adaugare_arc();
                }
                else if(x_mouse>=725 && x_mouse<=875 && y_mouse>=475 && y_mouse<=525)///buton adaugare cost
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(800,500,"Adaugare cost");
                    adaugare_cost_orientat();
                }
                else if(x_mouse>=325 && x_mouse<=475 && y_mouse>=550 && y_mouse<=600)///buton stergere nod
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(400,575,"Stergere nod");
                    stergere_nod_orientat();
                }
                else if(x_mouse>=525 && x_mouse<=675 && y_mouse>=550 && y_mouse<=600)///buton stergere arc
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(600,575,"Stergere arc");
                    stergere_arc();
                }
                else if(x_mouse>=725 && x_mouse<=875 && y_mouse>=550 && y_mouse<=600)///buton stergere tot graful
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(800,575,"Stergere graf");
                    stergere_graf_orientat();
                }
                else if(x_mouse>=920 && x_mouse<=1040 && y_mouse>=175 && y_mouse<=225)///buton BFS
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(980,200,"BFS");
                    BFSO();
                }
                else if(x_mouse>=1060 && x_mouse<=1180 && y_mouse>=175 && y_mouse<=225)///buton DFS
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(1120,200,"DFS");
                    DFSO();
                }
                else if(x_mouse>=920 && x_mouse<=1040 && y_mouse>=250 && y_mouse<=300)///buton dijkstra
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(980,275,"Dijkstra");
                    Dijkstra();
                }
                else if(x_mouse>=920 && x_mouse<=1040 && y_mouse>=325 && y_mouse<=375)///buton floyd-warshall
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(980,350,"Floyd-Warshall");
                    FloydWarshall();
                }
                else if(x_mouse>=920 && x_mouse<=1040 && y_mouse>=400 && y_mouse<=450)///buton tare conexitate
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(980,425,"Tare conex");
                    tare_conexitate();
                }
                else if(x_mouse>=1060 && x_mouse<=1180 && y_mouse>=250 && y_mouse<=300)///buton bellman-ford
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(1120,275,"Bellman-Ford");
                    BellmanFord();
                }
                else if(x_mouse>=1060 && x_mouse<=1180 && y_mouse>=325 && y_mouse<=375)///buton ford-fulkerson
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(1120,350,"Ford-Fulkerson");
                    FordFulkerson();
                }
                else if(x_mouse>=1060 && x_mouse<=1180 && y_mouse>=400 && y_mouse<=450)///buton componenta
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    colorare_buton(1120,425,"Componenta");
                    componenta_orientat();
                }
                else if(x_mouse>=300 && x_mouse<=900 && y_mouse>=75 && y_mouse<=450)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    nod_apasat=gasire_nod_apasat(x_mouse,y_mouse);
                    if(nod_apasat!=0&&nod_neciocnit(x_mouse,y_mouse,nod_apasat))
                    {
                        nodul_este_miscat=1;
                        while(nodul_este_miscat)
                        {
                            x_mouse=mousex();
                            y_mouse=mousey();
                            if(x_mouse>=300+r && x_mouse<=900-r && y_mouse>=75+r && y_mouse<=450-r && nod_neciocnit(x_mouse, y_mouse,nod_apasat))
                            {
                                G[nod_apasat].x=x_mouse;
                                G[nod_apasat].y=y_mouse;
                                setactivepage(1);
                                cleardevice();
                                redesenare_ecran_nod_mutat_orientat(nod_apasat);
                                circle(x_mouse,y_mouse,r);
                                itoa(nod_apasat,numeNod,10);
                                outtextxy(x_mouse,y_mouse,numeNod);
                                for(int i=1; i<=nrMaxDenumireNoduri; i++)
                                {
                                    if(N[nod_apasat][i].exista_arc==1 && N[i][nod_apasat].exista_arc==0)
                                    {
                                        N[nod_apasat][i].x1_capat=G[nod_apasat].x+r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].y1_capat=G[nod_apasat].y+r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].x2_capat=G[i].x+r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].y2_capat=G[i].y+r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        line(N[nod_apasat][i].x1_capat,N[nod_apasat][i].y1_capat,N[nod_apasat][i].x2_capat,N[nod_apasat][i].y2_capat);
                                        N[nod_apasat][i].x_arc=(N[nod_apasat][i].x1_capat+N[nod_apasat][i].x2_capat)/2;
                                        N[nod_apasat][i].y_arc=(N[nod_apasat][i].y1_capat+N[nod_apasat][i].y2_capat)/2;
                                        x_mijloc_sageata=G[i].x+2*r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        y_mijloc_sageata=G[i].y+2*r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        aux_x=x_mijloc_sageata-G[i].x;
                                        aux_y=y_mijloc_sageata-G[i].y;
                                        aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                        aux_x=aux_x/aux_dist;
                                        aux_y=aux_y/aux_dist;
                                        N[nod_apasat][i].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                        N[nod_apasat][i].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                        N[nod_apasat][i].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                        N[nod_apasat][i].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                        line(N[nod_apasat][i].x1_sageata,N[nod_apasat][i].y1_sageata,N[nod_apasat][i].x2_capat,N[nod_apasat][i].y2_capat);
                                        line(N[nod_apasat][i].x2_sageata,N[nod_apasat][i].y2_sageata,N[nod_apasat][i].x2_capat,N[nod_apasat][i].y2_capat);
                                        if(N[nod_apasat][i].cost[0]!='*')
                                        {
                                            outtextxy(N[nod_apasat][i].x_arc,N[nod_apasat][i].y_arc,N[nod_apasat][i].cost);
                                        }
                                    }
                                    else if(N[nod_apasat][i].exista_arc==0 && N[i][nod_apasat].exista_arc==1)
                                    {
                                        N[i][nod_apasat].x1_capat=G[i].x+r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].y1_capat=G[i].y+r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].x2_capat=G[nod_apasat].x+r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].y2_capat=G[nod_apasat].y+r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        line(N[i][nod_apasat].x1_capat,N[i][nod_apasat].y1_capat,N[i][nod_apasat].x2_capat,N[i][nod_apasat].y2_capat);
                                        N[i][nod_apasat].x_arc=(N[i][nod_apasat].x1_capat+N[i][nod_apasat].x2_capat)/2;
                                        N[i][nod_apasat].y_arc=(N[i][nod_apasat].y1_capat+N[i][nod_apasat].y2_capat)/2;
                                        x_mijloc_sageata=G[nod_apasat].x+2*r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        y_mijloc_sageata=G[nod_apasat].y+2*r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        aux_x=x_mijloc_sageata-G[nod_apasat].x;
                                        aux_y=y_mijloc_sageata-G[nod_apasat].y;
                                        aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                        aux_x=aux_x/aux_dist;
                                        aux_y=aux_y/aux_dist;
                                        N[i][nod_apasat].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                        N[i][nod_apasat].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                        N[i][nod_apasat].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                        N[i][nod_apasat].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                        line(N[i][nod_apasat].x1_sageata,N[i][nod_apasat].y1_sageata,N[i][nod_apasat].x2_capat,N[i][nod_apasat].y2_capat);
                                        line(N[i][nod_apasat].x2_sageata,N[i][nod_apasat].y2_sageata,N[i][nod_apasat].x2_capat,N[i][nod_apasat].y2_capat);
                                        if(N[i][nod_apasat].cost[0]!='*')
                                        {
                                            outtextxy(N[i][nod_apasat].x_arc,N[i][nod_apasat].y_arc,N[i][nod_apasat].cost);
                                        }
                                    }
                                    else if(N[nod_apasat][i].exista_arc==1 && N[i][nod_apasat].exista_arc==1)
                                    {
                                        N[nod_apasat][i].x1_capat=G[nod_apasat].x+r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].y1_capat=G[nod_apasat].y+r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].x2_capat=G[i].x+r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].y2_capat=G[i].y+r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[i][nod_apasat].x1_capat=G[i].x+r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].y1_capat=G[i].y+r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].x2_capat=G[nod_apasat].x+r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].y2_capat=G[nod_apasat].y+r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        nod_1=nod_apasat;
                                        nod_2=i;
                                        x_mij=(N[nod_1][nod_2].x1_capat+N[nod_1][nod_2].x2_capat)/2;
                                        y_mij=(N[nod_1][nod_2].y1_capat+N[nod_1][nod_2].y2_capat)/2;
                                        aux_x=x_mij-N[nod_1][nod_2].x1_capat;
                                        aux_y=y_mij-N[nod_1][nod_2].y1_capat;
                                        aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                        aux_x=aux_x/aux_dist;
                                        aux_y=aux_y/aux_dist;
                                        x1_mij_arc=x_mij+(2*r/3)*aux_y;
                                        y1_mij_arc=y_mij-(2*r/3)*aux_x;
                                        x2_mij_arc=x_mij-(2*r/3)*aux_y;
                                        y2_mij_arc=y_mij+(2*r/3)*aux_x;
                                        if(nod_1>nod_2)
                                        {
                                            aux=nod_1;
                                            nod_1=nod_2;
                                            nod_2=aux;
                                        }
                                        if(y1_mij_arc<y2_mij_arc)
                                        {
                                            N[nod_1][nod_2].x_arc=x1_mij_arc;
                                            N[nod_1][nod_2].y_arc=y1_mij_arc;
                                            N[nod_2][nod_1].x_arc=x2_mij_arc;
                                            N[nod_2][nod_1].y_arc=y2_mij_arc;
                                            ///incep cu arcul de sus
                                            x_mijloc_sageata=N[nod_1][nod_2].x2_capat+r*(x1_mij_arc-N[nod_1][nod_2].x2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x1_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y1_mij_arc,2));
                                            y_mijloc_sageata=N[nod_1][nod_2].y2_capat+r*(y1_mij_arc-N[nod_1][nod_2].y2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x1_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y1_mij_arc,2));
                                            aux_x=x_mijloc_sageata-N[nod_1][nod_2].x2_capat;
                                            aux_y=y_mijloc_sageata-N[nod_1][nod_2].y2_capat;
                                            aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                            aux_x=aux_x/aux_dist;
                                            aux_y=aux_y/aux_dist;
                                            N[nod_1][nod_2].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                            N[nod_1][nod_2].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                            N[nod_1][nod_2].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                            N[nod_1][nod_2].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                            line(N[nod_1][nod_2].x1_sageata,N[nod_1][nod_2].y1_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                            line(N[nod_1][nod_2].x2_sageata,N[nod_1][nod_2].y2_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                            ///arcul de jos acum
                                            x_mijloc_sageata=N[nod_2][nod_1].x2_capat+r*(x2_mij_arc-N[nod_2][nod_1].x2_capat)/sqrt(pow(x2_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y2_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                            y_mijloc_sageata=N[nod_2][nod_1].y2_capat+r*(y2_mij_arc-N[nod_2][nod_1].y2_capat)/sqrt(pow(x2_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y2_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                            aux_x=x_mijloc_sageata-N[nod_2][nod_1].x2_capat;
                                            aux_y=y_mijloc_sageata-N[nod_2][nod_1].y2_capat;
                                            aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                            aux_x=aux_x/aux_dist;
                                            aux_y=aux_y/aux_dist;
                                            N[nod_2][nod_1].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                            N[nod_2][nod_1].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                            N[nod_2][nod_1].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                            N[nod_2][nod_1].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                            line(N[nod_2][nod_1].x1_sageata,N[nod_2][nod_1].y1_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                            line(N[nod_2][nod_1].x2_sageata,N[nod_2][nod_1].y2_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                        }
                                        else if(y1_mij_arc>=y2_mij_arc)
                                        {
                                            N[nod_1][nod_2].x_arc=x2_mij_arc;
                                            N[nod_1][nod_2].y_arc=y2_mij_arc;
                                            N[nod_2][nod_1].x_arc=x1_mij_arc;
                                            N[nod_2][nod_1].y_arc=y1_mij_arc;
                                            ///incep cu arcul de sus
                                            x_mijloc_sageata=N[nod_1][nod_2].x2_capat+r*(x2_mij_arc-N[nod_1][nod_2].x2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x2_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y2_mij_arc,2));
                                            y_mijloc_sageata=N[nod_1][nod_2].y2_capat+r*(y2_mij_arc-N[nod_1][nod_2].y2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x2_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y2_mij_arc,2));
                                            aux_x=x_mijloc_sageata-N[nod_1][nod_2].x2_capat;
                                            aux_y=y_mijloc_sageata-N[nod_1][nod_2].y2_capat;
                                            aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                            aux_x=aux_x/aux_dist;
                                            aux_y=aux_y/aux_dist;
                                            N[nod_1][nod_2].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                            N[nod_1][nod_2].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                            N[nod_1][nod_2].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                            N[nod_1][nod_2].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                            line(N[nod_1][nod_2].x1_sageata,N[nod_1][nod_2].y1_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                            line(N[nod_1][nod_2].x2_sageata,N[nod_1][nod_2].y2_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                            ///arcul de jos acum
                                            x_mijloc_sageata=N[nod_2][nod_1].x2_capat+r*(x1_mij_arc-N[nod_2][nod_1].x2_capat)/sqrt(pow(x1_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y1_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                            y_mijloc_sageata=N[nod_2][nod_1].y2_capat+r*(y1_mij_arc-N[nod_2][nod_1].y2_capat)/sqrt(pow(x1_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y1_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                            aux_x=x_mijloc_sageata-N[nod_2][nod_1].x2_capat;
                                            aux_y=y_mijloc_sageata-N[nod_2][nod_1].y2_capat;
                                            aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                            aux_x=aux_x/aux_dist;
                                            aux_y=aux_y/aux_dist;
                                            N[nod_2][nod_1].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                            N[nod_2][nod_1].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                            N[nod_2][nod_1].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                            N[nod_2][nod_1].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                            line(N[nod_2][nod_1].x1_sageata,N[nod_2][nod_1].y1_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                            line(N[nod_2][nod_1].x2_sageata,N[nod_2][nod_1].y2_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                        }
                                        line(N[nod_1][nod_2].x_arc,N[nod_1][nod_2].y_arc,N[nod_1][nod_2].x1_capat,N[nod_1][nod_2].y1_capat);
                                        line(N[nod_1][nod_2].x_arc,N[nod_1][nod_2].y_arc,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                        line(N[nod_2][nod_1].x_arc,N[nod_2][nod_1].y_arc,N[nod_2][nod_1].x1_capat,N[nod_2][nod_1].y1_capat);
                                        line(N[nod_2][nod_1].x_arc,N[nod_2][nod_1].y_arc,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                        if(N[nod_apasat][i].cost[0]!='*')
                                        {
                                            outtextxy(N[nod_apasat][i].x_arc,N[nod_apasat][i].y_arc,N[nod_apasat][i].cost);
                                        }
                                        if(N[i][nod_apasat].cost[0]!='*')
                                        {
                                            outtextxy(N[i][nod_apasat].x_arc,N[i][nod_apasat].y_arc,N[i][nod_apasat].cost);
                                        }
                                    }
                                }
                                setvisualpage(1);
                                setactivepage(0);
                                cleardevice();
                                redesenare_ecran_nod_mutat_orientat(nod_apasat);
                                circle(x_mouse,y_mouse,r);
                                itoa(nod_apasat,numeNod,10);
                                outtextxy(x_mouse,y_mouse,numeNod);
                                for(int i=1; i<=nrMaxDenumireNoduri; i++)
                                {
                                    if(N[nod_apasat][i].exista_arc==1 && N[i][nod_apasat].exista_arc==0)
                                    {
                                        N[nod_apasat][i].x1_capat=G[nod_apasat].x+r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].y1_capat=G[nod_apasat].y+r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].x2_capat=G[i].x+r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].y2_capat=G[i].y+r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        line(N[nod_apasat][i].x1_capat,N[nod_apasat][i].y1_capat,N[nod_apasat][i].x2_capat,N[nod_apasat][i].y2_capat);
                                        N[nod_apasat][i].x_arc=(N[nod_apasat][i].x1_capat+N[nod_apasat][i].x2_capat)/2;
                                        N[nod_apasat][i].y_arc=(N[nod_apasat][i].y1_capat+N[nod_apasat][i].y2_capat)/2;
                                        x_mijloc_sageata=G[i].x+2*r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        y_mijloc_sageata=G[i].y+2*r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        aux_x=x_mijloc_sageata-G[i].x;
                                        aux_y=y_mijloc_sageata-G[i].y;
                                        aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                        aux_x=aux_x/aux_dist;
                                        aux_y=aux_y/aux_dist;
                                        N[nod_apasat][i].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                        N[nod_apasat][i].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                        N[nod_apasat][i].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                        N[nod_apasat][i].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                        line(N[nod_apasat][i].x1_sageata,N[nod_apasat][i].y1_sageata,N[nod_apasat][i].x2_capat,N[nod_apasat][i].y2_capat);
                                        line(N[nod_apasat][i].x2_sageata,N[nod_apasat][i].y2_sageata,N[nod_apasat][i].x2_capat,N[nod_apasat][i].y2_capat);
                                        if(N[nod_apasat][i].cost[0]!='*')
                                        {
                                            outtextxy(N[nod_apasat][i].x_arc,N[nod_apasat][i].y_arc,N[nod_apasat][i].cost);
                                        }
                                    }
                                    else if(N[nod_apasat][i].exista_arc==0 && N[i][nod_apasat].exista_arc==1)
                                    {
                                        N[i][nod_apasat].x1_capat=G[i].x+r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].y1_capat=G[i].y+r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].x2_capat=G[nod_apasat].x+r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].y2_capat=G[nod_apasat].y+r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        line(N[i][nod_apasat].x1_capat,N[i][nod_apasat].y1_capat,N[i][nod_apasat].x2_capat,N[i][nod_apasat].y2_capat);
                                        N[i][nod_apasat].x_arc=(N[i][nod_apasat].x1_capat+N[i][nod_apasat].x2_capat)/2;
                                        N[i][nod_apasat].y_arc=(N[i][nod_apasat].y1_capat+N[i][nod_apasat].y2_capat)/2;
                                        x_mijloc_sageata=G[nod_apasat].x+2*r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        y_mijloc_sageata=G[nod_apasat].y+2*r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        aux_x=x_mijloc_sageata-G[nod_apasat].x;
                                        aux_y=y_mijloc_sageata-G[nod_apasat].y;
                                        aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                        aux_x=aux_x/aux_dist;
                                        aux_y=aux_y/aux_dist;
                                        N[i][nod_apasat].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                        N[i][nod_apasat].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                        N[i][nod_apasat].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                        N[i][nod_apasat].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                        line(N[i][nod_apasat].x1_sageata,N[i][nod_apasat].y1_sageata,N[i][nod_apasat].x2_capat,N[i][nod_apasat].y2_capat);
                                        line(N[i][nod_apasat].x2_sageata,N[i][nod_apasat].y2_sageata,N[i][nod_apasat].x2_capat,N[i][nod_apasat].y2_capat);
                                        if(N[i][nod_apasat].cost[0]!='*')
                                        {
                                            outtextxy(N[i][nod_apasat].x_arc,N[i][nod_apasat].y_arc,N[i][nod_apasat].cost);
                                        }
                                    }
                                    else if(N[nod_apasat][i].exista_arc==1 && N[i][nod_apasat].exista_arc==1)
                                    {
                                        N[nod_apasat][i].x1_capat=G[nod_apasat].x+r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].y1_capat=G[nod_apasat].y+r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].x2_capat=G[i].x+r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[nod_apasat][i].y2_capat=G[i].y+r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[nod_apasat].x-G[i].x,2)+pow(G[nod_apasat].y-G[i].y,2));
                                        N[i][nod_apasat].x1_capat=G[i].x+r*(G[nod_apasat].x-G[i].x)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].y1_capat=G[i].y+r*(G[nod_apasat].y-G[i].y)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].x2_capat=G[nod_apasat].x+r*(G[i].x-G[nod_apasat].x)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        N[i][nod_apasat].y2_capat=G[nod_apasat].y+r*(G[i].y-G[nod_apasat].y)/sqrt(pow(G[i].x-G[nod_apasat].x,2)+pow(G[i].y-G[nod_apasat].y,2));
                                        nod_1=nod_apasat;
                                        nod_2=i;
                                        x_mij=(N[nod_1][nod_2].x1_capat+N[nod_1][nod_2].x2_capat)/2;
                                        y_mij=(N[nod_1][nod_2].y1_capat+N[nod_1][nod_2].y2_capat)/2;
                                        aux_x=x_mij-N[nod_1][nod_2].x1_capat;
                                        aux_y=y_mij-N[nod_1][nod_2].y1_capat;
                                        aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                        aux_x=aux_x/aux_dist;
                                        aux_y=aux_y/aux_dist;
                                        x1_mij_arc=x_mij+(2*r/3)*aux_y;
                                        y1_mij_arc=y_mij-(2*r/3)*aux_x;
                                        x2_mij_arc=x_mij-(2*r/3)*aux_y;
                                        y2_mij_arc=y_mij+(2*r/3)*aux_x;
                                        if(nod_1>nod_2)
                                        {
                                            aux=nod_1;
                                            nod_1=nod_2;
                                            nod_2=aux;
                                        }
                                        if(y1_mij_arc<y2_mij_arc)
                                        {
                                            N[nod_1][nod_2].x_arc=x1_mij_arc;
                                            N[nod_1][nod_2].y_arc=y1_mij_arc;
                                            N[nod_2][nod_1].x_arc=x2_mij_arc;
                                            N[nod_2][nod_1].y_arc=y2_mij_arc;
                                            ///incep cu arcul de sus
                                            x_mijloc_sageata=N[nod_1][nod_2].x2_capat+r*(x1_mij_arc-N[nod_1][nod_2].x2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x1_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y1_mij_arc,2));
                                            y_mijloc_sageata=N[nod_1][nod_2].y2_capat+r*(y1_mij_arc-N[nod_1][nod_2].y2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x1_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y1_mij_arc,2));
                                            aux_x=x_mijloc_sageata-N[nod_1][nod_2].x2_capat;
                                            aux_y=y_mijloc_sageata-N[nod_1][nod_2].y2_capat;
                                            aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                            aux_x=aux_x/aux_dist;
                                            aux_y=aux_y/aux_dist;
                                            N[nod_1][nod_2].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                            N[nod_1][nod_2].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                            N[nod_1][nod_2].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                            N[nod_1][nod_2].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                            line(N[nod_1][nod_2].x1_sageata,N[nod_1][nod_2].y1_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                            line(N[nod_1][nod_2].x2_sageata,N[nod_1][nod_2].y2_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                            ///arcul de jos acum
                                            x_mijloc_sageata=N[nod_2][nod_1].x2_capat+r*(x2_mij_arc-N[nod_2][nod_1].x2_capat)/sqrt(pow(x2_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y2_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                            y_mijloc_sageata=N[nod_2][nod_1].y2_capat+r*(y2_mij_arc-N[nod_2][nod_1].y2_capat)/sqrt(pow(x2_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y2_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                            aux_x=x_mijloc_sageata-N[nod_2][nod_1].x2_capat;
                                            aux_y=y_mijloc_sageata-N[nod_2][nod_1].y2_capat;
                                            aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                            aux_x=aux_x/aux_dist;
                                            aux_y=aux_y/aux_dist;
                                            N[nod_2][nod_1].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                            N[nod_2][nod_1].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                            N[nod_2][nod_1].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                            N[nod_2][nod_1].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                            line(N[nod_2][nod_1].x1_sageata,N[nod_2][nod_1].y1_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                            line(N[nod_2][nod_1].x2_sageata,N[nod_2][nod_1].y2_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                        }
                                        else if(y1_mij_arc>=y2_mij_arc)
                                        {
                                            N[nod_1][nod_2].x_arc=x2_mij_arc;
                                            N[nod_1][nod_2].y_arc=y2_mij_arc;
                                            N[nod_2][nod_1].x_arc=x1_mij_arc;
                                            N[nod_2][nod_1].y_arc=y1_mij_arc;
                                            ///incep cu arcul de sus
                                            x_mijloc_sageata=N[nod_1][nod_2].x2_capat+r*(x2_mij_arc-N[nod_1][nod_2].x2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x2_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y2_mij_arc,2));
                                            y_mijloc_sageata=N[nod_1][nod_2].y2_capat+r*(y2_mij_arc-N[nod_1][nod_2].y2_capat)/sqrt(pow(N[nod_1][nod_2].x2_capat-x2_mij_arc,2)+pow(N[nod_1][nod_2].y2_capat-y2_mij_arc,2));
                                            aux_x=x_mijloc_sageata-N[nod_1][nod_2].x2_capat;
                                            aux_y=y_mijloc_sageata-N[nod_1][nod_2].y2_capat;
                                            aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                            aux_x=aux_x/aux_dist;
                                            aux_y=aux_y/aux_dist;
                                            N[nod_1][nod_2].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                            N[nod_1][nod_2].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                            N[nod_1][nod_2].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                            N[nod_1][nod_2].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                            line(N[nod_1][nod_2].x1_sageata,N[nod_1][nod_2].y1_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                            line(N[nod_1][nod_2].x2_sageata,N[nod_1][nod_2].y2_sageata,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                            ///arcul de jos acum
                                            x_mijloc_sageata=N[nod_2][nod_1].x2_capat+r*(x1_mij_arc-N[nod_2][nod_1].x2_capat)/sqrt(pow(x1_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y1_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                            y_mijloc_sageata=N[nod_2][nod_1].y2_capat+r*(y1_mij_arc-N[nod_2][nod_1].y2_capat)/sqrt(pow(x1_mij_arc-N[nod_2][nod_1].x2_capat,2)+pow(y1_mij_arc-N[nod_2][nod_1].y2_capat,2));
                                            aux_x=x_mijloc_sageata-N[nod_2][nod_1].x2_capat;
                                            aux_y=y_mijloc_sageata-N[nod_2][nod_1].y2_capat;
                                            aux_dist=sqrt(aux_x*aux_x+aux_y*aux_y);
                                            aux_x=aux_x/aux_dist;
                                            aux_y=aux_y/aux_dist;
                                            N[nod_2][nod_1].x1_sageata=x_mijloc_sageata+(r/4)*aux_y;
                                            N[nod_2][nod_1].y1_sageata=y_mijloc_sageata-(r/4)*aux_x;
                                            N[nod_2][nod_1].x2_sageata=x_mijloc_sageata-(r/4)*aux_y;
                                            N[nod_2][nod_1].y2_sageata=y_mijloc_sageata+(r/4)*aux_x;
                                            line(N[nod_2][nod_1].x1_sageata,N[nod_2][nod_1].y1_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                            line(N[nod_2][nod_1].x2_sageata,N[nod_2][nod_1].y2_sageata,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                        }
                                        line(N[nod_1][nod_2].x_arc,N[nod_1][nod_2].y_arc,N[nod_1][nod_2].x1_capat,N[nod_1][nod_2].y1_capat);
                                        line(N[nod_1][nod_2].x_arc,N[nod_1][nod_2].y_arc,N[nod_1][nod_2].x2_capat,N[nod_1][nod_2].y2_capat);
                                        line(N[nod_2][nod_1].x_arc,N[nod_2][nod_1].y_arc,N[nod_2][nod_1].x1_capat,N[nod_2][nod_1].y1_capat);
                                        line(N[nod_2][nod_1].x_arc,N[nod_2][nod_1].y_arc,N[nod_2][nod_1].x2_capat,N[nod_2][nod_1].y2_capat);
                                        if(N[nod_apasat][i].cost[0]!='*')
                                        {
                                            outtextxy(N[nod_apasat][i].x_arc,N[nod_apasat][i].y_arc,N[nod_apasat][i].cost);
                                        }
                                        if(N[i][nod_apasat].cost[0]!='*')
                                        {
                                            outtextxy(N[i][nod_apasat].x_arc,N[i][nod_apasat].y_arc,N[i][nod_apasat].cost);
                                        }
                                    }
                                }
                                delay(1);
                                setvisualpage(0);
                            }
                            if(ismouseclick(WM_LBUTTONDOWN))
                            {
                                nodul_este_miscat=0;
                                clearmouseclick(WM_LBUTTONDOWN);
                            }
                        }
                        setactivepage(1);
                        cleardevice();
                        redesenare_graf_curent_orientat();
                        setvisualpage(1);
                        setactivepage(0);
                        cleardevice();
                        redesenare_graf_curent_orientat();
                        delay(1);
                        setvisualpage(0);
                    }
                }
                clearmouseclick(WM_LBUTTONDOWN);
            }
        }
    }
    return 0;
}
