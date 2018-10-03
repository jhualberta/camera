{
float a;
   //send the parameters out
   ofstream out("paras8.txt");
   for(int i=0;i<8;i++){
    a = calcP->GetParameter(i);
    out<<a<<endl;
   }
}
