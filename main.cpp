# include <iostream>

using namespace std;

int main(){

  int choice;

  cout << "Welcome!" << endl;
  cout << "Select one of the options below" << endl;
  cout << "1: Add Book" << endl;
  cout << "2: Add Magazine" << endl;
  cout << "3: Add User" << endl;
  cout << "4: Borrow Book" << endl;
  cout << "5: Return Book" << endl;
  cout << "6: View All Items" << endl;
  cout << "7: View All Users" << endl;
  cout << "8: Exit" << endl;

  cin >> choice;

  switch (choice)
  {
    case 1: "Add Book";
    break;
    case 2: "Add Magazine";
    break;
    case 3: "Add User";
    break;
    case 4: "Borrow Book";
    break;
    case 5: "Return Book";
    break;
    case 6: "View All Items";
    break;
    case 7: "View All Users";
    break;
    case 8: "Exit";
    break;
  
    default: 
    cout << "You have selected an invalid option" << endl;
    break;
  }


  return 0;
}