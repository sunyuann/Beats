// Assignment 2 20T1 COMP1511: CS bEats
// test_beats.c
//
// This program was written by LUM SUN YUAN (z5289055)
// on 12/4/2020
//
// Version 1.0.0: Assignment released.
#include <stdio.h>
#include <stdlib.h>

#include "test_beats.h"
#include "beats.h"


// Test function for `add_note_to_beat`
int test_add_note_to_beat(void) {
    // Test 1: Rejecting negative inputs.
    Beat test_beat = create_beat();
    if (add_note_to_beat(test_beat, -1, -1) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, -1, 0) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 1, -1) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Rejecting same notes that are inputted twice
    // TODO: Write Test 2
    if (add_note_to_beat(test_beat, 2, 2) == VALID_NOTE) {
        if (add_note_to_beat(test_beat, 2, 2) != NOT_HIGHEST_NOTE) {
            return DOES_NOT_MEET_SPEC;
        }
    }

    // Test 3: Rejecting lower notes that are inputted.
    // TODO: Write Test 3
    if (add_note_to_beat(test_beat, 2, 2) == VALID_NOTE) {
        if (add_note_to_beat(test_beat, 1, 1) != NOT_HIGHEST_NOTE) {
            return DOES_NOT_MEET_SPEC;
        }
    }
    
    // Test 4: Accepting higher notes that are inputted.
    if (add_note_to_beat(test_beat, 2, 2) == VALID_NOTE) {
        if (add_note_to_beat(test_beat, 3, 3) != VALID_NOTE) {
            return DOES_NOT_MEET_SPEC;
        }
    }
    return MEETS_SPEC;
}

// Test function for `count_notes_in_octave`
int test_count_notes_in_octave(void){
    // Test 1: Counting octaves in empty beat.
    Beat test_beat = create_beat();
    if (count_notes_in_octave(test_beat, 1) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 2) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 2: Counting valid octaves.
    // TODO: Write Test 2
    add_note_to_beat(test_beat, 1, 1);
    add_note_to_beat(test_beat, 2, 2);
    add_note_to_beat(test_beat, 2, 6);
    if (count_notes_in_octave(test_beat, 1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 2) != 2) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Counting invalid octaves.
    // TODO: Write Test 3
    if (count_notes_in_octave(test_beat, -1) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 11) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    
    
    return MEETS_SPEC;
}

// Test function for `add_beat_to_track`
int test_add_beat_to_track(void){
    // Test 1: Reject wrongly added Beat to Track
    // TODO: Write Test 1
    Beat testBeat1 = create_beat();
    add_note_to_beat(testBeat1, 1, 1);
    Track testTrack = create_track();
    add_beat_to_track(testTrack, testBeat1);
    if (count_beats_left_in_track(testTrack) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 2: Add beat after currently selected Beat when Beat is playing.
    // TODO: Write Test 2
    select_next_beat(testTrack);
    // select beat with octave 1
    
    // add beat with octave 2 to track
    Beat testBeat2 = create_beat();
    add_note_to_beat(testBeat2, 2, 2);
    add_beat_to_track(testTrack, testBeat2);
    
    // add beat with octave 2 to track
    Beat testBeat3 = create_beat();
    add_note_to_beat(testBeat3, 3, 3);
    add_beat_to_track(testTrack, testBeat3);
    select_next_beat(testTrack);
    
    // remove selected beat 
    // (should remove beat with octave 1 and
    // select next beat (beat with octave 2))
    remove_selected_beat(testTrack);
    

    // Test 3: ???
    // TODO: Write Test 3

    return MEETS_SPEC;
}

// Test function for `remove_selected_beat`
int test_remove_selected_beat(void){
    Track testTrack = create_track();
    Beat testBeat1 = create_beat();
    add_note_to_beat(testBeat1, 1, 1);
    add_beat_to_track(testTrack, testBeat1);
    Beat testBeat2 = create_beat();
    add_note_to_beat(testBeat2, 2, 2);
    add_beat_to_track(testTrack, testBeat2);
    Beat testBeat3 = create_beat();
    add_note_to_beat(testBeat3, 3, 3);
    add_beat_to_track(testTrack, testBeat3);
    
    // Test 1: checks if code removes beat when track is stopped
    // TODO: Write Test 1
    if (count_beats_left_in_track(testTrack) == 3) {
        remove_selected_beat(testTrack);
        if (count_beats_left_in_track(testTrack) != 3) {
            return DOES_NOT_MEET_SPEC;
        }
    }
    
    // Test 2: checks if code does not remove beats when track is playing
    // TODO: Write Test 2
    if (count_beats_left_in_track(testTrack) == 3) {
        select_next_beat(testTrack);
        remove_selected_beat(testTrack);
        if (count_beats_left_in_track(testTrack) != 1) {
            return DOES_NOT_MEET_SPEC;
        }
    }

    // Test 3: ???
    // TODO: Write Test 3

    return MEETS_SPEC;
}

// Test function for `add_musical_note_to_beat`
int test_add_musical_note_to_beat(void){
    // Test 1: Checks if code never adds musical notes
    // TODO: Write Test 1
    Beat testBeat = create_beat();
    if (add_musical_note_to_beat(testBeat, "3G") == VALID_NOTE) {
        if (count_notes_in_octave(testBeat, 3) == 0) {
            return DOES_NOT_MEET_SPEC;
        }
    }

    // Test 2: Checks if code rejects invalid inputs
    // TODO: Write Test 2
    if (add_musical_note_to_beat(testBeat, "23##") != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_musical_note_to_beat(testBeat, "3G#a") != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_musical_note_to_beat(testBeat, "3Ga##") != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_musical_note_to_beat(testBeat, "3Ga-+") != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_musical_note_to_beat(testBeat, "3Ga1") != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_musical_note_to_beat(testBeat, "a") != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    } 
    if (add_musical_note_to_beat(testBeat, "G3") != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 3: Checks if code can handle hashes
    // TODO: Write Test 3
    if (add_musical_note_to_beat(testBeat, "3G##") == INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 4: Checks if code rejects duplicate input
    // TODO: Write Test 4
    if (add_musical_note_to_beat(testBeat, "7C") == VALID_NOTE) {
        if (add_musical_note_to_beat(testBeat, "7C")
            != INVALID_MUSICAL_NOTE) {
            return DOES_NOT_MEET_SPEC;            
        }
    }

    return MEETS_SPEC;
}
