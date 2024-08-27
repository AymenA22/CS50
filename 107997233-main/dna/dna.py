######## IMPORTS #########
import csv
import sys

########## DEFINE MAIN ##########


def main():

    # TODO: Check for command-line usage
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
        # Convert the CSV file into a dictionary called "CSV_Dictionary"
        CSV_Dictionary = csv.DictReader(csv_file)
        # print("FIELD NAMES: ", reader.fieldnames)
        # Create an array for the STRs in the CSV File excluding the key
        STRs_from_CSV = CSV_Dictionary.fieldnames[1:]
        # convert each row of the CSV File to a new row in the reader variable
        for row in CSV_Dictionary:
            database.append(row)
        # print("DATABASE: ", database)
        # print(STRs_from_CSV)

    # TODO: Read DNA sequence file into a variable
    # Open the text file in Read Mode
    with open(txt_sequence, 'r') as text_file:
        # Read the text from the file into a variable called "dna_sequence"
        dna_sequence = text_file.read()
        # print("DNA SEQUENCE: ", dna_sequence)

    # TODO: Find longest match of each STR in DNA sequence
    # For the each subsequence in the list of subsequences (STRs_from_CSV) return the longest match
    # Do this by inputting the dna_sequence and the subsequence into LONGEST MATCH
    # Create a dictionary for the result
    result = {}
    # Create a "for" loop, to iterate through each STR in the list of subsequences (STRs_from_CSV)
    for STR in STRs_from_CSV:
        # Return the result from the longest match function
        result[STR] = longest_match(dna_sequence, STR)

    # TODO: Check database for matching profiles
    # Create a for loop to compare each name in the database and count for a match
    for name in database:
        counter = 0
        # for each STR in the list of subsequences (STRs_from_CSV)
        for STR in STRs_from_CSV:
            # if the number of subsequences (STRs_from_CSV) matches the name
            if int(name[STR]) == result[STR]:
                # increment the counter by 1
                counter += 1

        # If the counter for all subsequences (STRs_from_CSV) match a name, return the name
        if counter == len(STRs_from_CSV):
            print(name["name"])
            return

    # If there is no match, print "No Match"
    print("No Match")
    return (1)


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
