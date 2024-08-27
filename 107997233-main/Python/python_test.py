import csv
from csv import reader

with open('file.csv', newline='') as csvfile:
    reader = csv.DictReader(csvfile)
    reader.fieldnames = ['field1', 'field2', 'field3']
    print('Fieldnames: ', reader.fieldnames)

