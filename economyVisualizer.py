


import databaseHandler
import dataImport
import categorizer




if __name__ == '__main__':
	
	
	transactions = dataImport.importFile('data.dump', 'swedbank')
	
	db = databaseHandler.database()
	
	for transaction in transactions:
		db.addTransaction(transaction)
	
	
	transactions = categorizer.assignCategories( db, transactions )
	
	
	
	
	db.closeDatabase()
	
	
