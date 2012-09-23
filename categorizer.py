
from __future__ import division



def assignCategories( db, transactions ):
	""" Assign a category to each transaction in transactions.
		Use earlier manual categorizations to decrease the manual labour """
	
	if transactions == None:
		return

	
	for transaction in transactions:
				
		# First, check if there is a match in our database
		earlierCategorizations = db.getManualClassifications()
		print "\n\n"
		
		baseDistance = 0.5
		bestMatch = baseDistance
		for r in earlierCategorizations:
			distance = levenshtein(r[1], transaction['description'])
			if distance  < bestMatch:
				print 'Found match between "'+r[1]+'" and "'+transaction['description']+'"'
				transaction['category'] = r[0]
				bestMatch = distance
			
		if bestMatch < baseDistance:
			print "Classify "+transaction['description']+" as "+str(transaction['category'])+"?"
			response = str.lower(raw_input('Y/n'))
			if response == 'y' or response == '':
				continue
			
		# No earlier categorization found. Do manual
		print "Please categorize \""+transaction['description']+'"'
		print "1) Food"
		print "2) Apartment"
		print "3) Travelling"
		print "4) Recreation"
		print "0) Other"
		chosenCategory = int(raw_input('-->'))
		transaction['category'] = chosenCategory
		
		# Add this classification to database
		db.addManualClassification( chosenCategory, transaction['description'])
		db.commit()
		

def levenshtein(a,b):
    "Calculates the Levenshtein distance between a and b."
    n, m = len(a), len(b)
    if n > m:
        # Make sure n <= m, to use O(min(n,m)) space
        a,b = b,a
        n,m = m,n
        
    current = range(n+1)
    for i in range(1,m+1):
        previous, current = current, [i]+[0]*n
        for j in range(1,n+1):
            add, delete = previous[j]+1, current[j-1]+1
            change = previous[j-1]
            if a[j-1] != b[i-1]:
                change = change + 1
            current[j] = min(add, delete, change)
            
    return current[n]/m


if __name__=="__main__":
    from sys import argv
    print levenshtein(argv[1],argv[2])
