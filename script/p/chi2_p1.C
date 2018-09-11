{
double x_1[100],y_1[100];
double chi2_1=0;


for(int j=0;j<100;j++){ 
  chi2_1=0; 
  calcP->SetParameter(1,2000+10*j);
  for(int i=0;i<h1->GetNbinsX();i++){
    chi2_1+=TMath::Power(calcP->Eval(i)-h1->GetBinContent(i+1),2);
    //cout<<"chi2"<<" "<<chi2_1<<endl;
    x_1[j]=2000+10*j;
    y_1[j]=chi2_1;
    }
}
//for(int j=0;j<100;j++){ chi2=0; calcP->SetParameter(6,1900+2*j);for(int i=0;i<h1->GetNbinsX();i++)chi2+=pow(calcP->Eval(i)-h1->GetBinContent(i+1),2);x[j]=1900+2*j;y[j]=chi2;}
TGraph gr1(100,x_1,y_1);
gr1.Draw("AP");
CC->SaveAs("../../plot/chi2/p1.png");
}
