#include <TFile.h>
#include <TTree.h>

int readfile()
{
    TFile *f= new TFile("test.root");
    TTree *cry_data= (TTree*)f->Get("cry_data");
    uint nEvents,nSec,n;
    double KE,x,y,z,u,v,w;
    int entries;

    cry_data->SetBranchAddress("n",&n);
    cry_data->SetBranchAddress("nEvents",&nEvents);
    cry_data->SetBranchAddress("nSec",&nSec);
    cry_data->SetBranchAddress("KE",&KE);
    cry_data->SetBranchAddress("x",&x);
    cry_data->SetBranchAddress("y",&y);
    cry_data->SetBranchAddress("z",&z);
    cry_data->SetBranchAddress("u",&u);
    cry_data->SetBranchAddress("v",&v);
    cry_data->SetBranchAddress("w",&w);
    TString t;
    TEventList *elist; 
    // cry_data->GetEntries()
    for(int i=0; i<60;i++)
    {   
        t.Form("n==%u",i);
        entries=cry_data->Draw(">>event",t);
        elist = (TEventList*)gDirectory->Get("event");
        
        if(elist==NULL)
        cout<<"Error in pointer"<<endl;
        
        else{
        cry_data->SetEventList(elist);  
        // cout<<i<<" "<<entries<<endl;
        cry_data->GetEntry(elist->GetEntry(0));
        cout<<n<<endl;
        cry_data->SetEventList(0); //reset the entry list
        }

    }
    return 0;
}

