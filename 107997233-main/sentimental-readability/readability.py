from cs50 import get_string
import string

text = input("Text: ")
Letter_Count = 0
Word_Count = 1
Sentence_Count = 0

for character in text:
    if character == "!" or character == "?" or character == ".":
        Sentence_Count = Sentence_Count + 1
    elif character in string.punctuation:
        continue
    elif character in string.whitespace:
        Word_Count = Word_Count + 1
    else:
        Letter_Count = Letter_Count + 1

# Average number of letters per 100 words in the text
L_Ave = Letter_Count / Word_Count * 100
# Average number of sentences per 100 words in the text
S_Ave = Sentence_Count / Word_Count * 100
index = round(0.0588 * L_Ave - 0.29 * S_Ave - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
