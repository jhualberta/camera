{
double x_10[100],y_10[100];
double chi2_10=0;


for(int j=0;j<100;j++){ 
  chi2_10=0; 
  calcP->SetParameter(10,0+0.01*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_10+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    //cout<<"chi2_10"<<" "<<chi2_10<<endl;
    x_10[j]=0+0.01*j;
    y_10[j]=chi2_10;
    }
}
//for(int j=0;j<100;j++){ chi2_10=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2_10+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2_10;}
TGraph gr_10(100,x_10,y_10);
gr_10.Draw("AP");
CC->SaveAs("../../plot/chi2/p10.png");
}
