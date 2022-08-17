#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string.h>
#include <queue>
#include <regex>
#include <algorithm>
#include <memory>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

using namespace std;
using namespace Minisat;

std::vector<int> VcoverSAT(int v_num, vector<int>v_edge, int y) {
	Var x[v_num][y];
	Solver s;

	for (int i = 0; i < v_num; i++) {
		for (int j = 0; j < y; j++) {
			x[i][j] = s.newVar();
		}
	}

	for (int i = 0; i < y; i++) {
		vec<Lit> temp;
		
		for (int j = 0; j < v_num; j++) {
			temp.push(mkLit(x[j][i]));
		}

		s.addClause(temp);
		temp.clear();

	}

	for (int i = 0; i < v_num; i++) {
		for (int l = 0; l < y - 1; l++) {
			for (int m = l + 1; m < y; m++) {
				s.addClause(mkLit(x[i][l], true), mkLit(x[i][m], true));
			}
		}
	}
	for (int i = 0; i < y; i++){
		for (int l = 0; l < v_num - 1; l++) {
			for (int m = l + 1; m < v_num; m++) {
				s.addClause(mkLit(x[l][i], true), mkLit(x[m][i], true));
			}
		}
	}
	for (int i = 0; i < v_edge.size(); i++){	
		vec<Lit> temp;
		for (int l = 0; l < y; l++){
			temp.push(mkLit(x[v_edge[i]][l]));

			temp.push(mkLit(x[v_edge[i+1]][l]));
		}
		s.addClause(temp);
		temp.clear();
		i++;
	}

	std::vector<int> v_cover;
	if (s.solve()) {

		for (int i = 0; i < v_num; i++){
			for (int j = 0; j < y; j++){
				if (toInt(s.modelValue(x[i][j])) == 0){
					v_cover.push_back(i);
				}
			}
		}

		return v_cover;
	}
	else {
		return { -1 };
	}
}

void vertex_cover(int v_num, vector<int>edge) {
	Solver s;

	vector<int> ret_val;
	vector<int> final_val;

	int n = v_num;

	vector<int> vec_edge = edge;

	int max = v_num;
	int min = 1;
	vector<int> tmp = { -1 };

	while (max >= min) {
		int mid = (max + min) / 2;

		ret_val = VcoverSAT(n, vec_edge, mid);

		bool unsat = std::equal(ret_val.begin(), ret_val.end(), tmp.begin());
		if (not unsat) {
			max = mid - 1;
			final_val.clear();
			final_val = ret_val;
		}
		else {
			min = mid + 1;
		}

	}
	sort(final_val.begin(), final_val.end());

	for (int i = 0; i < final_val.size(); ++i) {
		cout << final_val[i] << " ";
	}
	cout << endl;

}


int main(int argc, char** argv) {
    int v=1;
    int flag=0;
    vector<int> edges;    
    while(!std::cin.eof()){
        std::string line;
        std::getline(std::cin,line);
        regex expr("-?[0-9]+"); //match consectuive numbers
        sregex_iterator next(line.begin(), line.end(), expr);
        sregex_iterator end;
        
        if (line.empty()){
            continue;
        }
        if (line[0] == 'V' && line[1] == ' '){
            v = stoi(line.substr(2));
            v=v+1;
        }
	    if (line[0]=='E' && line[2]=='{' && line[3]=='}')
	    {
	        cout<<endl;
	        continue;
	    }
        if (line[0] == 'E' && line[1] == ' '){
            while (next != end) {
                smatch var1;
                smatch var2;
                var1 = *next;
                next++;
                if (next != end) {
                    var2 = *next;
                    int e0 = std::stoi(var1.str());
                    int e1 = std::stoi(var2.str());		    
                    if (e0>=v or e1>=v or e0<0 or e1<0 or e0==e1){
                        flag=0;
                        std::cout << "Error: edges entered are not valid." << endl;
                        break;
                    }
		            else
		            {
		                flag=1;
		                edges.push_back(e0);
		                edges.push_back(e1);
                        next++;
		            }
            }
        }
        if (flag==1){
	        vertex_cover(v,edges);
            edges.clear();
        }
        }

    }

  return 0;
}

