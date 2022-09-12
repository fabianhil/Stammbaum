#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char const* const VERSIONSNR = "0.1.2";

int const DB_SIZE = 50;

struct name
{
    char nachname[20];
    char vorname[20];
};

struct datum
{
    int jahr;
    int monat;
    int tag;
};

struct person
{
    int  generation;
    struct name vorfahre;
    char nachname[20];
    char vorname[20];
    struct datum geb_datum;
    struct datum tod_datum;
    struct name ehe_partner;
    struct name kind1;
    struct name kind2;
    struct name kind3;
    struct name kind4;
};
typedef struct person person_t;

void readcsv(char const* const datei)
{
    FILE* filepointer = NULL;
    int   zaehler     = 0;

    filepointer = fopen(datei, "r");
    if(NULL == filepointer)
    {
        fprintf(stderr, "Couldnt open file '%s'\n", datei);
        exit(2);
    }
    person_t stammbaum[DB_SIZE];
    while(fscanf(filepointer,
                 "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d,%d,%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",
                 &stammbaum[zaehler].generation,
                 stammbaum[zaehler].vorfahre.nachname,
                 stammbaum[zaehler].vorfahre.vorname,
                 stammbaum[zaehler].nachname,
                 stammbaum[zaehler].vorname,
                 &stammbaum[zaehler].geb_datum.jahr,
                 &stammbaum[zaehler].geb_datum.monat,
                 &stammbaum[zaehler].geb_datum.tag,
                 &stammbaum[zaehler].tod_datum.jahr,
                 &stammbaum[zaehler].tod_datum.monat,
                 &stammbaum[zaehler].tod_datum.tag,
                 stammbaum[zaehler].ehe_partner.nachname,
                 stammbaum[zaehler].ehe_partner.vorname,
                 stammbaum[zaehler].kind1.nachname,
                 stammbaum[zaehler].kind1.vorname,
                 stammbaum[zaehler].kind2.nachname,
                 stammbaum[zaehler].kind2.vorname,
                 stammbaum[zaehler].kind3.nachname,
                 stammbaum[zaehler].kind3.vorname,
                 stammbaum[zaehler].kind4.nachname,
                 stammbaum[zaehler].kind4.vorname)
            != EOF)
    {
        printf("\nGeneration: %d \n Vorfahre: %s, %s \n Name: %s, %s \n Geburtsdatum: %d.%d.%d \n",
               stammbaum[zaehler].generation,
               stammbaum[zaehler].vorfahre.nachname,
               stammbaum[zaehler].vorfahre.vorname,
               stammbaum[zaehler].nachname,
               stammbaum[zaehler].vorname,
               stammbaum[zaehler].geb_datum.tag,
               stammbaum[zaehler].geb_datum.monat,
               stammbaum[zaehler].geb_datum.jahr);
        if(stammbaum[zaehler].tod_datum.jahr!= 0)
        {
            printf(" Todestag: %d.%d.%d \n",
                   stammbaum[zaehler].tod_datum.tag,
                   stammbaum[zaehler].tod_datum.monat,
                   stammbaum[zaehler].tod_datum.jahr);
        }
        printf(" Ehepartner: %s, %s \n",
               stammbaum[zaehler].ehe_partner.nachname,
               stammbaum[zaehler].ehe_partner.vorname);
        if(stammbaum[zaehler].kind1.vorname[1]!= '%')
        {
            printf(" Kind 1: %s, %s \n",
                   stammbaum[zaehler].kind1.nachname,
                   stammbaum[zaehler].kind1.vorname);
        }
        if(stammbaum[zaehler].kind2.vorname[1]!= '%')
        {
            printf(" Kind 2: %s, %s \n",
                   stammbaum[zaehler].kind2.nachname,
                   stammbaum[zaehler].kind2.vorname);
        }
        if(stammbaum[zaehler].kind3.vorname[1]!= '%')
        {
            printf(" Kind 3: %s, %s \n",
                   stammbaum[zaehler].kind3.nachname,
                   stammbaum[zaehler].kind3.vorname);
        }
        if(stammbaum[zaehler].kind4.vorname[0]!= '%')
        {
            printf(" Kind 4: %s, %s \n",
                   stammbaum[zaehler].kind4.nachname,
                   stammbaum[zaehler].kind4.vorname);
        }
        zaehler++;
        if(zaehler == DB_SIZE)
        {
            fprintf(stderr, "Datenbank voll! \n");
            break;
        }
    }
    // check if file closed correctly
    if(fclose(filepointer) == EOF)
    {
        fprintf(stderr, "Fehler beim schließen der Datei! \n");
        exit(2);
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "No option recognized. Wrong Usage. Please try -h\n");
    }

    while(true)
    {
        int option = getopt(argc, argv, "hvf:");
        switch(option)
        {
        case 'h':
            printf("Bitte -f nutzen um einen File-Path anzugeben\n");
            exit(0);

        case 'v':
            printf("Version %s\n", VERSIONSNR);
            exit(0);

        case 'f':
            readcsv(optarg);
            break;

        case '?':
            fprintf(stderr, "Please try -h\n");
            exit(1);

        case -1:
            exit(0);
        }
    }

    return 0;
}