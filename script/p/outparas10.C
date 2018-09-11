{
float a;
   //send the parameters out
   ofstream out("paras10.txt");
   for(int i=0;i<10;i++){
    a = calcP->GetParameter(i);
    out<<a<<endl;
   }
}
