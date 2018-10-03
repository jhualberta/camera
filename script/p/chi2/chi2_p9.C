{
double x_9[100],y_9[100];
double chi2_9=0;


for(int j=0;j<100;j++){ 
  chi2_9=0; 
  calcP->SetParameter(9,0+0.01*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_9+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    //cout<<"chi2_9"<<" "<<chi2_9<<endl;
    x_9[j]=0+0.01*j;
    y_9[j]=chi2_9;
    }
}
//for(int j=0;j<100;j++){ chi2_9=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2_9+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2_9;}
TGraph gr_9(100,x_9,y_9);
gr_9.Draw("AP");
CC->SaveAs("../../plot/chi2/p9.png");
}
