#include <iostream>
#include <unordered_map>
#include "Direction.hpp"
using namespace std;
using ariel::Direction;


namespace ariel{
    class Notebook {
        unordered_map<int, unordered_map<int, char[100]> > pages;
        public:
            void write(int page, int row, int col, ariel::Direction dir, string msg);
            string read(int page, int row, int col, ariel::Direction dir, int len);
            void erase(int page, int row, int col, ariel::Direction dir, int len);
            void show(int page);
    };
}
