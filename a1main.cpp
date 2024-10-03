// Mujtaba Fatah Moahammed 13th September 2024

//PlayList Methods 
//Default constructor: O(1) as only assignment operations are taking place, which are only constant time operators.
//Destructor: O(n) as it is using a while loop to iterate over the length of the list and deleting a node one by one.
//Copy Constructor: O(n) as the copy constructor iterates through the playlist inserted and inserts each node into a new playlist
//Overloaded assignment operator: O(n) as the assignment operator first calls the destructor to delete the existing playlist, which is O(n), and then iterates through the source playlist to insert each node, which also takes O(n).
//Insert: O(n) as the worst case scenario requires it to traverse through the whole list using a for loop to insert at the last position.
//Remove: O(n) as the worst case scenario requires it to traverse through the whole list using a for loop to remove the last element.
//Get: O(n) as the worst case scenario requires it to traverse through the whole list using a for loop to return the last element.
//Swap: O(n) as the funtion is traversing through 2 different list linearly and adding them gives O(2n) where we can take the constan outside leaving us with O(n).
//Size: O(1) returns the length which is a linear operation. 

//Main Function
//Enter a song: O(n) as the insert function uses a time complexity of O(n), as it may be required to traverse through the entire playlist to enter a song.
//Remove a song: O(n) as the remove function uses a time complexity of O(n), since  it requires traversing the list to find the song at the given position.
//Swap two songs: O(n) as the swap function uses a time complexity of O(n),  in the worst case, each position could be at the end of the list, so traversing to each position
//Print all songs: O(n) the get function uses O(n^2) as the get function itself is of O(n) and it uses another for loop as there can be n number of songs.


#include <iostream>
#include "Song.h"
#include "PlayList.h"
#include<stdexcept>
using std::cout;
using std::endl;
using std::cin;
using std::getline;

int main()
{
    PlayList playlist;
    int choice;

    cout << "Menu" << endl;
    cout << "1 - Enter a song in the playlist at a given position" << endl;
    cout << "2 - Remove a song from the playlist at a given position" << endl;
    cout << "3 - Swap two songs in the playlist" << endl;
    cout << "4 - Print all the songs in the playlist" << endl;
    cout << "5 - Quit" << endl;

    do 
    {
        cout << endl;
        cout << "Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";
        cin >> choice;

        cin.ignore();

        if (choice == 1)
        {
            string name, artist;
            unsigned int pos;
            int length;

            cout << "Song name: ";
            getline(cin, name);
            cout << "Artist: ";
            getline(cin, artist); 
            cout << "Length: ";
            cin >> length;

            cin.ignore();

            unsigned int lastPosition = playlist.size();
            if (lastPosition == 0)
            {
                cout << "Position(1): ";
            }
            else
            {
                cout << "Position (1 to " << lastPosition + 1 << "): ";
            }
            cin >> pos;

            cin.ignore();

            while (pos < 1 || pos > lastPosition + 1) 
            {
                cout << "Invalid position! Enter a Valid Position from 1 to " << lastPosition + 1 << endl;
                cin >> pos;
            } 
            Song newSong(name, artist, length);
            playlist.insert(newSong, pos - 1);  // Adjust for 0-based index
            cout << "You entered " << name << " at position " << pos << " in the playlist" << endl;
        }
        else if (choice == 2)
        {
            if (playlist.size() > 0)
            {
                unsigned int pos;
                cout << "Position (1 to " << playlist.size() << "): ";
                cin >> pos;

                cin.ignore();

                while (pos < 1 || pos > playlist.size()) 
                {
                    cout << "Invalid position! Enter a Valid Position from 1 to " << playlist.size() << endl;
                    cin >> pos;
                } 
                Song removedSong = playlist.remove(pos - 1);  
                cout << "You removed " << removedSong.getName() << " from the playlist" << endl;
            }
            else
            {
                cout << "The Playlist is empty as of now" << endl;
            }
        }
        else if (choice == 3)
        {
            if (playlist.size() > 1)
            {
                unsigned int pos1, pos2;
                cout << "Swap song at position (1 to " << playlist.size() << "): ";
                cin >> pos1;
                cout << "with the song at position (1 to " << playlist.size() << "): ";
                cin >> pos2;

                cin.ignore();

                if ((pos1 >= 1 && pos1 <= playlist.size()) && (pos2 >= 1 && pos2 <= playlist.size())) 
                {
                    playlist.swap(pos1 - 1, pos2 - 1); 
                    cout << "You swapped the songs at positions " << pos1 << " and " << pos2 << endl;
                } 
                else
                {
                    cout << "Invalid position!" << endl;
                }  
            }    
            else if (playlist.size() == 1)
            {
                cout << "There is only 1 song, it cannot be swapped!" << endl;
            }
            else
            {
                cout << "The playlist is empty" << endl;
            }
        }
        else if (choice == 4)
        {
            unsigned int total = playlist.size();
            if (total == 0) 
            {
                cout << "The playlist is empty." << endl;
            }
            else
            {
                for (unsigned int i = 0; i < total; i++) // Using i < total to iterate over all items
                {
                    Song song = playlist.get(i);
                    cout << i + 1 << " " << song.getName() << " (" << song.getArtist() << ")" << " " << song.getLength() << "s" << endl;
                }
                cout << "There are " << total << " songs in the playlist." << endl;
            }
        }
        else if (choice < 1 || choice > 5)
        {
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    cout << "You have chosen to quit the program." << endl;
    return 0;
}
