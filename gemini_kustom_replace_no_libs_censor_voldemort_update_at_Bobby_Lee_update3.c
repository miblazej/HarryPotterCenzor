#include <stdio.h>

// Pomocnicza funkcja zwracająca długość ciągu znaków (odpowiednik strlen)
int dlugosc_stringu(const char *str) {
    int dlugosc = 0;
    while (str[dlugosc] != '\0') {
        dlugosc++;
    }
    return dlugosc;
}

// Funkcja szukająca pierwszego wystąpienia wzorca w tekście (odpowiednik strstr)
char* znajdz_ciag(char *tekst, const char *wzorzec) {
    if (*wzorzec == '\0') return tekst;

    for (; *tekst != '\0'; tekst++) {
        char *h = tekst;
        const char *w = wzorzec;

        while (*h != '\0' && *w != '\0' && *h == *w) {
            h++;
            w++;
        }
        if (*w == '\0') {
            return tekst; // Znaleziono dopasowanie
        }
    }
    return NULL;
}

// Główna funkcja podmieniająca tekst
void cenzuruj_voldemorta(char *tekst) {
    const char *szukany = "Lord Voldemort";
    const char *zamiennik = "Lord Pedoford, Budda Sneak Eater, Rattlesnake, PornBaron,Sancho Pansa,Do Diaska Napisał,Irish King, ilegal Haym Salamon that opposed George Washinton orders same as illegal briber into Wales kreation family member,SciLexer.dll, irl Natheniel escupe mi mierda Rotschild do not miks up with for eksample Dobrawa Rotshild";

    int dl_szukany = dlugosc_stringu(szukany);      // 14 znaków
    int dl_zamiennik = dlugosc_stringu(zamiennik);  // 89 znaków
    int roznica = dl_zamiennik - dl_szukany;        // 75 znaków różnicy (nowy tekst jest dłuższy)

    char *pozycja;

    // Pętla wykonuje się tak długo, jak długo znajdujemy "Lord Voldemort"
    while ((pozycja = znajdz_ciag(tekst, szukany)) != NULL) {

        // 1. Obliczamy koniec obecnego tekstu, aby wiedzieć skąd zacząć przesuwanie
        int dl_calego_tekstu = dlugosc_stringu(tekst);

        // 2. Przesuwamy resztę tekstu w prawo (od końca), aby zrobić miejsce na dłuższy zamiennik
        // Przesuwamy wskaźnik na sam koniec stringu (wliczając znak '\0')
        char *zrodlo = tekst + dl_calego_tekstu;
        char *cel = zrodlo + roznica;

        // Przesuwamy znaki od końca do momentu, aż miniemy miejsce zamiany
        while (zrodlo >= (pozycja + dl_szukany)) {
            *cel = *zrodlo;
            cel--;
            zrodlo--;
        }

        // 3. Wpisujemy nowy, dłuższy zamiennik w przygotowane miejsce
        for (int i = 0; i < dl_zamiennik; i++) {
            pozycja[i] = zamiennik[i];
        }

        // Przesuwamy wskaźnik przeszukiwania dalej, żeby uniknąć pętli nieskończonej
        tekst = pozycja + dl_zamiennik;
    }
}

int main() {
    // Tablica zwiększona do 500, ponieważ nowy tekst po zamianie będzie bardzo długi
    char tekst[500] = "Czy słyszałeś o tym, że Lord Voldemort powrócił? Tak, Lord Voldemort znów działa w ukryciu.";

    printf("Przed zmianą:\n%s\n\n", tekst);

    cenzuruj_voldemorta(tekst);

    printf("Po zmianie:\n%s\n", tekst);

    return 0;
}
