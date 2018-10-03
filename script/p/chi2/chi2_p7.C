{
double x_7[100],y_7[100];
double chi2_7=0;


for(int j=0;j<100;j++){ 
  chi2_7=0; 
  calcP->SetParameter(7,0+0.01*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_7+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    //cout<<"chi2_7"<<" "<<chi2_7<<endl;
    x_7[j]=0+0.01*j;
    y_7[j]=chi2_7;
    }
}
//for(int j=0;j<100;j++){ chi2_7=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2_7+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2_7;}
TGraph gr_7(100,x_7,y_7);
gr_7.Draw("AP");
CC->SaveAs("../../plot/chi2/p7.png");
}
