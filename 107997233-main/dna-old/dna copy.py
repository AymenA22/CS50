######## IMPORTS #########
import csv
import sys
#from csv import reader, DictReader
#from sys import argv, exit

########## DEFINE MAIN ##########
def main():

    # TODO: Check for command-line usage
    # If the length of the input arguement is not equal to 3, print error
    if len(sys.argv) != 3:
        print("Usage must be: python dna.py ***.csv ***.txt")
        sys.exit(1)

    # If argv has 3 elements then assign argv[1] and argv[2] to variables for ease
    database = sys.argv[1]
    sequence = sys.argv[2]

    # TODO: Read database file into a variable
    # Open the database csv file as a csv file in read mode
    with open(database, 'r') as csv_file:
        # create a variable for the dictionary
        reader = DictReader(csv_file)
        db = list(reader)

    # TODO: Read DNA sequence file into a variable
    with open(sequence, 'r') as file
        seq = file.read()


    # TODO: Find longest match of each STR in DNA sequence



    # Define an empty array as a counter for the length of each DNA sequence
    str_len = []

    for i in range(l, len(reader.fieldnames)):


    # Loop through each STR in the DNA sequence
    # Iterate through the fieldnames


    AGATC = compute('AGATC', text)
    AATG = compute('AATG', text)
    TATC = compute('TATC', text)
    TTTTTTCT = compute('TTTTTTCT', text)
    TCTAG = compute('TCTAG', text)
    GATA = compute('GATA', text)
    GAAA = compute('GAAA', text)
    TCTG = compute('TCTG', text)


    # TODO: Check database for matching profiles

    return


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
