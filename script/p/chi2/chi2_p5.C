{
double x_5[100],y_5[100];
double chi2_5=0;


for(int j=0;j<100;j++){ 
  chi2_5=0; 
  calcP->SetParameter(5,-0.05+0.001*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_5+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    //cout<<"chi2_5"<<" "<<chi2_5<<endl;
    x_5[j]=-0.05+0.001*j;
    y_5[j]=chi2_5;
    }
}
//for(int j=0;j<100;j++){ chi2_5=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2_5+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2_5;}
TGraph gr_5(100,x_5,y_5);
gr_5.Draw("AP");
CC->SaveAs("../../plot/chi2/p5.png");
}
