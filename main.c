/******************************************************************************/
/*                                                                            */
/*  KONRAD ZDANOWICZ          NR ALBUMU 180394                                */
/*                                                                            */
/*  POLITECHNIKA WROCLAWSKA   WYDZ. ELEKTRONIKI, AUTOMATYKA I ROBOTYKA        */
/*                                                                            */                        
/******************************************************************************/

/*                       
 o----------------------------------------------------------------------------o  
 
 
                    ___________________________  _________  
                    \______   \______   \      \ \_   ___ \ 
                     |       _/|     ___/   |   \/    \  \/ 
                     |    |   \|    |  /    |    \     \____
                     |____|_  /|____|  \____|__  /\______  /
                            \/                 \/        \/ 
                              REVERSE POLISH NOTATION CALCULATOR
   
   
   
 o----------------------------------------------------------------------------o  
   
   
    
  +- OPERATORY -----------------------------------------------------+
  |                                                                 |
  |            +        DODAJE DWIE OSTATNIE LICZBY                 |
  |            -        ODEJMUJE        ||                          |
  |            *        MNOZY           ||                          |
  |            /        DZIELI          ||                          |
  |                                                                 |
  |            --------------------------------------               |
  |                                                                 |
  |            #        USUWA OSTATNIA WPISANA LICZBE               |
  |            $        ZAMIENIA DWIE OSTATNIE MIEJSCAMI            |
  |            &        KOPIUJE OSTATNI ELEMENT                     |
  |            ?        WYPISUJE CALY STOS OD GORY                  |
  |            q        ZAMYKA PROGRAM (wielkosc znaku              |
  |                                               MA znaczenie)     |
  |                                                                 |
  +-----------------------------------------------------------------+
  
 o----------------------------------------------------------------------------o 
  
              /""\
             /    \          PARAMETRY I LICZBY ODDZIELAJ SPACJA.*
            /   _  \              
           /   \/   \          
          /    o     \       NA PRZYKLAD: 2 + -3 3 $ -4 # ? q   
         /____________\
        |__U_W_A_G_A!__|
        |// // // // //|
        '""""""""""""""' 
   
  o----------------------------------------------------------------------------o   
   
                                                                              */




#include <stdio.h>
#include <stdlib.h>




                                       /* definicja kodow ASCII               */
                                       /* znakow operatorow dzialan           */

#define PLUS            43                                               /* + */             
#define MINUS           45                                               /* - */
#define RAZY            42                                               /* * */
#define PRZEZ           47                                               /* / */




                                       /* definicja kodow ASCII               */
                                       /* znakow operatorow dodatkowych       */

#define POP             35                                               /* # */
#define SWAP            36                                               /* $ */
#define COPY            38                                               /* & */
#define PRINT           63                                               /* ? */
#define EXIT            113                                              /* q */




                                       /* kody ASCII znakow, ktore pomijamy   */


#define SPACJA   32                                                 /* spacja */
#define ENTER    10                                                 /* enter  */  





#define POCZ_LICZB 48                                    /* kod ASCII liczby 0*/
#define KON_LICZB 57                                     /* kod ASCII liczby 9*/



/*----------------------------------------------------------------------------*/


typedef      struct                     /* definicja struktury listy          */

{
    int      dana;                      /* wartosc przechowywana przez el.    */
    
    void *   wsk;                       /* wskaznik na nastepny element       */
                                        /* pomimo tego, ze deklaruje wskaznik */
                                        /* na void, w procedurach program     */
                                        /* dokonuje konwersji na typ elem     */
    
} elem;                                 /* etykieta struktury                 */          


/*----------------------------------------------------------------------------*/


elem  *    inicjuj      (int, elem*);   /* tworzy liste i zwraca glowe        */

elem  *    push         (int, elem*);   /* dodaje na poczatek listy           */
elem  *    pop          (elem *);       /* usuwa pierwszy el. z listy         */
  
int        mozna        (elem*);        /* sprawdza czy istnieja dwa          */
elem  *    dzialaj      (elem *,int);   /* elementy do dzialania              */

elem  *    swap         (elem*);        /* zamienia dwa el. miejscami         */
elem  *    copy         (elem*);        /* duplikuje pierwszy el.             */

int        czy_liczba   (char*);        /* zwraca cyfra lub -1 gdy znak       */
                                        /* nie jest cyfra                     */
                                        
int        na_liczbe    (char *);       /* konwersja char->int                */
                                        /* zwraca -1 w razie bledu            */

void       wypisz       (elem *);       /* wypisuje cala zawartosc listy      */




/*----------------------------------------------------------------------------*/



int main (void)
{
 

    elem * pocz = NULL;                        /* poczatek listy              */
    
    int kontynuuj=1;                    /* zmienna pomocnicza                 */
    
    char wczytywany;                    /* tu przechowujemy wyczytywany znak  */
    
    
    int wczytuj_liczbe;                 /* tutaj przechowujemy informacje     */
                                        /* o tym czy wczytywac liczbe         */
                                        /* (czujnik znaku 'q')                */
                                        
    int znak=1;                         /* flaga znaku minus w liczbie        */
    
    int liczba=0;                       /* zmienna na liczbe                  */
    
    int i;                              /* pomocnicza zmienna                 */



    while(kontynuuj)                    /* glowna procedura, powtarza sie     */
    {                                   /* az do momentu ze kontynnuj=0       */
    
                                 
       liczba=0;                        /* zerujemy opcje                     */
       znak=1;                          /* ustawiamy znak na + (domyslnie)    */
       wczytuj_liczbe=0;                /* zerujemy opcje                     */
       

       
       scanf("%c",&wczytywany);         /***** WCZYTYWANIE                *****/
       
       

       if(wczytywany!=SPACJA && wczytywany!=ENTER) /* pomijamy spacje i enter */
       
       {                   
                           
                           
          switch(wczytywany)                       /* przetwarzanie znaku     */
          {
          
          case POP:    pocz=pop(pocz);       break;         /* usun ostatni   */
          case SWAP:   pocz=swap(pocz);      break;         /* zamien dwa     */
          case COPY:   pocz=copy(pocz);      break;         /* duplikuj       */
          case PRINT:  wypisz(pocz);         break;         /* wypisz         */
          case EXIT:   kontynuuj=0;          break;         /* zakoncz        */
          
          case PLUS:   pocz=dzialaj(pocz,1); break;         /* dodawanie      */
          
          case MINUS:                                       /* znak minus:    */
          {
                        scanf("%c",&wczytywany);            /* czytamy nast.  */
                        
                        if(czy_liczba(&wczytywany))         /* jesli liczba   */
                        {
                            znak=-1;                        /* to ujemna      */
                            wczytuj_liczbe=1;   /* i szykujemy do dalszego    */
                                                /* przetwarzania              */                 
                        }
                 
                        else pocz=dzialaj(pocz,2);             /* odejmowanie */
                        
                                             break;     
          } 
          
          
          case RAZY:   pocz=dzialaj(pocz,3); break;            /* mnozenie    */
          case PRZEZ:  pocz=dzialaj(pocz,4); break;            /* dzielenie   */
          
          default:  if(czy_liczba(&wczytywany)) wczytuj_liczbe=1; 
          
          /****************************************************************/
          /* sprawdzamy czy wczytuje sie liczbe, jesli tak, przekaz dalej */
          /* polecenie dalszego wczytywania liczby                        */                      
          /****************************************************************/
              
          }  /* koniec switcha */   
            
            
          if(wczytuj_liczbe)                           /* dalsze wczyt. liczb */
           {
                    liczba=na_liczbe(&wczytywany);     /* konwersja char->int */

                    while(liczba==0)                   /* usuwamy zera przed  */
                    {
                         scanf("%c",&wczytywany);
                         liczba=na_liczbe(&wczytywany);
                    }

                     
                     scanf("%c",&wczytywany);          /* wczytujemy nastepna */
                                                       /* pozycje liczby      */
                     
                     i=na_liczbe(&wczytywany);       
                     
                     
                     
                     
                     while(i+1)       /* sposob na przeliczenie liczby z char */
                     {     
                         liczba*=10;     /* wczytujemy kolejne pozycje liczby */
                         liczba+=i;                           
                         scanf("%c",&wczytywany);
                         i=na_liczbe(&wczytywany);
                     }
                     
                     liczba*=znak;             /* domnazamy minus, jesli jest */
                     pocz=push(liczba,pocz);   /* dodajemy element na liste   */

           }                                           
       }         
    }
    
    return 0;    
}













/*----------------------------------------------------------------------------*/
/* FUNKCJE                                                                    */
/*----------------------------------------------------------------------------*/



elem *inicjuj(int dana, elem* element)
{
     element=(elem*)malloc(sizeof(elem));
     element->wsk=NULL;
     element->dana=dana;
     
     return element;     
}




elem* push (int dana, elem* element)
{
     elem *pom;
     pom=(elem*)malloc(sizeof(elem));
     pom->wsk=element;
     pom->dana=dana;
     
     return pom;      
}



elem* pop (elem *element)
{
     elem* pom;
           
     if(element==NULL) return NULL;

     pom=element->wsk;
     free(element);
    
     return pom;
}


void wypisz(elem *pocz)
{

    if(pocz==NULL) printf("[ lista jest pusta ]\n");
    
    while(pocz!=NULL)
    {
          printf("[%i]",pocz->dana);
          pocz=pocz->wsk;           
    }
    
    
}

int mozna(elem*pocz)
{

   int te=1;
   if(pocz==NULL) te=0;                
   else if(pocz->wsk==NULL) te=0;
   
   if(te==1) return 1;
   printf("nie mozna wykonac operacji. potrzebuje przynajmniej 2 elementow.\n");
   return 0;

      
}



elem* dzialaj(elem *pocz,int operacja) 
{
      /* jezeli nie ma dwoch elementow to anulujemy operacje i wyrzucamy blad */
    int a,b,wynik;   /* dwie liczby. a jest liczba pierwsza (glebiej w stosie)*/
    elem* pom;                                          /* zmienna pomocnicza */
    
    if(!mozna(pocz)) return pocz;
    
    
        b=pocz->dana;
        pom=pocz->wsk;    
        a=pom->dana;

                                                                  /* dzialamy */
    
       switch(operacja)
       {
           case 1: wynik=a+b; break;
           case 2: wynik=a-b; break;
           case 3: wynik=a*b; break;
           case 4: 
                {
                if(b==0)
                {
                         printf("nie mozna dzielic przez 0.\n\n");
                         return pocz;         
                }
                else wynik=a/b;
                break;              
                 }
       }
                                     /* sciagamy ze stosu dwie osatnie liczby */
        pocz=pop(pocz);
        pocz=pop(pom);
        
        
                 /* zwracamy wskaznik na nowy element listy = wynik dzialania */
    
        return push(wynik,pocz);  
}

/* zamiana miejscami */

elem* swap(elem *pocz)
{
      
      int a,b; 
      
      if(!mozna(pocz)) return pocz; 

      a=pocz->dana;
      pocz=pop(pocz);
      b=pocz->dana;
      pocz=pop(pocz);
      pocz=push(a,pocz);
      pocz=push(b,pocz);
      return pocz;      
}

elem* copy(elem*pocz)
{
      
      int a;
      if(pocz->wsk==NULL) return pocz;       /* potrzebujemy jednego elementu */
      

      a=pocz->dana;
      pocz=push(a,pocz);
      return pocz; 
      
}


int czy_liczba(char * znak) /* sprawdza przez porownanie kodow ASCII          */
                            /* poprawnosc cyfry                               */
{
    int pocz=POCZ_LICZB; 
    int kon=KON_LICZB; 
    
    for(;pocz<=kon;pocz++)
    if(*znak==pocz) return 1;
    
    return 0;   
}


int na_liczbe(char * znak) /* konwersja INT na CHAR                           */
{
    int i;
    
    for(i=0;i<=9;i++) if(*znak==POCZ_LICZB+i) return i;
    return -1;
       
}
