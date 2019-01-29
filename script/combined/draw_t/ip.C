//Create a 2-D histogram from an image.
//Author: Olivier Couet


{
gStyle->SetOptStat("n");
   TASImage image("../../../picture/cPmiddle.ppm");
   UInt_t yPixels = image.GetHeight();
   UInt_t xPixels = image.GetWidth();
   UInt_t *argb   = image.GetArgbArray();

   TH2D* h = new TH2D("h","histogram",xPixels,-2155,2155,yPixels,-1434,1434);

   for (int row=0; row<xPixels; ++row) {
      for (int col=0; col<yPixels; ++col) {
         int index = col*xPixels+row;
         float grey = float(argb[index]&0xff)/256;
         h->SetBinContent(row+1,yPixels-col,grey);
      }
   }

   gStyle->SetPalette(53);
   h->Draw("colz");
}
