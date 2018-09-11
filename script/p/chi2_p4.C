{
double x_4[100],y_4[100];
double chi2_4=0;


for(int j=0;j<100;j++){ 
  chi2_4=0; 
  calcP->SetParameter(4,0+0.1*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_4+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    //cout<<"chi2_4"<<" "<<chi2_4<<endl;
    x_4[j]=0+0.1*j;
    y_4[j]=chi2_4;
    }
}
//for(int j=0;j<100;j++){ chi2_4=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2_4+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2_4;}
TGraph gr_4(100,x_4,y_4);
gr_4.Draw("AP");
CC->SaveAs("../../plot/chi2/p4.png");
}
