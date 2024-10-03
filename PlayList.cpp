// Mujtaba Fatah Moahammed 13th September 2024
#include "PlayList.h"
#include <iostream>
#include<stdexcept>
using std::cout;
using std::endl;
using std::out_of_range;
using std::runtime_error;


// PlayList method implementations go here
PlayList::PlayList()
{
    head = nullptr; // Initializing the head pointer of the playlist to nullptr to show an empty list
    length = 0; //Since there are no songs the length will be 0
}

PlayList::PlayList(const PlayList& pl)
{
    //initializing an empty list
    head = nullptr;
    length = 0;
    PlayListNode* current = pl.head; // Start copying nodes from the source playlist
    unsigned int pos = 0;
    while (current != nullptr) 
    {
        insert(current->song, pos);   //Using the insert function to insert at the given position
        current = current->next;
        pos++; //incrementing the position for next position
    }
}

PlayList::~PlayList() 
{
    while (head != nullptr) // To ensure that all nodes are deleted
    {
        PlayListNode* temp = head; //To store current head temporarily
        head = head->next;
        delete temp;  
    }
}

PlayList& PlayList::operator=(const PlayList& pl) 
{
    if (this != &pl) // Check for self-assignment
    {  
        this->~PlayList();
        PlayListNode* current = pl.head;
        unsigned int pos = 0;
        while (current != nullptr) //Copies nodes pl to current
        {
            insert(current->song, pos);
            current = current->next;
            pos++;
        }
    }
    return *this;
}

void PlayList::insert(Song sng, unsigned int pos)
{
    if (pos > length) //ensures that pos isnt greater than length
        throw out_of_range("Position is out of range");

    PlayListNode* newNode = new PlayListNode(sng); // Create a new node with the given song

    if (pos == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        PlayListNode* current = head;
        for (unsigned int i = 0; i < pos - 1; i++) // Traverse the list to find the node before the insertion point
        {
            current = current->next;
        }
        newNode->next = current->next; // Insert the new node after current
        current->next = newNode;
    }
    length++; //Incrementing the length of the list
}

Song PlayList::remove(unsigned int pos) {
	if (pos >= length) // Check if the position is valid
    {
		throw out_of_range("Position is out of range");
	}
	PlayListNode* temp = nullptr;
	if (pos == 0) // Handle the case where removal is from the beginning
    {
		temp = head;
		head = head->next;
	} 
    else 
    {
		PlayListNode* current = head;
		for (unsigned int i = 0; i < pos - 1; ++i) 
        {
			current = current->next;
		}
		temp = current->next;
		current->next = temp->next;
	}
	Song removedSong = temp->song;
	delete temp;
	length--;
	return removedSong;
}

void PlayList::swap(unsigned int pos1, unsigned int pos2)
{
    if (pos1 >= length || pos2 >= length) //Ensures the position entered in in the range
    {
		throw out_of_range("Position is out of range");
	}
    if (pos1 ==  pos2) //To end the function
    {
        return;
    }
    else
    {
        PlayListNode* previousOne = nullptr;
        PlayListNode* one = head; 
        PlayListNode* previousTwo = nullptr;
        PlayListNode* two = head;

        for (unsigned int i = 0; i < pos1; ++i)
        {
            previousOne = one;
            one = one->next; 
        }
        for (unsigned int i = 0; i < pos2; ++i) 
        {
            previousTwo = two;
		    two = two->next;  
	    }

        if (previousOne != nullptr)
        {
            previousOne->next = two;
        }
        else
        {
            head = two;
        }

        if (previousTwo != nullptr)
        {
            previousTwo->next = one;
        }
        else
        {
            head = one;
        }

        PlayListNode* temp = one->next;
	    one->next = two->next; 
	    two->next = temp;
    }
}

Song PlayList::get(unsigned int pos) const 
{
	if (pos >= length)  // Check if the position is out of range
    {
		throw out_of_range("Position is out of range");
	}
	PlayListNode* current = head;
	for (unsigned int i = 0; i < pos; ++i) 
    {
		current = current->next;
	}
	return current->song; //Returns the song at specified position
}

unsigned int PlayList::size() const 
{ 
    return length; //Returns the size of the playlist
}
