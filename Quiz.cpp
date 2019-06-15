#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include <stdlib.h>

using namespace std ;

class Question {

public:

    string category ;
    string qs ;
    string options[4] ;
    char ca ;

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

    void printQues() {

        cout << qs << endl ;
        for ( auto i : options ) 
            cout << i << endl ;

    }

    void resPrint() {
        cout << "Category : " << category << endl ;
        cout << qs << endl ;
        cout << "Correct Ans : " << ca << endl ;
    }

};

class Category {

public:

    vector<Question> questions ;
    string category ;
    Category( vector< string >& qs, string cat ) {
        category = cat ;
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

string quizHead() {
    string plrName;
    cout << "\n\n\nQuiz Time\n" ;
    cin.ignore() ;
    cout << "\nPls eneter player's name :    " ;
    getline(cin, plrName) ;
    cout << "\nHi " << plrName << " ! Welcome to the fun quiz.\nIn this quiz you will be geting 10 questions from different domains of daily life. Each question will have 4 answers. You has to choose the correct one. Choose an answer by entering the option no. written before the desired option. You'll get +10 for every correct annswer and 0 for a wrong answer i.e. there is no negative marking. No more instructions to keep it simple.\nPress eneter to begin.\n\n" ;
    getchar() ;
    return plrName ;
}

vector< Category > makeQuestionBank() { 

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
    Question Statement
    A. Option A
    B. Option B
    C. Option C
    D. Option D
    CE. Correct Option 
    ....

    There are 5 categories and 6 questions in each category. Every category is differentiated by a "|" charachter. The below fragment of code fetches the questions from question bank file "Questions.txt" based on the above orgainzation.

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

    return QB ;

}

void description() {
    
    ifstream fp ;
    string s ;
    cout << "\n\n-----------Description-----------\n" ;
    fp.open("Readme.txt") ;
    while ( getline(fp,s) ) 
        cout << s ;
    cout << "\n\nPress any key !"  ;
    cin.ignore() ;
    getchar() ;

}

void play(vector<Category>& QB ) {

    // Begining of playing Quiz
    int score = 0 ; //+10 for correct ans
    vector< char > responses ;
    vector< Question > quesAsked ;
    vector< char > scorecard ;


    for ( auto i = 0 ; i < QB.size() ; ++i ) {

        cout << "\n\nCategory No. " << i+1 << " :  " << QB[i].category ;
        int qno, q1, q2 ;
        q1 = rand()%6 ;
        q2 = rand()%6 ; 
        while ( q1==q2 )
            q2 = rand()%6 ;
        for ( auto j = 0 ; j < 2 ; ++j ) {
            cout  << endl << endl ;
            int qno = ( j==0 )? q1 : q2;
            (QB[i].questions[qno]).printQues() ;
            cout << "\nYour choice :          " ;
            string ans ;
            cin >> ans ;
            
            while ( true ) {
                if ( ans.size() == 1 ) {
                    if ( 65 <= (int)(ans[0]) && (int)(ans[0]) < 69 )
                        break ;
                }
                cout << "Invalid Option. Use A, B, C or D :            " ;
                cin >> ans ;
            }
            
            char a = ans[0] ;
            responses.push_back(a) ;
            quesAsked.push_back(QB[i].questions[qno]) ;
            
            if ( QB[i].questions[qno].getCorrectAnswer() == a )
                score += 10 ;

        }

    }

    //Quiz Over all answers recorded.

    cout << "\nYou have successfully completed the Quiz.\n" ;
    getchar() ;
    if ( 100 >= score &&  score >= 70 ) 
        cout << "Bingo! You got " << score/10 << " out of 10 correct answers.\n" ;
    else if ( score >= 50 )
        cout << "You got " << score/10 << " out of 10 correct answers. Not Bad !\n" ;
    else 
        cout << "You got " << score/10 << " out of 10 correct answers. Better Luck Next Time !\n" ;


    cout << "\n\nHere are your responses:\n" ;
    getchar() ;
    for ( auto i = 0 ; i < 10 ; ++i ) {

        cout << "\n\nQuestion No. " << i+1 << endl ;
        quesAsked[i].resPrint() ;
        cout << "Your Response : " << responses[i] << endl ;
        cout << "Marks Awarded : " ;
        if ( responses[i] == quesAsked[i].getCorrectAnswer() ) 
            cout << "+10\n" ;
        else 
            cout << "0\n" ;
    }

    cout << "\nYour Total Score is:  " << score << endl ;
    cout << "Press any key to go back to Main Menu\n" ;

    getchar() ;


}

void displayMenu() {

    cout << "\n\n\n\n-----------QUIZZE Time-----------\n" ;
    cout << "Pls Choose an option from below:\n" ;
    cout << "1. Play Quiz\n" ;
    cout << "2. Description\n" ;
    cout << "3. Exit\n" ;

}

int main() {

    
    vector< Category > QB=makeQuestionBank() ;
    bool invin = 0 ;

    while ( true ) {

        if ( !invin )
            displayMenu() ;
        
        string opt ;
        cin >> opt ;

        if ( opt == "1" ) {
            string plrName ;
            plrName = quizHead() ;
            play(QB) ;
            invin = 0 ;
        }
        else if ( opt == "2" ) {
            description() ;
            invin = 0 ;
        }
        else if ( opt == "3" ) {
            cout << "\nThanks!\n" ;
            break ;
        }
        else {
            cout << "Invalid Operation\nTry Again :             " ;
            invin = 1 ;
        }

    }
    

}