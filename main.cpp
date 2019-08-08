#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Naming protein chains in file called md1_pymol.pdb "<<endl;

    int numofchains=2;
    if(argc>1)
    {
        numofchains=atoi(argv[1]);
        //numofchains=(int)argv[1];
        if(numofchains<1) numofchains=0;
        cout<<"Number of chains: "<<numofchains<<endl;
        if(numofchains<1)
        {
            cout<<"ERROR: Bad chain number\n\n";
            return 1;
        }
    }
    else
    cout<<"Assumed number of chains: "<<numofchains<<endl;

    ifstream infile("md1_pymol.pdb");
    if(infile==0)
    { cout<<"Error reading file\n"; return 1;}
    ofstream outfile("md1_fix.pdb");
    if(outfile==0)
    { cout<<"Error printing file\n"; return 1;}

    string line;
    vector<string> vec_print_file;
    int counter=0;
    while(getline(infile,line))
    {
        //skip non protein atoms
        if(  (line[0]=='A'&&line[1]=='T'&&line[2]=='O'&&line[3]=='M') &&
             (
             (line[17]=='S'&&line[18]=='O'&&line[19]=='L') ||
             (line[17]==' '&&line[18]=='N'&&line[19]=='A') ||
             (line[17]==' '&&line[18]=='C'&&line[19]=='L')
             ) )
         continue;
        if(line[0]!='A'||line[1]!='T'||line[2]!='O'||line[3]!='M')
         continue;

        switch(counter)
        {
            case 0:  line[21]='A'; break;
            case 1:  line[21]='B'; break;
            case 2:  line[21]='C'; break;
            case 3:  line[21]='D'; break;
            case 4:  line[21]='E'; break;
            case 5:  line[21]='F'; break;
            case 6:  line[21]='G'; break;
            case 7:  line[21]='H'; break;
            case 8:  line[21]='I'; break;
            case 9:  line[21]='J'; break;
            case 10: line[21]='K'; break;
            case 11: line[21]='L'; break;
            case 12: line[21]='M'; break;
            case 13: line[21]='N'; break;
        }
        counter++;
        if(counter>numofchains-1) counter=0;

        vec_print_file.push_back(line);
    }

    //sort
    while(true)
    {
        bool done=true;
        for(int i=0;i<(int)vec_print_file.size()-1;i++)
        {
            if(vec_print_file[i][0]=='A'&&vec_print_file[i][1]=='T'&&vec_print_file[i][2]=='O'&&vec_print_file[i][3]=='M'&&
               vec_print_file[i+1][0]=='A'&&vec_print_file[i+1][1]=='T'&&vec_print_file[i+1][2]=='O'&&vec_print_file[i+1][3]=='M')
             if(vec_print_file[i][21]>vec_print_file[i+1][21])
            {
                done=false;
                string temp=vec_print_file[i];
                vec_print_file[i]=vec_print_file[i+1];
                vec_print_file[i+1]=temp;

                //keep atom number order
                for(int j=4;j<11;j++)
                {
                    char tempc=vec_print_file[i][j];
                    vec_print_file[i][j]=vec_print_file[i+1][j];
                    vec_print_file[i+1][j]=tempc;
                }
            }
        }
        if(done) break;
    }

    //print
    for(int i=0;i<(int)vec_print_file.size();i++)
    {
        outfile<<vec_print_file[i]<<endl;
    }
    outfile<<"TER"<<endl;

    infile.close();
    outfile.close();

    cout<<"Complete: File output in md1_fix.pdb\n\n";
    return 0;
}
