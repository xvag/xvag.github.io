#! python3
# mcb.pyw - Saves and loads pieces of text to the clipboard.
# Usage: python mcb.pyw save <keyword> - Saves clipboard to keyword
#	 python mcb.pyw <keyword> - Loads keyword to clipboard.
#	 python mcb.pyw list - Loads all keywords to clipboard.

import shelve, pyperclip, sys

mcbShelf = shelve.open('mcb')

if len(sys.argv)==3 and sys.argv[1].lower()=='save':
	mcbShelf[sys.argv[2]]=pyperclip.paste()
	print(sys.argv)
elif len(sys.argv)==2:
	if sys.argv[1].lower()=='list':
		print(str(list(mcbShelf.keys())))
	elif sys.argv[1] in mcbShelf:
		pyperclip.copy(mcbShelf[sys.argv[1]])

mcbShelf.close()
