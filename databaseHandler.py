

import sqlite3
import hashlib

class database:
	""" Class for handling the database and the communication protocol """

	def __init__(self):
		self.databaseFilename = 'data.sql'
		self.cur = 0
		#self.dbcurection = 0
		self.initializeDatabase()
		
		# Transaction column id's
		self.tid=0  
		self.tdate=1
		self.tdesc=2
		self.tcost=3
		self.tbal=4
		self.tcat=5
		self.tcheck=6
		
	def addTransaction(self, transaction):
		""" Adds a transaction to database if it not already exists """
		
		#transaction = dict( {'date':date, 'description':description, 'cost':cost, 'balance':balance})
		
		checksumParts = str(transaction['date'])+transaction['description'].encode('utf8')+str(transaction['cost']+transaction['balance'])
		checksum = hashlib.md5(checksumParts).hexdigest()

		self.cur.execute('SELECT * FROM transactions WHERE checksum = ?',[checksum])
		if self.cur.fetchone() == None:
			# No match, go ahead and add transaction to database
			preprocTransaction = (transaction['date'], transaction['description'], transaction['cost'], transaction['balance'], transaction['category'],checksum,)
			self.cur.execute("INSERT INTO transactions (date, description, amount, balance, category, checksum) VALUES (?,?,?,?,?,?)", preprocTransaction)
		else:
			print "Transaction already added to table"
		
		

	def initializeDatabase(self):
		""" Set up the database curection. """
		
		self.dbConnection = sqlite3.connect( self.databaseFilename )
		self.cur = self.dbConnection.cursor()
		
		# Set up tables if not already done
		# Transactions
		self.cur.execute('''SELECT * FROM sqlite_master WHERE type='table' AND name='transactions';''')
		response = self.cur.fetchone()
		if response == None:
			print "Adding tables"
			self.cur.execute('''CREATE TABLE transactions (id INTEGER PRIMARY KEY, date INTEGER, description TEXT, amount REAL,  balance REAL, category INTEGER, checksum TEXT)''')
		
		# Categories
		self.cur.execute('''SELECT * FROM sqlite_master WHERE type='table' AND name='categories';''')
		response = self.cur.fetchone()
		if response == None:
			self.cur.execute('''create table categories (id INTEGER, name TEXT)''')
		
		# Memory bank of descriptions and assigned categories
		self.cur.execute('''SELECT * FROM sqlite_master WHERE type='table' AND name='assignedCategories';''')
		response = self.cur.fetchone()
		if response == None:
			self.cur.execute('''CREATE TABLE assignedCategories (id INTEGER, description TEXT)''')
		
		
	def getUnclassifiedTransactions(self):
		""" Return all rows of unclassified transactions """
		self.cur.execute('SELECT * FROM transactions WHERE category=-1')
		return self.cur.fetchall()
		
	def getManualClassifications( self ):
		""" Retrieve list of manual classifications """
		
		self.cur.execute('SELECT * FROM assignedCategories ')
		return self.cur.fetchall()
		
	def addManualClassification( self, id, description ):
		""" Add a manual classification to database """
		self.cur.execute("INSERT INTO assignedCategories VALUES (?,?)",[id, description])
		
	def closeDatabase(self):
		""" Securely save and close database curection """
		
		self.dbConnection.commit()
		self.dbConnection.close()

	def commit(self):
		""" Commit changes to database """
		self.dbConnection.commit()
		
	
if __name__ == '__main__':

	db = database()
	db.initializeDatabase()
	
	
	db.closeDatabase()
	
	
