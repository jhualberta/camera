{
double number[100];
double xm[100];
double ym[100];
int ip;


	//read the corresponding pixal location
	ifstream myReadFile2;
	myReadFile2.open("av_pos_r.txt");
	std::string linep;
	getline(myReadFile2,linep);
	ip=0;
	if (myReadFile2.is_open()) {
	while (!myReadFile2.eof()) {

   	myReadFile2 >> number[ip] >> xm[ip] >> ym[ip];
   	//cout<<number[im]<<" "<<xm[im]<<" "<<ym[im]<<endl;
   	ip++;
	}	
	}
	myReadFile2.close();


   //send the parameters out2
   ofstream out2("av_pos.txt");
   for(int i=0;i<(sizeof(number)/sizeof(number[0]));i++){
    if(number[i]==0)break;
    out2<<number[i]<<" "<<xm[i] -1434 <<" "<<-ym[i] + 2155<<endl;
   }
}
