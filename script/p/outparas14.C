{
float a;
   //send the parameters out
   ofstream out("paras14.txt");
   for(int i=0;i<14;i++){
    a = calcP->GetParameter(i);
    out<<a<<endl;
   }
}
