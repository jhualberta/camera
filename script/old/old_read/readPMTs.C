{
std::vector<TVector3>pmtList;	
FILE *stream=fopen("../data/database20040923b.dat","r");
char *line=NULL;
size_t len=0;
int r=getline(&line,&len,stream);
r=getline(&line,&len,stream);
for(int iline=0;r>0;iline++){
  r=getline(&line,&len,stream);
  if(r==0)continue;
  if (TString(line,4)==TString("EOHV"))break;
  if(line[0]=='E'){
    double x=TString(line+31,8).Atof();
    double y=TString(line+40,8).Atof();
    double z=TString(line+49,8).Atof();
    pmtList.push_back(TVector3(x,y,z));
  }
}
}

