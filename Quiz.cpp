//6ques, 5categ

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

using namespace std ;

vector< string > _split( string s, string del=" " ) {

    vector< string > res ;
    string str="" ;
    for ( auto i = 0 ; i < s.size() ; ++i ) {
        string ch ;
        ch = s[i] ;
        if ( ch==del ) {
            res.push_back(str) ;
            str = "" ;
        }
        else 
            str += s[i] ;
    }
    return res ;

}

class Question {

public:

    string category ;
    string qs ;
    string options[4] ;
    unsigned short int ca ;

    Question( vector<string>& q, string cat ) {
        category = cat ;
        qs = q[0] ;
        for ( auto i = 1 ; i < 5 ; ++i ) 
            options[i-1] = q[i] ;
        ca = q[5][4] ;
    }

    char getCorrectAnswer() {
        return ca ;
    }

};

class Category {

public:

    vector<Question> questions ;
    string category ;
    Category( vector< string >& qs, string cat ) {
        category = cat ;
        cout << category << " here\n" ;
        for ( auto i = 0 ; i < 6 ; ++i ) {
            vector< string > q(6) ;
            for ( auto j = 0 ; j < 6 ; ++j ) {
                string qvec = qs[6*i + j]  ;
                q[j] = qvec ; 
            }
            Question newq(q, category) ;
            questions.push_back(newq) ;
        }

    }

    string getCat() {
        return category ;
    }


};

int main() {

    //FIle reading and creation of database starts

    string s, category;
    bool catbegread = 1 ;
    vector< Category > QB ;
    ifstream fp ;
    fp.open("Questions.txt") ;
    
    /*
    The content of file is organized like this:
    |
    CAT-Category
    Question Statement
    A. Option A
    B. Option B
    C. Option C
    D. Option D
    CE. Correct Option 
    */

    
    vector< string > q ;
    bool skip = 1; 
    while ( getline(fp,s) ) {

        //cout << s << endl << endl << endl ;
        if ( s=="|" ) {
            catbegread = 1 ;
            //C= ;
            Category new_cat(q,category) ;
            QB.push_back(new_cat) ;
            
            continue ;
        }

        if ( catbegread ) {
            catbegread = 0 ;
            q.clear() ;
            category = "" ;
            for ( auto i = 4 ; i < s.size() ; ++i ) 
                category += s[i] ;
            continue ;
        }
        q.push_back(s) ;
    }
    
    fp.close() ;

    //File Reading Ends. A vector of Categories is created as QB. Each Category has 6 questions.

    // Begining of playing Quiz

    for ( auto i = 0 ; i < QB.size() ; ++i ) {

        //cout << "Category No. : " << i+1 << " :  " << QB[i].getCat() << endl ;

    }

    fp.close() ;

}