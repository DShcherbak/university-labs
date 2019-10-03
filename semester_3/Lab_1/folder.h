#include "file.h"
#include <vector>
#include <string>
using namespace std;

class folder {
private:
    folder* parent;
    vector <folder*> subfolders;
    vector <file*> files;
    string name;
    int size;

public:
    void add_subfolder(folder* f);
    void add_file(file* f);
    void add_size(int size);
    void delete_folder();
};
