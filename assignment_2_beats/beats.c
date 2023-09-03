// Assignment 2 20T1 COMP1511: CS bEats
// beats.c
//
// This program was written by LUM SUN YUAN (z5289055)
// on 12/4/2020
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Fix default return value of add_musical_note_to_beat.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.

#include "beats.h"

// Add your own #defines here.
#define MIN_OCTAVE 0
#define MAX_OCTAVE 9
#define MIN_KEY 0
#define MAX_KEY 11

////////////////////////////////////////////////////////////////////////

// You don't have to use the provided struct track, you are free to
// make your own struct instead.
// If you use the provided struct track, you will have to add fields
// to store other information.

struct track {
    // TODO: You will have to add extra fields here in Stage 2.
    
    struct beat *currentBeat;
    // stores currently selected beat
    struct beat *headBeat;
};

// You don't have to use the provided struct beat, you are free to
// make your own struct instead.
// If you use the provided struct beat, you may add fields
// to it to store other information.

struct beat {
    // You may choose to add or change fields in this struct.
    struct note *notes;
    struct beat *next;
};

// You don't have to use the provided struct note, you are free to
// make your own struct instead.
// If you use the provided struct note, you add fields
// to it to store other information.

struct note {
    // You may choose to add or change fields in this struct.
    int octave;
    int key;
    struct note *next;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////

// Add prototypes for any extra functions you create here.

// Return a malloced Beat with fields initialized.
Beat create_beat(void) {
    Beat new_beat = malloc(sizeof (struct beat));
    assert(new_beat != NULL);

    new_beat->next = NULL;
    new_beat->notes = NULL;

    // You do not need to change this function, unless you change
    // the implementation of struct beat.

    return new_beat;
}

// You need to implement the following functions.
// You can find descriptions of what each function should do in beats.h

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a note to the end of a beat.
int add_note_to_beat(Beat beat, int octave, int key) {

    struct note *currentNote = beat->notes;
    // create temporary note struct pointer to loop through while loop
    // using the first beat note so that the original beat note is not
    // changed in the while loop
            
    struct note *previousNote;
    // create temporary note struct pointer to store
    // previous beat of the current beat
        
    if (octave < MIN_OCTAVE || octave > MAX_OCTAVE) { 
        // check if the input octave is outside of the octave range
        
        // if it is outside of the octave range,
        // return INVALID_OCTAVE (octave is not valid)
        return INVALID_OCTAVE;
        
    } else if (octave >= MIN_OCTAVE && octave <= MAX_OCTAVE) {
        // check if the input octave is inside of the octave range
        
        // if it is in the octave range,
        if (key < MIN_KEY || key > MAX_KEY) {
            // check if the input key is outside of the key range
            
            // if it is outside of the key range,
            // return INVALID_KEY (octave is valid, but key is not)
            return INVALID_KEY;
            
        } else {
            // this runs if input key is inside of the key range
            
            if (currentNote == NULL) {
            
                struct note *addedNote = malloc(sizeof(struct note));
                addedNote->octave = octave;
                addedNote->key = key;
                // use malloc to define the new addedNote
                // change addedNote struct octave to input octave
                // change addedNote struct key to input key 
            
                beat->notes = addedNote;
                // replace the beat->notes (first struct node pointer in the
                // linked list (head) with the newly added note (addedNote)
            
                addedNote->next = NULL;
                // direct the new struct (addedNote) to point at NULL,
                // indicating the end of the list
            
                return VALID_NOTE;
                // as the note is a valid note and 
                // can be added into the linked 
                // list, return VALID_NOTE to show that a 
                // valid note has been inputted
            
            } else {
                while (currentNote != NULL) { 
                    // loops through all beat nodes in the list until it
                    // reaches the end of the linked list
                    if (octave < currentNote->octave) {
                        // return NOT_HIGHEST_NOTE if the input octave is 
                        // smaller than any of the octaves in the existing 
                        // beat nodes, as this shows that the input note is 
                        // not the highest note in the current 
                        // linked list (beat).
                        return NOT_HIGHEST_NOTE;
                    
                    } else if (octave == currentNote->octave) {
                        // checks if the input octave is equal to the octave 
                        // of the current note node in the linked list.
                    
                        if (key <= currentNote->key) {
                            // if the input key is less than the key of the
                            // current note node in the linked list,
                            // this shows that the input note is not the 
                            // highest. hence, return NOT_HIGHEST_NOTE
                            return NOT_HIGHEST_NOTE;
                        }
                    } 
                    previousNote = currentNote;
                    currentNote = currentNote->next;
                }
            
                // if the whole while loop has ended and looped through the 
                // whole linked list without returning any values and stopping
                // the program, this shows that the input note is the highest
                // note amongst all the notes in the existing linked list
                // thus, we can add the note to the list:
                struct note *addedNote = malloc(sizeof(struct note));
                addedNote->octave = octave;
                addedNote->key = key;
                // use malloc to define the new addedNote
                // change addedNote struct octave to input octave
                // change addedNote struct key to input key 
            
                previousNote->next = addedNote;
                // direct the last note struct in the linked list to point
                // at the new struct (addedNote)
            
                addedNote->next = NULL;
                // direct the new struct (addedNote) to point at NULL,
                // indicating the end of the list
            
                return VALID_NOTE;
                // as the note is a valid note and can be added into the 
                // linked list, return VALID_NOTE to show that a valid note 
                // has been inputted
            }
        }
    }
    return VALID_NOTE;
}

// Print the contents of a beat.
void print_beat(Beat beat) {
    struct note *currentNote = beat->notes;
    // create temporary note struct pointer to loop through while loop
    // using the first beat note so that the original beat note is not
    // changed in the while loop
    
    while (currentNote != NULL) {
        // loops through all notes in the beat linked list until it reaches 
        // the end of the linked list
        
        printf("%d ", currentNote->octave);
        // print octave of current note node 
        
        if (currentNote->key < 10) {
            // if key of current beat node is less than 10,
            printf("0%d", currentNote->key);
            // print the key of the current beat node with a 0 in front
            
        } else if (currentNote->key >= 10) {
            // if the key of the current beat node is equal or more than 10,
            printf("%d", currentNote->key);
            // print the key of the current note node
        }
        
        if (currentNote->next != NULL) {
            printf(" | ");
        }
        
        currentNote = currentNote->next;
    }
    printf("\n");
}

// Count the number of notes in a beat that are in a given octave.
int count_notes_in_octave(Beat beat, int octave) {
    struct note *currentNote = beat->notes;

    int totalNotesOctave = 0;
    // totalNotesOctave represents total notes within the given octave 
    while (currentNote != NULL) {
        // loops through all note nodes in the beat linked list 
        // until it reaches the end of the linked list
        
        if (currentNote->octave == octave) { 
            // check if the octave of the current note node is equal to the
            // given input octave
            totalNotesOctave++;
            // if it is equal, add one to the totalNotesOctave variable 
        }
        currentNote = currentNote->next;
    }
    return totalNotesOctave;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Return a malloced track with fields initialized.
Track create_track(void) {
    // Note: there is no fprintf in this function, as the
    // Stage 1 autotests call create_track but expect it to return NULL
    // (so this function should do nothing in Stage 1).
    
    struct track *newTrack = malloc(sizeof(struct track));
    newTrack->currentBeat = NULL;
    newTrack->headBeat = NULL;
    // use malloc to define the new track
    // direct currentBeat node and headBeat node towards NULL 
    // as it starts with an empty list

    return newTrack;
}

// Add a beat after the current beat in a track.
void add_beat_to_track(Track track, Beat beat) {
    if (track->currentBeat == NULL) {
        // if the currently selected beat (track->currentBeat) is 
        // not selected (track is 'stopped')
        // insert given beat as the first element of the Track.
        
        if (track->headBeat == NULL) {
            // if track->headBeat is NULL, this shows that the start of 
            // the headBeat linked list is empty, which indicates that 
            // the whole headBeat linked list is empty (NULL)
            
            track->headBeat = beat;
            // replace the start of the headBeat linked list (track->headBeat
            // with beat
            
            track->headBeat->next = NULL;
            // replace the next element of the headBeat linked list
            // (track->headBeat->next) with NULL
            
        } else if (track->headBeat != NULL) {
            // if track->headBeat is not NULL, this shows that the start of
            // the headBeat linked list is not empty, which indicates that
            // elements are present in the whole headBeat linked list.
            
            beat->next = track->headBeat;
            // point the beat pointer to point at the original 
            // head of the headBeat linked list.
            
            track->headBeat = beat;
            // replace the head of the linked list with
            // the newly added beat (beat)
        }
        
    } else if (track->currentBeat != NULL) {
        // if the currently selected beat (track->currentBeat) is
        // selected (track is 'playing');
        
        beat->next = track->currentBeat->next;
        // copy and change the new beat (beat) to direct it at the
        // next beat node (currentBeat->next)
        
        track->currentBeat->next = beat;
        // change the currentBeat (insertion point) to 
        // direct it at the new beat (beat)
    }
    return;
}

// Set a track's current beat to the next beat.
int select_next_beat(Track track) {
    struct beat *checkerBeat = track->headBeat;
    // create temporary note struct pointer (checkerBeat) to loop 
    // through while loop using the first beat note so that the 
    // original beat note is not changed in the while loop
    
    if (track->currentBeat == NULL) {
        // if the currentBeat is NULL, this shows that the linked list
        // is either empty or the currentBeat has reached the end of the 
        // linked list (no currently selected beat)
        
        if (track->headBeat == NULL) {
            // if the first element of the linked list is NULL, this shows
            // that the linked list is empty as it contains no elements inside
            // it. 
            // Do nothing and return TRACK_STOPPED 
            return TRACK_STOPPED;
                        
        } else if (track->headBeat != NULL) {
            // if the first elemnt of the linked list is not NULL, this shows
            // that the linked list is not empty as it contains at least one
            // element inside it. This indicates that the currentBeat has 
            // reached the end of the linked list.
            // replace currentBeat with the first element of the linked list,
            // which is headBeat (first beat in the track)
            // and return TRACK_PLAYING
            track->currentBeat = track->headBeat;
            return TRACK_PLAYING;
        }
        
    } else if (track->currentBeat != NULL) {
        // checks if the currentBeat in the track is not NULL.
        while (checkerBeat != track->currentBeat) {
            // loop through the beat linked list and stop when the 
            // checkerBeat is equal to the currentBeat.
            // checkerBeat will be equal to the currentBeat after the 
            // while loop exits
            checkerBeat = checkerBeat->next;
        }
        track->currentBeat = checkerBeat->next;
        // change currentBeat and direct it to point at the next element
        // after the checkerBeat (which was the old currentBeat)
        if (track->currentBeat == NULL) {
            // if the newly changed currentBeat is NULL, this indicates that
            // it has reached the end of the linked list.
            // return TRACK_STOPPED (no beat is currently selected)
            return TRACK_STOPPED;
            
        } else if (track->currentBeat != NULL) {
            // if the newly changed currentBeat is not NULL, this indicates 
            // that it has not reached the end of the linked list and is 
            // still pointing at one of the elements in the linked list.
            // return TRACK_PLAYING (beat is currently selected)
            return TRACK_PLAYING;
        }
    }
    return TRACK_STOPPED;
}

// Print the contents of a track.
void print_track(Track track) {
    struct beat *checkerBeat = track->headBeat;
    // create temporary note struct pointer (checkerBeat) to loop 
    // through while loop using the first beat note so that the 
    // original beat note is not changed in the while loop
    
    int numNote = 1;
    // int variable numNote to keep track of the beat note number as 
    // the while loop is looping
    while (checkerBeat != NULL) {
        // loop through the beat nodes in the track
        if (checkerBeat == track->currentBeat) {
            // if the current beat node is equal to the 
            // currentBeat of the track, print ">" 
            printf(">");
        } else if (checkerBeat != track->currentBeat) {
            // if the current beat node is not equal to the 
            //  currentBeat of the track, print " " 
            printf(" ");
        }
        printf("[%d] ", numNote);
        // print the note number of the beat that is being printed
        print_beat(checkerBeat);
        // call the print_beat function on the currently looped beat to 
        // print all the notes in the beat
        numNote++;
        checkerBeat = checkerBeat->next;
    }
}

// Count beats after the current beat in a track.
int count_beats_left_in_track(Track track) {
    int totalBeatsPrev = 1;
    int totalBeats = 0;
    int totalBeatsLeft = 0;
    
    struct beat *checkerTotalBeat = track->headBeat;
    struct beat *checkerBeat = track->headBeat;
    if (track->currentBeat == NULL) {
        // if currentBeat is equal to NULL, then the track is stopped,
        // which means all the beats in the track has to be counted
        while (checkerTotalBeat != NULL) { 
            // loops through all the beat nodes in the linked list until 
            // the end, and adds one to totalBeatsLeft everytime the loop
            // runs
            // totalBeatsLeft represents the total 
            // number of beats in the track
            totalBeatsLeft++;
            checkerTotalBeat = checkerTotalBeat->next;
        }
    } else if (track->currentBeat != NULL) {
        // if currentBeat is not equal to NULL, then the track is playing,
        // (there is a selected beat) which means only the beats after the
        // selected beat has to be counted.
        while (checkerTotalBeat != NULL) {
            // loops through all the beat nodes in the linked list until
            // the end, and adds one to totalBeats everytime the loop
            // runs
            // totalBeats represents the total number of beats in the track
            totalBeats++;
            checkerTotalBeat = checkerTotalBeat->next;
        }
        while (checkerBeat != NULL && checkerBeat != track->currentBeat) {
            // if the linked list is not empty and the checkerBeat is not
            // equal to the currently selected beat (currentBeat),
            // loop through the list and add one to totalBeatsPrev everytime
            // the loop runs
            // totalBeatsPrev represents the number of beats from the start
            // of the beats linked list to the currentBeat (excluding 
            // currentBeat) 
            // note that totalBeatsPrev starts with 1 and not 0 as 1 is added
            // into totalBeatsPrev to include the currentBeat in the 
            // totalBeatsPrev
            totalBeatsPrev++;
            checkerBeat = checkerBeat->next;
        }
        // totalBeatsLeft in the linked list is the total number of beats 
        // (totalBeats) minus the total number of beats before the currently
        // selected beat and the currently selected beat, which leaves
        // the number of remaining beats after the currently selected beat,
        // which is totalBeatsLeft
        totalBeatsLeft = totalBeats - totalBeatsPrev;
    }
    // return the total number of beats left
    return totalBeatsLeft;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Free the memory of a beat, and any memory it points to.
void free_beat(Beat beat) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_beat but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than exit).
    
    struct note *current = beat->notes;
    struct note *previous = NULL;
    if (beat != NULL) {
        // if beat is not NULL (not empty) then loop through and free the 
        // associated memory of the contents in beat and the beat itself.
        while (current != NULL) {
            // loop from the start of the notes linked list to the end of the 
            // notes linked list (until current is NULL)
        
            previous = current;        
            current = current->next;                
            free(previous);
            // use previous and current to keep track of note nodes pointers
            // so that when free is called, the next note node in the linked
            // list is still accessible
        }
        free(beat);
        // after freeing all the notes in beat, free the beat as there are no
        // more memory associated with the notes inside the beat.
    }
    // if beat is NULL, do nothing.
    return;
}

// Free the memory of a track, and any memory it points to.
void free_track(Track track) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_track but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than print an error).
    
    Beat current = track->headBeat;
    Beat previous = NULL;
    if (track != NULL) {
        // if track is not NULL (not empty) then loop through and free the 
        // associated memory of the contents in track and the track itself.
        while (current != NULL) {
            // loop from the start of the beats linked list to the end of the 
            // beats linked list (until current is NULL)
            
            previous = current;        
            current = current->next;                
            free_beat(previous);
            // use previous and current to keep track of beat nodes pointers
            // so that when free_beat is called, the next beat node in the 
            // linked list is still accessible
            // free_beat is called to free the notes inside the selected beat
            // node then free the beat itself, freeing all associated 
            // memory of the currently selected beat.
        }
        free(track);
        // after freeing all the beats in track, free the track as there are 
        // no more memory associated with the beats inside the track.
    }
    // if track is NULL, do nothing.
    return;
}

// Remove the currently selected beat from a track.
int remove_selected_beat(Track track) {
    struct beat *checkerBeat = track->headBeat;
    struct beat *prevBeat = NULL;
    if (track->currentBeat == NULL) {
        // if there is no currently selected beat, do not remove any beat 
        // (do nothing and return TRACK_STOPPED)
        return TRACK_STOPPED;      
    } else if (track->currentBeat != NULL) {
        // checks if there is a currently selected beat 
        while (checkerBeat != NULL && checkerBeat != track->currentBeat) {
            // loops through until checkerBeat is equal to currentBeat,
            // and prevBeat is the beat node right before the currentBeat
            prevBeat = checkerBeat;
            checkerBeat = checkerBeat->next;
        }
        if (prevBeat != NULL) {
            // if prevBeat is not NULL, this means that the currently 
            // selected beat (currentBeat) is not the first beat node 
            // in the linked list
            
            prevBeat->next = checkerBeat->next;
            // point the previousBeat at the next node of checkerBeat 
            // (one after the currently selected beat)
            track->currentBeat = checkerBeat->next;
            // set the track's currently selected beat (currentBeat) to
            // checkerBeat->next, which is the beat node after the old
            // currently selected beat (currentBeat)
            free_beat(checkerBeat); 
            // free the old currently selected beat 
            
            if (prevBeat->next == NULL) {
                // if the next node of prevBeat is NULL, this means that 
                // there were no more beats after the original currently 
                // selected beat, which means that the new currently selected
                // beat is now NULL (meaning there are no currently selected 
                // beats 
                // return TRACK_STOPPED (there is no currently selected beat)
                return TRACK_STOPPED;
            } else if (prevBeat->next != NULL) {
                // if the next node of prevBeat is not NULL, this means that
                // there are beats after the original currently selected 
                // beat, which means that the new currently selected beat is
                // still pointing at a beat node (meaning there is still a 
                // currently selected beat)
                // return TRACK_PLAYING (there is a currently selected beat)
                return TRACK_PLAYING;
            }
        } else if (prevBeat == NULL) {
            // if prevBeat is NULL, this means that the currently 
            // selected beat (currentBeat) is the first beat node 
            // in the linked list
            
            track->headBeat = checkerBeat->next;
            // set the headBeat of the track to point at the next node of
            // the original currently selected beat 
            track->currentBeat = checkerBeat->next;
            // set the currentBeat of the track to point at the next node of
            // the original currently selected beat
        }    
        free_beat(checkerBeat); 
        // free the old currently selected beat
        
        if (track->currentBeat == NULL) {
            // if the currentBeat of the track is NULL, this means that 
            // there were no more beats after the original currently 
            // selected beat, which means that the new currently selected
            // beat is now NULL (meaning there are no currently selected 
            // beats 
            // return TRACK_STOPPED (there is no currently selected beat)
            return TRACK_STOPPED;
        } else if (track->currentBeat != NULL) {
            // if the currentBeat is not NULL, this means that
            // there are beats after the original currently selected 
            // beat, which means that the new currently selected beat is
            // still pointing at a beat node (meaning there is still a 
            // currently selected beat)
            // return TRACK_PLAYING (there is a currently selected beat)
            return TRACK_PLAYING;
        }
    }
    return TRACK_STOPPED;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add note to beat, given its 'musical notation'.
int add_musical_note_to_beat(Beat beat, char *musical_notation) {
    int inputOctave = musical_notation[0];
    // set inputOctave to be the first character of musical_notation
    // (represents the octave of the input note)
    
    // convert the characters of the musical_notation to number values
    // and put them back into inputOctave
    // (convert '0' into 0, '1' into 1 and so on...)
    // ('0' and 0 are different)
    int counter = 0;
    int inputNum = inputOctave - '0';
    inputOctave = 0;
    while (counter < inputNum) {
        inputOctave++;
        counter++;
    }
    if (inputOctave < MIN_OCTAVE || inputOctave > MAX_OCTAVE) {
        return INVALID_MUSICAL_NOTE;
    }
    
    int inputKey = musical_notation[1];
    // set inputKey to be the second character of the musical_notation 
    // (represents the key of the input note)
    
    // convert the characters of the musical_notation to number values 
    // and put them back into inputKey
    // (convert 'A' into 0, 'B' into 2 and so on...)
    // only convert the characters if they are valid (from 'A' to 'G')
    if (inputKey == 'A') {
        inputKey = 0;
    } else if (inputKey == 'B') {
        inputKey = 2;
    } else if (inputKey == 'C') {
        inputKey = 3;
    } else if (inputKey == 'D') {
        inputKey = 5;
    } else if (inputKey == 'E') {
        inputKey = 7;
    } else if (inputKey == 'F') {
        inputKey = 8;
    } else if (inputKey == 'G') {
        inputKey = 10;
    } else { 
        // if inputKey is not converted, this indicates that the input
        // being entered into inputKey does not suit the format
        // hence, do nothing and return INVALID_MUSICAL_NOTE
        return INVALID_MUSICAL_NOTE;
    }
    
    int i = 2;
    // int variable i starts at 2 as the first two values in the 
    // musical_notation array are used to determine
    // inputKey and inputOctave 
    int numSharps = 0;
    // int variable numSharps records the number of sharps
    while (musical_notation[i] != '\0') {
        // loops while the musical_notation array has not reached 
        // the end (has not reached the NULL terminator)
        if (musical_notation[i] == '#') {
            // add 1 to the numSharps variable if the value in the
            // selected musical_notation array is '#'
            numSharps++;
        } else {
            // if the musical notation is not '\0' and '#', this indicates
            // that invalid input has been entered
            // hence, do nothing and return INVALID_MUSICAL_NOTE
            return INVALID_MUSICAL_NOTE;
        }
        i++;
    }
    
    inputKey = inputKey + numSharps;
    // add the number of sharps to inputKey
    while (inputKey > MAX_KEY) {
        // loops if the inputKey is more than the MAX_KEY
        
        inputOctave++;
        // add 1 to inputOctave as when the key is bigger than the MAX_KEY,
        // keys are transferred into the octave 
        
        // change the keys into the octaves until the inputKey is no longer
        // more than the inputKey, which makes it a valid key 
        int j = inputKey - MAX_KEY;
        inputKey = -1;
        while (j > 0) {
            inputKey++;
            j--;
        }        
    } 
    if (inputOctave < MIN_OCTAVE || inputOctave > MAX_OCTAVE) {
        // if after converting the inputKey into a valid inputKey, 
        // the inputOctave is smaller than the MIN_OCTAVE or bigger than 
        // the MAX_OCTAVE, this shows that invalid input has been entered
        // do nothing and return INVALID_MUSICAL_NOTE;
        return INVALID_MUSICAL_NOTE;
    } 
    
    struct note *currentNote = beat->notes;
    struct note *insertionPoint = NULL;
    while (currentNote != NULL) {
        // loop through all the note nodes in the beat linked list
        if (currentNote->octave == inputOctave && 
            currentNote->key == inputKey) {
            // if the currently looped note has the same octave and key as 
            // the inputOctave and inputKey, this shows that the same note
            // is already in the beat 
            // hence, do nothing and return INVALID_MUSICAL_NOTE
            return INVALID_MUSICAL_NOTE;
        }
        
        // by the end of the while loop, the insertionPoint will be the
        // note node which is a note node before the first note that is 
        // higher than the inputted note 
        if (inputOctave > currentNote->octave) {
            // if the currently looped note's octave is lower than
            // the inputOctave, set the insertionPoint as the currently 
            // looped note 
            insertionPoint = currentNote;
        } else if (inputOctave == currentNote->octave
            && inputKey > currentNote->key) {
            // if the currently looped note's octave is equal to the 
            // inputOctave and the currently looped note's key is lower 
            // than the inputKey, set the insertionPoint as the currently 
            // looped note    
            insertionPoint = currentNote;
        }
        currentNote = currentNote->next;
    }
    
    struct note *newNote = malloc(sizeof(struct note));
    // create a newNote note using malloc 
    newNote->octave = inputOctave;
    newNote->key = inputKey;
    // set the newNote's octave and key to the inputOctave and inputKey 
    
    if (beat->notes == NULL) {
        // if the notes linked list in the beat is empty,
        // set the first note in the beat to be newNote (head of the notes 
        // linked list) and then direct the newNote to point to NULL as
        // it is currently the only note present in the list.
        beat->notes = newNote;
        newNote->next = NULL;
    } else if (beat->notes != NULL) {
        // checks if the notes linked list in the beat is not empty
        if (insertionPoint == NULL) {
            // if the insertionPoint is NULL, this means that the 
            // insertionPoint is at the start of the notes linked list
            newNote->next = beat->notes;  
            beat->notes = newNote;
            // set the newNote to point at the first note in the linked
            // list, then set the first note in the beat to be newNote (head 
            // of the notes linked list)
        } else if (insertionPoint != NULL) {
            // if the insertionPoint is not NULL, this means that
            // the insertionPoint is either in the middle or at the end of
            // the notes linked list 
            newNote->next = insertionPoint->next;
            insertionPoint->next = newNote;
            // set the newNote to point at the next node of the
            // insertionPoint, then direct the insertionPoint to point at
            // the newNote 
        }
    }
    // return VALID_NOTE as a valid note has been added 
    return VALID_NOTE;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Cut a range of beats to the end of a track.
void cut_range_to_end(Track track, int range_length) {
    struct beat *previousBeat = NULL;
    struct beat *headBeat = track->headBeat;
    struct beat *currentBeat = track->currentBeat;
    int remainingBeats = count_beats_left_in_track(track) + 1;
    // call count_beats_left_in_track to count the remaining beats in the
    // track and add 1 to it (to include the currently selected beat)
    if (range_length > remainingBeats) {
        // if the range_length is more than the remainingBeats, 
        // limit and set the range_length to be equal to remainingBeats 
        range_length = remainingBeats;
    }
    
    struct beat *lastBeat = track->headBeat;
    while (lastBeat->next != NULL) {
        // loop through the beat nodes in the linked list until it reaches
        // the last beat node in the linked list 
        // then set lastBeat as the last beat node in the linked list 
        lastBeat = lastBeat->next;
    }
    
    if (range_length < 1) {
        // if the range_length is less than 1, do nothing and return 
        return;
    }
    
    if (currentBeat == NULL) {
        // if there is no currently selected beat, do nothing and return 
        return;
    } else if (currentBeat == headBeat) {
        // checks if the currently selected beat (currentBeat) is equal to 
        // the start of the beats linked list (headBeat)
        int i = 0;
        while (i < range_length) {
            // loops range_length number of times
            lastBeat->next = currentBeat;
            // set the last beat node in the linked list (lastBeat) to 
            // point at the currently selected beat (currentBeat)
            lastBeat = lastBeat->next;
            // set lastBeat to be equal to the newly added lastBeat->next,
            // which is the currentBeat
            currentBeat = currentBeat->next; 
            // set currentBeat to be equal to currentBeat->next
            i++;
        }
        lastBeat->next = NULL;
        // direct the lastBeat to point at NULL
        track->headBeat = currentBeat;
        // set the head beat of the track to point at currentBeat, which 
        // is now the beat node right after the range of cut beat nodes 
        
    } else if (currentBeat != headBeat) {
        // checks if the currently selected beat (currentBeat) is not equal 
        // to the start of the beats linked list (headBeat)
        while (headBeat != currentBeat) {
            // loops while headBeat is not equal to currentBeat
            previousBeat = headBeat;
            // set previousBeat to be equal to headBeat
            headBeat = headBeat->next;
            // set headBeat to be equal to headBeat->next
        }
        // after the while loop above has finished, previousBeat will be 
        // the beat node before the currently selected beat
        
        int i = 0;
        while (i < range_length) {
            // loops range_length number of times
            lastBeat->next = currentBeat;
            // set the last beat node in the linked list (lastBeat) to 
            // point at the currently selected beat (currentBeat)
            lastBeat = lastBeat->next;
            // set lastBeat to be equal to the newly added lastBeat->next,
            // which is the currentBeat
            currentBeat = currentBeat->next;   
            // set currentBeat to be equal to currentBeat->next 
            i++;
        }
        lastBeat->next = NULL;
        // direct the lastBeat to point at NULL
        previousBeat->next = currentBeat;
        // direct the beat node before the original currently selected beat 
        // (previousBeat) to point at the currentBeat, which is the beat node
        // right after the range of cut beat nodes 
    }
    return;
}

// Reverse a list of beats within a range of a track.
int reverse_range(Track track, int range_length) {
    struct beat *headBeat = track->headBeat;
    struct beat *currentBeat = track->currentBeat;
    int remainingBeats = count_beats_left_in_track(track) + 1;
    // call count_beats_left_in_track to count the remaining beats in the
    // track and add 1 to it (to include the currently selected beat)
    if (range_length > remainingBeats) {
        // if the range_length is more than the remainingBeats, 
        // limit and set the range_length to be equal to remainingBeats 
        range_length = remainingBeats;
    }
    int reversedBeats = range_length - 1;
    // reversedBeats variable is the range_length - 1 (represents the 
    // number of beats reversed) 
    if (range_length < 1) {
        // if the range_length is less than 1, set the reversedBeats to 0
        // then return reversedBeats
        reversedBeats = 0;
        return reversedBeats;
    }
    
    if (currentBeat == NULL) {
        // if there is no currently selected beat, set the reversedBeats
        // to 0 then return reversedBeats
        reversedBeats = 0;
        return reversedBeats;
    } else if (currentBeat != NULL) {
        // checks if there is a currently selected beat
        int i = 0;
        struct beat *lastBeatInRange = currentBeat;
        while (i < range_length - 1) {
            // loops range_length - 1 number of times to find 
            // the last beat in the range and set it to lastBeatInRange
            lastBeatInRange = lastBeatInRange->next;
            i++;
        }
        struct beat *firstBeatOutRange = lastBeatInRange->next;
        // set firstBeatOutRange to be equal to the next beat node after 
        // the last beat in the range (lastBeatInRange)
        if (currentBeat == headBeat) {
            // if the currently selected beat (currentBeat) is 
            //  equal to the head of the beats linked list (headBeat),
            // set the track's headBeat to be equal to the lastBeatInRange 
            track->headBeat = lastBeatInRange;
        } else if (currentBeat != headBeat) {
            // checks if the currently selected beat (currentBeat) is not
            // equal to the heads of the beats linked list (headBeat),
            struct beat *previousBeat = headBeat;
            while (previousBeat->next != currentBeat) {
                // loop while the previousBeat->next is not equal to
                // currentBeat
                previousBeat = previousBeat->next;
                // by the end of this while loop, previousBeat will be equal
                // to the beat node right before the currently selected beat 
                // (currentBeat)
            } 
            previousBeat->next = lastBeatInRange;
            // direct previousBeat to point at the lastBeatInRange
        }
        int j = 0;
        while (j < range_length - 1) {
            // loops range_length - 1 number of times 
            int k = j;
            // sets k to be equal to j (which increases by 1 every loop)
            while (k < range_length - 2) {
                // loops range_length - 2 - k number of times 
                currentBeat = currentBeat->next;
                k++;
                // this while loop is used to find the currentBeat
            }
            lastBeatInRange->next = currentBeat;
            // direct lastBeatInRange to point at currentBeat 
            lastBeatInRange = lastBeatInRange->next;
            // set lastBeatInRange to lastBeatInRange->next
            currentBeat = track->currentBeat;
            // set currentBeat to be equal to the track's currentBeat
            // (reset the currentBeat so that the currentBeat is unchanged)
            j++;
        }
        lastBeatInRange->next = firstBeatOutRange;
        // direct the lastBeatInRange to point at the firstBeatOutRange
        lastBeatInRange = lastBeatInRange->next;
        // replace the lastBeatInRange with lastBeatInRange->next
    }
    // return the number of beats reversed (reversedBeats)
    return reversedBeats;
}
