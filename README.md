*This activity has been created as part of the 42 curriculum by mschyns*

## Description
The goal of this project is to create a function that will read from a file descriptor (file, standard input, ...) and return the first line that the function can read from it.

## Instructions
**If you wish to use this function in your programs, you must:**

**Place the following at the top of your program:**

	 #include "get_next_line.h"

**Then run your program by compiling the two .c files:**

	 cc -Wall -Wextra -Werror get_next_line_utils.c get_next_line.c program.c

**Program is the name of your program.**

**You can add a flag during compilation to determine the read buffer size yourself.**
**That is, how many blocks of the file will be read.**

	 cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_utils.c get_next_line.c program.c

**Here, the size is set to 42. You can change it as you wish.**

## Resources

More information on the scope of variables: https://www.codequoi.com/variables-locales-globales-statiques-en-c/https://en.cppreference.com/c/preprocessor/error

Preprocessor error handling :  https://en.cppreference.com/c/preprocessor/error

AI (chatgpt):
Was used to perform the English translation of README.md

## Description of the algorithm

At first, I planned to read the file character by character, in a very inefficient way, until I encountered a \n. From there, I would extract a line by storing each character one by one into a dynamic array that would double in size whenever it reached its capacity limit.

Since the assignment mentioned using a BUFFER_SIZE to read the file in chunks, I revisited my approach to adapt it to block-based reading.

I eventually concluded that the goal was to manage a fixed-size buffer. The algorithm reads the file in blocks of BUFFER_SIZE, then searches within each block for a \n. If it finds one, it records its position.

If no \n is found in the buffer that was just read, it means the content read is only part of the line to return. Therefore, it must be stored before continuing to read the rest. I then store it in a character string whose size grows dynamically. As we progress through the file, this string keeps expanding.

So the algorithm keeps storing what it reads until it either encounters a \n or reaches the end of the file. Everything is accumulated into a growing string based on the characters read.

When a \n is found, or EOF is reached, the search stops. The algorithm appends the relevant characters to the string: either up to the end of the file, or up to and including the \n if one was found.

For subsequent reads, the remaining part of the buffer after the \n must be preserved. This means shifting the remaining characters in the buffer so that reading can continue correctly from where it stopped.

Example :

	 ['a','b','c','\n','d','e', ...];

-> We extract:

	 abc\n
	
->But we no longer need abc\n for the next step.

So we shift the buffer:

Before:

	 ['a','b','c','\n','d','e', ...];

After: 

	 ['d','e', ...];

This allows the next function call to continue directly from e, since the position of the unread part of the buffer is stored.

**-> Concretely, the algorithm:**

- Reads until EOF is reached or a \n is found
- Reads the file in BUFFER_SIZE chunks
- Searches for a \n in the newly read data
- If none is found, stores everything in a growing string
- If one is found, stores data up to and including the \n
- Returns the constructed line
- Preserves the remaining unread part of the buffer after the \n for the next call