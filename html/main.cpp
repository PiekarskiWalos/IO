#include <iostream>
#include<fstream>

using namespace std;


#define ile_kategorii 7; //! zdefiniowanie 7 kategorii
int x; //! zmienna x, sluzy do wyboru
class menu; //! klasa o nazwie menu odpowiada za obsluge, jest kontrolerem
class kategoria; //! klasa o nazwie kategoria, przechowuje informacje o nazwie kategorii i limicie
class saldo; //! klasa o nzawie saldo, odpowiada za aktualny stan konta
void dodaj_transakcje(saldo*); //! funkcja
void pokaz_kategorie(); //! funkcja dodajaca konkretne transakcje





class kategoria //! klasa kategoria
{
    public:
string nazwa; //! zmienna przechowujaca nazwe
int index; //! zmienna indeksujaca kategorie
double limit; //! zmienna do wprowadzania limitow w poszczegolnych kategoriach
//! konstruktor
kategoria()
{
    limit=0;
}

void ustaw_limit()//! funkcja do ustawiania konkretnych limitow
{
    cout<<endl<<"Obecny limit kategorii "<<nazwa<<" wynosi: "<<limit<<endl; //! podglad dotychczasowego limitu
    cout<<"Wprowadz nowy limit:"<<endl; //! mozliwosc wprowadzenia nowego limitu
    cin>>limit;
    cout<<endl<<"zmieniono limit dla kategorii "<<nazwa<<endl; //! wyswietlenie zmian
}


};
kategoria KATEGORIE[8]; //! nowy obiekt

class saldo //! klasa saldo
{
    public:
double saldo_glowne; //! saldo ogolne
double salda[8]; //! tablica poszczegolnych sald kazdej kategorii
double wydatki[8]; //! wydatki z poszczegiolnych kategorii
//! konstruktor
saldo()
{
    saldo_glowne=0;
    for(int i=0;i<=7;i++)
        {salda[i]=0; wydatki[i]=0;}
}

void pokaz_salda() //! funkcja pokazujaca stan aktualny salda
{
    cout<<endl;
    cout<<"Saldo glowne: "<<saldo_glowne<<endl;
    for(int i=1;i<=7;i++)
    {
        cout<<"Saldo kategorii "<<KATEGORIE[i].nazwa<<" wynosi: "<<salda[i]<<endl; //! wyswietlenie salda konkretnych kategorii
    }

}
friend int main(); //! zaprzyjaznienie

public:
    void przelicz(int ind,double kw)//! funkcja przeliczajca stany sald
    {
        if(ind>0) //! jezeli indeks kategorii jest wiekszy od 0
        {
        wydatki[ind]+=kw; //! do wydatkow kategorii dodajemy kwote wydana
        salda[ind]-=kw; //! w saldzie kategorii odejmujemy kwote wydana
        saldo_glowne-=kw; //! saldo ogolne zmniejszamy o kwote wydana
        }
        else if(ind==0) //! jezeli indeks kategorii jest rowny 0
        {
            saldo_glowne+=kw; //! dodajemy wplate do salda glownego
        }
        else{cout<<"blad"<<endl;} //! w przeciwnym wypadku pokaz blad
    }
};



class menu //! klasa menu
{
public:
bool menu_glowne(saldo* Saldo)
{
    int x; //! zmienna sterujaca
    cout<<"wybierz interesujaca cie opcje:"<<endl<<"1. dodaj transakcje"<<endl<<"2. pokaz salda"<<endl<<"3. ustaw limity"<<endl<<"4. wyjscie"<<endl; //! wyswietlanie opcji menu
    cin>>x;
    switch(x) //! wybor menu glownego
    {
        case 1: dodaj_transakcje (Saldo); break; //! wybor 1 - dodawanie transkacji
        case 2:
                Saldo->pokaz_salda(); //! wybor 2- podglad salda
                break;

        case 3: //! wybor 3 - ustawianie limitow
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


};


void pokaz_kategorie()//!  funkcja wyswietlajaca nazwy kategorii
{
    for(int i=0;i<=7;i++)
        cout<<i<<". "<<KATEGORIE[i].nazwa<<endl; //! wyswietlanie kategorii wedlug indeksow
}

void dodaj_transakcje(saldo* Saldo)//! funkcja dodajaca transakcje
{
    double k; //! podana przez uzytkownika kwota
	fstream plik; //! zapis do pliku

    cout<<"Wybierz kategorie"<<endl;//! mozliwosc wyboru kategorii
    pokaz_kategorie();
    cin>>x;
    if(x<0 || x>7)
    {
        cout<<"blad"<<endl; //! blad jezeli poza zakresem
        return;
    }
    cout<<"podaj kwote"<<endl;//! wpisywanie kwoty
    cin>>k;
    cout<<"Wykonano operacje"<<endl; //! potwierdzenie da uzytkownika

	plik.open("transakcje.txt"/*,ios::app*/);//!otwarcie pliku do dopisania

		plik<<x<<" "<<k<<endl;//!zapis do pliku

	plik.close(); //!zamkniecie pliku
    Saldo->przelicz(x,k);
return;
}

int main()//! main
{
    saldo Saldo;
    menu m;
    //! nazwy wszystkich kategorii wedlug indeksow
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

	for(;;) //! petla nieskonczona
	{
	if(m.menu_glowne(&Saldo))
	break;
	}

    return 0;
}
