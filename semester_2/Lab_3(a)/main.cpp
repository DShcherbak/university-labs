#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Point{
    double x,y,z;
    double dist;

    Point(int _x = 0, int _y = 0, int _z = 0){
        x = _x;
        y = _y;
        z = _z;
        dist = sqrt(x*x+y*y+z*z);
    }
};

bool operator <(Point a, Point b){
    if(a.dist < b.dist)
        return true;
    else if (a.dist > b.dist)
        return false;
    else{
        if(a.x < b.x)
            return true;
        else if(a.x > b.x)
            return false;
        else{
            return a.y < b.y;
        }
    }
}


bool operator >(Point a, Point b){
    if(a.dist > b.dist)
        return true;
    else if (a.dist < b.dist)
        return false;
    else{
        if(a.x > b.x)
            return true;
        else if(a.x < b.x)
            return false;
        else{
            return a.y > b.y;
        }
    }
}

std::ostream& operator<<(std::ostream& os, Point& p)
{
    os << "({" << p.x << ", " << p.y << ", " << p.z << "}; " << p.dist << ')';
    return os;
}

void print(const std::vector<Point> &a){
    for(auto t:a) std::cout << t << " ";
    std::cout << std::endl;
}

void print(const std::vector<int> &a){
    for(auto t:a) std::cout << t << " ";
    std::cout << std::endl;
}

void insert_sort(std::vector<Point> &a,int left, int right){
    int id_max;
    for(int i = right+1; i > left; i--){
        id_max = left;
        for(int j = left; j < i; j++){
            if(a[id_max] < a[j])
                id_max = j;
        }
        std::swap(a[id_max], a[i-1]);
        print(a);
    }
}

int divide(std::vector<Point> &a,int left, int right){
    int middle = left;
    int l = left-1, r = right+1;
    while(l < r){
        do{
            l++;
        }while(a[l] < a[middle]);
        do{
            r--;
        }while(a[r] > a[middle]);
        if(l >= r)
            return r;
        std::swap(a[l],a[r]);

    }
}

void quicksort(std::vector<Point> &a,int left, int right){
    int middle = 0;
    if(left < right){
        middle = divide(a,left,right);

        quicksort(a,left,middle);
        quicksort(a,middle+1,right);

    }
    print(a);
}

void merge(std::vector <Point> &a, int l1, int r1, int l2, int r2){
    std::vector<Point> b;
    int p1 = r1, p2 = r2;
    int cnt = r2-l1+1;
    b.resize(cnt--);
    while(cnt >= 0){
        if(p2 < l2)
            b[cnt--] = a[p1--];
        else if(p1 < l1)
            b[cnt--] = a[p2--];
        else if (a[p1] > a[p2])
            b[cnt--] = a[p1--];
        else
            b[cnt--] = a[p2--];
    }

    for(int i = 0; i <= r2-l1; i++)
        a[l1+i] = b[i];
}

void merge_sort(std::vector <Point> &a, int left, int right){
    if(left >= right) return;
    int middle = (left+right)>>1;
    merge_sort(a,left,middle);
    merge_sort(a,middle+1,right);
    merge(a,left,middle,middle+1,right);
    print(a);
}

void frankenstein_sort(std::vector <Point> &a, int left, int right, int threshold){
    if(right-left < threshold){
        insert_sort(a,left,right);
        return;
    }
    int middle = (left+right)>>1;
    frankenstein_sort(a,left,middle,threshold);
    frankenstein_sort(a,middle+1,right,threshold);
    merge(a,left,middle,middle+1,right);

}

int main() {
    std::vector <Point> a = {*(new Point(5,0,0)),*(new Point(0,3,0)),*(new Point(0,0,4)),};
    std::vector <Point> b = {*(new Point(10,0,0)),*(new Point(1,0,0)),*(new Point(8,0,0)),*(new Point(3,0,0)),
                           *(new Point(6,0,0)),*(new Point(5,0,0)),*(new Point(4,0,0)),*(new Point(7,0,0)),*(new Point(2,0,0)),*(new Point(9,0,0))};
    std::vector <Point> c = {*(new Point(10,0,0)),*(new Point(1,0,0)),*(new Point(8,0,0)),*(new Point(3,0,0)),
                             *(new Point(6,0,0)),*(new Point(5,0,0)),*(new Point(4,0,0)),*(new Point(7,0,0)),*(new Point(2,0,0)),*(new Point(9,0,0))};
    std::vector <Point> d = {*(new Point(11,0,0)), *(new Point(10,0,0)),*(new Point(1,0,0)),*(new Point(8,0,0)),*(new Point(3,0,0)),
                             *(new Point(6,0,0)),*(new Point(5,0,0)),*(new Point(4,0,0)),*(new Point(7,0,0)),*(new Point(2,0,0)),*(new Point(9,0,0))};
    std::vector <Point> e = {*(new Point(11,0,0)), *(new Point(10,0,0)),*(new Point(1,0,0)),*(new Point(8,0,0)),*(new Point(3,0,0)),
                             *(new Point(6,0,0)),*(new Point(5,0,0)),*(new Point(4,0,0)),*(new Point(7,0,0)),*(new Point(2,0,0)),*(new Point(9,0,0))};

    frankenstein_sort(c,0,c.size()-1,10);
    std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";
    frankenstein_sort(d,0,d.size()-1,10);
    print(d);
    std::stable_sort(e.begin(),e.end());
    print(e);
    return 0;
}