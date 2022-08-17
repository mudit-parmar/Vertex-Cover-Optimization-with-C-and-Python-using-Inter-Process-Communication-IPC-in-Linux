#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <limits>
#include <algorithm>

using namespace std;

int get_random_number(int min_val, int max_val){
    std::ifstream urandom("/dev/urandom");
    unsigned int num;
    urandom.read((char *) &num, sizeof(num));
    urandom.close();

    if (min_val==max_val){
        return min_val;
    }else{
        int rand_num = (num%(max_val-min_val+1));
        rand_num = rand_num+min_val;
        return rand_num;
    }
}

bool zero_length(vector<int> point1, vector<int> point2){
    int x1 = point1[0], y1 = point1[1], x2 = point2[0], y2 = point2[1];
    return x1==x2 and y1==y2;
}

bool on_line(vector<int>point_l1, vector<int>point_l2,vector<double>point_i){
    int min_x,max_x,min_y,max_y;
    if(point_l2[0]>point_l1[0]){
        max_x=point_l2[0];
        min_x=point_l1[0];
    }
    else{
        max_x=point_l1[0];
        min_x=point_l2[0];
    }
        
    if(point_l2[1]>point_l1[1]){
        max_y=point_l2[1];
        min_y=point_l1[1];
    }
    else{
        max_y=point_l1[1];
        min_y=point_l2[1];    
    }
        
    if ((min_x<=point_i[0])&&(point_i[0]<=max_x)&&(min_y<=point_i[1])&&(point_i[1]<=max_y)){
        return true;
    }else{
        return false;
    }
}

bool check_overlap(vector<int> p1, vector<int> p2, vector<int> p3, vector<int> p4){
    int x1, y1, x2, y2, x3, y3, x4, y4;

    if (p1[0]==p2[0] && p3[0]==p4[0] && p1[0]==p3[0]){
        if (p1[1]<p2[1]){
            y1 = p1[1], y2 = p2[1];
        }else{
            y1 = p2[1], y2 = p1[1];
        }
        if (p3[1]<p4[1]){
            y3 = p3[1], y4 = p4[1];
        }else{
            y3 = p4[1], y4 = p3[1];
        }

        if ((y1<=y3&&y3<y2)||(y1<y4&&y4<=y2)||(y3<=y1&&y1<y4)||(y3<y2&&y2<=y4)){
            return true;
        }
    }

    if (p1[0] != p2[0] and p3[0] != p4[0]){
        if (p1[0]< p2[0]){
            x1=p1[0], y1=p1[1], x2=p2[0], y2=p2[1];
        }else{
            x1=p2[0], y1=p2[1], x2=p1[0], y2=p1[1];
        }
        if (p3[0]<p4[0]){
            x3=p3[0], y3=p3[1], x4=p4[0], y4=p4[1];
        }else{
            x3=p4[0], y3=p4[1], x4=p3[0], y4=p3[1];
        }
        double n1=(y2-y1);
        n1 = n1/(x2-x1);
        double n2=(y4-y3);
        n2 = n2/(x4-x3);
        double m1=(x2*y1-x1*y2);
        m1 = m1/(x2-x1);
        double m2=(x4*y3-x3*y4);
        m2 = m2/(x4-x3);
        if (n1 == n2 && m1 == m2){
            if((x1<=x3&&x3<x2)||(x1<x4&&x4<=x2)||(x3<=x1&&x1<x4)||(x3<x2&&x2<=x4)){
                return true;
            }
        }
    }
    return false;
}

bool intersect(vector<int> p1, vector<int> p2, vector<int> p3, vector<int> p4){
    int x1=p1[0], y1=p1[1], x2=p2[0], y2=p2[1];
    int x3=p3[0], y3=p3[1], x4=p4[0], y4=p4[1];

    if (p1[0]==p2[0] and p3[0]!=p4[0]){
        double n2 = (y4-y3);
        n2 = n2/(x4-x3);
        double m2 = (x4*y3-x3*y4);
        m2 = m2/(x4-x3);

        double y_ist = n2*x1 + m2;
        vector<double> intersection;
        intersection.push_back(x1);
        intersection.push_back(y_ist);
        if ((on_line(p1,p2,intersection)) and (on_line(p3,p4,intersection))){
            return true;
        }
    }
    if (p3[0]==p4[0] and p1[0]!=p2[0]){
        double n1=(y2-y1);
        n1=n1/(x2-x1);
        double m1=(x2*y1-x1*y2);
        m1=m1/(x2-x1);

        double y_ist = n1*x3 + m1;
        vector<double> intersection;
        intersection.push_back(x3);
        intersection.push_back(y_ist);
        if ((on_line(p3,p4,intersection)) and (on_line(p1,p2,intersection))){
            return true;
        }
    }
    if (p1[0]!=p2[0] and p3[0]!=p4[0]){
        double n1=(y2-y1);
        n1=n1/(x2-x1);
        double m1=(x2*y1-x1*y2);
        m1=m1/(x2-x1);
        double n2=(y4-y3);
        n2=n2/(x4-x3);
        double m2=(x4*y3-x3*y4);
        m2=m2/(x4-x3);

        if (n1!=n2){
            double x_ist=(m2-m1);
            x_ist = x_ist/(n1-n2);
            double y_ist=(n1*m2-n2*m1);
            y_ist = y_ist/(n1-n2);

            vector<double> intersection;
            intersection.push_back(x_ist);
            intersection.push_back(y_ist);

            if ((on_line(p1,p2,intersection)) and (on_line(p3,p4,intersection))){
                return true;
            }
        }
    }
    return false;
}


int main(int argc, char *argv[]){
    int option;

    string s_string, n_string, l_string, c_string;
    int s = 10;
    int n = 5;
    int l = 5;
    int c = 20;

    while((option=getopt(argc,argv,"s:n:l:c:")) != -1){
        switch (option) {
            case 's':
                s_string=optarg;
                s = atoi(s_string.c_str());
                break;

            case 'n':
                n_string=optarg;
                n = atoi(n_string.c_str());
                break;

            case 'l':
                l_string=optarg;
                l = atoi(l_string.c_str());
                break;

            case 'c':
                c_string=optarg;
                c = atoi(c_string.c_str());
                break;

        }
    }

    vector<string> sList;
    while(1){
        int st_temp = 1;
        int s_num = get_random_number(2,s); // # of the streets
        int l_num = get_random_number(5,l); // # of seconds to wait
        vector< vector< vector<int> > > graph;


        while (st_temp <= s_num) {
            int n_num = get_random_number(1, n); // # of line segments in a street
            vector<vector<int>> street;

            int n_temp = 1;
            while (n_temp <= n_num + 1) {
                vector<int> point_temp;

                point_temp.push_back(get_random_number(-c, c));
                point_temp.push_back(get_random_number(-c, c));

                if (!street.empty()) {
                    int f1 = 0, f2 = 0, f3 = 0, f4 = 0;
                    int count = 0;
                    while (f1 == 0 || f2 == 0 || f3 == 0 || f4 == 0) {
                        count += 1;
                        if (count > 25) {
                            cerr << "Error: failed to generate valid input for 25 simultaneous attempts. \n";
                            exit(1);
                        }
                        point_temp[0] = get_random_number(-c, c);
                        point_temp[1] = get_random_number(-c, c);

                        if (!zero_length(point_temp, street.back())) {
                            f1 = 1;
                        } else {
                            f1 = 0;
                        }

                        int f22 = 0;
                        if (street.size() > 1) {
                            for (unsigned int i = 0; i < street.size() - 1; i++) {
                                if (check_overlap(street[i], street[i + 1], street.back(), point_temp)) {
                                    f22 = 1;
                                }
                            }
                        }
                        if (f22 == 1) {
                            f2 = 0;
                        } else {
                            f2 = 1;
                        }

                        int f33 = 1;
                        if (graph.size() > 1) {
                            for (unsigned int i = 0; i < graph.size() - 1; i++) {
                                for (unsigned int j = 0; j < graph[i].size() - 1; j++) {
                                    if (check_overlap(graph[i][j], graph[i][j + 1], street.back(),
                                                                 point_temp)) {
                                        f33 = 0;
                                    }
                                }
                            }
                        }
                        if (f33 != 0) {
                            f3 = 1;
                        } else {
                            f3 = 0;
                        }

                        int f44 = 0;

                        if (street.size() > 2) {
                            for (unsigned int i = 0; i < street.size() - 2; i++) {
                                if (intersect(street[i], street[i + 1], street.back(),
                                                               point_temp)) {
                                    f44 = 1;
                                }
                            }
                        }
                        if (f44 == 1) {
                            f4 = 0;
                        } else {
                            f4 = 1;
                        }
                    }
                }
                street.push_back(point_temp);
                n_temp++;
            }

            graph.push_back(street);
            st_temp++;
        }

        for(unsigned int i=0; i<graph.size(); i++){
            sList.push_back("street " + to_string(i+1));
            cout << "add \"street " << i+1 << "\"";
            for (unsigned int j=0; j<graph[i].size(); j++){
                cout << " (" << graph[i][j][0] << "," << graph[i][j][1] << ")";
            }
            cout << endl;
        }

        cout << "gg" << endl;

        sleep(l_num);

        if (!sList.empty()){
            for (unsigned int i=0; i<sList.size();i++){
                cout << "rm \"" << sList[i] << "\"" << endl;
            }
        }
        sList.clear();
    }
    return 0;
}