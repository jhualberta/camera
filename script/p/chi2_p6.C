{
double x_6[100],y_6[100];
double chi2_6=0;


for(int j=0;j<100;j++){ 
  chi2_6=0; 
  calcP->SetParameter(6,1000+15*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_6+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    x_6[j]=0+15*j;
    y_6[j]=chi2_6;
    }
}
//for(int j=0;j<100;j++){ chi2=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2;}
TGraph gr_6(100,x_6,y_6);
gr_6.Draw("AP");
CC->SaveAs("../../plot/chi2/p6.png");
}
