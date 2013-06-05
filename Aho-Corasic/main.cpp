/**@mainpage
*   Titov Roman Group IU 8 -21
*   Laboratory  "C++ realisation algoritm Aho-Corasic"
*/
/************************************************************************/
/// @brief                       HEADERS                               ///
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
/************************************************************************/
using namespace std;
/************************************************************************/
/// @brief               Prototypes and declarations                   ///
class Node;
void write( const char* );
typedef map <const char, Node* > Lmap;
/************************************************************************/
class Node
{
public:

    Lmap links;      
    Node *word;
	Node *fail;
    int exit;
 
public:

    Node(Node *fail_node = NULL): word(NULL), fail(fail_node), exit(-1) { }
 
    Node* get_link( const char c ) const 
    {
        Lmap::const_iterator i = links.find(c);

        if ( i != links.cend() ) {
            return i -> second;
        }
        else {

            return NULL;
        }
    }
 
    bool is_word() const 
    {
        return ( exit >= 0 );
    }
};
/***************************************************************/ 
class Aho_Corasic
{
public:

    typedef void ( *Callback ) (const char* sub_string);
    vector< string > words;	
	Node root;    
    Node* cur_state;
 
public:

    void add_str( const char* const str ) 
    {
        Node *cur_node = &root;

        for( const char *cp = str; *cp; ++cp) {
            Node *child_node = cur_node -> get_link( *cp );

            if ( !child_node ) {
                child_node = new Node( &root );
                cur_node -> links[ *cp ] = child_node;
            }

            cur_node = child_node;
        }
        cur_node -> exit = words.size();
        words.push_back( str );
    }
 
    void init() 
    {
        queue < Node *> t;
        t.push( &root );
        while ( !t.empty() ) {
            Node *cur_node = t.front();
            t.pop();
            for ( Lmap::const_iterator i = cur_node -> links.cbegin(); i != cur_node -> links.cend(); ++i)
            {
                const char symbol = i -> first;
                Node *child = i -> second;                
                Node *temp_node = cur_node -> fail;

                while (temp_node) {

                    Node *error = temp_node -> get_link(symbol);

                    if ( error ) {
                        child -> fail = error;
                        break;
                    }

                    temp_node = temp_node -> fail;
                }
				
				
				if ( child -> fail -> is_word() ) {
					
					child -> word = child -> fail;
				}
				else
				{
					child -> word = child -> fail -> word;
				}
                t.push( child );
			}
        }
    }
 
    void pitch(const char c) 
    {
        while ( cur_state ) {

            Node *member = cur_state -> get_link(c);

            if ( member ) {
                cur_state = member;
                return;
            }

            cur_state = cur_state -> fail;
        }

        cur_state = &root;
    }
	 
    void write_words( Callback beam) const 
    {
        if ( cur_state -> is_word() ) {
            beam( words[cur_state -> exit].c_str());
        }

        Node *temp_node = cur_state -> word;
        while ( temp_node ) {

            beam( words[ temp_node -> exit ] . c_str() ); 
            temp_node = temp_node -> word;
        }
    }
 
    void search(const char* str, Callback beam) 
    {
        cur_state = &root;

        for( ; *str++; ) {

            cout << *str << "-\n";
            pitch( *str );
            write_words( beam );
		}
    }
};
/************************************************************************/
///                        MAIN FUNCTION                               ///
/// {
int main()
{
    Aho_Corasic sample;
 
    sample.add_str("chemical");
    sample.add_str("chemistry");
    sample.add_str("chess");
    sample.add_str("chessmaster");
 
    sample.init(); 
    sample.search("Loading", write); 
    cin.get();
 
    return 0;
}
/// }
/************************************************************************/
void write( const char* str)
{
	cout << " sub-string is found " << str << endl;
}
/************************************************************************/

 