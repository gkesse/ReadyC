//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//===============================================
void GDate_Read(char* buffer);
//===============================================
int main(int argc, char** argv) {
  int h, min, s, day, mois, an;
  time_t now;
    
  // Renvoie l'heure actuelle
  time(&now);
  // Convertir au format heure locale
  printf("Aujourd'hui est : %s", ctime(&now));
  struct tm *local = localtime(&now);
  h = local->tm_hour;        
  min = local->tm_min;       
  s = local->tm_sec;       
  day = local->tm_mday;          
  mois = local->tm_mon + 1;     
  an = local->tm_year + 1900;  
  printf("L'heure : %02d:%02d:%02d\n", h, min, s);
  // Afficher la date courante
  printf("La date : %02d/%02d/%d\n", day, mois, an);
  return 0;
}
//===============================================
void GDate_Read(char* buffer) {
    time_t lRawTime;
    time(&lRawTime);
    struct tm* lTimeInfo = localtime(&lRawTime);
    int lDay = lTimeInfo->tm_mday;
    int lMonth = lTimeInfo->tm_mon + 1;
    int lYear = lTimeInfo->tm_year + 1900;
    int lHour = lTimeInfo->tm_hour;
    int lMin = lTimeInfo->tm_min;
    int lSec = lTimeInfo->tm_sec;
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d", lDay, lMonth, lYear, lHour, lMin, lSec);
}
//===============================================