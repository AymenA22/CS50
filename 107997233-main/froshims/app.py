from flask import Flask, render_template, request, redirect

app = Flask(__name__)


# To add registrants for sports, create an empty dictionary
REGISTRANTS = {}

# Create a list of sports that can be selected
SPORTS = ["Basketball", "Soccer", "Ultimate Frisbee"]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

# New route called Register with the POST method
@app.route("/register", methods=["POST"])
def register():

#option 1
    # This line below will return "Failure" if the user tries to register without entering a name
    #if not request.form.get("name"):
        #return "failure"
    #elseif return failure if the user did not enter a sport
    #elif not request.form.get("sport"):
        #return "failure"
    #else return success
    #return "Success"

#option 2
#OR BETTER YET, tighten it up with an OR NOT

    #if not request.form.get("name") or not request.form.get("sport"):
        #return "failure"
    #return "Success"

#option 3
#OR BETTER YET, send to a webpage if failure or success

    #if not request.form.get("name") or not request.form.get("sport"):
        #return render_template("failure.html")
    #return render_template("success.html")

#option 4
#OR BETTER YET, add validation to make sure the user can only select the sports that are in the list (top of this page SPORTS)

    if not request.form.get("name") or request.form.get("sport") not in SPORTS:
        return render_template("failure.html")
#    return render_template("success.html")

# validate name
    name = request.form.get("name")

# validate sport
    sport = request.form.get("sport")

# Remember registrant
    REGISTRANTS[name] = sport

# Confirm registration
    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    return render_template("registrants.html", registrants=REGISTRANTS) #passes REGISTRANTS into the function in the HTML
