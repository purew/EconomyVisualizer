

import re


def utf8(str):
	"""Translate a latin1-string to utf8-encoding."""
	return unicode(str, "iso-8859-1").encode("utf-8")

def importFile( filename, bank ):
	""" Imports file and returns a tuple of transactions """
	f = open( filename, 'r')
	text = f.read()
	transactions = splitIntoTransactions(text, bank)
	return transactions

def splitIntoTransactions( text, bank ):
	""" Split and return a chunk of text into transactions. 
		Result is a list of tuples with (date, description, cost, balance)."""
	transactions = [] 
	
	pattern = fetchRE( bank )
	re.MULTILINE = True
	results = re.findall( pattern, text )
	for match in results:
		date = match[0]
		description = match[1].decode('utf-8')
		cost = int(match[2].replace(' ',''))
		balance = int(match[3].replace(' ',''))
		transaction = dict( {'date':date, 'description':description, 'cost':cost, 'balance':balance, 'category':-1})
		transactions.append(transaction)
		
	return transactions


def fetchRE( bank ):
	""" Fetch the RE used when splitting transactions for a given bank """
	if (bank == 'swedbank'):
		return '(?m)^(\S{8})\t\S{8}\s\t(.*?)\s*?(-?[\d| ]*?),\d\d\s*?(-?[\d| ]*?),\d\d'
	else:
		raise TypeError('Bank '+str(bank)+' not implemented yet')

if __name__ == '__main__':

	pass
