{
double x_3[100],y_3[100];
double chi2_3=0;


for(int j=0;j<100;j++){ 
  chi2_3=0; 
  calcP->SetParameter(3,0.2+0.001*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_3+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    //cout<<"chi2"<<" "<<chi2_3<<endl;
    x_3[j]=0.2+0.001*j;
    y_3[j]=chi2_3;
    }
}
//for(int j=0;j<100;j++){ chi2=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2;}
TGraph gr3(100,x_3,y_3);
gr3.Draw("AP");
CC->SaveAs("../../plot/chi2/p3.png");
}
