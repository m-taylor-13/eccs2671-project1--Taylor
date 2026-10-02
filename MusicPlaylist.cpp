// ECCS 2671 - Project 1: Doubly Linked List Implementation (Music Playlist)
//
// Do NOT modify the constructor, destructor, getNumSongs(), or the
// operator<< friend function below -- they are already implemented.
//
// Student 1 implements the functions marked "STUDENT 1" below.
// Student 2 implements the functions marked "STUDENT 2" below.

//Student 1 & 2: Margaret Taylor

#include "MusicPlaylist.h"

//function to update song numbers sequentially
static void updateSongNumbers(SongNode* head) {

    int pos = 1;
    SongNode* cur = head;
    while (cur != nullptr) {
        cur->songNumber = pos++;
        cur = cur->next;
    }
}

// ---------------------------------------------------------------------
// Already implemented - do not modify
// ---------------------------------------------------------------------
MusicPlaylist::MusicPlaylist() {
    head = nullptr;
    tail = nullptr;
    numSongs = 0;
}

MusicPlaylist::~MusicPlaylist() {
    SongNode* cur = head;
    while (cur != nullptr) {
        SongNode* toDelete = cur;
        cur = cur->next;
        delete toDelete;
    }//
    head = nullptr;
    tail = nullptr;
    numSongs = 0;
}

int MusicPlaylist::getNumSongs() {
    return numSongs;
}

ostream& operator<<(ostream& os, const MusicPlaylist& list) {
    SongNode* cur = list.head;
    if (cur == nullptr) {
        os << "Empty Play List" << endl;
        return os;
    }
    while (cur != nullptr) {
        os << cur->songNumber << ". " << cur->songName;
        if (!cur->artistName.empty()) {
            os << " - " << cur->artistName;
        }
        os << endl;
        cur = cur->next;
    }
    return os;
}

// =======================================================================
// STUDENT 1 - implement the five functions below
// =======================================================================

// Traverses the list looking for the given song name and returns a
// pointer to the first node with that name, or nullptr if not present.
SongNode* MusicPlaylist::getSongNode(const string song) {
    SongNode* cur = head;
    while (cur != nullptr) {
        if (cur->songName == song) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

// Adds a new song at the head of the playlist. All other song numbers
// shift up by one. No artist is given, so use an empty string.
void MusicPlaylist::addSong(const string addedSongName) {

    SongNode* newNode = new SongNode(addedSongName, "", 1, nullptr, head);

    if (head != nullptr) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
    numSongs++;

    updateSongNumbers(head);
}

// Adds a new song at position songOrder (valid range 1..numSongs).
// If songOrder < 2, place at the head; if songOrder > numSongs, place
// at the tail. No artist is given, so use an empty string.
void MusicPlaylist::addSong(const string addedSongName, const int songOrder) {
    addSong(addedSongName, songOrder, "");
}

// Deletes the song node with the given name, if present.
void MusicPlaylist::deleteSong(const string deletedSongName) {
    SongNode* target = getSongNode(deletedSongName);

    //if the song isnt found or list empty
    if (target == nullptr) {
        return; 
    }

    if (target->prev != nullptr) {
        target->prev->next = target->next;
    } else {
        head = target->next;
    }

    if (target->next != nullptr) {
        target->next->prev = target->prev;
    } else {
        tail = target->prev; // Deleting tail node
    }

    delete target;
    numSongs--;

    updateSongNumbers(head);
}

// Searches for searchedSongName and returns its song number if found,
// or -1 if it is not in the playlist.
int MusicPlaylist::getSongNum(const string searchedSongName) {
    SongNode* target = getSongNode(searchedSongName);
    if (target != nullptr) {
        return target->songNumber;
    }
    return -1;
}

// =======================================================================
// STUDENT 2 - implement the five functions below
// =======================================================================

// Traverses the list looking for the node with the given song number.
// Return head if songNumber < 2, tail if songNumber >= numSongs, or the
// first node whose song number is at least songNumber.
SongNode* MusicPlaylist::getSongNode(const int songNumber) {
    if (head == nullptr) {
        return nullptr;
    }
    if (songNumber < 2) {
        return head;
    }
    if (songNumber >= numSongs) {
        return tail;
    }

    SongNode* cur = head;
    while (cur != nullptr) {
        if (cur->songNumber >= songNumber) {
            return cur;
        }
        cur = cur->next;
    }
    return tail;
}

// Adds a new song at position songOrder (valid range 1..numSongs) with
// the given artist. If songOrder < 2, place at the head; if
// songOrder > numSongs, place at the tail.
void MusicPlaylist::addSong(const string addedSongName, const int songOrder, const string artistName) {
    if (head == nullptr || songOrder < 2) {
        SongNode* newNode = new SongNode(addedSongName, artistName, 1, nullptr, head);

        if (head != nullptr) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
    } else if (songOrder > numSongs) {
        SongNode* newNode = new SongNode(addedSongName, artistName, numSongs + 1, tail, nullptr);

        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
    } else {
        // Insert in middle (before target node at songOrder)
        SongNode* target = getSongNode(songOrder);
        SongNode* newNode = new SongNode(addedSongName, artistName, songOrder, target->prev, target);

        if (target->prev != nullptr) {
            target->prev->next = newNode;
        }
        target->prev = newNode;
    }

    numSongs++;
    updateSongNumbers(head);
}

// Deletes the last song in the playlist (at the tail).
void MusicPlaylist::deleteLastSong() {


    if (tail == nullptr) {
        return; 
    }

    SongNode* target = tail;
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete target;
    numSongs--;
    updateSongNumbers(head);
}

// Deletes the song node at the given position (songNumInList). Delete
// the first song if songNumInList < 2, or the last node if
// songNumInList >= numSongs.
void MusicPlaylist::deleteSong(const int songNumInList) {
    if (head == nullptr) {
        return;
    }

    if(songNumInList < 2){
        SongNode* target = head;
        head = head->next;

        if(head !=nullptr){head->prev = nullptr;}
        else {tail = nullptr;}

        delete target;
    } else if (songNumInList >= numSongs){
        deleteLastSong();
        return;
    } else{

        SongNode* target = getSongNode(songNumInList);
        if (target != nullptr) {
            if (target->prev != nullptr) {
                target->prev->next = target->next;
            }
            if (target->next != nullptr) {
                target->next->prev = target->prev;
            }
            delete target;
        }
    }
//
}

// Returns the name of the song at the given position. Return the head's
// name if songNumInList < 2, and the tail's name if
// songNumInList >= numSongs. For an empty list, return "Empty Play List".
string MusicPlaylist::getSongName(const int songNumInList) {
    if(head == nullptr){
        return "Empty Play List";

    }
    if(songNumInList < 2){
        return head->songName;
    }
    if(songNumInList >= numSongs){
        return tail->songName;
    }

    SongNode* target = getSongNode(songNumInList);

    if(target !=nullptr){
        return target->songName;
    }
    return "Empty Play List";
    //
}