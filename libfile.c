void data_zo_suboru(char namedata[],char data[][10],int pocetdat){
   FILE * pFile;
   pFile = fopen (namedata , "r");
   if (pFile == NULL) perror ("Error opening file");
   else {
      for(int x=0;x!=pocetdat;x++){
        fgets (data[x] , 11 , pFile);
      }
   }
  fclose (pFile);
}
void data_do_suboru(char namedata[],char data[][10],int pocetdat){
   FILE * pFile;
   pFile = fopen (namedata , "w");
   if (pFile == NULL) perror ("Error opening file");
   else {
      for(int x=0;x!=pocetdat;x++){
        data[x][9] = '\n';
        fwrite (data[x] , 1 , sizeof(data[x]) , pFile );
      }
   }
  fclose (pFile);
}