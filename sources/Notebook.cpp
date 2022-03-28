#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>
#include "Notebook.hpp"
#include "Direction.hpp"
using namespace std;
using namespace ariel;
using ariel::Direction;
const int COL = 100;
const int MAX_LEN = 99;
const int MIN_CHAR = 32; //min acceptable char
const int MAX_CHAR = 126; //max acceptable char


namespace ariel{

    void Notebook::write(int page, int row, int col, ariel::Direction dir, string msg){
        if(page < 0 || row < 0 || col < 0 || col > MAX_LEN){
            throw invalid_argument("invalid input!");
        }
        //check for invalid character input
        for (unsigned long i = 0; i < (int)msg.length(); i++)
        {
            if(msg.at(i) < MIN_CHAR || msg.at(i) > MAX_CHAR || msg.at(i) == '~'){
                throw invalid_argument("invalid input!");
            }
        }
        
        if(dir == Direction::Horizontal){
            //check that string is acceptable length for position
            if((int)msg.length() > COL || (int)msg.length() > COL - col){
                throw invalid_argument("invalid input!");
            }
            //checking to see if spot is written or erased already
            for (int i = col; i < col + (int)msg.length(); i++)
            {
                if(this->pages[page][row][i] != '\0' && this->pages[page][row][i] != '_'){
                    throw invalid_argument("invalid input!");
                }
            }
            unsigned long j = 0;
            for (int i = col; i < col + (int)msg.length(); i++)
            {
                this->pages[page][row][i] = msg.at(j);
                j++;
            }    
        }

        if(dir == Direction::Vertical){
           for (int i = 0; i < (int)msg.length(); i++)
            {
               //checking to see if spot is written or erased already
                if(this->pages[page][row+i][col] != '\0' && this->pages[page][row+i][col] != '_'){
                    throw invalid_argument("invalid input!");
                }
            }
            unsigned long j = 0;
            for (int i = 0; i < (int)msg.length(); i++)
            {
                this->pages[page][row+i][col] = msg.at(j);
                j++;
            }  
        }
    }
    
    string Notebook::read(int page, int row, int col, ariel::Direction dir, int len){
        if(page < 0 || row < 0 || col < 0 || col > MAX_LEN || len < 0){
            throw invalid_argument("invalid input!");
        }
        string text;
        
        if(dir == Direction::Horizontal){
            //check that string is acceptable length for position
            if(len > COL - col || len > COL){
                throw invalid_argument("invalid input!");
            }
            for (int i = col; i < col + len; i++)
                {
                    //if spot is empty
                    if(this->pages[page][row][i] == '\0'){
                        text += '_';
                    }  
                    else{
                        text += this->pages[page][row][i];
                    }
                }
        }
            
        if(dir == Direction::Vertical){
            for (int j = 0; j < len; j++)
                {
                    //if spot is empty
                    if(this->pages[page][row+j][col] == '\0'){
                        text += '_'; 
                    }
            
                    else{
                        text += this->pages[page][row+j][col];
                    }
                }
        }   
    return text;
    }

    void Notebook::erase(int page, int row, int col, ariel::Direction dir, int len){
        //checking valid input
        if(page < 0 || row < 0 || col < 0 || col > MAX_LEN || len < 0){
            throw invalid_argument("invalid input!");
        }
        if(dir == Direction::Horizontal){
            //check that string is acceptable length for position
            if(len > COL - col || len > COL){
                throw invalid_argument("invalid input!");
             }
            for (int i = col; i < col + len; i++)
            {
                this->pages[page][row][i] = '~';
            }    
        }
        if(dir == Direction::Vertical){
            for (int j = 0; j < len; j++)
            {
                this->pages[page][row+j][col] = '~';
            }
        }
    }

    void Notebook::show(int page){
        if(page < 0){
            throw invalid_argument("invalid input!");
        }
        string s;
        //finding min and max rows of page in order to know range to iterate over
        int min = std::numeric_limits<int>::max();
        int max = 0;
        for(auto x : this->pages[page]){
            if(x.first < min){
                min = x.first;
            }
            if(x.first > max){
                max = x.first;
            }
        }

        for (int i = min; i < max; i++)
        {
            if(this->pages[page].find(i) == this->pages[page].end()){
                cout << i << ": ____________________________________________________________________________________________________" << endl;
            }
            else{
                for (int j = 0; j < COL; j++)
                {
                    if(this->pages[page][i][j] == '\0'){
                        s += '_';
                    }
                    else{
                        s += this->pages[page][i][j];
                    }
                }
                cout << i << ": " << s << endl;
            }
        }
    }

}

