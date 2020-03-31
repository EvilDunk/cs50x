from cs50 import SQL
import csv
import sys

if (len(sys.argv) != 2):
    print("Usage: python import.py <text>.csv")
    sys.exit(1)
    
csvfile = sys.argv[1]
opencsvfile = open(csvfile)
data = csv.DictReader(opencsvfile)
db = SQL("sqlite:///students.db")


for row in data:
    fname = ""
    mname = ""
    lname = ""
    fullname = row['name'].split()
    if (len(fullname) == 2):
        fname = fullname[0]
        lname = fullname[1]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                fname, None, lname, row['house'], row['birth'])
    if (len(fullname) == 3):
        fname = fullname[0]
        mname = fullname[1]
        lname = fullname[2]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                    fname, mname, lname, row['house'], row['birth'])
    
    

