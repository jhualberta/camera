{
double x_11[100],y_11[100];
double chi2_11=0;


for(int j=0;j<100;j++){ 
  chi2_11=0; 
  calcP->SetParameter(11,0+0.01*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_11+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    //cout<<"chi2_11"<<" "<<chi2_11<<endl;
    x_11[j]=0+0.01*j;
    y_11[j]=chi2_11;
    }
}
//for(int j=0;j<100;j++){ chi2_11=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2_11+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2_11;}
TGraph gr_11(100,x_11,y_11);
gr_11.Draw("AP");
CC->SaveAs("../../plot/chi2/p11.png");
}
