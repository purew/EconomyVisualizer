
from __future__ import division



def assignCategories( db, transactionRows ):
	""" Assign a category to each transaction in transactions.
		Use earlier manual categorizations to decrease the manual labour """
	
	if transactionRows == None:
		return

	commitAfter = 3 # commit to database this often
	baseDistance = 0.5 # Required Levenschtein distance for algorithm to suggest category
	
	i = 0
	
	for transRow in transactionRows:
				
		# First, check if there is a match in our database
		earlierCategorizations = db.getManualClassifications()
		#print str(len(earlierCategorizations))+" older classifications"
		print "\n\n"
		
		newCat = 0
		
		bestMatch = baseDistance
		for r in earlierCategorizations:
			distance = levenshtein(r[1], transRow[db.tdesc])
			#print r[1]+" - " +transRow[db.tdesc]+" has distance of "+str(distance)
			if distance  < bestMatch:
				print 'Found match between "'+r[1]+'" and "'+transRow[db.tdesc]+'"'
				newCat = r[0]
				bestMatch = distance
			
		doManual = True
		if bestMatch < baseDistance:
			print "Classify "+transRow[db.tdesc]+" as "+str(newCat)+"?"
			response = str.lower(raw_input('Y/n'))
			if response == 'y' or response == '':
				doManual = False

		if doManual:
			# No earlier categorization found. Do manual
			print "Please categorize \""+transRow[db.tdesc]+'"'
			print "1) Food"
			print "2) Apartment"
			print "3) Travelling"
			print "4) Recreation"
			print "0) Other"
			chosenCategory = int(raw_input('-->'))
			newCat = chosenCategory
			
			# Add this classification to database
			db.addManualClassification( chosenCategory, transRow[db.tdesc])
			
		# Go ahead and set category
		db.cur.execute("UPDATE transactions SET category=? WHERE id=?",(newCat,transRow[db.tid],))
		i += 1
		if i==commitAfter:
			db.commit()
			i=0
		

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
