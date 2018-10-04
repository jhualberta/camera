//send the parameters out form the fit


{
float aa;

   ofstream out2("paras11.txt");
   for(int i=0;i<11;i++){
    aa = calcP->GetParameter(i);
    out2<<aa<<endl;
   }
}
