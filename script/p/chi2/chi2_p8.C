{
double x_8[100],y_8[100];
double chi2_8=0;


for(int j=0;j<100;j++){ 
  chi2_8=0; 
  calcP->SetParameter(8,-200+10*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_8+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    //cout<<"chi2_8"<<" "<<chi2_8<<endl;
    x_8[j]=-200+10*j;
    y_8[j]=chi2_8;
    }
}
//for(int j=0;j<100;j++){ chi2_8=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2_8+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2_8;}
TGraph gr_8(100,x_8,y_8);
gr_8.Draw("AP");
CC->SaveAs("../../plot/chi2/p8.png");
}
