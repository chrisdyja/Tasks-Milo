# Tasks-Milo


GENERAL:

I hope code is atleast a little self explanatory.

================ Morse Code translator ================

-

=======================================================

================== Anagram Derivation =================

Note:
The algorithm's main drawback is that while searching for the new N+1 word derivative, it accepts the first possibility and continues to search for N+2 word derivative and so on...



current_word = <users 3 letter input word>

Loop through sorted by length dictionary

if (current_word.length+1 == current_word_in_sorted_dictionary)

true -> loop through alphabet
  
tmp = sort_by_letters(current_word+current_alphabet_letter)
              
if(tmp == current_word_in_sorted_dictionary)
              
true -> output_chain.append(tmp)

continue 

=======================================================
