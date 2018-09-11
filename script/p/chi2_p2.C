{
double x_2[100],y_2[100];
double chi2_2=0;


for(int j=0;j<100;j++){ 
  chi2_2=0; 
  calcP->SetParameter(2,4000+20*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_2+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    //cout<<"chi2"<<" "<<chi2_2<<endl;
    x_2[j]=4000+20*j;
    y_2[j]=chi2_2;
    }
}
//for(int j=0;j<100;j++){ chi2=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2;}
TGraph gr2(100,x_2,y_2);
gr2.Draw("AP");
CC->SaveAs("../../plot/chi2/p2.png");
}
