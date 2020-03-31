from cs50 import SQL
import sys

if (len(sys.argv) != 2):
    print("Usage: python roster.py <house>")
    sys.exit(1)

db = SQL("sqlite:///students.db")
query = db.execute("SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first", sys.argv[1])
for row in query:
    if row['middle'] == None:
        print(row['first'], row['last'] + ",", "born", row['birth'])
    else:
        print(row['first'], row['middle'], row['last'] + ",", "born", row['birth'])

