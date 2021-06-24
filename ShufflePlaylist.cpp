/**This code imitates the music playlist in which you can add song,
 * play any song from the current playlist, and
 * let the playlist play the songs in order.
 */

#include <bits/stdc++.h>
using namespace std;

class Playlist {

list<string> playlist;
map<string, list<string>::iterator> songIterator;
list<string>::iterator currSongIndex;

public:
    string addSong(string name) {
        if(songIterator.find(name) != songIterator.end()) {
            return "Song already present!!";
        }
        if(playlist.size() == 0) {
            songIterator[name] = playlist.insert(playlist.end(), name);
            currSongIndex = playlist.begin();
        } else {
            songIterator[name] = playlist.insert(currSongIndex, name);
        }
        return name + " added!";
    }

    string getNextSong() {
        if(playlist.size() == 0) {
            return "No Song present!!";
        }
        string name = *currSongIndex;
        ++currSongIndex;
        if(currSongIndex == playlist.end()) {
            currSongIndex = playlist.begin();
        }
        return name;
    }

    string playSong(string name) {
        if(songIterator.find(name) == songIterator.end()) {
            return "Song not present!!";
        }
        if(currSongIndex == songIterator[name]) {
            return getNextSong();
        }
        playlist.erase(songIterator[name]);
        songIterator[name] = playlist.insert(currSongIndex, name);
        return name;
    }
};

int main()
{
    Playlist playlist = Playlist();
    while(true) {
        int option;
        string input;
        cin >> option;
        if(option == 1) {
            cin >> input;
            cout << playlist.addSong(input) << endl;
        } else if(option == 2) {
            cout << playlist.getNextSong() << endl;
        } else {
            cin >> input;
            cout << playlist.playSong(input) << endl;
        }
    }
    return 0;
}