from cs50 import get_string

text = get_string("Text: ")
numOfLetters = 0
numOfWords = 1
numOfSentences = 0
for i in range(len(text)):
    if text[i].isalpha():
        numOfLetters += 1
    elif text[i].isspace():
        numOfWords += 1
    elif text[i] == '.' or text[i] == '!' or text[i] == '?':
        numOfSentences += 1

l = numOfLetters / numOfWords * 100
s = numOfSentences / numOfWords * 100
index = 0.0588 * l - 0.29 * s - 15.8
index = round(index)

if index > 16:
    print("Grade 16+")
elif index > 1 and index < 17:
    print(f"Grade {index}")
else:
    print("Before Grade 1")


if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")








count_letter = 0
count_word = 1
count_sentence = 0

#Collecting input from user
text = input("Text: ")
text_length = len(text)

#count the number of letters in the text
for i in range(text_length):
    if(text[i].isalpha()):
        count_letter+=1

#count the number of words in text
    if (text[i].isspace()):
        count_word +=1

#count the number of sentence
    if(text[i] == '.' or text[i] == '?' or text[i] == '!'):
        count_sentence +=1

calculation = (0.0588 * count_letter / count_word * 100) - (0.296 * count_sentence / count_word * 100) - 15.8 #to calculate Index

index = round(calculation)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
