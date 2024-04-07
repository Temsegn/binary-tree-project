#include <iostream>
#include <fstream>
#include<string>
#include<sstream>
#include "GUI.hpp"
#include "validation.hpp"
//#include <chrono>
//#include <regex>

//#include <ctime>
using namespace std;

Validator validate;

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

void insertMusic(Music* node);
void displayMenu();

void saveMusicToFile(Music* node, ofstream& file) {
    if (node == NULL) {
        return;
    }

    saveMusicToFile(node->left, file);        
        file<<node->key<<","<<node->artistName<<","<<node->musicName<<","<<node->dateAdded<<","<<node->rate <<endl;
	saveMusicToFile(node->right, file);
}


void saveToFile(Music* node) {

    ofstream file;
    file.open("music_data.txt",ios::app);
    if (file.is_open()) {
        saveMusicToFile(node, file);
        file.close();
        cout << "Music library saved to file." <<endl;
    } else {
        cout << "Unable to open file for saving music library." << endl;
    } 
    
}
 void parseFileRecursive(fstream& file, Music*& root) {
    string line;

    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
    }
    Music* newm=newNode();

    while (getline(file,line)) {
        
        stringstream ss(line);
        string item;
        int key;
        string artistName;
        string musicName;
        string dateAdded;
        int rate;

        // Parse each line by comma-separated values
        if (getline(ss, item, ','))
            key = stoi(item);
        
        if (getline(ss, item, ','))
            artistName = item;

        if (getline(ss, item, ','))
            musicName = item; 

        if (getline(ss, item, ','))
            dateAdded = item;

        if (getline(ss, item, ','))
            rate = stoi(item);
            
       newm->key=key;
       newm->artistName=artistName;
       newm->musicName=musicName;
       newm->dateAdded=dateAdded;
       newm->rate=rate;

       insertMusic(newm);
    }

    // Close the file
    file.close();
}
 

void proceedOption() {
    char choice;
    cout << "Do you want to continue? (Y/N) :  ";
    cin >> choice;
    cin.ignore();
    system("cls");

    if (choice == 'Y' || choice == 'y') {
       displayMenu();
    } else {
       cout << "\n\n Exiting program..." << endl;
       saveToFile(root);
   } 
}


void insertMusic(Music* music) {
	bool isFound=false;
	Music* current=root;
	Music* temp=current;


     while (temp!=NULL) {
      	if (temp->key == music->key)
     	    {
     	    	cout<<"you entered the used key , exited"<<endl;
     	    	return;
			 }
        else if (music->key < temp->key)
		    temp = temp->left;
        else
		    temp = temp->right;
    }

    if (root == NULL) {
        root = music;
    } else {
        Music* current = root;
        Music* parent = NULL;

        while (true) {
            parent = current;

            if (music->key < current->key) {
                current = current->left;
                if (current == NULL) {
                    parent->left = music;
                    break;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = music;
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
                
                cout << "Key        : " << music->key << endl;
                cout << "Music Name : " << music->musicName << endl;
                cout << "Artist Name: " << music->artistName << endl;
                cout << "Date Added : " << music->dateAdded << endl;
                cout << "Rate       : " << music->rate << endl;
                
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


void preorderTraversal(Music* node) {
    if (node != NULL) {
        displayDetail(node);
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

void inorderTraversal(Music* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        displayDetail(node);
        inorderTraversal(node->right);
    }
}


void postorderTraversal(Music* node) {
    if (node != NULL) {
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        displayDetail(node);
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
    cout<<"enter your choice :";
    cin>>choice;
    switch(choice){
    	  case 1:
           {
           	 int key;
            cout << "Enter the key to search: ";
            cin >> key;

           Music* musics = searchByKey(key);
            if (musics != NULL)
                displayDetail(musics);
           else
                cout << "Music with key " << key << " not found." << endl;
            proceedOption();
            break;

		   }
         case 2:
           {
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

		   }
        case 3:
           {
           	 string artistName;
            cout << "Enter the artist name to search: ";
            getline(cin, artistName);

            searchByArtistName(artistName);
            proceedOption();
            break;
		   }
         case 4:
           {
           	 string dateAdded;
            cout << "Enter the date added to search (YYYY-MM-DD): ";
            getline(cin, dateAdded);

           searchByDateAdded(dateAdded);

            proceedOption();
            break;
		   }
        case 5:
           {

		   }
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
void deleteDisplayMenu()
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
         		deleteAll( );
        		break;
 		case 5:
			 	displayMenu();
			 	break;
		case 0 :
			exitProgram();
			break;
		default :
			system("cls");
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
       cout<<  "5. preorder "<<endl;
       cout<<  "6. inorder "<<endl;
       cout<<  "7. postorder "<<endl;
       cout<<  "8. level order "<<endl;
       cout<<  "9. MainMenu "<<endl;
       cout<<  "0. Exit"<<endl;
       int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    switch(choice){
    	case 1:
    		display();
    		proceedOption();
    		break;
    	case 2:
    		displayMaximum();
    		proceedOption();
    		break;
		case 3:
			displayMinimum();
			proceedOption();

    		break;
		case 4:
			display();
			proceedOption();

    		break;
		case 5:
		 cout << "Preorder Traversal: ";
            preorderTraversal(root);
            cout << endl;
            proceedOption();
            break;
 
 		case 6:
			inorderTraversal(root);
			    		proceedOption();

    		break;
		case 7:
			cout << "Postorder Traversal: ";
            postorderTraversal(root);
            cout << endl;
            proceedOption();
            break;
 		case 8:
			    		proceedOption();

			cout<<"level order"<<endl;
    		break;
		case 9:
			    		proceedOption();

			displayMenu();
    		break;
		case 0:
			exitProgram();
    		break;
    	 default:
    	 	cout<<"invalid "<<endl;
    		break;
	}
} 

void addoption()
{
	 cout<<"1. from the local disk "<<endl;
	 cout<<"2. from the Keyboard"<<endl;
	 
}
void displayMenu(){
    cout<<"-----------Music player------------------------"<<endl;
    cout << "                         1. Add Music" << endl;
    cout << "                         2. Delete Music" << endl;
    cout << "                         3. Display Music" << endl;
    cout << "                         4. Search Music" << endl;
    cout << "                         5. rotate root Music" << endl;
    cout << "                         0. Exit\n\n\n" << endl;  
    cout << "                   Enter your choice : ";
    int choice;
    cin >> choice;
    cin.ignore();  // Ignore remaining newline character
    system("cls");
    switch (choice) {
        case 1 :
        {  
              addoption();
               cin >> choice;
               cin.ignore();  // Ignore remaining newline character
               if(choice==1)
                 { 
                    // Open the file for reading
                   fstream file("music_data.txt");
                   if (!file.is_open()) {
                   cerr << "Failed to open the file." << endl;
                  return ;
                 }

        
                parseFileRecursive(file,root);
                proceedOption();
                  break;                 	
				 }
               system("cls");
            
  
    
    	        
	Music* newMusic=newNode();
        	cout<<endl<<"***************************"<<endl<<endl;
            cout << "Enter the key           : ";
            cin >> newMusic->key;
                        cin.ignore();

            int k= newMusic->key;
            string key= to_string(k);
           if(!validate.isNumber(key))
           {
           	 cout<<"it is not number , should be integer"<<endl;
           	 exit(0);
		   }
            cout << "Enter the music name    : ";
            getline(cin, newMusic->musicName);
          if(!validate.hasNoNumber(newMusic->musicName))
            {
            	cout<<"the name is invalid , only letter allowed"<<endl;
            	exitProgram();
									}                        
            cout << "Enter the artist name   : ";
            getline(cin, newMusic->artistName);
             if(!validate.hasNoNumber(newMusic->artistName))
            {
            	cout<<"the name is invalid , only letter allowed"<<endl;
            	exitProgram();
									} 
            cout << "Enter date (YYYY-MM-DD) : ";
            getline(cin, newMusic->dateAdded);
            
            if(!validate.isValidDate(newMusic->dateAdded))
            {
            	cout<<"invalid date format"<<endl;
                 exitProgram();
 			}
            cout << "Enter the rate          : ";
            cin >>newMusic->rate;
            int rate=newMusic->rate;
            string stringNumber =to_string(rate);
            
            if(validate.isNumber(stringNumber))
              { 
                
              	if(!validate.isValidRating(newMusic->rate))
              	  {
              	  	cout<<"invalid value , between 0 and 10"<<endl;
              	  	exitProgram();
					}
			  }
			  else
			    {
			    	cout<<"you have to enter a number , not character"<<endl;
			    	exitProgram();
				}
            cin.ignore();
            cout<<endl<<endl<<endl;
             insertMusic(newMusic);
            proceedOption();
            break;
		}
        case 2 :
        	deleteDisplayMenu();
        	cout<<"display menu"<<endl;
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
    printf("\n\n\nPress any key to continue...\n\n\n");
    getchar();
    system("cls");
    displayMenu();
	cout<<"\n\n\n\n\n";
    return 0;
}                                            

                                            
                    
 