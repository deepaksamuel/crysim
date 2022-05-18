#include <TFile.h>
#include <TTree.h>

int readOutput()
{
    TFile *f= new TFile("output.root");
    TTree *cry_data= (TTree*)f->Get("events");
    double event;
    double x,y,z,t,px,py,pz;
    double pid,entries;

    cry_data->SetBranchAddress("event",&event);
    cry_data->SetBranchAddress("x",&x);
    cry_data->SetBranchAddress("y",&y);
    cry_data->SetBranchAddress("z",&z);
    cry_data->SetBranchAddress("px",&px);
    cry_data->SetBranchAddress("py",&py);
    cry_data->SetBranchAddress("pz",&pz);
    cry_data->SetBranchAddress("id",&pid);
    cry_data->SetBranchAddress("t",&t);

    TString tt;
    TEventList *elist; 
    cout<<"Entries in tree:"<< cry_data->GetEntries()<<endl;

    // cry_data->GetEntries()
    for(int i=0; i<60;i++)
    {   
        tt.Form("event==%u &&id==13",i);
        // cout<<t<<endl;
        // cry_data->GetEntry(i);
        
        entries=cry_data->Draw(">>event",tt);
        elist = (TEventList*)gDirectory->Get("event");
        
        if(elist==NULL)
        cout<<"Error in pointer"<<endl;
        
        else{
        cry_data->SetEventList(elist);  
        // cry_data->GetEntry(elist->GetEntry(0));
        cout<<i<<" "<<entries<<endl;
        cry_data->SetEventList(0); //reset the entry list
        }

    }
    return 0;
}

