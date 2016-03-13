REGEX Worksheet for Cleaning HTML tags


Find all HTML tags
FIND:
<.+?>
REPLACE: *leave blank*

Final all instances of &nbsp;
FIND:
REPLACE: *leave blank*

	#There may be some HTML or CSS coding leftover near the top/beginning of the text file, this can easily be removed manually. Lines 5-50
	#For this particular document the column names can be found just below the line which reads "List of all Event assertions around a specific date." This would be line 64 for if the above step has not been taken yet or line 24 if it has.
		#To format this for a CSV these column titles need to be on one line and separated by a comma. (CSV stands for Comma Separated Values). Again, this is easy to do manually.

Reformat source/publication information example London: 1645, 7 becomes London: 1645 p.7
FIND: 
([0-9]{4}), ([0-9]{1,})
([0-9]{4}), ([0-9]{1,}-[0-9]{1,})
REPLACE:
\1 p.\2

Remove all commas
FIND:
(,)
REPLACE: *leave blank*

		#Putting the source publication information inbetween brackets will keep them from getting mixed up in our later expressions.
		FIND:
		(London: 16\d\d p\..+)\n
		(London: 16\d\d)\n
		(London: 16\d\d Cover .+)\n
		(London: 16\d\d Cover)\n
		(London: [0-9]{4} p\.[0-9]{1,}$)
		REPLACE:
		(\1)


Remove all doubles spaces at beginning of lines.
FIND:
^(  )
REPLACE: *leave blank*

	#Begin to join the locations together. Keeping in mind that some of the results have all 5 location columns filled. It helps to refer back to the original html page that you downloaded. I started with nation and worked backwards. (starting from screenshot 18)
FIND:
(\s)+(England)
REPLACE:
,\2

There are severals rows that are missing both the city and the parish information. Using this expression will take into account those blank cells.
FIND:
(1645)\n\s\s\n
REPLACE:
\1, , ,

				#The result should look like: 
					line 1314	1645, , ,Suffolk
					line 1315	Suffolke,England

This next expression takes into account any rows which had blank cells in the city column. By adding , , we are accounting for that blank cell and ensuring that our information remain in the correct columns. This needs to be done for each of the location columns.
FIND:
(1645)\n\s
REPLACE:
\1, ,
				#The result should look like: 
					line 183  1645, , St. Osyth; St. Ofes; St. Oses
					line 184  Essex
					line 185  Essex,England

Lastly there are results that do not contain parish or old county.
FIND: 
(1645)\n(\w.+)\n\s\n(\w.+)
REPLACE:
\1,\2,,\3
	
	#The result should look like: 
			line 154  1645,Ramsey,,Essex
			line 155  Essex,England

The above results you'll want to use this expression to join them all onto one line.
FIND: 
(1645,.+)\n(.+\w)
REPLACE:
\1,\2

	#If they still aren't all on one line, just repeat the exact same expression.
	
For results that have data in all 5 location columns, we have already begun to collect them together when we removed the extra space between the country and the old county columns. For example:
		line 1890 1645
		line 1891 Manningtree
		line 1892  Manningtree
		line 1893 Essex
		line 1894 Essex, England
	#Now we just need to continue to collect them together, continuing to use the date as an anchor of sorts. BUT! Before we do this there are a couple of things mistakes that need to be cleaned up. Some of the sources which we were formatting earlier did not have page numbers therefore the line ended with just a date and accidentally got mixed up with our regex patterns
FIND: 
(1645)\n(.+\w)\n (.+\w)\n(.+\w)\n(.+\w)
REPLACE:
\1,\2,\3,\4,\5

Remove all blank lines
FIND:
^\n
REPLACE: *leave blank*

Join the date and location lines to the source line, separating it with a comma. I chose to get rid of some of the extra space there as well.
FIND:
\s\n(1645.+)
REPLACE:
,\1

	#The next step deals with the source line and the lines which contain "Appears in:"

Find each line that begins with "Appears in" followed by a line containing source information and format so that it joins the description line above it and the line with source information is joined to it. 
FIND: \n(\sAppears in:)\n
REPLACE: \1
	
	#The final step is joining the Row ID numbers. 
	#Now I am able to use a regular expression to locate the ID number without it also recognizing the date. {#} looks for a pattern containing a number with only a specific amount digits, but if I add a comma {#,} it tells it to look for either # or more.
Find each line that contains only digits, this are the ID numbers, and join the line with the description line separating them with a comma.
FIND: ^([0-9]{1,})\n
REPLACE: \1,


Join the date 1645, to the description description line with a comma separating the description value and the data value. 
FIND:\n\s\n(1645,)
REPLACE:,\1

