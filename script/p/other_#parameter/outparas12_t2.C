{
float aa;
   //send the parameters out2
   ofstream out2("paras12_t2.txt");
   for(int i=0;i<12;i++){
    aa = calcP->GetParameter(i);
    out2<<aa<<endl;
   }
}
