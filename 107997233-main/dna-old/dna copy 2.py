######## IMPORTS #########
import csv
import sys

########## DEFINE MAIN ##########
def main():

    # Check for command-line usage
    # If the length of the input arguement is not equal to 3, print error
    if len(sys.argv) != 3:
        print("Usage must be: python dna.py ***.csv ***.txt")
        sys.exit(1)

    csv_data = sys.argv[1]
    txt_sequence = sys.argv[2]

    # TODO: Read database file into a variable
    # Create an array for the database
    database = []
    STRs_from_CSV = []
    # Open the CSV File in Read Mode
    with open(csv_data, 'r') as csv_file:
        # Convert the CSV file into a dictionary called "reader"
        reader = csv.DictReader(csv_file)
        #print("FIELD NAMES: ", reader.fieldnames)
        # Create an array for the STRs in the CSV File
        STRs_from_CSV = reader.fieldnames[1:]
        # convert each row of the CSV File to a new row in the reader variable
        for row in reader:
            database.append(row)
        #print("DATABASE: ", database)
        #print(STRs_from_CSV)

    # TODO: Read DNA sequence file into a variable
    # Open the text file in Read Mode
    with open(txt_sequence, 'r') as text_file:
        # Read the text from the file into a variable called "dna_sequence"
        dna_sequence = text_file.read()
        #print("DNA SEQUENCE: ", dna_sequence)

#OK TO THIS POINT

    # Find longest match of each STR in DNA sequence
    # For the each subsequence in the list of subsequences (STRs_from_CSV) return the longest match
    # Do this by inputting the dna_sequence and the subsequence into LONGEST MATCH
    # First, create a variable for the result
    result = {}
    # Create a for loop, to iterate through each sequence in the list of subsequences
    for subsequence in STRs_from_CSV:
        # Return the result from the longest match function
        result[subsequence] = longest_match(dna_sequence, subsequence)

    # Check database for matching profiles
    # Create a for loop to compare each person in the database and count for a match
    for person in database:
        match = 0
        # for each subsequence in the list of subsequences (STRs_from_CSV)
        for subsequence in STRs_from_CSV:
            # if the number of subsequences matches the person
            if int(person[subsequence]) == result[subsequence]:
                # increment the counter "match" by 1
                match += 1

        # If all subsequences match the person, return their name
        if match == len(STRs_from_CSV):
            print(person["name"])
            return

    # If there is no match, print "No Match"
    print("No Match")
    return(1)

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
