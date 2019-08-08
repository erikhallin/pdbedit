#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Naming protein chains in file called prot.pdb "<<endl;



    ifstream infile("prot.pdb");
    if(infile==0)
    { cout<<"Error reading file\n"; return 1;}
    ofstream outfile("prot_fix.pdb");
    if(outfile==0)
    { cout<<"Error printing file\n"; return 1;}

    string line;
    vector<string> vec_print_file;
    int counter=0;
    while(getline(infile,line))
    {
        if(line[0]=='T'&&line[1]=='E'&&line[2]=='R'&&line[3]==' ')
        {
            counter++;
            continue;
        }
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
            case 0: line[21]='A'; break;
            case 1: line[21]='B'; break;
            case 2: line[21]='C'; break;
            case 3: line[21]='D'; break;
            case 4: line[21]='E'; break;
            case 5: line[21]='F'; break;
            case 6: line[21]='G'; break;
            case 7: line[21]='H'; break;
            case 8: line[21]='I'; break;
            case 9: line[21]='J'; break;
            case 10: line[21]='K'; break;
            case 11: line[21]='L'; break;
            case 12: line[21]='M'; break;
            case 13: line[21]='N'; break;
        }

        vec_print_file.push_back(line);
    }

    //sort


    //print
    for(int i=0;i<(int)vec_print_file.size();i++)
    {
        outfile<<vec_print_file[i]<<endl;
    }
    outfile<<"TER"<<endl;

    infile.close();
    outfile.close();

    cout<<"Complete: File output in prot_fix.pdb\n\n";
    return 0;
}
