
#include <iostream>
#include <vector>
#include <algorithm>
bool isSafe(const std::vector<std::vector<int>>& allocation,
            const std::vector<std::vector<int>>& request,
            const std::vector<int>& available,std::vector<int>& safeSequence);

bool requestResources(std::vector<std::vector<int>>& allocation,
                      std::vector<std::vector<int>>& request,
                      std::vector<int>& available,
                      int processID,
                      const std::vector<int>& requestAmount,std::vector<std::string>& procesi);



int main()
{
    int num_proc;
    std::cout<<"Unesite broj procesa:";
    std::cin>>num_proc;
    //std::cout<<"Hvala";
    std::vector<std::string> procesi;
    std::cout<<"Unesite imena procesa: ";
    for(int i=0;i<num_proc;i++)
    {
        //std::cout<<"Unesite ime "<<i+1<<". procesa: ";
        std::string name;
        std::cin>>name;
        //std::cout<<name<<std::endl;
        procesi.push_back(name);
    }
    std::cout<<"Unesite broj resursa ";
    int num_res;
    std::cin>>num_res;
    int j=0;
    std::vector<std::string> resursi;
    std::vector<int> instance;
    while(j<num_res)
    {
        std::cout<<"Unesite ime "<<j+1<<". resursa: ";
        std::string name;
        std::cin>>name;
        std::cout<<"Unesite instance "<<name<<" resursa: ";
        int in;
        std::cin>>in;
        
        resursi.push_back(name);
        instance.push_back(in);
        j++;
    }

    std::vector<int> raspolozivost;
    for(int i=0;i<num_res;i++)
    {
        std::cout<<"Unesite broj raspolozivih instanci "<<resursi[i]<<" resursa: ";
        int ras;
        std::cin>>ras;
        raspolozivost.push_back(ras);
    }
    std::cout<<"Unesite matricu alokacije: "<<std::endl;
    std::vector<std::vector<int>> matrica_alokacije (num_proc, std::vector<int>(num_res,0));
    for(int i=0;i<num_proc;i++)
        for(int j=0;j<num_res;j++)
        {
            int l;
            std::cin>>l;
            matrica_alokacije[i][j]=l;
        }
    std::cout<<"Unesite matricu maksimalnih zahtjeva: "<<std::endl;
    std::vector<std::vector<int>> matrica_maks_zah (num_proc, std::vector<int>(num_res,0));
    for(int i=0;i<num_proc;i++)
        for(int j=0;j<num_res;j++)
        {
            int l;
            std::cin>>l;
            matrica_maks_zah[i][j]=l;
        }
     std::vector<std::vector<int>> matrica_potreba(num_proc, std::vector<int>(num_res));

    
    for (int i = 0; i < num_proc; ++i) {
        for (int j = 0; j < num_res; ++j) {
            matrica_potreba[i][j] = matrica_maks_zah[i][j] - matrica_alokacije[i][j];
        }
    }
    std::cout<<"Unesite broj zahtjeva: ";
    int br_zah;
    std::cin>>br_zah;
    std::cout<<"Unesite listu zahtjeva: "<<std::endl;
    std::vector<std::vector<int>> zahtjevi;
    std::vector<int> id_zahtjeva; 
    for(int i=0;i<br_zah;i++)
    {
        std::string tp;
        std::cin>>tp;
        auto it = std::find(procesi.begin(), procesi.end(), tp);
        int index = std::distance(procesi.begin(), it);
        id_zahtjeva.push_back(index);
        int k=0;
        std::vector<int> zahh;
        for(int j=0;j<num_res;j++)
        {
            
            std::cin>>k;
            zahh.push_back(k);
        }
        zahtjevi.push_back(zahh);
        
    }


    
    

    

    std::cout<<"================================================================="<<std::endl;
    std::cout<<"                    REZULTATI IZVRSAVANJA                           "<<std::endl;

    std::cout<<"Matrica potreba: "<<std::endl;
    for (const auto& row : matrica_potreba) {
        for (int elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
    
    std::vector<int> sigurna;
    if(isSafe(matrica_alokacije,matrica_potreba,raspolozivost,sigurna))
    {
        std::cout << "Sistem je u stabilnom stanju: (";
    /*for (int i : sigurna) {
        std::cout << procesi[i] << "->";
    }*/
   for(int i=0;i<(sigurna.size()-1);i++)
   {
    std::cout<<procesi[sigurna[i]]<<"->";
   }
    std::cout<<procesi[sigurna[sigurna.size()-1]];
    std::cout <<")"<< std::endl;
    }
    else
    {
        std::cout<<"Sistem nije u stabilnom stanju!"<<std::endl;
    }
    
    for(int i=0;i<br_zah;i++)
    {
        requestResources(matrica_alokacije,matrica_potreba,raspolozivost,id_zahtjeva[i],zahtjevi[i],procesi);
    }
    return 0;
}

bool isSafe(const std::vector<std::vector<int>>& allocation,
            const std::vector<std::vector<int>>& request,
            const std::vector<int>& available,std::vector<int>& safeSequence) {
    int numProcesses = allocation.size();
    int numResources = available.size();

    std::vector<int> work = available;
    std::vector<bool> finish(numProcesses, false);
    
    while (safeSequence.size() < numProcesses) {
        bool progressMade = false;

        for (int i = 0; i < numProcesses; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;

                for (int j = 0; j < numResources; ++j) {
                    if (request[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int k = 0; k < numResources; ++k) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    safeSequence.push_back(i);
                    progressMade = true;
                }
            }
        }

        if (!progressMade) {
            return false;
        }
    }

    

    return true;
}


bool requestResources(std::vector<std::vector<int>>& allocation,
                      std::vector<std::vector<int>>& request,
                      std::vector<int>& available,
                      int processID,
                      const std::vector<int>& requestAmount,std::vector<std::string>& procesi) {
    int numResources = available.size();
    
    std::vector<std::vector<int>> allocationc=allocation;
    std::vector<std::vector<int>> requestc=request;
    std::vector<int> availablec=available;
    for (int i = 0; i < numResources; ++i) {
        if (requestAmount[i] > request[processID][i]) {
            std::cout << "Zahtjev (" << procesi[processID]<< ", ";
            for(int i=0;i<requestAmount.size()-1;i++)
            {
                std::cout<<requestAmount[i]<<", ";
            }
            std::cout<<requestAmount[requestAmount.size()-1];
            std::cout<<") nece biti odobren"<<std::endl;
            return false;
        }
    }

    
    for (int i = 0; i < numResources; ++i) {
        if (requestAmount[i] > available[i]) {
            std::cout << "Zahtjev (" << procesi[processID]<< ", ";
            for(int i=0;i<requestAmount.size()-1;i++)
            {
                std::cout<<requestAmount[i]<<", ";
            }
            std::cout<<requestAmount[requestAmount.size()-1];
            std::cout<<") nece biti odobren"<<std::endl;
            return false;
        }
    }

    
    for (int i = 0; i < numResources; ++i) {
        availablec[i] -= requestAmount[i];
        allocationc[processID][i] += requestAmount[i];
        requestc[processID][i] -= requestAmount[i];
    }
    std::vector<int> sigurna;
    
    if (isSafe(allocationc, requestc, availablec,sigurna)) {
        std::cout << "Zahtjev (" << procesi[processID]<< ", ";
            for(int i=0;i<requestAmount.size()-1;i++)
            {
                std::cout<<requestAmount[i]<<", ";
            }
            std::cout<<requestAmount[requestAmount.size()-1];
            std::cout<<") ce biti odobren"<<std::endl;
        return true;
    } else {
        
        for (int i = 0; i < numResources; ++i) {
            availablec[i] += requestAmount[i];
            allocationc[processID][i] -= requestAmount[i];
            requestc[processID][i] += requestAmount[i];
        }
        std::cout << "Zahtjev (" << procesi[processID]<< ", ";
            for(int i=0;i<requestAmount.size()-1;i++)
            {
                std::cout<<requestAmount[i]<<", ";
            }
            std::cout<<requestAmount[requestAmount.size()-1];
            std::cout<<") nece biti odobren"<<std::endl;
        return false;
    }
}