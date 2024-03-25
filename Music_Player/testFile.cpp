#include <iostream>
#include <fstream>
#include <sstream>
#include "GUI.hpp"
//#include <chrono>
//#include <regex>

//#include <ctime>
using namespace std;

struct Music {
    int key;
    string musicName;
    string artistName;
    string dateAdded;
    int rate; 
    Music *left, *right;
};

struct Music* newNode()
{
    struct Music* temp = new Music;
    temp->left = temp->right = NULL;
    return temp;
}


Music* root = NULL;
string filename = "music_data.txt";


void saveMusicToFile(Music* node, ofstream& file) {
    if (node == NULL) {
        return;
    }
    
    saveMusicToFile(node->left, file);
        file<<"***music "<<node->key<<"***"<<endl;
        file<<"key   :"<<node->key <<endl;
        file<<"name  :"<<node->artistName<<endl;
        file<<"music :"<<node->musicName<<endl;
        file<<"date  :"<<node->dateAdded<<endl;
        file<<"Rate  :"<<node->rate <<endl;
        file<<"==========================================="<<endl;
    saveMusicToFile(node->right, file);
}

void saveToFile(Music* node) {
    ofstream file(filename,ios::app);
    if (file.is_open()) {
        saveMusicToFile(node, file);
        file.close();
        cout << "Music library saved to file." <<endl;
    } else {
        cout << "Unable to open file for saving music library." << std::endl;
    }
}
void buildBinaryTreeFromFile(TreeNode*& root, const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error opening file." << std::endl;
        return;
    }

    int value;
    while (inputFile >> value) {
        insert(root, value);
    }

    inputFile.close();
}

void proceedOption() {
    char choice;
    cout << "Do you want to continue? (Y/N): ";
    cin >> choice;
    cin.ignore();

    if (choice == 'Y' || choice == 'y') {
       displayMenu();
    } else {
       cout << "Exiting program..." << endl;
       saveToFile(root);
   }
}
 

void insertMusic(Music* music) {
	bool isFound=false;
	Music* current=root;
    Music* newNod = newNode();
    
     while (true) {
     	if (current->key == music->key)
     	    {
     	    	cout<<"you entered the used key , exited"<<endl;
     	    	return;
			 }
        else if (music->key < current->key) 
		    current = current->left;
        else    
		    current = current->right;
    }

    if (root == NULL) {
        root = newNod;
    } else {
        Music* current = root;
        Music* parent = NULL;

        while (true) {
            parent = current;

            if (music->key < current->key) {
                current = current->left;
                if (current == NULL) {
                    parent->left = newNod;
                    break;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = newNod;
                    break;
                }
            }
        }
    }

    cout << "Music added successfully." << endl;
}

Music* getSuccessor(Music* node) {
    Music* successorParent = node;
    Music* successor = node->right;
    Music* current = node->right;

    while (current != NULL) {
        successorParent = successor;
        successor = current;
        current = current->left;
    }

    if (successor != node->right) {
        successorParent->left = successor->right;
        successor->right = node->right;
    }

    return successor;
}

void deleteMusic(int key) {
    if (root == NULL) {
        cout << "Music library is empty." << endl;
        return;
    }

    Music* parent = NULL;
    Music* current = root;
    bool isLeftChild = false;

    while (current->key != key) {
        parent = current;

        if (key < current->key) {
            current = current->left;
            isLeftChild = true;
        } else {
            current = current->right;
            isLeftChild = false;
        }

        if (current == NULL) {
            cout << "Music with key " << key << " not found." << endl;
            return;
        }
    }

    if (current->left == NULL && current->right == NULL) {
        // Case 1: Node to be deleted is a leaf node
        if (current == root) {
            root = NULL;
        } else if (isLeftChild) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    } else if (current->right == NULL) {
        // Case 2: Node to be deleted has only left child
        if (current == root) {
            root = current->left;
        } else if (isLeftChild) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
    } else if (current->left == NULL) {
        // Case 2: Node to be deleted has only right child
        if (current == root) {
            root = current->right;
        } else if (isLeftChild) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
    } else {
        // Case 3: Node to be deleted has both left and right children
        Music* successor = getSuccessor(current);

        if (current == root) {
            root = successor;
        } else if (isLeftChild) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }

        successor->left = current->left;
    }

    delete current;
    cout << "Music with key " << key << " deleted successfully." << endl;
}

void deleteMusic() {
	
    if (root == NULL) {
        cout << "Music library is empty." << endl;
        return;
    } 

         Music* temp = root;
        if (root->left == NULL && root->right == NULL) {
            root = NULL;
        } else if (root->right == NULL) {
            root = root->left;
        } else if (root->left == NULL) {
            root = root->right;
        } else {
            Music* successor = getSuccessor(root);
            successor->left = root->left;
            if (successor != root->right) {
                successor->right = root->right;
            }
            root = successor;
        }
        delete temp;
        cout << " The root node deleted successfully." << endl;
        
        return;     
}

void deleteMinimum() {
    if (root == NULL) {
        cout << "Music library is empty." << endl;
        return;
    }

    Music* parent = NULL;
    Music* current = root;

    while (current->left != NULL) {
        parent = current;
        current = current->left;
    }

    if (current == root) {
        root = current->right;
    } else {
        parent->left = current->right;
    }

    delete current;
    cout << "Minimum music deleted successfully." << endl;
}

void deleteMaximum() {
    if (root == NULL) {
        cout << "Music library is empty." << endl;
        return;
    }

    Music* parent = NULL;
    Music* current = root;

    while (current->right != NULL) {
        parent = current;
        current = current->right;
    }

    if (current == root) {
        root = current->left;
    } else {
        parent->right = current->left;
    }

    delete current;
    cout << "Maximum music deleted successfully." << endl;
}

void deleteAll(){
	 Music* temp=root;
	 root->left=NULL;
	 root->right=NULL;
	 root=NULL; 
	 delete temp;
}

void displayDetail(Music* music)
{               
                cout<<"********* MUSIC ************"<<endl<<endl;
                cout << "Key: " << music->key << endl;
                cout << "Music Name: " << music->musicName << endl;
                cout << "Artist Name: " << music->artistName << endl;
                cout << "Date Added: " << music->dateAdded << endl;
                cout << "Rate: " << music->rate << endl;
                cout<<"********************************"<<endl<<endl;

	
}

void display(){}

void displayMinimum() {
    if (root == NULL) {
        cout << "Music library is empty." << endl;
        return;
    }

     Music* music = root;

    while (music->left != NULL) {
         music = music->left;
    }
            displayDetail(music);

               
    }


void displayMaximum() {
    if (root == NULL) {
        cout << "Music library is empty." << endl;
        return;
    }

     Music* music = root;

    while (music->right != NULL) {
         music = music->right;
    }
    
        displayDetail(music);
    }


Music* searchByKey(int key) {
    Music* current = root;

    while (current != NULL) {
        if (key == current->key) {
            return current;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

Music* searchByMusicName(const string& musicName) {
    Music* current = root;

    while (current != NULL) {
        if (musicName == current->musicName) {
            return current;
        } else if (musicName < current->musicName) {
            current = current->left;
        } else {
            current = current->right; 
        }
    }

    return NULL;
}

void searchByArtistName(const string& artistName) {
    Music* current = root;
    bool found=false;
    while (current != NULL) {
        if (artistName == current->artistName) {
              displayDetail(current);
              found=true;
        } else if (artistName < current->artistName) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if(!found)
      cout << "Music by artist \"" << artistName << "\" not found." << endl;


    return;
}

void searchByDateAdded(const string& dateAdded) {
    Music* current = root;
    bool found=false;

    while (current != NULL) {
        if (dateAdded == current->dateAdded) {
              displayDetail(current);
              found=true;
        } else if (dateAdded < current->dateAdded) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
  
   if(!found)
       cout << "Music by artist \"" << dateAdded << "\" not found." << endl;

    return  ;
}

void searchByRate(int rate) {
    Music* current = root;

    while (current != NULL) {
        if (rate == current->rate) {
              displayDetail(current);
        } else if (rate < current->rate) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
       cout << "Music that has rate " << rate << " not found." << endl;

    return ;
}


void preorderTraversal(Node* node) {
    if (node != NULL) {
        cout << displayDetail(node) << endl;
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

void inorderTraversal(Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        cout << displayDetail(node) << endl;
        inorderTraversal(node->right);
    }
}


void postorderTraversal(Node* node) {
    if (node != NULL) {
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << displayDetail(node) << endl;
    }
}

void exitProgram()
{
	cout<<"Bye Bye \n program exiting";
	exit(0);
}

void displaySearchMenu()
{
	cout << "1. Search by Key" << endl;
    cout << "2. Search by Music Name" << endl;
    cout << "3. Search by Artist Name" << endl;
    cout << "4. Search by Date Added" << endl;
    cout << "5. Search by Rate" << endl;
    cout<<  "6. MainMenu "<<endl;
    cout<<  "0. Exit"<<endl;
    int choice;
    cin>>choice;
    switch(choice){
    	  case 1: 
            int key;
            cout << "Enter the key to search: ";
            cin >> key;

           Music* music = searchByKey(key);
            if (music != NULL) 
                displayDetail(music);
           else 
                cout << "Music with key " << key << " not found." << endl;

            proceedOption();
            break;
         case 2: 
            string musicName;
            cout << "Enter the music name to search: ";
            getline(cin, musicName);

            Music* music = searchByMusicName(musicName);
            if (music != NULL) {
                displayDetail(music);
            } else {
                cout << "Music with name \"" << musicName << "\" not found." << endl;
            }

            proceedOption();
            break;
        
        case 3: 
            string artistName;
            cout << "Enter the artist name to search: ";
            getline(cin, artistName);

            searchByArtistName(artistName);
            proceedOption();
            break;
         case 4: 
            string dateAdded;
            cout << "Enter the date added to search (YYYY-MM-DD): ";
            getline(cin, dateAdded);

           searchByDateAdded(dateAdded);
             
            proceedOption();
            break;
        case 5: 
            int rate;
            cout << "Enter the rate to search: ";
            cin >> rate;             
            proceedOption();
            break;
        case 6:
       	 displayMenu();
       	 break;
       case 0:
       	  exitProgram();
       	  break;
       default :
       	    cout << "Invalid choice. Please try again." << endl;
            displaySearchMenu();
            break;
	}
    
}
void displayDeleteMenu()
{
	   cout << "1. Delete Music" << endl;
       cout << "2. Delete Min key Music" << endl;
       cout << "3. Delete Max key Music" << endl;
       cout<<  "4. Clear All"<<endl;
       cout<<  "5. MainMenu "<<endl;
       cout<<  "0. Exit"<<endl;
       int choice;
       cin>>choice;
       switch(choice){
       	  case 1: 
            int key;
            cout << "Enter the key to delete: ";
            cin >> key;
            deleteMusic(key);
            proceedOption();
            break;
        case 2: 
            deleteMinimum();
            proceedOption();
            break;
         case 3: 
            deleteMaximum();
            proceedOption();
            break;
         case 4:
         		deleteAll(root);
        		break;
 		case 5:
			 	displayMenu();
			 	break;
		case 0 :
			exitProgram();
			break;
		default :
			system("clr");
			cout<<" wrong option , try again"<<endl;
            deleteDisplayMenu();
            break;
	   }
}
void displayMenus(){
	   cout << "1. Display Music" << endl;
	   cout<<  "2. Display Top Music"<<endl;
       cout << "3. Display Low Music" << endl;
       cout << "4. Display All Music" << endl;
       cout<<  "5. MainMenu "<<endl;
       cout<<  "0. Exit"<<endl;
}
void displayMenu() {
    cout << "------ Music Library ------" << endl;
    cout << "1. Add Music" << endl;
    cout << "2. Delete Music" << endl;
    cout << "3. Display Music" << endl;
    cout << "4. Search Music" << endl;
    cout << "0. Exit" << endl;
    cout << "---------------------------" << endl;
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();  // Ignore remaining newline character
    
    switch (choice) {
        case 1 : 
        	Music* newMusic=newNode();
        	cout<<endl<<"***************************"<<endl<<endl;
            cout << "Enter the key: ";
            cin >> newMusic->key;
            cin.ignore();
            cout << "Enter the music name: ";
            getline(cin, newMusic->musicName);
            cout << "Enter the artist name: ";
            getline(cin, newMusic->musicName);
            cout << "Enter the date added (YYYY-MM-DD): ";
            getline(cin, newMusic->artistName);
            cout << "Enter the rate: ";
            cin >>newMusic->rate;
            cin.ignore();
            cout<<endl<<endl<<endl;
             insertMusic(newMusic);
            proceedOption();
            break;
        case 2 :
        	displayDeleteMenu();
        	break;
        case 3:
        	 displayMenus();
        	 break;
        case 4:
        	 displaySearchMenu();
        	 break;
        case 0: 
           saveToFile(root);
              exitProgram();
            break;
        
        default: 
            cout << "Invalid choice. Please try again." << endl;
            proceedOption();
            break;
  }
}
int main()
{ 
    GUI ui;
    ui.someFunction();
    printf("Press any key to continue...");
    getchar();
    displayMenu();  
	  
    return 0;
}
 
//bool isValidDate(const string& dateStr) {
//	
//    regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");
//
//    if (!regex_match(dateStr, dateRegex)) {
//        return false;
//    }
//
//    int year = stoi(dateStr.substr(0, 4));
//    int month = stoi(dateStr.substr(5, 2));
//    int day = stoi(dateStr.substr(8, 2));
//
//    try {
//        year_month_day date{ year, month, day };
//        return date.ok();
//    } catch (const exception&) {
//        return false;
//    }
//}
//bool isNumber()
//{ 
//    
//	return true;
//}

