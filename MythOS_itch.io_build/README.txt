Welcome to MythOS!
Join our Discord server: https://discord.gg/rPM6Y2ABRX

-----------------------------------------------------------------
			How to begin
MythOS always starts with the file called "START.txt", so make sure it's there!
MythOS only ends when it is sent to "End.txt", so make sure that's also there!
(Nothing in "End.txt" gets printed out)

Modify "START.txt" with whatever you want, and link it to some
other text files. You'll see the linker line at the bottom of
"START.txt" and of "Middle.txt". Notice you don't need to include
".txt" when adding files to the linker line.

-----------------------------------------------------------------
			   Linking

The linker line is surrounded in square brackets [ and ].
Write the names of the text files to link to with commas in between -- 
			NO SPACES AFTER COMMAS
	(unless you get us on Discord, then we might build that in)
Also, don't include ".txt" at the end of the filename -- MythOS will 
take care of that for you. ;)

-----------------------------------------------------------------
			Using folders

The first time you link to a .txt file within a folder, include
the full filepath to that file ("folder1\folder2\myFile.txt", for example).
Once you're in the folder, MythOS remembers and you don't need to keep
adding the full filepath!

To go back to the top folder (where _MythOS.exe is located), 
start the filepath with "PARENTFOLDER\..." and MythOS will reset whatever
filepath it was storing. You're back in the parent folder!

-----------------------------------------------------------------
			Little technicalities

You can't have more than 200 newlines in a single description.
Contact us if you need more! 

Always make sure to end your files with the linker line! 
(It must be surrounded by square brackets, [ and ])