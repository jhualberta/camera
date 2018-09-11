{
float a;
   //send the parameters out
   ofstream out("paras7.txt");
   for(int i=0;i<7;i++){
    a = calcP->GetParameter(i);
    out<<a<<endl;
   }
}
