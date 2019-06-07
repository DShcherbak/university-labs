#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

const int MOD = 2134;
const double max_time = 10;

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
  //      print(a);
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

void quick_sort(std::vector<Point> &a,int left, int right){
    int middle = 0;
    if(left < right){
        middle = divide(a,left,right);

        quick_sort(a,left,middle);
        quick_sort(a,middle+1,right);

    }
   // print(a);
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
 //   print(a);
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

Point create_random_point(){
    int _x = rand()%MOD;
    int _y = rand()%MOD;
    int _z = rand()%MOD;
    Point* p = new Point(_x,_y,_z);
    return *p;

}

Point create_point(double n){
    int _x = n/3.0;
    int _y = n/3.0;
    int _z = n/3.0;

    Point* p = new Point(_x,_y,_z);
    return *p;

}

std::vector <Point> create_random_vector(int n){
   // std::cout <<
    std::vector <Point> vec;
    vec.resize(n);
    for(int i = 0; i < n; i++){
        vec[i] = create_random_point();
    }
    return vec;
}

std::vector <Point> create_sorted_vector(int n){
    // std::cout <<
    std::vector <Point> vec;
    vec.resize(n);
    for(int i = 0; i < n; i++){
        vec[i] = create_point(i);
    }
    return vec;
}

std::vector <Point> create_unsorted_vector(int n){
    // std::cout <<
    std::vector <Point> vec;
    vec.resize(n);
    for(int i = 0; i < n; i++){
        vec[i] = create_point(i);
    }
    return vec;
}

void benchmark_threshold() {
    freopen("benchmark_threshold.txt","w",stdout);
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
        //  std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";
        frankenstein_sort(d,0,d.size()-1,10);
        print(d);
        std::stable_sort(e.begin(),e.end());
        print(e);

        std::cout << "let's find optimal value of threshold for frankenstein (mixed) sort: \n";
        int n = 10;
        int max_size = 1 << 30;
        int best_threshold = 0;
        double time_threshold = 5.5;
        int size_threshold = 5;
        std::vector <Point> testing;
        testing.resize(20);

        for(int new_threshold = 5; new_threshold <= 145; new_threshold+=10){
            std::cout << "New threshold: " << new_threshold << std::endl;
            std::cout << "Count of Points --- random --- sorted --- unsorted\n";
            double diff_rand = 0.0, diff_sort, diff_unsort;
            long long cnt_for_sec = 1;
            auto bench_clock = clock();
            //   std::cin >> diff_rand;
            diff_rand = 0.0;
            diff_sort = 0.0;
            diff_unsort = 0.0;
            for(int i = 1; i < max_size && (std::max(diff_rand,std::max(diff_sort,diff_unsort) ) < 0.2);i = i << 1) {
                testing.clear();
                testing = create_random_vector(i);
                bench_clock = clock();
                frankenstein_sort(testing,0,testing.size()-1,new_threshold);
                diff_rand = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

                testing.clear();
                testing = create_sorted_vector(i);
                bench_clock = clock();
                frankenstein_sort(testing,0,testing.size()-1,new_threshold);
                diff_sort = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

                testing.clear();
                testing = create_unsorted_vector(i);
                bench_clock = clock();
                frankenstein_sort(testing,0,testing.size()-1,new_threshold);
                diff_unsort = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

                std::cout.setf(std::ios::left);
                std::cout.width(18);
                std::cout << i;
                std::cout.width(17);
                std::cout << diff_rand;
                std::cout.width(16);
                std::cout << diff_sort;
                std::cout.width(15);
                std::cout << diff_unsort << "\n";
                if(size_threshold < i){
                    best_threshold = new_threshold;
                    time_threshold = diff_rand;
                    size_threshold = i;
                }
                else if(i == size_threshold && diff_rand < time_threshold){
                    best_threshold = new_threshold;
                    time_threshold = diff_rand;
                    size_threshold = i;
                }
            }
            std::cout << "Optimal threshold: " << best_threshold << "\n";
        }
        //  std::vector <Point> test = create_random_vector(n);
        //   std::cout << "Size:" << test.size() << std::endl;
        //   for(auto t : test) std::cout << t << ", ";
        //  std::cout << std::endl;
        

}

int main() {
    freopen("benchmark.txt","w",stdout);

    std::cout << "On a random array: \n";
    int n = 10;
    int max_size = 1 << 30;
    int best_threshold = 25;
    std::vector <Point> testing;
    testing.resize(20);
    std::cout << "Count of Points --- insert_sort --- quick_sort --- merge_sort --- mixed_sort\n";
    double diff_insert = 0.0, diff_quick, diff_merge, diff_franken;
    long long cnt_for_sec = 1;
    auto bench_clock = clock();
    //   std::cin >> diff_rand;
    diff_quick = 0.0;
    diff_insert = 0.0;
    diff_merge = 0.0;
    diff_franken = 0.0;
    for(int i = 1; i < max_size && (std::max(std::max(diff_insert,diff_quick),std::max(diff_merge,diff_franken) ) < max_time);i = i << 1) {
        testing.clear();
        testing = create_random_vector(i);
        bench_clock = clock();
        insert_sort(testing, 0, testing.size() - 1);
        diff_insert = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

        testing.clear();
        testing = create_random_vector(i);
        bench_clock = clock();
        quick_sort(testing, 0, testing.size() - 1);
        diff_quick = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

        testing.clear();
        testing = create_random_vector(i);
        bench_clock = clock();
        merge_sort(testing, 0, testing.size() - 1);
        diff_merge = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

        testing.clear();
        testing = create_random_vector(i);
        bench_clock = clock();
        frankenstein_sort(testing, 0, testing.size() - 1, best_threshold);
        diff_franken = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;


        std::cout.setf(std::ios::left);
        std::cout.width(20);
        std::cout << i;
        std::cout.width(17);
        std::cout << diff_insert;
        std::cout.width(15);
        std::cout << diff_quick;
        std::cout.width(15);
        std::cout << diff_merge;
        std::cout.width(15);
        std::cout << diff_franken << "\n";


    }

    std::cout << "On a sorted array: \n";
    std::cout << "Count of Points --- insert_sort --- quick_sort --- merge_sort --- mixed_sort\n";
    //   std::cin >> diff_rand;
    diff_quick = 0.0;
    diff_insert = 0.0;
    diff_merge = 0.0;
    diff_franken = 0.0;
    for(int i = 1; i < max_size && (std::max(std::max(diff_insert,diff_quick),std::max(diff_merge,diff_franken) ) < max_time);i = i << 1) {
        testing.clear();
        testing = create_sorted_vector(i);
        bench_clock = clock();
        insert_sort(testing, 0, testing.size() - 1);
        diff_insert = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

        testing.clear();
        testing = create_sorted_vector(i);
        bench_clock = clock();
        quick_sort(testing, 0, testing.size() - 1);
        diff_quick = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

        testing.clear();
        testing = create_sorted_vector(i);
        bench_clock = clock();
        merge_sort(testing, 0, testing.size() - 1);
        diff_merge = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

        testing.clear();
        testing = create_sorted_vector(i);
        bench_clock = clock();
        frankenstein_sort(testing, 0, testing.size() - 1, best_threshold);
        diff_franken = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;


        std::cout.setf(std::ios::left);
        std::cout.width(20);
        std::cout << i;
        std::cout.width(17);
        std::cout << diff_insert;
        std::cout.width(15);
        std::cout << diff_quick;
        std::cout.width(15);
        std::cout << diff_merge;
        std::cout.width(15);
        std::cout << diff_franken << "\n";


    }

    std::cout << "On a reversed array: \n";
    std::cout << "Count of Points --- insert_sort --- quick_sort --- merge_sort --- mixed_sort\n";
    //   std::cin >> diff_rand;
    diff_quick = 0.0;
    diff_insert = 0.0;
    diff_merge = 0.0;
    diff_franken = 0.0;
    for(int i = 1; i < max_size && (std::max(std::max(diff_insert,diff_quick),std::max(diff_merge,diff_franken) ) < max_time);i = i << 1) {
        testing.clear();
        testing = create_unsorted_vector(i);
        bench_clock = clock();
        insert_sort(testing, 0, testing.size() - 1);
        diff_insert = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

        testing.clear();
        testing = create_unsorted_vector(i);
        bench_clock = clock();
        quick_sort(testing, 0, testing.size() - 1);
        diff_quick = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

        testing.clear();
        testing = create_unsorted_vector(i);
        bench_clock = clock();
        merge_sort(testing, 0, testing.size() - 1);
        diff_merge = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

        testing.clear();
        testing = create_unsorted_vector(i);
        bench_clock = clock();
        frankenstein_sort(testing, 0, testing.size() - 1, best_threshold);
        diff_franken = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;


        std::cout.setf(std::ios::left);
        std::cout.width(20);
        std::cout << i;
        std::cout.width(17);
        std::cout << diff_insert;
        std::cout.width(15);
        std::cout << diff_quick;
        std::cout.width(15);
        std::cout << diff_merge;
        std::cout.width(15);
        std::cout << diff_franken << "\n";


    }


    return 0;
}

/*
    testing.clear();
    testing = create_sorted_vector(i);
    bench_clock = clock();
    insertion_sort(testing,0,testing.size()-1,new_threshold);
    diff_sort = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;

    testing.clear();
    testing = create_unsorted_vector(i);
    bench_clock = clock();
    inserttion_sort(testing,0,testing.size()-1,new_threshold);
    diff_unsort = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;
    */