{
double x_0[100],y_0[100];
double chi2_0=0;


for(int j=0;j<100;j++){ 
  chi2_0=0; 
  calcP->SetParameter(0,7233+15*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_0+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    //cout<<"chi2"<<" "<<chi2_0<<endl;
    x_0[j]=7233+15*j;
    y_0[j]=chi2_0;
    }
}
//for(int j=0;j<100;j++){ chi2=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2;}
TGraph gr0(100,x_0,y_0);
gr0.Draw("AP");
CC->SaveAs("../../plot/chi2/p0.png");
}
