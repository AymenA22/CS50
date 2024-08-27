###### DEFINE MAIN ######
def main():
    height = get_height()
    # nested for loop to iterate through each number in height
    for i in range(height):
        for j in range(height):
            if i + j < height - 1:
                print(" ", end="")
            else:
                print("#", end="")
        print()

###### DEFINE GET_HEIGHT ######
# Check for correct usage and return height as n if within parameters
def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if 9 > n > 0:
                return n
        # add exception for incorrect input
        except ValueError:
            print("Not an integer!")


# Add main() as entry point into program
main()
