# VI-Editor
A program using various data structures in C++ to simulate simple elements of a VI editor such as typing in sentences, deleting, undoing, and saving sentences to a .txt file. 

Simply add each file (.h, .cpp, .inl) to the corresponding containers from visual studio and debug the program.

Inputting a new sentence(node) onto a file
<img src="VI-editor sample output.png">

Shows the new sentence added to the current line
<img src="VI-editor sample output inserting new sentence.png">

The txt file with the VI editor contents with the changes saved
<img src="changes save to txt file.png">

Save changes to a file
<img src="Save to file.png">

Key commands available:
	j - move cursor down
	k - move cursor up
	h - move cursor left
	dd - delete whole current line
	u - undo previous command

	i - insert text incurrent line
	I - insert new line
	x - delete a character on cursor

	<ESC> - leave editing mode
	q - exit program
	
