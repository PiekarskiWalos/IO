#include <iostream>
#include<fstream>

using namespace std;


#define ile_kategorii 7;
int x;
class menu;
class kategoria;
class saldo;
void dodaj_transakcje(saldo*);
void pokaz_kategorie();





class kategoria
{
    public:
string nazwa;
int index;
double limit;
//konstruktor
kategoria()
{
    limit=0;
}

void ustaw_limit()
{
    cout<<endl<<"Obecny limit kategorii "<<nazwa<<" wynosi: "<<limit<<endl;
    cout<<"Wprowadz nowy limit:"<<endl;
    cin>>limit;
    cout<<endl<<"zmieniono limit dla kategorii "<<nazwa<<endl;
}

//friend menu;
//friend main;
};
kategoria KATEGORIE[8];

class saldo
{
    public:
double saldo_glowne;
double salda[8];
double wydatki[8];
//konstruktor
saldo()
{
    saldo_glowne=0;
    for(int i=0;i<=7;i++)
        {salda[i]=0; wydatki[i]=0;}
}

void pokaz_salda()
{
    cout<<endl;
    cout<<"Saldo glowne: "<<saldo_glowne<<endl;
    for(int i=1;i<=7;i++)
    {
        cout<<"Saldo kategorii "<<KATEGORIE[i].nazwa<<" wynosi: "<<salda[i]<<endl;
    }

}
friend int main();
//friend menu;
public:
    void przelicz(int ind,double kw)
    {
        if(ind>0)
        {
        wydatki[ind]+=kw;
        salda[ind]-=kw;
        saldo_glowne-=kw;
        }
        else if(ind==0)
        {
            saldo_glowne+=kw;
        }
        else{cout<<"blad"<<endl;}
    }
};



class menu
{
public:
bool menu_glowne(saldo* Saldo)
{
    int x;
    cout<<"wybierz interesujaca cie opcje:"<<endl<<"1. dodaj transakcje"<<endl<<"2. pokaz salda"<<endl<<"3. ustaw limity"<<endl<<"4. wyjscie"<<endl;
    cin>>x;
    switch(x)
    {
        case 1: dodaj_transakcje (Saldo); break;
        case 2:
                Saldo->pokaz_salda();
                break;

        case 3:
                cout<<"Wybierz kategorie dla ktorej chcesz zmienic limit"<<endl;
                pokaz_kategorie();
                cin>>x;
                KATEGORIE[x].ustaw_limit();
                break;
		case 4:return true;
        default: cout<<"BLAD"<<endl; break;
    }

	return false;
}
//friend main;

};


void pokaz_kategorie()
{
    for(int i=0;i<=7;i++)
        cout<<i<<". "<<KATEGORIE[i].nazwa<<endl;
}

void dodaj_transakcje(saldo* Saldo)
{
    double k;
	fstream plik;

    cout<<"Wybierz kategorie"<<endl;
    pokaz_kategorie();
    cin>>x;
    if(x<0 || x>7)
    {
        cout<<"blad"<<endl;
        return;
    }
    cout<<"podaj kwote"<<endl;
    cin>>k;
    cout<<"Wykonano operacje"<<endl;
    //otwarcie pliku do dopisania
	plik.open("transakcje.txt"/*,ios::app*/);
    //zapis do pliku
		plik<<x<<" "<<k<<endl;
    //zamkniecie pliku
	plik.close();
    Saldo->przelicz(x,k);
return;
}

int main()
{
    saldo Saldo;
    menu m;
KATEGORIE[0].nazwa="przychod";
KATEGORIE[1].nazwa="jedzenie";
KATEGORIE[2].nazwa="rozrywka";
KATEGORIE[3].nazwa="chemia";
KATEGORIE[4].nazwa="odziez";
KATEGORIE[5].nazwa="rachunki";
KATEGORIE[6].nazwa="transport";
KATEGORIE[7].nazwa="inne";

for(int i;i<=7;i++)
    KATEGORIE[i].index=i;

	for(;;)
	{
	if(m.menu_glowne(&Saldo))
	break;
	}

    return 0;
}
