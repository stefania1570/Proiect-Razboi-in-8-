#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <time.h>
#include<fstream>
#include <SFML/Audio.hpp>
#include <stdio.h>
using namespace std;

int stanga,sus,width_tabla=560,height_tabla=560,latura, numar=8,k,window,window2,window_w=800,window_h=560,comp,piesaeliminata,numarpieseeliminate,lin;
int jucator=0,nrpiese1=8,nrpiese2=8;
int nrMutari=50;
bool randComp=false;
bool muzicada=0;
int scorrosu,scorgalben;
int culoare[10]= {CYAN,LIGHTRED,YELLOW,LIGHTBLUE,LIGHTGREEN,LIGHTMAGENTA,LIGHTCYAN,WHITE};
int cul1=culoare[1];
int cul2=culoare[2];
int TablaDeJoc[10][10];
char rnd[200], ch;
FILE *f1= fopen("romana.txt","r");
FILE *f2= fopen("english.txt","r");
FILE *f3= fopen("franceza.txt","r");

sf::Music music1;
sf::Music music2;
sf::Music music3;
sf::Music music4;

char limba[150][150]=
{
    "PLAYER VS COMPUTER", "PLAYER VS PLAYER", "SETTINGS", "HELP", "BACK", "LANGUAGE", "RESOLUTION","MUSIC: ON/OFF","EXIT","COLORS","PLAYER 1 WON!", "PLAYER 2 WON!", "THE SCORE IS EQUAL!", "NEXT MOVE", "RED/YELLOW", "BLUE/GREEN", "MAGENTA/CYAN", "PLAYER 1", "PLAYER 2",
    "JUCATOR VS COMPUTER", "JUCATOR VS JUCATOR", "SETARI", "AJUTOR", "INAPOI","LIMBA", "REZOLUTIE","MUZICA:ON/OFF", "IESIRE","CULORI","JUCATORUL 1 A CASTIGAT!", "JUCATORUL 2 A CASTIGAT!", "SCORUL ESTE EGAL!", "URMATOAREA MUTARE", "ROSU/GALBEN", "ALBAS/VERDE", "MAG/TURCOAZ", "JUCATOR 1", "JUCATOR 2",
    "JOUEUR VS ORDINATEUR", "JOUEUR VS JOUEUR", "REGLAGES GENERAUX","AIDER","ARRIERE","LANGUE","RESOLUTION","LA MUSIQUE:ON/OFF","SORTIR","COULEURS","JOUEUR 1 A GAGNE!", "JOUEUR 2 A GAGNE!", "LE SCOR EST EGAL!", "SUIVANT MOUVEMENT", "ROUGE/JAUNE", "BLEU/VERT", "MAG/TURQOISE", "JOUEUR 1", "JOUEUR 2"
};
int nrLimba=0;
struct butoane
{
    int x1,y1;///starting point
    int x2,y2;///ending point
} pvc,pvp,settings,help,exi,Back,language,resolution,colors,music,exi2,optCuloare1,optCuloare2,optCuloare3,BackHelp;

void scorosu(int nrelim) 
{
    settextstyle(6, HORIZ_DIR,2);
    char sirScor[10];
    setcolor(cul1);
    scorrosu+=nrelim;
    sprintf(sirScor,"%d",scorrosu);
    outtextxy(width_tabla+20,80,sirScor);


}
void scogalben(int nrelim) 
{
    settextstyle(6, HORIZ_DIR,2);
    char sirScor[10];
    setcolor(cul2);
    scorgalben+=nrelim;
    sprintf(sirScor,"%d",scorgalben);
    outtextxy(width_tabla+20,height_tabla-80,sirScor);
}
void calculeazaScor()
{
    if(piesaeliminata)
    {
        {
            if(piesaeliminata==1)


                scogalben(numarpieseeliminate);


            else if(piesaeliminata==2)

                scorosu(numarpieseeliminate);

        }

    }

}
void afiseazaScor()
{
    settextstyle(6, HORIZ_DIR,2);
    char sirScor[10];
    setcolor(cul1);
    sprintf(sirScor,"%d",scorrosu);
    outtextxy(width_tabla+20,80,sirScor);


    setcolor(cul2);
    sprintf(sirScor,"%d",scorgalben);
    outtextxy(width_tabla+20,height_tabla-80,sirScor);
}
int xmijloc, ymijloc;
void deseneazaPiesa(int linia, int coloana, int culoare)
{
    int x1, y1, x2, y2;


    setcolor(culoare);
    setfillstyle(SOLID_FILL,culoare);
    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    xmijloc=(x1+x2)/2;
    ymijloc=(y1+y2)/2;
    circle(xmijloc,ymijloc,20);
    floodfill(xmijloc+1,ymijloc+1,culoare);
}
void stergePiesa(int linia,int coloana)
{
    int x1, y1, x2, y2;

    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    bar3d(x1,y1,x2,y2,0,0); ///bar3d la care al 5lea parametru e 0 pt ca nu vreau sa fie 3d
    ///dar am folosit functia asta pt ca atunci cand deseneaza, face si fill automat

}

bool verificare(int l1,int c1,int l2,int c2) 
{
    if (l1-l2==-1 and(c1-c2==1 or c1-c2==-1))
        return 1;
    else if(l1-l2==1 and (c1-c2==1 or c1-c2==-1))
        return 1;
    return 0;
}

void VerificareScoaterePiesa()
{
    int x,y,linia,coloana,click_dr=false,click_st=false;
    while(!click_dr&& !click_st )
    {
        click_dr=ismouseclick(WM_RBUTTONDOWN);
        if(ismouseclick(WM_LBUTTONDOWN))
            click_st=true;
        if(click_dr==true)
        {
            clearmouseclick(WM_RBUTTONDOWN);
            x=mousex();
            y=mousey();
            linia=(y-sus)/latura+1;
            coloana=(x-stanga)/latura+1;
            if(TablaDeJoc[linia][coloana]==0)
                click_dr=false;
            /*if(jucator!=0)
            {
                if(TablaDeJoc[linia][coloana]==jucator) ///jucatorul advers trebuie sa elimine piesele
                    click_dr=false;
            }*/

            if(TablaDeJoc[linia-1][coloana-1]==0 || TablaDeJoc[linia-1][coloana+1]==0 || TablaDeJoc[linia+1][coloana-1]==0||TablaDeJoc[linia+1][coloana+1]==0)
                click_dr=false;
            if(click_dr==true)///daca a ramas true sterge piesa
            {
                stergePiesa(linia,coloana);
                piesaeliminata=TablaDeJoc[linia][coloana];
                if(piesaeliminata==1)
                    nrpiese1--;
                else if(piesaeliminata==2)
                    nrpiese2--;
                TablaDeJoc[linia][coloana]=0;
                numarpieseeliminate++;

                calculeazaScor();
                piesaeliminata=0;
                numarpieseeliminate=0;
            }

        }
        click_dr=false; ///ca sa nu iasa din while pana nu intalneste click stanga

    }



}

void mutarePiesa(int &jucator) 
{
    ///variabila jucator se va schimba in functie de randul cui este

    int linia1,coloana1,linia2,coloana2;
    int x1, y1, x2, y2;
    int click=false;
    int maxx=getmaxx(),maxy=getmaxy();
    do
    {

        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            click=true;
            clearmouseclick(WM_LBUTTONDOWN);
            x1=mousex();
            y1=mousey();
            linia1=(y1-sus)/latura+1; ///linia si coloana de la piesa pe care vrem sa o mutam
            coloana1=(x1-stanga)/latura+1;
        }

        if(TablaDeJoc[linia1][coloana1]==0)
            click=false;
        if(jucator!=0)
            if(TablaDeJoc[linia1][coloana1]!=jucator)
                click=false;
        if(TablaDeJoc[linia1-1][coloana1-1]!=0 && TablaDeJoc[linia1-1][coloana1+1]!=0 && TablaDeJoc[linia1+1][coloana1-1]!=0&&TablaDeJoc[linia1+1][coloana1+1]!=0)
            click=false;
        if(x1>width_tabla)
            click=false;
    }
    while (!click);

    if(jucator==0)///inseamna ca e prima mutare, deci stabilim jucatorul care porneste
        if(linia1==1||linia1==2)
            jucator=1;
        else if (linia1==7 || linia1==8)
            jucator=2;


    if(TablaDeJoc[linia1+1][coloana1+1]==0  and (linia1+1)<=8 and (coloana1+1)<=8) ///evidentiere pozitii posibile de a muta
    {
        deseneazaPiesa(1+linia1,1+coloana1,LIGHTGRAY);
        TablaDeJoc[1+linia1][1+coloana1]=-5;
    }
    if(TablaDeJoc[linia1+1][coloana1-1]==0 and (linia1+1)<=8 and (coloana1-1)<=8)
    {
        TablaDeJoc[linia1+1][coloana1-1]=-5;
        deseneazaPiesa(1+linia1,coloana1-1,LIGHTGRAY);
    }
    if(TablaDeJoc[linia1-1][coloana1-1]==0 and (linia1-1)<=8 and (coloana1-1)<=8)
    {
        deseneazaPiesa(linia1-1,coloana1-1,LIGHTGRAY);
        TablaDeJoc[linia1-1][coloana1-1]=-5;
    }
    if(TablaDeJoc[linia1-1][coloana1+1]==0 and (linia1-1)<=8 and (coloana1+1)<=8)
    {
        deseneazaPiesa(linia1-1,coloana1+1,LIGHTGRAY);
        TablaDeJoc[linia1-1][coloana1+1]=-5;
    }

    click=false;
    do
    {

        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {

            clearmouseclick(WM_LBUTTONDOWN);
            x2=mousex();
            y2=mousey();
            linia2=(y2-sus)/latura+1;
            coloana2=(x2-stanga)/latura+1;

            if((TablaDeJoc[linia2][coloana2]==0 or TablaDeJoc[linia2][coloana2]==-5) && verificare(linia1,coloana1,linia2,coloana2))
            {
                if(muzicada)
                {
                    music4.setVolume(25);
                    music4.play();
                }
                TablaDeJoc[linia2][coloana2]=jucator;
                if(jucator==1)
                    deseneazaPiesa(linia2,coloana2,cul1);
                else if(jucator==2)
                    deseneazaPiesa(linia2,coloana2,cul2);
                if(TablaDeJoc[linia1+1][coloana1-1]==-5)
                {
                    stergePiesa(linia1+1,coloana1-1);
                    TablaDeJoc[linia1+1][coloana1-1]=0;
                }
                if(TablaDeJoc[linia1-1][coloana1-1]==-5)
                {
                    stergePiesa(linia1-1,coloana1-1);
                    TablaDeJoc[linia1-1][coloana1-1]=0;
                }
                if(TablaDeJoc[linia1-1][coloana1+1]==-5)
                {
                    stergePiesa(linia1-1,coloana1+1);
                    TablaDeJoc[linia1-1][coloana1+1]=0;
                }
                if(TablaDeJoc[linia1+1][coloana1+1]==-5)
                {
                    stergePiesa(1+linia1,1+coloana1);
                    TablaDeJoc[linia1+1][coloana1+1]=0;
                }
                stergePiesa(linia1,coloana1);
                TablaDeJoc[linia1][coloana1]=0;
                click=true;
            }
        }
        if(coloana2>=9)
            click=false;
    }
    while (!click);

    if(jucator==1)  ///ca sa se schimbe randul jucatorilor
    {
        if(comp==0) ///inseamna ca nu am ales modul player vs computer
            jucator=2;
        else
            comp=2;

        setcolor(cul2);
        setfillstyle(SOLID_FILL,cul2);
        circle(width_tabla+110,300,20);
        floodfill(width_tabla+111,301,cul2);

    }
    else if(jucator==2)
    {
        if(comp==0)
            jucator=1;
        else
            comp=1;

        setcolor(cul1);
        setfillstyle(SOLID_FILL,cul1);
        circle(width_tabla+110,300,20);
        floodfill(width_tabla+111,301,cul1);


    }
}

void desen()
{
    int i,j;
    latura=width_tabla/numar;
    sus=0; ///coordonata y de unde incepe tabla
    stanga=0; ///coordonata x de unde incepe tabla
    setbkcolor(COLOR(204, 204, 179)); ///CULOAREA FUNDALULUI
    clearviewport(); ///ca sa stearga fundalul de la setari si sa intre in joc

    for (i=1; i<=numar; i++)
        for (j=1; j<=numar; j++)
        {
            if((i+j)%2==1)
                setcolor(BLACK);
            else
                setcolor(WHITE);
            rectangle(stanga+latura*(i-1),sus+latura*(j-1),stanga+latura*i,sus+latura*j);

            if((i+j)%2==1)
            {

                setfillstyle(SOLID_FILL, BLACK);
                floodfill(stanga+latura*(i-1)+1,sus+latura*(j-1)+1,BLACK);

            }
            else
            {
                setfillstyle(SOLID_FILL, WHITE);
                floodfill(stanga+latura*(i-1)+1,sus+latura*(j-1)+1,WHITE);
            }
        }


}
void deseneazaPieseleInitiale() 
{

    for (int i=1; i<=numar; i++)
        if (i % 2 == 0)
        {
            TablaDeJoc[1][i]=1;
            deseneazaPiesa(1,i,cul1);

            TablaDeJoc[7][i]=2;
            deseneazaPiesa(7,i,cul2);
        }
        else
        {
            TablaDeJoc[numar][i]=2;
            deseneazaPiesa(numar,i,cul2);

            TablaDeJoc[2][i]=1;
            deseneazaPiesa(2,i,cul1);

        }
}

void joacaPVP()
{
    desen();
    afiseazaScor();
    setcolor(BLACK);
    settextstyle(3, HORIZ_DIR,1);
    int maxx=getmaxx(),maxy=getmaxy();
    outtextxy(width_tabla+35,maxy/2-30,limba[nrLimba+13]);        ///afiseaza "Next move:"
    setcolor(cul1);
    outtextxy(width_tabla+90,60,limba[nrLimba+17]);      ///afiseaza "PLAYER 1"
    setcolor(cul2);
    outtextxy(width_tabla+90,window_h-90,limba[nrLimba+18]);     ///afiseaza "PLAYER 2"
    deseneazaPieseleInitiale();
    int i=1;///contor mutari
    do
    {

        mutarePiesa(jucator);
        if(i>=9) ///Primele 8 mutari nu putem scoate piese
            VerificareScoaterePiesa();
        nrMutari--;
        i++;
        if(nrpiese1==0||nrpiese2==0)   ///Au fost capturate toate piesele cuiva
            nrMutari=0;

    }
    while (nrMutari>0);
    ///DUPA CE JOCUL S-A TERMINAT  
    if(nrMutari==0)
        if(scorrosu>scorgalben)
        {
            delay(200);
            cleardevice();
            delay(200);
            if(muzicada)
            {
                music1.stop();
                music2.setVolume(25);
                music2.play();
            }
            setcolor(15);
            setbkcolor(cul1);
            setfillstyle(SOLID_FILL,cul1);
            floodfill(1,1,cul1);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR,3);
            outtextxy(maxx/2-textwidth(limba[nrLimba+10])/2,maxy/2-textheight(limba[nrLimba+10])/2,limba[nrLimba+10]);
            delay(5000);
            exit(0);

        }
        else if(scorrosu<scorgalben)
        {
            delay(200);
            cleardevice();
            delay(200);
            if(muzicada)
            {
                music1.stop();
                music2.setVolume(25);
                music2.play();
            }
            setfillstyle(SOLID_FILL,cul2);
            floodfill(1,1,cul2);
            setcolor(15);
            setbkcolor(cul2);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR,3);
            outtextxy(maxx/2-textwidth(limba[nrLimba+11])/2,maxy/2-textheight(limba[nrLimba+11])/2,limba[nrLimba+11]);
            delay(5000);
            exit(0);

        }
        else if(scorrosu==scorgalben)      ///cand scorul e egal

        {

            delay(200);
            cleardevice();
            delay(200);
            if(muzicada)
            {
                music1.stop();
                music3.setVolume(25);
                music3.play();
            }
            setfillstyle(SOLID_FILL,WHITE);
            floodfill(1,1,WHITE);
            setbkcolor(WHITE);
            setcolor(BLACK);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR,3);
            outtextxy(maxx/2-textwidth(limba[nrLimba+12])/2,maxy/2-textheight(limba[nrLimba+12])/2,limba[nrLimba+12]);
            delay(5000);
            exit(0);
        }



}

int linieComp1,coloanaComp1,linieComp2,coloanaComp2;
bool verificarePozLibera(int linieComp2, int coloanaComp2) 
{

    if(linieComp2==0 && coloanaComp2==0) ///inseamna ca nu a intrat inca in if cu pozrand
        return false;
    else if(TablaDeJoc[linieComp2][coloanaComp2]!=0)
        return false;
    return true;

}

void CompAlegeMutarea(int &linieComp1,int &coloanaComp1,int &linieComp2,int &coloanaComp2)
{
    int ok=0,pozrand;
    srand(time(NULL));

    while(ok==0)
    {

        linieComp1=rand()%8+1;
        coloanaComp1=rand()%8+1;
        ///verificam daca s-a ales piesa corecta: sa apartina computerului si sa aiba minim o pozitie libera
        if(TablaDeJoc[linieComp1][coloanaComp1]==comp)
            if((verificarePozLibera(linieComp1-1, coloanaComp1-1)==true) ||(verificarePozLibera(linieComp1-1,coloanaComp1+1)==true ) || (verificarePozLibera(linieComp1+1,coloanaComp1-1)==true)||(verificarePozLibera(linieComp1+1,coloanaComp1+1)==true))
                ok=1;
    }

    while(verificarePozLibera(linieComp2,coloanaComp2)!=true)
    {
        pozrand=rand()%4;

        if(pozrand==0)                                           ///mutare in stanga sus
            linieComp2=linieComp1-1,coloanaComp2=coloanaComp1-1;
        else if(pozrand==1)                                      ///mutare in dreapta sus
            linieComp2=linieComp1-1,coloanaComp2=coloanaComp1+1;
        else if(pozrand==2)                                      ///mutare in stanga jos
            linieComp2=linieComp1+1,coloanaComp2=coloanaComp1-1;
        else if(pozrand==3)                                      ///mutare in dreapta jos
            linieComp2=linieComp1+1,coloanaComp2=coloanaComp1+1;

    }




}
bool ok;
void compalegemuatarebuna(int &lin1,int &col1,int &lin2,int &col2) 
{
    {
        ok=0;
        int i,j;
        for(i=1; i<=8; i++)
            for(j=1; j<=8; j++)
            {
                //cout<<i<<" "<<j<<endl;;

                if(TablaDeJoc[i][j]!=comp and TablaDeJoc[i][j]!=0 and ok==0) ///caut piesa adversara
                {
                    cout<<endl<<i<<" "<<j;
                    if(TablaDeJoc[i-1][j+1]!=0 and TablaDeJoc[i+1][j+1]!=0 and TablaDeJoc[i+1][j-1]!=0 and ok==0 and TablaDeJoc[i-1][j-1]==0) /// stnga sus liber
                    {
                        if(TablaDeJoc[i-2][j-2]==comp)
                        {
                            lin1=i-2;
                            col1=j-2;
                            lin2=i-1;
                            col2=j-1;
                            ok=1;
                        }
                        if(TablaDeJoc[i-2][j]==comp)
                        {
                            lin1=i-2;
                            col1=j;
                            lin2=i-1;
                            col2=j-1;
                            ok=1;
                        }
                        if(TablaDeJoc[i][j-2]==comp)
                        {
                            lin1=i;
                            col1=j-2;
                            lin2=i-1;
                            col2=j-1;
                            ok=1;
                        }

                    }
                    if(TablaDeJoc[i-1][j-1]!=0 and TablaDeJoc[i+1][j-1]!=0 and TablaDeJoc[i+1][j+1]!=0  and ok==0 )
                    {
                        if(TablaDeJoc[i-1][j+1]==0)
                        {
                            if(TablaDeJoc[i-2][j+2]==comp)
                            {
                                lin1=i-2;
                                col2=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;
                                cout<<2;
                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;
                            }
                        }

                    }
                    if(TablaDeJoc[i-1][j-1]!=0 and TablaDeJoc[i-1][j+1]!=0 and TablaDeJoc[i+1][j-1]!=0  and ok==0)
                    {

                        if(TablaDeJoc[i+1][j+1]==0)
                        {
                            if(TablaDeJoc[i+2][j+2]==comp)
                            {
                                lin1=i+2;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                                cout<<3;
                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                {
                                    lin1=i;
                                    col1=j+2;
                                    lin2=i+1;
                                    col2=j+1;
                                    ok=1;
                                    cout<<3;
                                }

                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                {
                                    lin1=i+2;
                                    col1=j;
                                    lin2=i+1;
                                    col2=j+1;
                                    ok=1;
                                    cout<<3;
                                }

                            }

                        }
                    }
                    if(TablaDeJoc[i-1][j-1]!=0 and TablaDeJoc[i+1][j+1]!=0 and TablaDeJoc[i-1][j+1]!=0 and ok==0)
                    {
                        if(TablaDeJoc[i+1][j-1]==0)
                        {
                            if(TablaDeJoc[i+2][j-2]==comp)
                            {
                                lin1=i+2;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                                cout<<4;
                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                                cout<<4;
                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                                cout<<4;
                            }

                        }
                    }
                }
            }
        /// terminare cazuri cu 3
        ///evadare
        for(i=1; i<=8; i++)
            for(j=1; j<=8; j++)
            {
                if(TablaDeJoc[i][j]==comp and ok==0)
                {
                    if(TablaDeJoc[i-1][j+1]!=0 and TablaDeJoc[i-1][j-1]!=0 and TablaDeJoc[i+1][j+1]!=0 and TablaDeJoc[i+1][j-1]==0)
                    {
                        if(TablaDeJoc[i-1][j+1]!=8 and TablaDeJoc[i-1][j-1]!=8 and TablaDeJoc[i+1][j+1]!=8 and TablaDeJoc[i+1][j-1]==0)
                        {
                            lin1=i;
                            col1=j;
                            lin2=i+1;
                            col2=j-1;
                            ok=1;
                        }
                    }
                    if(TablaDeJoc[i+1][j-1]!=0 and TablaDeJoc[i-1][j-1]!=0 and TablaDeJoc[i+1][j+1]!=0 and TablaDeJoc[i-1][j+1]==0)
                    {
                        if(TablaDeJoc[i+1][j-1]!=8 and TablaDeJoc[i-1][j-1]!=8 and TablaDeJoc[i+1][j+1]!=8 and TablaDeJoc[i-1][j+1]==0)
                        {
                            lin1=i;
                            col1=j;
                            lin2=i-1;
                            col2=j+1;
                            ok=1;
                        }
                    }
                    if(TablaDeJoc[i+1][j-1]!=0 and TablaDeJoc[i-1][j+1]!=0 and TablaDeJoc[i+1][j+1]!=0 and TablaDeJoc[i-1][j-1]==0)
                    {
                        if(TablaDeJoc[i+1][j-1]!=8 and TablaDeJoc[i-1][j+1]!=8 and TablaDeJoc[i+1][j+1]!=8 and TablaDeJoc[i-1][j-1]==0)
                        {
                            lin1=i;
                            col1=j;
                            lin2=i-1;
                            col2=j-1;
                            ok=1;
                        }
                    }
                    if(TablaDeJoc[i+1][j-1]!=0 and TablaDeJoc[i-1][j-1]!=0 and TablaDeJoc[i-1][j+1]!=0 and TablaDeJoc[i+1][j+1]==0)
                    {
                        if(TablaDeJoc[i+1][j-1]!=8 and TablaDeJoc[i-1][j-1]!=8 and TablaDeJoc[i-1][j+1]!=8 and TablaDeJoc[i+1][j+1]==0)
                        {
                            lin1=i;
                            col1=j;
                            lin2=i+1;
                            col2=j+1;
                            ok=1;
                        }
                    }
                }

            }
        ///cazuri incoltite cu 2

        for(i=1; i<=8; i++)
            for(j=1; j<=8; j++)
            {
                if(TablaDeJoc[i][j]!=comp and TablaDeJoc[i][j]!=0 and ok==0)
                {
                    if(TablaDeJoc[i-1][j-1]!=0 and TablaDeJoc[i+1][j+1]!=0 and ok==0)
                    {
                        if(TablaDeJoc[i-1][j+1]==0)
                        {
                            if(TablaDeJoc[i-2][j+2]==comp)
                            {
                                lin1=i-2;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;
                                cout<<4;

                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;
                                cout<<4;

                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;
                                cout<<4;

                            }
                        }
                        if(TablaDeJoc[i+1][j-1]==0)
                        {
                            if(TablaDeJoc[i+2][j-2]==comp)
                            {
                                lin1=i+2;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;

                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;

                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;

                            }
                        }
                    }
                    if(TablaDeJoc[i-1][j-1]!=0 and TablaDeJoc[i+1][j-1]!=0 and ok==0)
                    {
                        if(TablaDeJoc[i-1][j+1]==0)
                        {
                            if(TablaDeJoc[i-2][j+2]==comp)
                            {
                                lin1=i-2;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;

                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;

                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;

                            }
                        }
                        if(TablaDeJoc[i+1][j+1]==0)
                        {
                            if(TablaDeJoc[i+2][j+2]==comp)
                            {
                                lin1=i+2;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                        }
                    }
                    if(TablaDeJoc[i-1][j-1]!=0 and TablaDeJoc[i-1][j+1]!=0 and ok==0)
                    {
                        if(TablaDeJoc[i+1][j-1]==0)
                        {
                            if(TablaDeJoc[i+2][j-2]==comp)
                            {
                                lin1=i+2;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;

                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;

                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;

                            }
                        }
                        if(TablaDeJoc[i+1][j+1]==0)
                        {
                            if(TablaDeJoc[i+2][j+2]==comp)
                            {
                                lin1=i+2;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                        }
                    }
                    if(TablaDeJoc[i-1][j+1]!=0 and TablaDeJoc[i+1][j+1]!=0 and ok==0)
                    {
                        if(TablaDeJoc[i+1][j-1]==0)
                        {
                            if(TablaDeJoc[i+2][j-2]==comp)
                            {
                                lin1=i+2;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }
                        }
                        if(TablaDeJoc[i-1][j-1]==0)
                        {
                            if(TablaDeJoc[i-2][j-2]==comp)
                            {
                                lin1=i-2;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;


                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;


                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;


                            }
                        }
                    }
                    if(TablaDeJoc[i-1][j+1]!=0 and TablaDeJoc[i+1][j-1]!=0 and ok==0)
                    {
                        if(TablaDeJoc[i-1][j-1]==0)
                        {
                            if(TablaDeJoc[i-2][j-2]==comp)
                            {
                                lin1=i-2;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;


                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;


                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;


                            }
                        }
                        if(TablaDeJoc[i+1][j+1]==0)
                        {
                            if(TablaDeJoc[i+2][j+2]==comp)
                            {
                                lin1=i+2;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                        }
                    }
                    if(TablaDeJoc[i+1][j-1]!=0 and TablaDeJoc[i+1][j+1]!=0 and ok==0)
                    {
                        if(TablaDeJoc[i-1][j-1]==0)
                        {
                            if(TablaDeJoc[i-2][j-2]==comp)
                            {
                                lin1=i-2;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;


                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;


                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;


                            }
                        }
                        if(TablaDeJoc[i-1][j+1]==0)
                        {
                            if(TablaDeJoc[i-2][j+2]==comp)
                            {
                                lin1=i-2;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;

                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;

                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;

                            }
                        }
                    }
                }
            }
        /// cazul in care o piesa este incoltita doar de o piesa
        for(i=1; i<=8; i++)
            for(j=1; j<=8; j++)
            {
                if(TablaDeJoc[i][j]!=comp and TablaDeJoc[i][j]!=0 and ok==0)
                {
                    if(TablaDeJoc[i-1][j-1]!=0 and ok==0) /// stanga sus+mijloc
                    {
                        if(TablaDeJoc[i-1][j+1]==0)
                        {
                            if(TablaDeJoc[i-2][j+2]==comp )
                            {
                                lin1=i-2;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;


                            }
                            if(TablaDeJoc[i-2][j]==comp )
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;


                            }
                            if(TablaDeJoc[i][j+2]==comp )
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;


                            }

                        }
                        if(TablaDeJoc[i+1][j+1]==0)
                        {
                            if(TablaDeJoc[i+2][j+2]==comp)
                            {
                                lin1=i+2;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }

                        }
                        if(TablaDeJoc[i+1][j-1]==0)
                        {
                            if(TablaDeJoc[i+2][j-2]==comp)
                            {
                                lin1=i+2;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }

                        }
                    }
                    if(TablaDeJoc[i-1][j+1]!=0 and ok==0) ///dreapta sus+mij
                    {
                        if(TablaDeJoc[i+1][j+1]==0)
                        {
                            if(TablaDeJoc[i+2][j+2]==comp )
                            {
                                lin1=i+2;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i][j+2]==comp )
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i+2][j]==comp )
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                        }
                        if(TablaDeJoc[i+1][j-1]==0)
                        {
                            if(TablaDeJoc[i+2][j-2]==comp)
                            {
                                lin1=i+2;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }
                        }
                        if(TablaDeJoc[i-1][j-1]==0)
                        {
                            if(TablaDeJoc[i-2][j-2]==comp)
                            {
                                lin1=i-2;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;

                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;

                            }
                            if(TablaDeJoc[i-2][j-2]==comp)
                            {
                                lin1=i-2;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;

                            }
                        }
                    }
                    if(TablaDeJoc[i+1][j-1]!=0 and ok==0) ///stanga jos+mij
                    {
                        if(TablaDeJoc[i-1][j-1]==0)
                        {
                            if(TablaDeJoc[i-2][j-2]==comp)
                            {
                                lin1=i-2;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;

                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;

                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;

                            }
                        }
                        if(TablaDeJoc[i-1][j+1]==0)
                        {
                            if(TablaDeJoc[i-2][j+2]==comp)
                            {
                                lin1=i-2;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;


                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;


                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;


                            }
                        }
                        if(TablaDeJoc[i+1][j+1]==0)
                        {
                            if(TablaDeJoc[i+2][j+2]==comp)
                            {
                                lin1=i+2;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j+1;
                                ok=1;
                            }
                        }
                    }
                    if(TablaDeJoc[i+1][j+1]!=0 and ok==0) ///dreapta joc+mij
                    {
                        if(TablaDeJoc[i-1][j-1]==0)
                        {
                            if(TablaDeJoc[i-2][j-2]==comp)
                            {
                                lin1=i-2;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;

                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;

                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j-1;
                                ok=1;

                            }

                        }
                        if(TablaDeJoc[i-1][j+1]==0)
                        {
                            if(TablaDeJoc[i-2][j+2]==comp)
                            {
                                lin1=i-2;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;


                            }
                            if(TablaDeJoc[i-2][j]==comp)
                            {
                                lin1=i-2;
                                col1=j;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;


                            }
                            if(TablaDeJoc[i][j+2]==comp)
                            {
                                lin1=i;
                                col1=j+2;
                                lin2=i-1;
                                col2=j+1;
                                ok=1;


                            }
                        }
                        if(TablaDeJoc[i+1][j-1]==0)
                        {
                            if(TablaDeJoc[i+2][j-2]==comp)
                            {
                                lin1=i+2;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }
                            if(TablaDeJoc[i][j-2]==comp)
                            {
                                lin1=i;
                                col1=j-2;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }
                            if(TablaDeJoc[i+2][j]==comp)
                            {
                                lin1=i+2;
                                col1=j;
                                lin2=i+1;
                                col2=j-1;
                                ok=1;
                            }



                        }






                    }
                }
            }
///daca este incoltita de 3 piese si un colt liber se elibereaza

        cout<<ok;
        cout<<comp;
    }
}
void CompStergePiesele()
{
    for(int i=1; i<=8; i++)
        for(int j=1; j<=8; j++)
            if(TablaDeJoc[i][j]!=comp && TablaDeJoc[i][j]!=0)
            {
                if(TablaDeJoc[i-1][j-1]!=0 && TablaDeJoc[i-1][j+1]!=0 && TablaDeJoc[i+1][j-1]!=0&&TablaDeJoc[i+1][j+1]!=0)
                {
                    stergePiesa(i,j);
                    piesaeliminata=TablaDeJoc[i][j];
                    TablaDeJoc[i][j]=0;
                    numarpieseeliminate++;
                    if(piesaeliminata==1)
                        nrpiese1--;
                    else if(piesaeliminata==2)
                        nrpiese2--;

                    calculeazaScor();
                    piesaeliminata=0;
                    numarpieseeliminate=0;
                }



            }

}
void joacaPVC()
{
    desen();
    int maxx=getmaxx(),maxy=getmaxy();
    afiseazaScor();
    setcolor(BLACK);
    settextstyle(3, HORIZ_DIR,1);
    int i=1;///Contorizeaza mutarile
    outtextxy(width_tabla+35,maxy/2-30,limba[nrLimba+13]);        ///afiseaza "Next move:"
    setcolor(cul1);
    outtextxy(width_tabla+90,60,limba[nrLimba+17]);      ///afiseaza "PLAYER 1"
    setcolor(cul2);
    outtextxy(width_tabla+90,window_h-90,limba[nrLimba+18]);     ///afiseaza "PLAYER 2"
    deseneazaPieseleInitiale();
    comp=3;                       ///ceva diferit de 0-INSEAMNA CA AM INCEPUT MODUL PVC
    mutarePiesa(jucator);        ///ca sa stabilim cu care piese va juca playerul
    randComp=true;              ///pt ca mai sus a mutat jucatorul

    while (nrMutari-1>=0) ///-1 pt ca am mutat deja o piesa inainte de while
    {
        if(randComp==false) ///daca este randul jucatorului ales (adica randul omului)
        {
            if(jucator==1)
            {
                setcolor(cul1);
                setfillstyle(SOLID_FILL,cul1);
                circle(width_tabla+110,300,20);
                floodfill(width_tabla+111,301,cul1);
            }
            else
            {
                setcolor(cul2);
                setfillstyle(SOLID_FILL,cul2);
                circle(width_tabla+110,300,20);
                floodfill(width_tabla+111,301,cul2);
            }
            if(i>=9)
                VerificareScoaterePiesa();
            mutarePiesa(jucator);

            nrMutari--;
            randComp=true;
            i++;
        }

        else if(randComp==true)
        {
            if(comp==1)
            {
                setcolor(cul1);
                setfillstyle(SOLID_FILL,cul1);
                circle(width_tabla+110,300,20);
                floodfill(width_tabla+111,301,cul1);
            }
            else
            {
                setcolor(cul2);
                setfillstyle(SOLID_FILL,cul2);
                circle(width_tabla+110,300,20);
                floodfill(width_tabla+111,301,cul2);
            }

            delay(200);

            delay(200);
            compalegemuatarebuna(linieComp1,coloanaComp1,linieComp2,coloanaComp2);
            if(ok==0)
                CompAlegeMutarea(linieComp1,coloanaComp1, linieComp2, coloanaComp2);
            stergePiesa(linieComp1,coloanaComp1);
            TablaDeJoc[linieComp1][coloanaComp1]=0;
            if(muzicada)
            {
                music4.setVolume(25);
                music4.play();
            }
            if(comp==1)
                deseneazaPiesa(linieComp2,coloanaComp2,cul1);
            else
                deseneazaPiesa(linieComp2,coloanaComp2,cul2);
            i++;
            TablaDeJoc[linieComp2][coloanaComp2]=comp;
            if(i>=9)
                CompStergePiesele();
            nrMutari--;
            linieComp1=0;
            coloanaComp1=0;
            linieComp2=0;
            coloanaComp2=0;
            randComp=false;


        }
    }
    ///DUPA CE JOCUL S-A TERMINAT
    if(nrMutari==0)
        if(scorrosu>scorgalben)
        {
            delay(200);
            cleardevice();
            delay(200);
            if(muzicada)
            {
                music1.stop();
                music2.setVolume(25);
                music2.play();
            }
            setcolor(15);
            setbkcolor(cul1);
            setfillstyle(SOLID_FILL,cul1);
            floodfill(1,1,cul1);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR,3);
            outtextxy(maxx/2-textwidth(limba[nrLimba+10])/2,maxy/2-textheight(limba[nrLimba+10])/2,limba[nrLimba+10]);
            delay(5000);
            exit(0);

        }
        else if(scorrosu<scorgalben)
        {
            delay(200);
            cleardevice();
            delay(200);
            if(muzicada)
            {
                music1.stop();
                music2.setVolume(25);
                music2.play();
            }
            setfillstyle(SOLID_FILL,cul2);
            floodfill(1,1,cul2);
            setcolor(15);
            setbkcolor(cul2);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR,3);
            outtextxy(maxx/2-textwidth(limba[nrLimba+11])/2,maxy/2-textheight(limba[nrLimba+11])/2,limba[nrLimba+11]);
            delay(5000);
            exit(0);

        }
        else if(scorrosu==scorgalben)      ///cand scorul e egal

        {

            delay(200);
            cleardevice();
            delay(200);
            if(muzicada)
            {
                music1.stop();
                music3.setVolume(25);
                music3.play();
            }
            setfillstyle(SOLID_FILL,WHITE);
            floodfill(1,1,WHITE);
            setbkcolor(WHITE);
            setcolor(BLACK);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR,3);
            outtextxy(maxx/2-textwidth(limba[nrLimba+12])/2,maxy/2-textheight(limba[nrLimba+12])/2,limba[nrLimba+12]);
            delay(5000);
            exit(0);
        }
}
void stareMouse (int x1, int y1,int x2, int y2,int color1,int colorHover)
{
    if(mousex()>x1 && mousex()<x2 && mousey()>y1 && mousey()<y2 )
    {
        setcolor(colorHover);
    }
    else
    {
        setcolor(color1);
    }
}
void butoaneMeniu() 
{
    int maxx=getmaxx(),maxy=getmaxy();
    ///TITLU
    setbkcolor(DARKGRAY);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,8);
    outtextxy(maxx/2-textwidth("RAZBOI IN 8")/2,30,"RAZBOI IN 8");

    ///BUTOANE
    setbkcolor(DARKGRAY);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,DARKGRAY);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR,3);
    floodfill(0,0,DARKGRAY); ///coloreaza background ul

    pvc.x1=maxx/2-textwidth(limba[nrLimba])/2;
    pvc.y1=maxy/3-23;
    pvc.x2=maxx/2+textwidth(limba[nrLimba])/2;
    pvc.y2=maxy/3;

    pvp.x1=maxx/2-textwidth(limba[nrLimba+1])/2;
    pvp.y1=maxy/3+13;
    pvp.x2=maxx/2+textwidth(limba[nrLimba+1])/2;
    pvp.y2=maxy/3+13+23;

    settings.x1=maxx/2-textwidth(limba[nrLimba+2])/2;
    settings.y1=maxy/3+49;
    settings.x2=maxx/2+textwidth(limba[nrLimba+2])/2;
    settings.y2=maxy/3+72;

    help.x1=maxx/2-textwidth(limba[nrLimba+3])/2;
    help.y1=maxy/3+85;
    help.x2=maxx/2+textwidth(limba[nrLimba+3])/2;
    help.y2=maxy/3+108;


    exi.x1=maxx/2-textwidth(limba[nrLimba+8])/2;
    exi.y1=maxy/3+121;
    exi.x2=maxx/2+textwidth(limba[nrLimba+8])/2;
    exi.y2=maxy/3+144;

}
void butoaneMeniuHover() 
{
    stareMouse(pvc.x1,pvc.y1,pvc.x2,pvc.y2,BLACK,RED);
    outtextxy(pvc.x1,pvc.y1,limba[nrLimba]);
    rectangle(pvc.x1,pvc.y1,pvc.x2,pvc.y2);

    stareMouse(pvp.x1,pvp.y1,pvp.x2,pvp.y2,BLACK,RED);
    outtextxy(pvp.x1,pvp.y1,limba[nrLimba+1]);
    rectangle(pvp.x1,pvp.y1,pvp.x2,pvp.y2);

    stareMouse(settings.x1,settings.y1,settings.x2,settings.y2,BLACK,RED);
    outtextxy(settings.x1,settings.y1,limba[nrLimba+2]);
    rectangle(settings.x1,settings.y1,settings.x2,settings.y2);

    stareMouse(help.x1,help.y1,help.x2,help.y2,BLACK,RED);
    outtextxy(help.x1,help.y1,limba[nrLimba+3]);
    rectangle(help.x1,help.y1,help.x2,help.y2);

    stareMouse(exi.x1,exi.y1,exi.x2,exi.y2,BLACK,RED);
    outtextxy(exi.x1,exi.y1,limba[nrLimba+8]);
    rectangle(exi.x1,exi.y1,exi.x2,exi.y2);

}
void Pornestemuzica() 
{
    if(muzicada)
    {
        music1.setLoop(true);
        music1.setVolume(25);
        music1.play();

    }
    else
        music1.stop();
}
void meniu();
void PaginaDeSetari()
{
    cleardevice();

    int mx,my,maxx=getmaxx(),maxy=getmaxy();
    setbkcolor(DARKGRAY);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,DARKGRAY);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR,2);///textheight=20
    floodfill(1,1,DARKGRAY);

    Back.x1=maxx/22;
    Back.y1=maxy/3-20;
    Back.x2=maxx/22+textwidth(limba[nrLimba+4]);
    Back.y2=maxy/3;
    outtextxy(Back.x1,Back.y1,limba[nrLimba+4]);
    rectangle(Back.x1,Back.y1,Back.x2,Back.y2);

    language.x1=maxx/22;
    language.y1=maxy/3+20;
    language.x2=maxx/22+textwidth(limba[nrLimba+5]);
    language.y2=maxy/3+40;
    outtextxy(language.x1,language.y1,limba[nrLimba+5]);
    rectangle(language.x1,language.y1,language.x2,language.y2);

    resolution.x1=maxx/22;
    resolution.y1=maxy/3+60;
    resolution.x2=maxx/22+textwidth(limba[nrLimba+6]);
    resolution.y2=maxy/3+80;
    outtextxy(resolution.x1,resolution.y1,limba[nrLimba+6]);
    rectangle(resolution.x1,resolution.y1,resolution.x2,resolution.y2);

    colors.x1=maxx/22;
    colors.y1=maxy/3+100;
    colors.x2=maxx/22+textwidth(limba[nrLimba+9]);
    colors.y2=maxy/3+120;
    outtextxy(colors.x1,colors.y1,limba[nrLimba+9]);
    rectangle(colors.x1,colors.y1,colors.x2,colors.y2);

    optCuloare1.x1=colors.x2+40;
    optCuloare1.x2=colors.x2+60+textwidth("/")+20;
    optCuloare1.y1=optCuloare2.y1=optCuloare3.y1=colors.y1;
    optCuloare1.y2=optCuloare2.y2=optCuloare3.y2=colors.y2;
    optCuloare2.x1=optCuloare1.x2+50;
    optCuloare2.x2=optCuloare2.x1+20+textwidth("/")+20;
    optCuloare3.x1=optCuloare2.x2+50;
    optCuloare3.x2=optCuloare3.x1+20+textwidth("/")+20;

    setcolor(LIGHTRED);
    setfillstyle(SOLID_FILL,LIGHTRED);
    bar3d(optCuloare1.x1,optCuloare1.y1,optCuloare1.x1+20,optCuloare1.y2,0,0);
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL,YELLOW);
    bar3d(optCuloare1.x2-20,optCuloare1.y1,optCuloare1.x2,optCuloare1.y2,0,0);
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar3d(optCuloare2.x1,optCuloare2.y1,optCuloare2.x1+20,optCuloare2.y2,0,0);
    setcolor(LIGHTGREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    bar3d(optCuloare2.x2-20,optCuloare2.y1,optCuloare2.x2,optCuloare2.y2,0,0);
    setcolor(LIGHTMAGENTA);
    setfillstyle(SOLID_FILL,LIGHTMAGENTA);
    bar3d(optCuloare3.x1,optCuloare3.y1,optCuloare3.x1+20,optCuloare3.y2,0,0);
    setcolor(LIGHTCYAN);
    setfillstyle(SOLID_FILL,LIGHTCYAN);
    bar3d(optCuloare3.x2-20,optCuloare3.y1,optCuloare3.x2,optCuloare3.y2,0,0);


    ///Liniile intre culori "/"
    setcolor(BLACK);
    outtextxy(optCuloare1.x1+20,optCuloare1.y1,"/");
    outtextxy(optCuloare2.x1+20,optCuloare2.y1,"/");
    outtextxy(optCuloare3.x1+20,optCuloare3.y1,"/");

    music.x1=maxx/22;
    music.y1=maxy/3+140;
    music.x2=maxx/22+textwidth(limba[nrLimba+7]);
    music.y2=maxy/3+160;
    outtextxy(music.x1,music.y1,limba[nrLimba+7]);
    rectangle(music.x1,music.y1,music.x2,music.y2);

    exi2.x1=maxx/22;
    exi2.y1=maxy/3+180;
    exi2.x2=maxx/22+textwidth(limba[nrLimba+8]);
    exi2.y2=maxy/3+200;
    outtextxy(exi2.x1,exi2.y1,limba[nrLimba+8]);
    rectangle(exi2.x1,exi2.y1,exi2.x2,exi2.y2);

    outtextxy(language.x2+30,language.y1,"ENGLISH"); ///30=spatiul dintre "language" si "ENGLISH"
    outtextxy(language.x2+30+textwidth("ENGLISH")+25,language.y1,"ROMANA");///25=spatiul dintre limbi
    outtextxy(language.x2+30+textwidth("ENGLISH")+25+textwidth("ROMANA")+25,language.y1,"FRANCAIS");

    outtextxy(resolution.x2+20,resolution.y1,"800 x 560");
    outtextxy(resolution.x2+20+textwidth("800 x 560")+25,resolution.y1,"1360 x 700");

    while(1)
    {
        stareMouse(Back.x1,Back.y1,Back.x2,Back.y2,BLACK,RED);
        outtextxy(Back.x1,Back.y1,limba[nrLimba+4]);
        rectangle(Back.x1,Back.y1,Back.x2,Back.y2);

        stareMouse(exi2.x1,exi2.y1,exi2.x2,exi2.y2,BLACK,RED);
        outtextxy(exi2.x1,exi2.y1,limba[nrLimba+8]);
        rectangle(exi2.x1,exi2.y1,exi2.x2,exi2.y2);

        stareMouse(music.x1,music.y1,music.x2,music.y2,BLACK,RED);
        outtextxy(music.x1,music.y1,limba[nrLimba+7]);
        rectangle(music.x1,music.y1,music.x2,music.y2);
        ///Highlight english
        stareMouse(language.x2+30,language.y1,language.x2+30+textwidth("ENGLISH"),language.y2,BLACK,RED);
        outtextxy(language.x2+30,language.y1,"ENGLISH");
        rectangle(language.x2+30,language.y1,language.x2+30+textwidth("ENGLISH"),language.y2);

        ///Highlight romana
        stareMouse(language.x2+30+textwidth("ENGLISH")+25,language.y1,language.x2+30+textwidth("ENGLISH")+25+textwidth("ROMANA"),language.y2,BLACK,RED);
        outtextxy(language.x2+30+textwidth("ENGLISH")+25,language.y1,"ROMANA");
        rectangle(language.x2+30+textwidth("ENGLISH")+25,language.y1,language.x2+30+textwidth("ENGLISH")+25+textwidth("ROMANA"),language.y2);

        ///Highlight francais
        stareMouse(language.x2+30+textwidth("ENGLISH")+25+textwidth("ROMANA")+25,language.y1,language.x2+30+textwidth("ENGLISH")+25+textwidth("ROMANA")+25+textwidth("FRANCAIS"),language.y2,BLACK,RED);
        outtextxy(language.x2+30+textwidth("ENGLISH")+25+textwidth("ROMANA")+25,language.y1,"FRANCAIS");
        rectangle(language.x2+30+textwidth("ENGLISH")+25+textwidth("ROMANA")+25,language.y1,language.x2+30+textwidth("ENGLISH")+25+textwidth("ROMANA")+25+textwidth("FRANCAIS"),language.y2);

        ///Highlight 800 x 560
        stareMouse(resolution.x2+20,resolution.y1,resolution.x2+20+textwidth("800 x 560"),resolution.y2,BLACK,RED);
        outtextxy(resolution.x2+20,resolution.y1,"800 x 560");
        rectangle(resolution.x2+20,resolution.y1,resolution.x2+20+textwidth("800 x 560"),resolution.y2);

        ///Highlight 1360 x 720
        stareMouse(resolution.x2+20+textwidth("800 x 560")+25,resolution.y1,resolution.x2+20+textwidth("800 x 560")+25+textwidth("1360 x 700"),resolution.y2,BLACK,RED);
        outtextxy(resolution.x2+20+textwidth("800 x 560")+25,resolution.y1,"1360 x 700");
        rectangle(resolution.x2+20+textwidth("800 x 560")+25,resolution.y1,resolution.x2+20+textwidth("800 x 560")+25+textwidth("1360 x 700"),resolution.y2);

        ///Highlight Optiune culoare 1
        stareMouse(optCuloare1.x1,optCuloare1.y1,optCuloare1.x2,optCuloare1.y2,DARKGRAY,RED);
        rectangle(optCuloare1.x1,optCuloare1.y1,optCuloare1.x2,optCuloare1.y2);

        ///Highlight Optiune culoare 2
        stareMouse(optCuloare2.x1,optCuloare2.y1,optCuloare2.x2,optCuloare2.y2,DARKGRAY,RED);
        rectangle(optCuloare2.x1,optCuloare2.y1,optCuloare2.x2,optCuloare2.y2);

        ///Highlight Optiune culoare 3
        stareMouse(optCuloare3.x1,optCuloare3.y1,optCuloare3.x2,optCuloare3.y2,DARKGRAY,RED);
        rectangle(optCuloare3.x1,optCuloare3.y1,optCuloare3.x2,optCuloare3.y2);

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,mx,my);
            cout << mx << " " << my << endl;
        }
        if(mx>=Back.x1 && mx<=Back.x2&& my>=Back.y1 && my<=Back.y2)
        {
            cleardevice();
            meniu();
            }
        else if(mx>=music.x1&&mx<=music.x2&&my>=music.y1&&my<=music.y2)
        {
            if(muzicada)
                muzicada=0;
            else
                muzicada=1;
            Pornestemuzica();
            break;
        }
        else if(my>=resolution.y1 && my<=resolution.y2)
        {
            if(mx>=resolution.x2+20 && mx<=resolution.x2+20+textwidth("800 x 560"))
            {
                window_w=800;
                window_h=560;
                width_tabla=height_tabla=560;
                closegraph(window);
                window=initwindow(window_w,window_h,"RAZBOI IN 8");

                PaginaDeSetari();

            }
            else if(mx>=resolution.x2+20+textwidth("800 x 560")+25 && my<=resolution.x2+20+textwidth("800 x 560")+25+textwidth("1360 x 700"))
            {
                window_w=1360;
                window_h=700;
                width_tabla=height_tabla=700;
                closegraph(window);
                window=initwindow(window_w,window_h,"RAZBOI IN 8");

                PaginaDeSetari();
            }
        }
        else if(my>=colors.y1 && my<=colors.y2) ///CLAUDIA
        {
            if(mx>=optCuloare1.x1 && mx<=optCuloare1.x2)
            {
                cul1=culoare[1];
                cul2=culoare[2];
            }
            else if(mx>=optCuloare2.x1 && mx<=optCuloare2.x2)
            {
                cul1=culoare[3];
                cul2=culoare[4];
            }
            else if(mx>=optCuloare3.x1 && mx<=optCuloare3.x2)
            {
                cul1=culoare[5];
                cul2=culoare[6];
            }

        }
        else if(my>=language.y1 && my<=language.y2)
        {
            if(mx>=language.x1+30 && mx<=language.x2+30+textwidth("ENGLISH"))
            {
                nrLimba=0; ///pt engleza
                PaginaDeSetari();
            }
            else if(mx>=language.x2+30+textwidth("ENGLISH")+25&&mx<=language.x2+30+textwidth("ENGLISH")+25+textwidth("ROMANA"))
            {
                nrLimba=19; ///pt romana
                PaginaDeSetari();
            }
            else if(mx>=language.x2+30+textwidth("ENGLISH")+25+textwidth("ROMANA")+25 && mx<=language.x2+30+textwidth("ENGLISH")+25+textwidth("ROMANA")+25+textwidth("FRANCAIS"))
            {
                nrLimba=38;///pt franceza
                PaginaDeSetari();
            }
        }
        ///EXIT de la setari
        else if(mx>=exi2.x1 && mx<=exi2.x2&& my>=exi2.y1 &&my<=exi2.y2)
            exit(0);




    }
}
void instructiuni()   
{
    int mx,my,maxx=getmaxx(),maxy=getmaxy();
    cleardevice();
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    setbkcolor(LIGHTGRAY);
    settextstyle(SIMPLEX_FONT,HORIZ_DIR,4);   ///titlu
    outtextxy(maxx/2-textwidth(limba[nrLimba+3])/2,25,limba[nrLimba+3]);

    BackHelp.x1=window_w-140;
    BackHelp.y1=window_h-70;
    BackHelp.x2=BackHelp.x1+textwidth(limba[nrLimba+4]);
    BackHelp.y2=BackHelp.y1+textheight(limba[nrLimba+4]);
    settextstyle(SIMPLEX_FONT,HORIZ_DIR,2);
    outtextxy(BackHelp.x1,BackHelp.y1,limba[nrLimba+4]);  ///Back


    setfillstyle(SOLID_FILL,WHITE);
    bar(10,90,window_w-10,window_h-95);
    setcolor(BLACK);
    setbkcolor(WHITE);


    while(1)
    {
        stareMouse(BackHelp.x1,BackHelp.y1,BackHelp.x2,BackHelp.y2,BLACK,RED);
        outtextxy(BackHelp.x1,BackHelp.y1,limba[nrLimba+4]);
        rectangle(BackHelp.x1,BackHelp.y1,BackHelp.x2,BackHelp.y2);
        if(nrLimba==0)   ///in engleza
        {
            fgets(rnd,200,f2);
            lin++;
            if(!feof(f2))
                outtextxy(stanga+30,sus+100+30*lin,rnd);

        }

        else if(nrLimba==19)    ///in romana
        {
            fgets(rnd,200,f1);
            lin++;
            if(!feof(f1))
                outtextxy(stanga+30,sus+100+30*lin,rnd);
        }

        else if(nrLimba==38)    ///in franceza
        {
            fgets(rnd,200,f3);
            lin++;
            if(!feof(f3))
                outtextxy(stanga+30,sus+100+30*lin,rnd);
        }
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,mx,my);
        }
    if(mx>=BackHelp.x1 && mx<=BackHelp.x2 && my>=BackHelp.y1 && my<=BackHelp.y2)
    {
       cleardevice();
       meniu();
    }
}
}
void meniu()
{
    int mx=0,my=0;
    butoaneMeniu();
    while(1)
    {
        butoaneMeniuHover();

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,mx,my);
            ///cout << mx << " " << my << endl;
        }

        if(mx >= pvp.x1 && mx <= pvp.x2&& my >=pvp.y1 && my<=pvp.y2)
        {
            joacaPVP();


        }
        else if(mx >= pvc.x1 && mx <= pvc.x2&& my >=pvc.y1 && my<=pvc.y2)
        {
            joacaPVC();

        }

        else if(mx >= settings.x1 && mx <= settings.x2 && my >=settings.y1 && my<=settings.y2)
        {
            cleardevice();
            PaginaDeSetari();

        }

        else if(mx >= help.x1 && mx <= help.x2 && my>=help.y1 && my<=help.y2)
            instructiuni();

        else if(mx >= exi.x1 && mx <= exi.x2 && my >=exi.y1 && my<=exi.y2)
            exit(0);

    }


}

int main()
{
    window=initwindow(800,560,"RAZBOI IN 8");
    scorrosu=0;
    scorgalben=0;
    ///Bordare matrice
    int k;
    for(k=0; k<=9; k++)
        TablaDeJoc[0][k]=TablaDeJoc[9][k]=8;///ceva diferit de 0 ca sa poata elimina piesele
    for(k=0; k<=9; k++)
        TablaDeJoc[k][0]=TablaDeJoc[k][9]=8;
    if(!music1.openFromFile("muzica.ogg"))

    {
        std::cout<<"ERROR"<<std::endl;

    }
    if(!music2.openFromFile("win.ogg"))

    {
        std::cout<<"ERROR"<<std::endl;

    }
    if(!music3.openFromFile("fail.ogg"))

    {
        std::cout<<"ERROR"<<std::endl;

    }
    if(!music4.openFromFile("mutare.ogg"))

    {
        std::cout<<"ERROR"<<std::endl;

    }
    meniu();
    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}
