#include "TH2D.h"
#include "TH1D.h"
#include "stdio.h"

void readpic(int irun=0){
  TH2D *r,*g,*b;
  TH1D *h,*hct,*hct3;
  r=NULL;
  FILE *inp=fopen("../picture/cPmiddle.ppm","r");
  int height, width,max;
  fscanf(inp,"P6 %d %d %d",&width,&height,&max);
  fgetc(inp);
    if(r==NULL){
      r=new TH2D("hR","Red",width,0,width,height,0,height);
      g=new TH2D("hG","Green",width,0,width,height,0,height);
      b=new TH2D("hB","Blue",width,0,width,height,0,height);
      h=new TH1D("hDist","Dist",60000,0,60000);
      hct=new TH1D("hDistCt","Dist Cos Theta corrected",60000,0,60000);
      hct3=new TH1D("hDistCt3","Dist Cos Theta cubed corrected",60000,0,60000);
   }
    h->Reset();
    hct->Reset(); hct3->Reset();
    int i,j;
    unsigned short *row=new unsigned short[3*width];
    //unsigned char *row=new unsigned char[3*width];
    for(i=height-1;i>=0;i--){
      fread(row,6,width,inp);
      for(j=0;j<width;j++){ 
	int val;
      val=((row[j*3]<<8)|(row[j*3]>>8))&0xffff;
      
      //     if(i%1000==0 && j%1000==0)printf("%d %d %d\n",i,j,val);
      r->SetBinContent(j,i,val);
      val=((row[1+j*3]<<8)|(row[1+j*3]>>8))&0xffff;
      g->SetBinContent(j,i,val);
      val=((row[2+j*3]<<8)|(row[2+j*3]>>8))&0xffff;
      //      val=row[2+j*3];
      b->SetBinContent(j,i,val);
      h->Fill(val);
      float theta=atan(sqrt((j-3017)*(j-3017)+(i-2014)*(i-2014))/9942.0);
      float ct=cos(theta);
      hct->Fill(val/ct);
      hct3->Fill(val/(ct*ct*ct));
      }
    }
    delete[] row;
    fclose(inp);
    h->GetXaxis()->SetRangeUser(8000,60000);
    hct->GetXaxis()->SetRangeUser(8000,60000);
    hct3->GetXaxis()->SetRangeUser(8000,60000);
    //printf("%s %10.0f %f %10.0f %f %10.0f %f\n",h->Integral(),h->GetMean(),hct->Integral(), hct->GetMean(),hct3->Integral(),hct3->GetMean());
     //h->Draw();
    //r->SetMarkerColor(kRed);
    //g->SetMarkerColor(kGreen);
    //b->SetMarkerColor(kBlue); 
    //r->SetMarkerSize(1e-15);  

    //g->SetMarkerSize(1e-15);
    //b->SetMarkerSize(1e-15); 
    r->Draw("colz");
    //g->Draw("SAME");
    //b->Draw("SAME");
    //c1->SaveAs("../plot/read.pdf");

}

