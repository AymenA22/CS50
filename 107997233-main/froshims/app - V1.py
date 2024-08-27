from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

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

    if not request.form.get("name") or not request.form.get("sport"):
        return render_template("failure.html")
    return render_template("success.html")
